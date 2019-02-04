#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#include <cstddef>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-pbr/Module.h>
#include <meta/gfx-pbr/Convert.h>
#endif

#include <gfx-pbr/Api.h>

using namespace mud;

void mud_TonemapMode__to_string(void* val, string& str) { str = g_enu[type<mud::TonemapMode>().m_id]->name(uint32_t((*static_cast<mud::TonemapMode*>(val)))); }
void mud_TonemapMode__to_value(const string& str, void* val) { (*static_cast<mud::TonemapMode*>(val)) = mud::TonemapMode(g_enu[type<mud::TonemapMode>().m_id]->value(str.c_str())); }
void mud_BCS__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::BCS*>(ref))) mud::BCS(  ); }
void mud_BCS__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::BCS*>(ref))) mud::BCS((*static_cast<mud::BCS*>(other))); }
void mud_DofBlur__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::DofBlur*>(ref))) mud::DofBlur(  ); }
void mud_DofBlur__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::DofBlur*>(ref))) mud::DofBlur((*static_cast<mud::DofBlur*>(other))); }
void mud_Glow__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Glow*>(ref))) mud::Glow(  ); }
void mud_Glow__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Glow*>(ref))) mud::Glow((*static_cast<mud::Glow*>(other))); }
void mud_LightShadow__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::LightShadow*>(ref))) mud::LightShadow(  ); }
void mud_LightShadow__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::LightShadow*>(ref))) mud::LightShadow((*static_cast<mud::LightShadow*>(other))); }
void* mud_ReflectionProbe__get_node(void* object) { return &(*static_cast<mud::ReflectionProbe*>(object)).m_node; }
void mud_Tonemap__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Tonemap*>(ref))) mud::Tonemap(  ); }
void mud_Tonemap__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Tonemap*>(ref))) mud::Tonemap((*static_cast<mud::Tonemap*>(other))); }
void mud_gfx_gi_probe_0(array<void*> args, void*& result) { result = &mud::gfx::gi_probe(*static_cast<mud::Gnode*>(args[0]), *static_cast<uint16_t*>(args[1]), *static_cast<mud::vec3*>(args[2])); }
void mud_gfx_lightmap_1(array<void*> args, void*& result) { result = &mud::gfx::lightmap(*static_cast<mud::Gnode*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<float*>(args[2]), *static_cast<string*>(args[3])); }

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
		static cstring ids[] = { "Linear", "Reinhardt", "Filmic", "ACES" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::TonemapMode vars[] = { mud::TonemapMode::Linear, mud::TonemapMode::Reinhardt, mud::TonemapMode::Filmic, mud::TonemapMode::ACES};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
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
	// mud::DofBlur
	{
		Type& t = type<mud::DofBlur>();
		static Meta meta = { t, &namspc({ "mud" }), "DofBlur", sizeof(mud::DofBlur), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static float far_distance_default = 10.f;
		static float far_transition_default = 5.f;
		static float far_radius_default = 5.f;
		static float near_distance_default = 2.f;
		static float near_transition_default = 1.f;
		static float near_radius_default = 5.f;
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
			{ t, offsetof(mud::DofBlur, m_far_distance), type<float>(), "far_distance", &far_distance_default, Member::Value, nullptr },
			{ t, offsetof(mud::DofBlur, m_far_transition), type<float>(), "far_transition", &far_transition_default, Member::Value, nullptr },
			{ t, offsetof(mud::DofBlur, m_far_radius), type<float>(), "far_radius", &far_radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::DofBlur, m_near_distance), type<float>(), "near_distance", &near_distance_default, Member::Value, nullptr },
			{ t, offsetof(mud::DofBlur, m_near_transition), type<float>(), "near_transition", &near_transition_default, Member::Value, nullptr },
			{ t, offsetof(mud::DofBlur, m_near_radius), type<float>(), "near_radius", &near_radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::DofBlur, m_max_coc_radius), type<float>(), "max_coc_radius", &max_coc_radius_default, Member::Value, nullptr }
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
		static mud::vec4 levels_5_8_default = Zero4;
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
			{ t, offsetof(mud::Glow, m_levels_5_8), type<mud::vec4>(), "levels_5_8", &levels_5_8_default, Member::Value, nullptr },
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
		static mud::vec3 extents_default = Zero3;
		static bool shadows_default = false;
		static bool dirty_default = true;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Node3>(), "node", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_ReflectionProbe__get_node },
			{ t, offsetof(mud::ReflectionProbe, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(mud::ReflectionProbe, m_intensity), type<float>(), "intensity", &intensity_default, Member::Value, nullptr },
			{ t, offsetof(mud::ReflectionProbe, m_extents), type<mud::vec3>(), "extents", &extents_default, Member::Value, nullptr },
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
		m.m_types.push_back(&type<mud::BCS>());
		m.m_types.push_back(&type<mud::DofBlur>());
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
		m.m_types.push_back(&type<mud::BlockGIBake>());
		m.m_types.push_back(&type<mud::BlockGITrace>());
		m.m_types.push_back(&type<mud::BlockGeometry>());
		m.m_types.push_back(&type<mud::BlockGlow>());
		m.m_types.push_back(&type<mud::BlockLight>());
		m.m_types.push_back(&type<mud::BlockLightmap>());
		m.m_types.push_back(&type<mud::BlockRadiance>());
		m.m_types.push_back(&type<mud::BlockReflection>());
		m.m_types.push_back(&type<mud::BlockShadow>());
		m.m_types.push_back(&type<mud::BlockTonemap>());
		{
			static Function f = { &namspc({ "mud", "gfx" }), "gi_probe", nullptr, mud_gfx_gi_probe_0, { { "parent", type<mud::Gnode>(),  }, { "subdiv", type<uint16_t>(),  }, { "extents", type<mud::vec3>(),  } }, { &type<mud::GIProbe>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "lightmap", nullptr, mud_gfx_lightmap_1, { { "parent", type<mud::Gnode>(),  }, { "resolution", type<uint32_t>(),  }, { "density", type<float>(), Param::Default }, { "save_path", type<string>(), Param::Default } }, { &type<mud::LightmapAtlas>(), QualType::None } };
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
