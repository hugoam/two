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
#include <gfx-pbr/Shadow.h>

#include <cstring>

namespace mud
{
	template <>
	struct GpuState<GpuCSM>
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

	template <>
	struct GpuState<GpuShadow>
	{
		void init()
		{
			u_shadow_matrix = bgfx::createUniform("u_shadow_matrix", bgfx::UniformType::Mat4, c_max_shadows, bgfx::UniformFreq::View);
		}

		void upload(const Pass& render_pass, span<mat4> matrices)
		{
			bgfx::setViewUniform(render_pass.m_index, u_shadow_matrix, matrices.m_pointer, uint16_t(matrices.size()));
		}

		bgfx::UniformHandle u_shadow_matrix;

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
			u_light_spot_p0				= bgfx::createUniform("u_light_spot_p0",			bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformFreq::View);
			u_light_shadow_p0			= bgfx::createUniform("u_light_shadow_p0",			bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformFreq::View);
			u_light_shadowmap_p0		= bgfx::createUniform("u_light_shadowmap_p0",		bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformFreq::View);
		}

		void upload(const Pass& render_pass, span<GpuLight> lights, span<GpuLightShadow> shadows) const
		{
			vec4 position_range[c_max_forward_lights];
			vec4 energy_specular[c_max_forward_lights];
			vec4 direction_attenuation[c_max_forward_lights];
			vec4 spot_p0[c_max_forward_lights];
			vec4 shadow_p0[c_max_forward_lights];
			vec4 shadowmap_p0[c_max_forward_lights];
			//mat4 shadow_matrix[c_max_forward_lights];

			for(size_t i = 0; i < lights.size(); ++i)
			{
				GpuLight& l = lights[i];
				position_range[i] = { l.position, l.range };
				energy_specular[i] = { l.energy, l.specular };
				direction_attenuation[i] = { l.direction, l.attenuation };
				spot_p0[i] = { l.spot_attenuation, l.spot_cutoff, 0.f, 0.f };
			}

			for(size_t i = 0; i < lights.size(); ++i)
			{
				GpuLightShadow& s = shadows[i];
				shadow_p0[i] = { s.matrix, s.bias, s.radius, 0.f };
				shadowmap_p0[i] = { s.atlas_slot, s.atlas_subdiv };
			}

			bgfx::setViewUniform(render_pass.m_index, u_light_position_range,			&position_range,		uint16_t(lights.size()));
			bgfx::setViewUniform(render_pass.m_index, u_light_energy_specular,			&energy_specular,		uint16_t(lights.size()));
			bgfx::setViewUniform(render_pass.m_index, u_light_direction_attenuation,	&direction_attenuation,	uint16_t(lights.size()));
			bgfx::setViewUniform(render_pass.m_index, u_light_spot_p0,				&spot_p0,			uint16_t(lights.size()));
			bgfx::setViewUniform(render_pass.m_index, u_light_shadow_p0,			&shadow_p0,			uint16_t(lights.size()));
			bgfx::setViewUniform(render_pass.m_index, u_light_shadowmap_p0,			&shadowmap_p0,		uint16_t(lights.size()));
		}

		bgfx::UniformHandle u_light_position_range;
		bgfx::UniformHandle u_light_energy_specular;
		bgfx::UniformHandle u_light_direction_attenuation;
		bgfx::UniformHandle u_light_spot_p0;
		bgfx::UniformHandle u_light_shadow_p0;
		bgfx::UniformHandle u_light_shadowmap_p0;

		static GpuState me;
	};
#else
	template <>
	struct GpuState<GpuLight>
	{
		void pack(GpuLight& gpu_light, GpuLightShadow& gpu_shadow, size_t index, const GpuTexture& buffer, float* dest)
		{
			size_t offset = index * buffer.stride;// + (index % texture_size) * height;

			//memcpy(pack, &gpu_light, sizeof(GpuLight));

			memcpy(dest + offset, &gpu_light.position, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.energy, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.direction, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.spot_attenuation, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_shadow.matrix, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_shadow.atlas_slot, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		void pack(Texture& texture, span<GpuLight> lights, span<GpuLightShadow> shadows)
		{
			GpuTexture buffer = { texture, 1024, 4 };

			const size_t height = 6;
			const size_t lines = 1;
			const uvec2 size = uvec2(buffer.width, uint16_t(lines * height));

			if(!texture.m_size != size)
				texture = { size, bgfx::TextureFormat::RGBA32F, GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP };

			const uint32_t size = uint32_t(buffer.width * lines * height);
			const bgfx::Memory* memory = bgfx::alloc(uint32_t(size * buffer.stride * sizeof(float)));

			for(size_t index = 0; index < lights.size(); ++index)
			{
				this->pack(lights[index], shadows[index], index, buffer, (float*)memory->data);
			}

			//const bgfx::Memory* mem = bgfx::makeRef(m_texture_data.data(), sizeof(float) * m_texture_data.size());
			bgfx::updateTexture2D(texture, 0, 0, 0, 0, buffer.width, uint16_t(lines * height), memory);
		}

		static GpuState me;
	};
#endif
}
