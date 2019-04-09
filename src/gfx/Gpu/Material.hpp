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

#define PAD 0.f

namespace mud
{
#if !MATERIALS_BUFFER
	template <>
	struct GpuState<MaterialBase>
	{
		void init()
		{
			u_uv0_scale_offset = bgfx::createUniform("u_material_p0", bgfx::UniformType::Vec4);
			u_uv1_scale_offset = bgfx::createUniform("u_material_p1", bgfx::UniformType::Vec4);
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
			vec4 alpha = { block.m_alpha.m_value, PAD, PAD, PAD };
			encoder.setUniform(u_alpha, &alpha);
		}

		bgfx::UniformHandle u_alpha = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialSolid>
	{
		void init()
		{
			u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialSolid& block) const
		{
			vec4 colour = to_vec4(block.m_colour.m_value);
			encoder.setUniform(u_color, &colour);
		}

		bgfx::UniformHandle u_color = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPoint>
	{
		void init()
		{
			u_point_p0 = bgfx::createUniform("u_point_p0", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPoint& block) const
		{
			vec4 params = { block.m_point_size, float(block.m_project), PAD, PAD };
			encoder.setUniform(u_point_p0, &params);
		}

		bgfx::UniformHandle u_point_p0 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialLine>
	{
		void init()
		{
			// @kludge those are split only as a workaround for precision mismatch between frag and vertex shaders in bgfx
			u_line_p0 = bgfx::createUniform("u_line_p0", bgfx::UniformType::Vec4);
			u_line_p1 = bgfx::createUniform("u_line_p1", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialLine& block) const
		{
			vec4 p0 = { block.m_line_width, block.m_dash_scale, PAD, PAD };
			vec4 p1 = { block.m_dash_size, block.m_dash_gap, PAD, PAD };
			encoder.setUniform(u_line_p0, &p0);
			encoder.setUniform(u_line_p1, &p1);
		}

		bgfx::UniformHandle u_line_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_line_p1 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialFresnel>
	{
		void init()
		{
			u_fresnel_p0 = bgfx::createUniform("u_fresnel_p0", bgfx::UniformType::Vec4);
			u_fresnel_value = bgfx::createUniform("u_fresnel_value", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialFresnel& block) const
		{
			vec4 value = to_vec4(block.m_value.m_value);
			vec4 params = { block.m_fresnel_bias, block.m_fresnel_scale, block.m_fresnel_power, 1.f };
			encoder.setUniform(u_fresnel_value, &value);
			encoder.setUniform(u_fresnel_p0, &params);
		}

		bgfx::UniformHandle u_fresnel_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fresnel_value = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialLit>
	{
		void init()
		{
			u_lit_p0 = bgfx::createUniform("u_lit_p0", bgfx::UniformType::Vec4);
			u_lit_p1 = bgfx::createUniform("u_lit_p1", bgfx::UniformType::Vec4);
			u_emissive = bgfx::createUniform("u_emissive", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialLit& block) const
		{
			vec4 p0 = { block.m_normal.m_value, PAD, PAD, PAD };
			encoder.setUniform(u_lit_p0, &p0);

			vec4 emissive = to_vec4(block.m_emissive.m_value);
			encoder.setUniform(u_emissive, &emissive);

			vec4 p1 = { block.m_displace.m_value, block.m_displace_bias, PAD, PAD };
			encoder.setUniform(u_lit_p1, &p1);
		}

		bgfx::UniformHandle u_lit_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_lit_p1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_emissive = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPbr>
	{
		void init()
		{
			u_albedo = bgfx::createUniform("u_albedo", bgfx::UniformType::Vec4);
			u_pbr_p0 = bgfx::createUniform("u_pbr_p0", bgfx::UniformType::Vec4);
			u_pbr_p1 = bgfx::createUniform("u_pbr_p1", bgfx::UniformType::Vec4);
			u_pbr_channels_0 = bgfx::createUniform("u_pbr_channels_0", bgfx::UniformType::Vec4);
			u_emissive = bgfx::createUniform("u_emissive", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPbr& block) const
		{
			vec4 albedo = { to_vec3(block.m_albedo.m_value), 1.f }; //block.m_alpha.m_value };
			encoder.setUniform(u_albedo, &albedo);

			vec4 pbr_p0 = { block.m_specular, block.m_metallic.m_value, block.m_roughness.m_value, PAD };
			encoder.setUniform(u_pbr_p0, &pbr_p0);

			vec4 pbr_p1 = { block.m_anisotropy.m_value, block.m_refraction.m_value, block.m_subsurface.m_value, block.m_depth.m_value };
			encoder.setUniform(u_pbr_p1, &pbr_p1);

			//vec4 pbr_channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), float(block.m_occlusion.m_channel), PAD };
			vec4 pbr_channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), PAD, PAD };
			encoder.setUniform(u_pbr_channels_0, &pbr_channels);
		}

		bgfx::UniformHandle u_albedo = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_pbr_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_pbr_p1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_pbr_channels_0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_emissive = BGFX_INVALID_HANDLE;
		//bgfx::UniformHandle u_lightmap_p0;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPhong>
	{
		void init()
		{
			u_diffuse = bgfx::createUniform("u_diffuse", bgfx::UniformType::Vec4);
			u_specular = bgfx::createUniform("u_specular", bgfx::UniformType::Vec4);
			u_phong_p0 = bgfx::createUniform("u_phong_p0", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPhong& block) const
		{
			vec4 diffuse = { to_vec3(block.m_diffuse.m_value), 1.f };
			encoder.setUniform(u_diffuse, &diffuse);

			vec4 specular = { to_vec3(block.m_specular.m_value), 1.f };
			encoder.setUniform(u_specular, &specular);

			vec4 p0 = { block.m_shininess.m_value, block.m_reflectivity.m_value, block.m_refraction.m_value, PAD };
			encoder.setUniform(u_phong_p0, &p0);
		}

		bgfx::UniformHandle u_diffuse = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_specular = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_phong_p0 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialUser>
	{
		void init()
		{
			u_p0 = bgfx::createUniform("u_user_p0", bgfx::UniformType::Vec4);
			u_p1 = bgfx::createUniform("u_user_p1", bgfx::UniformType::Vec4);
			u_p2 = bgfx::createUniform("u_user_p2", bgfx::UniformType::Vec4);
			u_p3 = bgfx::createUniform("u_user_p3", bgfx::UniformType::Vec4);
			u_p4 = bgfx::createUniform("u_user_p4", bgfx::UniformType::Vec4);
			u_p5 = bgfx::createUniform("u_user_p5", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialUser& block) const
		{
			encoder.setUniform(u_p0, &block.m_attr0);
			encoder.setUniform(u_p1, &block.m_attr1);
			encoder.setUniform(u_p2, &block.m_attr2);
			encoder.setUniform(u_p3, &block.m_attr3);
			encoder.setUniform(u_p4, &block.m_attr4);
			encoder.setUniform(u_p5, &block.m_attr5);
		}

		bgfx::UniformHandle u_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p2 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p3 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p4 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p5 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<Material>
	{
		void upload(bgfx::Encoder& encoder, const Material& material) const
		{
			GpuState<MaterialBase>::me.upload(encoder, material.m_base);
			GpuState<MaterialAlpha>::me.upload(encoder, material.m_alpha);
			GpuState<MaterialSolid>::me.upload(encoder, material.m_solid);
			GpuState<MaterialPoint>::me.upload(encoder, material.m_point);
			GpuState<MaterialLine>::me.upload(encoder, material.m_line);
			GpuState<MaterialLit>::me.upload(encoder, material.m_lit);
			GpuState<MaterialPbr>::me.upload(encoder, material.m_pbr);
			GpuState<MaterialPhong>::me.upload(encoder, material.m_phong);
			GpuState<MaterialFresnel>::me.upload(encoder, material.m_fresnel);
			GpuState<MaterialUser>::me.upload(encoder, material.m_user);
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
			vec4 alpha = { block.m_alpha.m_value, PAD, PAD, PAD };

			memcpy(dest + offset, &alpha, sizeof(float) * 1);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialSolid>
	{
		constexpr static size_t rows = 1;

		void pack(const MaterialSolid& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 color = { to_vec4(block.m_colour.m_value) };

			memcpy(dest + offset, &color, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPoint>
	{
		constexpr static size_t rows = 1;

		void pack(const MaterialPoint& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 params = { block.m_point_size, float(block.m_project), PAD, PAD };

			memcpy(dest + offset, &params, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialLine>
	{
		constexpr static size_t rows = 1;

		void pack(const MaterialLine& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 params = { block.m_line_width, block.m_dash_scale, block.m_dash_size, block.m_dash_gap };

			memcpy(dest + offset, &params, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialLit>
	{
		constexpr static size_t rows = 3;

		void pack(const MaterialLit& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 p0 = { block.m_normal.m_value, PAD, PAD, PAD };
			vec4 emissive = { to_vec3(block.m_emissive.m_value), block.m_emissive.m_value.a };
			vec4 p1 = { block.m_displace.m_value, block.m_displace_bias, PAD, PAD };

			memcpy(dest + offset, &p0, sizeof(float) * 1);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &emissive, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &p1, sizeof(float) * 2);
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
			vec4 albedo = { to_vec3(block.m_albedo.m_value), PAD };
			vec4 spec_met_rough = { block.m_specular, block.m_metallic.m_value, block.m_roughness.m_value, PAD };
			vec4 channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), PAD, PAD };
			vec4 params1 = { block.m_anisotropy.m_value, block.m_refraction.m_value, block.m_subsurface.m_value, block.m_depth.m_value };
			vec4 params2 = { block.m_rim.m_value, block.m_rim_tint, block.m_clearcoat.m_value, block.m_clearcoat_gloss };

			memcpy(dest + offset, &albedo, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &spec_met_rough, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &channels, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params1, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params2, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPhong>
	{
		constexpr static size_t rows = 3;

		void pack(const MaterialPhong& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 diffuse = { to_vec3(block.m_diffuse.m_value), PAD };
			vec4 specular = { to_vec3(block.m_specular.m_value), PAD };
			vec4 p0 = { block.m_shininess.m_value, block.m_reflectivity.m_value, block.m_refraction.m_value, PAD };

			memcpy(dest + offset, &diffuse, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &specular, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &p0, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialUser>
	{
		constexpr static size_t rows = 6;

		void pack(const MaterialUser& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			memcpy(dest + offset, &block.m_attr0, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr1, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr2, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr3, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr4, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr5, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};
	template <>
	struct GpuState<Material>
	{
		void pack(const Material& material, size_t index, const GpuTexture& buffer, float* dest)
		{
			size_t offset = index * buffer.stride;// + (index % texture_size) * height;

			GpuState<MaterialBase>::me.pack(material.m_base, offset, buffer, dest);
			GpuState<MaterialAlpha>::me.pack(material.m_alpha, offset, buffer, dest);
			GpuState<MaterialSolid>::me.pack(material.m_solid, offset, buffer, dest);
			GpuState<MaterialPoint>::me.pack(material.m_point, offset, buffer, dest);
			GpuState<MaterialLine>::me.pack(material.m_line, offset, buffer, dest);
			GpuState<MaterialLit>::me.pack(material.m_lit, offset, buffer, dest);
			GpuState<MaterialPbr>::me.pack(material.m_pbr, offset, buffer, dest);
			GpuState<MaterialPhong>::me.pack(material.m_phong, offset, buffer, dest);
			//GpuState<MaterialFresnel>::me.pack(material.m_fresnel, offset, buffer, dest);
			GpuState<MaterialUser>::me.pack(material.m_user, offset, buffer, dest);
		}

		void pack(Texture& texture, span<Material*> materials)
		{
			GpuTexture buffer = { &texture, 1024, 4 };

			const uint32_t height = GpuState<MaterialBase>::me.rows
								  + GpuState<MaterialAlpha>::me.rows
								  + GpuState<MaterialSolid>::me.rows
								  + GpuState<MaterialPoint>::me.rows
								  + GpuState<MaterialLine>::me.rows
								  + GpuState<MaterialLit>::me.rows
								  + GpuState<MaterialPbr>::me.rows
								  + GpuState<MaterialPhong>::me.rows
								  + GpuState<MaterialUser>::me.rows;
			const uint32_t lines = 1;
			const uvec2 size = uvec2(buffer.width, uint16_t(lines * height));

			if(texture.m_size != size)
				texture = { size, false, TextureFormat::RGBA32F, TEXTURE_POINT | TEXTURE_CLAMP };

			const bgfx::Memory* memory = bgfx::alloc(size.x * size.y * buffer.stride * sizeof(float));

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

#undef PAD
