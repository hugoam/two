//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx-pbr/Types.h>
#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <gfx/ManualRender.h>
#include <gfx/GfxSystem.h>
#include <gfx/Assets.h>
#include <gfx/Shot.h>
#include <gfx-pbr/VoxelGI.h>
#include <gfx-pbr/Light.h>
#endif

namespace mud
{
	GIProbe::GIProbe()
	{}

	void GIProbe::resize(uint16_t subdiv, const vec3& extents)
	{
		m_transform = bxidentity();
		m_subdiv = subdiv;
		m_extents = extents;

		m_raster = bgfx::createTexture2D(subdiv, subdiv, false, 0, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT);
		m_voxels_color = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);
		m_voxels_normals = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);

		bgfx::TextureHandle textures[3] = { m_raster, m_voxels_color, m_voxels_normals };
		m_fbo = bgfx::createFrameBuffer(3, textures);
	}

	PassGIBake::PassGIBake(GfxSystem& gfx_system, BlockGIBake& block_gi_bake)
		: DrawPass(gfx_system, "voxelGI", PassType::VoxelGI)
		, m_block_gi_bake(block_gi_bake)
		, m_voxelize(m_gfx_system.programs().fetch("gi/voxelize"))
		, m_voxelize_material(&m_gfx_system.fetch_material("voxelizeGI", "gi/voxelize"))
	{}

	void PassGIBake::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render); UNUSED(render_pass);
	}

	void PassGIBake::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled)
		{
			element.m_material = m_voxelize_material;

			element.m_shader_version = { element.m_material->m_program };

			add_element(element);
		}
	}

	void PassGIBake::submit_draw_element(Pass& render_pass, DrawElement& element) const
	{
		UNUSED(render_pass); UNUSED(element);

		if(true)//render.m_shot->m_gi_probes.size() > 0)
		{
			GIProbe& probe = m_block_gi_bake.m_probe;//*render.m_shot->m_gi_probes[0];

			vec4 voxelgi_extents = { probe.m_extents, 0.f };
			vec4 voxelgi_resolution = { vec3(probe.m_subdiv), 0.f };

			mat4 voxelgi_world = probe.m_transform;
			//mat3 voxelgi_normal = {};

			int voxels_index = 1;
			int voxels_normals_index = 2;
			bgfx::setUniform(m_block_gi_bake.u_voxelgi.s_voxels_albedo, &voxels_index);
			bgfx::setUniform(m_block_gi_bake.u_voxelgi.s_voxels_normals, &voxels_normals_index);

			bgfx::setUniform(m_block_gi_bake.u_voxelgi.u_params_0, &voxelgi_extents);
			bgfx::setUniform(m_block_gi_bake.u_voxelgi.u_params_1, &voxelgi_resolution);

			bgfx::setUniform(m_block_gi_bake.u_voxelgi.u_world, &voxelgi_world);
			//bgfx::setUniform(m_block_gi.u_voxelgi.u_normal, &voxelgi_normal);
		}
	}
	
	PassGIProbes::PassGIProbes(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake)
		: RenderPass(gfx_system, "voxelGI", PassType::VoxelGI)
		, m_block_light(block_light)
		, m_block_gi_bake(block_gi_bake)
	{}

	void PassGIProbes::begin_render_pass(Render& render)
	{
		UNUSED(render);
	}

	void PassGIProbes::submit_render_pass(Render& render)
	{
		GIProbe& gi_probe = m_block_gi_bake.m_probe;

		uvec4 viewport = { uvec2(0), uvec2(gi_probe.m_subdiv) };
		ManualRender voxel_render = { render, gi_probe.m_fbo, viewport,  gi_probe.m_transform, bxidentity() };
		Renderer& renderer = m_gfx_system.renderer(Shading::Voxels);

		voxel_render.cull();
		voxel_render.render(renderer);

		Pass render_pass = render.next_pass("compute light");
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setImage(0, gi_probe.m_voxels_color,   0, bgfx::Access::Read,      bgfx::TextureFormat::RGBA8);
		encoder.setImage(1, gi_probe.m_voxels_normals, 0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(2, gi_probe.m_voxels_light,   0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);

		m_block_light.upload_lights(render, render_pass);
		
		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_block_gi_bake.m_light_program.default_version();
		encoder.dispatch(render_pass.m_index, program, subdiv, subdiv, subdiv, BGFX_VIEW_NONE);
	}

	BlockGIBake::BlockGIBake(GfxSystem& gfx_system)
		: GfxBlock(gfx_system, type<BlockGIBake>())
		, m_light_program(m_gfx_system.programs().fetch("gi/voxel_light"))
	{
		//static cstring options[0] = { };
		//m_shader_block->m_options = { options, 0 };
	}

	void BlockGIBake::init_gfx_block()
	{
		u_voxelgi.createUniforms();

		m_probe.resize(256U, vec3(256.f));
	}

	void BlockGIBake::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockGIBake::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	BlockGITrace::BlockGITrace(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockGITrace>())
	{
		//static cstring options[0] = { };
		//m_shader_block->m_options = { options, 0 };
	}

	void BlockGITrace::init_gfx_block()
	{
		u_gi_probe.createUniforms();
	}

	void BlockGITrace::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::begin_gfx_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::submit_gfx_element(Render& render, const Pass& render_pass, DrawElement& element) const
	{
		this->submit_pass(render, render_pass, element.m_shader_version);
	}

	void BlockGITrace::submit_gfx_cluster(Render& render, const Pass& render_pass, DrawCluster& cluster) const
	{
		this->submit_pass(render, render_pass, cluster.m_shader_version);
	}

	void BlockGITrace::submit_pass(Render& render, const Pass& render_pass, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(render_pass);
		uint8_t index = 0;

		for(GIProbe* gi_probe : render.m_shot->m_gi_probes)
		{
			if(gi_probe->m_enabled)
			{
				float multiplier = gi_probe->m_dynamic_range * gi_probe->m_energy;
				vec4 params = { multiplier, gi_probe->m_bias, gi_probe->m_normal_bias, float(gi_probe->m_interior) };
				mat4 transform = gi_probe->m_transform * inverse(render.m_camera.m_transform);
				vec4 cell_size = { Unit3 / vec3(float(gi_probe->m_subdiv)), 1.f };

				bgfx::setTexture(uint8_t(TextureSampler::GIProbe) + index++, u_gi_probe.s_gi_probe, gi_probe->m_voxels_light);

				bgfx::setUniform(u_gi_probe.u_transform, &transform);
				bgfx::setUniform(u_gi_probe.u_bounds, &gi_probe->m_extents);
				bgfx::setUniform(u_gi_probe.u_params, &params);
				bgfx::setUniform(u_gi_probe.u_cell_size, &cell_size);
			}
		}
	}

	void BlockGITrace::upload_gi_probes(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);

		//bgfx::Encoder& encoder = *render_pass.m_encoder;
	}
}
