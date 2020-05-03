

#pragma once

#ifndef TWO_MODULES
#include <stl/map.h>
#include <math/Vec.hpp>
#include <gfx/Renderer.h>
#include <gfx/Frustum.h>
#include <gfx/Depth.h>
#endif
#include <gfx-pbr/Forward.h>
#include <gfx-pbr/ShadowAtlas.h>

#define SHADOW_DEPTH 0
#define SHADOW_SAMPLER 0

namespace two
{
	enum ShaderOptionShadow : unsigned int
	{
		SHADOWS,
		SHADOWS_PACKED,
		SHADOWS_COMPARE, // TODO adapt to const branches
		//CSM_BLEND, // TODO
	};

	enum ShaderModeShadow : unsigned int
	{
		PCF_LEVEL,
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
		~Shadowmap() {}

		Shadowmap(const Shadowmap& other) = delete;
		Shadowmap& operator=(const Shadowmap& other) = delete;

		void create(const uvec2& size, DepthMethod method = DepthMethod::Depth);

		uvec2 m_size = uvec2(0U);
		DepthMethod m_depth_method = DepthMethod::Depth;
		FrameBuffer m_fbo;
		Texture m_depth;
		Texture m_color;

		const Texture& texture() const { return m_depth_method == DepthMethod::Depth ? m_depth : m_color; }
	};

	struct ShadowmapCube
	{
		ShadowmapCube() {}
		~ShadowmapCube() { if(bgfx::isValid(m_depth)) bgfx::destroy(m_depth); }

		void create(uint32_t size);

		uint32_t m_size = 0U;
		FrameBuffer m_fbos[6];
		Texture m_depth;
	};

	export_ TWO_GFX_PBR_EXPORT void pass_shadowmaps(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT void pass_shadow(GfxSystem& gfx, Render& render);

	export_ struct LightBounds
	{
		vec3 min = { 9000.0f,  9000.0f,  9000.0f };
		vec3 max = { -9000.0f, -9000.0f, -9000.0f };
	};

	export_ struct refl_ TWO_GFX_PBR_EXPORT LightShadow
	{
		Light* m_light = nullptr;

		FrameBuffer* m_fbo = nullptr;
		vec4 m_rect = {};
		
		float m_near = 0.f;
		float m_far = 100.f;
		mat4 m_proj = {};
		mat4 m_transform = {};

		mat4 m_shadow_matrix = {};
		DepthMethod m_depth_method = DepthMethod::Depth;
		float m_bias_scale = 1.f;

		FrustumSlice m_frustum_slice;
		LightBounds m_light_bounds;

		vector<Item*> m_items;
	};

	export_ struct refl_ TWO_GFX_PBR_EXPORT CSMSlice : public LightShadow, public FrustumSlice
	{};

	export_ struct refl_ TWO_GFX_PBR_EXPORT CSMShadow
	{
		Light* m_light;

		vector<CSMSlice> m_slices;
	};

#ifdef TWO_PLATFORM_EMSCRIPTEN
	constexpr size_t c_max_shadows = 8;
#else
	constexpr size_t c_max_shadows = 32;
#endif

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockShadow : public DrawBlock
	{
	public:
		BlockShadow(GfxSystem& gfx, BlockDepth& block_depth, BlockLight& block_light);

		virtual void init_block() override;
		virtual void begin_frame(const RenderFrame& frame) override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void setup_shadows(Render& render);
		void commit_shadows(Render& render, const mat4& view);
		void upload_shadows(Render& render, const Pass& pass) const;

		void update_csm(Render& render, Light& light, CSMShadow& csm);

		DepthMethod depth_method()
		{
#if SHADOW_SAMPLER || SHADOW_DEPTH
			return DepthMethod::Depth;
#else
			return bgfx::getRendererType() == bgfx::RendererType::WebGPU
				? DepthMethod::DepthPacked
				: DepthMethod::Depth;
#endif
		}

		BlockDepth& m_block_depth;
		BlockLight& m_block_light;

		DepthMethod m_depth_method = DepthMethod::Depth;
		DepthParams m_depth_params = {};
		DistanceParams m_distance_params = {};

		struct ShadowUniform
		{
			void createUniforms()
			{
				s_shadow_atlas = bgfx::createUniform("s_shadow_atlas", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
				u_shadow_atlas = bgfx::createUniform("u_shadow_atlas", bgfx::UniformType::Vec4,    1U, bgfx::UniformSet::View);
				u_pcf_p0   = bgfx::createUniform("u_pcf_p0",   bgfx::UniformType::Vec4,    1U, bgfx::UniformSet::View);
				u_csm_p0   = bgfx::createUniform("u_csm_p0",   bgfx::UniformType::Vec4,    1U, bgfx::UniformSet::View);
			}

			bgfx::UniformHandle s_shadow_atlas;
			bgfx::UniformHandle u_shadow_atlas;
			bgfx::UniformHandle u_pcf_p0;
			bgfx::UniformHandle u_csm_p0;

		} u_shadow;

#ifdef TWO_PLATFORM_EMSCRIPTEN
		ShadowFilterMode m_pcf_level = PCF_HARD; // @todo can't get true pcf working on WebGL so far
#else
		ShadowFilterMode m_pcf_level = PCF_5;
#endif

		ShadowAtlas m_atlas;

		vector<CSMShadow> m_csm_shadows;
		vector<LightShadow> m_shadows;

		vector<mat4> m_shadow_matrices;
	};
}
