//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <xatlas.h>
#include <gfx/Cpp20.h>
module two.gfx.pbr;
#else

#include <cstdio>
#include <stl/algorithm.h>
#include <infra/Log.h>
#include <math/Vec.hpp>
#include <geom/Intersect.h>
#include <tree/Graph.hpp>
#include <pool/ObjectPool.hpp>
#include <gfx/Item.h>
#include <gfx/Shot.h>
#include <gfx/Camera.h>
#include <gfx/Graph.h>
#include <gfx/Scene.h>
#include <gfx/Assets.h>
#include <gfx/GfxSystem.h>
#include <gfx/Pipeline.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/VoxelGI.h>
#include <gfx-pbr/Lighting.h>
#include <gfx-pbr/Shadow.h>
#include <gfx-pbr/Lightmap.h>
#include <gfx-pbr/PipelinePbr.h>
#include <gfx-pbr/Gpu/VoxelGI.hpp>
#endif

#define LIGHTMAP_XATLAS

namespace two
{
	GpuState<GpuVoxelGI> GpuState<GpuVoxelGI>::me;
	GpuState<GIProbe> GpuState<GIProbe>::me;

namespace gfx
{
	template <class T, class... Args>
	inline T& create(Scene& scene, Args&&... args)
	{
		return scene.m_pool->pool<T>().construct(static_cast<Args&&>(args)...);
	}

	GIProbe& gi_probe(Gnode& parent, uint16_t subdiv, const vec3& extents)
	{
		Gnode& self = parent.suba();
		GIProbe* gi_probe = self.as<GIProbe>();
		if(!gi_probe)
			gi_probe = self.instantiate<GIProbe>(*self.m_scene, *self.m_attach);
		if(subdiv != gi_probe->m_subdiv || extents != gi_probe->m_extents)
			gi_probe->resize(subdiv, extents);
		return *gi_probe;
	}

	LightmapAtlas& lightmap(Gnode& parent, uint32_t resolution, float density, const string& save_path)
	{
		Gnode& self = parent.suba();
		LightmapAtlas* lightmap_atlas = self.as<LightmapAtlas>();
		if(!lightmap_atlas)
		{
			lightmap_atlas = self.instantiate<LightmapAtlas>(*self.m_scene, resolution, density);
			lightmap_atlas->m_dirty = true;
		}
		lightmap_atlas->m_save_path = save_path;
		return *lightmap_atlas;
	}
}

	struct gpu_ GpuGIProbe
	{
		attr_ gpu_ mat4 transform;
		attr_ gpu_ vec4 params;
		attr_ gpu_ vec4 bounds;
		attr_ gpu_ vec4 inv_extents;
		attr_ gpu_ vec4 cell_size;
	};

	GIProbe::GIProbe(Node3& node)
		: m_node(node)
	{}

	GIProbe::~GIProbe()
	{}

	void GIProbe::resize(uint16_t subdiv, const vec3& extents)
	{
		m_transform = bxidentity();
		m_subdiv = subdiv;
		m_extents = extents;

		m_normal_bias = length(extents * 2.f / float(subdiv)) * sqrt(2.f) * 2.f;

		m_raster = { uvec2(uint(subdiv)), false, TextureFormat::RGBA8, BGFX_TEXTURE_RT };
		m_voxels_color   = { uvec3(uint(subdiv)), false, TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE };
		m_voxels_normals = { uvec3(uint(subdiv)), false, TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE };
		m_voxels_light   = { uvec3(uint(subdiv)), false, TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE };

		m_fbo = { uvec2(subdiv, subdiv), { &m_raster, &m_voxels_color, &m_voxels_normals, &m_voxels_light } };
		
		m_voxels_light_rgba = { uvec3(uint(subdiv)), true, TextureFormat::RGBA16F, BGFX_TEXTURE_RT | BGFX_TEXTURE_COMPUTE_WRITE };

		m_dirty = true;
	}

	void save_gi_probe(GfxSystem& gfx, GIProbe& gi_probe, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path)
	{
		const uint16_t subdiv = gi_probe.m_subdiv;
		Texture texture = { uvec3(subdiv, subdiv, subdiv), true, TextureFormat(source_format), BGFX_TEXTURE_BLIT_DST | BGFX_TEXTURE_READ_BACK };
		bgfx::blit(0, texture, 0, 0, 0, 0, gi_probe.m_voxels_light_rgba, 0, 0, 0, 0, subdiv, subdiv, subdiv);
		bgfx::frame();
		bgfx::frame();

		save_texture(gfx, texture, path, TextureFormat(target_format));
	}

	void load_gi_probe(GfxSystem& gfx, GIProbe& gi_probe, const string& path)
	{
		gi_probe.m_voxels_light_rgba = { "voxels" };
		gi_probe.m_voxels_light_rgba.load(gfx, path);
	}

