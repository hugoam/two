//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <type/Type.h>
#include <type/Indexer.h>
#include <infra/StringConvert.h>
#include <math/VecOps.h>
#include <gfx/Types.h>
#include <gfx/Material.h>
#include <gfx/Texture.h>
#include <gfx/Skeleton.h>
#include <gfx/Program.h>
#include <gfx/Asset.h>
#endif

namespace mud
{
	void blend_state(BlendMode blend_mode, uint64_t& bgfx_state)
	{
		if(blend_mode == BlendMode::Mix)
			bgfx_state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
		else if(blend_mode == BlendMode::Add)
			//bgfx_state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_ONE);
			bgfx_state |= BGFX_STATE_BLEND_ADD;
		else if(blend_mode == BlendMode::Sub)
			bgfx_state |= (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_ONE))
						 | BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_REVSUB);
		else if(blend_mode == BlendMode::Mul)
			bgfx_state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
		else if(blend_mode == BlendMode::Normal)
			bgfx_state |= BGFX_STATE_BLEND_NORMAL;
		else if(blend_mode == BlendMode::Alpha)
			bgfx_state |= BGFX_STATE_BLEND_ALPHA;
	}

	struct BaseMaterialUniform
	{
		BaseMaterialUniform() {}
		BaseMaterialUniform(GfxSystem& gfx_system)
			: u_uv1_scale_offset(bgfx::createUniform("u_material_params_0", bgfx::UniformType::Vec4))
			, u_uv2_scale_offset(bgfx::createUniform("u_material_params_1", bgfx::UniformType::Vec4))
			, s_skeleton(bgfx::createUniform("s_skeleton", bgfx::UniformType::Int1))
		{
			UNUSED(gfx_system);
		}

		void upload(bgfx::Encoder& encoder, const BaseMaterialBlock& data) const
		{
			encoder.setUniform(u_uv1_scale_offset, &data.m_uv1_scale.x);
			encoder.setUniform(u_uv2_scale_offset, &data.m_uv2_scale.x);
		}

		bgfx::UniformHandle u_uv1_scale_offset;
		bgfx::UniformHandle u_uv2_scale_offset;
		bgfx::UniformHandle s_skeleton;
	};

	struct UnshadedMaterialUniform
	{
		UnshadedMaterialUniform() {}
		UnshadedMaterialUniform(GfxSystem& gfx_system)
			: m_white_tex (&gfx_system.default_texture(TextureHint::White))
			, u_color(bgfx::createUniform("u_color", bgfx::UniformType::Vec4))
			, s_color (bgfx::createUniform("s_color", bgfx::UniformType::Int1))
		{}

		void upload(bgfx::Encoder& encoder, const UnshadedMaterialBlock& data) const
		{
			vec4 colour = to_vec4(data.m_colour.m_value);
			encoder.setUniform(u_color, &colour);

			encoder.setTexture(uint8_t(TextureSampler::Color), s_color, data.m_colour.m_texture ? data.m_colour.m_texture->m_texture : m_white_tex->m_texture);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle u_color;
		bgfx::UniformHandle s_color;
	};

	struct FresnelMaterialUniform
	{
		FresnelMaterialUniform() {}
		FresnelMaterialUniform(GfxSystem& gfx_system)
			: m_white_tex(&gfx_system.default_texture(TextureHint::White))
			, u_fresnel_params(bgfx::createUniform("u_fresnel_params", bgfx::UniformType::Vec4))
			, u_fresnel_value(bgfx::createUniform("u_fresnel_value", bgfx::UniformType::Vec4))
			, s_fresnel(bgfx::createUniform("s_fresnel", bgfx::UniformType::Int1))
		{}

		void upload(bgfx::Encoder& encoder, const FresnelMaterialBlock& data) const
		{
			vec4 value = to_vec4(data.m_value.m_value);
			vec4 params = { data.m_fresnel_bias, data.m_fresnel_scale, data.m_fresnel_power, 1.f };
			encoder.setUniform(u_fresnel_value, &value);
			encoder.setUniform(u_fresnel_params, &params);

			encoder.setTexture(uint8_t(TextureSampler::Color), s_fresnel, data.m_value.m_texture ? data.m_value.m_texture->m_texture : m_white_tex->m_texture);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle u_fresnel_params;
		bgfx::UniformHandle u_fresnel_value;
		bgfx::UniformHandle s_fresnel;
	};

	struct PbrMaterialUniform
	{
		PbrMaterialUniform() {}
		PbrMaterialUniform(GfxSystem& gfx_system)
			: m_white_tex(&gfx_system.default_texture(TextureHint::White))
			, m_black_tex (&gfx_system.default_texture(TextureHint::Black))
			, m_normal_tex(&gfx_system.default_texture(TextureHint::Normal))
			, u_albedo(bgfx::createUniform("u_albedo", bgfx::UniformType::Vec4))
			, u_pbr_params_0(bgfx::createUniform("u_pbr_params_0", bgfx::UniformType::Vec4))
			, u_pbr_params_1(bgfx::createUniform("u_pbr_params_1", bgfx::UniformType::Vec4))
			, u_pbr_channels_0(bgfx::createUniform("u_pbr_channels_0", bgfx::UniformType::Vec4))
			, u_emissive(bgfx::createUniform("u_emissive", bgfx::UniformType::Vec4))
			, s_albedo(bgfx::createUniform("s_albedo", bgfx::UniformType::Int1))
			, s_metallic (bgfx::createUniform("s_metallic", bgfx::UniformType::Int1))
			, s_roughness(bgfx::createUniform("s_roughness", bgfx::UniformType::Int1))
			, s_emissive(bgfx::createUniform("s_emissive", bgfx::UniformType::Int1))
			, s_normal(bgfx::createUniform("s_normal", bgfx::UniformType::Int1))
			, s_depth(bgfx::createUniform("s_depth", bgfx::UniformType::Int1))
			, s_ambient_occlusion(bgfx::createUniform("s_ambient_occlusion", bgfx::UniformType::Int1))
		{}

		void upload(bgfx::Encoder& encoder, const PbrMaterialBlock& block) const
		{
			vec4 albedo = to_vec4(block.m_albedo.m_value);
			encoder.setUniform(u_albedo, &albedo);

			vec4 spec_met_rough = { block.m_specular, block.m_metallic.m_value, block.m_roughness.m_value, block.m_normal.m_value };
			encoder.setUniform(u_pbr_params_0, &spec_met_rough);

			vec4 emissive = to_vec4(block.m_emissive.m_value);
			encoder.setUniform(u_emissive, &emissive);

			vec4 pbr_params_1 = { block.m_anisotropy.m_value, block.m_refraction.m_value, block.m_subsurface.m_value, block.m_depth.m_value };
			encoder.setUniform(u_pbr_params_1, &pbr_params_1);

			vec4 pbr_channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), 0.f, 0.f };
			encoder.setUniform(u_pbr_channels_0, &pbr_channels);

			encoder.setTexture(uint8_t(TextureSampler::Color), s_albedo, block.m_albedo.m_texture ? block.m_albedo.m_texture->m_texture : m_white_tex->m_texture);
			encoder.setTexture(uint8_t(TextureSampler::Metallic), s_metallic, block.m_metallic.m_texture ? block.m_metallic.m_texture->m_texture : m_white_tex->m_texture);
			encoder.setTexture(uint8_t(TextureSampler::Roughness), s_roughness, block.m_roughness.m_texture ? block.m_roughness.m_texture->m_texture : m_white_tex->m_texture);

			if(block.m_normal.m_texture)
				encoder.setTexture(uint8_t(TextureSampler::Normal), s_normal, block.m_normal.m_texture->m_texture);

			if(block.m_emissive.m_value.m_a > 0.f || block.m_emissive.m_texture)
				encoder.setTexture(uint8_t(TextureSampler::Emissive), s_emissive, block.m_emissive.m_texture ? block.m_emissive.m_texture->m_texture : m_black_tex->m_texture);

			if(block.m_depth.m_texture)
				encoder.setTexture(uint8_t(TextureSampler::Depth), s_depth, block.m_depth.m_texture->m_texture);
			
			if(block.m_ambient_occlusion.m_texture)
				encoder.setTexture(uint8_t(TextureSampler::AO), s_ambient_occlusion, block.m_ambient_occlusion.m_texture->m_texture);
		}

		Texture* m_white_tex;
		Texture* m_black_tex;
		Texture* m_normal_tex;

		bgfx::UniformHandle u_albedo;
		bgfx::UniformHandle u_pbr_params_0;
		bgfx::UniformHandle u_pbr_params_1;
		bgfx::UniformHandle u_pbr_channels_0;
		bgfx::UniformHandle u_emissive;

		bgfx::UniformHandle s_albedo;
		bgfx::UniformHandle s_metallic;
		bgfx::UniformHandle s_roughness;
		bgfx::UniformHandle s_emissive;
		bgfx::UniformHandle s_normal;
		bgfx::UniformHandle s_depth;
		bgfx::UniformHandle s_ambient_occlusion;
	};

	PbrBlock::PbrBlock(GfxSystem& gfx_system)
		: GfxBlock(gfx_system, *this)
	{
		static cstring options[6] = {
			"NORMAL_MAP",
			"EMISSIVE",
			"ANISOTROPY",
			"AMBIENT_OCCLUSION",
			"DEPTH_MAPPING",
			"DEEP_PARALLAX"
		};
		m_shader_block->m_options = { options, 6 };
	}

	template <> Type& type<mud::PbrBlock>() { static Type ty("PbrBlock"); return ty; }

	PbrBlock& pbr_block(GfxSystem& gfx_system)
	{
		static PbrBlock pbr = { gfx_system };
		return pbr;
	}

	//static TypedUniformBlock<BaseMaterialBlock> s_base_material_block = { "material" };
	//static TypedUniformBlock<UnshadedMaterialBlock> s_unshaded_material_block = { "unshaded" };
	//static TypedUniformBlock<PbrMaterialBlock> s_pbr_material_block = { "pbr" };

	GfxSystem* Material::ms_gfx_system = nullptr;

	void load_material(Material& material, Program& program)
	{
		material.m_program = &program;
	}

	//static uint16_t s_material_index = 0;

	static BaseMaterialUniform s_base_material_block = {};
	static UnshadedMaterialUniform s_unshaded_material_block = {};
	static FresnelMaterialUniform s_fresnel_material_block = {};
	static PbrMaterialUniform s_pbr_material_block = {};

	Material::Material(cstring name)
		: m_index(uint16_t(index(type<Material>(), Ref(this))))//++s_material_index)
		, m_name(name)
	{
		static bool init_blocks = true;
		if(init_blocks)
		{
			s_base_material_block = { *ms_gfx_system };
			s_unshaded_material_block = { *ms_gfx_system };
			s_fresnel_material_block = { *ms_gfx_system };
			s_pbr_material_block = { *ms_gfx_system };

			init_blocks = false;
		}
	}

	ShaderVersion Material::shader_version(const Program& program) const
	{
		PbrBlock& pbr = pbr_block(*ms_gfx_system);

		ShaderVersion version = { &program };
		if(m_pbr_block.m_enabled && m_pbr_block.m_normal.m_texture)
			version.set_option(pbr.m_index, NORMAL_MAP);
		if(m_pbr_block.m_enabled && (m_pbr_block.m_emissive.m_value.m_a > 0.f || m_pbr_block.m_emissive.m_texture))
			version.set_option(pbr.m_index, EMISSIVE);
		if(m_pbr_block.m_enabled && m_pbr_block.m_ambient_occlusion.m_texture)
			version.set_option(pbr.m_index, AMBIENT_OCCLUSION);
		if(m_pbr_block.m_enabled && m_pbr_block.m_depth.m_texture)
			version.set_option(pbr.m_index, DEPTH_MAPPING);
		if(m_pbr_block.m_enabled && m_pbr_block.m_deep_parallax)
			version.set_option(pbr.m_index, DEEP_PARALLAX);

		return version;
	}

	void Material::state(uint64_t& bgfx_state) const
	{
		if(m_base_block.m_cull_mode == CullMode::None)
			bgfx_state &= ~BGFX_STATE_CULL_MASK;

		if(m_base_block.m_depth_test == DepthTest::Disabled)
			bgfx_state &= ~BGFX_STATE_DEPTH_TEST_MASK;

		if(m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
			bgfx_state |= BGFX_STATE_WRITE_Z;
		if(m_base_block.m_depth_draw_mode == DepthDraw::Disabled)
			bgfx_state &= ~BGFX_STATE_WRITE_Z;
	}

	void Material::submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const Skin* skin) const
	{
		this->state(bgfx_state);

		s_base_material_block.upload(encoder, m_base_block);
		if(m_unshaded_block.m_enabled)
			s_unshaded_material_block.upload(encoder, m_unshaded_block);
		if(m_fresnel_block.m_enabled)
			s_fresnel_material_block.upload(encoder, m_fresnel_block);
		if(m_pbr_block.m_enabled)
			s_pbr_material_block.upload(encoder, m_pbr_block);

		if(skin)
			encoder.setTexture(uint8_t(TextureSampler::Skeleton), s_base_material_block.s_skeleton, skin->m_texture);
	}
}
