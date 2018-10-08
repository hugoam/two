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
#endif

namespace mud
{
	GIProbe::GIProbe()
	{}

	void GIProbe::resize(uvec3 subdiv)
	{
		m_subdiv = subdiv;

		m_voxels = bgfx::createTexture3D(subdiv.x, subdiv.y, subdiv.z, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);
		m_voxels_normals = bgfx::createTexture3D(subdiv.x, subdiv.y, subdiv.z, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);
	}

	struct VoxelGIRender : public ManualRender
	{
		VoxelGIRender(Render& render, bgfx::FrameBufferHandle fbo, GIProbe& gi_probe)
			: ManualRender(render, fbo, uvec4(uvec2(0), gi_probe.m_subdiv.x, gi_probe.m_subdiv.y))
			, m_camera(render.m_camera)
			, m_gi_probe(gi_probe)
		{}

		void render(BlockGI& block_gi)
		{
			Renderer& renderer = block_gi.m_gfx_system.renderer(Shading::Voxels);
			ManualRender::render(renderer);
		}

		Camera& m_camera;
		GIProbe& m_gi_probe;
	};

	PassGI::PassGI(GfxSystem& gfx_system, BlockGI& block_gi)
		: DrawPass(gfx_system, "voxelGI", PassType::VoxelGI)
		, m_block_gi(block_gi)
		, m_voxelize(m_gfx_system.programs().fetch("gi/voxelize"))
		, m_voxelize_material(&m_gfx_system.fetch_material("voxelizeGI", "gi/voxelize"))
	{}

	void PassGI::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render); UNUSED(render_pass);

		if(true)//render.m_shot->m_gi_probes.size() > 0)
		{
			GIProbe& probe = m_block_gi.m_probe;//*render.m_shot->m_gi_probes[0];

			bgfx::setViewImage(render_pass.m_index, 0, probe.m_voxels, 0, bgfx::Access::ReadWrite);
			bgfx::setViewImage(render_pass.m_index, 1, probe.m_voxels_normals, 0, bgfx::Access::ReadWrite);

			vec4 voxelgi_extents = { vec3(probe.m_subdiv), 0.f };
			vec4 voxelgi_resolution = { 1.f / vec3(probe.m_subdiv), 0.f };

			bgfx::setUniform(m_block_gi.u_voxelgi.u_params_0, &voxelgi_extents);
			bgfx::setUniform(m_block_gi.u_voxelgi.u_params_0, &voxelgi_resolution);
		}
	}

	void PassGI::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled)
		{
			element.m_material = m_voxelize_material;

			element.m_shader_version = { element.m_material->m_program };

			add_element(element);
		}
	}

	void PassGI::submit_draw_element(Pass& render_pass, DrawElement& element) const
	{
		UNUSED(render_pass); UNUSED(element);
	}
	
	PassVoxelGI::PassVoxelGI(GfxSystem& gfx_system, BlockGI& block_gi)
		: RenderPass(gfx_system, "voxelGI", PassType::VoxelGI)
		, m_block_gi(block_gi)
	{}

	void PassVoxelGI::begin_render_pass(Render& render)
	{
		UNUSED(render);
	}

	void PassVoxelGI::submit_render_pass(Render& render)
	{
		VoxelGIRender voxel_render = { render, render.m_target_fbo, m_block_gi.m_probe };
		voxel_render.cull();
		voxel_render.render(m_block_gi);
	}

	BlockGI::BlockGI(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockGI>())
	{
		//static cstring options[0] = { };
		//m_shader_block->m_options = { options, 0 };
	}

	void BlockGI::init_gfx_block()
	{
		u_voxelgi.createUniforms();

		m_probe.resize(uvec3(256));
	}

	void BlockGI::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockGI::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockGI::begin_gfx_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGI::submit_gfx_element(Render& render, const Pass& render_pass, DrawElement& element) const
	{
		this->submit_pass(render, render_pass, element.m_shader_version);
	}

	void BlockGI::submit_gfx_cluster(Render& render, const Pass& render_pass, DrawCluster& cluster) const
	{
		this->submit_pass(render, render_pass, cluster.m_shader_version);
	}

	void BlockGI::submit_pass(Render& render, const Pass& render_pass, ShaderVersion& shader_version) const
	{
		UNUSED(render);
	}

	void BlockGI::upload_gi_probes(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);

		//bgfx::Encoder& encoder = *render_pass.m_encoder;
	}
}