	void pass_voxel_gi(GfxSystem& gfx, Render& render)
	{
		static BlockLight& block_light = *gfx.m_renderer.block<BlockLight>();
		static BlockShadow& block_shadow = *gfx.m_renderer.block<BlockShadow>();
		static BlockGIBake& block_gi_bake = *gfx.m_renderer.block<BlockGIBake>();

		Pass pass = render.next_pass("voxelGI", PassType::VoxelGI);

		block_light.submit(render, pass);
		block_shadow.submit(render, pass);
		block_gi_bake.submit(render, pass);

		bool conservative = (bgfx::getCaps()->supported & BGFX_CAPS_CONSERVATIVE_RASTER) != 0;
		if(!conservative)
			warn("rendering GI probe without conservative raster support will produce wrong output");

		UNUSED(render); UNUSED(pass);
		pass.m_bgfx_state = BGFX_STATE_CONSERVATIVE_RASTER | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA;

#ifndef VOXELGI_COMPUTE_LIGHTS
		GIProbe& gi_probe = *block_gi_bake.m_bake_probe; UNUSED(gi_probe);
		mat4 view = bxidentity();//gi_probe.m_transform * bxscale(1.f / gi_probe.m_extents);
		block_light.setup_lights(render, view);
		block_shadow.commit_shadows(render, view);
#endif

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(gfx); UNUSED(render); UNUSED(pass);
			const Program& program = *element.m_program.m_program;
			if(!program.m_blocks[MaterialBlock::Lit])
				return false;

			element.set_program(*block_gi_bake.m_voxelize);
			return true;
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	}

	void pass_gi_probes(GfxSystem& gfx, Render& render)
	{
		static BlockGIBake& block_gi_bake = *gfx.m_renderer.block<BlockGIBake>();

		if(!check_lighting(render.m_lighting, Lighting::VoxelGI))
			return;

		PBRShot& shot = static_cast<PBRShot&>(*render.m_shot);
		for(GIProbe* gi_probe : shot.m_gi_probes)
		{
			if(!gi_probe->m_enabled || !gi_probe->m_dirty)
				continue;

			if(gi_probe->m_mode == GIProbeMode::Voxelize)
			{
				info("bake GIProbe");

				block_gi_bake.voxelize(render, *gi_probe);
				block_gi_bake.output(render, *gi_probe);

				for(int i = 0; i < gi_probe->m_bounces; ++i)
				{
					// @todo fix D3D bounce bug
					block_gi_bake.bounce(render, *gi_probe);
					block_gi_bake.output(render, *gi_probe);
				}

				gi_probe->m_dirty = false;

				info("bake GIProbe done");

				//string path = m_gfx.m_resource_path + "/" + "gi_probe.dds";
				//save_gi_probe(m_gfx, *gi_probe, bgfx::TextureFormat::RGBA16F, bgfx::TextureFormat::BC6H, path);
			}

			if(gi_probe->m_mode == GIProbeMode::LoadVoxels)
			{
				string path = gfx.m_resource_path + "/" + "gi_probe.dds";
				load_gi_probe(gfx, *gi_probe, path);
			}
		}
	}

	BlockGIBake::BlockGIBake(GfxSystem& gfx, BlockLight& block_light, BlockShadow& block_shadow, BlockGITrace& block_trace)
		: DrawBlock(gfx, type<BlockGIBake>())
		, m_block_light(block_light)
		, m_block_shadow(block_shadow)
		, m_block_trace(block_trace)
	{}

	void BlockGIBake::init_block()
	{
		u_voxelgi.createUniforms();

		m_voxelize = &m_gfx.programs().fetch("gi/voxelize");
		m_direct_light = &m_gfx.programs().fetch("gi/direct_light");
		m_bounce_light = &m_gfx.programs().fetch("gi/bounce_light");
		m_output_light = &m_gfx.programs().fetch("gi/output_light");
	}

	void BlockGIBake::voxelize(Render& render, GIProbe& gi_probe)
	{
		m_bake_probe = &gi_probe;

		vec3 extents = gi_probe.m_extents;
		
		Camera camera = { gi_probe.m_transform, vec2(extents.x * 2.f, extents.y * 2.f), -extents.z, extents.z };
		Viewport viewport = { camera, *render.m_scene, Rect4 };
		Render voxel_render = { Shading::Voxels, viewport, *render.m_target, gi_probe.m_fbo, *render.m_frame };

		ShadowFilterMode pcf_level = m_block_shadow.m_pcf_level;
		//uint8_t splits = 0;
		m_block_shadow.m_pcf_level = PCF_NONE;
		//if(m_block_light.m_direct_light)
		//{
		//	splits = m_block_light.m_direct_light->m_shadow_num_splits;
		//	m_block_light.m_direct_light->m_shadow_num_splits = 1;
		//}

		Plane6 planes = frustum_planes(camera.m_proj, camera.m_view);
		voxel_render.m_shot->m_lights = render.m_shot->m_lights;
		cull_items(*render.m_scene, planes, voxel_render.m_shot->m_items);
		m_gfx.m_renderer.subrender(render, voxel_render, m_gfx.renderer(Shading::Voxels));

		//if(m_block_light.m_direct_light)
		//{
		//	m_block_light.m_direct_light->m_shadow_num_splits = splits;
		//}
		m_block_shadow.m_pcf_level = pcf_level;

		if(m_direct_light_compute)
			this->compute(render, gi_probe);
	}

