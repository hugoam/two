//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Strung.h>
#include <math/Vec.h>
#include <math/Colour.h>
#include <gfx/Generated/Forward.h>
#include <gfx/Renderer.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

namespace mud
{
	enum class _refl_ BlendMode : unsigned int
	{
		Mix,
		Add,
		Sub,
		Mul,
		Normal,
		Alpha
	};

	void blend_state(BlendMode blend_mode, uint64_t& bgfx_state);

	enum class _refl_ CullMode : unsigned int
	{
		None,
		Front,
		Back
	};

	enum class _refl_ DepthDraw : unsigned int
	{
		Enabled,
		Disabled
	};

	enum class _refl_ DepthTest : unsigned int
	{
		Enabled,
		Disabled
	};

	enum class _refl_ MaterialFlag : unsigned int
	{
		TriplanarUV1,
		TriplanarUV2,
		Count
	};

	struct _refl_ MUD_GFX_EXPORT BaseMaterialBlock
	{
		_attr_ _mut_ BlendMode m_blend_mode = BlendMode::Mix;
		_attr_ _mut_ CullMode m_cull_mode = CullMode::Back;
		_attr_ _mut_ DepthDraw m_depth_draw_mode = DepthDraw::Enabled;
		_attr_ _mut_ DepthTest m_depth_test = DepthTest::Enabled;

		_attr_ _mut_ vec2 m_uv1_scale = { 1.f, 1.f };
		_attr_ _mut_ vec2 m_uv1_offset = { 0.f, 0.f };
		_attr_ _mut_ vec2 m_uv2_scale = { 1.f, 1.f };
		_attr_ _mut_ vec2 m_uv2_offset = { 0.f, 0.f };

		_attr_ _mut_ bool m_is_alpha = false;
		_attr_ _mut_ bool m_screen_filter = false;

#if 0
		BillboardMode m_billboard_mode;
#endif		
	};

	enum class _refl_ TextureChannel : unsigned int
	{
		Red,
		Green,
		Blue,
		Alpha,
		All
	};

	template <class T_Param>
	struct _refl_ _struct_ MaterialParam
	{
		MaterialParam() {}
		MaterialParam(T_Param value, Texture* texture = nullptr, TextureChannel channel = TextureChannel::All) : m_value(value), m_texture(texture), m_channel(channel) {}
		_attr_ _mut_ T_Param m_value = {};
		_attr_ _mut_ Texture* m_texture = nullptr;
		_attr_ _mut_ TextureChannel m_channel = TextureChannel::All;
	};

	template struct _refl_ _struct_ MUD_GFX_EXPORT MaterialParam<Colour>;
	template struct _refl_ _struct_ MUD_GFX_EXPORT MaterialParam<float>;

	struct _refl_ MUD_GFX_EXPORT UnshadedMaterialBlock
	{
		_attr_ _mut_ bool m_enabled = false;

		_attr_ _mut_ MaterialParam<Colour> m_colour = { Colour::White, nullptr };
	};

	enum class _refl_ PbrDiffuseMode : unsigned int
	{
		Lambert,
		LambertHalf,
		OrenNayar,
		Burley,
		Toon,
	};

	enum class _refl_ PbrSpecularMode : unsigned int
	{
		SchlickGGX,
		Blinn,
		Phong,
		Toon,
		Disabled,
	};

	enum PbrShaderOption : unsigned int
	{
		NORMAL_MAP,
		EMISSIVE,
		ANISOTROPY,
		AMBIENT_OCCLUSION,
		DEPTH_MAPPING,
		DEEP_PARALLAX
	};

	struct _refl_ MUD_GFX_EXPORT PbrMaterialBlock
	{
		_attr_ _mut_ bool m_enabled = false;

		// basic
		_attr_ _mut_ MaterialParam<Colour> m_albedo = { Colour::White, nullptr };
		_attr_ _mut_ float m_specular = 0.5f;
		_attr_ _mut_ MaterialParam<float> m_metallic = { 0.f, nullptr, TextureChannel::Red };
		_attr_ _mut_ MaterialParam<float> m_roughness = { 1.f, nullptr, TextureChannel::Red };
		_attr_ _mut_ MaterialParam<Colour> m_emissive = { Colour::Black, nullptr };
		_attr_ _mut_ float m_emissive_energy = 0.f;
		_attr_ _mut_ MaterialParam<float> m_normal = { 1.f, nullptr };

		// advanced
		_attr_ _mut_ MaterialParam<float> m_rim;
		_attr_ _mut_ float m_rim_tint;
		_attr_ _mut_ MaterialParam<float> m_clearcoat;
		_attr_ _mut_ float m_clearcoat_gloss;
		_attr_ _mut_ MaterialParam<float> m_anisotropy;
		_attr_ _mut_ MaterialParam<float> m_subsurface;
		_attr_ _mut_ MaterialParam<Colour> m_transmission;
		_attr_ _mut_ MaterialParam<float> m_refraction;
		_attr_ _mut_ MaterialParam<float> m_ambient_occlusion;
		_attr_ _mut_ MaterialParam<float> m_depth = { -0.02f, nullptr };

		_attr_ _mut_ bool m_deep_parallax = false;

		_attr_ _mut_ PbrDiffuseMode m_diffuse_mode = PbrDiffuseMode::Burley;
		_attr_ _mut_ PbrSpecularMode m_specular_mode = PbrSpecularMode::SchlickGGX;

		bool m_flags[size_t(MaterialFlag::Count)];
	};

	struct PbrBlock : public GfxBlock
	{
		PbrBlock(GfxSystem& gfx_system);

		virtual void init_gfx_block() final {}

		virtual void begin_gfx_block(Render& render) final { UNUSED(render); }
		virtual void submit_gfx_block(Render& render) final { UNUSED(render); }
	};

	PbrBlock& pbr_block(GfxSystem& gfx_system);

	class _refl_ MUD_GFX_EXPORT Material
	{
	public:
		Material() {}
		Material(cstring name, Program& program);
		Material(cstring name, cstring shader);

		_attr_ uint16_t m_index = 0;
		/*_attr_ _mut_*/ strung m_name;
		_attr_ Program* m_program = nullptr;

		_attr_ _mut_ BaseMaterialBlock m_base_block;
		_attr_ _mut_ UnshadedMaterialBlock m_unshaded_block;
		_attr_ _mut_ PbrMaterialBlock m_pbr_block;

		void submit(uint64_t& bgfx_state, const Skin* skin = nullptr) const;
		ShaderVersion shader_version() const;

		static GfxSystem* ms_gfx_system;
	};
}
