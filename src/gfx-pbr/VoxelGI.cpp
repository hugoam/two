//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx-pbr/Types.h>
#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <pool/ObjectPool.h>
#include <gfx/ManualRender.h>
#include <gfx/Shot.h>
#include <gfx/Graph.h>
#include <gfx/Scene.h>
#include <gfx/Assets.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/VoxelGI.h>
#include <gfx-pbr/Light.h>
#include <gfx-pbr/Shadow.h>
#endif

//#define VOXELGI_COMPUTE_LIGHTS
//#define VOXELGI_BOUNCE

namespace mud
{
namespace gfx
{
	template <class T_Element, class... T_Args>
	inline T_Element& create(Scene& scene, T_Args&&... args)
	{
		return scene.m_pool->pool<T_Element>().construct(std::forward<T_Args>(args)...);
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
}

	GIProbe::GIProbe(Node3& node)
		: m_node(node)
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

		m_raster = bgfx::createTexture2D(subdiv, subdiv, false, 0, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT);
		m_voxels_color   = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);
		m_voxels_normals = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);
		m_voxels_light   = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);

		bgfx::TextureHandle textures[4] = { m_raster, m_voxels_color, m_voxels_normals, m_voxels_light };
		m_fbo = bgfx::createFrameBuffer(4, textures, true);

		m_voxels_light_rgba = bgfx::createTexture3D(subdiv, subdiv, subdiv, true, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT | BGFX_TEXTURE_COMPUTE_WRITE);

		m_dirty = true;
	}

	PassGIBake::PassGIBake(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake)
		: DrawPass(gfx_system, "voxelGI", PassType::VoxelGI)
		, m_block_light(block_light)
		, m_block_gi_bake(block_gi_bake)
	{}

	void PassGIBake::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render); UNUSED(render_pass);
		render_pass.m_bgfx_state = BGFX_STATE_CONSERVATIVE_RASTER | BGFX_STATE_MSAA;
		//render_pass.m_bgfx_state = BGFX_STATE_CONSERVATIVE_RASTER | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA;

