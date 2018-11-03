

#pragma once

#ifndef MUD_MODULES
#include <meta/gfx/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_gfx_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::BackgroundMode>(), &namspc({ "mud" }), "BackgroundMode", sizeof(mud::BackgroundMode), TypeClass::Enum };
        static Enum enu = { type<mud::BackgroundMode>(),
            true,
            { "None", "Panorama", "Radiance", "Custom" },
            { 0, 1, 2, 3 },
            { var(mud::BackgroundMode::None), var(mud::BackgroundMode::Panorama), var(mud::BackgroundMode::Radiance), var(mud::BackgroundMode::Custom) }
        };
        meta_enum<mud::BackgroundMode>();
    }
    
    {
        static Meta meta = { type<mud::BlendMode>(), &namspc({ "mud" }), "BlendMode", sizeof(mud::BlendMode), TypeClass::Enum };
        static Enum enu = { type<mud::BlendMode>(),
            true,
            { "Mix", "Add", "Sub", "Mul", "Normal", "Alpha" },
            { 0, 1, 2, 3, 4, 5 },
            { var(mud::BlendMode::Mix), var(mud::BlendMode::Add), var(mud::BlendMode::Sub), var(mud::BlendMode::Mul), var(mud::BlendMode::Normal), var(mud::BlendMode::Alpha) }
        };
        meta_enum<mud::BlendMode>();
    }
    
    {
        static Meta meta = { type<mud::CullMode>(), &namspc({ "mud" }), "CullMode", sizeof(mud::CullMode), TypeClass::Enum };
        static Enum enu = { type<mud::CullMode>(),
            true,
            { "None", "Front", "Back" },
            { 0, 1, 2 },
            { var(mud::CullMode::None), var(mud::CullMode::Front), var(mud::CullMode::Back) }
        };
        meta_enum<mud::CullMode>();
    }
    
    {
        static Meta meta = { type<mud::DepthDraw>(), &namspc({ "mud" }), "DepthDraw", sizeof(mud::DepthDraw), TypeClass::Enum };
        static Enum enu = { type<mud::DepthDraw>(),
            true,
            { "Enabled", "Disabled" },
            { 0, 1 },
            { var(mud::DepthDraw::Enabled), var(mud::DepthDraw::Disabled) }
        };
        meta_enum<mud::DepthDraw>();
    }
    
    {
        static Meta meta = { type<mud::DepthTest>(), &namspc({ "mud" }), "DepthTest", sizeof(mud::DepthTest), TypeClass::Enum };
        static Enum enu = { type<mud::DepthTest>(),
            true,
            { "Enabled", "Disabled" },
            { 0, 1 },
            { var(mud::DepthTest::Enabled), var(mud::DepthTest::Disabled) }
        };
        meta_enum<mud::DepthTest>();
    }
    
    {
        static Meta meta = { type<mud::EmitterFlow>(), &namspc({ "mud" }), "EmitterFlow", sizeof(mud::EmitterFlow), TypeClass::Enum };
        static Enum enu = { type<mud::EmitterFlow>(),
            true,
            { "Outward", "Absolute" },
            { 0, 1 },
            { var(mud::EmitterFlow::Outward), var(mud::EmitterFlow::Absolute) }
        };
        meta_enum<mud::EmitterFlow>();
    }
    
    {
        static Meta meta = { type<mud::Interpolation>(), &namspc({ "mud" }), "Interpolation", sizeof(mud::Interpolation), TypeClass::Enum };
        static Enum enu = { type<mud::Interpolation>(),
            true,
            { "Nearest", "Linear", "Cubic" },
            { 0, 1, 2 },
            { var(mud::Interpolation::Nearest), var(mud::Interpolation::Linear), var(mud::Interpolation::Cubic) }
        };
        meta_enum<mud::Interpolation>();
    }
    
    {
        static Meta meta = { type<mud::IsometricAngle>(), &namspc({ "mud" }), "IsometricAngle", sizeof(mud::IsometricAngle), TypeClass::Enum };
        static Enum enu = { type<mud::IsometricAngle>(),
            false,
            { "NORTH", "SOUTH", "EAST", "WEST" },
            { 1, 2, 256, 512 },
            { var(mud::NORTH), var(mud::SOUTH), var(mud::EAST), var(mud::WEST) }
        };
        meta_enum<mud::IsometricAngle>();
    }
    
    {
        static Meta meta = { type<mud::ItemShadow>(), &namspc({ "mud" }), "ItemShadow", sizeof(mud::ItemShadow), TypeClass::Enum };
        static Enum enu = { type<mud::ItemShadow>(),
            true,
            { "Default", "DoubleSided" },
            { 0, 1 },
            { var(mud::ItemShadow::Default), var(mud::ItemShadow::DoubleSided) }
        };
        meta_enum<mud::ItemShadow>();
    }
    
    {
        static Meta meta = { type<mud::LightType>(), &namspc({ "mud" }), "LightType", sizeof(mud::LightType), TypeClass::Enum };
        static Enum enu = { type<mud::LightType>(),
            true,
            { "Direct", "Point", "Spot", "Count" },
            { 0, 1, 2, 3 },
            { var(mud::LightType::Direct), var(mud::LightType::Point), var(mud::LightType::Spot), var(mud::LightType::Count) }
        };
        meta_enum<mud::LightType>();
    }
    
    {
        static Meta meta = { type<mud::MSAA>(), &namspc({ "mud" }), "MSAA", sizeof(mud::MSAA), TypeClass::Enum };
        static Enum enu = { type<mud::MSAA>(),
            true,
            { "Disabled", "X2", "X4", "X8", "X16" },
            { 0, 1, 2, 3, 4 },
            { var(mud::MSAA::Disabled), var(mud::MSAA::X2), var(mud::MSAA::X4), var(mud::MSAA::X8), var(mud::MSAA::X16) }
        };
        meta_enum<mud::MSAA>();
    }
    
    {
        static Meta meta = { type<mud::MaterialFlag>(), &namspc({ "mud" }), "MaterialFlag", sizeof(mud::MaterialFlag), TypeClass::Enum };
        static Enum enu = { type<mud::MaterialFlag>(),
            true,
            { "TriplanarUV1", "TriplanarUV2", "Count" },
            { 0, 1, 2 },
            { var(mud::MaterialFlag::TriplanarUV1), var(mud::MaterialFlag::TriplanarUV2), var(mud::MaterialFlag::Count) }
        };
        meta_enum<mud::MaterialFlag>();
    }
    
    {
        static Meta meta = { type<mud::Month>(), &namspc({ "mud" }), "Month", sizeof(mud::Month), TypeClass::Enum };
        static Enum enu = { type<mud::Month>(),
            true,
            { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" },
            { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 },
            { var(mud::Month::January), var(mud::Month::February), var(mud::Month::March), var(mud::Month::April), var(mud::Month::May), var(mud::Month::June), var(mud::Month::July), var(mud::Month::August), var(mud::Month::September), var(mud::Month::October), var(mud::Month::November), var(mud::Month::December) }
        };
        meta_enum<mud::Month>();
    }
    
    {
        static Meta meta = { type<mud::PbrDiffuseMode>(), &namspc({ "mud" }), "PbrDiffuseMode", sizeof(mud::PbrDiffuseMode), TypeClass::Enum };
        static Enum enu = { type<mud::PbrDiffuseMode>(),
            true,
            { "Lambert", "LambertHalf", "OrenNayar", "Burley", "Toon" },
            { 0, 1, 2, 3, 4 },
            { var(mud::PbrDiffuseMode::Lambert), var(mud::PbrDiffuseMode::LambertHalf), var(mud::PbrDiffuseMode::OrenNayar), var(mud::PbrDiffuseMode::Burley), var(mud::PbrDiffuseMode::Toon) }
        };
        meta_enum<mud::PbrDiffuseMode>();
    }
    
    {
        static Meta meta = { type<mud::PbrSpecularMode>(), &namspc({ "mud" }), "PbrSpecularMode", sizeof(mud::PbrSpecularMode), TypeClass::Enum };
        static Enum enu = { type<mud::PbrSpecularMode>(),
            true,
            { "SchlickGGX", "Blinn", "Phong", "Toon", "Disabled" },
            { 0, 1, 2, 3, 4 },
            { var(mud::PbrSpecularMode::SchlickGGX), var(mud::PbrSpecularMode::Blinn), var(mud::PbrSpecularMode::Phong), var(mud::PbrSpecularMode::Toon), var(mud::PbrSpecularMode::Disabled) }
        };
        meta_enum<mud::PbrSpecularMode>();
    }
    
    {
        static Meta meta = { type<mud::PrefabType>(), &namspc({ "mud" }), "PrefabType", sizeof(mud::PrefabType), TypeClass::Enum };
        static Enum enu = { type<mud::PrefabType>(),
            true,
            { "None", "Item", "Model", "Shape", "Particles", "Light" },
            { 0, 1, 2, 3, 4, 5 },
            { var(mud::PrefabType::None), var(mud::PrefabType::Item), var(mud::PrefabType::Model), var(mud::PrefabType::Shape), var(mud::PrefabType::Particles), var(mud::PrefabType::Light) }
        };
        meta_enum<mud::PrefabType>();
    }
    
    {
        static Meta meta = { type<mud::ShaderType>(), &namspc({ "mud" }), "ShaderType", sizeof(mud::ShaderType), TypeClass::Enum };
        static Enum enu = { type<mud::ShaderType>(),
            true,
            { "Fragment", "Vertex", "Count" },
            { 0, 1, 2 },
            { var(mud::ShaderType::Fragment), var(mud::ShaderType::Vertex), var(mud::ShaderType::Count) }
        };
        meta_enum<mud::ShaderType>();
    }
    
    {
        static Meta meta = { type<mud::Shading>(), &namspc({ "mud" }), "Shading", sizeof(mud::Shading), TypeClass::Enum };
        static Enum enu = { type<mud::Shading>(),
            true,
            { "Wireframe", "Unshaded", "Shaded", "Volume", "Clear" },
            { 0, 1, 2, 3, 4 },
            { var(mud::Shading::Wireframe), var(mud::Shading::Unshaded), var(mud::Shading::Shaded), var(mud::Shading::Volume), var(mud::Shading::Clear) }
        };
        meta_enum<mud::Shading>();
    }
    
    {
        static Meta meta = { type<mud::ShadowFlags>(), &namspc({ "mud" }), "ShadowFlags", sizeof(mud::ShadowFlags), TypeClass::Enum };
        static Enum enu = { type<mud::ShadowFlags>(),
            false,
            { "CSM_Stabilize", "CSM_Optimize", "CSM_BlendSplits" },
            { 1, 2, 4 },
            { var(mud::CSM_Stabilize), var(mud::CSM_Optimize), var(mud::CSM_BlendSplits) }
        };
        meta_enum<mud::ShadowFlags>();
    }
    
    {
        static Meta meta = { type<mud::TextureChannel>(), &namspc({ "mud" }), "TextureChannel", sizeof(mud::TextureChannel), TypeClass::Enum };
        static Enum enu = { type<mud::TextureChannel>(),
            true,
            { "Red", "Green", "Blue", "Alpha", "All" },
            { 0, 1, 2, 3, 4 },
            { var(mud::TextureChannel::Red), var(mud::TextureChannel::Green), var(mud::TextureChannel::Blue), var(mud::TextureChannel::Alpha), var(mud::TextureChannel::All) }
        };
        meta_enum<mud::TextureChannel>();
    }
    
    {
        static Meta meta = { type<mud::TextureHint>(), &namspc({ "mud" }), "TextureHint", sizeof(mud::TextureHint), TypeClass::Enum };
        static Enum enu = { type<mud::TextureHint>(),
            true,
            { "Black", "White", "Normal" },
            { 0, 1, 2 },
            { var(mud::TextureHint::Black), var(mud::TextureHint::White), var(mud::TextureHint::Normal) }
        };
        meta_enum<mud::TextureHint>();
    }
    
    {
        static Meta meta = { type<mud::TextureSampler>(), &namspc({ "mud" }), "TextureSampler", sizeof(mud::TextureSampler), TypeClass::Enum };
        static Enum enu = { type<mud::TextureSampler>(),
            true,
            { "Source0", "Source1", "Source2", "Source3", "SourceDepth", "Color", "Albedo", "Metallic", "Roughness", "Emissive", "Normal", "AO", "Depth", "Skeleton", "ShadowCSM", "ShadowAtlas", "Radiance", "ReflectionProbe", "GIProbe" },
            { 0, 1, 2, 3, 3, 0, 0, 1, 2, 3, 4, 11, 12, 5, 6, 7, 8, 9, 10 },
            { var(mud::TextureSampler::Source0), var(mud::TextureSampler::Source1), var(mud::TextureSampler::Source2), var(mud::TextureSampler::Source3), var(mud::TextureSampler::SourceDepth), var(mud::TextureSampler::Color), var(mud::TextureSampler::Albedo), var(mud::TextureSampler::Metallic), var(mud::TextureSampler::Roughness), var(mud::TextureSampler::Emissive), var(mud::TextureSampler::Normal), var(mud::TextureSampler::AO), var(mud::TextureSampler::Depth), var(mud::TextureSampler::Skeleton), var(mud::TextureSampler::ShadowCSM), var(mud::TextureSampler::ShadowAtlas), var(mud::TextureSampler::Radiance), var(mud::TextureSampler::ReflectionProbe), var(mud::TextureSampler::GIProbe) }
        };
        meta_enum<mud::TextureSampler>();
    }
    
    {
        static Meta meta = { type<mud::ModelFormat>(), &namspc({ "mud" }), "ModelFormat", sizeof(mud::ModelFormat), TypeClass::Enum };
        static Enum enu = { type<mud::ModelFormat>(),
            true,
            { "obj", "gltf" },
            { 0, 1 },
            { var(mud::ModelFormat::obj), var(mud::ModelFormat::gltf) }
        };
        meta_enum<mud::ModelFormat>();
    }
    // Sequences
    {
        static Meta meta = { type<array<mud::mat4>>(), &namspc({}), "array<mud::mat4>", sizeof(array<mud::mat4>), TypeClass::Sequence };
        static Class cls = { type<array<mud::mat4>>() };
        cls.m_content = &type<mud::mat4>();
        meta_sequence<array<mud::mat4>, mud::mat4>();
    }

	{
		static Meta meta = { type<std::vector<mud::Animation*>>(), &namspc({}), "std::vector<mud::Animation*>", sizeof(std::vector<mud::Animation*>), TypeClass::Sequence };
		static Class cls = { type<std::vector<mud::Animation*>>() };
		cls.m_content = &type<mud::Animation>();
		meta_sequence<std::vector<mud::Animation*>, mud::Animation*>();
	}

	{
		static Meta meta = { type<std::vector<mud::AnimationPlay>>(), &namspc({}), "std::vector<mud::AnimationPlay>", sizeof(std::vector<mud::AnimationPlay>), TypeClass::Sequence };
		static Class cls = { type<std::vector<mud::AnimationPlay>>() };
		cls.m_content = &type<mud::AnimationPlay>();
		meta_sequence<std::vector<mud::AnimationPlay>, mud::AnimationPlay>();
	}

    {
        static Meta meta = { type<std::vector<mud::PrefabNode>>(), &namspc({}), "std::vector<mud::PrefabNode>", sizeof(std::vector<mud::PrefabNode>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::PrefabNode>>() };
        cls.m_content = &type<mud::PrefabNode>();
        meta_sequence<std::vector<mud::PrefabNode>, mud::PrefabNode>();
    }
    
    
    


	// mud::AnimationPlay
	{
		static Meta meta = { type<mud::AnimationPlay>(), &namspc({ "mud" }), "AnimationPlay", sizeof(mud::AnimationPlay), TypeClass::Struct };
		static Class cls = { type<mud::AnimationPlay>(),
			// bases
		{},
		{},
			// constructors
		{
		},
		// copy constructor
		{
			{ type<mud::AnimationPlay>(), [](Ref ref, Ref other) { new(&val<mud::AnimationPlay>(ref)) mud::AnimationPlay(val<mud::AnimationPlay>(other)); } }
		},
			// members
		{
			{ type<mud::AnimationPlay>(), member_address(&mud::AnimationPlay::m_animation), type<mud::Animation>(), "animation", Ref(type<mud::Animation>()), Member::Flags(Member::Pointer | Member::Link), nullptr },
			{ type<mud::AnimationPlay>(), member_address(&mud::AnimationPlay::m_loop), type<bool>(), "loop", var(bool(true)), Member::Value, nullptr },
			{ type<mud::AnimationPlay>(), member_address(&mud::AnimationPlay::m_speed), type<float>(), "speed", var(float(1.f)), Member::Value, nullptr },
			{ type<mud::AnimationPlay>(), member_address(&mud::AnimationPlay::m_transient), type<bool>(), "transient", var(bool(false)), Member::Value, nullptr },
			{ type<mud::AnimationPlay>(), member_address(&mud::AnimationPlay::m_fadeout), type<float>(), "fadeout", var(float(0.f)), Member::Value, nullptr },
			{ type<mud::AnimationPlay>(), member_address(&mud::AnimationPlay::m_fadeout_left), type<float>(), "fadeout_left", var(float(0.f)), Member::Value, nullptr },
			{ type<mud::AnimationPlay>(), member_address(&mud::AnimationPlay::m_cursor), type<float>(), "cursor", var(float(0.f)), Member::Value, nullptr },
			{ type<mud::AnimationPlay>(), member_address(&mud::AnimationPlay::m_ended), type<bool>(), "ended", var(bool(false)), Member::Value, nullptr }
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
		static Meta meta = { type<mud::AnimationTrack>(), &namspc({ "mud" }), "AnimationTrack", sizeof(mud::AnimationTrack), TypeClass::Object };
		static Class cls = { type<mud::AnimationTrack>(),
			// bases
		{},
		{},
			// constructors
		{
		},
		// copy constructor
		{
		},
		// members
		{
			{ type<mud::AnimationTrack>(), member_address(&mud::AnimationTrack::m_animation), type<mud::Animation>(), "animation", Ref(type<mud::Animation>()), Member::Flags(Member::Pointer | Member::Link), nullptr },
			{ type<mud::AnimationTrack>(), member_address(&mud::AnimationTrack::m_node), type<size_t>(), "node", var(size_t()), Member::Value, nullptr },
			{ type<mud::AnimationTrack>(), member_address(&mud::AnimationTrack::m_node_name), type<std::string>(), "node_name", var(std::string()), Member::Value, nullptr },
			{ type<mud::AnimationTrack>(), member_address(&mud::AnimationTrack::m_member), type<mud::Member>(), "member", Ref(type<mud::Member>()), Member::Flags(Member::Pointer | Member::Link), nullptr },
			{ type<mud::AnimationTrack>(), member_address(&mud::AnimationTrack::m_length), type<float>(), "length", var(float(0.f)), Member::Value, nullptr },
			{ type<mud::AnimationTrack>(), member_address(&mud::AnimationTrack::m_interpolation), type<mud::Interpolation>(), "interpolation", var(mud::Interpolation()), Member::Value, nullptr }
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

    
        
    // mud::AnimatedTrack
    {
        static Meta meta = { type<mud::AnimatedTrack>(), &namspc({ "mud" }), "AnimatedTrack", sizeof(mud::AnimatedTrack), TypeClass::Struct };
        static Class cls = { type<mud::AnimatedTrack>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::AnimatedTrack>(), [](Ref ref, Ref other) { new(&val<mud::AnimatedTrack>(ref)) mud::AnimatedTrack(val<mud::AnimatedTrack>(other)); } }
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
        static Meta meta = { type<mud::Animation>(), &namspc({ "mud" }), "Animation", sizeof(mud::Animation), TypeClass::Object };
        static Class cls = { type<mud::Animation>(),
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
        
        
        
        
        meta_class<mud::Animation>();
    }
    
    
    
        
    // mud::AnimationPlay
    {
        static Meta meta = { type<mud::AnimationPlay>(), &namspc({ "mud" }), "AnimationPlay", sizeof(mud::AnimationPlay), TypeClass::Struct };
        static Class cls = { type<mud::AnimationPlay>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::AnimationPlay>(), [](Ref ref, Ref other) { new(&val<mud::AnimationPlay>(ref)) mud::AnimationPlay(val<mud::AnimationPlay>(other)); } }
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
        
        
        
        
        meta_class<mud::AnimationPlay>();
    }
    
    
        
    // mud::AnimationTrack
    {
        static Meta meta = { type<mud::AnimationTrack>(), &namspc({ "mud" }), "AnimationTrack", sizeof(mud::AnimationTrack), TypeClass::Object };
        static Class cls = { type<mud::AnimationTrack>(),
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
        
        
        
        
        meta_class<mud::AnimationTrack>();
    }
    
    
        
    // mud::AssetStore<mud::Material>
    {
        static Meta meta = { type<mud::AssetStore<mud::Material>>(), &namspc({ "mud" }), "AssetStore<mud::Material>", sizeof(mud::AssetStore<mud::Material>), TypeClass::Object };
        static Class cls = { type<mud::AssetStore<mud::Material>>(),
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
                { type<mud::AssetStore<mud::Material>>(), "get", member_address(&mud::AssetStore<mud::Material>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Material>>(object).get(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Material>()) },
                { type<mud::AssetStore<mud::Material>>(), "create", member_address(&mud::AssetStore<mud::Material>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Material>>(object).create(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Material>()) },
                { type<mud::AssetStore<mud::Material>>(), "fetch", member_address(&mud::AssetStore<mud::Material>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Material>>(object).fetch(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Material>()) },
                { type<mud::AssetStore<mud::Material>>(), "file_at", member_address(&mud::AssetStore<mud::Material>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Material>>(object).file_at(val<cstring>(args[0]), val<cstring>(args[1]))); }, { { "path", var(cstring()) }, { "name", var(cstring()) } }, Ref(type<mud::Material>()) },
                { type<mud::AssetStore<mud::Material>>(), "file", member_address(&mud::AssetStore<mud::Material>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Material>>(object).file(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Material>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::AssetStore<mud::Material>>();
    }
    
    
        
    // mud::AssetStore<mud::Model>
    {
        static Meta meta = { type<mud::AssetStore<mud::Model>>(), &namspc({ "mud" }), "AssetStore<mud::Model>", sizeof(mud::AssetStore<mud::Model>), TypeClass::Object };
        static Class cls = { type<mud::AssetStore<mud::Model>>(),
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
                { type<mud::AssetStore<mud::Model>>(), "get", member_address(&mud::AssetStore<mud::Model>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Model>>(object).get(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Model>()) },
                { type<mud::AssetStore<mud::Model>>(), "create", member_address(&mud::AssetStore<mud::Model>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Model>>(object).create(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Model>()) },
                { type<mud::AssetStore<mud::Model>>(), "fetch", member_address(&mud::AssetStore<mud::Model>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Model>>(object).fetch(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Model>()) },
                { type<mud::AssetStore<mud::Model>>(), "file_at", member_address(&mud::AssetStore<mud::Model>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Model>>(object).file_at(val<cstring>(args[0]), val<cstring>(args[1]))); }, { { "path", var(cstring()) }, { "name", var(cstring()) } }, Ref(type<mud::Model>()) },
                { type<mud::AssetStore<mud::Model>>(), "file", member_address(&mud::AssetStore<mud::Model>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Model>>(object).file(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Model>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::AssetStore<mud::Model>>();
    }
    
    
        
    // mud::AssetStore<mud::ParticleGenerator>
    {
        static Meta meta = { type<mud::AssetStore<mud::ParticleGenerator>>(), &namspc({ "mud" }), "AssetStore<mud::ParticleGenerator>", sizeof(mud::AssetStore<mud::ParticleGenerator>), TypeClass::Object };
        static Class cls = { type<mud::AssetStore<mud::ParticleGenerator>>(),
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
                { type<mud::AssetStore<mud::ParticleGenerator>>(), "get", member_address(&mud::AssetStore<mud::ParticleGenerator>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::ParticleGenerator>>(object).get(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::ParticleGenerator>()) },
                { type<mud::AssetStore<mud::ParticleGenerator>>(), "create", member_address(&mud::AssetStore<mud::ParticleGenerator>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::ParticleGenerator>>(object).create(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::ParticleGenerator>()) },
                { type<mud::AssetStore<mud::ParticleGenerator>>(), "fetch", member_address(&mud::AssetStore<mud::ParticleGenerator>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::ParticleGenerator>>(object).fetch(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::ParticleGenerator>()) },
                { type<mud::AssetStore<mud::ParticleGenerator>>(), "file_at", member_address(&mud::AssetStore<mud::ParticleGenerator>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::ParticleGenerator>>(object).file_at(val<cstring>(args[0]), val<cstring>(args[1]))); }, { { "path", var(cstring()) }, { "name", var(cstring()) } }, Ref(type<mud::ParticleGenerator>()) },
                { type<mud::AssetStore<mud::ParticleGenerator>>(), "file", member_address(&mud::AssetStore<mud::ParticleGenerator>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::ParticleGenerator>>(object).file(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::ParticleGenerator>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::AssetStore<mud::ParticleGenerator>>();
    }
    
    
        
    // mud::AssetStore<mud::Prefab>
    {
        static Meta meta = { type<mud::AssetStore<mud::Prefab>>(), &namspc({ "mud" }), "AssetStore<mud::Prefab>", sizeof(mud::AssetStore<mud::Prefab>), TypeClass::Object };
        static Class cls = { type<mud::AssetStore<mud::Prefab>>(),
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
                { type<mud::AssetStore<mud::Prefab>>(), "get", member_address(&mud::AssetStore<mud::Prefab>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Prefab>>(object).get(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Prefab>()) },
                { type<mud::AssetStore<mud::Prefab>>(), "create", member_address(&mud::AssetStore<mud::Prefab>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Prefab>>(object).create(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Prefab>()) },
                { type<mud::AssetStore<mud::Prefab>>(), "fetch", member_address(&mud::AssetStore<mud::Prefab>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Prefab>>(object).fetch(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Prefab>()) },
                { type<mud::AssetStore<mud::Prefab>>(), "file_at", member_address(&mud::AssetStore<mud::Prefab>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Prefab>>(object).file_at(val<cstring>(args[0]), val<cstring>(args[1]))); }, { { "path", var(cstring()) }, { "name", var(cstring()) } }, Ref(type<mud::Prefab>()) },
                { type<mud::AssetStore<mud::Prefab>>(), "file", member_address(&mud::AssetStore<mud::Prefab>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Prefab>>(object).file(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Prefab>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::AssetStore<mud::Prefab>>();
    }
    
    
        
    // mud::AssetStore<mud::Program>
    {
        static Meta meta = { type<mud::AssetStore<mud::Program>>(), &namspc({ "mud" }), "AssetStore<mud::Program>", sizeof(mud::AssetStore<mud::Program>), TypeClass::Object };
        static Class cls = { type<mud::AssetStore<mud::Program>>(),
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
                { type<mud::AssetStore<mud::Program>>(), "get", member_address(&mud::AssetStore<mud::Program>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Program>>(object).get(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Program>()) },
                { type<mud::AssetStore<mud::Program>>(), "create", member_address(&mud::AssetStore<mud::Program>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Program>>(object).create(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Program>()) },
                { type<mud::AssetStore<mud::Program>>(), "fetch", member_address(&mud::AssetStore<mud::Program>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Program>>(object).fetch(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Program>()) },
                { type<mud::AssetStore<mud::Program>>(), "file_at", member_address(&mud::AssetStore<mud::Program>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Program>>(object).file_at(val<cstring>(args[0]), val<cstring>(args[1]))); }, { { "path", var(cstring()) }, { "name", var(cstring()) } }, Ref(type<mud::Program>()) },
                { type<mud::AssetStore<mud::Program>>(), "file", member_address(&mud::AssetStore<mud::Program>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Program>>(object).file(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Program>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::AssetStore<mud::Program>>();
    }
    
    
        
    // mud::AssetStore<mud::Texture>
    {
        static Meta meta = { type<mud::AssetStore<mud::Texture>>(), &namspc({ "mud" }), "AssetStore<mud::Texture>", sizeof(mud::AssetStore<mud::Texture>), TypeClass::Object };
        static Class cls = { type<mud::AssetStore<mud::Texture>>(),
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
                { type<mud::AssetStore<mud::Texture>>(), "get", member_address(&mud::AssetStore<mud::Texture>::get), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Texture>>(object).get(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Texture>()) },
                { type<mud::AssetStore<mud::Texture>>(), "create", member_address(&mud::AssetStore<mud::Texture>::create), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Texture>>(object).create(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Texture>()) },
                { type<mud::AssetStore<mud::Texture>>(), "fetch", member_address(&mud::AssetStore<mud::Texture>::fetch), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Texture>>(object).fetch(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Texture>()) },
                { type<mud::AssetStore<mud::Texture>>(), "file_at", member_address(&mud::AssetStore<mud::Texture>::file_at), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::AssetStore<mud::Texture>>(object).file_at(val<cstring>(args[0]), val<cstring>(args[1]))); }, { { "path", var(cstring()) }, { "name", var(cstring()) } }, Ref(type<mud::Texture>()) },
                { type<mud::AssetStore<mud::Texture>>(), "file", member_address(&mud::AssetStore<mud::Texture>::file), [](Ref object, array<Var> args, Var& result) { result = Ref(val<mud::AssetStore<mud::Texture>>(object).file(val<cstring>(args[0]))); }, { { "name", var(cstring()) } }, Ref(type<mud::Texture>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::AssetStore<mud::Texture>>();
    }
    


	// mud::Animated
	{
		static Meta meta = { type<mud::Animated>(), &namspc({ "mud" }), "Animated", sizeof(mud::Animated), TypeClass::Object };
		static Class cls = { type<mud::Animated>(),
		// bases
		{},
		{},
		// constructors
		{
		},
		// copy constructor
		{
		},
		// members
		{
			//{ type<mud::Animated>(), member_address(&mud::Animated::m_playing), type<std::vector<mud::AnimationPlay>>(), "playing", var(std::vector<mud::AnimationPlay>()), Member::Value, nullptr },
			{ type<mud::Animated>(), member_address(&mud::Animated::m_queue), type<std::vector<mud::Animation*>>(), "queue", var(std::vector<mud::Animation*>()), Member::Value, nullptr },
			{ type<mud::Animated>(), member_address(&mud::Animated::m_active), type<bool>(), "active", var(bool(true)), Member::Value, nullptr },
			{ type<mud::Animated>(), member_address(&mud::Animated::m_speed_scale), type<float>(), "speed_scale", var(float(1.f)), Member::Value, nullptr },
			{ type<mud::Animated>(), member_address(&mud::Animated::m_default_blend_time), type<float>(), "default_blend_time", var(float(1.f)), Member::Value, nullptr }
		},
		// methods
		{
			//{ type<mud::Animated>(), "play", member_address<void (mud::Animated::*)(const Animation&, bool, float, float, bool)>(&mud::Animated::play), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Animated>(object).play(val<mud::Animation>(args[0]), val<bool>(args[1]), val<float>(args[2]), val<float>(args[3]), val<bool>(args[4])); },{ { "animation", Ref(type<mud::Animation>()) },{ "loop", var(bool()) },{ "blend", var(float(0.f)), Param::Default },{ "speed", var(float(1.f)), Param::Default },{ "transient", var(bool(false)), Param::Default } }, Var() },
			{ type<mud::Animated>(), "play", member_address<void (mud::Animated::*)(cstring, bool, float, float, bool)>(&mud::Animated::play), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Animated>(object).play(val<cstring>(args[0]), val<bool>(args[1]), val<float>(args[2]), val<float>(args[3]), val<bool>(args[4])); },{ { "animation", var(cstring()) },{ "loop", var(bool()) },{ "blend", var(float(0.f)), Param::Default },{ "speed", var(float(1.f)), Param::Default },{ "transient", var(bool(false)), Param::Default } }, Var() },
			{ type<mud::Animated>(), "seek", member_address(&mud::Animated::seek), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Animated>(object).seek(val<float>(args[0])); },{ { "time", var(float()) } }, Var() },
			{ type<mud::Animated>(), "pause", member_address(&mud::Animated::pause), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Animated>(object).pause(); },{}, Var() },
			{ type<mud::Animated>(), "stop", member_address(&mud::Animated::stop), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Animated>(object).stop(); },{}, Var() },
			{ type<mud::Animated>(), "advance", member_address(&mud::Animated::advance), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Animated>(object).advance(val<float>(args[0])); },{ { "time", var(float()) } }, Var() },
			{ type<mud::Animated>(), "next_animation", member_address(&mud::Animated::next_animation), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Animated>(object).next_animation(); },{}, Var() },
			{ type<mud::Animated>(), "playing", member_address(&mud::Animated::playing), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<std::string>(result) = val<mud::Animated>(object).playing(); },{}, var(std::string()) }
		},
		// static members
		{
		}
		};




		meta_class<mud::Animated>();
	}
        
    // mud::Background
    {
        static Meta meta = { type<mud::Background>(), &namspc({ "mud" }), "Background", sizeof(mud::Background), TypeClass::Struct };
        static Class cls = { type<mud::Background>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Background>(), [](Ref ref, Ref other) { new(&val<mud::Background>(ref)) mud::Background(val<mud::Background>(other)); } }
            },
            // members
            {
                { type<mud::Background>(), member_address(&mud::Background::m_mode), type<mud::BackgroundMode>(), "mode", var(mud::BackgroundMode()), Member::Value, nullptr },
                { type<mud::Background>(), member_address(&mud::Background::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Background>(), member_address(&mud::Background::m_custom_program), type<mud::Program>(), "custoprogram", Ref(type<mud::Program>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
        static Meta meta = { type<mud::BaseMaterialBlock>(), &namspc({ "mud" }), "BaseMaterialBlock", sizeof(mud::BaseMaterialBlock), TypeClass::Struct };
        static Class cls = { type<mud::BaseMaterialBlock>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::BaseMaterialBlock>(), [](Ref ref, Ref other) { new(&val<mud::BaseMaterialBlock>(ref)) mud::BaseMaterialBlock(val<mud::BaseMaterialBlock>(other)); } }
            },
            // members
            {
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_blend_mode), type<mud::BlendMode>(), "blend_mode", var(mud::BlendMode()), Member::Value, nullptr },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_cull_mode), type<mud::CullMode>(), "cull_mode", var(mud::CullMode()), Member::Value, nullptr },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_depth_draw_mode), type<mud::DepthDraw>(), "depth_draw_mode", var(mud::DepthDraw()), Member::Value, nullptr },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_depth_test), type<mud::DepthTest>(), "depth_test", var(mud::DepthTest()), Member::Value, nullptr },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_uv1_scale), type<mud::vec2>(), "uv1_scale", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_uv1_offset), type<mud::vec2>(), "uv1_offset", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_uv2_scale), type<mud::vec2>(), "uv2_scale", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_uv2_offset), type<mud::vec2>(), "uv2_offset", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_is_alpha), type<bool>(), "is_alpha", var(bool(false)), Member::Value, nullptr },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_screen_filter), type<bool>(), "screen_filter", var(bool(false)), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Bone>(), &namspc({ "mud" }), "Bone", sizeof(mud::Bone), TypeClass::Struct };
        static Class cls = { type<mud::Bone>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Bone>(), [](Ref ref, Ref other) { new(&val<mud::Bone>(ref)) mud::Bone(val<mud::Bone>(other)); } }
            },
            // members
            {
                { type<mud::Bone>(), member_address(&mud::Bone::m_position), type<mud::vec3>(), "position", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Bone>(), member_address(&mud::Bone::m_rotation), type<mud::quat>(), "rotation", var(mud::quat()), Member::Value, nullptr },
                { type<mud::Bone>(), member_address(&mud::Bone::m_scale), type<mud::vec3>(), "scale", var(mud::vec3()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Camera>(), &namspc({ "mud" }), "Camera", sizeof(mud::Camera), TypeClass::Object };
        static Class cls = { type<mud::Camera>(),
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
                //{ type<mud::Camera>(), member_address(&mud::Camera::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_eye), type<mud::vec3>(), "eye", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_target), type<mud::vec3>(), "target", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_transform), type<mud::mat4>(), "transform", var(mud::mat4()), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_projection), type<mud::mat4>(), "projection", var(mud::mat4()), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_fov), type<float>(), "fov", var(float(60.f)), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_aspect), type<float>(), "aspect", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_near), type<float>(), "near", var(float(0.001f)), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_far), type<float>(), "far", var(float(100.f)), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_orthographic), type<bool>(), "orthographic", var(bool(false)), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_height), type<float>(), "height", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_optimize_ends), type<bool>(), "optimize_ends", var(bool(true)), Member::Value, nullptr },
                { type<mud::Camera>(), member_address(&mud::Camera::m_lod_offsets), type<mud::vec4>(), "lod_offsets", var(mud::vec4()), Member::Value, nullptr }
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
    
    
    
    
        
    // mud::DepthParams
    {
        static Meta meta = { type<mud::DepthParams>(), &namspc({ "mud" }), "DepthParams", sizeof(mud::DepthParams), TypeClass::Struct };
        static Class cls = { type<mud::DepthParams>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::DepthParams>(), [](Ref ref, Ref other) { new(&val<mud::DepthParams>(ref)) mud::DepthParams(val<mud::DepthParams>(other)); } }
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
        static Meta meta = { type<mud::Environment>(), &namspc({ "mud" }), "Environment", sizeof(mud::Environment), TypeClass::Struct };
        static Class cls = { type<mud::Environment>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Environment>(), [](Ref ref, Ref other) { new(&val<mud::Environment>(ref)) mud::Environment(val<mud::Environment>(other)); } }
            },
            // members
            {
                { type<mud::Environment>(), member_address(&mud::Environment::m_background), type<mud::Background>(), "background", var(mud::Background()), Member::Value, nullptr },
                { type<mud::Environment>(), member_address(&mud::Environment::m_radiance), type<mud::Radiance>(), "radiance", var(mud::Radiance()), Member::Value, nullptr },
                { type<mud::Environment>(), member_address(&mud::Environment::m_sun), type<mud::Sun>(), "sun", var(mud::Sun()), Member::Value, nullptr },
                { type<mud::Environment>(), member_address(&mud::Environment::m_fog), type<mud::Fog>(), "fog", var(mud::Fog()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Filter>(), &namspc({ "mud" }), "Filter", sizeof(mud::Filter), TypeClass::Object };
        static Class cls = { type<mud::Filter>(),
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
        static Meta meta = { type<mud::Fog>(), &namspc({ "mud" }), "Fog", sizeof(mud::Fog), TypeClass::Struct };
        static Class cls = { type<mud::Fog>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Fog>(), [](Ref ref, Ref other) { new(&val<mud::Fog>(ref)) mud::Fog(val<mud::Fog>(other)); } }
            },
            // members
            {
                { type<mud::Fog>(), member_address(&mud::Fog::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_density), type<float>(), "density", var(float(0.01f)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_depth), type<bool>(), "depth", var(bool(false)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_depth_begin), type<float>(), "depth_begin", var(float(0.f)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_depth_curve), type<float>(), "depth_curve", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_height), type<bool>(), "height", var(bool(false)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_height_min), type<float>(), "height_min", var(float(0.f)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_height_max), type<float>(), "height_max", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_height_curve), type<float>(), "height_curve", var(float(0.1f)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_transmit), type<bool>(), "transmit", var(bool(false)), Member::Value, nullptr },
                { type<mud::Fog>(), member_address(&mud::Fog::m_transmit_curve), type<float>(), "transmit_curve", var(float(1.f)), Member::Value, nullptr }
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
        static Meta meta = { type<mud::FrameBuffer>(), &namspc({ "mud" }), "FrameBuffer", sizeof(mud::FrameBuffer), TypeClass::Object };
        static Class cls = { type<mud::FrameBuffer>(),
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
        static Meta meta = { type<mud::FresnelMaterialBlock>(), &namspc({ "mud" }), "FresnelMaterialBlock", sizeof(mud::FresnelMaterialBlock), TypeClass::Struct };
        static Class cls = { type<mud::FresnelMaterialBlock>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::FresnelMaterialBlock>(), [](Ref ref, Ref other) { new(&val<mud::FresnelMaterialBlock>(ref)) mud::FresnelMaterialBlock(val<mud::FresnelMaterialBlock>(other)); } }
            },
            // members
            {
                { type<mud::FresnelMaterialBlock>(), member_address(&mud::FresnelMaterialBlock::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Value, nullptr },
                { type<mud::FresnelMaterialBlock>(), member_address(&mud::FresnelMaterialBlock::m_value), type<mud::MaterialParam<mud::Colour>>(), "value", var(mud::MaterialParam<mud::Colour>()), Member::Value, nullptr },
                { type<mud::FresnelMaterialBlock>(), member_address(&mud::FresnelMaterialBlock::m_fresnel_scale), type<float>(), "fresnel_scale", var(float(1.f)), Member::Value, nullptr },
                { type<mud::FresnelMaterialBlock>(), member_address(&mud::FresnelMaterialBlock::m_fresnel_bias), type<float>(), "fresnel_bias", var(float(0.01f)), Member::Value, nullptr },
                { type<mud::FresnelMaterialBlock>(), member_address(&mud::FresnelMaterialBlock::m_fresnel_power), type<float>(), "fresnel_power", var(float(5.f)), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Frustum>(), &namspc({ "mud" }), "Frustum", sizeof(mud::Frustum), TypeClass::Object };
        static Class cls = { type<mud::Frustum>(),
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
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_fov), type<float>(), "fov", var(float(60.f)), Member::Value, nullptr },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_aspect), type<float>(), "aspect", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_near), type<float>(), "near", var(float()), Member::Value, nullptr },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_far), type<float>(), "far", var(float()), Member::Value, nullptr },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_center), type<mud::vec3>(), "center", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_radius), type<float>(), "radius", var(float()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::FrustumSlice>(), &namspc({ "mud" }), "FrustumSlice", sizeof(mud::FrustumSlice), TypeClass::Struct };
        static Class cls = { type<mud::FrustumSlice>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::FrustumSlice>(), [](Ref ref, Ref other) { new(&val<mud::FrustumSlice>(ref)) mud::FrustumSlice(val<mud::FrustumSlice>(other)); } }
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
        static Meta meta = { type<mud::GfxBlock>(), &namspc({ "mud" }), "GfxBlock", sizeof(mud::GfxBlock), TypeClass::Object };
        static Class cls = { type<mud::GfxBlock>(),
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
                { type<mud::GfxBlock>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxBlock>(object).m_type); } },
                { type<mud::GfxBlock>(), member_address(&mud::GfxBlock::m_index), type<uint8_t>(), "index", var(uint8_t()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::GfxContext>(), &namspc({ "mud" }), "GfxContext", sizeof(mud::GfxContext), TypeClass::Object };
        static Class cls = { type<mud::GfxContext>(),
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
        static Meta meta = { type<mud::GfxSystem>(), &namspc({ "mud" }), "GfxSystem", sizeof(mud::GfxSystem), TypeClass::Object };
        static Class cls = { type<mud::GfxSystem>(),
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
                { type<mud::GfxSystem>(), member_address(&mud::GfxSystem::textures), type<mud::AssetStore<mud::Texture>>(), "textures", Ref(type<mud::AssetStore<mud::Texture>>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).textures()); } },
                { type<mud::GfxSystem>(), member_address(&mud::GfxSystem::programs), type<mud::AssetStore<mud::Program>>(), "programs", Ref(type<mud::AssetStore<mud::Program>>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).programs()); } },
                { type<mud::GfxSystem>(), member_address(&mud::GfxSystem::materials), type<mud::AssetStore<mud::Material>>(), "materials", Ref(type<mud::AssetStore<mud::Material>>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).materials()); } },
                { type<mud::GfxSystem>(), member_address(&mud::GfxSystem::models), type<mud::AssetStore<mud::Model>>(), "models", Ref(type<mud::AssetStore<mud::Model>>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).models()); } },
                { type<mud::GfxSystem>(), member_address(&mud::GfxSystem::particles), type<mud::AssetStore<mud::ParticleGenerator>>(), "particles", Ref(type<mud::AssetStore<mud::ParticleGenerator>>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).particles()); } },
                { type<mud::GfxSystem>(), member_address(&mud::GfxSystem::prefabs), type<mud::AssetStore<mud::Prefab>>(), "prefabs", Ref(type<mud::AssetStore<mud::Prefab>>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::GfxSystem>(object).prefabs()); } }
            },
            // methods
            {
				{ type<mud::GfxSystem>(), "add_resource_path", member_address(&mud::GfxSystem::add_resource_path), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::GfxSystem>(object).add_resource_path(val<cstring>(args[0])); },{ { "path", var(cstring()) } }, Ref() },
				{ type<mud::GfxSystem>(), "fetch_symbol", member_address(&mud::GfxSystem::fetch_symbol), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::GfxSystem>(object).fetch_symbol(val<mud::Symbol>(args[0]), val<mud::Shape>(args[1]), val<mud::DrawMode>(args[2]))); }, { { "symbol", Ref(type<mud::Symbol>()) }, { "shape", Ref(type<mud::Shape>()) }, { "draw_mode", var(mud::DrawMode()) } }, Ref(type<mud::Model>()) },
				{ type<mud::GfxSystem>(), "fetch_symbol_material", member_address(&mud::GfxSystem::fetch_symbol_material), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::GfxSystem>(object).fetch_symbol_material(val<mud::Symbol>(args[0]), val<mud::DrawMode>(args[1]))); }, { { "symbol", Ref(type<mud::Symbol>()) }, { "draw_mode", var(mud::DrawMode()) } }, Ref(type<mud::Material>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::GfxSystem>();
    }
    
    
    
        
    // mud::ImmediateDraw
    {
        static Meta meta = { type<mud::ImmediateDraw>(), &namspc({ "mud" }), "ImmediateDraw", sizeof(mud::ImmediateDraw), TypeClass::Object };
        static Class cls = { type<mud::ImmediateDraw>(),
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
    
    
        
    // mud::Item
    {
        static Meta meta = { type<mud::Item>(), &namspc({ "mud" }), "Item", sizeof(mud::Item), TypeClass::Object };
        static Class cls = { type<mud::Item>(),
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
                { type<mud::Item>(), member_address(&mud::Item::m_node), type<mud::Node3>(), "node", Ref(type<mud::Node3>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Item>(), member_address(&mud::Item::m_model), type<mud::Model>(), "model", Ref(type<mud::Model>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Item>(), member_address(&mud::Item::m_flags), type<uint32_t>(), "flags", var(uint32_t()), Member::Value, nullptr },
                { type<mud::Item>(), member_address(&mud::Item::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Item>(), member_address(&mud::Item::m_material), type<mud::Material>(), "material", Ref(type<mud::Material>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Item>(), member_address(&mud::Item::m_visible), type<bool>(), "visible", var(bool(true)), Member::Value, nullptr },
                { type<mud::Item>(), member_address(&mud::Item::m_shadow), type<mud::ItemShadow>(), "shadow", var(mud::ItemShadow()), Member::Value, nullptr },
                { type<mud::Item>(), member_address(&mud::Item::m_rig), type<mud::Rig>(), "rig", Ref(type<mud::Rig>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
        static Meta meta = { type<mud::Joint>(), &namspc({ "mud" }), "Joint", sizeof(mud::Joint), TypeClass::Struct };
        static Class cls = { type<mud::Joint>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Joint>(), [](Ref ref, Ref other) { new(&val<mud::Joint>(ref)) mud::Joint(val<mud::Joint>(other)); } }
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
        static Meta meta = { type<mud::Light>(), &namspc({ "mud" }), "Light", sizeof(mud::Light), TypeClass::Object };
        static Class cls = { type<mud::Light>(),
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
                { type<mud::Light>(), Address(), type<mud::Node3>(), "node", Ref(type<mud::Node3>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Light>(object).m_node); } },
                { type<mud::Light>(), member_address(&mud::Light::m_type), type<mud::LightType>(), "type", var(mud::LightType()), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_visible), type<bool>(), "visible", var(bool(true)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_range), type<float>(), "range", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_energy), type<float>(), "energy", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_specular), type<float>(), "specular", var(float(0.5f)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_attenuation), type<float>(), "attenuation", var(float(0.5f)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_shadows), type<bool>(), "shadows", var(bool(false)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_colour), type<mud::Colour>(), "shadow_colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_range), type<float>(), "shadow_range", var(float(100.f)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_layers), type<uint32_t>(), "layers", var(uint32_t(0xFFFFFFFF)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_last_render), type<uint32_t>(), "last_render", var(uint32_t()), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_last_update), type<uint32_t>(), "last_update", var(uint32_t()), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_spot_angle), type<float>(), "spot_angle", var(float(45.f)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_spot_attenuation), type<float>(), "spot_attenuation", var(float(0.5f)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_flags), type<mud::ShadowFlags>(), "shadow_flags", var(mud::ShadowFlags()), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_num_splits), type<uint8_t>(), "shadow_nusplits", var(uint8_t()), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_split_distribution), type<float>(), "shadow_split_distribution", var(float(0.6f)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_normal_bias), type<float>(), "shadow_normal_bias", var(float(0.1f)), Member::Value, nullptr },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_bias), type<float>(), "shadow_bias", var(float(0.f)), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Material>(), &namspc({ "mud" }), "Material", sizeof(mud::Material), TypeClass::Object };
        static Class cls = { type<mud::Material>(),
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
                { type<mud::Material>(), member_address(&mud::Material::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value, nullptr },
                { type<mud::Material>(), member_address(&mud::Material::m_builtin), type<bool>(), "builtin", var(bool(false)), Member::Value, nullptr },
                { type<mud::Material>(), member_address(&mud::Material::m_program), type<mud::Program>(), "program", Ref(type<mud::Program>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Material>(), member_address(&mud::Material::m_base_block), type<mud::BaseMaterialBlock>(), "base_block", var(mud::BaseMaterialBlock()), Member::Value, nullptr },
                { type<mud::Material>(), member_address(&mud::Material::m_unshaded_block), type<mud::UnshadedMaterialBlock>(), "unshaded_block", var(mud::UnshadedMaterialBlock()), Member::Value, nullptr },
                { type<mud::Material>(), member_address(&mud::Material::m_pbr_block), type<mud::PbrMaterialBlock>(), "pbr_block", var(mud::PbrMaterialBlock()), Member::Value, nullptr },
                { type<mud::Material>(), member_address(&mud::Material::m_fresnel_block), type<mud::FresnelMaterialBlock>(), "fresnel_block", var(mud::FresnelMaterialBlock()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::MaterialParam<float>>(), &namspc({ "mud" }), "MaterialParam<float>", sizeof(mud::MaterialParam<float>), TypeClass::Struct };
        static Class cls = { type<mud::MaterialParam<float>>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::MaterialParam<float>>(), [](Ref ref, Ref other) { new(&val<mud::MaterialParam<float>>(ref)) mud::MaterialParam<float>(val<mud::MaterialParam<float>>(other)); } }
            },
            // members
            {
                { type<mud::MaterialParam<float>>(), member_address(&mud::MaterialParam<float>::m_value), type<float>(), "value", var(float()), Member::Value, nullptr },
                { type<mud::MaterialParam<float>>(), member_address(&mud::MaterialParam<float>::m_texture), type<mud::Texture>(), "texture", Ref(type<mud::Texture>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::MaterialParam<float>>(), member_address(&mud::MaterialParam<float>::m_channel), type<mud::TextureChannel>(), "channel", var(mud::TextureChannel()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::MaterialParam<mud::Colour>>(), &namspc({ "mud" }), "MaterialParam<mud::Colour>", sizeof(mud::MaterialParam<mud::Colour>), TypeClass::Struct };
        static Class cls = { type<mud::MaterialParam<mud::Colour>>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::MaterialParam<mud::Colour>>(), [](Ref ref, Ref other) { new(&val<mud::MaterialParam<mud::Colour>>(ref)) mud::MaterialParam<mud::Colour>(val<mud::MaterialParam<mud::Colour>>(other)); } }
            },
            // members
            {
                { type<mud::MaterialParam<mud::Colour>>(), member_address(&mud::MaterialParam<mud::Colour>::m_value), type<mud::Colour>(), "value", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::MaterialParam<mud::Colour>>(), member_address(&mud::MaterialParam<mud::Colour>::m_texture), type<mud::Texture>(), "texture", Ref(type<mud::Texture>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::MaterialParam<mud::Colour>>(), member_address(&mud::MaterialParam<mud::Colour>::m_channel), type<mud::TextureChannel>(), "channel", var(mud::TextureChannel()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Mesh>(), &namspc({ "mud" }), "Mesh", sizeof(mud::Mesh), TypeClass::Object };
        static Class cls = { type<mud::Mesh>(),
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
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_name), type<std::string>(), "name", var(std::string()), Member::Value, nullptr },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value, nullptr },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_draw_mode), type<mud::DrawMode>(), "draw_mode", var(mud::DrawMode()), Member::Value, nullptr },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_aabb), type<mud::Aabb>(), "aabb", var(mud::Aabb()), Member::Value, nullptr },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_radius), type<float>(), "radius", var(float(0.f)), Member::Value, nullptr },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_origin), type<mud::vec3>(), "origin", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_readback), type<bool>(), "readback", var(bool(false)), Member::Value, nullptr },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_vertex_count), type<size_t>(), "vertex_count", var(size_t()), Member::Value, nullptr },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_index_count), type<size_t>(), "index_count", var(size_t()), Member::Value, nullptr },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_material), type<mud::Material>(), "material", Ref(type<mud::Material>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
        static Meta meta = { type<mud::Model>(), &namspc({ "mud" }), "Model", sizeof(mud::Model), TypeClass::Object };
        static Class cls = { type<mud::Model>(),
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
                { type<mud::Model>(), member_address(&mud::Model::m_name), type<std::string>(), "name", var(std::string()), Member::Value, nullptr },
                { type<mud::Model>(), member_address(&mud::Model::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value, nullptr },
                { type<mud::Model>(), member_address(&mud::Model::m_aabb), type<mud::Aabb>(), "aabb", var(mud::Aabb()), Member::Value, nullptr },
                { type<mud::Model>(), member_address(&mud::Model::m_radius), type<float>(), "radius", var(float(0.f)), Member::Value, nullptr },
                { type<mud::Model>(), member_address(&mud::Model::m_origin), type<mud::vec3>(), "origin", var(mud::vec3()), Member::Value, nullptr }
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
    

	// mud::ImportConfig
	{
		static Meta meta = { type<mud::ImportConfig>(), &namspc({ "mud" }), "ImportConfig", sizeof(mud::ImportConfig), TypeClass::Struct };
		static Class cls = { type<mud::ImportConfig>(),
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
				{ type<mud::ImportConfig>(), [](Ref ref, Ref other) { new(&val<mud::ImportConfig>(ref)) mud::ImportConfig(val<mud::ImportConfig>(other)); } }
			},
			// members
			{
				{ type<mud::ImportConfig>(), member_address(&mud::ImportConfig::m_format), type<mud::ModelFormat>(), "format", var(ModelFormat::obj), Member::Value, nullptr },
				{ type<mud::ImportConfig>(), member_address(&mud::ImportConfig::m_position), type<mud::vec3>(), "position", var(Zero3), Member::Value, nullptr },
				{ type<mud::ImportConfig>(), member_address(&mud::ImportConfig::m_rotation), type<mud::quat>(), "rotation", var(ZeroQuat), Member::Value, nullptr },
				{ type<mud::ImportConfig>(), member_address(&mud::ImportConfig::m_scale), type<mud::vec3>(), "scale", var(Unit3), Member::Value, nullptr },
				{ type<mud::ImportConfig>(), member_address(&mud::ImportConfig::m_as_prefab), type<bool>(), "as_prefab", var(bool(false)), Member::Value, nullptr },
				{ type<mud::ImportConfig>(), member_address(&mud::ImportConfig::m_exclude_elements), type<std::vector<std::string>>(), "exclude_elements", var(std::vector<std::string>()), Member::Value, nullptr },
				{ type<mud::ImportConfig>(), member_address(&mud::ImportConfig::m_exclude_materials), type<std::vector<std::string>>(), "exclude_materials", var(std::vector<std::string>()), Member::Value, nullptr },
				{ type<mud::ImportConfig>(), member_address(&mud::ImportConfig::m_include_elements), type<std::vector<std::string>>(), "include_elements", var(std::vector<std::string>()), Member::Value, nullptr }
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

    
        
    // mud::ModelItem
    {
        static Meta meta = { type<mud::ModelItem>(), &namspc({ "mud" }), "ModelItem", sizeof(mud::ModelItem), TypeClass::Struct };
        static Class cls = { type<mud::ModelItem>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::ModelItem>(), [](Ref ref, Ref other) { new(&val<mud::ModelItem>(ref)) mud::ModelItem(val<mud::ModelItem>(other)); } }
            },
            // members
            {
                { type<mud::ModelItem>(), member_address(&mud::ModelItem::m_transform), type<mud::mat4>(), "transform", var(mud::mat4()), Member::Value, nullptr },
                { type<mud::ModelItem>(), member_address(&mud::ModelItem::m_mesh), type<mud::Mesh>(), "mesh", Ref(type<mud::Mesh>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::ModelItem>(), member_address(&mud::ModelItem::m_skin), type<int>(), "skin", var(int()), Member::Value, nullptr },
                { type<mud::ModelItem>(), member_address(&mud::ModelItem::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::ModelItem>(), member_address(&mud::ModelItem::m_material), type<mud::Material>(), "material", Ref(type<mud::Material>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
        static Meta meta = { type<mud::Node3>(), &namspc({ "mud" }), "Node3", sizeof(mud::Node3), TypeClass::Object };
        static Class cls = { type<mud::Node3>(),
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
                { type<mud::Node3>(), member_address(&mud::Node3::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Node3>(), member_address(&mud::Node3::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value, nullptr },
                //{ type<mud::Node3>(), member_address(&mud::Node3::m_position), type<mud::vec3>(), "position", var(mud::vec3()), Member::Value, nullptr },
                //{ type<mud::Node3>(), member_address(&mud::Node3::m_rotation), type<mud::quat>(), "rotation", var(mud::quat()), Member::Value, nullptr },
                //{ type<mud::Node3>(), member_address(&mud::Node3::m_scale), type<mud::vec3>(), "scale", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Node3>(), member_address(&mud::Node3::m_visible), type<bool>(), "visible", var(bool(true)), Member::Value, nullptr }
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
    
    
    
        
    // mud::ParticleGenerator
    {
        static Meta meta = { type<mud::ParticleGenerator>(), &namspc({ "mud" }), "ParticleGenerator", sizeof(mud::ParticleGenerator), TypeClass::Struct };
        static Class cls = { type<mud::ParticleGenerator>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::ParticleGenerator>(), [](Ref ref, Ref other) { new(&val<mud::ParticleGenerator>(ref)) mud::ParticleGenerator(val<mud::ParticleGenerator>(other)); } }
            },
            // members
            {
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_name), type<std::string>(), "name", var(std::string()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_duration), type<float>(), "duration", var(float(1.f)), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_start_time), type<float>(), "start_time", var(float(0.f)), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_loop), type<bool>(), "loop", var(bool(false)), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_shape), type<mud::ShapeVar>(), "shape", var(mud::ShapeVar()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_flow), type<mud::EmitterFlow>(), "flow", var(mud::EmitterFlow()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_billboard), type<bool>(), "billboard", var(bool(true)), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_direction), type<mud::vec3>(), "direction", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_rotation), type<mud::quat>(), "rotation", var(mud::quat()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_blend_mode), type<mud::BlendMode>(), "blend_mode", var(mud::BlendMode()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_volume), type<mud::ValueTrack<float>>(), "volume", var(mud::ValueTrack<float>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_rate), type<mud::ValueTrack<uint32_t>>(), "rate", var(mud::ValueTrack<uint32_t>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_lifetime), type<mud::ValueTrack<float>>(), "lifetime", var(mud::ValueTrack<float>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_gravity), type<mud::ValueTrack<float>>(), "gravity", var(mud::ValueTrack<float>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_speed), type<mud::ValueTrack<float>>(), "speed", var(mud::ValueTrack<float>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_angle), type<mud::ValueTrack<float>>(), "angle", var(mud::ValueTrack<float>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_blend), type<mud::ValueTrack<float>>(), "blend", var(mud::ValueTrack<float>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_colour), type<mud::ValueTrack<mud::Colour>>(), "colour", var(mud::ValueTrack<mud::Colour>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_scale), type<mud::ValueTrack<float>>(), "scale", var(mud::ValueTrack<float>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_sprite_frame), type<mud::ValueTrack<float>>(), "sprite_frame", var(mud::ValueTrack<float>()), Member::Value, nullptr },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_sprite_name), type<std::string>(), "sprite_name", var(std::string()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ParticleGenerator>();
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    // mud::PbrMaterialBlock
    {
        static Meta meta = { type<mud::PbrMaterialBlock>(), &namspc({ "mud" }), "PbrMaterialBlock", sizeof(mud::PbrMaterialBlock), TypeClass::Struct };
        static Class cls = { type<mud::PbrMaterialBlock>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::PbrMaterialBlock>(), [](Ref ref, Ref other) { new(&val<mud::PbrMaterialBlock>(ref)) mud::PbrMaterialBlock(val<mud::PbrMaterialBlock>(other)); } }
            },
            // members
            {
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_albedo), type<mud::MaterialParam<mud::Colour>>(), "albedo", var(mud::MaterialParam<mud::Colour>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_specular), type<float>(), "specular", var(float(0.5f)), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_metallic), type<mud::MaterialParam<float>>(), "metallic", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_roughness), type<mud::MaterialParam<float>>(), "roughness", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_emissive), type<mud::MaterialParam<mud::Colour>>(), "emissive", var(mud::MaterialParam<mud::Colour>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_emissive_energy), type<float>(), "emissive_energy", var(float(0.f)), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_normal), type<mud::MaterialParam<float>>(), "normal", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_rim), type<mud::MaterialParam<float>>(), "rim", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_rim_tint), type<float>(), "ritint", var(float()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_clearcoat), type<mud::MaterialParam<float>>(), "clearcoat", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_clearcoat_gloss), type<float>(), "clearcoat_gloss", var(float()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_anisotropy), type<mud::MaterialParam<float>>(), "anisotropy", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_subsurface), type<mud::MaterialParam<float>>(), "subsurface", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_transmission), type<mud::MaterialParam<mud::Colour>>(), "transmission", var(mud::MaterialParam<mud::Colour>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_refraction), type<mud::MaterialParam<float>>(), "refraction", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_ambient_occlusion), type<mud::MaterialParam<float>>(), "ambient_occlusion", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_depth), type<mud::MaterialParam<float>>(), "depth", var(mud::MaterialParam<float>()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_deep_parallax), type<bool>(), "deep_parallax", var(bool(false)), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_diffuse_mode), type<mud::PbrDiffuseMode>(), "diffuse_mode", var(mud::PbrDiffuseMode()), Member::Value, nullptr },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_specular_mode), type<mud::PbrSpecularMode>(), "specular_mode", var(mud::PbrSpecularMode()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Prefab>(), &namspc({ "mud" }), "Prefab", sizeof(mud::Prefab), TypeClass::Object };
        static Class cls = { type<mud::Prefab>(),
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
                { type<mud::Prefab>(), member_address(&mud::Prefab::m_name), type<std::string>(), "name", var(std::string()), Member::Value, nullptr },
                { type<mud::Prefab>(), member_address(&mud::Prefab::m_node), type<mud::PrefabNode>(), "node", var(mud::PrefabNode()), Member::Value, nullptr }
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
    
    
        
    // mud::PrefabNode
    {
        static Meta meta = { type<mud::PrefabNode>(), &namspc({ "mud" }), "PrefabNode", sizeof(mud::PrefabNode), TypeClass::Struct };
        static Class cls = { type<mud::PrefabNode>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::PrefabNode>(), [](Ref ref, Ref other) { new(&val<mud::PrefabNode>(ref)) mud::PrefabNode(val<mud::PrefabNode>(other)); } }
            },
            // members
            {
                { type<mud::PrefabNode>(), member_address(&mud::PrefabNode::m_transform), type<mud::Transform>(), "transform", var(mud::Transform()), Member::Value, nullptr },
                { type<mud::PrefabNode>(), member_address(&mud::PrefabNode::m_object), type<mud::Ref>(), "object", Ref(type<mud::Ref>()), Member::None, nullptr },
                { type<mud::PrefabNode>(), member_address(&mud::PrefabNode::m_prefab_type), type<mud::PrefabType>(), "prefab_type", var(mud::PrefabType()), Member::Value, nullptr },
                { type<mud::PrefabNode>(), member_address(&mud::PrefabNode::m_call), type<mud::Call>(), "call", var(mud::Call()), Member::Value, nullptr },
                { type<mud::PrefabNode>(), member_address(&mud::PrefabNode::m_nodes), type<std::vector<mud::PrefabNode>>(), "nodes", var(std::vector<mud::PrefabNode>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::PrefabNode>();
    }
    
    
    
        
    // mud::Program
    {
        static Meta meta = { type<mud::Program>(), &namspc({ "mud" }), "Program", sizeof(mud::Program), TypeClass::Object };
        static Class cls = { type<mud::Program>(),
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
                { type<mud::Program>(), member_address(&mud::Program::name), type<cstring>(), "name", var(cstring()), Member::Value, [](Ref object) { return Ref(val<mud::Program>(object).name()); } }
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
        static Meta meta = { type<mud::Radiance>(), &namspc({ "mud" }), "Radiance", sizeof(mud::Radiance), TypeClass::Struct };
        static Class cls = { type<mud::Radiance>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Radiance>(), [](Ref ref, Ref other) { new(&val<mud::Radiance>(ref)) mud::Radiance(val<mud::Radiance>(other)); } }
            },
            // members
            {
                { type<mud::Radiance>(), member_address(&mud::Radiance::m_energy), type<float>(), "energy", var(float(1.0f)), Member::Value, nullptr },
                { type<mud::Radiance>(), member_address(&mud::Radiance::m_ambient), type<float>(), "ambient", var(float(1.0f)), Member::Value, nullptr },
                { type<mud::Radiance>(), member_address(&mud::Radiance::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Radiance>(), member_address(&mud::Radiance::m_texture), type<mud::Texture>(), "texture", Ref(type<mud::Texture>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
        static Meta meta = { type<mud::RenderFrame>(), &namspc({ "mud" }), "RenderFrame", sizeof(mud::RenderFrame), TypeClass::Struct };
        static Class cls = { type<mud::RenderFrame>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::RenderFrame>(), [](Ref ref, Ref other) { new(&val<mud::RenderFrame>(ref)) mud::RenderFrame(val<mud::RenderFrame>(other)); } }
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
        static Meta meta = { type<mud::RenderQuad>(), &namspc({ "mud" }), "RenderQuad", sizeof(mud::RenderQuad), TypeClass::Struct };
        static Class cls = { type<mud::RenderQuad>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::RenderQuad>(), [](Ref ref, Ref other) { new(&val<mud::RenderQuad>(ref)) mud::RenderQuad(val<mud::RenderQuad>(other)); } }
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
        static Meta meta = { type<mud::Rig>(), &namspc({ "mud" }), "Rig", sizeof(mud::Rig), TypeClass::Object };
        static Class cls = { type<mud::Rig>(),
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
        static Meta meta = { type<mud::Scene>(), &namspc({ "mud" }), "Scene", sizeof(mud::Scene), TypeClass::Object };
        static Class cls = { type<mud::Scene>(),
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
                { type<mud::Scene>(), member_address(&mud::Scene::m_graph), type<mud::Gnode>(), "graph", Ref(type<mud::Gnode>()), Member::None, nullptr },
                { type<mud::Scene>(), member_address(&mud::Scene::m_root_node), type<mud::Node3>(), "root_node", Ref(type<mud::Node3>()), Member::None, nullptr },
                { type<mud::Scene>(), member_address(&mud::Scene::m_environment), type<mud::Environment>(), "environment", var(mud::Environment()), Member::Value, nullptr },
                { type<mud::Scene>(), member_address(&mud::Scene::m_user), type<mud::Ref>(), "user", Ref(type<mud::Ref>()), Member::None, nullptr }
            },
            // methods
            {
                { type<mud::Scene>(), "begin", member_address(&mud::Scene::begin), [](Ref object, array<Var> args, Var& result) { UNUSED(args);result = Ref(&val<mud::Scene>(object).begin()); }, {}, Ref(type<mud::Gnode>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Scene>();
    }
    
    
    
    
    
        
    // mud::Shot
    {
        static Meta meta = { type<mud::Shot>(), &namspc({ "mud" }), "Shot", sizeof(mud::Shot), TypeClass::Object };
        static Class cls = { type<mud::Shot>(),
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
        static Meta meta = { type<mud::Skeleton>(), &namspc({ "mud" }), "Skeleton", sizeof(mud::Skeleton), TypeClass::Object };
        static Class cls = { type<mud::Skeleton>(),
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
        static Meta meta = { type<mud::Skin>(), &namspc({ "mud" }), "Skin", sizeof(mud::Skin), TypeClass::Object };
        static Class cls = { type<mud::Skin>(),
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
        static Meta meta = { type<mud::Sun>(), &namspc({ "mud" }), "Sun", sizeof(mud::Sun), TypeClass::Struct };
        static Class cls = { type<mud::Sun>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Sun>(), [](Ref ref, Ref other) { new(&val<mud::Sun>(ref)) mud::Sun(val<mud::Sun>(other)); } }
            },
            // members
            {
                { type<mud::Sun>(), member_address(&mud::Sun::azimuth), type<float>(), "azimuth", var(float()), Member::Value, nullptr },
                { type<mud::Sun>(), member_address(&mud::Sun::elevation), type<float>(), "elevation", var(float()), Member::Value, nullptr },
                { type<mud::Sun>(), member_address(&mud::Sun::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Sun>(), member_address(&mud::Sun::m_intensity), type<float>(), "intensity", var(float(0.f)), Member::Value, nullptr }
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
        static Meta meta = { type<mud::SymbolIndex>(), &namspc({ "mud" }), "SymbolIndex", sizeof(mud::SymbolIndex), TypeClass::Object };
        static Class cls = { type<mud::SymbolIndex>(),
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
        static Meta meta = { type<mud::Texture>(), &namspc({ "mud" }), "Texture", sizeof(mud::Texture), TypeClass::Object };
        static Class cls = { type<mud::Texture>(),
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
                { type<mud::Texture>(), member_address(&mud::Texture::m_width), type<uint16_t>(), "width", var(uint16_t()), Member::Value, nullptr },
                { type<mud::Texture>(), member_address(&mud::Texture::m_height), type<uint16_t>(), "height", var(uint16_t()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::UnshadedMaterialBlock>(), &namspc({ "mud" }), "UnshadedMaterialBlock", sizeof(mud::UnshadedMaterialBlock), TypeClass::Struct };
        static Class cls = { type<mud::UnshadedMaterialBlock>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::UnshadedMaterialBlock>(), [](Ref ref, Ref other) { new(&val<mud::UnshadedMaterialBlock>(ref)) mud::UnshadedMaterialBlock(val<mud::UnshadedMaterialBlock>(other)); } }
            },
            // members
            {
                { type<mud::UnshadedMaterialBlock>(), member_address(&mud::UnshadedMaterialBlock::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Value, nullptr },
                { type<mud::UnshadedMaterialBlock>(), member_address(&mud::UnshadedMaterialBlock::m_colour), type<mud::MaterialParam<mud::Colour>>(), "colour", var(mud::MaterialParam<mud::Colour>()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Viewport>(), &namspc({ "mud" }), "Viewport", sizeof(mud::Viewport), TypeClass::Object };
        static Class cls = { type<mud::Viewport>(),
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
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_camera), type<mud::Camera>(), "camera", Ref(type<mud::Camera>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value, nullptr },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_rect), type<mud::uvec4>(), "rect", var(mud::uvec4()), Member::Value, nullptr },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_scissor), type<bool>(), "scissor", var(bool(false)), Member::Value, nullptr },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_clear_colour), type<mud::Colour>(), "clear_colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_shading), type<mud::Shading>(), "shading", var(mud::Shading()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::BlockCopy>(), &namspc({ "mud" }), "BlockCopy", sizeof(mud::BlockCopy), TypeClass::Object };
        static Class cls = { type<mud::BlockCopy>(),
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
    
    
        
    // mud::BlockFilter
    {
        static Meta meta = { type<mud::BlockFilter>(), &namspc({ "mud" }), "BlockFilter", sizeof(mud::BlockFilter), TypeClass::Object };
        static Class cls = { type<mud::BlockFilter>(),
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
        static Meta meta = { type<mud::BlockParticles>(), &namspc({ "mud" }), "BlockParticles", sizeof(mud::BlockParticles), TypeClass::Object };
        static Class cls = { type<mud::BlockParticles>(),
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
        static Meta meta = { type<mud::BlockResolve>(), &namspc({ "mud" }), "BlockResolve", sizeof(mud::BlockResolve), TypeClass::Object };
        static Class cls = { type<mud::BlockResolve>(),
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
        static Meta meta = { type<mud::BlockSky>(), &namspc({ "mud" }), "BlockSky", sizeof(mud::BlockSky), TypeClass::Object };
        static Class cls = { type<mud::BlockSky>(),
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
    
    
        
    // mud::DrawBlock
    {
        static Meta meta = { type<mud::DrawBlock>(), &namspc({ "mud" }), "DrawBlock", sizeof(mud::DrawBlock), TypeClass::Object };
        static Class cls = { type<mud::DrawBlock>(),
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
        static Meta meta = { type<mud::BlockDepth>(), &namspc({ "mud" }), "BlockDepth", sizeof(mud::BlockDepth), TypeClass::Object };
        static Class cls = { type<mud::BlockDepth>(),
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
    
    
        
    // mud::Particles
    {
        static Meta meta = { type<mud::Particles>(), &namspc({ "mud" }), "Particles", sizeof(mud::Particles), TypeClass::Struct };
        static Class cls = { type<mud::Particles>(),
            // bases
            { &type<mud::ParticleGenerator>() },
            { base_offset<mud::Particles, mud::ParticleGenerator>() },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Particles>(), [](Ref ref, Ref other) { new(&val<mud::Particles>(ref)) mud::Particles(val<mud::Particles>(other)); } }
            },
            // members
            {
                { type<mud::Particles>(), member_address(&mud::Particles::m_node), type<mud::Node3>(), "node", Ref(type<mud::Node3>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
        static Meta meta = { type<mud::RenderTarget>(), &namspc({ "mud" }), "RenderTarget", sizeof(mud::RenderTarget), TypeClass::Object };
        static Class cls = { type<mud::RenderTarget>(),
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
    
    
        
    // mud::Gnode
    {
        static Meta meta = { type<mud::Gnode>(), &namspc({ "mud" }), "Gnode", sizeof(mud::Gnode), TypeClass::Object };
        static Class cls = { type<mud::Gnode>(),
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
    

    
        m.m_types.push_back(&type<mud::Animated>());
        m.m_types.push_back(&type<mud::AnimatedTrack>());
        m.m_types.push_back(&type<mud::Animation>());
        m.m_types.push_back(&type<mud::AnimationPlay>());
        m.m_types.push_back(&type<mud::AnimationTrack>());
        m.m_types.push_back(&type<mud::AssetStore<mud::Material>>());
        m.m_types.push_back(&type<mud::AssetStore<mud::Model>>());
        m.m_types.push_back(&type<mud::AssetStore<mud::ParticleGenerator>>());
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
        m.m_types.push_back(&type<mud::ImmediateDraw>());
        m.m_types.push_back(&type<mud::Interpolation>());
        m.m_types.push_back(&type<mud::IsometricAngle>());
        m.m_types.push_back(&type<mud::Item>());
        m.m_types.push_back(&type<mud::ItemShadow>());
        m.m_types.push_back(&type<mud::Joint>());
        m.m_types.push_back(&type<mud::Light>());
        m.m_types.push_back(&type<mud::LightType>());
        m.m_types.push_back(&type<mud::MSAA>());
        m.m_types.push_back(&type<mud::Material>());
        m.m_types.push_back(&type<mud::MaterialFlag>());
        m.m_types.push_back(&type<mud::MaterialParam<float>>());
        m.m_types.push_back(&type<mud::MaterialParam<mud::Colour>>());
        m.m_types.push_back(&type<mud::Mesh>());
        m.m_types.push_back(&type<mud::Model>());
		m.m_types.push_back(&type<mud::ModelFormat>());
		m.m_types.push_back(&type<mud::ImportConfig>());
        m.m_types.push_back(&type<mud::ModelItem>());
        m.m_types.push_back(&type<mud::Month>());
        m.m_types.push_back(&type<mud::Node3>());
        m.m_types.push_back(&type<mud::ParticleGenerator>());
        m.m_types.push_back(&type<mud::PbrDiffuseMode>());
        m.m_types.push_back(&type<mud::PbrMaterialBlock>());
        m.m_types.push_back(&type<mud::PbrSpecularMode>());
        m.m_types.push_back(&type<mud::Prefab>());
        m.m_types.push_back(&type<mud::PrefabNode>());
        m.m_types.push_back(&type<mud::PrefabType>());
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
        m.m_types.push_back(&type<std::vector<mud::PrefabNode>>());
        m.m_types.push_back(&type<mud::BlockCopy>());
        m.m_types.push_back(&type<mud::BlockFilter>());
        m.m_types.push_back(&type<mud::BlockParticles>());
        m.m_types.push_back(&type<mud::BlockResolve>());
        m.m_types.push_back(&type<mud::BlockSky>());
        m.m_types.push_back(&type<mud::DrawBlock>());
        m.m_types.push_back(&type<mud::BlockDepth>());
        m.m_types.push_back(&type<mud::Particles>());
        m.m_types.push_back(&type<mud::RenderTarget>());
        m.m_types.push_back(&type<mud::Gnode>());
    
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::update_item_lights(val<mud::Item>(args[0])); };
            std::vector<Param> params = { { "item", Ref(type<mud::Item>()) } };
            static Function f = { &namspc({ "mud", "gfx" }), "update_item_lights", function_id<void(*)(mud::Item&)>(&mud::gfx::update_item_lights), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::update_item_aabb(val<mud::Item>(args[0])); };
            std::vector<Param> params = { { "item", Ref(type<mud::Item>()) } };
            static Function f = { &namspc({ "mud", "gfx" }), "update_item_aabb", function_id<void(*)(mud::Item&)>(&mud::gfx::update_item_aabb), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::node(val<mud::Gnode>(args[0]), args[1], val<mud::vec3>(args[2]), val<mud::quat>(args[3]), val<mud::vec3>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "object", Ref(), Param::Flags(Param::Nullable|Param::Default) }, { "position", var(Zero3), Param::Default }, { "rotation", var(ZeroQuat), Param::Default }, { "scale", var(Unit3), Param::Default } };
            static Function f = { &namspc({ "mud", "gfx" }), "node", function_id<mud::Gnode&(*)(mud::Gnode&, mud::Ref, const mud::vec3&, const mud::quat&, const mud::vec3&)>(&mud::gfx::node), func, params, Ref(type<mud::Gnode>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::shape(val<mud::Gnode>(args[0]), val<mud::Shape>(args[1]), val<mud::Symbol>(args[2]), val<uint32_t>(args[3]), &val<mud::Material>(args[4]), val<size_t>(args[5]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "shape", Ref(type<mud::Shape>()) }, { "symbol", var(mud::Symbol()) }, { "flags", var(uint32_t()), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t()), Param::Default } };
            static Function f = { &namspc({ "mud", "gfx" }), "shape", function_id<mud::Item&(*)(mud::Gnode&, const mud::Shape&, const mud::Symbol&, uint32_t, mud::Material*, size_t)>(&mud::gfx::shape), func, params, Ref(type<mud::Item>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::draw(val<mud::Gnode>(args[0]), val<mud::Shape>(args[1]), val<mud::Symbol>(args[2]), val<uint32_t>(args[3])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "shape", Ref(type<mud::Shape>()) }, { "symbol", var(mud::Symbol()) }, { "flags", var(uint32_t()), Param::Default } };
            static Function f = { &namspc({ "mud", "gfx" }), "draw", function_id<void(*)(mud::Gnode&, const mud::Shape&, const mud::Symbol&, uint32_t)>(&mud::gfx::draw), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::sprite(val<mud::Gnode>(args[0]), val<mud::Image256>(args[1]), val<mud::vec2>(args[2]), val<uint32_t>(args[3]), &val<mud::Material>(args[4]), val<size_t>(args[5]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "image", var(mud::Image256()) }, { "size", var(mud::vec2()) }, { "flags", var(uint32_t()), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t()), Param::Default } };
            static Function f = { &namspc({ "mud", "gfx" }), "sprite", function_id<mud::Item&(*)(mud::Gnode&, const mud::Image256&, const mud::vec2&, uint32_t, mud::Material*, size_t)>(&mud::gfx::sprite), func, params, Ref(type<mud::Item>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::item(val<mud::Gnode>(args[0]), val<mud::Model>(args[1]), val<uint32_t>(args[2]), &val<mud::Material>(args[3]), val<size_t>(args[4]), val<array<mud::mat4>>(args[5]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "model", Ref(type<mud::Model>()) }, { "flags", var(uint32_t()), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t()), Param::Default }, { "transforms", var(array<mud::mat4>()), Param::Default } };
            static Function f = { &namspc({ "mud", "gfx" }), "item", function_id<mud::Item&(*)(mud::Gnode&, const mud::Model&, uint32_t, mud::Material*, size_t, array<mud::mat4>)>(&mud::gfx::item), func, params, Ref(type<mud::Item>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(mud::gfx::model(val<mud::Gnode>(args[0]), val<std::string>(args[1]), val<uint32_t>(args[2]), &val<mud::Material>(args[3]), val<size_t>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "name", var(std::string()) }, { "flags", var(uint32_t()), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t()), Param::Default } };
            static Function f = { &namspc({ "mud", "gfx" }), "model", function_id<mud::Item*(*)(mud::Gnode&, const std::string&, uint32_t, mud::Material*, size_t)>(&mud::gfx::model), func, params, Ref(type<mud::Item>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::animated(val<mud::Gnode>(args[0]), val<mud::Item>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "item", Ref(type<mud::Item>()) } };
            static Function f = { &namspc({ "mud", "gfx" }), "animated", function_id<mud::Animated&(*)(mud::Gnode&, mud::Item&)>(&mud::gfx::animated), func, params, Ref(type<mud::Animated>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Particles>(result) = mud::gfx::particles(val<mud::Gnode>(args[0]), val<mud::ParticleGenerator>(args[1]), val<uint32_t>(args[2]), val<size_t>(args[3])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "emitter", var(mud::ParticleGenerator()) }, { "flags", var(uint32_t()), Param::Default }, { "instances", var(size_t()), Param::Default } };
            static Function f = { &namspc({ "mud", "gfx" }), "particles", function_id<mud::Particles&(*)(mud::Gnode&, const mud::ParticleGenerator&, uint32_t, size_t)>(&mud::gfx::particles), func, params, var(mud::Particles()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::light(val<mud::Gnode>(args[0]), val<mud::LightType>(args[1]), val<bool>(args[2]), val<mud::Colour>(args[3]), val<float>(args[4]), val<float>(args[5]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "type", var(mud::LightType()) }, { "shadows", var(bool()) }, { "colour", var(mud::Colour()) }, { "range", var(float(0.f)), Param::Default }, { "attenuation", var(float(0.5f)), Param::Default } };
            static Function f = { &namspc({ "mud", "gfx" }), "light", function_id<mud::Light&(*)(mud::Gnode&, mud::LightType, bool, mud::Colour, float, float)>(&mud::gfx::light), func, params, Ref(type<mud::Light>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::sun_light(val<mud::Gnode>(args[0]), val<float>(args[1]), val<float>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "azimuth", var(float()) }, { "elevation", var(float()) } };
            static Function f = { &namspc({ "mud", "gfx" }), "sun_light", function_id<mud::Light&(*)(mud::Gnode&, float, float)>(&mud::gfx::sun_light), func, params, Ref(type<mud::Light>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::radiance(val<mud::Gnode>(args[0]), val<std::string>(args[1]), val<mud::BackgroundMode>(args[2])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "texture", var(std::string()) }, { "background", var(mud::BackgroundMode()) } };
            static Function f = { &namspc({ "mud", "gfx" }), "radiance", function_id<void(*)(mud::Gnode&, const std::string&, mud::BackgroundMode)>(&mud::gfx::radiance), func, params, Var() };
            m.m_functions.push_back(&f);
        }
		/*{
			auto func = [](array<Var> args, Var& result) { result = Ref(&mud::gfx::pbr_material(val<mud::GfxSystem>(args[0]), val<cstring>(args[1]), val<mud::PbrMaterialBlock>(args[2]))); };
			std::vector<Param> params = { { "gfx_system", Ref(type<mud::GfxSystem>()) }, { "name", Ref(type<cstring>()) }, { "pbr_block", Ref(type<mud::PbrMaterialBlock>()) } };
			static Function f = { &namspc({ "mud", "gfx" }), "pbr_material", function_id<mud::Material&(*)(mud::GfxSystem&, cstring, const mud::PbrMaterialBlock&)>(&mud::gfx::pbr_material), func, params, Ref(type<mud::Material>()) };
			m.m_functions.push_back(&f);
		}*/
		{
			auto func = [](array<Var> args, Var& result) { result = Ref(&mud::gfx::pbr_material(val<mud::GfxSystem>(args[0]), val<cstring>(args[1]), val<mud::Colour>(args[2]), val<float>(args[3]), val<float>(args[4]))); };
			std::vector<Param> params = { { "gfx_system", Ref(type<mud::GfxSystem>()) }, { "name", Ref(type<cstring>()) }, { "albedo", var(mud::Colour()) }, { "metallic", var(float(0.f)), Param::Default }, { "roughness", var(float(1.f)), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "pbr_material", function_id<mud::Material&(*)(mud::GfxSystem&, cstring, const mud::Colour&, float, float)>(&mud::gfx::pbr_material), func, params, Ref(type<mud::Material>()) };
			m.m_functions.push_back(&f);
		}
    }
}
