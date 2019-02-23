//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <math/Vec.hpp>
#include <gfx/Material.h>
#endif

#include <cstring>

namespace mud
{
#if !MATERIALS_BUFFER
	template <>
	struct GpuState<MaterialBase>
	{
		void init()
		{
			u_uv0_scale_offset = bgfx::createUniform("u_material_params_0", bgfx::UniformType::Vec4);
			u_uv1_scale_offset = bgfx::createUniform("u_material_params_1", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialBase& block) const
		{
			encoder.setUniform(u_uv0_scale_offset, &block.m_uv0_scale.x);
			//encoder.setUniform(u_uv1_scale_offset, &block.m_uv1_scale.x);
		}

		bgfx::UniformHandle u_uv0_scale_offset = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_uv1_scale_offset = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialAlpha>
	{
		void init()
		{
			u_alpha = bgfx::createUniform("u_alpha", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialAlpha& block) const
		{
			encoder.setUniform(u_alpha, &block.m_alpha);
		}

		bgfx::UniformHandle u_alpha = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialUnshaded>
	{
		void init()
		{
			u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialUnshaded& block) const
		{
			vec4 colour = to_vec4(block.m_colour.m_value);
			encoder.setUniform(u_color, &colour);
		}

		bgfx::UniformHandle u_color = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialFresnel>
	{
		void init()
		{
			u_fresnel_params = bgfx::createUniform("u_fresnel_params", bgfx::UniformType::Vec4);
			u_fresnel_value = bgfx::createUniform("u_fresnel_value", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialFresnel& block) const
		{
			vec4 value = to_vec4(block.m_value.m_value);
			vec4 params = { block.m_fresnel_bias, block.m_fresnel_scale, block.m_fresnel_power, 1.f };
			encoder.setUniform(u_fresnel_value, &value);
			encoder.setUniform(u_fresnel_params, &params);
		}

		bgfx::UniformHandle u_fresnel_params = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fresnel_value = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPbr>
	{
		void init()
		{
			u_albedo = bgfx::createUniform("u_albedo", bgfx::UniformType::Vec4);
			u_pbr_params_0 = bgfx::createUniform("u_pbr_params_0", bgfx::UniformType::Vec4);
			u_pbr_params_1 = bgfx::createUniform("u_pbr_params_1", bgfx::UniformType::Vec4);
			u_pbr_channels_0 = bgfx::createUniform("u_pbr_channels_0", bgfx::UniformType::Vec4);
			u_emissive = bgfx::createUniform("u_emissive", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPbr& block) const
		{
			vec4 albedo = { to_vec3(block.m_albedo.m_value), 1.f }; //block.m_alpha.m_value };
			encoder.setUniform(u_albedo, &albedo);

			vec4 spec_met_rough = { block.m_specular, block.m_metallic.m_value, block.m_roughness.m_value, block.m_normal.m_value };
			encoder.setUniform(u_pbr_params_0, &spec_met_rough);

			vec4 emissive = to_vec4(block.m_emissive.m_value);
			encoder.setUniform(u_emissive, &emissive);

			vec4 pbr_params_1 = { block.m_anisotropy.m_value, block.m_refraction.m_value, block.m_subsurface.m_value, block.m_depth.m_value };
			encoder.setUniform(u_pbr_params_1, &pbr_params_1);

			vec4 pbr_channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), 0.f, 0.f };
			encoder.setUniform(u_pbr_channels_0, &pbr_channels);
		}

		bgfx::UniformHandle u_albedo = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_pbr_params_0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_pbr_params_1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_pbr_channels_0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_emissive = BGFX_INVALID_HANDLE;
		//bgfx::UniformHandle u_lightmap_params;

		static GpuState me;
	};

	template <>
	struct GpuState<Material>
	{
		void upload(bgfx::Encoder& encoder, const Material& material) const
		{
			GpuState<MaterialBase>::me.upload(encoder, material.m_base);
			GpuState<MaterialAlpha>::me.upload(encoder, material.m_alpha);
			GpuState<MaterialUnshaded>::me.upload(encoder, material.m_unshaded);
			GpuState<MaterialPbr>::me.upload(encoder, material.m_pbr);
			GpuState<MaterialFresnel>::me.upload(encoder, material.m_fresnel);
		}

		static GpuState me;
	};
#else

	template <>
	struct GpuState<MaterialBase>
	{
		constexpr static size_t rows = 2;

		void pack(const MaterialBase& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 uv0_scale_offset = { block.m_uv0_scale, block.m_uv0_offset };
			vec4 uv1_scale_offset = { block.m_uv1_scale, block.m_uv1_offset };

			memcpy(dest + offset, &uv0_scale_offset, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &uv1_scale_offset, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialAlpha>
	{
		constexpr static size_t rows = 1;

		void pack(const MaterialAlpha& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 alpha = { block.m_alpha.m_value, 0.f, 0.f, 0.f };

			memcpy(dest + offset, &alpha, sizeof(float) * 1);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialUnshaded>
	{
		constexpr static size_t rows = 1;

		void pack(const MaterialUnshaded& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 color = { to_vec4(block.m_colour.m_value) };

			memcpy(dest + offset, &color, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPbr>
	{
		constexpr static size_t rows = 5;

		void pack(const MaterialPbr& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 albedo = { to_vec3(block.m_albedo.m_value), 0.f };
			vec4 spec_met_rough = { block.m_specular, block.m_metallic.m_value, block.m_roughness.m_value, block.m_normal.m_value };
			vec4 emissive = { to_vec3(block.m_emissive.m_value), block.m_emissive.m_value.m_a };
			vec4 channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), 0.f, 0.f };
			vec4 params = { block.m_anisotropy.m_value, block.m_refraction.m_value, block.m_subsurface.m_value, block.m_depth.m_value };

			memcpy(dest + offset, &albedo, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &spec_met_rough, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &emissive, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &channels, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			//memcpy(dest + offset, &gp.rim, sizeof(float) * 4);
			//offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<Material>
	{
		void pack(const Material& material, size_t index, const GpuTexture& buffer, float* dest)
		{
			size_t offset = index * buffer.stride;// + (index % texture_size) * height;

			GpuState<MaterialBase>::me.me.pack(material.m_base, offset, buffer, dest);
			GpuState<MaterialAlpha>::me.me.pack(material.m_alpha, offset, buffer, dest);
			GpuState<MaterialUnshaded>::me.me.pack(material.m_unshaded, offset, buffer, dest);
			GpuState<MaterialPbr>::me.me.pack(material.m_pbr, offset, buffer, dest);
			//GpuState<MaterialFresnel>::me.me.pack(material.m_fresnel, offset, buffer, dest);
		}

		void pack(bgfx::TextureHandle& texture, span<Material*> materials)
		{
			GpuTexture buffer = { texture, 1024, 4 };

			uint32_t height = GpuState<MaterialBase>::me.rows
							+ GpuState<MaterialAlpha>::me.rows
						    + GpuState<MaterialUnshaded>::me.rows
						    + GpuState<MaterialPbr>::me.rows;
			uint32_t lines = 1;

			if(!bgfx::isValid(texture))
				texture = bgfx::createTexture2D(buffer.width, uint16_t(lines * height), false, 1, bgfx::TextureFormat::RGBA32F, GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP);

			const bgfx::Memory* memory = bgfx::alloc(buffer.width * lines * height * buffer.stride * sizeof(float));

			for(size_t index = 0; index < materials.size(); ++index)
			{
				this->pack(*materials[index], index, buffer, (float*)memory->data);
			}

			//const bgfx::Memory* mem = bgfx::makeRef(m_texture_data.data(), sizeof(float) * m_texture_data.size());
			bgfx::updateTexture2D(texture, 0, 0, 0, 0, buffer.width, uint16_t(lines * height), memory);
		}

		static GpuState me;
	};
#endif
}
