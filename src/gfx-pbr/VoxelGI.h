

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
	export_ MUD_GFX_EXPORT func_ LightmapAtlas& lightmap(Gnode& parent, uint32_t resolution, float density = 8.f, const string& save_path = "");
}

	enum ShaderOptionGI : unsigned int
	{
		GI_CONETRACE
	};

	enum class GIProbeMode
	{
		Voxelize,
		LoadVoxels,
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT GIProbe
	{
	public:
		GIProbe(Node3& node);
		~GIProbe();

		void resize(uint16_t subdiv, const vec3& extents);
		void lightmap(uint32_t size, float density, const string& save_path = "");

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
		GIProbeMode m_mode = GIProbeMode::Voxelize;
		bool m_dirty = false;

		int m_dynamic_range = 4;
		float m_diffuse = 3.0f;
		float m_specular = 1.0f;
		int m_bounces = 0;
		float m_propagation = 1.0f;
		
		float m_bias = 0.0f;
		float m_normal_bias = 0.8f;
	};

	export_ MUD_GFX_PBR_EXPORT void save_gi_probe(GfxSystem& gfx_system, GIProbe& gi_probe, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path);
	export_ MUD_GFX_PBR_EXPORT void load_gi_probe(GfxSystem& gfx_system, GIProbe& gi_probe, const string& path);

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
				u_transform   = bgfx::createUniform("u_gi_probe_transform",    bgfx::UniformType::Mat4, max_gi_probes);
				u_bounds      = bgfx::createUniform("u_gi_probe_bounds4",      bgfx::UniformType::Vec4, max_gi_probes);
				// multiplier, bias, normal_bias, blend_ambient
				u_params      = bgfx::createUniform("u_gi_probe_params",       bgfx::UniformType::Vec4, max_gi_probes);
				u_inv_extents = bgfx::createUniform("u_gi_probe_inv_extents4", bgfx::UniformType::Vec4, max_gi_probes);
				u_cell_size   = bgfx::createUniform("u_gi_probe_cell_size4",   bgfx::UniformType::Vec4, max_gi_probes);

				s_gi_probe = bgfx::createUniform("s_gi_probe", bgfx::UniformType::Int1, max_gi_probes);
			}

			void setUniforms(bgfx::Encoder& encoder, GIProbe& gi_probe, const mat4& view) const
			{
				float diffuse = gi_probe.m_dynamic_range * gi_probe.m_diffuse;
				float specular = gi_probe.m_dynamic_range * gi_probe.m_specular;
				vec4 params = { diffuse, specular, gi_probe.m_bias, gi_probe.m_normal_bias };
				vec4 bounds = { gi_probe.m_extents * 2.f, 0.f };
				mat4 transform = gi_probe.m_transform * inverse(view);
				vec4 inv_extents = { Unit3 / gi_probe.m_extents, 1.f };
				vec4 cell_size = { gi_probe.m_extents * 2.f / float(gi_probe.m_subdiv), 1.f };

				encoder.setUniform(u_transform, &transform);
				encoder.setUniform(u_bounds, &bounds);
				encoder.setUniform(u_params, &params);
				encoder.setUniform(u_inv_extents, &inv_extents);
				encoder.setUniform(u_cell_size, &cell_size);
			}

			bgfx::UniformHandle u_transform;
			bgfx::UniformHandle u_bounds;
			bgfx::UniformHandle u_params;
			bgfx::UniformHandle u_inv_extents;
			bgfx::UniformHandle u_cell_size;

			bgfx::UniformHandle s_gi_probe;

		} u_gi_probe;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGIBake : public DrawBlock
	{
	public:
		BlockGIBake(GfxSystem& gfx_system, BlockLight& block_light, BlockGITrace& block_trace);

		BlockLight& m_block_light;
		BlockGITrace& m_block_trace;

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		void voxelize(Render& render, GIProbe& gi_probe);
		void compute(Render& render, GIProbe& gi_probe);
		void bounce(Render& render, GIProbe& gi_probe);
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
				vec4 voxelgi_subdiv = { vec3(float(gi_probe.m_subdiv)), 0.f };

				mat4 voxelgi_world = gi_probe.m_transform;
				//mat3 voxelgi_normal = {};

				encoder.setUniform(u_params_0, &voxelgi_extents);
				encoder.setUniform(u_params_1, &voxelgi_subdiv);

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

		Program* m_direct_light;
		Program* m_bounce_light;
		Program* m_output_light;
		Program* m_voxelize;

		GIProbe* m_bake_probe = nullptr;

		bool m_direct_light_compute = false;
	};
}
