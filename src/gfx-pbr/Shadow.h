

#pragma once

#ifndef MUD_MODULES
#include <stl/map.h>
#include <math/Vec.hpp>
#include <gfx/Renderer.h>
#include <gfx/Frustum.h>
#include <gfx/Depth.h>
#endif
#include <gfx-pbr/Forward.h>
#include <gfx-pbr/ShadowAtlas.h>

namespace mud
{
	enum ShaderOptionShadow : unsigned int
	{
		CSM_SHADOW,
		CSM_BLEND,
	};

	enum ShaderModeShadow : unsigned int
	{
		PCF_LEVEL,
		CSM_NUM_CASCADES,
	};

	enum ShadowFilterMode : unsigned int
	{
		PCF_NONE = 0,
		PCF_HARD = 1,
		PCF_5 = 2,
		PCF_13 = 3
	};

	struct Shadowmap
	{
		Shadowmap() {}
		~Shadowmap() { if(bgfx::isValid(m_fbo)) bgfx::destroy(m_fbo); }

		void create(const uvec2& size, DepthMethod method = DepthMethod::Depth);

		uvec2 m_size = uvec2(0U);
		DepthMethod m_depth_method = DepthMethod::Depth;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_depth = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_color = BGFX_INVALID_HANDLE;

		bgfx::TextureHandle texture() const { return m_depth_method == DepthMethod::Depth ? m_depth : m_color; }
	};

	struct ShadowmapCube
	{
		ShadowmapCube() {}
		~ShadowmapCube() { if(bgfx::isValid(m_depth)) bgfx::destroy(m_depth); }

		void create(uint16_t size);

		uint16_t m_size = 0U;
		bgfx::FrameBufferHandle m_fbos[6];
		bgfx::TextureHandle m_depth = BGFX_INVALID_HANDLE;
	};

	export_ class MUD_GFX_PBR_EXPORT PassShadow : public PassDepth
	{
	public:
		PassShadow(GfxSystem& gfx, BlockDepth& block_depth, BlockShadow& block_shadow);

		BlockDepth& m_block_depth;
		BlockShadow& m_block_shadow;

		virtual void submit_render_pass(Render& render) final;

		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class MUD_GFX_PBR_EXPORT PassShadowmap : public RenderPass
	{
	public:
		PassShadowmap(GfxSystem& gfx, BlockShadow& block_shadow);

		BlockShadow& m_block_shadow;

		virtual void submit_render_pass(Render& render) override;
	};

	struct ShadowRenderer : public Renderer
	{
		ShadowRenderer(GfxSystem& gfx, Pipeline& pipeline);
	};

	export_ struct LightBounds
	{
		vec3 min = { 9000.0f,  9000.0f,  9000.0f };
		vec3 max = { -9000.0f, -9000.0f, -9000.0f };
	};

	struct gpu_ GpuCSM
	{
		mat4 matrix[4];
		vec4 splits;
	};

	struct gpu_ GpuShadow
	{
		mat4 matrix;
	};

	export_ struct refl_ MUD_GFX_PBR_EXPORT LightShadow
	{
		Light* m_light = nullptr;

		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		uvec4 m_rect = {};
		vec4 m_uv_rect = {};
		
		mat4 m_projection = {};
		mat4 m_transform = {};

		mat4 m_shadow_matrix = {};
		DepthMethod m_depth_method = DepthMethod::Depth;
		float m_bias_scale = 1.f;

		FrustumSlice m_frustum_slice;
		LightBounds m_light_bounds;

		vector<Item*> m_items;
	};

	export_ struct refl_ MUD_GFX_PBR_EXPORT CSMShadow
	{
		Light* m_light;

		vector<FrustumSlice> m_frustum_slices;
		vector<LightShadow> m_slices;
	};

#ifdef MUD_PLATFORM_EMSCRIPTEN
	constexpr size_t c_max_shadows = 4;
	constexpr size_t c_max_csm = 1;
#else
	constexpr size_t c_max_shadows = 32;
	constexpr size_t c_max_csm = 4;
#endif

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockShadow : public DrawBlock
	{
	public:
		BlockShadow(GfxSystem& gfx, BlockDepth& block_depth, BlockLight& block_light);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& render_pass) const override;

		void setup_shadows(Render& render);
		void render_shadows(Render& render);
		void commit_shadows(Render& render, const mat4& view);
		void upload_shadows(Render& render, const Pass& render_pass) const;

		void update_csm(Render& render, Light& light, size_t num_direct, CSMShadow& csm, size_t index);
		void render_csm(Render& render, Light& light, CSMShadow& csm);
		void render(ManualRender& render, Light& light, DepthMethod method, float bias_scale = 1.f);

		BlockDepth& m_block_depth;
		BlockLight& m_block_light;

		DepthMethod m_depth_method = DepthMethod::Depth;
		DepthParams m_depth_params = {};
		DistanceParams m_distance_params = {};

		Light* m_direct_light = nullptr;

		struct DirectionalShadowUniform
		{
			void createUniforms()
			{
				s_csm_atlas	 = bgfx::createUniform("s_csm_atlas",  bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View);
				u_csm_params = bgfx::createUniform("u_csm_params", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			}

			bgfx::UniformHandle s_csm_atlas;
			bgfx::UniformHandle u_csm_params;

		} u_direct_shadow;

		struct ShadowUniform
		{
			void createUniforms()
			{
				s_shadow_atlas = bgfx::createUniform("s_shadow_atlas", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View);
				u_shadow_atlas = bgfx::createUniform("u_shadow_atlas", bgfx::UniformType::Vec4,    1U, bgfx::UniformFreq::View);
				u_pcf_params   = bgfx::createUniform("u_pcf_params",   bgfx::UniformType::Vec4,    1U, bgfx::UniformFreq::View);
			}

			bgfx::UniformHandle s_shadow_atlas;
			bgfx::UniformHandle u_shadow_atlas;
			bgfx::UniformHandle u_pcf_params;

		} u_shadow;

#ifdef MUD_PLATFORM_EMSCRIPTEN
		ShadowFilterMode m_pcf_level = PCF_HARD; // @todo can't get true pcf working on WebGL so far
#else
		ShadowFilterMode m_pcf_level = PCF_5;
#endif

		ShadowAtlas m_atlas;

		vector<CSMShadow> m_csm_shadows;
		vector<LightShadow> m_shadows;

		Shadowmap m_csm;
		vector<Shadowmap> m_shadowmaps;
		vector<ShadowmapCube> m_shadowmaps_cubes;

		mat4 m_csm_matrix[4];
		vec4 m_csm_splits;

		vector<mat4> m_shadow_matrices;
	};
}
