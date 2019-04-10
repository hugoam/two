//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <type/Type.h>
#include <type/Indexer.h>
#include <math/Vec.hpp>
#include <gfx/Types.h>
#include <gfx/Material.h>
#include <gfx/Texture.h>
#include <gfx/Skeleton.h>
#include <gfx/Program.h>
#include <gfx/Asset.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Renderer.h>
#include <gfx/Pipeline.h>
#include <gfx/GfxSystem.h>
#include <gfx/Gpu/Material.hpp>
//#include <gfx-pbr/VoxelGI.h>
//#include <gfx-pbr/Lightmap.h>
#endif

#include <cstring>
#include <cstdio>

namespace mud
{
	bool is_valid(Texture* texture) { return texture != nullptr && texture->valid(); };

	template struct MaterialParam<Colour>;
	template struct MaterialParam<float>;
	template struct MaterialParam<vec4>;

	GpuState<MaterialBase> GpuState<MaterialBase>::me;
	GpuState<MaterialAlpha> GpuState<MaterialAlpha>::me;
	GpuState<MaterialSolid> GpuState<MaterialSolid>::me;
	GpuState<MaterialPoint> GpuState<MaterialPoint>::me;
	GpuState<MaterialLine> GpuState<MaterialLine>::me;
	GpuState<MaterialLit> GpuState<MaterialLit>::me;
	GpuState<MaterialPbr> GpuState<MaterialPbr>::me;
	GpuState<MaterialPhong> GpuState<MaterialPhong>::me;
	GpuState<MaterialUser> GpuState<MaterialUser>::me;
	GpuState<Material> GpuState<Material>::me;

