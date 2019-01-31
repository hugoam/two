//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <math/Vec.h>
#include <math/Colour.h>
#include <geom/Primitive.h>
#endif
#include <gfx/Forward.h>

namespace bgfx
{
	struct Encoder;
}

namespace mud
{
	export_ enum class refl_ BlendMode : unsigned int
	{
		Mix,
		Add,
		Sub,
		Mul,
		Normal,
		Alpha
	};

	void blend_state(BlendMode blend_mode, uint64_t& bgfx_state);

	export_ enum class refl_ CullMode : unsigned int
	{
		None,
		Front,
		Back
	};

	export_ enum class refl_ DepthDraw : unsigned int
	{
		Enabled,
		Disabled
	};

	export_ enum class refl_ DepthTest : unsigned int
	{
		Enabled,
		Disabled
	};

	export_ enum class refl_ MaterialFlag : unsigned int
	{
		TriplanarUV1,
		TriplanarUV2,
		Count
	};

	export_ struct refl_ MUD_GFX_EXPORT BaseMaterialBlock
	{
		attr_ BlendMode m_blend_mode = BlendMode::Mix;
		attr_ CullMode m_cull_mode = CullMode::Back;
		attr_ DepthDraw m_depth_draw_mode = DepthDraw::Enabled;
		attr_ DepthTest m_depth_test = DepthTest::Enabled;

		attr_ vec2 m_uv0_scale = { 1.f, 1.f };
		attr_ vec2 m_uv0_offset = { 0.f, 0.f };
		attr_ vec2 m_uv1_scale = { 1.f, 1.f };
		attr_ vec2 m_uv1_offset = { 0.f, 0.f };

		attr_ bool m_is_alpha = false;
		attr_ bool m_screen_filter = false;

		uint m_geometry_filter = (1 << OUTLINE) | (1 << PLAIN);

#if 0
		BillboardMode m_billboard_mode;
#endif		
	};

	export_ enum class refl_ TextureChannel : unsigned int
	{
		Red,
		Green,
		Blue,
		Alpha,
		All
	};

	export_ template <class T_Param>
	struct refl_ struct_ MaterialParam
	{
		MaterialParam() {}
		MaterialParam(T_Param value, Texture* texture = nullptr, TextureChannel channel = TextureChannel::All) : m_value(value), m_texture(texture), m_channel(channel) {}
		attr_ T_Param m_value = {};
		attr_ Texture* m_texture = nullptr;
		attr_ TextureChannel m_channel = TextureChannel::All;
	};

	export_ extern template struct refl_ MaterialParam<Colour>;
	export_ extern template struct refl_ MaterialParam<float>;

	export_ struct refl_ MUD_GFX_EXPORT UnshadedMaterialBlock
	{
		attr_ bool m_enabled = false;

		attr_ MaterialParam<Colour> m_colour = { Colour::White, nullptr };
	};

	export_ struct refl_ MUD_GFX_EXPORT FresnelMaterialBlock
	{
		attr_ bool m_enabled = false;

		attr_ MaterialParam<Colour> m_value = { Colour::White, nullptr };

		attr_ float m_fresnel_scale = 1.f;
		attr_ float m_fresnel_bias = 0.01f;
		attr_ float m_fresnel_power = 5.f;
	};

	export_ enum class refl_ PbrDiffuseMode : unsigned int
	{
		Lambert,
		LambertHalf,
		OrenNayar,
		Burley,
		Toon,
	};

	export_ enum class refl_ PbrSpecularMode : unsigned int
	{
		SchlickGGX,
		Blinn,
		Phong,
		Toon,
		Disabled,
	};

	export_ enum PbrShaderOption : unsigned int
	{
		NORMAL_MAP,
		EMISSIVE,
		ANISOTROPY,
		AMBIENT_OCCLUSION,
		DEPTH_MAPPING,
		DEEP_PARALLAX,
		LIGHTMAP
	};

	export_ struct refl_ MUD_GFX_EXPORT PbrMaterialBlock
	{
		constr_ PbrMaterialBlock() {}
		constr_ PbrMaterialBlock(const Colour& albedo, float metallic = 0.f, float roughness = 1.f) : m_enabled(true), m_albedo(albedo, nullptr), m_metallic(metallic, nullptr, TextureChannel::Red), m_roughness(roughness, nullptr, TextureChannel::Red) {}

		PbrMaterialBlock& operator=(const PbrMaterialBlock&) = default; // @kludge because clang-modules bug doesn't have copy-assign with member arrays ?

		attr_ bool m_enabled = false;

		// basic
		attr_ MaterialParam<Colour> m_albedo = { Colour::White, nullptr };
		attr_ float m_specular = 0.5f;
		attr_ MaterialParam<float> m_metallic = { 0.f, nullptr, TextureChannel::Red };
		attr_ MaterialParam<float> m_roughness = { 1.f, nullptr, TextureChannel::Red };
		attr_ MaterialParam<Colour> m_emissive = { Colour::None, nullptr };
		attr_ float m_emissive_energy = 0.f;
		attr_ MaterialParam<float> m_normal = { 1.f, nullptr };

		// advanced
		attr_ MaterialParam<float> m_rim;
		attr_ float m_rim_tint;
		attr_ MaterialParam<float> m_clearcoat;
		attr_ float m_clearcoat_gloss;
		attr_ MaterialParam<float> m_anisotropy;
		attr_ MaterialParam<float> m_subsurface;
		attr_ MaterialParam<Colour> m_transmission;
		attr_ MaterialParam<float> m_refraction;
		attr_ MaterialParam<float> m_ambient_occlusion;
		attr_ MaterialParam<float> m_depth = { -0.02f, nullptr };

		attr_ bool m_deep_parallax = false;

		attr_ PbrDiffuseMode m_diffuse_mode = PbrDiffuseMode::Burley;
		attr_ PbrSpecularMode m_specular_mode = PbrSpecularMode::SchlickGGX;

		bool m_flags[size_t(MaterialFlag::Count)];
	};

	export_ GfxBlock& pbr_block(GfxSystem& gfx_system);

	export_ MUD_GFX_EXPORT void load_material(Material& material, Program& program);

	export_ class refl_ MUD_GFX_EXPORT Material
	{
	public:
		Material() {}
		Material(const string& name);

		Material& operator=(const Material&) = default; // @kludge because clang-modules bug doesn't have copy-assign with member arrays ?

		attr_ uint16_t m_index = 0;
		attr_ string m_name;
		attr_ bool m_builtin = false;
		attr_ Program* m_program = nullptr;

		attr_ BaseMaterialBlock m_base_block;
		attr_ UnshadedMaterialBlock m_unshaded_block;
		attr_ PbrMaterialBlock m_pbr_block;
		attr_ FresnelMaterialBlock m_fresnel_block;

		void state(uint64_t& bgfx_state) const;
		ShaderVersion shader_version(const Program& program) const;
		ShaderVersion shader_version(const Program& program, const Item& item, const ModelItem& model_item) const;

		void submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const Skin* skin = nullptr) const;

		static GfxSystem* ms_gfx_system;
	};
}
