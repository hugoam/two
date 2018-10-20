

#pragma once

#ifndef MUD_MODULES
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
		CSM_NUM_CASCADES,
		CSM_PCF_LEVEL,
	};

	enum CSMFilterMode : unsigned int
	{
		CSM_NO_PCF = 0,
		CSM_HARD_PCF = 1,
		CSM_PCF5 = 2,
		CSM_PCF13 = 3
	};

	struct CSMShadow
	{
		CSMShadow() {}
		CSMShadow(uint16_t size);

		uint16_t m_size = 0;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_depth = BGFX_INVALID_HANDLE;
		CSMFilterMode m_filter_mode = CSM_PCF5;
	};

	export_ class MUD_GFX_PBR_EXPORT PassShadow : public PassDepth
	{
	public:
		PassShadow(GfxSystem& gfx_system, BlockDepth& block_depth, BlockShadow& block_shadow);

		BlockDepth& m_block_depth;
		BlockShadow& m_block_shadow;

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class MUD_GFX_PBR_EXPORT PassShadowmap : public RenderPass
	{
	public:
		PassShadowmap(GfxSystem& gfx_system, BlockShadow& block_shadow);

		BlockShadow& m_block_shadow;

		virtual void submit_render_pass(Render& render) final;
	};

	struct ShadowRenderer : public Renderer
	{
		ShadowRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	export_ struct LightBounds
	{
		vec3 min = { 9000.0f,  9000.0f,  9000.0f };
		vec3 max = { -9000.0f, -9000.0f, -9000.0f };
	};

	export_ struct refl_ MUD_GFX_PBR_EXPORT LightShadow
	{
		struct Slice
		{
			vec4 m_viewport_rect;
			vec4 m_texture_rect;
			mat4 m_projection;
			mat4 m_transform;
			mat4 m_shadow_matrix;
			float m_bias_scale;

			FrustumSlice m_frustum_slice;
			LightBounds m_light_bounds;

			std::vector<Item*> m_items;
		};

		std::vector<FrustumSlice> m_frustum_slices;
		std::vector<Slice> m_slices;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockShadow : public DrawBlock
	{
	public:
		BlockShadow(GfxSystem& gfx_system, BlockDepth& block_depth);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		void update_shadows(Render& render);
		void render_shadows(Render& render);

		void update_direct(Render& render, Light& light, size_t num_direct, size_t index);
		void render_direct(Render& render, Light& light, size_t index);

		BlockDepth& m_block_depth;

		DepthParams m_depth_params;

		Light* m_direct_light = nullptr;

		struct DirectionalShadowUniform
		{
			void createUniforms()
			{
				s_csm_atlas	 = bgfx::createUniform("s_csm_atlas",  bgfx::UniformType::Int1);
				u_csm_params = bgfx::createUniform("u_csm_params", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle s_csm_atlas;
			bgfx::UniformHandle u_csm_params;

		} u_direct_shadow;

		struct ShadowUniform
		{
			void createUniforms()
			{
				s_shadow_atlas = bgfx::createUniform("s_shadow_atlas", bgfx::UniformType::Int1);
				u_shadow_pixel_size = bgfx::createUniform("u_shadow_pixel_size", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle s_shadow_atlas;
			bgfx::UniformHandle u_shadow_pixel_size;

		} u_shadow;

		ShadowAtlas m_atlas;

		std::vector<LightShadow> m_shadows;

		CSMShadow m_csm;

#ifdef MUD_PLATFORM_EMSCRIPTEN
		CSMFilterMode m_pcf_level = CSM_HARD_PCF; // @todo can't get true pcf working on WebGL so far
#else
		CSMFilterMode m_pcf_level = CSM_PCF5;
#endif
	};
}
