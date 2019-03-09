

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
	export_ enum class refl_ DepthMethod : unsigned int
	{
		Depth,
		DepthPacked,
		Distance,
		Count
	};

	export_ struct refl_ DepthParams
	{
		attr_ gpu_ float m_depth_bias = 0.f;
		attr_ gpu_ float m_depth_normal_bias = 0.f;
		attr_ gpu_ float m_depth_z_far = 0.f;
	};

	export_ struct refl_ DistanceParams
	{
		attr_ gpu_ vec3 m_eye = vec3(0.f);
		attr_ gpu_ float m_near = 0.f;
		attr_ gpu_ float m_far = 1.f;
	};

	export_ MUD_GFX_EXPORT void pass_depth(GfxSystem& gfx, Render& render, Pass& render_pass, bool submit = true);
	export_ MUD_GFX_EXPORT void pass_depth(GfxSystem& gfx, Render& render);

	export_ class refl_ MUD_GFX_EXPORT BlockDepth : public DrawBlock
	{
	public:
		BlockDepth(GfxSystem& gfx);
		~BlockDepth();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& render_pass) const override;

		struct DepthUniform
		{
			void createUniforms()
			{
				u_depth_params = bgfx::createUniform("u_depth_params", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
				u_distance_params_0 = bgfx::createUniform("u_distance_params_0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
				u_distance_params_1 = bgfx::createUniform("u_distance_params_1", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			}

			bgfx::UniformHandle u_depth_params;
			bgfx::UniformHandle u_distance_params_0;
			bgfx::UniformHandle u_distance_params_1;

		} u_depth;

		DepthMethod m_depth_method = DepthMethod::Depth;
		DepthParams m_depth_params = {};
		DistanceParams m_distance_params = {};

		Program* m_depth_program = nullptr;
		Program* m_distance_program = nullptr;
	};
}
