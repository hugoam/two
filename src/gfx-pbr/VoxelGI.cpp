//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx-pbr/Types.h>
#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>
#include <xatlas.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <stl/algorithm.h>
#include <math/Vec.hpp>
#include <geom/Intersect.h>
#include <tree/Graph.hpp>
#include <pool/ObjectPool.hpp>
#include <gfx/Item.h>
#include <gfx/ManualRender.h>
#include <gfx/Shot.h>
#include <gfx/Graph.h>
#include <gfx/Scene.h>
#include <gfx/Assets.h>
#include <gfx/GfxSystem.h>
#include <gfx/Pipeline.h>
#include <gfx-pbr/VoxelGI.h>
#include <gfx-pbr/Lighting.h>
#include <gfx-pbr/Shadow.h>
#include <gfx-pbr/Lightmap.h>
#endif

#include <cstdio>

#define LIGHTMAP_XATLAS

namespace mud
{
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
		if(!self.m_gi_probe)
			self.m_gi_probe = &create<GIProbe>(*self.m_scene, *self.m_attach);
		if(subdiv != self.m_gi_probe->m_subdiv || extents != self.m_gi_probe->m_extents)
			self.m_gi_probe->resize(subdiv, extents);
		return *self.m_gi_probe;
	}

	LightmapAtlas& lightmap(Gnode& parent, uint32_t resolution, float density, const string& save_path)
	{
		Gnode& self = parent.suba();
		if(!self.m_lightmap_atlas)
		{
			self.m_lightmap_atlas = &create<LightmapAtlas>(*self.m_scene, resolution, density);
			self.m_lightmap_atlas->m_dirty = true;
		}
		self.m_lightmap_atlas->m_save_path = save_path;
		return *self.m_lightmap_atlas;
	}
}

	void BlockGITrace::GIProbeUniform::createUniforms()
	{
		u_transform   = bgfx::createUniform("u_gi_probe_transform",    bgfx::UniformType::Mat4, max_gi_probes);
		u_bounds      = bgfx::createUniform("u_gi_probe_bounds4",      bgfx::UniformType::Vec4, max_gi_probes);
		// multiplier, bias, normal_bias, blend_ambient
		u_params      = bgfx::createUniform("u_gi_probe_params",       bgfx::UniformType::Vec4, max_gi_probes);
		u_inv_extents = bgfx::createUniform("u_gi_probe_inv_extents4", bgfx::UniformType::Vec4, max_gi_probes);
		u_cell_size   = bgfx::createUniform("u_gi_probe_cell_size4",   bgfx::UniformType::Vec4, max_gi_probes);

		s_gi_probe = bgfx::createUniform("s_gi_probe", bgfx::UniformType::Int1, max_gi_probes);
	}

	void BlockGITrace::GIProbeUniform::setUniforms(bgfx::Encoder& encoder, GIProbe& gi_probe, const mat4& view) const
	{
		float diffuse = gi_probe.m_dynamic_range * gi_probe.m_diffuse;
		float specular = gi_probe.m_dynamic_range * gi_probe.m_specular;
		vec4 params = { diffuse, specular, gi_probe.m_bias, gi_probe.m_normal_bias };
		vec4 bounds = { gi_probe.m_extents * 2.f, 0.f };
		mat4 transform = gi_probe.m_transform * inverse(view);
		vec4 inv_extents = { vec3(1.f) / gi_probe.m_extents, 1.f };
		vec4 cell_size = { gi_probe.m_extents * 2.f / float(gi_probe.m_subdiv), 1.f };

		encoder.setUniform(u_transform, &transform);
		encoder.setUniform(u_bounds, &bounds);
		encoder.setUniform(u_params, &params);
		encoder.setUniform(u_inv_extents, &inv_extents);
		encoder.setUniform(u_cell_size, &cell_size);
	}

	GIProbe::GIProbe(Node3& node)
		: m_node(node)
	{}

	GIProbe::~GIProbe()
	{}

	void GIProbe::resize(uint16_t subdiv, const vec3& extents)
	{
		if(bgfx::isValid(m_raster))
		{
			bgfx::destroy(m_fbo);
			bgfx::destroy(m_voxels_light_rgba);
		}

		m_transform = bxidentity();
		m_subdiv = subdiv;
		m_extents = extents;

		m_normal_bias = length(extents * 2.f / float(subdiv)) * sqrt(2.f) * 2.f;

		m_raster = bgfx::createTexture2D(subdiv, subdiv, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT);
		m_voxels_color   = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);
		m_voxels_normals = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);
		m_voxels_light   = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);

		bgfx::TextureHandle textures[4] = { m_raster, m_voxels_color, m_voxels_normals, m_voxels_light };
		m_fbo = bgfx::createFrameBuffer(4, textures, true);
		
		m_voxels_light_rgba = bgfx::createTexture3D(subdiv, subdiv, subdiv, true, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_RT | BGFX_TEXTURE_COMPUTE_WRITE);

		m_dirty = true;
	}

	void save_gi_probe(GfxSystem& gfx_system, GIProbe& gi_probe, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path)
	{
		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::TextureHandle texture = bgfx::createTexture3D(subdiv, subdiv, subdiv, true, source_format, BGFX_TEXTURE_BLIT_DST | BGFX_TEXTURE_READ_BACK);
		bgfx::blit(0, texture, 0, 0, 0, 0, gi_probe.m_voxels_light_rgba, 0, 0, 0, 0, subdiv, subdiv, subdiv);
		bgfx::frame();
		bgfx::frame();

		save_bgfx_texture(gfx_system.allocator(), gfx_system.file_writer(), path.c_str(), target_format, texture, source_format, uint16_t(gi_probe.m_subdiv), uint16_t(gi_probe.m_subdiv), uint16_t(gi_probe.m_subdiv));
	}

	void load_gi_probe(GfxSystem& gfx_system, GIProbe& gi_probe, const string& path)
	{
		gi_probe.m_voxels_light_rgba = load_bgfx_texture(gfx_system.allocator(), gfx_system.file_reader(), path.c_str());
	}

	PassGIBake::PassGIBake(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake)
		: DrawPass(gfx_system, "voxelGI", PassType::VoxelGI)
		, m_block_light(block_light)
		, m_block_gi_bake(block_gi_bake)
	{}

	void PassGIBake::next_draw_pass(Render& render, Pass& render_pass)
	{
		bool conservative = (bgfx::getCaps()->supported & BGFX_CAPS_CONSERVATIVE_RASTER) != 0;
		if(!conservative)
			printf("WARNING: rendering GI probe without conservative raster support will produce wrong output\n");

		UNUSED(render); UNUSED(render_pass);
		render_pass.m_bgfx_state = BGFX_STATE_CONSERVATIVE_RASTER | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA;

#ifndef VOXELGI_COMPUTE_LIGHTS
		GIProbe& gi_probe = *m_block_gi_bake.m_bake_probe; UNUSED(gi_probe);
		mat4 view = bxidentity();//gi_probe.m_transform * bxscale(1.f / gi_probe.m_extents);
		m_block_light.update_lights(render, view, render.m_shot->m_lights, m_block_light.m_block_shadow.m_shadows);
#endif
	}

	void PassGIBake::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled)
		{
			element.m_program = m_block_gi_bake.m_voxelize;
			element.m_shader_version = element.m_material->shader_version(*element.m_program);

			this->add_element(render, element);
		}
	}

	PassGIProbes::PassGIProbes(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake)
		: RenderPass(gfx_system, "voxelGI", PassType::VoxelGI)
		, m_block_light(block_light)
		, m_block_gi_bake(block_gi_bake)
	{}

	void PassGIProbes::submit_render_pass(Render& render)
	{
		if(!check_lighting(render.m_lighting, Lighting::VoxelGI))
			return;

		for(GIProbe* gi_probe : render.m_shot->m_gi_probes)
		{
			if(gi_probe->m_enabled && gi_probe->m_dirty)
			{
				if(gi_probe->m_mode == GIProbeMode::Voxelize)
				{
					printf("INFO: bake GIProbe\n");

					m_block_gi_bake.voxelize(render, *gi_probe);
					m_block_gi_bake.output(render, *gi_probe);

					for(int i = 0; i < gi_probe->m_bounces; ++i)
					{
						// @todo fix D3D bounce bug
						m_block_gi_bake.bounce(render, *gi_probe);
						m_block_gi_bake.output(render, *gi_probe);
					}

					gi_probe->m_dirty = false;

					printf("INFO: bake GIProbe done\n");

					//string path = m_gfx_system.m_resource_path + "/" + "gi_probe.dds";
					//save_gi_probe(m_gfx_system, *gi_probe, bgfx::TextureFormat::RGBA16F, bgfx::TextureFormat::BC6H, path);
				}

				if(gi_probe->m_mode == GIProbeMode::LoadVoxels)
				{
					string path = m_gfx_system.m_resource_path + "/" + "gi_probe.dds";
					load_gi_probe(m_gfx_system, *gi_probe, path);
				}
			}
		}
	}

	BlockGIBake::BlockGIBake(GfxSystem& gfx_system, BlockLight& block_light, BlockGITrace& block_trace)
		: DrawBlock(gfx_system, type<BlockGIBake>())
		, m_block_light(block_light)
		, m_block_trace(block_trace)
	{}

	void BlockGIBake::init_block()
	{
		u_voxelgi.createUniforms();

		m_voxelize = &m_gfx_system.programs().fetch("gi/voxelize");
		m_direct_light = &m_gfx_system.programs().fetch("gi/direct_light");
		m_bounce_light = &m_gfx_system.programs().fetch("gi/bounce_light");
		m_output_light = &m_gfx_system.programs().fetch("gi/output_light");
	}

	void BlockGIBake::voxelize(Render& render, GIProbe& gi_probe)
	{
		m_bake_probe = &gi_probe;

		vec3 extents = gi_probe.m_extents;
		
		Camera camera = { gi_probe.m_transform, vec2(extents.x * 2.f, extents.y * 2.f), -extents.z, extents.z };
		Viewport viewport = { camera, render.m_scene, { uvec2(0U), uvec2(uint(gi_probe.m_subdiv)) } };
		Render voxel_render = { Shading::Voxels, viewport, gi_probe.m_fbo, render.m_frame };

		BlockShadow& block_shadow = *m_gfx_system.m_pipeline->block<BlockShadow>();
		CSMFilterMode pcf_level = block_shadow.m_pcf_level;
		uint8_t splits = 0;
		block_shadow.m_pcf_level = CSM_NO_PCF;
		if(m_block_light.m_direct_light)
		{
			splits = m_block_light.m_direct_light->m_shadow_num_splits;
			m_block_light.m_direct_light->m_shadow_num_splits = 1;
		}

		Plane6 planes = frustum_planes(camera.m_projection, camera.m_transform);
		voxel_render.m_shot->m_lights = render.m_shot->m_lights;
		cull_items(render.m_scene, planes, voxel_render.m_shot->m_items);
		m_gfx_system.renderer(Shading::Voxels).subrender(render, voxel_render);

		if(m_block_light.m_direct_light)
		{
			m_block_light.m_direct_light->m_shadow_num_splits = splits;
		}
		block_shadow.m_pcf_level = pcf_level;

		if(m_direct_light_compute)
			this->compute(render, gi_probe);
	}

	void BlockGIBake::compute(Render& render, GIProbe& gi_probe)
	{
		Pass render_pass = render.next_pass("gi direct");
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setImage(0, u_voxelgi.s_voxels_albedo,  gi_probe.m_voxels_color,   0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(1, u_voxelgi.s_voxels_normals, gi_probe.m_voxels_normals, 0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(2, u_voxelgi.s_voxels_light,   gi_probe.m_voxels_light,   0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);

		u_voxelgi.setUniforms(encoder, gi_probe);

		m_block_light.update_lights(render, bxidentity(), render.m_shot->m_lights, m_block_light.m_block_shadow.m_shadows);
		m_block_light.upload_lights(render_pass);

		ShaderVersion shader_version = { m_direct_light };
		if(m_block_light.m_direct_light)
			shader_version.set_option(m_block_light.m_index, DIRECT_LIGHT, true);

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_direct_light->version(shader_version);
		if(bgfx::isValid(program))
			encoder.dispatch(render_pass.m_index, program, subdiv / 64, subdiv, subdiv, BGFX_VIEW_NONE);
	}
	
	void BlockGIBake::bounce(Render& render, GIProbe& gi_probe)
	{
		Pass render_pass = render.next_pass("gi bounce");
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setImage(0,   u_voxelgi.s_voxels_normals,    gi_probe.m_voxels_normals,    0, bgfx::Access::Read,  bgfx::TextureFormat::R32U);
		//encoder.setImage(1,   u_voxelgi.s_voxels_light,      gi_probe.m_voxels_light,      0, bgfx::Access::Read,  bgfx::TextureFormat::R32U);
		encoder.setTexture(1, u_voxelgi.s_voxels_light_rgba, gi_probe.m_voxels_light_rgba);
		encoder.setImage(2,   u_voxelgi.s_voxels_light,      gi_probe.m_voxels_light,      0, bgfx::Access::Write, bgfx::TextureFormat::R32U);

		u_voxelgi.setUniforms(encoder, gi_probe);
		m_block_trace.u_gi_probe.setUniforms(encoder, gi_probe, bxidentity());

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_bounce_light->default_version();
		if(bgfx::isValid(program))
			encoder.dispatch(render_pass.m_index, program, subdiv / 64, subdiv, subdiv, BGFX_VIEW_NONE);
	}

	void BlockGIBake::output(Render& render, GIProbe& gi_probe)
	{
		Pass render_pass = render.next_pass("output light");
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setImage(0, u_voxelgi.s_voxels_light,      gi_probe.m_voxels_light,      0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);
		encoder.setImage(1, u_voxelgi.s_voxels_light_rgba, gi_probe.m_voxels_light_rgba, 0, bgfx::Access::ReadWrite, bgfx::TextureFormat::RGBA16F);

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_output_light->default_version();
		if(bgfx::isValid(program))
			encoder.dispatch(render_pass.m_index, program, subdiv / 64, subdiv, subdiv, BGFX_VIEW_NONE);
	}

	void BlockGIBake::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGIBake::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGIBake::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGIBake::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockGIBake::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);

		bgfx::Encoder& encoder = *render_pass.m_encoder;

		GIProbe& gi_probe = *m_bake_probe;

		int voxels_albedo_index  = 1;
		int voxels_normals_index = 2;
		int voxels_light_index   = 3;
		encoder.setUniform(u_voxelgi.s_voxels_albedo,  &voxels_albedo_index);
		encoder.setUniform(u_voxelgi.s_voxels_normals, &voxels_normals_index);
		encoder.setUniform(u_voxelgi.s_voxels_light,   &voxels_light_index);

		u_voxelgi.setUniforms(encoder, gi_probe);

#ifndef VOXELGI_COMPUTE_LIGHTS
		m_block_light.upload_lights(render_pass);
#endif
	}

	BlockGITrace::BlockGITrace(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockGITrace>())
	{
		static cstring options[1] = { "GI_CONETRACE" };
		m_shader_block->m_options = { options, 1 };
	}

	void BlockGITrace::init_block()
	{
		u_gi_probe.createUniforms();
	}

	void BlockGITrace::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::options(Render& render, ShaderVersion& shader_version) const
	{
		for(GIProbe* gi_probe : render.m_shot->m_gi_probes)
			if(gi_probe->m_enabled)
			{
				shader_version.set_option(m_index, GI_CONETRACE, true);
			}
	}

	void BlockGITrace::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);

		bgfx::Encoder& encoder = *render_pass.m_encoder;

		uint8_t index = 0;
		for(GIProbe* gi_probe : render.m_shot->m_gi_probes)
		{
			if(gi_probe->m_enabled)
			{
				encoder.setTexture(uint8_t(TextureSampler::GIProbe) + index++, u_gi_probe.s_gi_probe, gi_probe->m_voxels_light_rgba, GFX_TEXTURE_CLAMP_UVW);

				u_gi_probe.setUniforms(encoder, *gi_probe, render.m_camera.m_transform);
			}
		}
	}

	void BlockGITrace::upload_gi_probes(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);

		//bgfx::Encoder& encoder = *render_pass.m_encoder;
	}
}
