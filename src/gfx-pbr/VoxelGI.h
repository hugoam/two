

#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#include <gfx/Light.h>
#include <gfx/RenderTarget.h>
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

		Texture m_raster = {};
		Texture m_voxels_color = {};
		Texture m_voxels_normals = {};
		Texture m_voxels_light = {};
		FrameBuffer m_fbo = {};

		Texture m_voxels_light_rgba = {};

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

	export_ MUD_GFX_PBR_EXPORT void save_gi_probe(GfxSystem& gfx, GIProbe& gi_probe, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path);
	export_ MUD_GFX_PBR_EXPORT void load_gi_probe(GfxSystem& gfx, GIProbe& gi_probe, const string& path);

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGITrace : public DrawBlock
	{
	public:
		BlockGITrace(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, ProgramVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void upload_gi_probes(Render& render, const Pass& pass) const;

		struct GIProbeUniform
		{
			static const int max_gi_probes = 2;

			void createUniforms()
			{
				s_gi_probe = bgfx::createUniform("s_gi_probe", bgfx::UniformType::Sampler, max_gi_probes, bgfx::UniformFreq::View);
			}

			bgfx::UniformHandle s_gi_probe;

		} u_gi_probe;
	};

	struct gpu_ GpuVoxelGI
	{
		attr_ gpu_ vec3 extents;
		attr_ gpu_ vec3 subdiv;
		attr_ gpu_ mat4 world;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGIBake : public DrawBlock
	{
	public:
		BlockGIBake(GfxSystem& gfx, BlockLight& block_light, BlockShadow& block_shadow, BlockGITrace& block_trace);

		BlockLight& m_block_light;
		BlockShadow& m_block_shadow;
		BlockGITrace& m_block_trace;

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, ProgramVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void voxelize(Render& render, GIProbe& gi_probe);
		void compute(Render& render, GIProbe& gi_probe);
		void bounce(Render& render, GIProbe& gi_probe);
		void output(Render& render, GIProbe& gi_probe);

		struct VoxelGIUniform
		{
			void createUniforms()
			{
				s_voxels_albedo    = bgfx::createUniform("s_voxels_albedo",  bgfx::UniformType::Sampler);
				s_voxels_normals   = bgfx::createUniform("s_voxels_normals", bgfx::UniformType::Sampler);
				s_voxels_light     = bgfx::createUniform("s_voxels_light",   bgfx::UniformType::Sampler);

				s_voxels_light_rgba  = bgfx::createUniform("s_voxels_light_rgba",   bgfx::UniformType::Sampler);
			}

			bgfx::UniformHandle s_voxels_albedo;
			bgfx::UniformHandle s_voxels_normals;
			bgfx::UniformHandle s_voxels_light;
			bgfx::UniformHandle s_voxels_light_rgba;

		} u_voxelgi;

		Program* m_direct_light;
		Program* m_bounce_light;
		Program* m_output_light;
		Program* m_voxelize;

		GIProbe* m_bake_probe = nullptr;

		bool m_direct_light_compute = false;
	};
}
