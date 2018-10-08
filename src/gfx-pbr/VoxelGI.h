

#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#include <gfx/Light.h>
#endif
#include <gfx-pbr/Forward.h>

namespace mud
{
	enum ShaderOptionGI : unsigned int
	{
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT GIProbe
	{
	public:
		GIProbe();

		void resize(uvec3 subdiv);

		bgfx::TextureHandle m_voxels = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_voxels_normals = BGFX_INVALID_HANDLE;

		uvec3 m_subdiv = uvec3(256);
		mat4 m_to_cell_space;
	};

	struct VoxelRenderer : public Renderer
	{
		VoxelRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	export_ class MUD_GFX_PBR_EXPORT PassGI : public DrawPass
	{
	public:
		PassGI(GfxSystem& gfx_system, BlockGI& block_gi);

		BlockGI& m_block_gi;

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
		virtual void submit_draw_element(Pass& render_pass, DrawElement& element) const final;

		Material* m_voxelize_material = nullptr;
		Program& m_voxelize;
	};

	export_ class MUD_GFX_PBR_EXPORT PassVoxelGI : public RenderPass
	{
	public:
		PassVoxelGI(GfxSystem& gfx_system, BlockGI& block_gi);

		BlockGI& m_block_gi;

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGI : public DrawBlock
	{
	public:
		BlockGI(GfxSystem& gfx_system);

		void init_gfx_block() final;

		void begin_gfx_block(Render& render) final;
		void submit_gfx_block(Render& render) final;

		void begin_gfx_pass(Render& render) final;
		void submit_gfx_element(Render& render, const Pass& render_pass, DrawElement& element) const final;
		void submit_gfx_cluster(Render& render, const Pass& render_pass, DrawCluster& cluster) const final;

		void submit_pass(Render& render, const Pass& render_pass, ShaderVersion& shader_version) const;

		void upload_gi_probes(Render& render, const Pass& render_pass) const;

		struct VoxelGIUniform
		{
			void createUniforms()
			{
				s_voxels		   = bgfx::createUniform("s_voxels", bgfx::UniformType::Int1);
				s_voxels_normals   = bgfx::createUniform("s_voxels_normals", bgfx::UniformType::Int1);

				u_params_0 = bgfx::createUniform("u_voxelgi_params_0", bgfx::UniformType::Vec4);
				u_params_1 = bgfx::createUniform("u_voxelgi_params_1", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle s_voxels;
			bgfx::UniformHandle s_voxels_normals;

			bgfx::UniformHandle u_params_0;
			bgfx::UniformHandle u_params_1;

		} u_voxelgi;


		GIProbe m_probe;
	};
}
