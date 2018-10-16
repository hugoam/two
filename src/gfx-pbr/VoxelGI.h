

#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#include <gfx/Light.h>
#endif
#include <gfx-pbr/Forward.h>

namespace mud
{
namespace gfx
{
	export_ MUD_GFX_EXPORT func_ GIProbe& gi_probe(Gnode& parent, uint16_t subdiv, const vec3& extents);
}

	enum ShaderOptionGI : unsigned int
	{
		GI_CONETRACE
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT GIProbe
	{
	public:
		GIProbe(Node3& node);

		void resize(uint16_t subdiv, const vec3& extents);

		Node3& m_node;

		bgfx::TextureHandle m_raster = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_voxels_color = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_voxels_normals = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_voxels_light = BGFX_INVALID_HANDLE;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;

		bgfx::TextureHandle m_voxels_light_rgba = BGFX_INVALID_HANDLE;

		bool m_enabled = true;
		mat4 m_transform;
		uint16_t m_subdiv = 0;
		vec3 m_extents = vec3(0.f);
		bool m_dirty = false;

		int m_dynamic_range = 4;
		float m_energy = 1.0f;
		float m_propagation = 1.0f;
		bool m_interior = false;

		float m_bias = 0.0f;
		float m_normal_bias = 0.8f;
	};

	struct VoxelRenderer : public Renderer
	{
		VoxelRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	export_ class MUD_GFX_PBR_EXPORT PassGIBake : public DrawPass
	{
	public:
		PassGIBake(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake);

		BlockLight& m_block_light;
		BlockGIBake& m_block_gi_bake;

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class MUD_GFX_PBR_EXPORT PassGIProbes : public RenderPass
	{
	public:
		PassGIProbes(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake);

		BlockLight& m_block_light;
		BlockGIBake& m_block_gi_bake;

		virtual void submit_render_pass(Render& render) final;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGITrace : public DrawBlock
	{
	public:
		BlockGITrace(GfxSystem& gfx_system);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		void upload_gi_probes(Render& render, const Pass& render_pass) const;

		struct GIProbeUniform
		{
			static const int max_gi_probes = 2;

			void createUniforms()
			{
				u_transform = bgfx::createUniform("u_gi_probe_transform", bgfx::UniformType::Mat4, max_gi_probes);
				u_bounds    = bgfx::createUniform("u_gi_probe_bounds",    bgfx::UniformType::Vec4, max_gi_probes);
				// multiplier, bias, normal_bias, blend_ambient
				u_params    = bgfx::createUniform("u_gi_probe_params",    bgfx::UniformType::Vec4, max_gi_probes);
				u_cell_size = bgfx::createUniform("u_gi_probe_cell_size", bgfx::UniformType::Vec4, max_gi_probes);

				s_gi_probe = bgfx::createUniform("s_gi_probe", bgfx::UniformType::Int1, max_gi_probes);
			}

			bgfx::UniformHandle u_transform;
			bgfx::UniformHandle u_bounds;
			bgfx::UniformHandle u_params;
			bgfx::UniformHandle u_cell_size;

			bgfx::UniformHandle s_gi_probe;

		} u_gi_probe;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGIBake : public DrawBlock
	{
	public:
		BlockGIBake(GfxSystem& gfx_system, BlockLight& block_light);

		BlockLight& m_block_light;

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		void compile();
		void voxelize(Render& render, GIProbe& gi_probe);
		void compute(Render& render, GIProbe& gi_probe);
		void output(Render& render, GIProbe& gi_probe);

		struct VoxelGIUniform
		{
			void createUniforms()
			{
				s_voxels_albedo    = bgfx::createUniform("s_voxels_albedo",  bgfx::UniformType::Int1);
				s_voxels_normals   = bgfx::createUniform("s_voxels_normals", bgfx::UniformType::Int1);
				s_voxels_light     = bgfx::createUniform("s_voxels_light",   bgfx::UniformType::Int1);

				s_voxels_light_rgba  = bgfx::createUniform("s_voxels_light_rgba",   bgfx::UniformType::Int1);

				u_world  = bgfx::createUniform("u_voxelgi_world",  bgfx::UniformType::Mat4);
				u_normal = bgfx::createUniform("u_voxelgi_normal", bgfx::UniformType::Mat3);

				u_params_0 = bgfx::createUniform("u_voxelgi_params_0", bgfx::UniformType::Vec4);
				u_params_1 = bgfx::createUniform("u_voxelgi_params_1", bgfx::UniformType::Vec4);
			}

			void setUniforms(bgfx::Encoder& encoder, GIProbe& gi_probe) const
			{
				vec4 voxelgi_extents = { gi_probe.m_extents, 0.f };
				vec4 voxelgi_resolution = { vec3(gi_probe.m_subdiv), 0.f };

				mat4 voxelgi_world = gi_probe.m_transform;
				//mat3 voxelgi_normal = {};

				encoder.setUniform(u_params_0, &voxelgi_extents);
				encoder.setUniform(u_params_1, &voxelgi_resolution);

				encoder.setUniform(u_world, &voxelgi_world);
				//encoder.setUniform(u_normal, &voxelgi_normal);
			}

			bgfx::UniformHandle s_voxels_albedo;
			bgfx::UniformHandle s_voxels_normals;
			bgfx::UniformHandle s_voxels_light;
			bgfx::UniformHandle s_voxels_light_rgba;

			bgfx::UniformHandle u_world;
			bgfx::UniformHandle u_normal;

			bgfx::UniformHandle u_params_0;
			bgfx::UniformHandle u_params_1;

		} u_voxelgi;

		Program* m_voxel_light;
		Program* m_voxel_output;
		Program* m_voxelize;

		GIProbe* m_bake_probe = nullptr;
	};


}
