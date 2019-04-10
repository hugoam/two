#include <mud/gfx.pbr.refl.h>
#include <mud/geom.refl.h>
#include <mud/gfx.pbr.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace mud;

void mud_TonemapMode__to_string(void* val, string& str) { str = g_enu[type<mud::TonemapMode>().m_id]->name(uint32_t((*static_cast<mud::TonemapMode*>(val)))); }
void mud_TonemapMode__to_value(const string& str, void* val) { (*static_cast<mud::TonemapMode*>(val)) = mud::TonemapMode(g_enu[type<mud::TonemapMode>().m_id]->value(str.c_str())); }
void mud_BCS__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::BCS(  ); }
void mud_BCS__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::BCS((*static_cast<mud::BCS*>(other))); }
void mud_CSMShadow__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CSMShadow(  ); }
void mud_CSMShadow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CSMShadow((*static_cast<mud::CSMShadow*>(other))); }
void mud_CubeCamera__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CubeCamera(  ); }
void mud_CubeCamera__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::CubeCamera( *static_cast<mud::Scene*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<uint32_t*>(args[3]) ); }
void mud_CubeCamera_render(void* object, span<void*> args, void*& result) { (*static_cast<mud::Render*>(result)) = (*static_cast<mud::CubeCamera*>(object)).render(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1]), *static_cast<mud::SignedAxis*>(args[2])); }
void mud_CubeTarget__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CubeTarget(  ); }
void mud_CubeTarget_create(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::CubeTarget*>(object)).create(*static_cast<uint32_t*>(args[0])); }
void mud_CubeTarget_side(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::CubeTarget*>(object)).side(*static_cast<size_t*>(args[0])); }
void mud_DofBlur__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::DofBlur(  ); }
void mud_DofBlur__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::DofBlur((*static_cast<mud::DofBlur*>(other))); }
void mud_DofParams__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::DofParams(  ); }
void mud_DofParams__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::DofParams((*static_cast<mud::DofParams*>(other))); }
void mud_Glow__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Glow(  ); }
void mud_Glow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Glow((*static_cast<mud::Glow*>(other))); }
void mud_LightShadow__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::LightShadow(  ); }
void mud_LightShadow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::LightShadow((*static_cast<mud::LightShadow*>(other))); }
void* mud_ReflectionProbe__get_node(void* object) { return &(*static_cast<mud::ReflectionProbe*>(object)).m_node; }
void mud_Tonemap__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Tonemap(  ); }
void mud_Tonemap__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Tonemap((*static_cast<mud::Tonemap*>(other))); }
void mud_CSMSlice__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CSMSlice(  ); }
void mud_CSMSlice__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CSMSlice((*static_cast<mud::CSMSlice*>(other))); }
void mud_begin_pbr_render_0(span<void*> args, void*& result) { UNUSED(result);  mud::begin_pbr_render(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_gi_probes_1(span<void*> args, void*& result) { UNUSED(result);  mud::pass_gi_probes(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_shadowmaps_2(span<void*> args, void*& result) { UNUSED(result);  mud::pass_shadowmaps(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_shadow_3(span<void*> args, void*& result) { UNUSED(result);  mud::pass_shadow(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_opaque_4(span<void*> args, void*& result) { UNUSED(result);  mud::pass_opaque(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_alpha_5(span<void*> args, void*& result) { UNUSED(result);  mud::pass_alpha(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_geometry_6(span<void*> args, void*& result) { UNUSED(result);  mud::pass_geometry(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_lights_7(span<void*> args, void*& result) { UNUSED(result);  mud::pass_lights(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_voxel_gi_8(span<void*> args, void*& result) { UNUSED(result);  mud::pass_voxel_gi(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_lightmap_9(span<void*> args, void*& result) { UNUSED(result);  mud::pass_lightmap(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_begin_post_10(span<void*> args, void*& result) { UNUSED(result);  mud::pass_begin_post(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_post_auto_11(span<void*> args, void*& result) { UNUSED(result);  mud::pass_post_auto(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_post_effects_12(span<void*> args, void*& result) { UNUSED(result);  mud::pass_post_effects(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1]), *static_cast<mud::DofBlur*>(args[2]), *static_cast<mud::Glow*>(args[3]), *static_cast<mud::Tonemap*>(args[4]), *static_cast<mud::BCS*>(args[5])); }
void mud_render_pbr_forward_13(span<void*> args, void*& result) { UNUSED(result);  mud::render_pbr_forward(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_render_pbr_deferred_14(span<void*> args, void*& result) { UNUSED(result);  mud::render_pbr_deferred(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_render_shadow_15(span<void*> args, void*& result) { UNUSED(result);  mud::render_shadow(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_render_voxel_16(span<void*> args, void*& result) { UNUSED(result);  mud::render_voxel(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_render_lightmap_17(span<void*> args, void*& result) { UNUSED(result);  mud::render_lightmap(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_render_reflection_18(span<void*> args, void*& result) { UNUSED(result);  mud::render_reflection(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pipeline_pbr_19(span<void*> args, void*& result) { UNUSED(result);  mud::pipeline_pbr(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Renderer*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_gfx_setup_pipeline_pbr_20(span<void*> args, void*& result) { UNUSED(result);  mud::gfx::setup_pipeline_pbr(*static_cast<mud::GfxSystem*>(args[0])); }
void mud_pass_shadowmaps_21(span<void*> args, void*& result) { UNUSED(result);  mud::pass_shadowmaps(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_shadow_22(span<void*> args, void*& result) { UNUSED(result);  mud::pass_shadow(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_gfx_gi_probe_23(span<void*> args, void*& result) { result = &mud::gfx::gi_probe(*static_cast<mud::Gnode*>(args[0]), *static_cast<uint16_t*>(args[1]), *static_cast<mud::vec3*>(args[2])); }
void mud_gfx_lightmap_24(span<void*> args, void*& result) { result = &mud::gfx::lightmap(*static_cast<mud::Gnode*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<float*>(args[2]), *static_cast<stl::string*>(args[3])); }
void mud_pass_dofblur_25(span<void*> args, void*& result) { UNUSED(result);  mud::pass_dofblur(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1]), *static_cast<mud::DofBlur*>(args[2])); }
void mud_pass_glow_26(span<void*> args, void*& result) { UNUSED(result);  mud::pass_glow(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1]), *static_cast<mud::Glow*>(args[2])); }
void mud_pass_tonemap_27(span<void*> args, void*& result) { UNUSED(result);  mud::pass_tonemap(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1]), *static_cast<mud::Tonemap*>(args[2]), *static_cast<mud::BCS*>(args[3])); }

namespace mud
{
	void mud_gfx_pbr_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::TonemapMode>();
		static Meta meta = { t, &namspc({ "mud" }), "TonemapMode", sizeof(mud::TonemapMode), TypeClass::Enum };
		static cstring ids[] = { "Linear", "Reinhardt", "Filmic", "ACES", "Cineon", "Uncharted2" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static mud::TonemapMode vars[] = { mud::TonemapMode::Linear, mud::TonemapMode::Reinhardt, mud::TonemapMode::Filmic, mud::TonemapMode::ACES, mud::TonemapMode::Cineon, mud::TonemapMode::Uncharted2};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_TonemapMode__to_string,
		                           mud_TonemapMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// mud::BCS
	{
		Type& t = type<mud::BCS>();
		static Meta meta = { t, &namspc({ "mud" }), "BCS", sizeof(mud::BCS), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static float brightness_default = 1.0f;
		static float contrast_default = 1.0f;
		static float saturation_default = 1.0f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_BCS__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_BCS__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::BCS, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(mud::BCS, m_brightness), type<float>(), "brightness", &brightness_default, Member::Value, nullptr },
			{ t, offsetof(mud::BCS, m_contrast), type<float>(), "contrast", &contrast_default, Member::Value, nullptr },
			{ t, offsetof(mud::BCS, m_saturation), type<float>(), "saturation", &saturation_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::CSMShadow
	{
		Type& t = type<mud::CSMShadow>();
		static Meta meta = { t, &namspc({ "mud" }), "CSMShadow", sizeof(mud::CSMShadow), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CSMShadow__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CSMShadow__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::CubeCamera
	{
		Type& t = type<mud::CubeCamera>();
		static Meta meta = { t, &namspc({ "mud" }), "CubeCamera", sizeof(mud::CubeCamera), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CubeCamera__construct_0, {} },
			{ t, mud_CubeCamera__construct_1, { { "scene", type<mud::Scene>(),  }, { "near", type<float>(),  }, { "far", type<float>(),  }, { "size", type<uint32_t>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::CubeCamera, m_cubemap), type<mud::CubeTarget>(), "cubemap", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::CubeCamera, m_size), type<mud::uvec2>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "render", Address(), mud_CubeCamera_render, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  }, { "axis", type<mud::SignedAxis>(),  } }, { &type<mud::Render>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// mud::CubeTarget
	{
		Type& t = type<mud::CubeTarget>();
		static Meta meta = { t, &namspc({ "mud" }), "CubeTarget", sizeof(mud::CubeTarget), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CubeTarget__construct_0, {} }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::CubeTarget, m_cubemap), type<mud::Texture>(), "cubemap", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::CubeTarget, m_depth), type<mud::Texture>(), "depth", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::CubeTarget, m_size), type<uint32_t>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "create", Address(), mud_CubeTarget_create, { { "size", type<uint32_t>(),  } }, g_qvoid },
			{ t, "side", Address(), mud_CubeTarget_side, { { "i", type<size_t>(),  } }, { &type<mud::FrameBuffer>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// mud::DofBlur
	{
		Type& t = type<mud::DofBlur>();
		static Meta meta = { t, &namspc({ "mud" }), "DofBlur", sizeof(mud::DofBlur), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static float max_coc_radius_default = 8.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_DofBlur__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_DofBlur__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::DofBlur, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(mud::DofBlur, m_far), type<mud::DofParams>(), "far", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::DofBlur, m_near), type<mud::DofParams>(), "near", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::DofBlur, m_max_coc_radius), type<float>(), "max_coc_radius", &max_coc_radius_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::DofParams
	{
		Type& t = type<mud::DofParams>();
		static Meta meta = { t, &namspc({ "mud" }), "DofParams", sizeof(mud::DofParams), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_DofParams__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_DofParams__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::DofParams, m_distance), type<float>(), "distance", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::DofParams, m_transition), type<float>(), "transition", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::DofParams, m_radius), type<float>(), "radius", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::GIProbe
	{
		Type& t = type<mud::GIProbe>();
		static Meta meta = { t, &namspc({ "mud" }), "GIProbe", sizeof(mud::GIProbe), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Glow
	{
		Type& t = type<mud::Glow>();
		static Meta meta = { t, &namspc({ "mud" }), "Glow", sizeof(mud::Glow), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static mud::vec4 levels_1_4_default = {1.f,0.f,0.f,0.f};
		static float intensity_default = 0.4f;
		static float bloom_default = 0.0f;
		static float bleed_threshold_default = 1.0f;
		static float bleed_scale_default = 2.0f;
		static bool bicubic_filter_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Glow__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Glow__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Glow, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(mud::Glow, m_levels_1_4), type<mud::vec4>(), "levels_1_4", &levels_1_4_default, Member::Value, nullptr },
			{ t, offsetof(mud::Glow, m_levels_5_8), type<mud::vec4>(), "levels_5_8", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Glow, m_intensity), type<float>(), "intensity", &intensity_default, Member::Value, nullptr },
			{ t, offsetof(mud::Glow, m_bloom), type<float>(), "bloom", &bloom_default, Member::Value, nullptr },
			{ t, offsetof(mud::Glow, m_bleed_threshold), type<float>(), "bleed_threshold", &bleed_threshold_default, Member::Value, nullptr },
			{ t, offsetof(mud::Glow, m_bleed_scale), type<float>(), "bleed_scale", &bleed_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::Glow, m_bicubic_filter), type<bool>(), "bicubic_filter", &bicubic_filter_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::LightShadow
	{
		Type& t = type<mud::LightShadow>();
		static Meta meta = { t, &namspc({ "mud" }), "LightShadow", sizeof(mud::LightShadow), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_LightShadow__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_LightShadow__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Lightmap
	{
		Type& t = type<mud::Lightmap>();
		static Meta meta = { t, &namspc({ "mud" }), "Lightmap", sizeof(mud::Lightmap), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::LightmapAtlas
	{
		Type& t = type<mud::LightmapAtlas>();
		static Meta meta = { t, &namspc({ "mud" }), "LightmapAtlas", sizeof(mud::LightmapAtlas), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::LightmapItem
	{
		Type& t = type<mud::LightmapItem>();
		static Meta meta = { t, &namspc({ "mud" }), "LightmapItem", sizeof(mud::LightmapItem), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::ReflectionProbe
	{
		Type& t = type<mud::ReflectionProbe>();
		static Meta meta = { t, &namspc({ "mud" }), "ReflectionProbe", sizeof(mud::ReflectionProbe), TypeClass::Object };
		// bases
		// defaults
		static bool visible_default = true;
		static float intensity_default = 1.f;
		static bool shadows_default = false;
		static bool dirty_default = true;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Node3>(), "node", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_ReflectionProbe__get_node },
			{ t, offsetof(mud::ReflectionProbe, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(mud::ReflectionProbe, m_intensity), type<float>(), "intensity", &intensity_default, Member::Value, nullptr },
			{ t, offsetof(mud::ReflectionProbe, m_extents), type<mud::vec3>(), "extents", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ReflectionProbe, m_shadows), type<bool>(), "shadows", &shadows_default, Member::Value, nullptr },
			{ t, offsetof(mud::ReflectionProbe, m_dirty), type<bool>(), "dirty", &dirty_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Tonemap
	{
		Type& t = type<mud::Tonemap>();
		static Meta meta = { t, &namspc({ "mud" }), "Tonemap", sizeof(mud::Tonemap), TypeClass::Struct };
		// bases
		// defaults
		static mud::TonemapMode mode_default = mud::TonemapMode::Linear;
		static bool enabled_default = false;
		static float exposure_default = 1.0f;
		static float white_point_default = 1.0f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Tonemap__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Tonemap__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Tonemap, m_mode), type<mud::TonemapMode>(), "mode", &mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::Tonemap, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(mud::Tonemap, m_exposure), type<float>(), "exposure", &exposure_default, Member::Value, nullptr },
			{ t, offsetof(mud::Tonemap, m_white_point), type<float>(), "white_point", &white_point_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::BlockBlur
	{
		Type& t = type<mud::BlockBlur>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockBlur", sizeof(mud::BlockBlur), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockBlur, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockDofBlur
	{
		Type& t = type<mud::BlockDofBlur>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockDofBlur", sizeof(mud::BlockDofBlur), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockDofBlur, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockGIBake
	{
		Type& t = type<mud::BlockGIBake>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockGIBake", sizeof(mud::BlockGIBake), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockGIBake, mud::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockGITrace
	{
		Type& t = type<mud::BlockGITrace>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockGITrace", sizeof(mud::BlockGITrace), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockGITrace, mud::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockGeometry
	{
		Type& t = type<mud::BlockGeometry>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockGeometry", sizeof(mud::BlockGeometry), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockGeometry, mud::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockGlow
	{
		Type& t = type<mud::BlockGlow>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockGlow", sizeof(mud::BlockGlow), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockGlow, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockLight
	{
		Type& t = type<mud::BlockLight>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockLight", sizeof(mud::BlockLight), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockLight, mud::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockLightmap
	{
		Type& t = type<mud::BlockLightmap>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockLightmap", sizeof(mud::BlockLightmap), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockLightmap, mud::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockRadiance
	{
		Type& t = type<mud::BlockRadiance>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockRadiance", sizeof(mud::BlockRadiance), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockRadiance, mud::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockReflection
	{
		Type& t = type<mud::BlockReflection>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockReflection", sizeof(mud::BlockReflection), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockReflection, mud::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockShadow
	{
		Type& t = type<mud::BlockShadow>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockShadow", sizeof(mud::BlockShadow), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockShadow, mud::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockTonemap
	{
		Type& t = type<mud::BlockTonemap>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockTonemap", sizeof(mud::BlockTonemap), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockTonemap, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::CSMSlice
	{
		Type& t = type<mud::CSMSlice>();
		static Meta meta = { t, &namspc({ "mud" }), "CSMSlice", sizeof(mud::CSMSlice), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::LightShadow>(), &type<mud::FrustumSlice>() };
		static size_t bases_offsets[] = { base_offset<mud::CSMSlice, mud::LightShadow>(), base_offset<mud::CSMSlice, mud::FrustumSlice>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CSMSlice__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CSMSlice__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::BCS>());
		m.m_types.push_back(&type<mud::CSMShadow>());
		m.m_types.push_back(&type<mud::CubeCamera>());
		m.m_types.push_back(&type<mud::CubeTarget>());
		m.m_types.push_back(&type<mud::DofBlur>());
		m.m_types.push_back(&type<mud::DofParams>());
		m.m_types.push_back(&type<mud::GIProbe>());
		m.m_types.push_back(&type<mud::Glow>());
		m.m_types.push_back(&type<mud::LightShadow>());
		m.m_types.push_back(&type<mud::Lightmap>());
		m.m_types.push_back(&type<mud::LightmapAtlas>());
		m.m_types.push_back(&type<mud::LightmapItem>());
		m.m_types.push_back(&type<mud::ReflectionProbe>());
		m.m_types.push_back(&type<mud::Tonemap>());
		m.m_types.push_back(&type<mud::TonemapMode>());
		m.m_types.push_back(&type<mud::BlockBlur>());
		m.m_types.push_back(&type<mud::BlockDofBlur>());
		m.m_types.push_back(&type<mud::BlockTonemap>());
		m.m_types.push_back(&type<mud::BlockGIBake>());
		m.m_types.push_back(&type<mud::BlockGITrace>());
		m.m_types.push_back(&type<mud::BlockGeometry>());
		m.m_types.push_back(&type<mud::BlockGlow>());
		m.m_types.push_back(&type<mud::BlockLight>());
		m.m_types.push_back(&type<mud::BlockLightmap>());
		m.m_types.push_back(&type<mud::BlockRadiance>());
		m.m_types.push_back(&type<mud::BlockReflection>());
		m.m_types.push_back(&type<mud::BlockShadow>());
		m.m_types.push_back(&type<mud::CSMSlice>());
		{
			static Function f = { &namspc({ "mud" }), "begin_pbr_render", nullptr, mud_begin_pbr_render_0, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_gi_probes", nullptr, mud_pass_gi_probes_1, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_shadowmaps", nullptr, mud_pass_shadowmaps_2, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_shadow", nullptr, mud_pass_shadow_3, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_opaque", nullptr, mud_pass_opaque_4, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_alpha", nullptr, mud_pass_alpha_5, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_geometry", nullptr, mud_pass_geometry_6, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_lights", nullptr, mud_pass_lights_7, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_voxel_gi", nullptr, mud_pass_voxel_gi_8, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_lightmap", nullptr, mud_pass_lightmap_9, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_begin_post", nullptr, mud_pass_begin_post_10, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_post_auto", nullptr, mud_pass_post_auto_11, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_post_effects", nullptr, mud_pass_post_effects_12, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  }, { "dof", type<mud::DofBlur>(),  }, { "glow", type<mud::Glow>(),  }, { "tonemap", type<mud::Tonemap>(),  }, { "bcs", type<mud::BCS>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "render_pbr_forward", nullptr, mud_render_pbr_forward_13, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "render_pbr_deferred", nullptr, mud_render_pbr_deferred_14, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "render_shadow", nullptr, mud_render_shadow_15, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "render_voxel", nullptr, mud_render_voxel_16, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "render_lightmap", nullptr, mud_render_lightmap_17, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "render_reflection", nullptr, mud_render_reflection_18, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static bool deferred_default = false;
			static Function f = { &namspc({ "mud" }), "pipeline_pbr", nullptr, mud_pipeline_pbr_19, { { "gfx", type<mud::GfxSystem>(),  }, { "pipeline", type<mud::Renderer>(),  }, { "deferred", type<bool>(), Param::Default, &deferred_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "setup_pipeline_pbr", nullptr, mud_gfx_setup_pipeline_pbr_20, { { "gfx", type<mud::GfxSystem>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_shadowmaps", nullptr, mud_pass_shadowmaps_21, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_shadow", nullptr, mud_pass_shadow_22, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "gi_probe", nullptr, mud_gfx_gi_probe_23, { { "parent", type<mud::Gnode>(),  }, { "subdiv", type<uint16_t>(),  }, { "extents", type<mud::vec3>(),  } }, { &type<mud::GIProbe>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float density_default = 8.f;
			static stl::string save_path_default = "";
			static Function f = { &namspc({ "mud", "gfx" }), "lightmap", nullptr, mud_gfx_lightmap_24, { { "parent", type<mud::Gnode>(),  }, { "resolution", type<uint32_t>(),  }, { "density", type<float>(), Param::Default, &density_default }, { "save_path", type<stl::string>(), Param::Default, &save_path_default } }, { &type<mud::LightmapAtlas>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_dofblur", nullptr, mud_pass_dofblur_25, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  }, { "blur", type<mud::DofBlur>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_glow", nullptr, mud_pass_glow_26, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  }, { "glow", type<mud::Glow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_tonemap", nullptr, mud_pass_tonemap_27, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  }, { "tonemap", type<mud::Tonemap>(),  }, { "bcs", type<mud::BCS>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_gfx_pbr::mud_gfx_pbr()
		: Module("mud::gfx-pbr", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m() })
	{
		// setup reflection meta data
		mud_gfx_pbr_meta(*this);
	}
}

#ifdef MUD_GFX_PBR_MODULE
extern "C"
Module& getModule()
{
	return mud_gfx_pbr::m();
}
#endif
