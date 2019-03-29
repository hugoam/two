

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

	export_ MUD_GFX_PBR_EXPORT void pass_shadowmaps(GfxSystem& gfx, Render& render);

	export_ MUD_GFX_PBR_EXPORT void pass_shadow(GfxSystem& gfx, Render& render);

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

		FrameBuffer* m_fbo = nullptr;
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

		virtual void options(Render& render, ProgramVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void setup_shadows(Render& render);
		void commit_shadows(Render& render, const mat4& view);
		void upload_shadows(Render& render, const Pass& pass) const;

		void update_csm(Render& render, Light& light, size_t num_direct, CSMShadow& csm, size_t index);

		BlockDepth& m_block_depth;
		BlockLight& m_block_light;

		DepthMethod m_depth_method = DepthMethod::Depth;
		DepthParams m_depth_params = {};
		DistanceParams m_distance_params = {};

		Light* m_direct_light = nullptr;

		struct ShadowUniform
		{
			void createUniforms()
			{
				s_shadow_atlas = bgfx::createUniform("s_shadow_atlas", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View);
				u_shadow_atlas = bgfx::createUniform("u_shadow_atlas", bgfx::UniformType::Vec4,    1U, bgfx::UniformFreq::View);
				u_pcf_p0   = bgfx::createUniform("u_pcf_p0",   bgfx::UniformType::Vec4,    1U, bgfx::UniformFreq::View);
				u_csm_p0 = bgfx::createUniform("u_csm_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			}

			bgfx::UniformHandle s_shadow_atlas;
			bgfx::UniformHandle u_shadow_atlas;
			bgfx::UniformHandle u_pcf_p0;
			bgfx::UniformHandle u_csm_p0;

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

		mat4 m_csm_matrix[4];
		vec4 m_csm_splits;

		vector<mat4> m_shadow_matrices;
	};
}
