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
			u_radiance_p0 = bgfx::createUniform("u_radiance_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			u_ambient_p0 = bgfx::createUniform("u_ambient_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
		}

		void upload(const Pass& pass, const Radiance& radiance) const
		{
			vec4 radiance_p0 = { to_vec3(radiance.m_colour), radiance.m_energy };
			vec4 ambient_p0 = { radiance.m_ambient, 0.f, 0.f, 0.f };

			bgfx::setViewUniform(pass.m_index, u_radiance_p0, &radiance_p0);
			bgfx::setViewUniform(pass.m_index, u_ambient_p0, &ambient_p0);
		}

		bgfx::UniformHandle u_radiance_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_ambient_p0 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<Fog>
	{
		void init()
		{
			u_fog_p0 = bgfx::createUniform("u_fog_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			u_fog_p1 = bgfx::createUniform("u_fog_p1", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			u_fog_p2 = bgfx::createUniform("u_fog_p2", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			u_fog_p3 = bgfx::createUniform("u_fog_p3", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
		}

		void upload(const Pass& pass, const Fog& fog) const
		{
			vec4 params_0 = { fog.m_density, to_vec3(fog.m_colour) };
			vec4 params_1 = { float(fog.m_depth), fog.m_depth_begin, fog.m_depth_curve, 0.f };
			vec4 params_2 = { float(fog.m_height), fog.m_height_max, fog.m_height_max, fog.m_height_curve };
			vec4 params_3 = { float(fog.m_transmit), fog.m_transmit_curve, 0.f, 0.f };

			bgfx::setViewUniform(pass.m_index, u_fog_p0, &params_0);
			bgfx::setViewUniform(pass.m_index, u_fog_p1, &params_1);
			bgfx::setViewUniform(pass.m_index, u_fog_p2, &params_2);
			bgfx::setViewUniform(pass.m_index, u_fog_p3, &params_3);
		}

		bgfx::UniformHandle u_fog_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fog_p1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fog_p2 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fog_p3 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<Zone>
	{
		void upload(const Pass& pass, const Zone& zone) const
		{
			GpuState<Radiance>::me.upload(pass, zone.m_radiance);
			GpuState<Fog>::me.upload(pass, zone.m_fog);
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
			vec4 radiance_p0 = { to_vec3(radiance.m_colour), radiance.m_energy };
			vec4 ambient_p0 = { radiance.m_ambient, 0.f, 0.f, 0.f };

			memcpy(dest + offset, &radiance_p0, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &ambient_p0, sizeof(float) * 4);
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

		void pack(Texture& texture, span<Zone> zones)
		{
			GpuTexture buffer = { texture, 1024, 4 };

			const uint32_t height = GpuState<Radiance>::me.rows
								  + GpuState<Fog>::me.rows;
			const uint32_t lines = 1;
			const uvec2 size = uvec2(buffer.width, lines * height);

			if(texture.m_size != size)
				texture = { size, bgfx::TextureFormat::RGBA32F, GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP };

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
