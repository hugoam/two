

#pragma once

#include <gfx/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>

namespace mud
{
    
#ifdef MUD_GFX_REFLECTION_IMPL
    void gfx_meta(Module& module)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::BackgroundMode>(), &namspc({ "mud" }), "BackgroundMode", sizeof(mud::BackgroundMode), TypeClass::Enum };
        static Enum enu = { type<mud::BackgroundMode>(),
            true,
            { "None", "Panorama", "Radiance", "Custom" },
            { 0, 1, 2, 3 },
            { var(BackgroundMode::None), var(BackgroundMode::Panorama), var(BackgroundMode::Radiance), var(BackgroundMode::Custom) }
        };
        meta_enum<mud::BackgroundMode>();
    }
    
    {
        static Meta meta = { type<mud::BlendMode>(), &namspc({ "mud" }), "BlendMode", sizeof(mud::BlendMode), TypeClass::Enum };
        static Enum enu = { type<mud::BlendMode>(),
            true,
            { "Mix", "Add", "Sub", "Mul", "Normal", "Alpha" },
            { 0, 1, 2, 3, 4, 5 },
            { var(BlendMode::Mix), var(BlendMode::Add), var(BlendMode::Sub), var(BlendMode::Mul), var(BlendMode::Normal), var(BlendMode::Alpha) }
        };
        meta_enum<mud::BlendMode>();
    }
    
    {
        static Meta meta = { type<mud::CullMode>(), &namspc({ "mud" }), "CullMode", sizeof(mud::CullMode), TypeClass::Enum };
        static Enum enu = { type<mud::CullMode>(),
            true,
            { "None", "Front", "Back" },
            { 0, 1, 2 },
            { var(CullMode::None), var(CullMode::Front), var(CullMode::Back) }
        };
        meta_enum<mud::CullMode>();
    }
    
    {
        static Meta meta = { type<mud::DepthDraw>(), &namspc({ "mud" }), "DepthDraw", sizeof(mud::DepthDraw), TypeClass::Enum };
        static Enum enu = { type<mud::DepthDraw>(),
            true,
            { "Enabled", "Disabled" },
            { 0, 1 },
            { var(DepthDraw::Enabled), var(DepthDraw::Disabled) }
        };
        meta_enum<mud::DepthDraw>();
    }
    
    {
        static Meta meta = { type<mud::DepthTest>(), &namspc({ "mud" }), "DepthTest", sizeof(mud::DepthTest), TypeClass::Enum };
        static Enum enu = { type<mud::DepthTest>(),
            true,
            { "Enabled", "Disabled" },
            { 0, 1 },
            { var(DepthTest::Enabled), var(DepthTest::Disabled) }
        };
        meta_enum<mud::DepthTest>();
    }
    
    {
        static Meta meta = { type<mud::EmitterDirection>(), &namspc({ "mud" }), "EmitterDirection", sizeof(mud::EmitterDirection), TypeClass::Enum };
        static Enum enu = { type<mud::EmitterDirection>(),
            true,
            { "Outward", "Absolute" },
            { 0, 1 },
            { var(EmitterDirection::Outward), var(EmitterDirection::Absolute) }
        };
        meta_enum<mud::EmitterDirection>();
    }
    
    {
        static Meta meta = { type<mud::Interpolation>(), &namspc({ "mud" }), "Interpolation", sizeof(mud::Interpolation), TypeClass::Enum };
        static Enum enu = { type<mud::Interpolation>(),
            true,
            { "Nearest", "Linear", "Cubic" },
            { 0, 1, 2 },
            { var(Interpolation::Nearest), var(Interpolation::Linear), var(Interpolation::Cubic) }
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
        static Meta meta = { type<mud::ItemFlag>(), &namspc({ "mud" }), "ItemFlag", sizeof(mud::ItemFlag), TypeClass::Enum };
        static Enum enu = { type<mud::ItemFlag>(),
            false,
            { "ITEM_BILLBOARD", "ITEM_WORLD_GEOMETRY", "ITEM_SELECTABLE", "ITEM_UI", "ITEM_SHADEABLE", "ITEM_LOD_0", "ITEM_LOD_1", "ITEM_LOD_2", "ITEM_LOD_3", "ITEM_LOD_ALL" },
            { 1, 2, 4, 8, 16, 32, 64, 128, 256, 480 },
            { var(mud::ITEM_BILLBOARD), var(mud::ITEM_WORLD_GEOMETRY), var(mud::ITEM_SELECTABLE), var(mud::ITEM_UI), var(mud::ITEM_SHADEABLE), var(mud::ITEM_LOD_0), var(mud::ITEM_LOD_1), var(mud::ITEM_LOD_2), var(mud::ITEM_LOD_3), var(mud::ITEM_LOD_ALL) }
        };
        meta_enum<mud::ItemFlag>();
    }
    
    {
        static Meta meta = { type<mud::ItemShadow>(), &namspc({ "mud" }), "ItemShadow", sizeof(mud::ItemShadow), TypeClass::Enum };
        static Enum enu = { type<mud::ItemShadow>(),
            true,
            { "Off", "On", "DoubleSided", "OnlyShadow" },
            { 0, 1, 2, 3 },
            { var(ItemShadow::Off), var(ItemShadow::On), var(ItemShadow::DoubleSided), var(ItemShadow::OnlyShadow) }
        };
        meta_enum<mud::ItemShadow>();
    }
    
    {
        static Meta meta = { type<mud::LightType>(), &namspc({ "mud" }), "LightType", sizeof(mud::LightType), TypeClass::Enum };
        static Enum enu = { type<mud::LightType>(),
            true,
            { "Directional", "Point", "Spot", "Count" },
            { 0, 1, 2, 3 },
            { var(LightType::Directional), var(LightType::Point), var(LightType::Spot), var(LightType::Count) }
        };
        meta_enum<mud::LightType>();
    }
    
    {
        static Meta meta = { type<mud::MSAA>(), &namspc({ "mud" }), "MSAA", sizeof(mud::MSAA), TypeClass::Enum };
        static Enum enu = { type<mud::MSAA>(),
            true,
            { "Disabled", "X2", "X4", "X8", "X16" },
            { 0, 1, 2, 3, 4 },
            { var(MSAA::Disabled), var(MSAA::X2), var(MSAA::X4), var(MSAA::X8), var(MSAA::X16) }
        };
        meta_enum<mud::MSAA>();
    }
    
    {
        static Meta meta = { type<mud::MaterialFlag>(), &namspc({ "mud" }), "MaterialFlag", sizeof(mud::MaterialFlag), TypeClass::Enum };
        static Enum enu = { type<mud::MaterialFlag>(),
            true,
            { "TriplanarUV1", "TriplanarUV2", "Count" },
            { 0, 1, 2 },
            { var(MaterialFlag::TriplanarUV1), var(MaterialFlag::TriplanarUV2), var(MaterialFlag::Count) }
        };
        meta_enum<mud::MaterialFlag>();
    }
    
    {
        static Meta meta = { type<mud::Month>(), &namspc({ "mud" }), "Month", sizeof(mud::Month), TypeClass::Enum };
        static Enum enu = { type<mud::Month>(),
            true,
            { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" },
            { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 },
            { var(Month::January), var(Month::February), var(Month::March), var(Month::April), var(Month::May), var(Month::June), var(Month::July), var(Month::August), var(Month::September), var(Month::October), var(Month::November), var(Month::December) }
        };
        meta_enum<mud::Month>();
    }
    
    {
        static Meta meta = { type<mud::PbrDiffuseMode>(), &namspc({ "mud" }), "PbrDiffuseMode", sizeof(mud::PbrDiffuseMode), TypeClass::Enum };
        static Enum enu = { type<mud::PbrDiffuseMode>(),
            true,
            { "Lambert", "LambertHalf", "OrenNayar", "Burley", "Toon" },
            { 0, 1, 2, 3, 4 },
            { var(PbrDiffuseMode::Lambert), var(PbrDiffuseMode::LambertHalf), var(PbrDiffuseMode::OrenNayar), var(PbrDiffuseMode::Burley), var(PbrDiffuseMode::Toon) }
        };
        meta_enum<mud::PbrDiffuseMode>();
    }
    
    {
        static Meta meta = { type<mud::PbrSpecularMode>(), &namspc({ "mud" }), "PbrSpecularMode", sizeof(mud::PbrSpecularMode), TypeClass::Enum };
        static Enum enu = { type<mud::PbrSpecularMode>(),
            true,
            { "SchlickGGX", "Blinn", "Phong", "Toon", "Disabled" },
            { 0, 1, 2, 3, 4 },
            { var(PbrSpecularMode::SchlickGGX), var(PbrSpecularMode::Blinn), var(PbrSpecularMode::Phong), var(PbrSpecularMode::Toon), var(PbrSpecularMode::Disabled) }
        };
        meta_enum<mud::PbrSpecularMode>();
    }
    
    {
        static Meta meta = { type<mud::PrefabType>(), &namspc({ "mud" }), "PrefabType", sizeof(mud::PrefabType), TypeClass::Enum };
        static Enum enu = { type<mud::PrefabType>(),
            true,
            { "None", "Item", "Model", "Shape", "Particles", "Light" },
            { 0, 1, 2, 3, 4, 5 },
            { var(PrefabType::None), var(PrefabType::Item), var(PrefabType::Model), var(PrefabType::Shape), var(PrefabType::Particles), var(PrefabType::Light) }
        };
        meta_enum<mud::PrefabType>();
    }
    
    {
        static Meta meta = { type<mud::ShaderType>(), &namspc({ "mud" }), "ShaderType", sizeof(mud::ShaderType), TypeClass::Enum };
        static Enum enu = { type<mud::ShaderType>(),
            true,
            { "Fragment", "Vertex", "Count" },
            { 0, 1, 2 },
            { var(ShaderType::Fragment), var(ShaderType::Vertex), var(ShaderType::Count) }
        };
        meta_enum<mud::ShaderType>();
    }
    
    {
        static Meta meta = { type<mud::Shading>(), &namspc({ "mud" }), "Shading", sizeof(mud::Shading), TypeClass::Enum };
        static Enum enu = { type<mud::Shading>(),
            true,
            { "Wireframe", "Unshaded", "Shaded", "Clear" },
            { 0, 1, 2, 3 },
            { var(Shading::Wireframe), var(Shading::Unshaded), var(Shading::Shaded), var(Shading::Clear) }
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
            { var(TextureChannel::Red), var(TextureChannel::Green), var(TextureChannel::Blue), var(TextureChannel::Alpha), var(TextureChannel::All) }
        };
        meta_enum<mud::TextureChannel>();
    }
    
    {
        static Meta meta = { type<mud::TextureHint>(), &namspc({ "mud" }), "TextureHint", sizeof(mud::TextureHint), TypeClass::Enum };
        static Enum enu = { type<mud::TextureHint>(),
            true,
            { "Black", "White", "Normal" },
            { 0, 1, 2 },
            { var(TextureHint::Black), var(TextureHint::White), var(TextureHint::Normal) }
        };
        meta_enum<mud::TextureHint>();
    }
    
    {
        static Meta meta = { type<mud::TextureSampler>(), &namspc({ "mud" }), "TextureSampler", sizeof(mud::TextureSampler), TypeClass::Enum };
        static Enum enu = { type<mud::TextureSampler>(),
            true,
            { "Source0", "Source1", "Source2", "Source3", "SourceDepth", "Color", "Albedo", "Metallic", "Roughness", "Emissive", "Normal", "AO", "Depth", "Skeleton", "ShadowCSM", "ShadowAtlas", "Radiance", "ReflectionProbe", "GIProbe" },
            { 0, 1, 2, 3, 3, 0, 0, 1, 2, 3, 4, 11, 12, 5, 6, 7, 8, 9, 10 },
            { var(TextureSampler::Source0), var(TextureSampler::Source1), var(TextureSampler::Source2), var(TextureSampler::Source3), var(TextureSampler::SourceDepth), var(TextureSampler::Color), var(TextureSampler::Albedo), var(TextureSampler::Metallic), var(TextureSampler::Roughness), var(TextureSampler::Emissive), var(TextureSampler::Normal), var(TextureSampler::AO), var(TextureSampler::Depth), var(TextureSampler::Skeleton), var(TextureSampler::ShadowCSM), var(TextureSampler::ShadowAtlas), var(TextureSampler::Radiance), var(TextureSampler::ReflectionProbe), var(TextureSampler::GIProbe) }
        };
        meta_enum<mud::TextureSampler>();
    }
    
    
    // Sequences
    {
        static Meta meta = { type<std::vector<mud::PrefabNode>>(), &namspc({}), "std::vector<mud::PrefabNode>", sizeof(std::vector<mud::PrefabNode>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::PrefabNode>>() };
        cls.m_content = &type<mud::PrefabNode>();
        meta_sequence<std::vector<mud::PrefabNode>, mud::PrefabNode>();
    }
    
    
    
    
    
    
        
    // mud::Animated
    {
        static Meta meta = { type<mud::Animated>(), &namspc({ "mud" }), "Animated", sizeof(mud::Animated), TypeClass::Object };
        static Class cls = { type<mud::Animated>(),
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
        
        
        
        
        meta_class<mud::Animated>();
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
                { type<mud::Background>(), member_address(&mud::Background::m_mode), type<mud::BackgroundMode>(), "mode", var(mud::BackgroundMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Background>(), member_address(&mud::Background::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Background>(), member_address(&mud::Background::m_custom_program), type<mud::Program>(), "custoprogram", Ref(type<mud::Program>()), Member::Flags(Member::Pointer|Member::Mutable|Member::Link) }
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
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_blend_mode), type<mud::BlendMode>(), "blend_mode", var(mud::BlendMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_cull_mode), type<mud::CullMode>(), "cull_mode", var(mud::CullMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_depth_draw_mode), type<mud::DepthDraw>(), "depth_draw_mode", var(mud::DepthDraw()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_depth_test), type<mud::DepthTest>(), "depth_test", var(mud::DepthTest()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_uv1_scale), type<mud::vec2>(), "uv1_scale", var(mud::vec2()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_uv1_offset), type<mud::vec2>(), "uv1_offset", var(mud::vec2()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_uv2_scale), type<mud::vec2>(), "uv2_scale", var(mud::vec2()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_uv2_offset), type<mud::vec2>(), "uv2_offset", var(mud::vec2()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_is_alpha), type<bool>(), "is_alpha", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BaseMaterialBlock>(), member_address(&mud::BaseMaterialBlock::m_screen_filter), type<bool>(), "screen_filter", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Bone>(), member_address(&mud::Bone::m_position), type<mud::vec3>(), "position", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Bone>(), member_address(&mud::Bone::m_rotation), type<mud::quat>(), "rotation", var(mud::quat()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Bone>(), member_address(&mud::Bone::m_scale), type<mud::vec3>(), "scale", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Camera>(), member_address(&mud::Camera::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Camera>(), member_address(&mud::Camera::m_node), type<mud::Node3>(), "node", Ref(type<mud::Node3>()), Member::Mutable },
                { type<mud::Camera>(), member_address(&mud::Camera::m_target), type<mud::Node3>(), "target", Ref(type<mud::Node3>()), Member::Mutable },
                { type<mud::Camera>(), member_address(&mud::Camera::m_transform), type<mud::mat4>(), "transform", var(mud::mat4()), Member::Value },
                { type<mud::Camera>(), member_address(&mud::Camera::m_projection), type<mud::mat4>(), "projection", var(mud::mat4()), Member::Value },
                { type<mud::Camera>(), member_address(&mud::Camera::m_fov), type<float>(), "fov", var(float(60.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Camera>(), member_address(&mud::Camera::m_aspect), type<float>(), "aspect", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Camera>(), member_address(&mud::Camera::m_near), type<float>(), "near", var(float(0.001f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Camera>(), member_address(&mud::Camera::m_far), type<float>(), "far", var(float(100.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Camera>(), member_address(&mud::Camera::m_orthogonal), type<bool>(), "orthogonal", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Camera>(), member_address(&mud::Camera::m_height), type<float>(), "height", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Camera>(), member_address(&mud::Camera::m_optimize_ends), type<bool>(), "optimize_ends", var(bool(true)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Camera>(), member_address(&mud::Camera::m_lod_offsets), type<mud::vec4>(), "lod_offsets", var(mud::vec4()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Environment>(), member_address(&mud::Environment::m_background), type<mud::Background>(), "background", var(mud::Background()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Environment>(), member_address(&mud::Environment::m_radiance), type<mud::Radiance>(), "radiance", var(mud::Radiance()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Environment>(), member_address(&mud::Environment::m_sun), type<mud::Sun>(), "sun", var(mud::Sun()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_fov), type<float>(), "fov", var(float(60.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_aspect), type<float>(), "aspect", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_near), type<float>(), "near", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_far), type<float>(), "far", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_center), type<mud::vec3>(), "center", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Frustum>(), member_address(&mud::Frustum::m_radius), type<float>(), "radius", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::GfxBlock>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None },
                { type<mud::GfxBlock>(), member_address(&mud::GfxBlock::m_index), type<uint8_t>(), "index", var(uint8_t()), Member::Value }
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
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::GfxSystem>();
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
                { type<mud::Gnode>(), "begin", member_address(&mud::Gnode::begin), [](Ref object, array<Var> args, Var& result) { UNUSED(args);result = Ref(&val<mud::Gnode>(object).begin()); }, {}, Ref(type<mud::Gnode>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Gnode>();
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
                { type<mud::Item>(), Address(), type<mud::Node3>(), "node", Ref(type<mud::Node3>()), Member::None },
                { type<mud::Item>(), member_address(&mud::Item::m_model), type<mud::Model>(), "model", Ref(type<mud::Model>()), Member::Flags(Member::Pointer|Member::Mutable|Member::Link) },
                { type<mud::Item>(), member_address(&mud::Item::m_flags), type<uint32_t>(), "flags", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Item>(), member_address(&mud::Item::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Item>(), member_address(&mud::Item::m_material), type<mud::Material>(), "material", Ref(type<mud::Material>()), Member::Flags(Member::Pointer|Member::Mutable|Member::Link) },
                { type<mud::Item>(), member_address(&mud::Item::m_visible), type<bool>(), "visible", var(bool(true)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Item>(), member_address(&mud::Item::m_cast_shadows), type<mud::ItemShadow>(), "cast_shadows", var(mud::ItemShadow()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Item>(), member_address(&mud::Item::m_rig), type<mud::Rig>(), "rig", Ref(type<mud::Rig>()), Member::Flags(Member::Pointer|Member::Link) }
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
                { type<mud::Light>(), Address(), type<mud::Node3>(), "node", Ref(type<mud::Node3>()), Member::None },
                { type<mud::Light>(), member_address(&mud::Light::m_type), type<mud::LightType>(), "type", var(mud::LightType()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_visible), type<bool>(), "visible", var(bool(true)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_range), type<float>(), "range", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_energy), type<float>(), "energy", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_specular), type<float>(), "specular", var(float(0.5f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_shadows), type<bool>(), "shadows", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_colour), type<mud::Colour>(), "shadow_colour", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_range), type<float>(), "shadow_range", var(float(100.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_attenuation), type<float>(), "attenuation", var(float(0.5f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_layers), type<uint32_t>(), "layers", var(uint32_t(0xFFFFFFFF)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_last_render), type<uint32_t>(), "last_render", var(uint32_t()), Member::Value },
                { type<mud::Light>(), member_address(&mud::Light::m_last_update), type<uint32_t>(), "last_update", var(uint32_t()), Member::Value },
                { type<mud::Light>(), member_address(&mud::Light::m_spot_angle), type<float>(), "spot_angle", var(float(45.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_spot_attenuation), type<float>(), "spot_attenuation", var(float(0.5f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_flags), type<mud::ShadowFlags>(), "shadow_flags", var(mud::ShadowFlags()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_num_splits), type<uint8_t>(), "shadow_nusplits", var(uint8_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_split_distribution), type<float>(), "shadow_split_distribution", var(float(0.6f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_normal_bias), type<float>(), "shadow_normal_bias", var(float(0.1f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Light>(), member_address(&mud::Light::m_shadow_bias), type<float>(), "shadow_bias", var(float(0.f)), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Material>(), member_address(&mud::Material::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value },
                { type<mud::Material>(), member_address(&mud::Material::m_program), type<mud::Program>(), "program", Ref(type<mud::Program>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Material>(), member_address(&mud::Material::m_base_block), type<mud::BaseMaterialBlock>(), "base_block", var(mud::BaseMaterialBlock()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Material>(), member_address(&mud::Material::m_unshaded_block), type<mud::UnshadedMaterialBlock>(), "unshaded_block", var(mud::UnshadedMaterialBlock()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Material>(), member_address(&mud::Material::m_pbr_block), type<mud::PbrMaterialBlock>(), "pbr_block", var(mud::PbrMaterialBlock()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::MaterialParam<float>>(), member_address(&mud::MaterialParam<float>::m_value), type<float>(), "value", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::MaterialParam<float>>(), member_address(&mud::MaterialParam<float>::m_texture), type<mud::Texture>(), "texture", Ref(type<mud::Texture>()), Member::Flags(Member::Pointer|Member::Mutable|Member::Link) },
                { type<mud::MaterialParam<float>>(), member_address(&mud::MaterialParam<float>::m_channel), type<mud::TextureChannel>(), "channel", var(mud::TextureChannel()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::MaterialParam<mud::Colour>>(), member_address(&mud::MaterialParam<mud::Colour>::m_value), type<mud::Colour>(), "value", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::MaterialParam<mud::Colour>>(), member_address(&mud::MaterialParam<mud::Colour>::m_texture), type<mud::Texture>(), "texture", Ref(type<mud::Texture>()), Member::Flags(Member::Pointer|Member::Mutable|Member::Link) },
                { type<mud::MaterialParam<mud::Colour>>(), member_address(&mud::MaterialParam<mud::Colour>::m_channel), type<mud::TextureChannel>(), "channel", var(mud::TextureChannel()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_name), type<mud::strung>(), "name", var(mud::strung()), Member::Value },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_draw_mode), type<mud::DrawMode>(), "draw_mode", var(mud::DrawMode()), Member::Value },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_aabb), type<mud::Aabb>(), "aabb", var(mud::Aabb()), Member::Value },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_radius), type<float>(), "radius", var(float(0.f)), Member::Value },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_origin), type<mud::vec3>(), "origin", var(mud::vec3()), Member::Value },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_readback), type<bool>(), "readback", var(bool(false)), Member::Value },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_vertexCount), type<size_t>(), "vertexCount", var(size_t()), Member::Value },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_indexCount), type<size_t>(), "indexCount", var(size_t()), Member::Value },
                { type<mud::Mesh>(), member_address(&mud::Mesh::m_material), type<mud::Material>(), "material", Ref(type<mud::Material>()), Member::Flags(Member::Pointer|Member::Link) }
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
                { type<mud::Model>(), member_address(&mud::Model::m_name), type<mud::strung>(), "name", var(mud::strung()), Member::Value },
                { type<mud::Model>(), member_address(&mud::Model::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value },
                { type<mud::Model>(), member_address(&mud::Model::m_aabb), type<mud::Aabb>(), "aabb", var(mud::Aabb()), Member::Value },
                { type<mud::Model>(), member_address(&mud::Model::m_radius), type<float>(), "radius", var(float(0.f)), Member::Value },
                { type<mud::Model>(), member_address(&mud::Model::m_origin), type<mud::vec3>(), "origin", var(mud::vec3()), Member::Value }
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
                { type<mud::ModelItem>(), member_address(&mud::ModelItem::m_transform), type<mud::mat4>(), "transform", var(mud::mat4()), Member::Value },
                { type<mud::ModelItem>(), member_address(&mud::ModelItem::m_mesh), type<mud::Mesh>(), "mesh", Ref(type<mud::Mesh>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::ModelItem>(), member_address(&mud::ModelItem::m_skin), type<int>(), "skin", var(int()), Member::Value },
                { type<mud::ModelItem>(), member_address(&mud::ModelItem::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Value }
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
                { type<mud::Node3>(), member_address(&mud::Node3::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Node3>(), member_address(&mud::Node3::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value },
                { type<mud::Node3>(), member_address(&mud::Node3::m_position), type<mud::vec3>(), "position", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Node3>(), member_address(&mud::Node3::m_rotation), type<mud::quat>(), "rotation", var(mud::quat()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Node3>(), member_address(&mud::Node3::m_scale), type<mud::vec3>(), "scale", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Node3>(), member_address(&mud::Node3::m_visible), type<bool>(), "visible", var(bool(true)), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_name), type<mud::strung>(), "name", var(mud::strung()), Member::Value },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_duration), type<float>(), "duration", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_start_time), type<float>(), "start_time", var(float(0.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_loop), type<bool>(), "loop", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_shape), type<mud::ShapeVar>(), "shape", var(mud::ShapeVar()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_direction), type<mud::EmitterDirection>(), "direction", var(mud::EmitterDirection()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_absolute_direction), type<mud::vec3>(), "absolute_direction", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_blend_mode), type<mud::BlendMode>(), "blend_mode", var(mud::BlendMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_position), type<mud::ValueTrack<mud::vec3>>(), "position", var(mud::ValueTrack<mud::vec3>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_rotation), type<mud::ValueTrack<mud::quat>>(), "rotation", var(mud::ValueTrack<mud::quat>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_volume), type<mud::ValueTrack<float>>(), "volume", var(mud::ValueTrack<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_rate), type<mud::ValueTrack<uint32_t>>(), "rate", var(mud::ValueTrack<uint32_t>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_lifetime), type<mud::ValueTrack<float>>(), "lifetime", var(mud::ValueTrack<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_gravity), type<mud::ValueTrack<float>>(), "gravity", var(mud::ValueTrack<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_speed), type<mud::ValueTrack<float>>(), "speed", var(mud::ValueTrack<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_angle), type<mud::ValueTrack<float>>(), "angle", var(mud::ValueTrack<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_blend), type<mud::ValueTrack<float>>(), "blend", var(mud::ValueTrack<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_colour), type<mud::ValueTrack<mud::Colour>>(), "colour", var(mud::ValueTrack<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_scale), type<mud::ValueTrack<float>>(), "scale", var(mud::ValueTrack<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_sprite_frame), type<mud::ValueTrack<float>>(), "sprite_frame", var(mud::ValueTrack<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ParticleGenerator>(), member_address(&mud::ParticleGenerator::m_sprite_name), type<mud::strung>(), "sprite_name", var(mud::strung()), Member::Flags(Member::Value|Member::Mutable) }
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
    
    
    
    
    
        
    // mud::Particles
    {
        static Meta meta = { type<mud::Particles>(), &namspc({ "mud" }), "Particles", sizeof(mud::Particles), TypeClass::Object };
        static Class cls = { type<mud::Particles>(),
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
                { type<mud::Particles>(), Address(), type<mud::Node3>(), "node", Ref(type<mud::Node3>()), Member::None }
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
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_albedo), type<mud::MaterialParam<mud::Colour>>(), "albedo", var(mud::MaterialParam<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_specular), type<float>(), "specular", var(float(0.5f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_metallic), type<mud::MaterialParam<float>>(), "metallic", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_roughness), type<mud::MaterialParam<float>>(), "roughness", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_emissive), type<mud::MaterialParam<mud::Colour>>(), "emissive", var(mud::MaterialParam<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_emissive_energy), type<float>(), "emissive_energy", var(float(0.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_normal), type<mud::MaterialParam<float>>(), "normal", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_rim), type<mud::MaterialParam<float>>(), "rim", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_rim_tint), type<float>(), "ritint", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_clearcoat), type<mud::MaterialParam<float>>(), "clearcoat", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_clearcoat_gloss), type<float>(), "clearcoat_gloss", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_anisotropy), type<mud::MaterialParam<float>>(), "anisotropy", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_subsurface), type<mud::MaterialParam<float>>(), "subsurface", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_transmission), type<mud::MaterialParam<mud::Colour>>(), "transmission", var(mud::MaterialParam<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_refraction), type<mud::MaterialParam<float>>(), "refraction", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_ambient_occlusion), type<mud::MaterialParam<float>>(), "ambient_occlusion", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_depth), type<mud::MaterialParam<float>>(), "depth", var(mud::MaterialParam<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_deep_parallax), type<bool>(), "deep_parallax", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_diffuse_mode), type<mud::PbrDiffuseMode>(), "diffuse_mode", var(mud::PbrDiffuseMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PbrMaterialBlock>(), member_address(&mud::PbrMaterialBlock::m_specular_mode), type<mud::PbrSpecularMode>(), "specular_mode", var(mud::PbrSpecularMode()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Prefab>(), member_address(&mud::Prefab::m_name), type<mud::strung>(), "name", var(mud::strung()), Member::Value },
                { type<mud::Prefab>(), member_address(&mud::Prefab::m_node), type<mud::PrefabNode>(), "node", var(mud::PrefabNode()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::PrefabNode>(), member_address(&mud::PrefabNode::m_transform), type<mud::Transform>(), "transform", var(mud::Transform()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PrefabNode>(), member_address(&mud::PrefabNode::m_prefab_type), type<mud::PrefabType>(), "prefab_type", var(mud::PrefabType()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PrefabNode>(), member_address(&mud::PrefabNode::m_call), type<mud::Call>(), "call", var(mud::Call()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::PrefabNode>(), member_address(&mud::PrefabNode::m_nodes), type<std::vector<mud::PrefabNode>>(), "nodes", var(std::vector<mud::PrefabNode>()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Program>(), member_address(&mud::Program::name), type<cstring>(), "name", var(cstring()), Member::Value }
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
                { type<mud::Radiance>(), member_address(&mud::Radiance::m_energy), type<float>(), "energy", var(float(1.0f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Radiance>(), member_address(&mud::Radiance::m_ambient), type<float>(), "ambient", var(float(1.0f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Radiance>(), member_address(&mud::Radiance::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Radiance>(), member_address(&mud::Radiance::m_texture), type<mud::Texture>(), "texture", Ref(type<mud::Texture>()), Member::Flags(Member::Pointer|Member::Mutable|Member::Link) }
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
                { type<mud::Scene>(), member_address(&mud::Scene::m_graph), type<mud::Gnode>(), "graph", Ref(type<mud::Gnode>()), Member::None },
                { type<mud::Scene>(), member_address(&mud::Scene::m_root_node), type<mud::Node3>(), "root_node", Ref(type<mud::Node3>()), Member::None },
                { type<mud::Scene>(), member_address(&mud::Scene::m_environment), type<mud::Environment>(), "environment", var(mud::Environment()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Sun>(), member_address(&mud::Sun::azimuth), type<float>(), "azimuth", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Sun>(), member_address(&mud::Sun::elevation), type<float>(), "elevation", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Sun>(), member_address(&mud::Sun::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Sun>(), member_address(&mud::Sun::m_intensity), type<float>(), "intensity", var(float(0.f)), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Texture>(), member_address(&mud::Texture::m_width), type<uint16_t>(), "width", var(uint16_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Texture>(), member_address(&mud::Texture::m_height), type<uint16_t>(), "height", var(uint16_t()), Member::Flags(Member::Value|Member::Mutable) }
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
    
    
    
    
    
        
    // mud::Transform
    {
        static Meta meta = { type<mud::Transform>(), &namspc({ "mud" }), "Transform", sizeof(mud::Transform), TypeClass::Struct };
        static Class cls = { type<mud::Transform>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Transform>(), [](Ref ref, Ref other) { new(&val<mud::Transform>(ref)) mud::Transform(val<mud::Transform>(other)); } }
            },
            // members
            {
                { type<mud::Transform>(), member_address(&mud::Transform::m_position), type<mud::vec3>(), "position", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Transform>(), member_address(&mud::Transform::m_rotation), type<mud::quat>(), "rotation", var(mud::quat()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Transform>(), member_address(&mud::Transform::m_scale), type<mud::vec3>(), "scale", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Transform>();
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
                { type<mud::UnshadedMaterialBlock>(), member_address(&mud::UnshadedMaterialBlock::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::UnshadedMaterialBlock>(), member_address(&mud::UnshadedMaterialBlock::m_colour), type<mud::MaterialParam<mud::Colour>>(), "colour", var(mud::MaterialParam<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) }
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
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_camera), type<mud::Camera>(), "camera", Ref(type<mud::Camera>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_index), type<uint16_t>(), "index", var(uint16_t()), Member::Value },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_rect), type<mud::uvec4>(), "rect", var(mud::uvec4()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_scissor), type<bool>(), "scissor", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_clear_colour), type<mud::Colour>(), "clear_colour", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_shading), type<mud::Shading>(), "shading", var(mud::Shading()), Member::Flags(Member::Value|Member::Mutable) }
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
    
    
    
        
    // mud::BlockParticles
    {
        static Meta meta = { type<mud::BlockParticles>(), &namspc({ "mud" }), "BlockParticles", sizeof(mud::BlockParticles), TypeClass::Object };
        static Class cls = { type<mud::BlockParticles>(),
            // bases
            { &type<mud::DrawBlock>() },
            { base_offset<mud::BlockParticles, mud::DrawBlock>() },
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
    
    
        
    // mud::ParticleEmitter
    {
        static Meta meta = { type<mud::ParticleEmitter>(), &namspc({ "mud" }), "ParticleEmitter", sizeof(mud::ParticleEmitter), TypeClass::Struct };
        static Class cls = { type<mud::ParticleEmitter>(),
            // bases
            { &type<mud::ParticleGenerator>() },
            { base_offset<mud::ParticleEmitter, mud::ParticleGenerator>() },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::ParticleEmitter>(), [](Ref ref, Ref other) { new(&val<mud::ParticleEmitter>(ref)) mud::ParticleEmitter(val<mud::ParticleEmitter>(other)); } }
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
        
        
        
        
        meta_class<mud::ParticleEmitter>();
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
    

    
        module.m_types.push_back(&type<mud::Animated>());
        module.m_types.push_back(&type<mud::AnimatedTrack>());
        module.m_types.push_back(&type<mud::Animation>());
        module.m_types.push_back(&type<mud::AnimationPlay>());
        module.m_types.push_back(&type<mud::AnimationTrack>());
        module.m_types.push_back(&type<mud::Background>());
        module.m_types.push_back(&type<mud::BackgroundMode>());
        module.m_types.push_back(&type<mud::BaseMaterialBlock>());
        module.m_types.push_back(&type<mud::BlendMode>());
        module.m_types.push_back(&type<mud::Bone>());
        module.m_types.push_back(&type<mud::Camera>());
        module.m_types.push_back(&type<mud::CullMode>());
        module.m_types.push_back(&type<mud::DepthDraw>());
        module.m_types.push_back(&type<mud::DepthTest>());
        module.m_types.push_back(&type<mud::EmitterDirection>());
        module.m_types.push_back(&type<mud::Environment>());
        module.m_types.push_back(&type<mud::Filter>());
        module.m_types.push_back(&type<mud::FrameBuffer>());
        module.m_types.push_back(&type<mud::Frustum>());
        module.m_types.push_back(&type<mud::FrustumSlice>());
        module.m_types.push_back(&type<mud::GfxBlock>());
        module.m_types.push_back(&type<mud::GfxContext>());
        module.m_types.push_back(&type<mud::GfxSystem>());
        module.m_types.push_back(&type<mud::Gnode>());
        module.m_types.push_back(&type<mud::ImmediateDraw>());
        module.m_types.push_back(&type<mud::Interpolation>());
        module.m_types.push_back(&type<mud::IsometricAngle>());
        module.m_types.push_back(&type<mud::Item>());
        module.m_types.push_back(&type<mud::ItemFlag>());
        module.m_types.push_back(&type<mud::ItemShadow>());
        module.m_types.push_back(&type<mud::Joint>());
        module.m_types.push_back(&type<mud::Light>());
        module.m_types.push_back(&type<mud::LightType>());
        module.m_types.push_back(&type<mud::MSAA>());
        module.m_types.push_back(&type<mud::Material>());
        module.m_types.push_back(&type<mud::MaterialFlag>());
        module.m_types.push_back(&type<mud::MaterialParam<float>>());
        module.m_types.push_back(&type<mud::MaterialParam<mud::Colour>>());
        module.m_types.push_back(&type<mud::Mesh>());
        module.m_types.push_back(&type<mud::Model>());
        module.m_types.push_back(&type<mud::ModelItem>());
        module.m_types.push_back(&type<mud::Month>());
        module.m_types.push_back(&type<mud::Node3>());
        module.m_types.push_back(&type<mud::ParticleGenerator>());
        module.m_types.push_back(&type<mud::Particles>());
        module.m_types.push_back(&type<mud::PbrDiffuseMode>());
        module.m_types.push_back(&type<mud::PbrMaterialBlock>());
        module.m_types.push_back(&type<mud::PbrSpecularMode>());
        module.m_types.push_back(&type<mud::Prefab>());
        module.m_types.push_back(&type<mud::PrefabNode>());
        module.m_types.push_back(&type<mud::PrefabType>());
        module.m_types.push_back(&type<mud::Program>());
        module.m_types.push_back(&type<mud::Radiance>());
        module.m_types.push_back(&type<mud::RenderFrame>());
        module.m_types.push_back(&type<mud::RenderQuad>());
        module.m_types.push_back(&type<mud::Rig>());
        module.m_types.push_back(&type<mud::Scene>());
        module.m_types.push_back(&type<mud::ShaderType>());
        module.m_types.push_back(&type<mud::Shading>());
        module.m_types.push_back(&type<mud::ShadowFlags>());
        module.m_types.push_back(&type<mud::Shot>());
        module.m_types.push_back(&type<mud::Skeleton>());
        module.m_types.push_back(&type<mud::Skin>());
        module.m_types.push_back(&type<mud::Sun>());
        module.m_types.push_back(&type<mud::SymbolIndex>());
        module.m_types.push_back(&type<mud::Texture>());
        module.m_types.push_back(&type<mud::TextureChannel>());
        module.m_types.push_back(&type<mud::TextureHint>());
        module.m_types.push_back(&type<mud::TextureSampler>());
        module.m_types.push_back(&type<mud::Transform>());
        module.m_types.push_back(&type<mud::UnshadedMaterialBlock>());
        module.m_types.push_back(&type<mud::Viewport>());
        module.m_types.push_back(&type<std::vector<mud::PrefabNode>>());
        module.m_types.push_back(&type<mud::BlockCopy>());
        module.m_types.push_back(&type<mud::BlockFilter>());
        module.m_types.push_back(&type<mud::BlockResolve>());
        module.m_types.push_back(&type<mud::BlockSky>());
        module.m_types.push_back(&type<mud::DrawBlock>());
        module.m_types.push_back(&type<mud::BlockParticles>());
        module.m_types.push_back(&type<mud::ParticleEmitter>());
        module.m_types.push_back(&type<mud::RenderTarget>());
    
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::node(val<mud::Gnode>(args[0]), args[1], val<mud::vec3>(args[2]), val<mud::quat>(args[3]), val<mud::vec3>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "object", Ref(), Param::Flags(Param::Nullable|Param::Default) }, { "position", var(mud::vec3()), Param::Default }, { "rotation", var(mud::quat()), Param::Default }, { "scale", var(mud::vec3()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "node", function_id<mud::Gnode&(*)(mud::Gnode&, mud::Ref, const mud::vec3&, const mud::quat&, const mud::vec3&)>(&mud::gfx::node), func, params, Ref(type<mud::Gnode>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::node_model(val<mud::Gnode>(args[0]), val<mud::Model>(args[1]), val<mud::vec3>(args[2]), val<mud::quat>(args[3]), val<mud::vec3>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "model", Ref(type<mud::Model>()) }, { "position", var(mud::vec3()) }, { "rotation", var(mud::quat()), Param::Default }, { "scale", var(mud::vec3()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "node_model", function_id<mud::Item&(*)(mud::Gnode&, const mud::Model&, const mud::vec3&, const mud::quat&, const mud::vec3&)>(&mud::gfx::node_model), func, params, Ref(type<mud::Item>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::node_shape(val<mud::Gnode>(args[0]), val<mud::Shape>(args[1]), val<mud::Symbol>(args[2]), val<mud::vec3>(args[3]), val<mud::quat>(args[4]), val<mud::vec3>(args[5]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "shape", Ref(type<mud::Shape>()) }, { "symbol", var(mud::Symbol()) }, { "position", var(mud::vec3()) }, { "rotation", var(mud::quat()), Param::Default }, { "scale", var(mud::vec3()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "node_shape", function_id<mud::Item&(*)(mud::Gnode&, const mud::Shape&, const mud::Symbol&, const mud::vec3&, const mud::quat&, const mud::vec3&)>(&mud::gfx::node_shape), func, params, Ref(type<mud::Item>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::shape(val<mud::Gnode>(args[0]), val<mud::Shape>(args[1]), val<mud::Symbol>(args[2]), val<uint32_t>(args[3]), &val<mud::Material>(args[4]), val<size_t>(args[5]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "shape", Ref(type<mud::Shape>()) }, { "symbol", var(mud::Symbol()) }, { "flags", var(uint32_t()), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "shape", function_id<mud::Item&(*)(mud::Gnode&, const mud::Shape&, const mud::Symbol&, uint32_t, mud::Material*, size_t)>(&mud::gfx::shape), func, params, Ref(type<mud::Item>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::draw(val<mud::Gnode>(args[0]), val<mud::Shape>(args[1]), val<mud::Symbol>(args[2]), val<uint32_t>(args[3])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "shape", Ref(type<mud::Shape>()) }, { "symbol", var(mud::Symbol()) }, { "flags", var(uint32_t()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "draw", function_id<void(*)(mud::Gnode&, const mud::Shape&, const mud::Symbol&, uint32_t)>(&mud::gfx::draw), func, params, Var() });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::sprite(val<mud::Gnode>(args[0]), val<mud::Image256>(args[1]), val<mud::vec2>(args[2]), val<uint32_t>(args[3]), &val<mud::Material>(args[4]), val<size_t>(args[5]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "image", var(mud::Image256()) }, { "size", var(mud::vec2()) }, { "flags", var(uint32_t()), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "sprite", function_id<mud::Item&(*)(mud::Gnode&, const mud::Image256&, const mud::vec2&, uint32_t, mud::Material*, size_t)>(&mud::gfx::sprite), func, params, Ref(type<mud::Item>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::item(val<mud::Gnode>(args[0]), val<mud::Model>(args[1]), val<uint32_t>(args[2]), &val<mud::Material>(args[3]), val<size_t>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "model", Ref(type<mud::Model>()) }, { "flags", var(uint32_t()), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "item", function_id<mud::Item&(*)(mud::Gnode&, const mud::Model&, uint32_t, mud::Material*, size_t)>(&mud::gfx::item), func, params, Ref(type<mud::Item>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(mud::gfx::model(val<mud::Gnode>(args[0]), val<std::string>(args[1]), val<uint32_t>(args[2]), &val<mud::Material>(args[3]), val<size_t>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "name", var(std::string()) }, { "flags", var(uint32_t()), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "model", function_id<mud::Item*(*)(mud::Gnode&, const std::string&, uint32_t, mud::Material*, size_t)>(&mud::gfx::model), func, params, Ref(type<mud::Item>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::animated(val<mud::Gnode>(args[0]), val<mud::Item>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "item", Ref(type<mud::Item>()) } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "animated", function_id<mud::Animated&(*)(mud::Gnode&, mud::Item&)>(&mud::gfx::animated), func, params, Ref(type<mud::Animated>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::particles(val<mud::Gnode>(args[0]), val<mud::ParticleGenerator>(args[1]), val<uint32_t>(args[2]), val<size_t>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "emitter", var(mud::ParticleGenerator()) }, { "flags", var(uint32_t()), Param::Default }, { "instances", var(size_t()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "particles", function_id<mud::Particles&(*)(mud::Gnode&, const mud::ParticleGenerator&, uint32_t, size_t)>(&mud::gfx::particles), func, params, Ref(type<mud::Particles>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::light(val<mud::Gnode>(args[0]), val<mud::LightType>(args[1]), val<bool>(args[2]), val<mud::Colour>(args[3]), val<float>(args[4]), val<float>(args[5]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "type", var(mud::LightType()) }, { "shadows", var(bool()) }, { "colour", var(mud::Colour()) }, { "range", var(float(0.f)), Param::Default }, { "attenuation", var(float(0.5f)), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "light", function_id<mud::Light&(*)(mud::Gnode&, mud::LightType, bool, mud::Colour, float, float)>(&mud::gfx::light), func, params, Ref(type<mud::Light>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::sun_light(val<mud::Gnode>(args[0]), val<float>(args[1]), val<float>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "azimuth", var(float()) }, { "elevation", var(float()) } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "sun_light", function_id<mud::Light&(*)(mud::Gnode&, float, float)>(&mud::gfx::sun_light), func, params, Ref(type<mud::Light>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::gfx::radiance(val<mud::Gnode>(args[0]), val<std::string>(args[1]), val<mud::BackgroundMode>(args[2])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "texture", var(std::string()) }, { "background", var(mud::BackgroundMode()) } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "radiance", function_id<void(*)(mud::Gnode&, const std::string&, mud::BackgroundMode)>(&mud::gfx::radiance), func, params, Var() });
        }
    }
#endif

}
