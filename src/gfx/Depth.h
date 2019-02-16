

#pragma once

#ifndef MUD_MODULES
#include <type/Unique.h>
#include <stl/table.h>
#endif
#include <gfx/Renderer.h>
#include <gfx/Material.h>
#include <gfx/Forward.h>

namespace mud
{
	export_ struct refl_ DepthParams
	{
		attr_ gpu_ float m_depth_bias = 0.f;
		attr_ gpu_ float m_depth_normal_bias = 0.f;
		attr_ gpu_ float m_depth_z_far = 0.f;
	};

	export_ class MUD_GFX_EXPORT PassDepth : public DrawPass
	{
	public:
		PassDepth(GfxSystem& gfx_system, cstring name, BlockDepth& block_depth);
		PassDepth(GfxSystem& gfx_system, BlockDepth& block_depth);

		virtual void next_draw_pass(Render& render, Pass& render_pass) override;
		virtual void queue_draw_element(Render& render, DrawElement& element) override;

		BlockDepth& m_block_depth;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockDepth : public DrawBlock
	{
	public:
		BlockDepth(GfxSystem& gfx_system);
		~BlockDepth();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& render_pass) const override;

		struct DepthUniform
		{
			void createUniforms()
			{
				u_depth_params = bgfx::createUniform("u_depth_params", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			}

			bgfx::UniformHandle u_depth_params;

		} u_depth;

		DepthParams* m_current_params = nullptr;

		DepthParams m_depth_params;

		table<CullMode, Material*> m_depth_material = {};
	};
}
