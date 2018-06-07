

#pragma once

#ifndef MUD_MODULES
#include <obj/Unique.h>
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Generated/Forward.h>

namespace mud
{
	export_ struct refl_ DepthParams
	{
		float m_depth_bias = 0.f;
		float m_depth_normal_bias = 0.f;
		float m_depth_z_far = 0.f;
		float _padding;
	};

	export_ class MUD_GFX_PBR_EXPORT PassDepth : public DrawPass
	{
	public:
		PassDepth(GfxSystem& gfx_system, BlockDepth& block_depth);

		virtual void next_draw_pass(Render& render, Pass& render_pass) override;
		virtual void queue_draw_element(Render& render, DrawElement& element) override;
		virtual void submit_draw_element(Pass& render_pass, DrawElement& element) override;

		BlockDepth& m_block_depth;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockDepth : public DrawBlock
	{
	public:
		BlockDepth(GfxSystem& gfx_system);
		~BlockDepth();

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		virtual void begin_gfx_pass(Render& render) final;
		virtual void submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element) final;

		struct DepthUniform
		{
			void createUniforms()
			{
				u_depth_params = bgfx::createUniform("u_depth_params", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle u_depth_params;

		} u_depth;

		DepthParams m_depth_params;

		Material* m_depth_material = nullptr;
		Material* m_depth_material_twosided = nullptr;
	};
}