	void BlockGIBake::compute(Render& render, GIProbe& gi_probe)
	{
		Pass pass = render.next_pass("gi direct", PassType::VoxelGI);
		bgfx::Encoder& encoder = *pass.m_encoder;

		encoder.setImage(0, gi_probe.m_voxels_color,   0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(1, gi_probe.m_voxels_normals, 0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(2, gi_probe.m_voxels_light,   0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);

		GpuState<GpuVoxelGI>::me.upload(encoder, gi_probe);

		m_block_light.setup_lights(render, bxidentity());
		m_block_light.commit_lights(render, pass);
		m_block_shadow.commit_shadows(render, bxidentity());

		ProgramVersion program = { *m_direct_light };

		uint16_t subdiv = gi_probe.m_subdiv;
		if(bgfx::isValid(m_direct_light->version(program)))
			encoder.dispatch(pass.m_index, m_direct_light->version(program), subdiv / 64, subdiv, subdiv);
	}
	
	void BlockGIBake::bounce(Render& render, GIProbe& gi_probe)
	{
		Pass pass = render.next_pass("gi bounce", PassType::VoxelGI);
		bgfx::Encoder& encoder = *pass.m_encoder;

		encoder.setImage(0,   gi_probe.m_voxels_normals,    0, bgfx::Access::Read,  bgfx::TextureFormat::R32U);
		//encoder.setImage(1, gi_probe.m_voxels_light,      0, bgfx::Access::Read,  bgfx::TextureFormat::R32U);
		encoder.setTexture(1, gi_probe.m_voxels_light_rgba);
		encoder.setImage(2,   gi_probe.m_voxels_light,      0, bgfx::Access::Write, bgfx::TextureFormat::R32U);

		GpuState<GpuVoxelGI>::me.upload(encoder, gi_probe);
		GpuState<GIProbe>::me.upload(encoder, gi_probe, bxidentity());

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_bounce_light->default_version();
		if(bgfx::isValid(program))
			encoder.dispatch(pass.m_index, program, subdiv / 64, subdiv, subdiv);
	}

	void BlockGIBake::output(Render& render, GIProbe& gi_probe)
	{
		Pass pass = render.next_pass("output light", PassType::VoxelGI);
		bgfx::Encoder& encoder = *pass.m_encoder;

		encoder.setImage(0, gi_probe.m_voxels_light,      0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);
		encoder.setImage(1, gi_probe.m_voxels_light_rgba, 0, bgfx::Access::ReadWrite, bgfx::TextureFormat::RGBA16F);

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_output_light->default_version();
		if(bgfx::isValid(program))
			encoder.dispatch(pass.m_index, program, subdiv / 64, subdiv, subdiv);
	}

	void BlockGIBake::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGIBake::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		UNUSED(render); UNUSED(element); UNUSED(program);
	}

	void BlockGIBake::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
	}

	void BlockGIBake::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element);

		bgfx::Encoder& encoder = *pass.m_encoder;

		GIProbe& gi_probe = *m_bake_probe;

		int voxels_albedo_index  = 1;
		int voxels_normals_index = 2;
		int voxels_light_index   = 3;
		encoder.setUniform(u_voxelgi.s_voxels_albedo,  &voxels_albedo_index);
		encoder.setUniform(u_voxelgi.s_voxels_normals, &voxels_normals_index);
		encoder.setUniform(u_voxelgi.s_voxels_light,   &voxels_light_index);

		GpuState<GpuVoxelGI>::me.upload(encoder, gi_probe);

#ifndef VOXELGI_COMPUTE_LIGHTS
		m_block_light.commit_lights(render, pass);
#endif
	}

	BlockGITrace::BlockGITrace(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockGITrace>())
	{
		m_options = { "GI_CONETRACE" };
	}

	void BlockGITrace::init_block()
	{
		u_gi_probe.createUniforms();
	}

	void BlockGITrace::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		UNUSED(element);
		PBRShot& shot = static_cast<PBRShot&>(*render.m_shot);
		for(GIProbe* gi_probe : shot.m_gi_probes)
			if(gi_probe->m_enabled)
			{
				program.set_option(m_index, GI_CONETRACE, true);
			}
	}

	void BlockGITrace::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
		//uint32_t stage = uint32_t(TextureSampler::GIProbe);
		//bgfx::setViewUniform(pass.m_index, u_gi_probe.s_gi_probe, &stage);
	}

	void BlockGITrace::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(pass);

		bgfx::Encoder& encoder = *pass.m_encoder;

		uint8_t index = 0;
		PBRShot& shot = static_cast<PBRShot&>(*render.m_shot);
		for(GIProbe* gi_probe : shot.m_gi_probes)
		{
			if(gi_probe->m_enabled)
			{
				encoder.setTexture(uint8_t(TextureSampler::GIProbe) + index++, gi_probe->m_voxels_light_rgba, TEXTURE_CLAMP3);

				GpuState<GIProbe>::me.upload(encoder, *gi_probe, render.m_camera->m_view);
			}

			return;
		}
	}

	void BlockGITrace::upload_gi_probes(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);

		//bgfx::Encoder& encoder = *pass.m_encoder;
	}
}
