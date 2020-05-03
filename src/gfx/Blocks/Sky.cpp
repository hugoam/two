//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <bx/allocator.h>
#include <bx/math.h>
#include <bgfx/bgfx.h>
#include <infra/Cpp20.h>
module two.gfx;
#else
#include <bx/allocator.h>
#include <bx/math.h>
#include <math/Vec.hpp>
#include <gfx/Types.h>
#include <gfx/Blocks/Sky.h>
#include <gfx/GfxSystem.h>
#include <gfx/Scene.h>
#include <gfx/Camera.h>
#include <gfx/Texture.h>
#include <gfx/Asset.h>
#include <gfx/RenderTarget.h>
#endif

namespace two
{
	quat sun_rotation(float azimuth, float altitude, const vec3& up, const vec3& north)
	{
		UNUSED(north);
		return angle_axis(-azimuth, up) * angle_axis(-altitude, x3); // cross(north, up));
	}

	quat sun_rotation(Month month, float latitude_degrees, float hour, float ecliptic_obliquity, const vec3& up, const vec3& north)
	{
		float day = 30.0f * float(month) + 15.0f;
		float lambda = 280.46f + 0.9856474f * day;
		lambda = bx::toRad(lambda);
		float delta = bx::asin(bx::sin(ecliptic_obliquity) * bx::sin(lambda));

		float latitude = bx::toRad(latitude_degrees);
		float h = hour * bx::kPi / 12.0f;
		float azimuth = bx::atan2(bx::sin(h), bx::cos(h) * bx::sin(latitude) - bx::tan(delta) * bx::cos(latitude));
		float altitude = bx::asin(bx::sin(latitude) * bx::sin(delta) + bx::cos(latitude) * bx::cos(delta) * bx::cos(h));

		return sun_rotation(azimuth, altitude, up, north);
	}

	BlockSky::BlockSky(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_skybox_program(gfx.programs().create("skybox"))
	{
		m_skybox_program.register_block(m_filter);
	}

	void BlockSky::init_block()
	{
		u_skybox.createUniforms();
	}

	void BlockSky::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockSky::submit_pass(Render& render)
	{
		if(!render.m_env)
			return;

		BackgroundMode mode = render.m_env->m_background.m_mode;
		if(mode == BackgroundMode::Custom)
			return render.m_env->m_background.m_custom_function(m_gfx, render);
		else if(mode == BackgroundMode::Radiance || mode == BackgroundMode::Panorama)
		{
			if(mode == BackgroundMode::Radiance && render.m_env->m_radiance.m_filtered == nullptr)
				return;

			Pass pass = render.next_pass("sky", PassType::Background);
			bgfx::Encoder& encoder = *pass.m_encoder;

			Texture& texture = mode == BackgroundMode::Radiance
				? *render.m_env->m_radiance.m_filtered
				: *render.m_env->m_background.m_texture;

			unsigned int level = mode == BackgroundMode::Radiance ? 3 : 0;

			ProgramVersion program = { m_skybox_program };
			m_filter.source0p(texture, program, level);

			mat4 skybox_matrix = bxinverse(render.m_camera->m_view);
			encoder.setUniform(u_skybox.u_skybox_matrix, &skybox_matrix);

			const RenderQuad quad = RenderQuad(pass.m_rect, false);
			m_filter.submit(pass, *render.m_fbo, program, quad, BGFX_STATE_DEPTH_TEST_LEQUAL);
		}
	}
}
