//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <math/Vec.hpp>
#include <gfx/Scene.h>
#include <gfx-pbr/Lighting.h>
#endif

#include <cstring>

#define ZONES_LIGHTS_BUFFER 0
#define ZONES_BUFFER 1

namespace mud
{
#if !ZONES_LIGHTS_BUFFER
	template <>
	struct GpuState<ZoneLights>
	{
		void init()
		{
			u_light_indices = bgfx::createUniform("u_light_indices", bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformFreq::View);
			u_light_counts = bgfx::createUniform("u_light_counts", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
		}

		void upload(uint16_t view, const ZoneLights& lights) const
		{
			bgfx::setViewUniform(view, u_light_counts, &lights.m_light_counts);
			if(lights.m_light_count > 0U)
				bgfx::setViewUniform(view, u_light_indices, lights.m_light_indices, lights.m_light_count);
		}

		bgfx::UniformHandle u_light_indices = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_light_counts = BGFX_INVALID_HANDLE;

		static GpuState me;
	};
#else
	template <>
	struct GpuState<ZoneLights>
	{
		constexpr static size_t rows = 1 + BlockLight::ShotUniform::max_lights;

		void pack(const ZoneLights& lights, size_t& offset, GpuTexture& buffer, float* dest)
		{
			memcpy(dest + offset, &lights.m_light_counts, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			for(size_t i = 0; i < BlockLight::ShotUniform::max_lights; ++i)
			{
				memcpy(dest + offset, lights.m_light_indices + i, sizeof(float) * 4);
				offset += buffer.width * buffer.stride;
			}
		}

		static GpuState me;
	};
#endif

#if !ZONES_BUFFER
	template <>
	struct GpuState<Radiance>
	{
		void init()
		{
			u_radiance_color_energy = bgfx::createUniform("u_radiance_color_energy", bgfx::UniformType::Vec4);
			u_ambient_params = bgfx::createUniform("u_ambient_params", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const Radiance& radiance) const
		{
			vec4 radiance_color_energy = { to_vec3(radiance.m_colour), radiance.m_energy };
			vec4 ambient_params = { radiance.m_ambient, 0.f, 0.f, 0.f };

			encoder.setUniform(u_radiance_color_energy, &radiance_color_energy);
			encoder.setUniform(u_ambient_params, &ambient_params);
		}

		bgfx::UniformHandle u_radiance_color_energy = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_ambient_params = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<Fog>
	{
		void init()
		{
			u_fog_params_0 = bgfx::createUniform("u_fog_params_0", bgfx::UniformType::Vec4);
			u_fog_params_1 = bgfx::createUniform("u_fog_params_1", bgfx::UniformType::Vec4);
			u_fog_params_2 = bgfx::createUniform("u_fog_params_2", bgfx::UniformType::Vec4);
			u_fog_params_3 = bgfx::createUniform("u_fog_params_3", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const Fog& fog) const
		{
			vec4 params_0 = { fog.m_density, to_vec3(fog.m_colour) };
			vec4 params_1 = { float(fog.m_depth), fog.m_depth_begin, fog.m_depth_curve, 0.f };
			vec4 params_2 = { float(fog.m_height), fog.m_height_max, fog.m_height_max, fog.m_height_curve };
			vec4 params_3 = { float(fog.m_transmit), fog.m_transmit_curve, 0.f, 0.f };

			encoder.setUniform(u_fog_params_0, &params_0);
			encoder.setUniform(u_fog_params_1, &params_1);
			encoder.setUniform(u_fog_params_2, &params_2);
			encoder.setUniform(u_fog_params_3, &params_3);
		}

		bgfx::UniformHandle u_fog_params_0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fog_params_1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fog_params_2 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fog_params_3 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<Zone>
	{
		void upload(bgfx::Encoder& encoder, const Zone& zone) const
		{
			GpuState<Radiance>::me.upload(encoder, zone.m_radiance);
			if(zone.m_fog.m_enabled)
				GpuState<Fog>::me.upload(encoder, zone.m_fog);
		}

		static GpuState me;
	};
#else
	template <>
	struct GpuState<Radiance>
	{
		constexpr static size_t rows = 2;

		void pack(const Radiance& radiance, size_t& offset, GpuTexture& buffer, float* dest)
		{
			vec4 radiance_color_energy = { to_vec3(radiance.m_colour), radiance.m_energy };
			vec4 ambient_params = { radiance.m_ambient, 0.f, 0.f, 0.f };

			memcpy(dest + offset, &radiance_color_energy, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &ambient_params, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<Fog>
	{
		constexpr static size_t rows = 4;

		void pack(const Fog& fog, size_t& offset, GpuTexture& buffer, float* dest)
		{
			vec4 params_0 = { fog.m_density, to_vec3(fog.m_colour) };
			vec4 params_1 = { float(fog.m_depth), fog.m_depth_begin, fog.m_depth_curve, 0.f };
			vec4 params_2 = { float(fog.m_height), fog.m_height_max, fog.m_height_max, fog.m_height_curve };
			vec4 params_3 = { float(fog.m_transmit), fog.m_transmit_curve, 0.f, 0.f };

			memcpy(dest + offset, &params_0, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params_1, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params_2, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params_3, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<Zone>
	{
		void pack(const Zone& zone, size_t offset, GpuTexture& buffer, float* dest)
		{
			GpuState<Radiance>::me.me.pack(zone.m_radiance, offset, buffer, dest);
			if(zone.m_fog.m_enabled)
				GpuState<Fog>::me.me.pack(zone.m_fog, offset, buffer, dest);
		}

		void pack(bgfx::TextureHandle& texture, span<Zone> zones)
		{
			GpuTexture buffer = { texture, 1024, 4 };

			uint32_t height = GpuState<Radiance>::me.rows
						    + GpuState<Fog>::me.rows;
			uint32_t lines = 1;

			if(!bgfx::isValid(texture))
				texture = bgfx::createTexture2D(buffer.width, uint16_t(lines * height), false, 1, bgfx::TextureFormat::RGBA32F, GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP);

			const bgfx::Memory* memory = bgfx::alloc(buffer.width * lines * height * buffer.stride * sizeof(float));

			for(size_t index = 0; index < zones.size(); ++index)
			{
				this->pack(zones[index], index * buffer.stride, buffer, (float*)memory->data);
			}

			bgfx::updateTexture2D(texture, 0, 0, 0, 0, buffer.width, uint16_t(lines * height), memory);
		}

		static GpuState me;
	};
#endif
}
