//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.hpp>
#include <gfx/Light.h>
#include <gfx/Node3.h>
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Lighting.h>

#include <cstring>

namespace mud
{
	template <>
	struct GpuState<CSMShadow>
	{
		void init()
		{
			u_csm_matrix = bgfx::createUniform("u_csm_matrix", bgfx::UniformType::Mat4, 4U, bgfx::UniformFreq::View);
			u_csm_splits = bgfx::createUniform("u_csm_splits", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
		}

		void upload(const Pass& render_pass, span<mat4> matrices, const vec4& splits)
		{
			bgfx::setViewUniform(render_pass.m_index, u_csm_matrix, matrices.m_pointer, 4U);
			bgfx::setViewUniform(render_pass.m_index, u_csm_splits, &splits);
		}

		bgfx::UniformHandle u_csm_matrix;
		bgfx::UniformHandle u_csm_splits;

		static GpuState me;
	};

#if !LIGHTS_BUFFER
	template <>
	struct GpuState<GpuLight>
	{
		void init()
		{
			u_light_position_range			= bgfx::createUniform("u_light_position_range",			bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformFreq::View);
			u_light_energy_specular			= bgfx::createUniform("u_light_energy_specular",		bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformFreq::View);
			u_light_direction_attenuation	= bgfx::createUniform("u_light_direction_attenuation",	bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformFreq::View);
			u_light_shadow					= bgfx::createUniform("u_light_shadow",					bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformFreq::View);
			u_light_spot_params				= bgfx::createUniform("u_light_spot_params",			bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformFreq::View);
			u_light_shadow_matrix			= bgfx::createUniform("u_light_shadow_matrix",			bgfx::UniformType::Mat4, c_max_forward_lights, bgfx::UniformFreq::View);
		}

		void upload(const Pass& render_pass, span<GpuLight> lights) const
		{
			vec4 position_range[c_max_forward_lights];
			vec4 energy_specular[c_max_forward_lights];
			vec4 direction_attenuation[c_max_forward_lights];
			vec4 shadow_color_enabled[c_max_forward_lights];
			vec4 spot_params[c_max_forward_lights];
			//mat4 shadow_matrix[c_max_forward_lights];

			for(size_t i = 0; i < lights.size(); ++i)
			{
				GpuLight& l = lights[i];
				position_range[i] = { l.position, l.range };
				energy_specular[i] = { l.energy, l.specular };
				direction_attenuation[i] = { l.direction, l.attenuation };
				shadow_color_enabled[i] = { l.shadow_color, l.shadow_enabled };
				spot_params[i] = { l.spot_attenuation, l.spot_cutoff, 0.f, 0.f };
			}

			bgfx::setViewUniform(render_pass.m_index, u_light_position_range,			&position_range,		uint16_t(lights.size()));
			bgfx::setViewUniform(render_pass.m_index, u_light_energy_specular,			&energy_specular,		uint16_t(lights.size()));
			bgfx::setViewUniform(render_pass.m_index, u_light_direction_attenuation,	&direction_attenuation,	uint16_t(lights.size()));
			bgfx::setViewUniform(render_pass.m_index, u_light_shadow,					&shadow_color_enabled,	uint16_t(lights.size()));
			bgfx::setViewUniform(render_pass.m_index, u_light_spot_params,				&spot_params,			uint16_t(lights.size()));
			//bgfx::setViewUniform(render_pass.m_index, u_light_shadow_matrix,			&shadow_matrix,			uint16_t(lights.size()));
		}

		bgfx::UniformHandle u_light_position_range;
		bgfx::UniformHandle u_light_energy_specular;
		bgfx::UniformHandle u_light_direction_attenuation;
		bgfx::UniformHandle u_light_shadow;
		bgfx::UniformHandle u_light_shadow_matrix;
		bgfx::UniformHandle u_light_spot_params;

		static GpuState me;
	};
#else
	template <>
	struct GpuState<GpuLight>
	{
		void pack(GpuLight& gpu_light, size_t index, const GpuTexture& buffer, float* dest)
		{
			size_t offset = index * buffer.stride;// + (index % texture_size) * height;

			//memcpy(pack, &gpu_light, sizeof(GpuLight));

			memcpy(dest + offset, &gpu_light.position, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.energy, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.direction, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.shadow_enabled, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.spot_attenuation, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;
		}

		void pack(bgfx::TextureHandle& texture, span<GpuLight> lights)
		{
			GpuTexture buffer = { texture, 1024, 4 };

			size_t height = 5;
			size_t lines = 1;

			if(!bgfx::isValid(texture))
				texture = bgfx::createTexture2D(buffer.width, uint16_t(lines * height), false, 1, bgfx::TextureFormat::RGBA32F, GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP);

			const bgfx::Memory* memory = bgfx::alloc(buffer.width * lines * height * buffer.stride * sizeof(float));

			for(size_t index = 0; index < lights.size(); ++index)
			{
				this->pack(lights[index], index, buffer, (float*)memory->data);
			}

			//const bgfx::Memory* mem = bgfx::makeRef(m_texture_data.data(), sizeof(float) * m_texture_data.size());
			bgfx::updateTexture2D(texture, 0, 0, 0, 0, buffer.width, uint16_t(lines * height), memory);
		}

		static GpuState me;
	};
#endif
}
