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
	bool is_valid(Texture* texture) { return texture != nullptr && bgfx::isValid(texture->m_texture); };

	template struct MaterialParam<Colour>;
	template struct MaterialParam<float>;

	GpuState<MaterialBase> GpuState<MaterialBase>::me;
	GpuState<MaterialAlpha> GpuState<MaterialAlpha>::me;
	GpuState<MaterialSolid> GpuState<MaterialSolid>::me;
	GpuState<MaterialPoint> GpuState<MaterialPoint>::me;
	GpuState<MaterialLine> GpuState<MaterialLine>::me;
	GpuState<MaterialPbr> GpuState<MaterialPbr>::me;
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

	struct BaseMaterialUniform
	{
		BaseMaterialUniform() {}
		BaseMaterialUniform(GfxSystem& gfx)
			: s_skeleton(bgfx::createUniform("s_skeleton", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
			UNUSED(gfx);
#if !MATERIALS_BUFFER
			GpuState<MaterialBase>::me.init();
#endif
		}

		void prepare(const Pass& render_pass) const
		{
			uint32_t skeleton = uint32_t(TextureSampler::Skeleton);
			bgfx::setViewUniform(render_pass.m_index, s_skeleton, &skeleton);
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

	struct AlphaMaterialUniform
	{
		AlphaMaterialUniform() {}
		AlphaMaterialUniform(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_alpha(bgfx::createUniform("s_alpha", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialAlpha>::me.init();
#endif
		}

		void prepare(const Pass& render_pass) const
		{
			uint32_t alpha = uint32_t(TextureSampler::Alpha);
			bgfx::setViewUniform(render_pass.m_index, s_alpha, &alpha);
		}

		void upload(bgfx::Encoder& encoder, const MaterialAlpha& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialAlpha>::me.upload(encoder, block);
#endif
			encoder.setTexture(uint8_t(TextureSampler::Alpha), is_valid(block.m_alpha.m_texture) ? block.m_alpha.m_texture->m_texture : m_white_tex->m_texture);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_alpha;
	};

	struct SolidMaterialUniform
	{
		SolidMaterialUniform() {}
		SolidMaterialUniform(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_color(bgfx::createUniform("s_color", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialSolid>::me.init();
#endif
		}

		void prepare(const Pass& render_pass) const
		{
			uint32_t color = uint32_t(TextureSampler::Color);
			bgfx::setViewUniform(render_pass.m_index, s_color, &color);
		}

		void upload(bgfx::Encoder& encoder, const MaterialSolid& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialSolid>::me.upload(encoder, block);
#endif

			encoder.setTexture(uint8_t(TextureSampler::Color), block.m_colour.m_texture ? block.m_colour.m_texture->m_texture : m_white_tex->m_texture);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_color;
	};

	struct PointMaterialUniform
	{
		PointMaterialUniform() {}
		PointMaterialUniform(GfxSystem& gfx)
		{
			UNUSED(gfx);
#if !MATERIALS_BUFFER
			GpuState<MaterialPoint>::me.init();
#endif
		}

		void prepare(const Pass& render_pass) const
		{
			UNUSED(render_pass);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPoint& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPoint>::me.upload(encoder, block);
#endif
		}
	};

	struct LineMaterialUniform
	{
		LineMaterialUniform() {}
		LineMaterialUniform(GfxSystem& gfx)
		{
			UNUSED(gfx);
#if !MATERIALS_BUFFER
			GpuState<MaterialLine>::me.init();
#endif
		}

		void prepare(const Pass& render_pass) const
		{
			UNUSED(render_pass);
		}

		void upload(bgfx::Encoder& encoder, const MaterialLine& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialLine>::me.upload(encoder, block);
#endif
		}
	};

	struct FresnelMaterialUniform
	{
		FresnelMaterialUniform() {}
		FresnelMaterialUniform(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_fresnel(bgfx::createUniform("s_fresnel", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			//GpuState<MaterialFresnel>::me.init();
#endif
		}

		void prepare(const Pass& render_pass) const
		{
			uint8_t color = int8_t(TextureSampler::Color);
			bgfx::setViewUniform(render_pass.m_index, s_fresnel, &color);
		}

		void upload(bgfx::Encoder& encoder, const MaterialFresnel& block) const
		{
#if !MATERIALS_BUFFER
			//GpuState<MaterialFresnel>::me.upload(encoder, block);
#endif

			encoder.setTexture(uint8_t(TextureSampler::Color), block.m_value.m_texture ? block.m_value.m_texture->m_texture : m_white_tex->m_texture);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_fresnel;
	};

	struct UserMaterialUniform
	{
		UserMaterialUniform() {}
		UserMaterialUniform(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_user0(bgfx::createUniform("s_user0", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user1(bgfx::createUniform("s_user1", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user2(bgfx::createUniform("s_user2", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user3(bgfx::createUniform("s_user3", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user4(bgfx::createUniform("s_user4", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_user5(bgfx::createUniform("s_user5", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			//GpuState<MaterialUser>::me.init();
#endif
		}

		void prepare(const Pass& render_pass) const
		{
			uint32_t user0 = uint32_t(TextureSampler::User0);
			uint32_t user1 = uint32_t(TextureSampler::User1);
			uint32_t user2 = uint32_t(TextureSampler::User2);
			uint32_t user3 = uint32_t(TextureSampler::User3);
			uint32_t user4 = uint32_t(TextureSampler::User4);
			uint32_t user5 = uint32_t(TextureSampler::User5);

			bgfx::setViewUniform(render_pass.m_index, s_user0, &user0);
			bgfx::setViewUniform(render_pass.m_index, s_user1, &user1);
			bgfx::setViewUniform(render_pass.m_index, s_user2, &user2);
			bgfx::setViewUniform(render_pass.m_index, s_user3, &user3);
			bgfx::setViewUniform(render_pass.m_index, s_user4, &user4);
			bgfx::setViewUniform(render_pass.m_index, s_user5, &user5);
		}

		void upload(bgfx::Encoder& encoder, const MaterialUser& block) const
		{
#if !MATERIALS_BUFFER
			//GpuState<MaterialUser>::me.upload(encoder, block);
#endif

			if(is_valid(block.m_attr0.m_texture)) encoder.setTexture(uint8_t(TextureSampler::User0), block.m_attr0.m_texture->m_texture);
			if(is_valid(block.m_attr1.m_texture)) encoder.setTexture(uint8_t(TextureSampler::User1), block.m_attr1.m_texture->m_texture);
			if(is_valid(block.m_attr2.m_texture)) encoder.setTexture(uint8_t(TextureSampler::User2), block.m_attr2.m_texture->m_texture);
			if(is_valid(block.m_attr3.m_texture)) encoder.setTexture(uint8_t(TextureSampler::User3), block.m_attr3.m_texture->m_texture);
			//if(is_valid(block.m_attr4.m_texture)) encoder.setTexture(uint8_t(TextureSampler::User4), block.m_attr4.m_texture->m_texture);
			//if(is_valid(block.m_attr5.m_texture)) encoder.setTexture(uint8_t(TextureSampler::User5), block.m_attr5.m_texture->m_texture);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_user0;
		bgfx::UniformHandle s_user1;
		bgfx::UniformHandle s_user2;
		bgfx::UniformHandle s_user3;
		bgfx::UniformHandle s_user4;
		bgfx::UniformHandle s_user5;
	};

	struct PbrMaterialUniform
	{
		PbrMaterialUniform() {}
		PbrMaterialUniform(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, m_black_tex (&gfx.default_texture(TextureHint::Black))
			, m_normal_tex(&gfx.default_texture(TextureHint::Normal))
			, s_albedo(bgfx::createUniform("s_albedo", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_metallic (bgfx::createUniform("s_metallic", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_roughness(bgfx::createUniform("s_roughness", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_emissive(bgfx::createUniform("s_emissive", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_normal(bgfx::createUniform("s_normal", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_depth(bgfx::createUniform("s_depth", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			, s_ambient_occlusion(bgfx::createUniform("s_ambient_occlusion", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
			//, s_lightmap(bgfx::createUniform("s_lightmap", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPbr>::me.init();
#endif
		}

		void prepare(const Pass& render_pass) const
		{
			uint32_t albedo    = uint32_t(TextureSampler::Color);
			uint32_t metallic  = uint32_t(TextureSampler::Metallic);
			uint32_t roughness = uint32_t(TextureSampler::Roughness);
			uint32_t normal    = uint32_t(TextureSampler::Normal);
			uint32_t emissive  = uint32_t(TextureSampler::Emissive);
			uint32_t depth     = uint32_t(TextureSampler::Depth);
			uint32_t ao        = uint32_t(TextureSampler::AO);

			bgfx::setViewUniform(render_pass.m_index, s_albedo, &albedo);
			bgfx::setViewUniform(render_pass.m_index, s_metallic, &metallic);
			bgfx::setViewUniform(render_pass.m_index, s_roughness, &roughness);
			bgfx::setViewUniform(render_pass.m_index, s_normal, &normal);
			bgfx::setViewUniform(render_pass.m_index, s_emissive, &emissive);
			bgfx::setViewUniform(render_pass.m_index, s_depth, &depth);
			bgfx::setViewUniform(render_pass.m_index, s_ambient_occlusion, &ao);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPbr& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPbr>::me.upload(encoder, block);
#endif

			encoder.setTexture(uint8_t(TextureSampler::Color), is_valid(block.m_albedo.m_texture) ? block.m_albedo.m_texture->m_texture : m_white_tex->m_texture);
			encoder.setTexture(uint8_t(TextureSampler::Metallic), is_valid(block.m_metallic.m_texture) ? block.m_metallic.m_texture->m_texture : m_white_tex->m_texture);
			encoder.setTexture(uint8_t(TextureSampler::Roughness), is_valid(block.m_roughness.m_texture) ? block.m_roughness.m_texture->m_texture : m_white_tex->m_texture);

			if(is_valid(block.m_normal.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Normal), block.m_normal.m_texture->m_texture);

			if(is_valid(block.m_emissive.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Emissive), block.m_emissive.m_texture->m_texture);
			else if(block.m_emissive.m_value.a > 0.f)
				encoder.setTexture(uint8_t(TextureSampler::Emissive), m_black_tex->m_texture);

			if(is_valid(block.m_depth.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Depth), block.m_depth.m_texture->m_texture);
			
			if(is_valid(block.m_ambient_occlusion.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::AO), block.m_ambient_occlusion.m_texture->m_texture);
		}

		Texture* m_white_tex;
		Texture* m_black_tex;
		Texture* m_normal_tex;

		bgfx::UniformHandle s_albedo;
		bgfx::UniformHandle s_metallic;
		bgfx::UniformHandle s_roughness;
		bgfx::UniformHandle s_emissive;
		bgfx::UniformHandle s_normal;
		bgfx::UniformHandle s_depth;
		bgfx::UniformHandle s_ambient_occlusion;
		//bgfx::UniformHandle s_lightmap;
	};

	struct BlockPbr : public GfxBlock
	{
		BlockPbr(GfxSystem& gfx);

		virtual void init_block() override {}

		virtual void begin_render(Render& render) override { UNUSED(render); }
		virtual void begin_pass(Render& render) override { UNUSED(render); }
	};

	GfxSystem* Material::ms_gfx_system = nullptr;

	void load_material(Material& material, Program& program)
	{
		material.m_program = &program;
	}

	//static uint16_t s_material_index = 0;

	static BaseMaterialUniform s_base_material_block = {};
	static AlphaMaterialUniform s_alpha_material_block = {};
	static SolidMaterialUniform s_solid_material_block = {};
	static LineMaterialUniform s_line_material_block = {};
	static PointMaterialUniform s_point_material_block = {};
	static FresnelMaterialUniform s_fresnel_material_block = {};
	static PbrMaterialUniform s_pbr_material_block = {};
	static UserMaterialUniform s_user_material_block = {};

	Material::Material(const string& name)
		: m_index(uint16_t(index(type<Material>(), Ref(this))))//++s_material_index)
		, m_name(name)
	{
		static bool init_blocks = true;
		if(init_blocks)
		{
			s_base_material_block = { *ms_gfx_system };
			s_alpha_material_block = { *ms_gfx_system };
			s_solid_material_block = { *ms_gfx_system };
			s_line_material_block = { *ms_gfx_system };
			s_point_material_block = { *ms_gfx_system };
			s_fresnel_material_block = { *ms_gfx_system };
			s_pbr_material_block = { *ms_gfx_system };
			s_user_material_block = { *ms_gfx_system };

			init_blocks = false;
		}
	}

	ShaderVersion Material::shader_version(const Program& program) const
	{
		static GfxBlock& pbr = pbr_block(*ms_gfx_system);
		static GfxBlock& mat = *ms_gfx_system->m_pipeline->block<BlockMaterial>();

		ShaderVersion version = { &program };

		version.set_option(mat.m_index, DOUBLE_SIDED, m_base.m_cull_mode == CullMode::None);

		//version.set_option(mat.m_index, ALPHA, m_alpha.m_is_alpha);
		version.set_option(mat.m_index, ALPHA_TEST, m_alpha.m_alpha_test);

		if(program.m_blocks[MaterialBlock::Alpha])
		{
			version.set_option(mat.m_index, ALPHA_MAP, is_valid(m_alpha.m_alpha.m_texture));
		}

		if(program.m_blocks[MaterialBlock::Line])
		{
			version.set_option(mat.m_index, DASH, m_line.m_dashed);
		}

		if(program.m_blocks[MaterialBlock::Pbr])
		{
			version.set_mode(pbr.m_index, DIFFUSE_MODE, uint8_t(PbrDiffuseMode::Lambert));
			//version.set_mode(pbr.m_index, DIFFUSE_MODE, uint8_t(m_pbr.m_diffuse_mode));
			version.set_mode(pbr.m_index, SPECULAR_MODE, uint8_t(m_pbr.m_specular_mode));

			version.set_option(pbr.m_index, NORMAL_MAP, is_valid(m_pbr.m_normal.m_texture));
			version.set_option(pbr.m_index, EMISSIVE, is_valid(m_pbr.m_emissive.m_texture) || m_pbr.m_emissive.m_value.a > 0.f);
			version.set_option(pbr.m_index, AMBIENT_OCCLUSION, is_valid(m_pbr.m_ambient_occlusion.m_texture));
			version.set_option(pbr.m_index, DEPTH_MAPPING, is_valid(m_pbr.m_depth.m_texture));
			version.set_option(pbr.m_index, DEEP_PARALLAX, m_pbr.m_deep_parallax);
		}

		return version;
	}

#if 0
	ShaderVersion Material::shader_version(const Program& program, const Item& item, const ModelItem& model_item) const
	{
		ShaderVersion version = this->shader_version(program);
		UNUSED(item); UNUSED(model_item);
		BlockPbr& pbr = pbr_block(*ms_gfx_system);

		if(item.m_lightmaps.size() > 0)
		{
			LightmapItem& binding = *item.m_lightmaps[model_item.m_index];
			if(bgfx::isValid(binding.m_lightmap))
			{
				version.set_option(pbr.m_index, LIGHTMAP);
			}
		}
		return version;
	}
#endif

	void Material::state(uint64_t& bgfx_state) const
	{
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
		const BlockMaterial& block = *ms_gfx_system->m_pipeline->block<BlockMaterial>();
		vec4 state = { 0.f, float(m_index), 0.f, 0.f };
		encoder.setUniform(block.u_state, &state);
		encoder.setTexture(uint8_t(TextureSampler::Materials), block.m_materials_texture);
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
		if(program.m_blocks[MaterialBlock::Pbr])
			s_pbr_material_block.upload(encoder, m_pbr);
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
	{
		static cstring options[] = { "DOUBLE_SIDED", "ALPHA_MAP", "ALPHA_TEST", "DASH" }; // @todo move dash to correct place
		m_shader_block->m_options = options;
	}

	void BlockMaterial::init_block()
	{
		u_state = bgfx::createUniform("u_state", bgfx::UniformType::Vec4);

		s_materials = bgfx::createUniform("s_materials", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View);
	}

	void BlockMaterial::begin_render(Render& render)
	{
		UNUSED(render);
#if MATERIALS_BUFFER
		GpuState<Material>::me.pack(m_materials_texture, m_gfx.materials().m_vector);
#endif
	}

	void BlockMaterial::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockMaterial::submit(Render& render, const Pass& render_pass)
	{
		uint32_t materials = uint32_t(TextureSampler::Materials);
		bgfx::setViewUniform(render_pass.m_index, s_materials, &materials);

		s_base_material_block.prepare(render_pass);
		s_alpha_material_block.prepare(render_pass);
		s_solid_material_block.prepare(render_pass);
		s_point_material_block.prepare(render_pass);
		s_line_material_block.prepare(render_pass);
		s_fresnel_material_block.prepare(render_pass);
		s_pbr_material_block.prepare(render_pass);
		s_user_material_block.prepare(render_pass);
	}

	BlockPbr::BlockPbr(GfxSystem& gfx)
		: GfxBlock(gfx, *this)
	{
		static cstring options[] = { "NORMAL_MAP", "EMISSIVE", "ANISOTROPY", "AMBIENT_OCCLUSION", "DEPTH_MAPPING", "DEEP_PARALLAX", "LIGHTMAP" };
		static cstring modes[] = { "DIFFUSE_MODE", "SPECULAR_MODE" };
		m_shader_block->m_options = options;
		m_shader_block->m_modes = modes;
	}

	template <> Type& type<mud::BlockPbr>() { static Type ty("BlockPbr"); return ty; }

	GfxBlock& pbr_block(GfxSystem& gfx)
	{
		static BlockPbr pbr = { gfx };
		return pbr;
	}
}
