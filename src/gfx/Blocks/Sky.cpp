//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bx/allocator.h>
#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
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

	// HDTV rec. 709 matrix.
	static float M_XYZ2RGB[] =
	{
		3.240479f, -0.969256f, 0.055648f,
		-1.53715f, 1.875991f, -0.204043f,
		-0.49853f, 0.041556f, 1.057311f
	};


	// Converts color repesentation from CIE XYZ to RGB color-space.
	Color XYZToRGB(const Color& xyz)
	{
		Color rgb;
		rgb.r = M_XYZ2RGB[0] * xyz.X + M_XYZ2RGB[3] * xyz.Y + M_XYZ2RGB[6] * xyz.Z;
		rgb.g = M_XYZ2RGB[1] * xyz.X + M_XYZ2RGB[4] * xyz.Y + M_XYZ2RGB[7] * xyz.Z;
		rgb.b = M_XYZ2RGB[2] * xyz.X + M_XYZ2RGB[5] * xyz.Y + M_XYZ2RGB[8] * xyz.Z;
		return rgb;
	};


	// Precomputed luminance of sunlight in XYZ colorspace.
	// Computed using code from Game Engine Gems, Volume One, chapter 15. Implementation based on Dr. Richard Bird model.
	// This table is used for piecewise linear interpolation. Transitions from and to 0.0 at sunset and sunrise are highly inaccurate
	static std::map<float, Color> sunLuminanceXYZTable = {
		{ 5.0f, { { 0.000000f, 0.000000f, 0.000000f } } },
		{ 7.0f, { { 12.703322f, 12.989393f, 9.100411f } } },
		{ 8.0f, { { 13.202644f, 13.597814f, 11.524929f } } },
		{ 9.0f, { { 13.192974f, 13.597458f, 12.264488f } } },
		{ 10.0f, { { 13.132943f, 13.535914f, 12.560032f } } },
		{ 11.0f, { { 13.088722f, 13.489535f, 12.692996f } } },
		{ 12.0f, { { 13.067827f, 13.467483f, 12.745179f } } },
		{ 13.0f, { { 13.069653f, 13.469413f, 12.740822f } } },
		{ 14.0f, { { 13.094319f, 13.495428f, 12.678066f } } },
		{ 15.0f, { { 13.142133f, 13.545483f, 12.526785f } } },
		{ 16.0f, { { 13.201734f, 13.606017f, 12.188001f } } },
		{ 17.0f, { { 13.182774f, 13.572725f, 11.311157f } } },
		{ 18.0f, { { 12.448635f, 12.672520f, 8.267771f } } },
		{ 20.0f, { { 0.000000f, 0.000000f, 0.000000f } } }
	};


	// Precomputed luminance of sky in the zenith point in XYZ colorspace.
	// Computed using code from Game Engine Gems, Volume One, chapter 15. Implementation based on Dr. Richard Bird model.
	// This table is used for piecewise linear interpolation. Day/night transitions are highly inaccurate.
	// The scale of luminance change in Day/night transitions is not preserved.
	// Luminance at night was increased to eliminate need the of HDR render.
	static std::map<float, Color> skyLuminanceXYZTable = {
		{ 0.0f, { { 0.308f, 0.308f, 0.411f } } },
		{ 1.0f, { { 0.308f, 0.308f, 0.410f } } },
		{ 2.0f, { { 0.301f, 0.301f, 0.402f } } },
		{ 3.0f, { { 0.287f, 0.287f, 0.382f } } },
		{ 4.0f, { { 0.258f, 0.258f, 0.344f } } },
		{ 5.0f, { { 0.258f, 0.258f, 0.344f } } },
		{ 7.0f, { { 0.962851f, 1.000000f, 1.747835f } } },
		{ 8.0f, { { 0.967787f, 1.000000f, 1.776762f } } },
		{ 9.0f, { { 0.970173f, 1.000000f, 1.788413f } } },
		{ 10.0f, { { 0.971431f, 1.000000f, 1.794102f } } },
		{ 11.0f, { { 0.972099f, 1.000000f, 1.797096f } } },
		{ 12.0f, { { 0.972385f, 1.000000f, 1.798389f } } },
		{ 13.0f, { { 0.972361f, 1.000000f, 1.798278f } } },
		{ 14.0f, { { 0.972020f, 1.000000f, 1.796740f } } },
		{ 15.0f, { { 0.971275f, 1.000000f, 1.793407f } } },
		{ 16.0f, { { 0.969885f, 1.000000f, 1.787078f } } },
		{ 17.0f, { { 0.967216f, 1.000000f, 1.773758f } } },
		{ 18.0f, { { 0.961668f, 1.000000f, 1.739891f } } },
		{ 20.0f, { { 0.264f, 0.264f, 0.352f } } },
		{ 21.0f, { { 0.264f, 0.264f, 0.352f } } },
		{ 22.0f, { { 0.290f, 0.290f, 0.386f } } },
		{ 23.0f, { { 0.303f, 0.303f, 0.404f } } }
	};


	// Turbidity tables. Taken from:
	// A. J. Preetham, P. Shirley, and B. Smits. A Practical Analytic Model for Daylight. SIGGRAPH ’99
	// Coefficients correspond to xyY colorspace.
	static Color ABCDE[] =
	{
		{ { -0.2592f, -0.2608f, -1.4630f } },
		{ { 0.0008f,  0.0092f,  0.4275f } },
		{ { 0.2125f,  0.2102f,  5.3251f } },
		{ { -0.8989f, -1.6537f, -2.5771f } },
		{ { 0.0452f,  0.0529f,  0.3703f } }
	};
	static Color ABCDE_t[] =
	{
		{ { -0.0193f, -0.0167f,  0.1787f } },
		{ { -0.0665f, -0.0950f, -0.3554f } },
		{ { -0.0004f, -0.0079f, -0.0227f } },
		{ { -0.0641f, -0.0441f,  0.1206f } },
		{ { -0.0033f, -0.0109f, -0.0670f } }
	};

	void DynamicValueController::SetMap(const KeyMap& keymap)
	{
		m_keyMap = keymap;
	}

	DynamicValueController::ValueType DynamicValueController::GetValue(float time) const
	{
		typename KeyMap::const_iterator itUpper = m_keyMap.upper_bound(time + 1e-6f);
		typename KeyMap::const_iterator itLower = itUpper;
		--itLower;
		if(itLower == m_keyMap.end())
		{
			return itUpper->second;
		}
		if(itUpper == m_keyMap.end())
		{
			return itLower->second;
		}
		float lowerTime = itLower->first;
		const ValueType& lowerVal = itLower->second;
		float upperTime = itUpper->first;
		const ValueType& upperVal = itUpper->second;
		if(lowerTime == upperTime)
		{
			return lowerVal;
		}
		return interpolate(lowerTime, lowerVal, upperTime, upperVal, time);
	}

	void DynamicValueController::Clear()
	{
		m_keyMap.clear();
	}

	const DynamicValueController::ValueType DynamicValueController::interpolate(float lowerTime, const ValueType& lowerVal, float upperTime, const ValueType& upperVal, float time) const
	{
		float x = (time - lowerTime) / (upperTime - lowerTime);
		ValueType result;
		bx::vec3Lerp(result.data, lowerVal.data, upperVal.data, x);
		return result;
	}

	void SunController::Update(float time)
	{
		m_sun_rotation = sun_rotation(m_month, m_latitude, time - 12.0f, m_ecliptic_obliquity);
		m_sun_direction = m_sun_rotation * -m_north_direction;
	}

	struct ScreenPosVertex
	{
		float m_x;
		float m_y;

		static void init()
		{
			ms_decl
				.begin()
				.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
				.end();
		}

		static bgfx::VertexDecl ms_decl;
	};

	bgfx::VertexDecl ScreenPosVertex::ms_decl;

	void ProceduralSky::init(GfxSystem& gfx_system, ivec2 vertex_count)
	{
		// Create vertex stream declaration.
		ScreenPosVertex::init();

		m_program = gfx_system.programs().create("sky").default_version();
		//m_program_colorBandingFix = gfx_system.get_program("sky_color_banding_fix").default_version();

		m_preventBanding = false;

		ScreenPosVertex* vertices = (ScreenPosVertex*)BX_ALLOC(&gfx_system.m_allocator, vertex_count.y * vertex_count.x * sizeof(ScreenPosVertex));

		for(int i = 0; i < vertex_count.y; i++)
		{
			for(int j = 0; j < vertex_count.x; j++)
			{
				ScreenPosVertex& v = vertices[i * vertex_count.y + j];
				v.m_x = float(j) / (vertex_count.x - 1) * 2.0f - 1.0f;
				v.m_y = float(i) / (vertex_count.y - 1) * 2.0f - 1.0f;
			}
		}

		uint16_t* indices = (uint16_t*)BX_ALLOC(&gfx_system.m_allocator, (vertex_count.y - 1) * (vertex_count.x - 1) * 6 * sizeof(uint16_t));

		int k = 0;
		for(int i = 0; i < vertex_count.y - 1; i++)
		{
			for(int j = 0; j < vertex_count.x - 1; j++)
			{
				indices[k++] = (uint16_t)(j + 0 + vertex_count.x * (i + 0));
				indices[k++] = (uint16_t)(j + 1 + vertex_count.x * (i + 0));
				indices[k++] = (uint16_t)(j + 0 + vertex_count.x * (i + 1));

				indices[k++] = (uint16_t)(j + 1 + vertex_count.x * (i + 0));
				indices[k++] = (uint16_t)(j + 1 + vertex_count.x * (i + 1));
				indices[k++] = (uint16_t)(j + 0 + vertex_count.x * (i + 1));
			}
		}

		m_vbh = bgfx::createVertexBuffer(bgfx::copy(vertices, sizeof(ScreenPosVertex) * vertex_count.y * vertex_count.x), ScreenPosVertex::ms_decl);
		m_ibh = bgfx::createIndexBuffer(bgfx::copy(indices, sizeof(uint16_t) * k));

		BX_FREE(&gfx_system.m_allocator, indices);
		BX_FREE(&gfx_system.m_allocator, vertices);
	}

	void ProceduralSky::shutdown()
	{
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);
		bgfx::destroy(m_program_colorBandingFix);
	}

	void ProceduralSky::submit(Render& render, Pass& render_pass)
	{
		UNUSED(render);
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LEQUAL);
		encoder.setIndexBuffer(m_ibh);
		encoder.setVertexBuffer(0, m_vbh);

		encoder.submit(render_pass.m_index, m_preventBanding ? m_program_colorBandingFix : m_program);
	}

	void PerezSky::init(GfxSystem& gfx_system)
	{
		m_sun_luminance_xyz.SetMap(sunLuminanceXYZTable);
		m_sky_luminance_xyz.SetMap(skyLuminanceXYZTable);

		m_sky.init(gfx_system, { 32, 32 });
		
		u_uniform.createUniforms();

		m_sun.Update(0);

		m_initialized = true;
	}

	void compute_perez_coeff(float turbidity, float* perezCoeff)
	{
		for(int i = 0; i < 5; ++i)
		{
			Color tmp;
			bx::vec3Mul(tmp.data, ABCDE_t[i].data, turbidity);
			bx::vec3Add(perezCoeff + 4 * i, tmp.data, ABCDE[i].data);
			perezCoeff[4 * i + 3] = 0.0f;
		}
	}

	void PerezSky::render(Render& render)
	{
		Pass sky_pass = render.next_pass("sky");
		bgfx::Encoder& encoder = *sky_pass.m_encoder;

		m_time += m_time_scale * render.m_frame.m_delta_time;
		m_time = bx::mod(m_time, 24.0f);
		m_sun.Update(m_time);

		Color sun_luminance_xyz = m_sun_luminance_xyz.GetValue(m_time);
		Color sun_luminance_rgb = XYZToRGB(sun_luminance_xyz);

		Color sky_luminance_xyz = m_sky_luminance_xyz.GetValue(m_time);
		Color sky_luminance_rgb = XYZToRGB(sky_luminance_xyz);

		encoder.setUniform(u_uniform.u_sun_luminance, sun_luminance_rgb.data);
		encoder.setUniform(u_uniform.u_sky_luminance_xyz, sky_luminance_xyz.data);
		encoder.setUniform(u_uniform.u_sky_luminance, sky_luminance_rgb.data);

		encoder.setUniform(u_uniform.u_sun_direction, &m_sun.m_sun_direction);

		float exposition[4] = { 0.02f, 3.0f, 0.1f, m_time };
		encoder.setUniform(u_uniform.u_sky_params, exposition);

		float perez_coeff[4 * 5];
		compute_perez_coeff(m_turbidity, perez_coeff);
		encoder.setUniform(u_uniform.u_perez_coeff, perez_coeff, 5);

		m_sky.submit(render, sky_pass);
	}

	BlockSky::BlockSky(GfxSystem& gfx_system, BlockFilter& filter)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_skybox_program(gfx_system.programs().create("skybox"))
	{}

	void BlockSky::init_gfx_block()
	{
		u_skybox.createUniforms();
	}

	void BlockSky::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockSky::submit_gfx_block(Render& render)
	{
		if(!render.m_environment)
			return;
		
		BackgroundMode mode = render.m_environment->m_background.m_mode;
		if(mode == BackgroundMode::Custom)
			return render.m_environment->m_background.m_custom_function(render);
		else if(mode == BackgroundMode::Radiance || mode == BackgroundMode::Panorama)
		{
			Pass sky_pass = render.next_pass("sky");
			bgfx::Encoder& encoder = *sky_pass.m_encoder;

			encoder.setTexture(uint8_t(TextureSampler::Source0), u_skybox.s_skybox_map, render.m_environment->m_radiance.m_roughness_array);

			unsigned int level = mode == BackgroundMode::Radiance ? 3 : 0;
			vec4 skybox_params = { float(level), float(bgfx::getCaps()->originBottomLeft), 0.f, 0.f };
			encoder.setUniform(u_skybox.u_skybox_params, &skybox_params);

			mat4 skybox_matrix = bxinverse(render.m_camera.m_transform);
			encoder.setUniform(u_skybox.u_skybox_matrix, &skybox_matrix);

			m_filter.set_uniforms(render, encoder);

			m_filter.submit_quad(*render.m_target, sky_pass.m_index, render.m_target_fbo, m_skybox_program.default_version(), render.m_viewport.m_rect, BGFX_STATE_DEPTH_TEST_LEQUAL);
		}
	}
}