	void blend_state(BlendMode blend_mode, uint64_t& bgfx_state)
	{
		if(blend_mode == BlendMode::None)
			;
		else if(blend_mode == BlendMode::Mix)
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

	struct MaterialBlockBase
	{
		MaterialBlockBase() {}
		MaterialBlockBase(GfxSystem& gfx)
			: s_skeleton(bgfx::createUniform("s_skeleton", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
			UNUSED(gfx);
#if !MATERIALS_BUFFER
			GpuState<MaterialBase>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t skeleton = uint32_t(TextureSampler::Skeleton);
			bgfx::setViewUniform(pass.m_index, s_skeleton, &skeleton);
		}

		void upload(bgfx::Encoder& encoder, const MaterialBase& block) const
		{
			UNUSED(encoder); UNUSED(block);
#if !MATERIALS_BUFFER
			GpuState<MaterialBase>::me.upload(encoder, block);
#endif
		}

		bgfx::UniformHandle s_skeleton;
	};

	struct MaterialBlockAlpha
	{
		MaterialBlockAlpha() {}
		MaterialBlockAlpha(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_alpha(bgfx::createUniform("s_alpha", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialAlpha>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t alpha = uint32_t(TextureSampler::Alpha);
			bgfx::setViewUniform(pass.m_index, s_alpha, &alpha);
		}

		void upload(bgfx::Encoder& encoder, const MaterialAlpha& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialAlpha>::me.upload(encoder, block);
#endif
			encoder.setTexture(uint8_t(TextureSampler::Alpha), is_valid(block.m_alpha.m_texture) ? *block.m_alpha.m_texture : *m_white_tex);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_alpha;
	};

	struct MaterialBlockSolid
	{
		MaterialBlockSolid() {}
		MaterialBlockSolid(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_color(bgfx::createUniform("s_color", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialSolid>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t color = uint32_t(TextureSampler::Color);
			bgfx::setViewUniform(pass.m_index, s_color, &color);
		}

		void upload(bgfx::Encoder& encoder, const MaterialSolid& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialSolid>::me.upload(encoder, block);
#endif

			encoder.setTexture(uint8_t(TextureSampler::Color), block.m_colour.m_texture ? *block.m_colour.m_texture : *m_white_tex);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_color;
	};

	struct MaterialBlockPoint
	{
		MaterialBlockPoint() {}
		MaterialBlockPoint(GfxSystem& gfx)
		{
			UNUSED(gfx);
#if !MATERIALS_BUFFER
			GpuState<MaterialPoint>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			UNUSED(pass);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPoint& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPoint>::me.upload(encoder, block);
#endif
		}
	};

	struct MaterialBlockLine
	{
		MaterialBlockLine() {}
		MaterialBlockLine(GfxSystem& gfx)
		{
			UNUSED(gfx);
#if !MATERIALS_BUFFER
			GpuState<MaterialLine>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			UNUSED(pass);
		}

		void upload(bgfx::Encoder& encoder, const MaterialLine& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialLine>::me.upload(encoder, block);
#endif
		}
	};

	struct MaterialBlockFresnel
	{
		MaterialBlockFresnel() {}
		MaterialBlockFresnel(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_fresnel(bgfx::createUniform("s_fresnel", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			//GpuState<MaterialFresnel>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint8_t color = int8_t(TextureSampler::Color);
			bgfx::setViewUniform(pass.m_index, s_fresnel, &color);
		}

		void upload(bgfx::Encoder& encoder, const MaterialFresnel& block) const
		{
#if !MATERIALS_BUFFER
			//GpuState<MaterialFresnel>::me.upload(encoder, block);
#endif

			encoder.setTexture(uint8_t(TextureSampler::Color), block.m_value.m_texture ? *block.m_value.m_texture : *m_white_tex);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_fresnel;
	};

	struct MaterialBlockUser
	{
		MaterialBlockUser() {}
		MaterialBlockUser(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_user0(bgfx::createUniform("s_user0", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user1(bgfx::createUniform("s_user1", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user2(bgfx::createUniform("s_user2", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user3(bgfx::createUniform("s_user3", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user4(bgfx::createUniform("s_user4", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user5(bgfx::createUniform("s_user5", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialUser>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t user0 = uint32_t(TextureSampler::User0);
			uint32_t user1 = uint32_t(TextureSampler::User1);
			uint32_t user2 = uint32_t(TextureSampler::User2);
			uint32_t user3 = uint32_t(TextureSampler::User3);
			uint32_t user4 = uint32_t(TextureSampler::User4);
			uint32_t user5 = uint32_t(TextureSampler::User5);

			bgfx::setViewUniform(pass.m_index, s_user0, &user0);
			bgfx::setViewUniform(pass.m_index, s_user1, &user1);
			bgfx::setViewUniform(pass.m_index, s_user2, &user2);
			bgfx::setViewUniform(pass.m_index, s_user3, &user3);
			bgfx::setViewUniform(pass.m_index, s_user4, &user4);
			bgfx::setViewUniform(pass.m_index, s_user5, &user5);
		}

		void upload(bgfx::Encoder& encoder, const MaterialUser& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialUser>::me.upload(encoder, block);
#endif

			if(is_valid(block.m_tex0)) encoder.setTexture(uint8_t(TextureSampler::User0), *block.m_tex0);
			if(is_valid(block.m_tex1)) encoder.setTexture(uint8_t(TextureSampler::User1), *block.m_tex1);
			if(is_valid(block.m_tex2)) encoder.setTexture(uint8_t(TextureSampler::User2), *block.m_tex2);
			if(is_valid(block.m_tex3)) encoder.setTexture(uint8_t(TextureSampler::User3), *block.m_tex3);
			if(is_valid(block.m_tex4)) encoder.setTexture(uint8_t(TextureSampler::User4), *block.m_tex4);
			if(is_valid(block.m_tex5)) encoder.setTexture(uint8_t(TextureSampler::User5), *block.m_tex5);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_user0;
		bgfx::UniformHandle s_user1;
		bgfx::UniformHandle s_user2;
		bgfx::UniformHandle s_user3;
		bgfx::UniformHandle s_user4;
		bgfx::UniformHandle s_user5;
	};
	
	struct MaterialBlockLit
	{
		MaterialBlockLit() {}
		MaterialBlockLit(GfxSystem& gfx)
			: m_black_tex (&gfx.default_texture(TextureHint::Black))
			, s_emissive(bgfx::createUniform("s_emissive", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_normal(bgfx::createUniform("s_normal", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_occlusion(bgfx::createUniform("s_ambient_occlusion", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_displace(bgfx::createUniform("s_displace", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			//, s_lightmap(bgfx::createUniform("s_lightmap", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialLit>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t normal    = uint32_t(TextureSampler::Normal);
			uint32_t emissive  = uint32_t(TextureSampler::Emissive);
			uint32_t ao        = uint32_t(TextureSampler::AO);
			uint32_t displace  = uint32_t(TextureSampler::Displace);

			bgfx::setViewUniform(pass.m_index, s_normal, &normal);
			bgfx::setViewUniform(pass.m_index, s_emissive, &emissive);
			bgfx::setViewUniform(pass.m_index, s_occlusion, &ao);
			bgfx::setViewUniform(pass.m_index, s_displace, &displace);
		}

		void upload(bgfx::Encoder& encoder, const MaterialLit& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialLit>::me.upload(encoder, block);
#endif

			if(is_valid(block.m_normal.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Normal), *block.m_normal.m_texture);

			if(is_valid(block.m_emissive.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Emissive), *block.m_emissive.m_texture);
			else if(block.m_emissive.m_value.a > 0.f)
				encoder.setTexture(uint8_t(TextureSampler::Emissive), *m_black_tex);

			if(is_valid(block.m_occlusion.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::AO), *block.m_occlusion.m_texture);

			if(is_valid(block.m_displace.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Displace), *block.m_displace.m_texture);
		}

		Texture* m_black_tex;

		bgfx::UniformHandle s_emissive;
		bgfx::UniformHandle s_normal;
		bgfx::UniformHandle s_occlusion;
		//bgfx::UniformHandle s_lightmap;
		bgfx::UniformHandle s_displace;
	};

	struct MaterialBlockPbr
	{
		MaterialBlockPbr() {}
		MaterialBlockPbr(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, m_black_tex (&gfx.default_texture(TextureHint::Black))
			, m_normal_tex(&gfx.default_texture(TextureHint::Normal))
			, s_albedo(bgfx::createUniform("s_albedo", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_metallic (bgfx::createUniform("s_metallic", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_roughness(bgfx::createUniform("s_roughness", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_depth(bgfx::createUniform("s_depth", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			//, s_lightmap(bgfx::createUniform("s_lightmap", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPbr>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t albedo    = uint32_t(TextureSampler::Color);
			uint32_t metallic  = uint32_t(TextureSampler::Metallic);
			uint32_t roughness = uint32_t(TextureSampler::Roughness);
			//uint32_t depth     = uint32_t(TextureSampler::Depth);

			bgfx::setViewUniform(pass.m_index, s_albedo, &albedo);
			bgfx::setViewUniform(pass.m_index, s_metallic, &metallic);
			bgfx::setViewUniform(pass.m_index, s_roughness, &roughness);
			//bgfx::setViewUniform(pass.m_index, s_depth, &depth);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPbr& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPbr>::me.upload(encoder, block);
#endif

			encoder.setTexture(uint8_t(TextureSampler::Color), is_valid(block.m_albedo.m_texture) ? *block.m_albedo.m_texture : *m_white_tex);
			encoder.setTexture(uint8_t(TextureSampler::Metallic), is_valid(block.m_metallic.m_texture) ? *block.m_metallic.m_texture : *m_white_tex);
			encoder.setTexture(uint8_t(TextureSampler::Roughness), is_valid(block.m_roughness.m_texture) ? *block.m_roughness.m_texture : *m_white_tex);

			if(is_valid(block.m_depth.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Depth), *block.m_depth.m_texture);
		}

		Texture* m_white_tex;
		Texture* m_black_tex;
		Texture* m_normal_tex;

		bgfx::UniformHandle s_albedo;
		bgfx::UniformHandle s_metallic;
		bgfx::UniformHandle s_roughness;
		bgfx::UniformHandle s_depth;
		//bgfx::UniformHandle s_lightmap;
	};


	struct MaterialBlockPhong
	{
		MaterialBlockPhong() {}
		MaterialBlockPhong(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_diffuse(bgfx::createUniform("s_diffuse", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_specular(bgfx::createUniform("s_specular", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_shininess(bgfx::createUniform("s_shininess", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			//, s_lightmap(bgfx::createUniform("s_lightmap", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPhong>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t diffuse = uint32_t(TextureSampler::Diffuse);
			uint32_t specular = uint32_t(TextureSampler::Specular);
			uint32_t shininess = uint32_t(TextureSampler::Shininess);

			bgfx::setViewUniform(pass.m_index, s_diffuse, &diffuse);
			bgfx::setViewUniform(pass.m_index, s_specular, &specular);
			bgfx::setViewUniform(pass.m_index, s_shininess, &shininess);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPhong& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPhong>::me.upload(encoder, block);
#endif

			encoder.setTexture(uint8_t(TextureSampler::Diffuse), is_valid(block.m_diffuse.m_texture) ? *block.m_diffuse.m_texture : *m_white_tex);
			encoder.setTexture(uint8_t(TextureSampler::Specular), is_valid(block.m_specular.m_texture) ? *block.m_specular.m_texture : *m_white_tex);
			encoder.setTexture(uint8_t(TextureSampler::Shininess), is_valid(block.m_shininess.m_texture) ? *block.m_shininess.m_texture : *m_white_tex);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_diffuse;
		bgfx::UniformHandle s_specular;
		bgfx::UniformHandle s_shininess;
	};

	GfxSystem* Material::ms_gfx = nullptr;

	void load_material(Material& material, Program& program)
	{
		material.m_program = &program;
	}

	static uint16_t s_material_index = 0;

	static MaterialBlockBase s_base_material_block = {};
	static MaterialBlockAlpha s_alpha_material_block = {};
	static MaterialBlockSolid s_solid_material_block = {};
	static MaterialBlockLine s_line_material_block = {};
	static MaterialBlockPoint s_point_material_block = {};
	static MaterialBlockFresnel s_fresnel_material_block = {};
	static MaterialBlockLit s_lit_material_block = {};
	static MaterialBlockPbr s_pbr_material_block = {};
	static MaterialBlockPhong s_phong_material_block = {};
	static MaterialBlockUser s_user_material_block = {};

	ShaderBlock MaterialBase::s_block = ShaderBlock({ "VERTEX_COLOR", "DOUBLE_SIDED", "FLAT_SHADED" }, {});
	ShaderBlock MaterialAlpha::s_block = ShaderBlock({ "ALPHA_MAP", "ALPHA_TEST" }, {});
	ShaderBlock MaterialSolid::s_block = ShaderBlock();
	ShaderBlock MaterialLine::s_block = ShaderBlock({ "DASH" }, {});
	ShaderBlock MaterialPoint::s_block = ShaderBlock();
	ShaderBlock MaterialFresnel::s_block = ShaderBlock();
	ShaderBlock MaterialLit::s_block = ShaderBlock({ "NORMAL_MAP", "EMISSIVE", "AMBIENT_OCCLUSION", "LIGHTMAP", "DISPLACEMENT" }, {});
	ShaderBlock MaterialPbr::s_block = ShaderBlock({ "DEPTH_MAPPING", "DEEP_PARALLAX" }, { "DIFFUSE_MODE", "SPECULAR_MODE" }); // "REFRACTION", "ANISOTROPY", 
	ShaderBlock MaterialPhong::s_block = ShaderBlock({ "REFRACTION", "TOON" }, { "ENV_BLEND" });
	ShaderBlock MaterialUser::s_block = ShaderBlock();

	Material::Material(const string& name)
		: m_index(s_material_index++) // uint16_t(index(type<Material>(), Ref(this))))//
		, m_name(name)
	{
		m_pbr.m_diffuse_mode = PbrDiffuseMode::Lambert;

		static bool init_blocks = true;
		if(init_blocks)
		{
			s_base_material_block = { *ms_gfx };
			s_alpha_material_block = { *ms_gfx };
			s_solid_material_block = { *ms_gfx };
			s_line_material_block = { *ms_gfx };
			s_point_material_block = { *ms_gfx };
			s_fresnel_material_block = { *ms_gfx };
			s_lit_material_block = { *ms_gfx };
			s_pbr_material_block = { *ms_gfx };
			s_phong_material_block = { *ms_gfx };
			s_user_material_block = { *ms_gfx };

			init_blocks = false;
		}
	}

	ProgramVersion Material::program(const Program& program) const
	{
		ProgramVersion version = { program };

		version.set_option(MaterialBase::s_block.m_index, VERTEX_COLOR, m_base.m_shader_color == ShaderColor::Vertex);
		version.set_option(MaterialBase::s_block.m_index, DOUBLE_SIDED, m_base.m_cull_mode == CullMode::None);
		version.set_option(MaterialBase::s_block.m_index, FLAT_SHADED, m_base.m_flat_shaded);

		if(program.m_blocks[MaterialBlock::Alpha])
		{
			//version.set_option(MaterialAlpha::s_block.m_index, ALPHA, m_alpha.m_is_alpha);
			version.set_option(MaterialAlpha::s_block.m_index, ALPHA_TEST, m_alpha.m_alpha_test);
			version.set_option(MaterialAlpha::s_block.m_index, ALPHA_MAP, is_valid(m_alpha.m_alpha.m_texture));
		}

		if(program.m_blocks[MaterialBlock::Line])
		{
			version.set_option(MaterialLine::s_block.m_index, DASH, m_line.m_dashed);
		}

		if(program.m_blocks[MaterialBlock::Lit])
		{
			version.set_option(MaterialLit::s_block.m_index, NORMAL_MAP, is_valid(m_lit.m_normal.m_texture));
			version.set_option(MaterialLit::s_block.m_index, EMISSIVE, is_valid(m_lit.m_emissive.m_texture) || m_lit.m_emissive.m_value.a > 0.f);
			version.set_option(MaterialLit::s_block.m_index, AMBIENT_OCCLUSION, is_valid(m_lit.m_occlusion.m_texture));
			version.set_option(MaterialLit::s_block.m_index, DISPLACEMENT, is_valid(m_lit.m_displace.m_texture));
		}

		if(program.m_blocks[MaterialBlock::Pbr])
		{
			version.set_mode(MaterialPbr::s_block.m_index, DIFFUSE_MODE, uint8_t(m_pbr.m_diffuse_mode));
			version.set_mode(MaterialPbr::s_block.m_index, SPECULAR_MODE, uint8_t(m_pbr.m_specular_mode));

			//version.set_option(MaterialPbr::s_block.m_index, REFRACTION, m_pbr.m_refraction.m_value != 0.f);
			version.set_option(MaterialPbr::s_block.m_index, DEPTH_MAPPING, is_valid(m_pbr.m_depth.m_texture));
			version.set_option(MaterialPbr::s_block.m_index, DEEP_PARALLAX, m_pbr.m_deep_parallax);
		}

		if(program.m_blocks[MaterialBlock::Phong])
		{
			version.set_mode(MaterialPhong::s_block.m_index, ENV_BLEND, uint8_t(m_phong.m_env_blend));

			version.set_option(MaterialPhong::s_block.m_index, REFRACTION, m_phong.m_refraction.m_value != 0.f);
			version.set_option(MaterialPhong::s_block.m_index, TOON, m_phong.m_toon);
		}

		return version;
	}

	ProgramVersion Material::program(const Program& program, const Item& item, const ModelElem& elem) const
	{
		ProgramVersion version = this->program(program);
		
		const bool colours = (elem.m_mesh->m_vertex_format & VertexAttribute::Colour) != 0;

		version.set_option(MaterialBase::s_block.m_index, VERTEX_COLOR, colours && m_base.m_shader_color == ShaderColor::Vertex);

		//if(item.m_lightmaps.size() > 0)
		//{
		//	LightmapItem& binding = *item.m_lightmaps[elem.m_index];
		//	if(bgfx::isValid(binding.m_lightmap))
		//	{
		//		version.set_option(pbr.m_index, LIGHTMAP);
		//	}
		//}

		return version;
	}

	void Material::state(uint64_t& bgfx_state) const
	{
		// @todo cleanup culling flag responsibility, flipping etc
		if(m_base.m_cull_mode == CullMode::None
		|| m_base.m_cull_mode == CullMode::Front)
			bgfx_state &= ~BGFX_STATE_CULL_MASK;
		if(m_base.m_cull_mode == CullMode::Front)
			bgfx_state |= BGFX_STATE_CULL_CCW;

		if(m_base.m_depth_test == DepthTest::Disabled)
			bgfx_state &= ~BGFX_STATE_DEPTH_TEST_MASK;

		if(m_base.m_depth_draw == DepthDraw::Enabled)
			bgfx_state |= BGFX_STATE_WRITE_Z;
		if(m_base.m_depth_draw == DepthDraw::Disabled)
			bgfx_state &= ~BGFX_STATE_WRITE_Z;
	}

	void Material::submit(const Program& program, bgfx::Encoder& encoder, uint64_t& bgfx_state, const Skin* skin) const
	{
		this->state(bgfx_state);

		//if(program.m_blocks[MaterialBlock::Point])
			bgfx_state |= BGFX_STATE_POINT_SIZE(uint(m_point.m_point_size));

#if MATERIALS_BUFFER
		const BlockMaterial& block = *ms_gfx->m_renderer.block<BlockMaterial>();
		vec4 state = { 0.f, float(m_index), 0.f, 0.f };
		encoder.setUniform(block.u_state, &state);
		encoder.setUniform(block.u_state_vertex, &state);
		encoder.setTexture(uint8_t(TextureSampler::Materials), block.s_materials, block.m_materials_texture.texture, TEXTURE_POINT | TEXTURE_CLAMP);
#endif

		s_base_material_block.upload(encoder, m_base);
		if(program.m_blocks[MaterialBlock::Alpha])
			s_alpha_material_block.upload(encoder, m_alpha);
		if(program.m_blocks[MaterialBlock::Solid])
			s_solid_material_block.upload(encoder, m_solid);
		if(program.m_blocks[MaterialBlock::Point])
			s_point_material_block.upload(encoder, m_point);
		if(program.m_blocks[MaterialBlock::Line])
			s_line_material_block.upload(encoder, m_line);
		if(program.m_blocks[MaterialBlock::Lit])
			s_lit_material_block.upload(encoder, m_lit);
		if(program.m_blocks[MaterialBlock::Pbr])
			s_pbr_material_block.upload(encoder, m_pbr);
		if(program.m_blocks[MaterialBlock::Phong])
			s_phong_material_block.upload(encoder, m_phong);
		if(program.m_blocks[MaterialBlock::Fresnel])
			s_fresnel_material_block.upload(encoder, m_fresnel);
		if(program.m_blocks[MaterialBlock::User])
			s_user_material_block.upload(encoder, m_user);

		if(skin)
			encoder.setTexture(uint8_t(TextureSampler::Skeleton), skin->m_texture);

		if(m_submit)
			m_submit(encoder);
	}

	BlockMaterial::BlockMaterial(GfxSystem& gfx)
		: GfxBlock(gfx, *this)
	{}

	void BlockMaterial::init_block()
	{
		u_state = bgfx::createUniform("u_state", bgfx::UniformType::Vec4);
		u_state_vertex = bgfx::createUniform("u_state_vertex", bgfx::UniformType::Vec4);

		s_materials = bgfx::createUniform("s_materials", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View);
	}

	void BlockMaterial::begin_render(Render& render)
	{
		UNUSED(render);
#if MATERIALS_BUFFER
		const vector<Material*> materials = m_gfx.materials().m_vector;
		for(uint32_t i = 0; i < materials.size(); ++i)
			materials[i]->m_index = i;
		GpuState<Material>::me.pack(m_materials_texture, materials);
#endif
	}

	void BlockMaterial::submit(Render& render, const Pass& pass)
	{
		uint32_t materials = uint32_t(TextureSampler::Materials);
		bgfx::setViewUniform(pass.m_index, s_materials, &materials);

		s_base_material_block.prepare(pass);
		s_alpha_material_block.prepare(pass);
		s_solid_material_block.prepare(pass);
		s_point_material_block.prepare(pass);
		s_line_material_block.prepare(pass);
		s_fresnel_material_block.prepare(pass);
		s_lit_material_block.prepare(pass);
		s_pbr_material_block.prepare(pass);
		s_phong_material_block.prepare(pass);
		s_user_material_block.prepare(pass);
	}
}
