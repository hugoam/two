//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Strung.h>
#include <math/Vec.h>
#include <math/Colour.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Renderer.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

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
		attr_ mut_ BlendMode m_blend_mode = BlendMode::Mix;
		attr_ mut_ CullMode m_cull_mode = CullMode::Back;
		attr_ mut_ DepthDraw m_depth_draw_mode = DepthDraw::Enabled;
		attr_ mut_ DepthTest m_depth_test = DepthTest::Enabled;

		attr_ mut_ vec2 m_uv1_scale = { 1.f, 1.f };
		attr_ mut_ vec2 m_uv1_offset = { 0.f, 0.f };
		attr_ mut_ vec2 m_uv2_scale = { 1.f, 1.f };
		attr_ mut_ vec2 m_uv2_offset = { 0.f, 0.f };

		attr_ mut_ bool m_is_alpha = false;
		attr_ mut_ bool m_screen_filter = false;

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
		attr_ mut_ T_Param m_value = {};
		attr_ mut_ Texture* m_texture = nullptr;
		attr_ mut_ TextureChannel m_channel = TextureChannel::All;
	};

	export_ template struct refl_ struct_ MUD_GFX_EXPORT MaterialParam<Colour>;
	export_ template struct refl_ struct_ MUD_GFX_EXPORT MaterialParam<float>;

	export_ struct refl_ MUD_GFX_EXPORT UnshadedMaterialBlock
	{
		attr_ mut_ bool m_enabled = false;

		attr_ mut_ MaterialParam<Colour> m_colour = { Colour::White, nullptr };
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
		DEEP_PARALLAX
	};

	export_ struct refl_ MUD_GFX_EXPORT PbrMaterialBlock
	{
		PbrMaterialBlock& operator=(const PbrMaterialBlock&) = default; // @kludge because clang-modules bug doesn't have copy-assign with member arrays ?

		attr_ mut_ bool m_enabled = false;

		// basic
		attr_ mut_ MaterialParam<Colour> m_albedo = { Colour::White, nullptr };
		attr_ mut_ float m_specular = 0.5f;
		attr_ mut_ MaterialParam<float> m_metallic = { 0.f, nullptr, TextureChannel::Red };
		attr_ mut_ MaterialParam<float> m_roughness = { 1.f, nullptr, TextureChannel::Red };
		attr_ mut_ MaterialParam<Colour> m_emissive = { Colour::Black, nullptr };
		attr_ mut_ float m_emissive_energy = 0.f;
		attr_ mut_ MaterialParam<float> m_normal = { 1.f, nullptr };

		// advanced
		attr_ mut_ MaterialParam<float> m_rim;
		attr_ mut_ float m_rim_tint;
		attr_ mut_ MaterialParam<float> m_clearcoat;
		attr_ mut_ float m_clearcoat_gloss;
		attr_ mut_ MaterialParam<float> m_anisotropy;
		attr_ mut_ MaterialParam<float> m_subsurface;
		attr_ mut_ MaterialParam<Colour> m_transmission;
		attr_ mut_ MaterialParam<float> m_refraction;
		attr_ mut_ MaterialParam<float> m_ambient_occlusion;
		attr_ mut_ MaterialParam<float> m_depth = { -0.02f, nullptr };

		attr_ mut_ bool m_deep_parallax = false;

		attr_ mut_ PbrDiffuseMode m_diffuse_mode = PbrDiffuseMode::Burley;
		attr_ mut_ PbrSpecularMode m_specular_mode = PbrSpecularMode::SchlickGGX;

		bool m_flags[size_t(MaterialFlag::Count)];
	};

	export_ struct PbrBlock : public GfxBlock
	{
		PbrBlock(GfxSystem& gfx_system);

		virtual void init_gfx_block() final {}

		virtual void begin_gfx_block(Render& render) final { UNUSED(render); }
		virtual void submit_gfx_block(Render& render) final { UNUSED(render); }
	};

	export_ PbrBlock& pbr_block(GfxSystem& gfx_system);

	export_ MUD_GFX_EXPORT void load_material(Material& material, Program& program);

	export_ class refl_ MUD_GFX_EXPORT Material
	{
	public:
		Material() {}
		Material(cstring name);

		Material& operator=(const Material&) = default; // @kludge because clang-modules bug doesn't have copy-assign with member arrays ?

		attr_ uint16_t m_index = 0;
		/*attr_ mut_*/ string m_name;
		attr_ bool m_builtin = false;
		attr_ Program* m_program = nullptr;

		attr_ mut_ BaseMaterialBlock m_base_block;
		attr_ mut_ UnshadedMaterialBlock m_unshaded_block;
		attr_ mut_ PbrMaterialBlock m_pbr_block;

		void state(uint64_t& bgfx_state) const;
		void submit(uint64_t& bgfx_state, const Skin* skin = nullptr) const;
		ShaderVersion shader_version() const;

		static GfxSystem* ms_gfx_system;
	};
}
