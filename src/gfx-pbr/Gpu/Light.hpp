//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <cstring>
#include <math/Vec.hpp>
#include <gfx/Light.h>
#include <gfx/Node3.h>
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Lighting.h>
#include <gfx-pbr/Shadow.h>

#define PAD 0.f

namespace two
{
	export_ template <>
	struct GpuState<GpuShadow>
	{
		void init()
		{
			u_shadow_matrix = bgfx::createUniform("u_shadow_matrix", bgfx::UniformType::Mat4, c_max_shadows, bgfx::UniformSet::View);
		}

		void upload(const Pass& pass, span<mat4> matrices)
		{
			bgfx::setViewUniform(pass.m_index, u_shadow_matrix, matrices.m_pointer, uint16_t(matrices.size()));
		}

		bgfx::UniformHandle u_shadow_matrix;

		static GpuState me;
	};

#if !LIGHTS_BUFFER
	export_ template <>
	struct GpuState<GpuLight>
	{
		void init()
		{
			u_light_position_range			= bgfx::createUniform("u_light_position_range",			bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_energy_specular			= bgfx::createUniform("u_light_energy_specular",		bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_direction_attenuation	= bgfx::createUniform("u_light_direction_attenuation",	bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_spot_p0					= bgfx::createUniform("u_light_spot_p0",				bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_shadow_p0				= bgfx::createUniform("u_light_shadow_p0",				bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_shadowmap_p0			= bgfx::createUniform("u_light_shadowmap_p0",			bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_csm_p0					= bgfx::createUniform("u_light_csm_p0",					bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_csm_p1					= bgfx::createUniform("u_light_csm_p1",					bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_csm_p2					= bgfx::createUniform("u_light_csm_p2",					bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
		}

		void upload(const Pass& pass, span<GpuLight> lights) const
		{
			vec4 position_range[c_max_forward_lights];
			vec4 energy_specular[c_max_forward_lights];
			vec4 direction_attenuation[c_max_forward_lights];
			vec4 spot_p0[c_max_forward_lights];
			vec4 shadow_p0[c_max_forward_lights];
			vec4 shadowmap_p0[c_max_forward_lights];
			vec4 csm_p0[c_max_forward_lights];
			vec4 csm_p1[c_max_forward_lights];
			vec4 csm_p2[c_max_forward_lights];
			//mat4 shadow_matrix[c_max_forward_lights];

			for(size_t i = 0; i < lights.size(); ++i)
			{
				const GpuLight& l = lights[i];
				const GpuShadow& s = l.shadow;
				const GpuCSMShadow& csm = l.csm;

				position_range[i] = { l.position, l.range };
				energy_specular[i] = { l.energy, l.specular };
				direction_attenuation[i] = { l.direction, l.attenuation };
				spot_p0[i] = { l.spot_attenuation, l.spot_cutoff, PAD, PAD };

				shadow_p0[i] = { s.matrix, s.bias, s.radius, s.range };
				shadowmap_p0[i] = { s.atlas_slot, s.atlas_subdiv };

				csm_p0[i] = { csm.num_slices, PAD, PAD, PAD };
				csm_p1[i] = csm.matrices;
				csm_p2[i] = csm.splits;
			}

			bgfx::setViewUniform(pass.m_index, u_light_position_range,			&position_range,		uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_energy_specular,			&energy_specular,		uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_direction_attenuation,	&direction_attenuation,	uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_spot_p0,					&spot_p0,				uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_shadow_p0,				&shadow_p0,				uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_shadowmap_p0,			&shadowmap_p0,			uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_csm_p0,					&csm_p0,				uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_csm_p1,					&csm_p1,				uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_csm_p2,					&csm_p2,				uint16_t(lights.size()));
		}

		bgfx::UniformHandle u_light_position_range;
		bgfx::UniformHandle u_light_energy_specular;
		bgfx::UniformHandle u_light_direction_attenuation;
		bgfx::UniformHandle u_light_spot_p0;
		bgfx::UniformHandle u_light_shadow_p0;
		bgfx::UniformHandle u_light_shadowmap_p0;
		bgfx::UniformHandle u_light_csm_p0;
		bgfx::UniformHandle u_light_csm_p1;
		bgfx::UniformHandle u_light_csm_p2;

		static GpuState me;
	};
#else
	export_ template <>
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

			memcpy(dest + offset, &gpu_light.spot_attenuation, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.shadow.matrix, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.shadow.atlas_slot, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.csm.num_slices, sizeof(float) * 1);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.csm.matrices, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.csm.splits, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		void pack(GpuTexture& buffer, span<GpuLight> lights)
		{
			const size_t height = 9;
			const size_t lines = 1;
			const uvec2 size = uvec2(buffer.width, uint16_t(lines * height));

			// swap two buffers so that bgfx can still read the previous one
			swap(buffer.memory, buffer.prev);

			if(buffer.texture.m_size != size)
				buffer.texture = { size, false, TextureFormat::RGBA32F, TEXTURE_POINT | TEXTURE_CLAMP };

			const uint32_t memsize = uint32_t(size.x * size.y * buffer.stride);
			buffer.memory.resize(memsize);
			for(size_t index = 0; index < lights.size(); ++index)
			{
				this->pack(lights[index], index, buffer, buffer.memory.data());
			}

			const bgfx::Memory* mem = bgfx::makeRef(buffer.memory.data(), sizeof(float) * buffer.memory.size());
			bgfx::updateTexture2D(buffer.texture, 0, 0, 0, 0, buffer.width, uint16_t(lines * height), mem);
		}

		static GpuState me;
	};
#endif
}

#undef PAD
