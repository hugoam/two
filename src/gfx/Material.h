//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/table.h>
#include <stl/function.h>
#include <math/Vec.h>
#include <math/Colour.h>
#include <geom/Primitive.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Texture.h>
#include <gfx/Renderer.h>

namespace bgfx
{
	struct Encoder;
}

namespace mud
{
	export_ enum class refl_ BlendMode : unsigned int
	{
		None,
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
		Back,
		Count
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

	export_ enum class refl_ ShaderColor : unsigned int
	{
		Shader,
		Vertex,
		Face
	};

	export_ enum MaterialShaderOption : unsigned int
	{
		DOUBLE_SIDED,
		ALPHA_MAP,
		ALPHA_TEST,
		DASH,
	};

	export_ struct refl_ MUD_GFX_EXPORT MaterialBase
	{
		attr_ BlendMode m_blend_mode = BlendMode::None;
		attr_ CullMode m_cull_mode = CullMode::Back;
		attr_ DepthDraw m_depth_draw = DepthDraw::Enabled;
		attr_ DepthTest m_depth_test = DepthTest::Enabled;

		attr_ gpu_ vec2 m_uv0_scale = { 1.f, 1.f };
		attr_ gpu_ vec2 m_uv0_offset = { 0.f, 0.f };
		attr_ gpu_ vec2 m_uv1_scale = { 1.f, 1.f };
		attr_ gpu_ vec2 m_uv1_offset = { 0.f, 0.f };

		attr_ ShaderColor m_shader_color = ShaderColor::Shader;

		attr_ bool m_screen_filter = false;
		attr_ float m_anisotropy;

		uint32_t m_geometry_filter = UINT32_MAX;

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

	export_ template <class T>
	struct refl_ struct_ MaterialParam
	{
		MaterialParam() {}
		MaterialParam(T value, Texture* texture = nullptr, TextureChannel channel = TextureChannel::All) : m_value(value), m_texture(texture), m_channel(channel) {}
		//MaterialParam(Texture& texture, TextureChannel channel = TextureChannel::All) : m_value(T()), m_texture(texture), m_channel(channel) {}
		MaterialParam& operator=(const T& value) { m_value = value; return *this; }
		MaterialParam& operator=(Texture* texture) { m_texture = texture; return *this; }
		attr_ gpu_ T m_value = {};
		attr_ Texture* m_texture = nullptr;
		attr_ TextureChannel m_channel = TextureChannel::All;
	};

	export_ extern template struct refl_ MaterialParam<Colour>;
	export_ extern template struct refl_ MaterialParam<float>;
	export_ extern template struct refl_ MaterialParam<vec4>;

	export_ struct refl_ MUD_GFX_EXPORT MaterialUser
	{
		attr_ MaterialParam<vec4> m_attr0 = { vec4(0.f), nullptr };
		attr_ MaterialParam<vec4> m_attr1 = { vec4(0.f), nullptr };
		attr_ MaterialParam<vec4> m_attr2 = { vec4(0.f), nullptr };
		attr_ MaterialParam<vec4> m_attr3 = { vec4(0.f), nullptr };
	};

	export_ struct refl_ MUD_GFX_EXPORT MaterialAlpha
	{
		attr_ gpu_ MaterialParam<float> m_alpha = { 1.f, nullptr };
		attr_ gpu_ float m_alpha_scissor = 0.5f;

		attr_ bool m_alpha_test = false;
		attr_ bool m_is_alpha = false;
	};

	export_ struct refl_ MUD_GFX_EXPORT MaterialSolid
	{
		attr_ MaterialParam<Colour> m_colour = { Colour::White, nullptr };
	};

	enum LineShaderOption : unsigned int
	{
		//DASH,
	};

	export_ struct refl_ MUD_GFX_EXPORT MaterialPoint
	{
		attr_ gpu_ float m_point_size = 1.f;
		attr_ gpu_ bool m_project = false;
	};

	export_ struct refl_ MUD_GFX_EXPORT MaterialLine
	{
		attr_ gpu_ float m_line_width = 1.f;

		attr_ bool m_dashed = false;
		attr_ gpu_ float m_dash_scale = 1.f;
		attr_ gpu_ float m_dash_size = 1.f;
		attr_ gpu_ float m_dash_gap = 1.f;
		// resolution
	};

	export_ struct refl_ MUD_GFX_EXPORT MaterialFresnel
	{
		attr_ gpu_ MaterialParam<Colour> m_value = { Colour::White, nullptr };

		attr_ gpu_ float m_fresnel_scale = 1.f;
		attr_ gpu_ float m_fresnel_bias = 0.01f;
		attr_ gpu_ float m_fresnel_power = 5.f;
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

	enum PbrShaderOption : unsigned int
	{
		NORMAL_MAP,
		EMISSIVE,
		ANISOTROPY,
		AMBIENT_OCCLUSION,
		DEPTH_MAPPING,
		DEEP_PARALLAX,
		LIGHTMAP
	};

	enum PbrShaderMode : unsigned int
	{
		DIFFUSE_MODE,
		SPECULAR_MODE,
	};

	export_ class refl_ MUD_GFX_EXPORT BlockPbr : public GfxBlock
	{
	public:
		BlockPbr(GfxSystem& gfx);

		virtual void init_block() override {}

		virtual void begin_render(Render& render) override { UNUSED(render); }
	};

	export_ struct refl_ MUD_GFX_EXPORT MaterialPbr
	{
		constr_ MaterialPbr() {}
		constr_ MaterialPbr(const Colour& albedo, float metallic = 0.f, float roughness = 1.f) : m_albedo(albedo, nullptr), m_metallic(metallic, nullptr, TextureChannel::Red), m_roughness(roughness, nullptr, TextureChannel::Red) {}

		MaterialPbr& operator=(const MaterialPbr&) = default; // @kludge because clang-modules bug doesn't have copy-assign with member arrays ?

		// basic
		attr_ gpu_ MaterialParam<Colour> m_albedo = { Colour::White, nullptr };
		attr_ gpu_ float m_specular = 0.5f;
		attr_ gpu_ MaterialParam<float> m_metallic = { 0.f, nullptr, TextureChannel::Red };
		attr_ gpu_ MaterialParam<float> m_roughness = { 1.f, nullptr, TextureChannel::Red };
		attr_ gpu_ MaterialParam<float> m_normal = { 1.f, nullptr };
		attr_ gpu_ MaterialParam<Colour> m_emissive = { Colour::None, nullptr };
		attr_ gpu_ float m_emissive_energy = 0.f;

		// advanced
		attr_ gpu_ MaterialParam<float> m_rim;
		attr_ gpu_ float m_rim_tint;
		attr_ gpu_ MaterialParam<float> m_clearcoat;
		attr_ gpu_ float m_clearcoat_gloss;
		attr_ gpu_ MaterialParam<float> m_anisotropy;
		attr_ gpu_ MaterialParam<float> m_subsurface;
		attr_ gpu_ MaterialParam<float> m_refraction;
		attr_ gpu_ MaterialParam<float> m_depth = { -0.02f, nullptr };
		attr_ gpu_ MaterialParam<float> m_ambient_occlusion;
		attr_ gpu_ MaterialParam<Colour> m_transmission;

		attr_ bool m_deep_parallax = false;
		attr_ bool m_scene_environment = true;

		attr_ PbrDiffuseMode m_diffuse_mode = PbrDiffuseMode::Burley;
		attr_ PbrSpecularMode m_specular_mode = PbrSpecularMode::SchlickGGX;

		table<MaterialFlag, bool> m_flags;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockMaterial : public GfxBlock
	{
	public:
		BlockMaterial(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void submit(Render& render, const Pass& render_pass);

		bgfx::UniformHandle u_state = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle s_materials = BGFX_INVALID_HANDLE;
		Texture m_materials_texture = {};
	};

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

		attr_ MaterialBase m_base;
		attr_ MaterialAlpha m_alpha;
		attr_ MaterialSolid m_solid;
		attr_ MaterialPoint m_point;
		attr_ MaterialLine m_line;
		attr_ MaterialPbr m_pbr;
		attr_ MaterialFresnel m_fresnel;
		attr_ MaterialUser m_user;

		function<void(bgfx::Encoder&)> m_pass;
		function<void(bgfx::Encoder&)> m_submit;

		void state(uint64_t& bgfx_state) const;
		ShaderVersion shader_version(const Program& program) const;
		//ShaderVersion shader_version(const Program& program, const Item& item, const ModelItem& model_item) const;

		void submit(const Program& program, bgfx::Encoder& encoder, uint64_t& bgfx_state, const Skin* skin = nullptr) const;

		static GfxSystem* ms_gfx_system;
	};
}
