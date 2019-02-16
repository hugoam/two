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
			u_csm_matrix = bgfx::createUniform("u_csm_matrix", bgfx::UniformType::Mat4, 4);
			u_csm_splits = bgfx::createUniform("u_csm_splits", bgfx::UniformType::Vec4);
		}

		void upload()
		{

		}

		bgfx::UniformHandle u_csm_matrix;
		bgfx::UniformHandle u_csm_splits;

	};

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

}
