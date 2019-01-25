#include <mud/jobs.refl.h>
#include <mud/gfx.h>
#include <mud/pool.refl.h>
#include <mud/geom.refl.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/ctx.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>
#include <mud/bgfx.refl.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif


namespace mud
{
	void mud_gfx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::AnimationTarget>();
		static Meta meta = { t, &namspc({ "mud" }), "AnimationTarget", sizeof(mud::AnimationTarget), TypeClass::Enum };
		static cstring ids[] = { "Position", "Rotation", "Scale" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::AnimationTarget vars[] = { mud::AnimationTarget::Position, mud::AnimationTarget::Rotation, mud::AnimationTarget::Scale};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::AnimationTarget>();
	}
	{
		Type& t = type<mud::BackgroundMode>();
		static Meta meta = { t, &namspc({ "mud" }), "BackgroundMode", sizeof(mud::BackgroundMode), TypeClass::Enum };
		static cstring ids[] = { "None", "Panorama", "Radiance", "Custom" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::BackgroundMode vars[] = { mud::BackgroundMode::None, mud::BackgroundMode::Panorama, mud::BackgroundMode::Radiance, mud::BackgroundMode::Custom};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::BackgroundMode>();
	}
	{
		Type& t = type<mud::BlendMode>();
		static Meta meta = { t, &namspc({ "mud" }), "BlendMode", sizeof(mud::BlendMode), TypeClass::Enum };
		static cstring ids[] = { "Mix", "Add", "Sub", "Mul", "Normal", "Alpha" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static mud::BlendMode vars[] = { mud::BlendMode::Mix, mud::BlendMode::Add, mud::BlendMode::Sub, mud::BlendMode::Mul, mud::BlendMode::Normal, mud::BlendMode::Alpha};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::BlendMode>();
	}
	{
		Type& t = type<mud::CullMode>();
		static Meta meta = { t, &namspc({ "mud" }), "CullMode", sizeof(mud::CullMode), TypeClass::Enum };
		static cstring ids[] = { "None", "Front", "Back" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::CullMode vars[] = { mud::CullMode::None, mud::CullMode::Front, mud::CullMode::Back};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::CullMode>();
	}
	{
		Type& t = type<mud::DepthDraw>();
		static Meta meta = { t, &namspc({ "mud" }), "DepthDraw", sizeof(mud::DepthDraw), TypeClass::Enum };
		static cstring ids[] = { "Enabled", "Disabled" };
		static uint32_t values[] = { 0, 1 };
		static mud::DepthDraw vars[] = { mud::DepthDraw::Enabled, mud::DepthDraw::Disabled};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::DepthDraw>();
	}
	{
		Type& t = type<mud::DepthTest>();
		static Meta meta = { t, &namspc({ "mud" }), "DepthTest", sizeof(mud::DepthTest), TypeClass::Enum };
		static cstring ids[] = { "Enabled", "Disabled" };
		static uint32_t values[] = { 0, 1 };
		static mud::DepthTest vars[] = { mud::DepthTest::Enabled, mud::DepthTest::Disabled};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::DepthTest>();
	}
	{
		Type& t = type<mud::EmitterFlow>();
		static Meta meta = { t, &namspc({ "mud" }), "EmitterFlow", sizeof(mud::EmitterFlow), TypeClass::Enum };
		static cstring ids[] = { "Outward", "Absolute" };
		static uint32_t values[] = { 0, 1 };
		static mud::EmitterFlow vars[] = { mud::EmitterFlow::Outward, mud::EmitterFlow::Absolute};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::EmitterFlow>();
	}
	{
		Type& t = type<mud::Interpolation>();
		static Meta meta = { t, &namspc({ "mud" }), "Interpolation", sizeof(mud::Interpolation), TypeClass::Enum };
		static cstring ids[] = { "Nearest", "Linear", "Cubic" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Interpolation vars[] = { mud::Interpolation::Nearest, mud::Interpolation::Linear, mud::Interpolation::Cubic};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::Interpolation>();
	}
	{
		Type& t = type<mud::IsometricAngle>();
		static Meta meta = { t, &namspc({ "mud" }), "IsometricAngle", sizeof(mud::IsometricAngle), TypeClass::Enum };
		static cstring ids[] = { "NORTH", "SOUTH", "EAST", "WEST" };
		static uint32_t values[] = { 1, 2, 256, 512 };
		static mud::IsometricAngle vars[] = { mud::NORTH, mud::SOUTH, mud::EAST, mud::WEST};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::IsometricAngle>();
	}
	{
		Type& t = type<mud::ItemShadow>();
		static Meta meta = { t, &namspc({ "mud" }), "ItemShadow", sizeof(mud::ItemShadow), TypeClass::Enum };
		static cstring ids[] = { "Default", "DoubleSided" };
		static uint32_t values[] = { 0, 1 };
		static mud::ItemShadow vars[] = { mud::ItemShadow::Default, mud::ItemShadow::DoubleSided};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::ItemShadow>();
	}
	{
		Type& t = type<mud::LightType>();
		static Meta meta = { t, &namspc({ "mud" }), "LightType", sizeof(mud::LightType), TypeClass::Enum };
		static cstring ids[] = { "Direct", "Point", "Spot", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::LightType vars[] = { mud::LightType::Direct, mud::LightType::Point, mud::LightType::Spot, mud::LightType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::LightType>();
	}
	{
		Type& t = type<mud::Lighting>();
		static Meta meta = { t, &namspc({ "mud" }), "Lighting", sizeof(mud::Lighting), TypeClass::Enum };
		static cstring ids[] = { "None", "Clustered", "Deferred", "VoxelGI" };
		static uint32_t values[] = { 0, 1, 2, 4 };
		static mud::Lighting vars[] = { mud::Lighting::None, mud::Lighting::Clustered, mud::Lighting::Deferred, mud::Lighting::VoxelGI};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::Lighting>();
	}
	{
		Type& t = type<mud::MSAA>();
		static Meta meta = { t, &namspc({ "mud" }), "MSAA", sizeof(mud::MSAA), TypeClass::Enum };
		static cstring ids[] = { "Disabled", "X2", "X4", "X8", "X16" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::MSAA vars[] = { mud::MSAA::Disabled, mud::MSAA::X2, mud::MSAA::X4, mud::MSAA::X8, mud::MSAA::X16};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::MSAA>();
	}
	{
		Type& t = type<mud::MaterialFlag>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialFlag", sizeof(mud::MaterialFlag), TypeClass::Enum };
		static cstring ids[] = { "TriplanarUV1", "TriplanarUV2", "Count" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::MaterialFlag vars[] = { mud::MaterialFlag::TriplanarUV1, mud::MaterialFlag::TriplanarUV2, mud::MaterialFlag::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::MaterialFlag>();
	}
	{
		Type& t = type<mud::ModelFormat>();
		static Meta meta = { t, &namspc({ "mud" }), "ModelFormat", sizeof(mud::ModelFormat), TypeClass::Enum };
		static cstring ids[] = { "obj", "gltf", "Count" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::ModelFormat vars[] = { mud::ModelFormat::obj, mud::ModelFormat::gltf, mud::ModelFormat::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::ModelFormat>();
	}
	{
		Type& t = type<mud::Month>();
		static Meta meta = { t, &namspc({ "mud" }), "Month", sizeof(mud::Month), TypeClass::Enum };
		static cstring ids[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		static mud::Month vars[] = { mud::Month::January, mud::Month::February, mud::Month::March, mud::Month::April, mud::Month::May, mud::Month::June, mud::Month::July, mud::Month::August, mud::Month::September, mud::Month::October, mud::Month::November, mud::Month::December};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::Month>();
	}
	{
		Type& t = type<mud::PbrDiffuseMode>();
		static Meta meta = { t, &namspc({ "mud" }), "PbrDiffuseMode", sizeof(mud::PbrDiffuseMode), TypeClass::Enum };
		static cstring ids[] = { "Lambert", "LambertHalf", "OrenNayar", "Burley", "Toon" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::PbrDiffuseMode vars[] = { mud::PbrDiffuseMode::Lambert, mud::PbrDiffuseMode::LambertHalf, mud::PbrDiffuseMode::OrenNayar, mud::PbrDiffuseMode::Burley, mud::PbrDiffuseMode::Toon};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::PbrDiffuseMode>();
	}
	{
		Type& t = type<mud::PbrSpecularMode>();
		static Meta meta = { t, &namspc({ "mud" }), "PbrSpecularMode", sizeof(mud::PbrSpecularMode), TypeClass::Enum };
		static cstring ids[] = { "SchlickGGX", "Blinn", "Phong", "Toon", "Disabled" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::PbrSpecularMode vars[] = { mud::PbrSpecularMode::SchlickGGX, mud::PbrSpecularMode::Blinn, mud::PbrSpecularMode::Phong, mud::PbrSpecularMode::Toon, mud::PbrSpecularMode::Disabled};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::PbrSpecularMode>();
	}
	{
		Type& t = type<mud::ShaderType>();
		static Meta meta = { t, &namspc({ "mud" }), "ShaderType", sizeof(mud::ShaderType), TypeClass::Enum };
		static cstring ids[] = { "Compute", "Fragment", "Geometry", "Vertex", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::ShaderType vars[] = { mud::ShaderType::Compute, mud::ShaderType::Fragment, mud::ShaderType::Geometry, mud::ShaderType::Vertex, mud::ShaderType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::ShaderType>();
	}
	{
		Type& t = type<mud::Shading>();
		static Meta meta = { t, &namspc({ "mud" }), "Shading", sizeof(mud::Shading), TypeClass::Enum };
		static cstring ids[] = { "Wireframe", "Unshaded", "Shaded", "Volume", "Voxels", "Lightmap", "Clear", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static mud::Shading vars[] = { mud::Shading::Wireframe, mud::Shading::Unshaded, mud::Shading::Shaded, mud::Shading::Volume, mud::Shading::Voxels, mud::Shading::Lightmap, mud::Shading::Clear, mud::Shading::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::Shading>();
	}
	{
		Type& t = type<mud::ShadowFlags>();
		static Meta meta = { t, &namspc({ "mud" }), "ShadowFlags", sizeof(mud::ShadowFlags), TypeClass::Enum };
		static cstring ids[] = { "CSM_Stabilize", "CSM_Optimize", "CSM_BlendSplits" };
		static uint32_t values[] = { 1, 2, 4 };
		static mud::ShadowFlags vars[] = { mud::CSM_Stabilize, mud::CSM_Optimize, mud::CSM_BlendSplits};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::ShadowFlags>();
	}
	{
		Type& t = type<mud::TextureChannel>();
		static Meta meta = { t, &namspc({ "mud" }), "TextureChannel", sizeof(mud::TextureChannel), TypeClass::Enum };
		static cstring ids[] = { "Red", "Green", "Blue", "Alpha", "All" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::TextureChannel vars[] = { mud::TextureChannel::Red, mud::TextureChannel::Green, mud::TextureChannel::Blue, mud::TextureChannel::Alpha, mud::TextureChannel::All};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::TextureChannel>();
	}
	{
		Type& t = type<mud::TextureHint>();
		static Meta meta = { t, &namspc({ "mud" }), "TextureHint", sizeof(mud::TextureHint), TypeClass::Enum };
		static cstring ids[] = { "Black", "White", "Normal" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::TextureHint vars[] = { mud::TextureHint::Black, mud::TextureHint::White, mud::TextureHint::Normal};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::TextureHint>();
	}
	{
		Type& t = type<mud::TextureSampler>();
		static Meta meta = { t, &namspc({ "mud" }), "TextureSampler", sizeof(mud::TextureSampler), TypeClass::Enum };
		static cstring ids[] = { "Source0", "Source1", "Source2", "Source3", "SourceDepth", "Color", "Albedo", "Metallic", "Roughness", "Emissive", "Normal", "AO", "Depth", "Skeleton", "ShadowCSM", "ShadowAtlas", "Radiance", "ReflectionProbe", "GIProbe", "Lights", "Clusters", "LightRecords", "Lightmap" };
		static uint32_t values[] = { 0, 1, 2, 3, 3, 0, 0, 1, 2, 3, 4, 11, 12, 5, 6, 7, 8, 9, 10, 13, 14, 15, 7 };
		static mud::TextureSampler vars[] = { mud::TextureSampler::Source0, mud::TextureSampler::Source1, mud::TextureSampler::Source2, mud::TextureSampler::Source3, mud::TextureSampler::SourceDepth, mud::TextureSampler::Color, mud::TextureSampler::Albedo, mud::TextureSampler::Metallic, mud::TextureSampler::Roughness, mud::TextureSampler::Emissive, mud::TextureSampler::Normal, mud::TextureSampler::AO, mud::TextureSampler::Depth, mud::TextureSampler::Skeleton, mud::TextureSampler::ShadowCSM, mud::TextureSampler::ShadowAtlas, mud::TextureSampler::Radiance, mud::TextureSampler::ReflectionProbe, mud::TextureSampler::GIProbe, mud::TextureSampler::Lights, mud::TextureSampler::Clusters, mud::TextureSampler::LightRecords, mud::TextureSampler::Lightmap};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12], &vars[13], &vars[14], &vars[15], &vars[16], &vars[17], &vars[18], &vars[19], &vars[20], &vars[21], &vars[22]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::TextureSampler>();
	}
	
	// Sequences
	{
		Type& t = type<array<mud::mat4>>();
		static Meta meta = { t, &namspc({}), "array<mud::mat4>", sizeof(array<mud::mat4>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::mat4>();
		meta_sequence<array<mud::mat4>, mud::mat4>();
	}
	{
		Type& t = type<vector<mud::Animation*>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Animation*>", sizeof(vector<mud::Animation*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Animation>();
		meta_vector<vector<mud::Animation*>, mud::Animation*>();
	}
	{
		Type& t = type<vector<mud::AnimationPlay>>();
		static Meta meta = { t, &namspc({}), "vector<mud::AnimationPlay>", sizeof(vector<mud::AnimationPlay>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::AnimationPlay>();
		meta_vector<vector<mud::AnimationPlay>, mud::AnimationPlay>();
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<string>();
		meta_vector<vector<string>, string>();
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<string>();
		meta_vector<vector<string>, string>();
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<string>();
		meta_vector<vector<string>, string>();
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<string>();
		meta_vector<vector<string>, string>();
	}
	
	// mud::Animated
	{
		Type& t = type<mud::Animated>();
		static Meta meta = { t, &namspc({ "mud" }), "Animated", sizeof(mud::Animated), TypeClass::Object };
		// defaults
		static bool active_default = true;
		static float speed_scale_default = 1.f;
		static float default_blend_time_default = 1.f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Animated::m_playing), type<vector<mud::AnimationPlay>>(), "playing", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Animated::m_queue), type<vector<mud::Animation*>>(), "queue", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Animated::m_active), type<bool>(), "active", Ref(&active_default), Member::Value, nullptr },
				{ t, member_address(&mud::Animated::m_speed_scale), type<float>(), "speed_scale", Ref(&speed_scale_default), Member::Value, nullptr },
				{ t, member_address(&mud::Animated::m_default_blend_time), type<float>(), "default_blend_time", Ref(&default_blend_time_default), Member::Value, nullptr }
			},
			// methods
			{
				{ t, "start", member_address<void(mud::Animated::*)(const char*, bool, float, float, bool)>(&mud::Animated::start), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Animated>(object).start(val<const char*>(args[0]), val<bool>(args[1]), val<float>(args[2]), val<float>(args[3]), val<bool>(args[4])); }, { { "animation", Ref(type<const char*>()), Param::Nullable }, { "loop", var(bool()) }, { "blend", var(float(0.f)), Param::Default }, { "speed", var(float(1.f)), Param::Default }, { "transient", var(bool(false)), Param::Default } }, Var() },
				{ t, "play", member_address<void(mud::Animated::*)(const mud::Animation&, bool, float, float, bool)>(&mud::Animated::play), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Animated>(object).play(val<mud::Animation>(args[0]), val<bool>(args[1]), val<float>(args[2]), val<float>(args[3]), val<bool>(args[4])); }, { { "animation", Ref(type<mud::Animation>()) }, { "loop", var(bool()) }, { "blend", var(float(0.f)), Param::Default }, { "speed", var(float(1.f)), Param::Default }, { "transient", var(bool(false)), Param::Default } }, Var() },
				{ t, "seek", member_address<void(mud::Animated::*)(float)>(&mud::Animated::seek), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Animated>(object).seek(val<float>(args[0])); }, { { "time", var(float()) } }, Var() },
				{ t, "pause", member_address<void(mud::Animated::*)()>(&mud::Animated::pause), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Animated>(object).pause(); }, {}, Var() },
				{ t, "stop", member_address<void(mud::Animated::*)()>(&mud::Animated::stop), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Animated>(object).stop(); }, {}, Var() },
				{ t, "advance", member_address<void(mud::Animated::*)(float)>(&mud::Animated::advance), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Animated>(object).advance(val<float>(args[0])); }, { { "time", var(float()) } }, Var() },
				{ t, "next_animation", member_address<void(mud::Animated::*)()>(&mud::Animated::next_animation), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Animated>(object).next_animation(); }, {}, Var() },
				{ t, "playing", member_address<string(mud::Animated::*)()>(&mud::Animated::playing), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<string>(result) = val<mud::Animated>(object).playing(); }, {}, var(string()) }
			},
			// static members
			{
			}
		};
		meta_class<mud::Animated>();
	}
	// mud::AnimatedTrack
	{
		Type& t = type<mud::AnimatedTrack>();
		static Meta meta = { t, &namspc({ "mud" }), "AnimatedTrack", sizeof(mud::AnimatedTrack), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::AnimatedTrack>(ref)) mud::AnimatedTrack(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::AnimatedTrack>(ref)) mud::AnimatedTrack(val<mud::AnimatedTrack>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::AnimatedTrack>();
	}
	// mud::Animation
	{
		Type& t = type<mud::Animation>();
		static Meta meta = { t, &namspc({ "mud" }), "Animation", sizeof(mud::Animation), TypeClass::Object };
		// defaults
		static float length_default = 1.f;
		static float step_default = 0.1f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Animation::m_name), type<string>(), "name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Animation::m_length), type<float>(), "length", Ref(&length_default), Member::Value, nullptr },
				{ t, member_address(&mud::Animation::m_step), type<float>(), "step", Ref(&step_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Animation>();
	}
	// mud::AnimationPlay
	{
		Type& t = type<mud::AnimationPlay>();
		static Meta meta = { t, &namspc({ "mud" }), "AnimationPlay", sizeof(mud::AnimationPlay), TypeClass::Struct };
		// defaults
		static const mud::Animation* animation_default = nullptr;
		static bool loop_default = true;
		static float speed_default = 1.f;
		static bool transient_default = false;
		static float fadeout_default = 0.f;
		static float fadeout_left_default = 0.f;
		static float cursor_default = 0.f;
		static bool ended_default = false;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::AnimationPlay>(ref)) mud::AnimationPlay(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::AnimationPlay>(ref)) mud::AnimationPlay(val<mud::AnimationPlay>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::AnimationPlay::m_animation), type<mud::Animation>(), "animation", Ref(animation_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::AnimationPlay::m_loop), type<bool>(), "loop", Ref(&loop_default), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationPlay::m_speed), type<float>(), "speed", Ref(&speed_default), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationPlay::m_transient), type<bool>(), "transient", Ref(&transient_default), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationPlay::m_fadeout), type<float>(), "fadeout", Ref(&fadeout_default), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationPlay::m_fadeout_left), type<float>(), "fadeout_left", Ref(&fadeout_left_default), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationPlay::m_cursor), type<float>(), "cursor", Ref(&cursor_default), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationPlay::m_ended), type<bool>(), "ended", Ref(&ended_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::AnimationPlay>();
	}
	// mud::AnimationTrack
	{
		Type& t = type<mud::AnimationTrack>();
		static Meta meta = { t, &namspc({ "mud" }), "AnimationTrack", sizeof(mud::AnimationTrack), TypeClass::Object };
		// defaults
		static mud::Type* value_type_default = nullptr;
		static float length_default = 0.f;
		static mud::Interpolation interpolation_default = mud::Interpolation::Linear;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::AnimationTrack::m_animation), type<mud::Animation>(), "animation", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::AnimationTrack::m_node), type<size_t>(), "node", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationTrack::m_node_name), type<string>(), "node_name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationTrack::m_target), type<mud::AnimationTarget>(), "target", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationTrack::m_value_type), type<mud::Type>(), "value_type", Ref(value_type_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::AnimationTrack::m_length), type<float>(), "length", Ref(&length_default), Member::Value, nullptr },
				{ t, member_address(&mud::AnimationTrack::m_interpolation), type<mud::Interpolation>(), "interpolation", Ref(&interpolation_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::AnimationTrack>();
	}
	// mud::AssetStore<mud::Material>
	{
		Type& t = type<mud::AssetStore<mud::Material>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Material>", sizeof(mud::AssetStore<mud::Material>), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
				{ t, "get", member_address<mud::Material*(mud::AssetStore<mud::Material>::*)(const string&)>(&mud::AssetStore<mud::Material>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Material>>(object).get(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Material>()) },
				{ t, "create", member_address<mud::Material&(mud::AssetStore<mud::Material>::*)(const string&)>(&mud::AssetStore<mud::Material>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Material>>(object).create(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Material>()) },
				{ t, "fetch", member_address<mud::Material&(mud::AssetStore<mud::Material>::*)(const string&)>(&mud::AssetStore<mud::Material>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Material>>(object).fetch(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Material>()) },
				{ t, "file", member_address<mud::Material*(mud::AssetStore<mud::Material>::*)(const string&)>(&mud::AssetStore<mud::Material>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Material>>(object).file(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Material>()) },
				{ t, "file_at", member_address<mud::Material&(mud::AssetStore<mud::Material>::*)(const string&, const string&)>(&mud::AssetStore<mud::Material>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Material>>(object).file_at(val<string>(args[0]), val<string>(args[1]))); }, { { "path", var(string()) }, { "name", var(string()) } }, Ref(type<mud::Material>()) },
				{ t, "destroy", member_address<void(mud::AssetStore<mud::Material>::*)(const string&)>(&mud::AssetStore<mud::Material>::destroy), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::AssetStore<mud::Material>>(object).destroy(val<string>(args[0])); }, { { "name", var(string()) } }, Var() }
			},
			// static members
			{
			}
		};
		meta_class<mud::AssetStore<mud::Material>>();
	}
	// mud::AssetStore<mud::Model>
	{
		Type& t = type<mud::AssetStore<mud::Model>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Model>", sizeof(mud::AssetStore<mud::Model>), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
				{ t, "get", member_address<mud::Model*(mud::AssetStore<mud::Model>::*)(const string&)>(&mud::AssetStore<mud::Model>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Model>>(object).get(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Model>()) },
				{ t, "create", member_address<mud::Model&(mud::AssetStore<mud::Model>::*)(const string&)>(&mud::AssetStore<mud::Model>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Model>>(object).create(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Model>()) },
				{ t, "fetch", member_address<mud::Model&(mud::AssetStore<mud::Model>::*)(const string&)>(&mud::AssetStore<mud::Model>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Model>>(object).fetch(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Model>()) },
				{ t, "file", member_address<mud::Model*(mud::AssetStore<mud::Model>::*)(const string&)>(&mud::AssetStore<mud::Model>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Model>>(object).file(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Model>()) },
				{ t, "file_at", member_address<mud::Model&(mud::AssetStore<mud::Model>::*)(const string&, const string&)>(&mud::AssetStore<mud::Model>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Model>>(object).file_at(val<string>(args[0]), val<string>(args[1]))); }, { { "path", var(string()) }, { "name", var(string()) } }, Ref(type<mud::Model>()) },
				{ t, "destroy", member_address<void(mud::AssetStore<mud::Model>::*)(const string&)>(&mud::AssetStore<mud::Model>::destroy), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::AssetStore<mud::Model>>(object).destroy(val<string>(args[0])); }, { { "name", var(string()) } }, Var() }
			},
			// static members
			{
			}
		};
		meta_class<mud::AssetStore<mud::Model>>();
	}
	// mud::AssetStore<mud::ParticleFlow>
	{
		Type& t = type<mud::AssetStore<mud::ParticleFlow>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::ParticleFlow>", sizeof(mud::AssetStore<mud::ParticleFlow>), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
				{ t, "get", member_address<mud::ParticleFlow*(mud::AssetStore<mud::ParticleFlow>::*)(const string&)>(&mud::AssetStore<mud::ParticleFlow>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::ParticleFlow>>(object).get(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::ParticleFlow>()) },
				{ t, "create", member_address<mud::ParticleFlow&(mud::AssetStore<mud::ParticleFlow>::*)(const string&)>(&mud::AssetStore<mud::ParticleFlow>::create), [](Ref object, array<Var> args, Var& result) { val<mud::ParticleFlow>(result) = val<mud::AssetStore<mud::ParticleFlow>>(object).create(val<string>(args[0])); }, { { "name", var(string()) } }, var(mud::ParticleFlow()) },
				{ t, "fetch", member_address<mud::ParticleFlow&(mud::AssetStore<mud::ParticleFlow>::*)(const string&)>(&mud::AssetStore<mud::ParticleFlow>::fetch), [](Ref object, array<Var> args, Var& result) { val<mud::ParticleFlow>(result) = val<mud::AssetStore<mud::ParticleFlow>>(object).fetch(val<string>(args[0])); }, { { "name", var(string()) } }, var(mud::ParticleFlow()) },
				{ t, "file", member_address<mud::ParticleFlow*(mud::AssetStore<mud::ParticleFlow>::*)(const string&)>(&mud::AssetStore<mud::ParticleFlow>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::ParticleFlow>>(object).file(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::ParticleFlow>()) },
				{ t, "file_at", member_address<mud::ParticleFlow&(mud::AssetStore<mud::ParticleFlow>::*)(const string&, const string&)>(&mud::AssetStore<mud::ParticleFlow>::file_at), [](Ref object, array<Var> args, Var& result) { val<mud::ParticleFlow>(result) = val<mud::AssetStore<mud::ParticleFlow>>(object).file_at(val<string>(args[0]), val<string>(args[1])); }, { { "path", var(string()) }, { "name", var(string()) } }, var(mud::ParticleFlow()) },
				{ t, "destroy", member_address<void(mud::AssetStore<mud::ParticleFlow>::*)(const string&)>(&mud::AssetStore<mud::ParticleFlow>::destroy), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::AssetStore<mud::ParticleFlow>>(object).destroy(val<string>(args[0])); }, { { "name", var(string()) } }, Var() }
			},
			// static members
			{
			}
		};
		meta_class<mud::AssetStore<mud::ParticleFlow>>();
	}
	// mud::AssetStore<mud::Prefab>
	{
		Type& t = type<mud::AssetStore<mud::Prefab>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Prefab>", sizeof(mud::AssetStore<mud::Prefab>), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
				{ t, "get", member_address<mud::Prefab*(mud::AssetStore<mud::Prefab>::*)(const string&)>(&mud::AssetStore<mud::Prefab>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Prefab>>(object).get(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Prefab>()) },
				{ t, "create", member_address<mud::Prefab&(mud::AssetStore<mud::Prefab>::*)(const string&)>(&mud::AssetStore<mud::Prefab>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Prefab>>(object).create(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Prefab>()) },
				{ t, "fetch", member_address<mud::Prefab&(mud::AssetStore<mud::Prefab>::*)(const string&)>(&mud::AssetStore<mud::Prefab>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Prefab>>(object).fetch(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Prefab>()) },
				{ t, "file", member_address<mud::Prefab*(mud::AssetStore<mud::Prefab>::*)(const string&)>(&mud::AssetStore<mud::Prefab>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Prefab>>(object).file(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Prefab>()) },
				{ t, "file_at", member_address<mud::Prefab&(mud::AssetStore<mud::Prefab>::*)(const string&, const string&)>(&mud::AssetStore<mud::Prefab>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Prefab>>(object).file_at(val<string>(args[0]), val<string>(args[1]))); }, { { "path", var(string()) }, { "name", var(string()) } }, Ref(type<mud::Prefab>()) },
				{ t, "destroy", member_address<void(mud::AssetStore<mud::Prefab>::*)(const string&)>(&mud::AssetStore<mud::Prefab>::destroy), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::AssetStore<mud::Prefab>>(object).destroy(val<string>(args[0])); }, { { "name", var(string()) } }, Var() }
			},
			// static members
			{
			}
		};
		meta_class<mud::AssetStore<mud::Prefab>>();
	}
	// mud::AssetStore<mud::Program>
	{
		Type& t = type<mud::AssetStore<mud::Program>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Program>", sizeof(mud::AssetStore<mud::Program>), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
				{ t, "get", member_address<mud::Program*(mud::AssetStore<mud::Program>::*)(const string&)>(&mud::AssetStore<mud::Program>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Program>>(object).get(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Program>()) },
				{ t, "create", member_address<mud::Program&(mud::AssetStore<mud::Program>::*)(const string&)>(&mud::AssetStore<mud::Program>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Program>>(object).create(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Program>()) },
				{ t, "fetch", member_address<mud::Program&(mud::AssetStore<mud::Program>::*)(const string&)>(&mud::AssetStore<mud::Program>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Program>>(object).fetch(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Program>()) },
				{ t, "file", member_address<mud::Program*(mud::AssetStore<mud::Program>::*)(const string&)>(&mud::AssetStore<mud::Program>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Program>>(object).file(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Program>()) },
				{ t, "file_at", member_address<mud::Program&(mud::AssetStore<mud::Program>::*)(const string&, const string&)>(&mud::AssetStore<mud::Program>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Program>>(object).file_at(val<string>(args[0]), val<string>(args[1]))); }, { { "path", var(string()) }, { "name", var(string()) } }, Ref(type<mud::Program>()) },
				{ t, "destroy", member_address<void(mud::AssetStore<mud::Program>::*)(const string&)>(&mud::AssetStore<mud::Program>::destroy), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::AssetStore<mud::Program>>(object).destroy(val<string>(args[0])); }, { { "name", var(string()) } }, Var() }
			},
			// static members
			{
			}
		};
		meta_class<mud::AssetStore<mud::Program>>();
	}
	// mud::AssetStore<mud::Texture>
	{
		Type& t = type<mud::AssetStore<mud::Texture>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Texture>", sizeof(mud::AssetStore<mud::Texture>), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
				{ t, "get", member_address<mud::Texture*(mud::AssetStore<mud::Texture>::*)(const string&)>(&mud::AssetStore<mud::Texture>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Texture>>(object).get(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Texture>()) },
				{ t, "create", member_address<mud::Texture&(mud::AssetStore<mud::Texture>::*)(const string&)>(&mud::AssetStore<mud::Texture>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Texture>>(object).create(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Texture>()) },
				{ t, "fetch", member_address<mud::Texture&(mud::AssetStore<mud::Texture>::*)(const string&)>(&mud::AssetStore<mud::Texture>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Texture>>(object).fetch(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Texture>()) },
				{ t, "file", member_address<mud::Texture*(mud::AssetStore<mud::Texture>::*)(const string&)>(&mud::AssetStore<mud::Texture>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Texture>>(object).file(val<string>(args[0]))); }, { { "name", var(string()) } }, Ref(type<mud::Texture>()) },
				{ t, "file_at", member_address<mud::Texture&(mud::AssetStore<mud::Texture>::*)(const string&, const string&)>(&mud::AssetStore<mud::Texture>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Texture>>(object).file_at(val<string>(args[0]), val<string>(args[1]))); }, { { "path", var(string()) }, { "name", var(string()) } }, Ref(type<mud::Texture>()) },
				{ t, "destroy", member_address<void(mud::AssetStore<mud::Texture>::*)(const string&)>(&mud::AssetStore<mud::Texture>::destroy), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::AssetStore<mud::Texture>>(object).destroy(val<string>(args[0])); }, { { "name", var(string()) } }, Var() }
			},
			// static members
			{
			}
		};
		meta_class<mud::AssetStore<mud::Texture>>();
	}
	// mud::Background
	{
		Type& t = type<mud::Background>();
		static Meta meta = { t, &namspc({ "mud" }), "Background", sizeof(mud::Background), TypeClass::Struct };
		// defaults
		static mud::BackgroundMode mode_default = mud::BackgroundMode::None;
		static mud::Colour colour_default = mud::Colour::Black;
		static mud::Program* custoprogram_default = nullptr;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Background>(ref)) mud::Background(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Background>(ref)) mud::Background(val<mud::Background>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Background::m_mode), type<mud::BackgroundMode>(), "mode", Ref(&mode_default), Member::Value, nullptr },
				{ t, member_address(&mud::Background::m_colour), type<mud::Colour>(), "colour", Ref(&colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::Background::m_custom_program), type<mud::Program>(), "custoprogram", Ref(custoprogram_default), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Background>();
	}
	// mud::BaseMaterialBlock
	{
		Type& t = type<mud::BaseMaterialBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "BaseMaterialBlock", sizeof(mud::BaseMaterialBlock), TypeClass::Struct };
		// defaults
		static mud::BlendMode blend_mode_default = mud::BlendMode::Mix;
		static mud::CullMode cull_mode_default = mud::CullMode::Back;
		static mud::DepthDraw depth_draw_mode_default = mud::DepthDraw::Enabled;
		static mud::DepthTest depth_test_default = mud::DepthTest::Enabled;
		static mud::vec2 uv0_scale_default = {1.f,1.f};
		static mud::vec2 uv0_offset_default = {0.f,0.f};
		static mud::vec2 uv1_scale_default = {1.f,1.f};
		static mud::vec2 uv1_offset_default = {0.f,0.f};
		static bool is_alpha_default = false;
		static bool screen_filter_default = false;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::BaseMaterialBlock>(ref)) mud::BaseMaterialBlock(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::BaseMaterialBlock>(ref)) mud::BaseMaterialBlock(val<mud::BaseMaterialBlock>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::BaseMaterialBlock::m_blend_mode), type<mud::BlendMode>(), "blend_mode", Ref(&blend_mode_default), Member::Value, nullptr },
				{ t, member_address(&mud::BaseMaterialBlock::m_cull_mode), type<mud::CullMode>(), "cull_mode", Ref(&cull_mode_default), Member::Value, nullptr },
				{ t, member_address(&mud::BaseMaterialBlock::m_depth_draw_mode), type<mud::DepthDraw>(), "depth_draw_mode", Ref(&depth_draw_mode_default), Member::Value, nullptr },
				{ t, member_address(&mud::BaseMaterialBlock::m_depth_test), type<mud::DepthTest>(), "depth_test", Ref(&depth_test_default), Member::Value, nullptr },
				{ t, member_address(&mud::BaseMaterialBlock::m_uv0_scale), type<mud::vec2>(), "uv0_scale", Ref(&uv0_scale_default), Member::Value, nullptr },
				{ t, member_address(&mud::BaseMaterialBlock::m_uv0_offset), type<mud::vec2>(), "uv0_offset", Ref(&uv0_offset_default), Member::Value, nullptr },
				{ t, member_address(&mud::BaseMaterialBlock::m_uv1_scale), type<mud::vec2>(), "uv1_scale", Ref(&uv1_scale_default), Member::Value, nullptr },
				{ t, member_address(&mud::BaseMaterialBlock::m_uv1_offset), type<mud::vec2>(), "uv1_offset", Ref(&uv1_offset_default), Member::Value, nullptr },
				{ t, member_address(&mud::BaseMaterialBlock::m_is_alpha), type<bool>(), "is_alpha", Ref(&is_alpha_default), Member::Value, nullptr },
				{ t, member_address(&mud::BaseMaterialBlock::m_screen_filter), type<bool>(), "screen_filter", Ref(&screen_filter_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BaseMaterialBlock>();
	}
	// mud::Bone
	{
		Type& t = type<mud::Bone>();
		static Meta meta = { t, &namspc({ "mud" }), "Bone", sizeof(mud::Bone), TypeClass::Struct };
		// defaults
		static mud::vec3 position_default = Zero3;
		static mud::quat rotation_default = ZeroQuat;
		static mud::vec3 scale_default = Unit3;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Bone>(ref)) mud::Bone(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Bone>(ref)) mud::Bone(val<mud::Bone>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Bone::m_position), type<mud::vec3>(), "position", Ref(&position_default), Member::Value, nullptr },
				{ t, member_address(&mud::Bone::m_rotation), type<mud::quat>(), "rotation", Ref(&rotation_default), Member::Value, nullptr },
				{ t, member_address(&mud::Bone::m_scale), type<mud::vec3>(), "scale", Ref(&scale_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Bone>();
	}
	// mud::Camera
	{
		Type& t = type<mud::Camera>();
		static Meta meta = { t, &namspc({ "mud" }), "Camera", sizeof(mud::Camera), TypeClass::Object };
		// defaults
		static float fov_default = 60.f;
		static float aspect_default = 1.f;
		static float near_default = 0.1f;
		static float far_default = 100.f;
		static bool orthographic_default = false;
		static float height_default = 1.f;
		static bool optimize_ends_default = true;
		static bool clustered_default = false;
		static mud::vec4 lod_offsets_default = {0.1f,0.3f,0.6f,0.8f};
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Camera::m_eye), type<mud::vec3>(), "eye", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_target), type<mud::vec3>(), "target", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_transform), type<mud::mat4>(), "transform", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_projection), type<mud::mat4>(), "projection", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_fov), type<float>(), "fov", Ref(&fov_default), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_aspect), type<float>(), "aspect", Ref(&aspect_default), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_near), type<float>(), "near", Ref(&near_default), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_far), type<float>(), "far", Ref(&far_default), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_orthographic), type<bool>(), "orthographic", Ref(&orthographic_default), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_height), type<float>(), "height", Ref(&height_default), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_optimize_ends), type<bool>(), "optimize_ends", Ref(&optimize_ends_default), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_clustered), type<bool>(), "clustered", Ref(&clustered_default), Member::Value, nullptr },
				{ t, member_address(&mud::Camera::m_lod_offsets), type<mud::vec4>(), "lod_offsets", Ref(&lod_offsets_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Camera>();
	}
	// mud::Culler
	{
		Type& t = type<mud::Culler>();
		static Meta meta = { t, &namspc({ "mud" }), "Culler", sizeof(mud::Culler), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Culler::m_viewport), type<mud::Viewport>(), "viewport", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Culler>();
	}
	// mud::DepthParams
	{
		Type& t = type<mud::DepthParams>();
		static Meta meta = { t, &namspc({ "mud" }), "DepthParams", sizeof(mud::DepthParams), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::DepthParams>(ref)) mud::DepthParams(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::DepthParams>(ref)) mud::DepthParams(val<mud::DepthParams>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::DepthParams>();
	}
	// mud::Environment
	{
		Type& t = type<mud::Environment>();
		static Meta meta = { t, &namspc({ "mud" }), "Environment", sizeof(mud::Environment), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Environment>(ref)) mud::Environment(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Environment>(ref)) mud::Environment(val<mud::Environment>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Environment::m_background), type<mud::Background>(), "background", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Environment::m_radiance), type<mud::Radiance>(), "radiance", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Environment::m_sun), type<mud::Sun>(), "sun", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Environment::m_fog), type<mud::Fog>(), "fog", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Environment>();
	}
	// mud::Filter
	{
		Type& t = type<mud::Filter>();
		static Meta meta = { t, &namspc({ "mud" }), "Filter", sizeof(mud::Filter), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Filter>();
	}
	// mud::Fog
	{
		Type& t = type<mud::Fog>();
		static Meta meta = { t, &namspc({ "mud" }), "Fog", sizeof(mud::Fog), TypeClass::Struct };
		// defaults
		static bool enabled_default = false;
		static float density_default = 0.01f;
		static mud::Colour colour_default = mud::Colour::White;
		static bool depth_default = false;
		static float depth_begin_default = 0.f;
		static float depth_curve_default = 1.f;
		static bool height_default = false;
		static float height_min_default = 0.f;
		static float height_max_default = 1.f;
		static float height_curve_default = 0.1f;
		static bool transmit_default = false;
		static float transmit_curve_default = 1.f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Fog>(ref)) mud::Fog(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Fog>(ref)) mud::Fog(val<mud::Fog>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Fog::m_enabled), type<bool>(), "enabled", Ref(&enabled_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_density), type<float>(), "density", Ref(&density_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_colour), type<mud::Colour>(), "colour", Ref(&colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_depth), type<bool>(), "depth", Ref(&depth_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_depth_begin), type<float>(), "depth_begin", Ref(&depth_begin_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_depth_curve), type<float>(), "depth_curve", Ref(&depth_curve_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_height), type<bool>(), "height", Ref(&height_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_height_min), type<float>(), "height_min", Ref(&height_min_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_height_max), type<float>(), "height_max", Ref(&height_max_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_height_curve), type<float>(), "height_curve", Ref(&height_curve_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_transmit), type<bool>(), "transmit", Ref(&transmit_default), Member::Value, nullptr },
				{ t, member_address(&mud::Fog::m_transmit_curve), type<float>(), "transmit_curve", Ref(&transmit_curve_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Fog>();
	}
	// mud::FrameBuffer
	{
		Type& t = type<mud::FrameBuffer>();
		static Meta meta = { t, &namspc({ "mud" }), "FrameBuffer", sizeof(mud::FrameBuffer), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::FrameBuffer>();
	}
	// mud::FresnelMaterialBlock
	{
		Type& t = type<mud::FresnelMaterialBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "FresnelMaterialBlock", sizeof(mud::FresnelMaterialBlock), TypeClass::Struct };
		// defaults
		static bool enabled_default = false;
		static mud::MaterialParam<mud::Colour> value_default = {Colour::White,nullptr};
		static float fresnel_scale_default = 1.f;
		static float fresnel_bias_default = 0.01f;
		static float fresnel_power_default = 5.f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::FresnelMaterialBlock>(ref)) mud::FresnelMaterialBlock(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::FresnelMaterialBlock>(ref)) mud::FresnelMaterialBlock(val<mud::FresnelMaterialBlock>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::FresnelMaterialBlock::m_enabled), type<bool>(), "enabled", Ref(&enabled_default), Member::Value, nullptr },
				{ t, member_address(&mud::FresnelMaterialBlock::m_value), type<mud::MaterialParam<mud::Colour>>(), "value", Ref(&value_default), Member::Value, nullptr },
				{ t, member_address(&mud::FresnelMaterialBlock::m_fresnel_scale), type<float>(), "fresnel_scale", Ref(&fresnel_scale_default), Member::Value, nullptr },
				{ t, member_address(&mud::FresnelMaterialBlock::m_fresnel_bias), type<float>(), "fresnel_bias", Ref(&fresnel_bias_default), Member::Value, nullptr },
				{ t, member_address(&mud::FresnelMaterialBlock::m_fresnel_power), type<float>(), "fresnel_power", Ref(&fresnel_power_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::FresnelMaterialBlock>();
	}
	// mud::Frustum
	{
		Type& t = type<mud::Frustum>();
		static Meta meta = { t, &namspc({ "mud" }), "Frustum", sizeof(mud::Frustum), TypeClass::Object };
		// defaults
		static float fov_default = 60.f;
		static float aspect_default = 1.f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Frustum::m_fov), type<float>(), "fov", Ref(&fov_default), Member::Value, nullptr },
				{ t, member_address(&mud::Frustum::m_aspect), type<float>(), "aspect", Ref(&aspect_default), Member::Value, nullptr },
				{ t, member_address(&mud::Frustum::m_near), type<float>(), "near", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Frustum::m_far), type<float>(), "far", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Frustum::m_center), type<mud::vec3>(), "center", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Frustum::m_radius), type<float>(), "radius", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Frustum>();
	}
	// mud::FrustumSlice
	{
		Type& t = type<mud::FrustumSlice>();
		static Meta meta = { t, &namspc({ "mud" }), "FrustumSlice", sizeof(mud::FrustumSlice), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::FrustumSlice>(ref)) mud::FrustumSlice(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::FrustumSlice>(ref)) mud::FrustumSlice(val<mud::FrustumSlice>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::FrustumSlice>();
	}
	// mud::GfxBlock
	{
		Type& t = type<mud::GfxBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "GfxBlock", sizeof(mud::GfxBlock), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, Address(), type<mud::Type>(), "type", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxBlock>(object).m_type); } },
				{ t, member_address(&mud::GfxBlock::m_index), type<uint8_t>(), "index", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::GfxBlock>();
	}
	// mud::GfxContext
	{
		Type& t = type<mud::GfxContext>();
		static Meta meta = { t, &namspc({ "mud" }), "GfxContext", sizeof(mud::GfxContext), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::GfxContext>();
	}
	// mud::GfxSystem
	{
		Type& t = type<mud::GfxSystem>();
		static Meta meta = { t, &namspc({ "mud" }), "GfxSystem", sizeof(mud::GfxSystem), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::GfxSystem>(ref)) mud::GfxSystem( val<string>(args[0]) ); }, { { "resource_path", var(string()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address<mud::AssetStore<mud::Texture>&(mud::GfxSystem::*)()>(&mud::GfxSystem::textures), type<mud::AssetStore<mud::Texture>>(), "textures", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).textures()); } },
				{ t, member_address<mud::AssetStore<mud::Program>&(mud::GfxSystem::*)()>(&mud::GfxSystem::programs), type<mud::AssetStore<mud::Program>>(), "programs", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).programs()); } },
				{ t, member_address<mud::AssetStore<mud::Material>&(mud::GfxSystem::*)()>(&mud::GfxSystem::materials), type<mud::AssetStore<mud::Material>>(), "materials", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).materials()); } },
				{ t, member_address<mud::AssetStore<mud::Model>&(mud::GfxSystem::*)()>(&mud::GfxSystem::models), type<mud::AssetStore<mud::Model>>(), "models", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).models()); } },
				{ t, member_address<mud::AssetStore<mud::ParticleFlow>&(mud::GfxSystem::*)()>(&mud::GfxSystem::particles), type<mud::AssetStore<mud::ParticleFlow>>(), "particles", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).particles()); } },
				{ t, member_address<mud::AssetStore<mud::Prefab>&(mud::GfxSystem::*)()>(&mud::GfxSystem::prefabs), type<mud::AssetStore<mud::Prefab>>(), "prefabs", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).prefabs()); } }
			},
			// methods
			{
				{ t, "default_pipeline", member_address<void(mud::GfxSystem::*)()>(&mud::GfxSystem::default_pipeline), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::GfxSystem>(object).default_pipeline(); }, {}, Var() },
				{ t, "add_resource_path", member_address<void(mud::GfxSystem::*)(const string&, bool)>(&mud::GfxSystem::add_resource_path), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::GfxSystem>(object).add_resource_path(val<string>(args[0]), val<bool>(args[1])); }, { { "path", var(string()) }, { "relative", var(bool(true)), Param::Default } }, Var() },
				{ t, "debug_material", member_address<mud::Material&(mud::GfxSystem::*)()>(&mud::GfxSystem::debug_material), [](Ref object, array<Var> args, Var& result) { UNUSED(args); result = Ref(&val<mud::GfxSystem>(object).debug_material()); }, {}, Ref(type<mud::Material>()) },
				{ t, "fetch_material", member_address<mud::Material&(mud::GfxSystem::*)(const string&, const string&, bool)>(&mud::GfxSystem::fetch_material), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::GfxSystem>(object).fetch_material(val<string>(args[0]), val<string>(args[1]), val<bool>(args[2]))); }, { { "name", var(string()) }, { "shader", var(string()) }, { "builtin", var(bool(true)), Param::Default } }, Ref(type<mud::Material>()) },
				{ t, "fetch_image256_material", member_address<mud::Material&(mud::GfxSystem::*)(const mud::Image256&)>(&mud::GfxSystem::fetch_image256_material), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::GfxSystem>(object).fetch_image256_material(val<mud::Image256>(args[0]))); }, { { "image", var(mud::Image256()) } }, Ref(type<mud::Material>()) },
				{ t, "fetch_symbol", member_address<mud::Model&(mud::GfxSystem::*)(const mud::Symbol&, const mud::Shape&, mud::DrawMode)>(&mud::GfxSystem::fetch_symbol), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::GfxSystem>(object).fetch_symbol(val<mud::Symbol>(args[0]), val<mud::Shape>(args[1]), val<mud::DrawMode>(args[2]))); }, { { "symbol", var(mud::Symbol()) }, { "shape", Ref(type<mud::Shape>()) }, { "draw_mode", var(mud::DrawMode()) } }, Ref(type<mud::Model>()) },
				{ t, "fetch_symbol_material", member_address<mud::Material&(mud::GfxSystem::*)(const mud::Symbol&, mud::DrawMode)>(&mud::GfxSystem::fetch_symbol_material), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::GfxSystem>(object).fetch_symbol_material(val<mud::Symbol>(args[0]), val<mud::DrawMode>(args[1]))); }, { { "symbol", var(mud::Symbol()) }, { "draw_mode", var(mud::DrawMode()) } }, Ref(type<mud::Material>()) }
			},
			// static members
			{
			}
		};
		init_pool<mud::GfxSystem>();
		meta_class<mud::GfxSystem>();
	}
	// mud::Gnode
	{
		Type& t = type<mud::Gnode>();
		static Meta meta = { t, &namspc({ "mud" }), "Gnode", sizeof(mud::Gnode), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Gnode>();
	}
	// mud::ImmediateDraw
	{
		Type& t = type<mud::ImmediateDraw>();
		static Meta meta = { t, &namspc({ "mud" }), "ImmediateDraw", sizeof(mud::ImmediateDraw), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ImmediateDraw>();
	}
	// mud::ImportConfig
	{
		Type& t = type<mud::ImportConfig>();
		static Meta meta = { t, &namspc({ "mud" }), "ImportConfig", sizeof(mud::ImportConfig), TypeClass::Struct };
		// defaults
		static mud::ModelFormat format_default = mud::ModelFormat::obj;
		static mud::vec3 position_default = Zero3;
		static mud::quat rotation_default = ZeroQuat;
		static mud::vec3 scale_default = Unit3;
		static mud::mat4 transform_default = bxidentity();
		static vector<string> exclude_elements_default = {};
		static vector<string> exclude_materials_default = {};
		static vector<string> include_elements_default = {};
		static vector<string> include_materials_default = {};
		static bool force_reimport_default = false;
		static bool cache_geometry_default = false;
		static bool optimize_geometry_default = false;
		static uint32_t flags_default = ItemFlag::None;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ImportConfig>(ref)) mud::ImportConfig(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ImportConfig>(ref)) mud::ImportConfig(val<mud::ImportConfig>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ImportConfig::m_format), type<mud::ModelFormat>(), "format", Ref(&format_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_position), type<mud::vec3>(), "position", Ref(&position_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_rotation), type<mud::quat>(), "rotation", Ref(&rotation_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_scale), type<mud::vec3>(), "scale", Ref(&scale_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_transform), type<mud::mat4>(), "transform", Ref(&transform_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_exclude_elements), type<vector<string>>(), "exclude_elements", Ref(&exclude_elements_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_exclude_materials), type<vector<string>>(), "exclude_materials", Ref(&exclude_materials_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_include_elements), type<vector<string>>(), "include_elements", Ref(&include_elements_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_include_materials), type<vector<string>>(), "include_materials", Ref(&include_materials_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_suffix), type<string>(), "suffix", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_force_reimport), type<bool>(), "force_reimport", Ref(&force_reimport_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_cache_geometry), type<bool>(), "cache_geometry", Ref(&cache_geometry_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_optimize_geometry), type<bool>(), "optimize_geometry", Ref(&optimize_geometry_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImportConfig::m_flags), type<uint32_t>(), "flags", Ref(&flags_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ImportConfig>();
	}
	// mud::Item
	{
		Type& t = type<mud::Item>();
		static Meta meta = { t, &namspc({ "mud" }), "Item", sizeof(mud::Item), TypeClass::Object };
		// defaults
		static mud::Model* model_default = nullptr;
		static uint32_t flags_default = 0;
		static mud::Colour colour_default = mud::Colour::White;
		static mud::Material* material_default = nullptr;
		static bool visible_default = true;
		static mud::ItemShadow shadow_default = mud::ItemShadow::Default;
		static mud::Rig* rig_default = nullptr;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Item::m_node), type<mud::Node3>(), "node", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Item::m_model), type<mud::Model>(), "model", Ref(model_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Item::m_flags), type<uint32_t>(), "flags", Ref(&flags_default), Member::Value, nullptr },
				{ t, member_address(&mud::Item::m_colour), type<mud::Colour>(), "colour", Ref(&colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::Item::m_material), type<mud::Material>(), "material", Ref(material_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Item::m_visible), type<bool>(), "visible", Ref(&visible_default), Member::Value, nullptr },
				{ t, member_address(&mud::Item::m_shadow), type<mud::ItemShadow>(), "shadow", Ref(&shadow_default), Member::Value, nullptr },
				{ t, member_address(&mud::Item::m_rig), type<mud::Rig>(), "rig", Ref(rig_default), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Item>();
	}
	// mud::Joint
	{
		Type& t = type<mud::Joint>();
		static Meta meta = { t, &namspc({ "mud" }), "Joint", sizeof(mud::Joint), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Joint>(ref)) mud::Joint(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Joint>(ref)) mud::Joint(val<mud::Joint>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Joint>();
	}
	// mud::Light
	{
		Type& t = type<mud::Light>();
		static Meta meta = { t, &namspc({ "mud" }), "Light", sizeof(mud::Light), TypeClass::Object };
		// defaults
		static mud::LightType type_default = mud::LightType::Point;
		static bool visible_default = true;
		static mud::Colour colour_default = mud::Colour::White;
		static float range_default = 1.f;
		static float energy_default = 1.f;
		static float specular_default = 0.5f;
		static float attenuation_default = 0.5f;
		static bool shadows_default = false;
		static mud::Colour shadow_colour_default = mud::Colour::Black;
		static float shadow_range_default = 100.f;
		static uint32_t layers_default = 0xFFFFFFFF;
		static uint32_t last_render_default = 0;
		static uint32_t last_update_default = 0;
		static float spot_angle_default = 45.f;
		static float spot_attenuation_default = 0.5f;
		static uint8_t shadow_nusplits_default = 1;
		static float shadow_split_distribution_default = 0.6f;
		static float shadow_normal_bias_default = 0.1f;
		static float shadow_bias_default = 0.f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, Address(), type<mud::Node3>(), "node", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Light>(object).m_node); } },
				{ t, member_address(&mud::Light::m_type), type<mud::LightType>(), "type", Ref(&type_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_visible), type<bool>(), "visible", Ref(&visible_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_colour), type<mud::Colour>(), "colour", Ref(&colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_range), type<float>(), "range", Ref(&range_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_energy), type<float>(), "energy", Ref(&energy_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_specular), type<float>(), "specular", Ref(&specular_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_attenuation), type<float>(), "attenuation", Ref(&attenuation_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_shadows), type<bool>(), "shadows", Ref(&shadows_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_shadow_colour), type<mud::Colour>(), "shadow_colour", Ref(&shadow_colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_shadow_range), type<float>(), "shadow_range", Ref(&shadow_range_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_layers), type<uint32_t>(), "layers", Ref(&layers_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_last_render), type<uint32_t>(), "last_render", Ref(&last_render_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_last_update), type<uint32_t>(), "last_update", Ref(&last_update_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_spot_angle), type<float>(), "spot_angle", Ref(&spot_angle_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_spot_attenuation), type<float>(), "spot_attenuation", Ref(&spot_attenuation_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_shadow_flags), type<mud::ShadowFlags>(), "shadow_flags", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_shadow_num_splits), type<uint8_t>(), "shadow_nusplits", Ref(&shadow_nusplits_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_shadow_split_distribution), type<float>(), "shadow_split_distribution", Ref(&shadow_split_distribution_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_shadow_normal_bias), type<float>(), "shadow_normal_bias", Ref(&shadow_normal_bias_default), Member::Value, nullptr },
				{ t, member_address(&mud::Light::m_shadow_bias), type<float>(), "shadow_bias", Ref(&shadow_bias_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Light>();
	}
	// mud::Material
	{
		Type& t = type<mud::Material>();
		static Meta meta = { t, &namspc({ "mud" }), "Material", sizeof(mud::Material), TypeClass::Object };
		// defaults
		static uint16_t index_default = 0;
		static bool builtin_default = false;
		static mud::Program* program_default = nullptr;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Material::m_index), type<uint16_t>(), "index", Ref(&index_default), Member::Value, nullptr },
				{ t, member_address(&mud::Material::m_name), type<string>(), "name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Material::m_builtin), type<bool>(), "builtin", Ref(&builtin_default), Member::Value, nullptr },
				{ t, member_address(&mud::Material::m_program), type<mud::Program>(), "program", Ref(program_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Material::m_base_block), type<mud::BaseMaterialBlock>(), "base_block", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Material::m_unshaded_block), type<mud::UnshadedMaterialBlock>(), "unshaded_block", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Material::m_pbr_block), type<mud::PbrMaterialBlock>(), "pbr_block", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Material::m_fresnel_block), type<mud::FresnelMaterialBlock>(), "fresnel_block", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Material>();
	}
	// mud::MaterialParam<float>
	{
		Type& t = type<mud::MaterialParam<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialParam<float>", sizeof(mud::MaterialParam<float>), TypeClass::Struct };
		// defaults
		static mud::Texture* texture_default = nullptr;
		static mud::TextureChannel channel_default = mud::TextureChannel::All;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::MaterialParam<float>>(ref)) mud::MaterialParam<float>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::MaterialParam<float>>(ref)) mud::MaterialParam<float>(val<mud::MaterialParam<float>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::MaterialParam<float>::m_value), type<float>(), "value", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::MaterialParam<float>::m_texture), type<mud::Texture>(), "texture", Ref(texture_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::MaterialParam<float>::m_channel), type<mud::TextureChannel>(), "channel", Ref(&channel_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::MaterialParam<float>>();
	}
	// mud::MaterialParam<mud::Colour>
	{
		Type& t = type<mud::MaterialParam<mud::Colour>>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialParam<mud::Colour>", sizeof(mud::MaterialParam<mud::Colour>), TypeClass::Struct };
		// defaults
		static mud::Texture* texture_default = nullptr;
		static mud::TextureChannel channel_default = mud::TextureChannel::All;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::MaterialParam<mud::Colour>>(ref)) mud::MaterialParam<mud::Colour>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::MaterialParam<mud::Colour>>(ref)) mud::MaterialParam<mud::Colour>(val<mud::MaterialParam<mud::Colour>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::MaterialParam<mud::Colour>::m_value), type<mud::Colour>(), "value", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::MaterialParam<mud::Colour>::m_texture), type<mud::Texture>(), "texture", Ref(texture_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::MaterialParam<mud::Colour>::m_channel), type<mud::TextureChannel>(), "channel", Ref(&channel_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::MaterialParam<mud::Colour>>();
	}
	// mud::Mesh
	{
		Type& t = type<mud::Mesh>();
		static Meta meta = { t, &namspc({ "mud" }), "Mesh", sizeof(mud::Mesh), TypeClass::Object };
		// defaults
		static mud::DrawMode draw_mode_default = PLAIN;
		static mud::Aabb aabb_default = {};
		static float radius_default = 0.f;
		static mud::vec3 origin_default = Zero3;
		static bool readback_default = false;
		static uint32_t vertex_format_default = 0;
		static bool qnormals_default = false;
		static uint32_t vertex_count_default = 0;
		static uint32_t index_count_default = 0;
		static bool index32_default = false;
		static mud::Material* material_default = nullptr;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Mesh::m_name), type<string>(), "name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_index), type<uint16_t>(), "index", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_draw_mode), type<mud::DrawMode>(), "draw_mode", Ref(&draw_mode_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_aabb), type<mud::Aabb>(), "aabb", Ref(&aabb_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_radius), type<float>(), "radius", Ref(&radius_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_origin), type<mud::vec3>(), "origin", Ref(&origin_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_readback), type<bool>(), "readback", Ref(&readback_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_vertex_format), type<uint32_t>(), "vertex_format", Ref(&vertex_format_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_qnormals), type<bool>(), "qnormals", Ref(&qnormals_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_vertex_count), type<uint32_t>(), "vertex_count", Ref(&vertex_count_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_index_count), type<uint32_t>(), "index_count", Ref(&index_count_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_index32), type<bool>(), "index32", Ref(&index32_default), Member::Value, nullptr },
				{ t, member_address(&mud::Mesh::m_material), type<mud::Material>(), "material", Ref(material_default), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Mesh>();
	}
	// mud::Model
	{
		Type& t = type<mud::Model>();
		static Meta meta = { t, &namspc({ "mud" }), "Model", sizeof(mud::Model), TypeClass::Object };
		// defaults
		static mud::Aabb aabb_default = {Zero3,Zero3};
		static float radius_default = 0.f;
		static mud::vec3 origin_default = Zero3;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Model::m_name), type<string>(), "name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Model::m_index), type<uint16_t>(), "index", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Model::m_aabb), type<mud::Aabb>(), "aabb", Ref(&aabb_default), Member::Value, nullptr },
				{ t, member_address(&mud::Model::m_radius), type<float>(), "radius", Ref(&radius_default), Member::Value, nullptr },
				{ t, member_address(&mud::Model::m_origin), type<mud::vec3>(), "origin", Ref(&origin_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Model>();
	}
	// mud::ModelItem
	{
		Type& t = type<mud::ModelItem>();
		static Meta meta = { t, &namspc({ "mud" }), "ModelItem", sizeof(mud::ModelItem), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ModelItem>(ref)) mud::ModelItem(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ModelItem>(ref)) mud::ModelItem(val<mud::ModelItem>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ModelItem::m_index), type<size_t>(), "index", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ModelItem::m_mesh), type<mud::Mesh>(), "mesh", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::ModelItem::m_has_transform), type<bool>(), "has_transform", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ModelItem::m_transform), type<mud::mat4>(), "transform", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ModelItem::m_skin), type<int>(), "skin", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ModelItem::m_colour), type<mud::Colour>(), "colour", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ModelItem::m_material), type<mud::Material>(), "material", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ModelItem>();
	}
	// mud::Node3
	{
		Type& t = type<mud::Node3>();
		static Meta meta = { t, &namspc({ "mud" }), "Node3", sizeof(mud::Node3), TypeClass::Object };
		// defaults
		static mud::Scene* scene_default = nullptr;
		static uint16_t index_default = 0;
		static mud::mat4 transform_default = bxidentity();
		static bool visible_default = true;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Node3::m_scene), type<mud::Scene>(), "scene", Ref(scene_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Node3::m_index), type<uint16_t>(), "index", Ref(&index_default), Member::Value, nullptr },
				{ t, member_address(&mud::Node3::m_transform), type<mud::mat4>(), "transform", Ref(&transform_default), Member::Value, nullptr },
				{ t, member_address(&mud::Node3::m_visible), type<bool>(), "visible", Ref(&visible_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Node3>();
	}
	// mud::ParticleFlow
	{
		Type& t = type<mud::ParticleFlow>();
		static Meta meta = { t, &namspc({ "mud" }), "ParticleFlow", sizeof(mud::ParticleFlow), TypeClass::Struct };
		// defaults
		static float duration_default = 1.f;
		static float start_time_default = 0.f;
		static bool loop_default = false;
		static mud::ShapeVar shape_default = {};
		static mud::EmitterFlow flow_default = mud::EmitterFlow::Outward;
		static bool billboard_default = true;
		static mud::vec3 direction_default = {0.f,0.f,-1.f};
		static mud::quat rotation_default = ZeroQuat;
		static mud::BlendMode blend_mode_default = mud::BlendMode::Normal;
		static mud::ValueTrack<float> volume_default = {1.f};
		static mud::ValueTrack<uint32_t> rate_default = {0};
		static mud::ValueTrack<float> lifetime_default = {1.f};
		static mud::ValueTrack<float> gravity_default = {0.f};
		static mud::ValueTrack<float> speed_default = {1.f};
		static mud::ValueTrack<float> angle_default = {0.f};
		static mud::ValueTrack<float> blend_default = {vector<float>({0.8f,0.0f})};
		static mud::ValueTrack<mud::Colour> colour_default = {Colour::White};
		static mud::ValueTrack<float> scale_default = {0.1f};
		static mud::ValueTrack<float> sprite_frame_default = {0.f};
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ParticleFlow>(ref)) mud::ParticleFlow(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ParticleFlow>(ref)) mud::ParticleFlow(val<mud::ParticleFlow>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ParticleFlow::m_name), type<string>(), "name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_duration), type<float>(), "duration", Ref(&duration_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_start_time), type<float>(), "start_time", Ref(&start_time_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_loop), type<bool>(), "loop", Ref(&loop_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_shape), type<mud::ShapeVar>(), "shape", Ref(&shape_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_flow), type<mud::EmitterFlow>(), "flow", Ref(&flow_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_billboard), type<bool>(), "billboard", Ref(&billboard_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_direction), type<mud::vec3>(), "direction", Ref(&direction_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_rotation), type<mud::quat>(), "rotation", Ref(&rotation_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_blend_mode), type<mud::BlendMode>(), "blend_mode", Ref(&blend_mode_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_volume), type<mud::ValueTrack<float>>(), "volume", Ref(&volume_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_rate), type<mud::ValueTrack<uint32_t>>(), "rate", Ref(&rate_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_lifetime), type<mud::ValueTrack<float>>(), "lifetime", Ref(&lifetime_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_gravity), type<mud::ValueTrack<float>>(), "gravity", Ref(&gravity_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_speed), type<mud::ValueTrack<float>>(), "speed", Ref(&speed_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_angle), type<mud::ValueTrack<float>>(), "angle", Ref(&angle_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_blend), type<mud::ValueTrack<float>>(), "blend", Ref(&blend_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_colour), type<mud::ValueTrack<mud::Colour>>(), "colour", Ref(&colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_scale), type<mud::ValueTrack<float>>(), "scale", Ref(&scale_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_sprite_frame), type<mud::ValueTrack<float>>(), "sprite_frame", Ref(&sprite_frame_default), Member::Value, nullptr },
				{ t, member_address(&mud::ParticleFlow::m_sprite_name), type<string>(), "sprite_name", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ParticleFlow>();
	}
	// mud::PbrMaterialBlock
	{
		Type& t = type<mud::PbrMaterialBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "PbrMaterialBlock", sizeof(mud::PbrMaterialBlock), TypeClass::Struct };
		// defaults
		static bool enabled_default = false;
		static mud::MaterialParam<mud::Colour> albedo_default = {Colour::White,nullptr};
		static float specular_default = 0.5f;
		static mud::MaterialParam<float> metallic_default = {0.f,nullptr,TextureChannel::Red};
		static mud::MaterialParam<float> roughness_default = {1.f,nullptr,TextureChannel::Red};
		static mud::MaterialParam<mud::Colour> emissive_default = {Colour::None,nullptr};
		static float emissive_energy_default = 0.f;
		static mud::MaterialParam<float> normal_default = {1.f,nullptr};
		static mud::MaterialParam<float> depth_default = {-0.02f,nullptr};
		static bool deep_parallax_default = false;
		static mud::PbrDiffuseMode diffuse_mode_default = mud::PbrDiffuseMode::Burley;
		static mud::PbrSpecularMode specular_mode_default = mud::PbrSpecularMode::SchlickGGX;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::PbrMaterialBlock>(ref)) mud::PbrMaterialBlock(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::PbrMaterialBlock>(ref)) mud::PbrMaterialBlock( val<mud::Colour>(args[0]), val<float>(args[1]), val<float>(args[2]) ); }, { { "albedo", var(mud::Colour()) }, { "metallic", var(float(0.f)), Param::Default }, { "roughness", var(float(1.f)), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::PbrMaterialBlock>(ref)) mud::PbrMaterialBlock(val<mud::PbrMaterialBlock>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::PbrMaterialBlock::m_enabled), type<bool>(), "enabled", Ref(&enabled_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_albedo), type<mud::MaterialParam<mud::Colour>>(), "albedo", Ref(&albedo_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_specular), type<float>(), "specular", Ref(&specular_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_metallic), type<mud::MaterialParam<float>>(), "metallic", Ref(&metallic_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_roughness), type<mud::MaterialParam<float>>(), "roughness", Ref(&roughness_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_emissive), type<mud::MaterialParam<mud::Colour>>(), "emissive", Ref(&emissive_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_emissive_energy), type<float>(), "emissive_energy", Ref(&emissive_energy_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_normal), type<mud::MaterialParam<float>>(), "normal", Ref(&normal_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_rim), type<mud::MaterialParam<float>>(), "rim", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_rim_tint), type<float>(), "ritint", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_clearcoat), type<mud::MaterialParam<float>>(), "clearcoat", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_clearcoat_gloss), type<float>(), "clearcoat_gloss", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_anisotropy), type<mud::MaterialParam<float>>(), "anisotropy", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_subsurface), type<mud::MaterialParam<float>>(), "subsurface", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_transmission), type<mud::MaterialParam<mud::Colour>>(), "transmission", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_refraction), type<mud::MaterialParam<float>>(), "refraction", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_ambient_occlusion), type<mud::MaterialParam<float>>(), "ambient_occlusion", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_depth), type<mud::MaterialParam<float>>(), "depth", Ref(&depth_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_deep_parallax), type<bool>(), "deep_parallax", Ref(&deep_parallax_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_diffuse_mode), type<mud::PbrDiffuseMode>(), "diffuse_mode", Ref(&diffuse_mode_default), Member::Value, nullptr },
				{ t, member_address(&mud::PbrMaterialBlock::m_specular_mode), type<mud::PbrSpecularMode>(), "specular_mode", Ref(&specular_mode_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::PbrMaterialBlock>();
	}
	// mud::Prefab
	{
		Type& t = type<mud::Prefab>();
		static Meta meta = { t, &namspc({ "mud" }), "Prefab", sizeof(mud::Prefab), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Prefab::m_name), type<string>(), "name", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Prefab>();
	}
	// mud::Program
	{
		Type& t = type<mud::Program>();
		static Meta meta = { t, &namspc({ "mud" }), "Program", sizeof(mud::Program), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address<const char*(mud::Program::*)()>(&mud::Program::name), type<const char*>(), "name", Ref(), Member::Flags(Member::Pointer|Member::NonMutable|Member::Link), [](Ref object) { return Ref(val<mud::Program>(object).name()); } }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Program>();
	}
	// mud::Radiance
	{
		Type& t = type<mud::Radiance>();
		static Meta meta = { t, &namspc({ "mud" }), "Radiance", sizeof(mud::Radiance), TypeClass::Struct };
		// defaults
		static float energy_default = 1.0f;
		static float ambient_default = 1.0f;
		static mud::Colour colour_default = mud::Colour::Black;
		static mud::Texture* texture_default = nullptr;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Radiance>(ref)) mud::Radiance(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Radiance>(ref)) mud::Radiance(val<mud::Radiance>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Radiance::m_energy), type<float>(), "energy", Ref(&energy_default), Member::Value, nullptr },
				{ t, member_address(&mud::Radiance::m_ambient), type<float>(), "ambient", Ref(&ambient_default), Member::Value, nullptr },
				{ t, member_address(&mud::Radiance::m_colour), type<mud::Colour>(), "colour", Ref(&colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::Radiance::m_texture), type<mud::Texture>(), "texture", Ref(texture_default), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Radiance>();
	}
	// mud::RenderFrame
	{
		Type& t = type<mud::RenderFrame>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderFrame", sizeof(mud::RenderFrame), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::RenderFrame>(ref)) mud::RenderFrame(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::RenderFrame>(ref)) mud::RenderFrame(val<mud::RenderFrame>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::RenderFrame>();
	}
	// mud::RenderQuad
	{
		Type& t = type<mud::RenderQuad>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderQuad", sizeof(mud::RenderQuad), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::RenderQuad>(ref)) mud::RenderQuad(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::RenderQuad>(ref)) mud::RenderQuad(val<mud::RenderQuad>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::RenderQuad>();
	}
	// mud::Rig
	{
		Type& t = type<mud::Rig>();
		static Meta meta = { t, &namspc({ "mud" }), "Rig", sizeof(mud::Rig), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Rig>();
	}
	// mud::Scene
	{
		Type& t = type<mud::Scene>();
		static Meta meta = { t, &namspc({ "mud" }), "Scene", sizeof(mud::Scene), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Scene::m_graph), type<mud::Gnode>(), "graph", Ref(), Member::NonMutable, nullptr },
				{ t, member_address(&mud::Scene::m_root_node), type<mud::Node3>(), "root_node", Ref(), Member::NonMutable, nullptr },
				{ t, member_address(&mud::Scene::m_environment), type<mud::Environment>(), "environment", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Scene::m_user), type<mud::Ref>(), "user", Ref(), Member::Value, nullptr }
			},
			// methods
			{
				{ t, "begin", member_address<mud::Gnode&(mud::Scene::*)()>(&mud::Scene::begin), [](Ref object, array<Var> args, Var& result) { UNUSED(args); result = Ref(&val<mud::Scene>(object).begin()); }, {}, Ref(type<mud::Gnode>()) }
			},
			// static members
			{
			}
		};
		meta_class<mud::Scene>();
	}
	// mud::Shot
	{
		Type& t = type<mud::Shot>();
		static Meta meta = { t, &namspc({ "mud" }), "Shot", sizeof(mud::Shot), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Shot>();
	}
	// mud::Skeleton
	{
		Type& t = type<mud::Skeleton>();
		static Meta meta = { t, &namspc({ "mud" }), "Skeleton", sizeof(mud::Skeleton), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Skeleton>();
	}
	// mud::Skin
	{
		Type& t = type<mud::Skin>();
		static Meta meta = { t, &namspc({ "mud" }), "Skin", sizeof(mud::Skin), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Skin>();
	}
	// mud::Sun
	{
		Type& t = type<mud::Sun>();
		static Meta meta = { t, &namspc({ "mud" }), "Sun", sizeof(mud::Sun), TypeClass::Struct };
		// defaults
		static mud::Colour colour_default = {0.8f,0.8f,0.0f};
		static float intensity_default = 0.f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Sun>(ref)) mud::Sun(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Sun>(ref)) mud::Sun(val<mud::Sun>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Sun::azimuth), type<float>(), "azimuth", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Sun::elevation), type<float>(), "elevation", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Sun::m_colour), type<mud::Colour>(), "colour", Ref(&colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::Sun::m_intensity), type<float>(), "intensity", Ref(&intensity_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Sun>();
	}
	// mud::SymbolIndex
	{
		Type& t = type<mud::SymbolIndex>();
		static Meta meta = { t, &namspc({ "mud" }), "SymbolIndex", sizeof(mud::SymbolIndex), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::SymbolIndex>();
	}
	// mud::Texture
	{
		Type& t = type<mud::Texture>();
		static Meta meta = { t, &namspc({ "mud" }), "Texture", sizeof(mud::Texture), TypeClass::Object };
		// defaults
		static uint16_t width_default = 0;
		static uint16_t height_default = 0;
		static uint32_t bits_per_pixel_default = 0;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Texture::m_name), type<string>(), "name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Texture::m_width), type<uint16_t>(), "width", Ref(&width_default), Member::Value, nullptr },
				{ t, member_address(&mud::Texture::m_height), type<uint16_t>(), "height", Ref(&height_default), Member::Value, nullptr },
				{ t, member_address(&mud::Texture::m_bits_per_pixel), type<uint32_t>(), "bits_per_pixel", Ref(&bits_per_pixel_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Texture>();
	}
	// mud::UnshadedMaterialBlock
	{
		Type& t = type<mud::UnshadedMaterialBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "UnshadedMaterialBlock", sizeof(mud::UnshadedMaterialBlock), TypeClass::Struct };
		// defaults
		static bool enabled_default = false;
		static mud::MaterialParam<mud::Colour> colour_default = {Colour::White,nullptr};
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::UnshadedMaterialBlock>(ref)) mud::UnshadedMaterialBlock(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::UnshadedMaterialBlock>(ref)) mud::UnshadedMaterialBlock(val<mud::UnshadedMaterialBlock>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::UnshadedMaterialBlock::m_enabled), type<bool>(), "enabled", Ref(&enabled_default), Member::Value, nullptr },
				{ t, member_address(&mud::UnshadedMaterialBlock::m_colour), type<mud::MaterialParam<mud::Colour>>(), "colour", Ref(&colour_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::UnshadedMaterialBlock>();
	}
	// mud::Viewport
	{
		Type& t = type<mud::Viewport>();
		static Meta meta = { t, &namspc({ "mud" }), "Viewport", sizeof(mud::Viewport), TypeClass::Object };
		// defaults
		static uint16_t index_default = 0;
		static bool active_default = true;
		static bool scissor_default = false;
		static mud::Colour clear_colour_default = mud::Colour::Black;
		static mud::Shading shading_default = mud::Shading::Shaded;
		static mud::Lighting lighting_default = mud::Lighting::Clustered;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Viewport::m_camera), type<mud::Camera>(), "camera", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Viewport::m_scene), type<mud::Scene>(), "scene", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Viewport::m_index), type<uint16_t>(), "index", Ref(&index_default), Member::Value, nullptr },
				{ t, member_address(&mud::Viewport::m_active), type<bool>(), "active", Ref(&active_default), Member::Value, nullptr },
				{ t, member_address(&mud::Viewport::m_rect), type<mud::uvec4>(), "rect", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Viewport::m_scissor), type<bool>(), "scissor", Ref(&scissor_default), Member::Value, nullptr },
				{ t, member_address(&mud::Viewport::m_clear_colour), type<mud::Colour>(), "clear_colour", Ref(&clear_colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::Viewport::m_shading), type<mud::Shading>(), "shading", Ref(&shading_default), Member::Value, nullptr },
				{ t, member_address(&mud::Viewport::m_lighting), type<mud::Lighting>(), "lighting", Ref(&lighting_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Viewport>();
	}
	// mud::BlockCopy
	{
		Type& t = type<mud::BlockCopy>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockCopy", sizeof(mud::BlockCopy), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::BlockCopy, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockCopy>();
	}
	// mud::DrawBlock
	{
		Type& t = type<mud::DrawBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "DrawBlock", sizeof(mud::DrawBlock), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::DrawBlock, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::DrawBlock>();
	}
	// mud::BlockDepth
	{
		Type& t = type<mud::BlockDepth>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockDepth", sizeof(mud::BlockDepth), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::DrawBlock>() },
			{ base_offset<mud::BlockDepth, mud::DrawBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockDepth>();
	}
	// mud::BlockFilter
	{
		Type& t = type<mud::BlockFilter>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockFilter", sizeof(mud::BlockFilter), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::BlockFilter, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockFilter>();
	}
	// mud::BlockParticles
	{
		Type& t = type<mud::BlockParticles>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockParticles", sizeof(mud::BlockParticles), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::BlockParticles, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockParticles>();
	}
	// mud::BlockResolve
	{
		Type& t = type<mud::BlockResolve>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockResolve", sizeof(mud::BlockResolve), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::BlockResolve, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockResolve>();
	}
	// mud::BlockSky
	{
		Type& t = type<mud::BlockSky>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockSky", sizeof(mud::BlockSky), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::BlockSky, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockSky>();
	}
	// mud::ClusteredFrustum
	{
		Type& t = type<mud::ClusteredFrustum>();
		static Meta meta = { t, &namspc({ "mud" }), "ClusteredFrustum", sizeof(mud::ClusteredFrustum), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Frustum>() },
			{ base_offset<mud::ClusteredFrustum, mud::Frustum>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ClusteredFrustum>(ref)) mud::ClusteredFrustum(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ClusteredFrustum>(ref)) mud::ClusteredFrustum(val<mud::ClusteredFrustum>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ClusteredFrustum>();
	}
	// mud::Particles
	{
		Type& t = type<mud::Particles>();
		static Meta meta = { t, &namspc({ "mud" }), "Particles", sizeof(mud::Particles), TypeClass::Struct };
		// defaults
		static mud::Node3* node_default = nullptr;
		static Class cls = { t,
			// bases
			{ &type<mud::ParticleFlow>() },
			{ base_offset<mud::Particles, mud::ParticleFlow>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Particles>(ref)) mud::Particles(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Particles>(ref)) mud::Particles(val<mud::Particles>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Particles::m_node), type<mud::Node3>(), "node", Ref(node_default), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Particles>();
	}
	// mud::RenderTarget
	{
		Type& t = type<mud::RenderTarget>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderTarget", sizeof(mud::RenderTarget), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::FrameBuffer>() },
			{ base_offset<mud::RenderTarget, mud::FrameBuffer>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::RenderTarget>();
	}
		m.m_types.push_back(&type<mud::Animated>());
		m.m_types.push_back(&type<mud::AnimatedTrack>());
		m.m_types.push_back(&type<mud::Animation>());
		m.m_types.push_back(&type<mud::AnimationPlay>());
		m.m_types.push_back(&type<mud::AnimationTarget>());
		m.m_types.push_back(&type<mud::AnimationTrack>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Material>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Model>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::ParticleFlow>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Prefab>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Program>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Texture>>());
		m.m_types.push_back(&type<mud::Background>());
		m.m_types.push_back(&type<mud::BackgroundMode>());
		m.m_types.push_back(&type<mud::BaseMaterialBlock>());
		m.m_types.push_back(&type<mud::BlendMode>());
		m.m_types.push_back(&type<mud::Bone>());
		m.m_types.push_back(&type<mud::Camera>());
		m.m_types.push_back(&type<mud::CullMode>());
		m.m_types.push_back(&type<mud::Culler>());
		m.m_types.push_back(&type<mud::DepthDraw>());
		m.m_types.push_back(&type<mud::DepthParams>());
		m.m_types.push_back(&type<mud::DepthTest>());
		m.m_types.push_back(&type<mud::EmitterFlow>());
		m.m_types.push_back(&type<mud::Environment>());
		m.m_types.push_back(&type<mud::Filter>());
		m.m_types.push_back(&type<mud::Fog>());
		m.m_types.push_back(&type<mud::FrameBuffer>());
		m.m_types.push_back(&type<mud::FresnelMaterialBlock>());
		m.m_types.push_back(&type<mud::Frustum>());
		m.m_types.push_back(&type<mud::FrustumSlice>());
		m.m_types.push_back(&type<mud::GfxBlock>());
		m.m_types.push_back(&type<mud::GfxContext>());
		m.m_types.push_back(&type<mud::GfxSystem>());
		m.m_types.push_back(&type<mud::Gnode>());
		m.m_types.push_back(&type<mud::ImmediateDraw>());
		m.m_types.push_back(&type<mud::ImportConfig>());
		m.m_types.push_back(&type<mud::Interpolation>());
		m.m_types.push_back(&type<mud::IsometricAngle>());
		m.m_types.push_back(&type<mud::Item>());
		m.m_types.push_back(&type<mud::ItemShadow>());
		m.m_types.push_back(&type<mud::Joint>());
		m.m_types.push_back(&type<mud::Light>());
		m.m_types.push_back(&type<mud::LightType>());
		m.m_types.push_back(&type<mud::Lighting>());
		m.m_types.push_back(&type<mud::MSAA>());
		m.m_types.push_back(&type<mud::Material>());
		m.m_types.push_back(&type<mud::MaterialFlag>());
		m.m_types.push_back(&type<mud::MaterialParam<float>>());
		m.m_types.push_back(&type<mud::MaterialParam<mud::Colour>>());
		m.m_types.push_back(&type<mud::Mesh>());
		m.m_types.push_back(&type<mud::Model>());
		m.m_types.push_back(&type<mud::ModelFormat>());
		m.m_types.push_back(&type<mud::ModelItem>());
		m.m_types.push_back(&type<mud::Month>());
		m.m_types.push_back(&type<mud::Node3>());
		m.m_types.push_back(&type<mud::ParticleFlow>());
		m.m_types.push_back(&type<mud::PbrDiffuseMode>());
		m.m_types.push_back(&type<mud::PbrMaterialBlock>());
		m.m_types.push_back(&type<mud::PbrSpecularMode>());
		m.m_types.push_back(&type<mud::Prefab>());
		m.m_types.push_back(&type<mud::Program>());
		m.m_types.push_back(&type<mud::Radiance>());
		m.m_types.push_back(&type<mud::RenderFrame>());
		m.m_types.push_back(&type<mud::RenderQuad>());
		m.m_types.push_back(&type<mud::Rig>());
		m.m_types.push_back(&type<mud::Scene>());
		m.m_types.push_back(&type<mud::ShaderType>());
		m.m_types.push_back(&type<mud::Shading>());
		m.m_types.push_back(&type<mud::ShadowFlags>());
		m.m_types.push_back(&type<mud::Shot>());
		m.m_types.push_back(&type<mud::Skeleton>());
		m.m_types.push_back(&type<mud::Skin>());
		m.m_types.push_back(&type<mud::Sun>());
		m.m_types.push_back(&type<mud::SymbolIndex>());
		m.m_types.push_back(&type<mud::Texture>());
		m.m_types.push_back(&type<mud::TextureChannel>());
		m.m_types.push_back(&type<mud::TextureHint>());
		m.m_types.push_back(&type<mud::TextureSampler>());
		m.m_types.push_back(&type<mud::UnshadedMaterialBlock>());
		m.m_types.push_back(&type<mud::Viewport>());
		m.m_types.push_back(&type<array<mud::mat4>>());
		m.m_types.push_back(&type<vector<mud::Animation*>>());
		m.m_types.push_back(&type<vector<mud::AnimationPlay>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<mud::BlockCopy>());
		m.m_types.push_back(&type<mud::BlockDepth>());
		m.m_types.push_back(&type<mud::BlockFilter>());
		m.m_types.push_back(&type<mud::BlockParticles>());
		m.m_types.push_back(&type<mud::BlockResolve>());
		m.m_types.push_back(&type<mud::BlockSky>());
		m.m_types.push_back(&type<mud::ClusteredFrustum>());
		m.m_types.push_back(&type<mud::DrawBlock>());
		m.m_types.push_back(&type<mud::Particles>());
		m.m_types.push_back(&type<mud::RenderTarget>());
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::update_item_lights(val<mud::Item>(args[0])); };
			vector<Param> params = { { "item", Ref(type<mud::Item>()) } };
			static Function f = { &namspc({ "mud", "gfx" }), "update_item_lights", funcptr<void(*)(mud::Item&)>(&mud::gfx::update_item_lights), func, params, Var() };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::update_item_aabb(val<mud::Item>(args[0])); };
			vector<Param> params = { { "item", Ref(type<mud::Item>()) } };
			static Function f = { &namspc({ "mud", "gfx" }), "update_item_aabb", funcptr<void(*)(mud::Item&)>(&mud::gfx::update_item_aabb), func, params, Var() };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::node(val<mud::Gnode>(args[0]), args[1], val<mud::vec3>(args[2]), val<mud::quat>(args[3]), val<mud::vec3>(args[4]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "object", Ref(), Param::Flags(Param::Nullable|Param::Default) }, { "position", var(mud::vec3(Zero3)), Param::Default }, { "rotation", var(mud::quat(ZeroQuat)), Param::Default }, { "scale", var(mud::vec3(Unit3)), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "node", funcptr<mud::Gnode&(*)(mud::Gnode&, mud::Ref, const mud::vec3&, const mud::quat&, const mud::vec3&)>(&mud::gfx::node), func, params, Ref(type<mud::Gnode>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::shape(val<mud::Gnode>(args[0]), val<mud::Shape>(args[1]), val<mud::Symbol>(args[2]), val<uint32_t>(args[3]), &val<mud::Material>(args[4]), val<size_t>(args[5]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "shape", Ref(type<mud::Shape>()) }, { "symbol", var(mud::Symbol()) }, { "flags", var(uint32_t(0)), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t(0)), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "shape", funcptr<mud::Item&(*)(mud::Gnode&, const mud::Shape&, const mud::Symbol&, uint32_t, mud::Material*, size_t)>(&mud::gfx::shape), func, params, Ref(type<mud::Item>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::draw(val<mud::Gnode>(args[0]), val<mud::Shape>(args[1]), val<mud::Symbol>(args[2]), val<uint32_t>(args[3])); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "shape", Ref(type<mud::Shape>()) }, { "symbol", var(mud::Symbol()) }, { "flags", var(uint32_t(0)), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "draw", funcptr<void(*)(mud::Gnode&, const mud::Shape&, const mud::Symbol&, uint32_t)>(&mud::gfx::draw), func, params, Var() };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::sprite(val<mud::Gnode>(args[0]), val<mud::Image256>(args[1]), val<mud::vec2>(args[2]), val<uint32_t>(args[3]), &val<mud::Material>(args[4]), val<size_t>(args[5]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "image", var(mud::Image256()) }, { "size", var(mud::vec2()) }, { "flags", var(uint32_t(0)), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t(0)), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "sprite", funcptr<mud::Item&(*)(mud::Gnode&, const mud::Image256&, const mud::vec2&, uint32_t, mud::Material*, size_t)>(&mud::gfx::sprite), func, params, Ref(type<mud::Item>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::item(val<mud::Gnode>(args[0]), val<mud::Model>(args[1]), val<uint32_t>(args[2]), &val<mud::Material>(args[3]), val<size_t>(args[4]), val<array<mud::mat4>>(args[5]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "model", Ref(type<mud::Model>()) }, { "flags", var(uint32_t(0)), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t(0)), Param::Default }, { "transforms", var(array<mud::mat4>{}), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "item", funcptr<mud::Item&(*)(mud::Gnode&, const mud::Model&, uint32_t, mud::Material*, size_t, array<mud::mat4>)>(&mud::gfx::item), func, params, Ref(type<mud::Item>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::prefab(val<mud::Gnode>(args[0]), val<mud::Prefab>(args[1]), val<bool>(args[2]), val<uint32_t>(args[3]), &val<mud::Material>(args[4]), val<size_t>(args[5]), val<array<mud::mat4>>(args[6])); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "prefab", Ref(type<mud::Prefab>()) }, { "transform", var(bool(true)), Param::Default }, { "flags", var(uint32_t(0)), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t(0)), Param::Default }, { "transforms", var(array<mud::mat4>{}), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "prefab", funcptr<void(*)(mud::Gnode&, const mud::Prefab&, bool, uint32_t, mud::Material*, size_t, array<mud::mat4>)>(&mud::gfx::prefab), func, params, Var() };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(mud::gfx::model(val<mud::Gnode>(args[0]), val<string>(args[1]), val<uint32_t>(args[2]), &val<mud::Material>(args[3]), val<size_t>(args[4]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "name", var(string()) }, { "flags", var(uint32_t(0)), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t(0)), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "model", funcptr<mud::Item*(*)(mud::Gnode&, const string&, uint32_t, mud::Material*, size_t)>(&mud::gfx::model), func, params, Ref(type<mud::Item>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::animated(val<mud::Gnode>(args[0]), val<mud::Item>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "item", Ref(type<mud::Item>()) } };
			static Function f = { &namspc({ "mud", "gfx" }), "animated", funcptr<mud::Animated&(*)(mud::Gnode&, mud::Item&)>(&mud::gfx::animated), func, params, Ref(type<mud::Animated>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Particles>(result) = mud::gfx::particles(val<mud::Gnode>(args[0]), val<mud::ParticleFlow>(args[1]), val<uint32_t>(args[2]), val<size_t>(args[3])); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "emitter", var(mud::ParticleFlow()) }, { "flags", var(uint32_t(0)), Param::Default }, { "instances", var(size_t(0)), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "particles", funcptr<mud::Particles&(*)(mud::Gnode&, const mud::ParticleFlow&, uint32_t, size_t)>(&mud::gfx::particles), func, params, var(mud::Particles()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::light(val<mud::Gnode>(args[0]), val<mud::LightType>(args[1]), val<bool>(args[2]), val<mud::Colour>(args[3]), val<float>(args[4]), val<float>(args[5]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "type", var(mud::LightType()) }, { "shadows", var(bool()) }, { "colour", var(mud::Colour()) }, { "range", var(float(0.f)), Param::Default }, { "attenuation", var(float(0.5f)), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "light", funcptr<mud::Light&(*)(mud::Gnode&, mud::LightType, bool, mud::Colour, float, float)>(&mud::gfx::light), func, params, Ref(type<mud::Light>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::sun_light(val<mud::Gnode>(args[0]), val<float>(args[1]), val<float>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "azimuth", var(float()) }, { "elevation", var(float()) } };
			static Function f = { &namspc({ "mud", "gfx" }), "sun_light", funcptr<mud::Light&(*)(mud::Gnode&, float, float)>(&mud::gfx::sun_light), func, params, Ref(type<mud::Light>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::radiance(val<mud::Gnode>(args[0]), val<string>(args[1]), val<mud::BackgroundMode>(args[2])); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "texture", var(string()) }, { "background", var(mud::BackgroundMode()) } };
			static Function f = { &namspc({ "mud", "gfx" }), "radiance", funcptr<void(*)(mud::Gnode&, const string&, mud::BackgroundMode)>(&mud::gfx::radiance), func, params, Var() };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_gfx::mud_gfx()
		: Module("mud::gfx", { &mud_infra::m(), &mud_jobs::m(), &mud_type::m(), &mud_pool::m(), &mud_math::m(), &mud_geom::m(), &mud_ctx::m(), &mud_bgfx::m() })
	{
		// setup reflection meta data
		mud_gfx_meta(*this);
	}
}

#ifdef MUD_GFX_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx::m();
}
#endif