#ifndef VOXELGI_COMPUTE_LIGHTS
		m_block_light.update_lights(render, bxidentity(), to_array(render.m_shot->m_lights), to_array(m_block_light.m_block_shadow.m_shadows));
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

		m_block_gi_bake.compile();

		for(size_t i = 0; i < render.m_shot->m_gi_probes.size(); ++i)
		{
			GIProbe& gi_probe = *render.m_shot->m_gi_probes[i];

			if(gi_probe.m_enabled && gi_probe.m_dirty)
			{
				m_block_gi_bake.voxelize(render, gi_probe);
#ifdef VOXELGI_COMPUTE_LIGHTS
				m_block_gi_bake.compute(render, gi_probe);
#endif
				m_block_gi_bake.output(render, gi_probe);

				gi_probe.m_dirty = false;
			}
		}
	}

	BlockGIBake::BlockGIBake(GfxSystem& gfx_system, BlockLight& block_light)
		: DrawBlock(gfx_system, type<BlockGIBake>())
		, m_block_light(block_light)
	{}

	void BlockGIBake::init_block()
	{
		u_voxelgi.createUniforms();

		m_voxelize = &m_gfx_system.programs().fetch("gi/voxelize");
		m_voxel_light = &m_gfx_system.programs().fetch("gi/voxel_light");
		m_voxel_output = &m_gfx_system.programs().fetch("gi/voxel_light_out");
	}
	
	void BlockGIBake::compile()
	{
		m_voxelize->update(m_gfx_system);
		m_voxel_light->update(m_gfx_system);
		m_voxel_output->update(m_gfx_system);
	}

	void BlockGIBake::voxelize(Render& render, GIProbe& gi_probe)
	{
		m_bake_probe = &gi_probe;

		uvec4 viewport = { uvec2(0), uvec2(gi_probe.m_subdiv) };
		vec3 extents = gi_probe.m_extents;
		mat4 projection = bxortho(-extents.x, extents.x, -extents.y, extents.y, -extents.z, extents.z, 0.0f, bgfx::getCaps()->homogeneousDepth);

		ManualRender voxel_render = { render, gi_probe.m_fbo, viewport,  gi_probe.m_transform, projection };
		Renderer& renderer = m_gfx_system.renderer(Shading::Voxels);

		Plane6 planes = frustum_planes(voxel_render.m_camera.m_projection, voxel_render.m_camera.m_transform);
		render.m_scene.cull_items(planes, voxel_render.m_sub_render.m_shot->m_items);
		voxel_render.render(renderer);
	}

	void BlockGIBake::compute(Render& render, GIProbe& gi_probe)
	{
		Pass render_pass = render.next_pass("compute light");
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setImage(0, gi_probe.m_voxels_color,   0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(1, gi_probe.m_voxels_normals, 0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(2, gi_probe.m_voxels_light,   0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);

		int voxels_albedo_index  = 0;
		int voxels_normals_index = 1;
		int voxels_light_index   = 2;
		encoder.setUniform(u_voxelgi.s_voxels_albedo,  &voxels_albedo_index);
		encoder.setUniform(u_voxelgi.s_voxels_normals, &voxels_normals_index);
		encoder.setUniform(u_voxelgi.s_voxels_light,   &voxels_light_index);

		u_voxelgi.setUniforms(encoder, gi_probe);

		m_block_light.update_lights(render, bxidentity(), to_array(render.m_shot->m_lights), to_array(m_block_light.m_block_shadow.m_shadows));
		m_block_light.upload_lights(render_pass);

		ShaderVersion shader_version = { m_voxel_light };
		if(m_block_light.m_directional_light)
			shader_version.set_option(m_block_light.m_index, DIRECTIONAL_LIGHT, true);

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_voxel_light->version(shader_version);
		if(bgfx::isValid(program))
			encoder.dispatch(render_pass.m_index, program, subdiv / 64, subdiv, subdiv, BGFX_VIEW_NONE);
	}

	void BlockGIBake::output(Render& render, GIProbe& gi_probe)
	{
		Pass render_pass = render.next_pass("output light");
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setImage(0, gi_probe.m_voxels_light,      0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);
		encoder.setImage(1, gi_probe.m_voxels_light_rgba, 0, bgfx::Access::ReadWrite, bgfx::TextureFormat::RGBA8);

		int voxels_light      = 0;
		int voxels_light_rgba = 1;
		encoder.setUniform(u_voxelgi.s_voxels_light,      &voxels_light);
		encoder.setUniform(u_voxelgi.s_voxels_light_rgba, &voxels_light_rgba);

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_voxel_output->default_version();
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
				float multiplier = gi_probe->m_dynamic_range * gi_probe->m_energy;
				vec4 params = { multiplier, gi_probe->m_bias, gi_probe->m_normal_bias, float(gi_probe->m_interior) };
				vec4 bounds = { gi_probe->m_extents * 2.f, 0.f };
				mat4 transform = gi_probe->m_transform * inverse(render.m_camera.m_transform);
				vec4 cell_size = { Unit3 / gi_probe->m_extents, 1.f };

				encoder.setTexture(uint8_t(TextureSampler::GIProbe) + index++, u_gi_probe.s_gi_probe, gi_probe->m_voxels_light_rgba);

				encoder.setUniform(u_gi_probe.u_transform, &transform);
				encoder.setUniform(u_gi_probe.u_bounds, &bounds);
				encoder.setUniform(u_gi_probe.u_params, &params);
				encoder.setUniform(u_gi_probe.u_cell_size, &cell_size);
			}
		}
	}

	void BlockGITrace::upload_gi_probes(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);

		//bgfx::Encoder& encoder = *render_pass.m_encoder;
	}
}
