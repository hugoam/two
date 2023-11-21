module;
#include <infra/Cpp20.h>
module TWO2(gfx.pbr, meta);

using namespace two;

void two_TonemapMode__to_string(void* val, string& str) { str = g_enu[type<two::TonemapMode>().m_id]->name(uint32_t((*static_cast<two::TonemapMode*>(val)))); }
void two_TonemapMode__to_value(const string& str, void* val) { (*static_cast<two::TonemapMode*>(val)) = two::TonemapMode(g_enu[type<two::TonemapMode>().m_id]->value(str.c_str())); }
void two_CubeTarget__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CubeTarget(  ); }
void two_CubeTarget_create(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::CubeTarget*>(object)).create(*static_cast<uint32_t*>(args[0])); }
void two_CubeTarget_side(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::CubeTarget*>(object)).side(*static_cast<size_t*>(args[0])); }
void two_CubeCamera__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CubeCamera(  ); }
void two_CubeCamera__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::CubeCamera( *static_cast<two::Scene*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<uint32_t*>(args[3]) ); }
void two_CubeCamera_render(void* object, span<void*> args, void*& result) { (*static_cast<two::Render*>(result)) = (*static_cast<two::CubeCamera*>(object)).render(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1]), *static_cast<two::SignedAxis*>(args[2])); }
void* two_ReflectionProbe__get_node(void* object) { return &(*static_cast<two::ReflectionProbe*>(object)).m_node; }
void two_LightShadow__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::LightShadow(  ); }
void two_LightShadow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::LightShadow((*static_cast<two::LightShadow*>(other))); }
void two_CSMSlice__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CSMSlice(  ); }
void two_CSMSlice__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CSMSlice((*static_cast<two::CSMSlice*>(other))); }
void two_CSMShadow__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CSMShadow(  ); }
void two_CSMShadow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CSMShadow((*static_cast<two::CSMShadow*>(other))); }
void two_DofParams__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::DofParams(  ); }
void two_DofParams__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::DofParams((*static_cast<two::DofParams*>(other))); }
void two_DofBlur__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::DofBlur(  ); }
void two_DofBlur__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::DofBlur((*static_cast<two::DofBlur*>(other))); }
void two_Glow__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Glow(  ); }
void two_Glow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Glow((*static_cast<two::Glow*>(other))); }
void two_BCS__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::BCS(  ); }
void two_BCS__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::BCS((*static_cast<two::BCS*>(other))); }
void two_Tonemap__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Tonemap(  ); }
void two_Tonemap__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Tonemap((*static_cast<two::Tonemap*>(other))); }
void two_begin_pbr_render_0(span<void*> args, void*& result) { UNUSED(result);  two::begin_pbr_render(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_gi_probes_1(span<void*> args, void*& result) { UNUSED(result);  two::pass_gi_probes(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_shadowmaps_2(span<void*> args, void*& result) { UNUSED(result);  two::pass_shadowmaps(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_shadow_3(span<void*> args, void*& result) { UNUSED(result);  two::pass_shadow(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_opaque_4(span<void*> args, void*& result) { UNUSED(result);  two::pass_opaque(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_alpha_5(span<void*> args, void*& result) { UNUSED(result);  two::pass_alpha(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_geometry_6(span<void*> args, void*& result) { UNUSED(result);  two::pass_geometry(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_lights_7(span<void*> args, void*& result) { UNUSED(result);  two::pass_lights(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_voxel_gi_8(span<void*> args, void*& result) { UNUSED(result);  two::pass_voxel_gi(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_lightmap_9(span<void*> args, void*& result) { UNUSED(result);  two::pass_lightmap(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_begin_post_10(span<void*> args, void*& result) { UNUSED(result);  two::pass_begin_post(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_post_auto_11(span<void*> args, void*& result) { UNUSED(result);  two::pass_post_auto(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_post_effects_12(span<void*> args, void*& result) { UNUSED(result);  two::pass_post_effects(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1]), *static_cast<two::DofBlur*>(args[2]), *static_cast<two::Glow*>(args[3]), *static_cast<two::Tonemap*>(args[4]), *static_cast<two::BCS*>(args[5])); }
void two_render_pbr_forward_13(span<void*> args, void*& result) { UNUSED(result);  two::render_pbr_forward(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_render_pbr_deferred_14(span<void*> args, void*& result) { UNUSED(result);  two::render_pbr_deferred(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_render_shadow_15(span<void*> args, void*& result) { UNUSED(result);  two::render_shadow(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_render_voxel_16(span<void*> args, void*& result) { UNUSED(result);  two::render_voxel(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_render_lightmap_17(span<void*> args, void*& result) { UNUSED(result);  two::render_lightmap(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_render_reflection_18(span<void*> args, void*& result) { UNUSED(result);  two::render_reflection(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pipeline_pbr_19(span<void*> args, void*& result) { UNUSED(result);  two::pipeline_pbr(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Renderer*>(args[1]), *static_cast<bool*>(args[2])); }
void two_gfx_setup_pipeline_pbr_20(span<void*> args, void*& result) { UNUSED(result);  two::gfx::setup_pipeline_pbr(*static_cast<two::GfxSystem*>(args[0])); }
void two_pass_shadowmaps_21(span<void*> args, void*& result) { UNUSED(result);  two::pass_shadowmaps(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_shadow_22(span<void*> args, void*& result) { UNUSED(result);  two::pass_shadow(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_gfx_gi_probe_23(span<void*> args, void*& result) { result = &two::gfx::gi_probe(*static_cast<two::Gnode*>(args[0]), *static_cast<uint16_t*>(args[1]), *static_cast<two::vec3*>(args[2])); }
void two_gfx_lightmap_24(span<void*> args, void*& result) { result = &two::gfx::lightmap(*static_cast<two::Gnode*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<float*>(args[2]), *static_cast<stl::string*>(args[3])); }
void two_pass_dofblur_25(span<void*> args, void*& result) { UNUSED(result);  two::pass_dofblur(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1]), *static_cast<two::DofBlur*>(args[2])); }
void two_pass_glow_26(span<void*> args, void*& result) { UNUSED(result);  two::pass_glow(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1]), *static_cast<two::Glow*>(args[2])); }
void two_pass_tonemap_27(span<void*> args, void*& result) { UNUSED(result);  two::pass_tonemap(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1]), *static_cast<two::Tonemap*>(args[2]), *static_cast<two::BCS*>(args[3])); }

namespace two
{
	void two_gfx_pbr_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::TonemapMode>();
		static Meta meta = { t, &namspc({ "two" }), "TonemapMode", sizeof(two::TonemapMode), TypeClass::Enum };
		static cstring ids[] = { "Linear", "Reinhardt", "Filmic", "ACES", "Cineon", "Uncharted2" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static two::TonemapMode vars[] = { two::TonemapMode::Linear, two::TonemapMode::Reinhardt, two::TonemapMode::Filmic, two::TonemapMode::ACES, two::TonemapMode::Cineon, two::TonemapMode::Uncharted2};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_TonemapMode__to_string,
		                           two_TonemapMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// two::BlockLight
	{
		Type& t = type<two::BlockLight>();
		static Meta meta = { t, &namspc({ "two" }), "BlockLight", sizeof(two::BlockLight), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockLight, two::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::LightmapItem
	{
		Type& t = type<two::LightmapItem>();
		static Meta meta = { t, &namspc({ "two" }), "LightmapItem", sizeof(two::LightmapItem), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Lightmap
	{
		Type& t = type<two::Lightmap>();
		static Meta meta = { t, &namspc({ "two" }), "Lightmap", sizeof(two::Lightmap), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::LightmapAtlas
	{
		Type& t = type<two::LightmapAtlas>();
		static Meta meta = { t, &namspc({ "two" }), "LightmapAtlas", sizeof(two::LightmapAtlas), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::BlockLightmap
	{
		Type& t = type<two::BlockLightmap>();
		static Meta meta = { t, &namspc({ "two" }), "BlockLightmap", sizeof(two::BlockLightmap), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockLightmap, two::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::PBRShot
	{
		Type& t = type<two::PBRShot>();
		static Meta meta = { t, &namspc({ "two" }), "PBRShot", sizeof(two::PBRShot), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Shot>() };
		static size_t bases_offsets[] = { base_offset<two::PBRShot, two::Shot>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::BlockGeometry
	{
		Type& t = type<two::BlockGeometry>();
		static Meta meta = { t, &namspc({ "two" }), "BlockGeometry", sizeof(two::BlockGeometry), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockGeometry, two::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::BlockRadiance
	{
		Type& t = type<two::BlockRadiance>();
		static Meta meta = { t, &namspc({ "two" }), "BlockRadiance", sizeof(two::BlockRadiance), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockRadiance, two::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::CubeTarget
	{
		Type& t = type<two::CubeTarget>();
		static Meta meta = { t, &namspc({ "two" }), "CubeTarget", sizeof(two::CubeTarget), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CubeTarget__construct_0, {} }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::CubeTarget, m_cubemap), type<two::Texture>(), "cubemap", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::CubeTarget, m_depth), type<two::Texture>(), "depth", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::CubeTarget, m_size), type<uint32_t>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "create", Address(), two_CubeTarget_create, { { "size", type<uint32_t>(),  } }, g_qvoid },
			{ t, "side", Address(), two_CubeTarget_side, { { "i", type<size_t>(),  } }, { &type<two::FrameBuffer>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::CubeCamera
	{
		Type& t = type<two::CubeCamera>();
		static Meta meta = { t, &namspc({ "two" }), "CubeCamera", sizeof(two::CubeCamera), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CubeCamera__construct_0, {} },
			{ t, two_CubeCamera__construct_1, { { "scene", type<two::Scene>(),  }, { "near", type<float>(),  }, { "far", type<float>(),  }, { "size", type<uint32_t>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::CubeCamera, m_cubemap), type<two::CubeTarget>(), "cubemap", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::CubeCamera, m_size), type<two::uvec2>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "render", Address(), two_CubeCamera_render, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  }, { "axis", type<two::SignedAxis>(),  } }, { &type<two::Render>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::ReflectionProbe
	{
		Type& t = type<two::ReflectionProbe>();
		static Meta meta = { t, &namspc({ "two" }), "ReflectionProbe", sizeof(two::ReflectionProbe), TypeClass::Object };
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
			{ t, SIZE_MAX, type<two::Node3>(), "node", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_ReflectionProbe__get_node },
			{ t, offsetof(two::ReflectionProbe, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(two::ReflectionProbe, m_intensity), type<float>(), "intensity", &intensity_default, Member::Value, nullptr },
			{ t, offsetof(two::ReflectionProbe, m_extents), type<two::vec3>(), "extents", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ReflectionProbe, m_shadows), type<bool>(), "shadows", &shadows_default, Member::Value, nullptr },
			{ t, offsetof(two::ReflectionProbe, m_dirty), type<bool>(), "dirty", &dirty_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::BlockReflection
	{
		Type& t = type<two::BlockReflection>();
		static Meta meta = { t, &namspc({ "two" }), "BlockReflection", sizeof(two::BlockReflection), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockReflection, two::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::LightShadow
	{
		Type& t = type<two::LightShadow>();
		static Meta meta = { t, &namspc({ "two" }), "LightShadow", sizeof(two::LightShadow), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_LightShadow__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_LightShadow__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::CSMSlice
	{
		Type& t = type<two::CSMSlice>();
		static Meta meta = { t, &namspc({ "two" }), "CSMSlice", sizeof(two::CSMSlice), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::LightShadow>(), &type<two::FrustumSlice>() };
		static size_t bases_offsets[] = { base_offset<two::CSMSlice, two::LightShadow>(), base_offset<two::CSMSlice, two::FrustumSlice>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CSMSlice__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CSMSlice__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::CSMShadow
	{
		Type& t = type<two::CSMShadow>();
		static Meta meta = { t, &namspc({ "two" }), "CSMShadow", sizeof(two::CSMShadow), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CSMShadow__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CSMShadow__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::BlockShadow
	{
		Type& t = type<two::BlockShadow>();
		static Meta meta = { t, &namspc({ "two" }), "BlockShadow", sizeof(two::BlockShadow), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockShadow, two::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::GIProbe
	{
		Type& t = type<two::GIProbe>();
		static Meta meta = { t, &namspc({ "two" }), "GIProbe", sizeof(two::GIProbe), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::BlockGITrace
	{
		Type& t = type<two::BlockGITrace>();
		static Meta meta = { t, &namspc({ "two" }), "BlockGITrace", sizeof(two::BlockGITrace), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockGITrace, two::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::BlockGIBake
	{
		Type& t = type<two::BlockGIBake>();
		static Meta meta = { t, &namspc({ "two" }), "BlockGIBake", sizeof(two::BlockGIBake), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockGIBake, two::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::BlockBlur
	{
		Type& t = type<two::BlockBlur>();
		static Meta meta = { t, &namspc({ "two" }), "BlockBlur", sizeof(two::BlockBlur), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockBlur, two::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::DofParams
	{
		Type& t = type<two::DofParams>();
		static Meta meta = { t, &namspc({ "two" }), "DofParams", sizeof(two::DofParams), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_DofParams__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_DofParams__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::DofParams, m_distance), type<float>(), "distance", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::DofParams, m_transition), type<float>(), "transition", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::DofParams, m_radius), type<float>(), "radius", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::DofBlur
	{
		Type& t = type<two::DofBlur>();
		static Meta meta = { t, &namspc({ "two" }), "DofBlur", sizeof(two::DofBlur), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static float max_coc_radius_default = 8.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_DofBlur__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_DofBlur__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::DofBlur, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(two::DofBlur, m_far), type<two::DofParams>(), "far", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::DofBlur, m_near), type<two::DofParams>(), "near", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::DofBlur, m_max_coc_radius), type<float>(), "max_coc_radius", &max_coc_radius_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::BlockDofBlur
	{
		Type& t = type<two::BlockDofBlur>();
		static Meta meta = { t, &namspc({ "two" }), "BlockDofBlur", sizeof(two::BlockDofBlur), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockDofBlur, two::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Glow
	{
		Type& t = type<two::Glow>();
		static Meta meta = { t, &namspc({ "two" }), "Glow", sizeof(two::Glow), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static two::vec4 levels_1_4_default = {1.f,0.f,0.f,0.f};
		static float intensity_default = 0.4f;
		static float bloom_default = 0.0f;
		static float bleed_threshold_default = 1.0f;
		static float bleed_scale_default = 2.0f;
		static bool bicubic_filter_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Glow__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Glow__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Glow, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(two::Glow, m_levels_1_4), type<two::vec4>(), "levels_1_4", &levels_1_4_default, Member::Value, nullptr },
			{ t, offsetof(two::Glow, m_levels_5_8), type<two::vec4>(), "levels_5_8", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Glow, m_intensity), type<float>(), "intensity", &intensity_default, Member::Value, nullptr },
			{ t, offsetof(two::Glow, m_bloom), type<float>(), "bloom", &bloom_default, Member::Value, nullptr },
			{ t, offsetof(two::Glow, m_bleed_threshold), type<float>(), "bleed_threshold", &bleed_threshold_default, Member::Value, nullptr },
			{ t, offsetof(two::Glow, m_bleed_scale), type<float>(), "bleed_scale", &bleed_scale_default, Member::Value, nullptr },
			{ t, offsetof(two::Glow, m_bicubic_filter), type<bool>(), "bicubic_filter", &bicubic_filter_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::BlockGlow
	{
		Type& t = type<two::BlockGlow>();
		static Meta meta = { t, &namspc({ "two" }), "BlockGlow", sizeof(two::BlockGlow), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockGlow, two::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::BCS
	{
		Type& t = type<two::BCS>();
		static Meta meta = { t, &namspc({ "two" }), "BCS", sizeof(two::BCS), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static float brightness_default = 1.0f;
		static float contrast_default = 1.0f;
		static float saturation_default = 1.0f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_BCS__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_BCS__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::BCS, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(two::BCS, m_brightness), type<float>(), "brightness", &brightness_default, Member::Value, nullptr },
			{ t, offsetof(two::BCS, m_contrast), type<float>(), "contrast", &contrast_default, Member::Value, nullptr },
			{ t, offsetof(two::BCS, m_saturation), type<float>(), "saturation", &saturation_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Tonemap
	{
		Type& t = type<two::Tonemap>();
		static Meta meta = { t, &namspc({ "two" }), "Tonemap", sizeof(two::Tonemap), TypeClass::Struct };
		// bases
		// defaults
		static two::TonemapMode mode_default = two::TonemapMode::Linear;
		static bool enabled_default = false;
		static float exposure_default = 1.0f;
		static float white_point_default = 1.0f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Tonemap__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Tonemap__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Tonemap, m_mode), type<two::TonemapMode>(), "mode", &mode_default, Member::Value, nullptr },
			{ t, offsetof(two::Tonemap, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(two::Tonemap, m_exposure), type<float>(), "exposure", &exposure_default, Member::Value, nullptr },
			{ t, offsetof(two::Tonemap, m_white_point), type<float>(), "white_point", &white_point_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::BlockTonemap
	{
		Type& t = type<two::BlockTonemap>();
		static Meta meta = { t, &namspc({ "two" }), "BlockTonemap", sizeof(two::BlockTonemap), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockTonemap, two::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::BlockLight>());
		m.m_types.push_back(&type<two::LightmapItem>());
		m.m_types.push_back(&type<two::Lightmap>());
		m.m_types.push_back(&type<two::LightmapAtlas>());
		m.m_types.push_back(&type<two::BlockLightmap>());
		m.m_types.push_back(&type<two::PBRShot>());
		m.m_types.push_back(&type<two::BlockGeometry>());
		m.m_types.push_back(&type<two::BlockRadiance>());
		m.m_types.push_back(&type<two::CubeTarget>());
		m.m_types.push_back(&type<two::CubeCamera>());
		m.m_types.push_back(&type<two::ReflectionProbe>());
		m.m_types.push_back(&type<two::BlockReflection>());
		m.m_types.push_back(&type<two::LightShadow>());
		m.m_types.push_back(&type<two::CSMSlice>());
		m.m_types.push_back(&type<two::CSMShadow>());
		m.m_types.push_back(&type<two::BlockShadow>());
		m.m_types.push_back(&type<two::GIProbe>());
		m.m_types.push_back(&type<two::BlockGITrace>());
		m.m_types.push_back(&type<two::BlockGIBake>());
		m.m_types.push_back(&type<two::BlockBlur>());
		m.m_types.push_back(&type<two::DofParams>());
		m.m_types.push_back(&type<two::DofBlur>());
		m.m_types.push_back(&type<two::BlockDofBlur>());
		m.m_types.push_back(&type<two::Glow>());
		m.m_types.push_back(&type<two::BlockGlow>());
		m.m_types.push_back(&type<two::TonemapMode>());
		m.m_types.push_back(&type<two::BCS>());
		m.m_types.push_back(&type<two::Tonemap>());
		m.m_types.push_back(&type<two::BlockTonemap>());
		{
			static Function f = { &namspc({ "two" }), "begin_pbr_render", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::begin_pbr_render), two_begin_pbr_render_0, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_gi_probes", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_gi_probes), two_pass_gi_probes_1, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_shadowmaps", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_shadowmaps), two_pass_shadowmaps_2, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_shadow", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_shadow), two_pass_shadow_3, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_opaque", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_opaque), two_pass_opaque_4, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_alpha", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_alpha), two_pass_alpha_5, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_geometry", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_geometry), two_pass_geometry_6, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_lights", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_lights), two_pass_lights_7, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_voxel_gi", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_voxel_gi), two_pass_voxel_gi_8, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_lightmap", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_lightmap), two_pass_lightmap_9, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_begin_post", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_begin_post), two_pass_begin_post_10, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_post_auto", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_post_auto), two_pass_post_auto_11, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_post_effects", funcptr<void(*)(two::GfxSystem&, two::Render&, two::DofBlur&, two::Glow&, two::Tonemap&, two::BCS&)>(two::pass_post_effects), two_pass_post_effects_12, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  }, { "dof", type<two::DofBlur>(),  }, { "glow", type<two::Glow>(),  }, { "tonemap", type<two::Tonemap>(),  }, { "bcs", type<two::BCS>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "render_pbr_forward", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::render_pbr_forward), two_render_pbr_forward_13, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "render_pbr_deferred", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::render_pbr_deferred), two_render_pbr_deferred_14, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "render_shadow", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::render_shadow), two_render_shadow_15, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "render_voxel", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::render_voxel), two_render_voxel_16, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "render_lightmap", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::render_lightmap), two_render_lightmap_17, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "render_reflection", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::render_reflection), two_render_reflection_18, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static bool deferred_default = false;
			static Function f = { &namspc({ "two" }), "pipeline_pbr", funcptr<void(*)(two::GfxSystem&, two::Renderer&, bool)>(two::pipeline_pbr), two_pipeline_pbr_19, { { "gfx", type<two::GfxSystem>(),  }, { "pipeline", type<two::Renderer>(),  }, { "deferred", type<bool>(), Param::Default, &deferred_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "setup_pipeline_pbr", funcptr<void(*)(two::GfxSystem&)>(two::gfx::setup_pipeline_pbr), two_gfx_setup_pipeline_pbr_20, { { "gfx", type<two::GfxSystem>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_shadowmaps", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_shadowmaps), two_pass_shadowmaps_21, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_shadow", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_shadow), two_pass_shadow_22, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "gi_probe", funcptr<two::GIProbe&(*)(two::Gnode&, uint16_t, const two::vec3&)>(two::gfx::gi_probe), two_gfx_gi_probe_23, { { "parent", type<two::Gnode>(),  }, { "subdiv", type<uint16_t>(),  }, { "extents", type<two::vec3>(),  } }, { &type<two::GIProbe>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float density_default = 8.f;
			static stl::string save_path_default = "";
			static Function f = { &namspc({ "two", "gfx" }), "lightmap", funcptr<two::LightmapAtlas&(*)(two::Gnode&, uint32_t, float, const stl::string&)>(two::gfx::lightmap), two_gfx_lightmap_24, { { "parent", type<two::Gnode>(),  }, { "resolution", type<uint32_t>(),  }, { "density", type<float>(), Param::Default, &density_default }, { "save_path", type<stl::string>(), Param::Default, &save_path_default } }, { &type<two::LightmapAtlas>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_dofblur", funcptr<void(*)(two::GfxSystem&, two::Render&, const two::DofBlur&)>(two::pass_dofblur), two_pass_dofblur_25, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  }, { "blur", type<two::DofBlur>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_glow", funcptr<void(*)(two::GfxSystem&, two::Render&, two::Glow&)>(two::pass_glow), two_pass_glow_26, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  }, { "glow", type<two::Glow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_tonemap", funcptr<void(*)(two::GfxSystem&, two::Render&, two::Tonemap&, two::BCS&)>(two::pass_tonemap), two_pass_tonemap_27, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  }, { "tonemap", type<two::Tonemap>(),  }, { "bcs", type<two::BCS>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_gfx_pbr::two_gfx_pbr()
		: Module("two::gfx-pbr", { &two_infra::m(), &two_type::m(), &two_math::m(), &two_geom::m(), &two_gfx::m() })
	{
		// setup reflection meta data
		two_gfx_pbr_meta(*this);
	}
}

#ifdef TWO_GFX_PBR_MODULE
extern "C"
Module& getModule()
{
	return two_gfx_pbr::m();
}
#endif
