//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bx/allocator.h>
#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
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

namespace mud
{
	quat sun_rotation(float azimuth, float altitude, const vec3& up, const vec3& north)
	{
		UNUSED(north);
		return angle_axis(-azimuth, up) * angle_axis(-altitude, X3); // cross(north, up));
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
	{}

	void BlockSky::init_block()
	{
		u_skybox.createUniforms();
	}

	void BlockSky::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockSky::begin_pass(Render& render)
	{
		if(!render.m_env)
			return;

		BackgroundMode mode = render.m_env->m_background.m_mode;
		if(mode == BackgroundMode::Custom)
			return render.m_env->m_background.m_custom_function(render);
		else if(mode == BackgroundMode::Radiance || mode == BackgroundMode::Panorama)
		{
			if(!bgfx::isValid(render.m_env->m_radiance.m_roughness_array))
				return;

			Pass sky_pass = render.next_pass("sky");
			bgfx::Encoder& encoder = *sky_pass.m_encoder;

			encoder.setTexture(uint8_t(TextureSampler::Source0), u_skybox.s_skybox_map, render.m_env->m_radiance.m_roughness_array);

			unsigned int level = mode == BackgroundMode::Radiance ? 3 : 0;
			vec4 skybox_params = { float(level), float(bgfx::getCaps()->originBottomLeft), 0.f, 0.f };
			encoder.setUniform(u_skybox.u_skybox_params, &skybox_params);

			mat4 skybox_matrix = bxinverse(render.m_camera.m_transform);
			encoder.setUniform(u_skybox.u_skybox_matrix, &skybox_matrix);

			m_filter.submit_quad(*render.m_target, sky_pass.m_index, render.m_target_fbo, m_skybox_program.default_version(), render.m_viewport.m_rect, BGFX_STATE_DEPTH_TEST_LEQUAL);
		}
	}
}
