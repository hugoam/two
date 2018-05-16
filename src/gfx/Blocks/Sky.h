//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Generated/Forward.h>
#include <gfx/Renderer.h>

#include <gfx/Filter.h>
#include <gfx/Filter.h>

#include <map>

namespace mud
{
	enum class _refl_ Month : unsigned int
	{
		January = 0,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};

	MUD_GFX_EXPORT quat sun_rotation(float azimuth, float altitude, const vec3& up = Y3, const vec3& north = X3);
	MUD_GFX_EXPORT quat sun_rotation(Month month, float latitude, float hour, float ecliptic_obliquity = 0.408407f, const vec3& up = Y3, const vec3& north = X3);

	// Represents color. Color-space depends on context.
	// In the code below, used to represent color in XYZ, and RGB color-space
	union Color
	{
		struct {
			float X;
			float Y;
			float Z;
		};
		struct {
			float r;
			float g;
			float b;
		};

		float data[3];
	};


	// Performs piecewise linear interpolation of a Color parameter.
	class DynamicValueController
	{
		typedef Color ValueType;
		typedef std::map<float, ValueType> KeyMap;
	public:
		DynamicValueController() {}
		~DynamicValueController() {}

		void SetMap(const KeyMap& keymap);
		ValueType GetValue(float time) const;
		void Clear();

	private:
		const ValueType interpolate(float lowerTime, const ValueType& lowerVal, float upperTime, const ValueType& upperVal, float time) const;

		KeyMap	m_keyMap;
	};

	// Controls sun position according to time, month, and observer's latitude.
	// Sun position computation based on Earth's orbital elements: https://nssdc.gsfc.nasa.gov/planetary/factsheet/earthfact.html
	class MUD_GFX_EXPORT SunController
	{
	public:
		SunController() {}

		void Update(float time);

		vec3 m_north_direction = { 0.f, 0.f, -1.f }; //-Z3; // @kludge somehow meta generator doesn't like this ?
		quat m_sun_rotation = ZeroQuat;
		vec3 m_sun_direction = Zero3;
		vec3 m_up = Y3;
		float m_latitude = 50.f;
		Month m_month = Month::June;

		float m_ecliptic_obliquity = 0.408407f; //bx::toRad(23.4f);
		float m_delta = 0.0f;
	};
	// Renders a screen-space grid of triangles.
	// Because of performance reasons, and because sky color is smooth, sky color is computed in vertex shader.
	// 32x32 is a reasonable size for the grid to have smooth enough colors.
	struct MUD_GFX_EXPORT ProceduralSky
	{
		void init(GfxSystem& gfx_system, ivec2 vertex_count);
		void shutdown();
		void render(Render& render);

		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle m_ibh;

		bgfx::ProgramHandle m_program;
		bgfx::ProgramHandle m_program_colorBandingFix;

		bool m_preventBanding;
	};

	struct MUD_GFX_EXPORT PerezSky
	{
		struct SkyUniform
		{
			void createUniforms()
			{
				u_sun_luminance		= bgfx::createUniform("u_sun_luminance",		bgfx::UniformType::Vec4);
				u_sky_luminance_xyz = bgfx::createUniform("u_sky_luminance_xyz",	bgfx::UniformType::Vec4);
				u_sky_luminance		= bgfx::createUniform("u_sky_luminance",		bgfx::UniformType::Vec4);
				u_sun_direction		= bgfx::createUniform("u_sun_direction",		bgfx::UniformType::Vec4);
				u_sky_params		= bgfx::createUniform("u_sky_params",			bgfx::UniformType::Vec4);
				u_perez_coeff		= bgfx::createUniform("u_perez_coeff",			bgfx::UniformType::Vec4, 5);
			}

			bgfx::UniformHandle u_sun_luminance;
			bgfx::UniformHandle u_sky_luminance_xyz;
			bgfx::UniformHandle u_sky_luminance;
			bgfx::UniformHandle u_sun_direction;
			bgfx::UniformHandle u_sky_params;
			bgfx::UniformHandle u_perez_coeff;

		} u_uniform;

		ProceduralSky m_sky;
		SunController m_sun;

		DynamicValueController m_sun_luminance_xyz;
		DynamicValueController m_sky_luminance_xyz;

		float m_time = 0.0f;
		float m_time_scale = 1.0f;

		float m_turbidity = 2.15f;

		bool m_initialized = false;

		void init(GfxSystem& gfx_system);
		void render(Render& render);
	};

	class _refl_ MUD_GFX_EXPORT BlockSky : public GfxBlock
	{
	public:
		BlockSky(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		BlockFilter& m_filter;

		struct SkyboxUniform
		{
			void createUniforms()
			{
				u_skybox_matrix = bgfx::createUniform("u_skybox_matrix", bgfx::UniformType::Mat4);
				u_skybox_params = bgfx::createUniform("u_skybox_params", bgfx::UniformType::Vec4);
				s_skybox_map = bgfx::createUniform("s_skybox_map", bgfx::UniformType::Int1);
			}

			bgfx::UniformHandle u_skybox_matrix;
			bgfx::UniformHandle u_skybox_params;
			bgfx::UniformHandle s_skybox_map;

		} u_skybox;

		Program m_skybox_program;
	};
}
