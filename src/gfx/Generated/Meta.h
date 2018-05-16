

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
            { "Wireframe", "Unshaded", "Shaded" },
            { 0, 1, 2 },
            { var(Shading::Wireframe), var(Shading::Unshaded), var(Shading::Shaded) }
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
    
    {
        static Meta meta = { type<mud::TonemapMode>(), &namspc({ "mud" }), "TonemapMode", sizeof(mud::TonemapMode), TypeClass::Enum };
        static Enum enu = { type<mud::TonemapMode>(),
            true,
            { "Linear", "Reinhardt", "Filmic", "ACES" },
            { 0, 1, 2, 3 },
            { var(TonemapMode::Linear), var(TonemapMode::Reinhardt), var(TonemapMode::Filmic), var(TonemapMode::ACES) }
        };
        meta_enum<mud::TonemapMode>();
    }
    
    {
        static Meta meta = { type<mud::TrackMode>(), &namspc({ "mud" }), "TrackMode", sizeof(mud::TrackMode), TypeClass::Enum };
        static Enum enu = { type<mud::TrackMode>(),
            true,
            { "Constant", "ConstantRandom", "Curve", "CurveRandom" },
            { 0, 1, 2, 3 },
            { var(TrackMode::Constant), var(TrackMode::ConstantRandom), var(TrackMode::Curve), var(TrackMode::CurveRandom) }
        };
        meta_enum<mud::TrackMode>();
    }
    
    {
        static Meta meta = { type<glTFAlphaMode>(), &namspc({}), "glTFAlphaMode", sizeof(glTFAlphaMode), TypeClass::Enum };
        static Enum enu = { type<glTFAlphaMode>(),
            true,
            { "OPAQUE", "MASK", "BLEND" },
            { 0, 1, 2 },
            { var(glTFAlphaMode::OPAQUE), var(glTFAlphaMode::MASK), var(glTFAlphaMode::BLEND) }
        };
        meta_enum<glTFAlphaMode>();
    }
    
    {
        static Meta meta = { type<glTFComponentType>(), &namspc({}), "glTFComponentType", sizeof(glTFComponentType), TypeClass::Enum };
        static Enum enu = { type<glTFComponentType>(),
            true,
            { "BYTE", "UNSIGNED_BYTE", "SHORT", "UNSIGNED_SHORT", "INT", "FLOAT" },
            { 5120, 5121, 5122, 5123, 5125, 5126 },
            { var(glTFComponentType::BYTE), var(glTFComponentType::UNSIGNED_BYTE), var(glTFComponentType::SHORT), var(glTFComponentType::UNSIGNED_SHORT), var(glTFComponentType::INT), var(glTFComponentType::FLOAT) }
        };
        meta_enum<glTFComponentType>();
    }
    
    {
        static Meta meta = { type<glTFInterpolation>(), &namspc({}), "glTFInterpolation", sizeof(glTFInterpolation), TypeClass::Enum };
        static Enum enu = { type<glTFInterpolation>(),
            true,
            { "LINEAR", "STEP", "CATMULLROMSPLINE", "CUBIC_SPLINE" },
            { 0, 1, 2, 3 },
            { var(glTFInterpolation::LINEAR), var(glTFInterpolation::STEP), var(glTFInterpolation::CATMULLROMSPLINE), var(glTFInterpolation::CUBIC_SPLINE) }
        };
        meta_enum<glTFInterpolation>();
    }
    
    {
        static Meta meta = { type<glTFPrimitiveType>(), &namspc({}), "glTFPrimitiveType", sizeof(glTFPrimitiveType), TypeClass::Enum };
        static Enum enu = { type<glTFPrimitiveType>(),
            true,
            { "POINTS", "LINES", "LINE_LOOP", "LINE_STRIP", "TRIANGLES", "TRIANGLE_STRIP", "TRIANGLE_FAN" },
            { 0, 1, 2, 3, 4, 5, 6 },
            { var(glTFPrimitiveType::POINTS), var(glTFPrimitiveType::LINES), var(glTFPrimitiveType::LINE_LOOP), var(glTFPrimitiveType::LINE_STRIP), var(glTFPrimitiveType::TRIANGLES), var(glTFPrimitiveType::TRIANGLE_STRIP), var(glTFPrimitiveType::TRIANGLE_FAN) }
        };
        meta_enum<glTFPrimitiveType>();
    }
    
    {
        static Meta meta = { type<glTFType>(), &namspc({}), "glTFType", sizeof(glTFType), TypeClass::Enum };
        static Enum enu = { type<glTFType>(),
            true,
            { "SCALAR", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4" },
            { 0, 1, 2, 3, 4, 5, 6 },
            { var(glTFType::SCALAR), var(glTFType::VEC2), var(glTFType::VEC3), var(glTFType::VEC4), var(glTFType::MAT2), var(glTFType::MAT3), var(glTFType::MAT4) }
        };
        meta_enum<glTFType>();
    }
    
    
    // Sequences
    {
        static Meta meta = { type<std::vector<glTFAccessor>>(), &namspc({}), "std::vector<glTFAccessor>", sizeof(std::vector<glTFAccessor>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFAccessor>>() };
        cls.m_content = &type<glTFAccessor>();
        meta_sequence<std::vector<glTFAccessor>, glTFAccessor>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFAnimation>>(), &namspc({}), "std::vector<glTFAnimation>", sizeof(std::vector<glTFAnimation>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFAnimation>>() };
        cls.m_content = &type<glTFAnimation>();
        meta_sequence<std::vector<glTFAnimation>, glTFAnimation>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFAnimationChannel>>(), &namspc({}), "std::vector<glTFAnimationChannel>", sizeof(std::vector<glTFAnimationChannel>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFAnimationChannel>>() };
        cls.m_content = &type<glTFAnimationChannel>();
        meta_sequence<std::vector<glTFAnimationChannel>, glTFAnimationChannel>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFAnimationSampler>>(), &namspc({}), "std::vector<glTFAnimationSampler>", sizeof(std::vector<glTFAnimationSampler>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFAnimationSampler>>() };
        cls.m_content = &type<glTFAnimationSampler>();
        meta_sequence<std::vector<glTFAnimationSampler>, glTFAnimationSampler>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFBuffer>>(), &namspc({}), "std::vector<glTFBuffer>", sizeof(std::vector<glTFBuffer>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFBuffer>>() };
        cls.m_content = &type<glTFBuffer>();
        meta_sequence<std::vector<glTFBuffer>, glTFBuffer>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFBufferView>>(), &namspc({}), "std::vector<glTFBufferView>", sizeof(std::vector<glTFBufferView>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFBufferView>>() };
        cls.m_content = &type<glTFBufferView>();
        meta_sequence<std::vector<glTFBufferView>, glTFBufferView>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFCamera>>(), &namspc({}), "std::vector<glTFCamera>", sizeof(std::vector<glTFCamera>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFCamera>>() };
        cls.m_content = &type<glTFCamera>();
        meta_sequence<std::vector<glTFCamera>, glTFCamera>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFImage>>(), &namspc({}), "std::vector<glTFImage>", sizeof(std::vector<glTFImage>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFImage>>() };
        cls.m_content = &type<glTFImage>();
        meta_sequence<std::vector<glTFImage>, glTFImage>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFMaterial>>(), &namspc({}), "std::vector<glTFMaterial>", sizeof(std::vector<glTFMaterial>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFMaterial>>() };
        cls.m_content = &type<glTFMaterial>();
        meta_sequence<std::vector<glTFMaterial>, glTFMaterial>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFMesh>>(), &namspc({}), "std::vector<glTFMesh>", sizeof(std::vector<glTFMesh>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFMesh>>() };
        cls.m_content = &type<glTFMesh>();
        meta_sequence<std::vector<glTFMesh>, glTFMesh>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFMorphTarget>>(), &namspc({}), "std::vector<glTFMorphTarget>", sizeof(std::vector<glTFMorphTarget>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFMorphTarget>>() };
        cls.m_content = &type<glTFMorphTarget>();
        meta_sequence<std::vector<glTFMorphTarget>, glTFMorphTarget>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFNode>>(), &namspc({}), "std::vector<glTFNode>", sizeof(std::vector<glTFNode>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFNode>>() };
        cls.m_content = &type<glTFNode>();
        meta_sequence<std::vector<glTFNode>, glTFNode>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFPrimitive>>(), &namspc({}), "std::vector<glTFPrimitive>", sizeof(std::vector<glTFPrimitive>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFPrimitive>>() };
        cls.m_content = &type<glTFPrimitive>();
        meta_sequence<std::vector<glTFPrimitive>, glTFPrimitive>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFScene>>(), &namspc({}), "std::vector<glTFScene>", sizeof(std::vector<glTFScene>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFScene>>() };
        cls.m_content = &type<glTFScene>();
        meta_sequence<std::vector<glTFScene>, glTFScene>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFSkin>>(), &namspc({}), "std::vector<glTFSkin>", sizeof(std::vector<glTFSkin>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFSkin>>() };
        cls.m_content = &type<glTFSkin>();
        meta_sequence<std::vector<glTFSkin>, glTFSkin>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFTexture>>(), &namspc({}), "std::vector<glTFTexture>", sizeof(std::vector<glTFTexture>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFTexture>>() };
        cls.m_content = &type<glTFTexture>();
        meta_sequence<std::vector<glTFTexture>, glTFTexture>();
    }
    
    {
        static Meta meta = { type<std::vector<int>>(), &namspc({}), "std::vector<int>", sizeof(std::vector<int>), TypeClass::Sequence };
        static Class cls = { type<std::vector<int>>() };
        cls.m_content = &type<int>();
        meta_sequence<std::vector<int>, int>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::PrefabNode>>(), &namspc({}), "std::vector<mud::PrefabNode>", sizeof(std::vector<mud::PrefabNode>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::PrefabNode>>() };
        cls.m_content = &type<mud::PrefabNode>();
        meta_sequence<std::vector<mud::PrefabNode>, mud::PrefabNode>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::quat>>(), &namspc({}), "std::vector<mud::quat>", sizeof(std::vector<mud::quat>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::quat>>() };
        cls.m_content = &type<mud::quat>();
        meta_sequence<std::vector<mud::quat>, mud::quat>();
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
    
    
        
    // mud::BCS
    {
        static Meta meta = { type<mud::BCS>(), &namspc({ "mud" }), "BCS", sizeof(mud::BCS), TypeClass::Struct };
        static Class cls = { type<mud::BCS>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::BCS>(), [](Ref ref, Ref other) { new(&val<mud::BCS>(ref)) mud::BCS(val<mud::BCS>(other)); } }
            },
            // members
            {
                { type<mud::BCS>(), member_address(&mud::BCS::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BCS>(), member_address(&mud::BCS::m_brightness), type<float>(), "brightness", var(float(1.0f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BCS>(), member_address(&mud::BCS::m_contrast), type<float>(), "contrast", var(float(1.0f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::BCS>(), member_address(&mud::BCS::m_saturation), type<float>(), "saturation", var(float(1.0f)), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::BCS>();
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
    
    
    
    
        
    // mud::DofBlur
    {
        static Meta meta = { type<mud::DofBlur>(), &namspc({ "mud" }), "DofBlur", sizeof(mud::DofBlur), TypeClass::Struct };
        static Class cls = { type<mud::DofBlur>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::DofBlur>(), [](Ref ref, Ref other) { new(&val<mud::DofBlur>(ref)) mud::DofBlur(val<mud::DofBlur>(other)); } }
            },
            // members
            {
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_far_distance), type<float>(), "far_distance", var(float(10.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_far_transition), type<float>(), "far_transition", var(float(5.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_far_radius), type<float>(), "far_radius", var(float(5.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_near_distance), type<float>(), "near_distance", var(float(2.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_near_transition), type<float>(), "near_transition", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_near_radius), type<float>(), "near_radius", var(float(5.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_max_coc_radius), type<float>(), "max_coc_radius", var(float(8.f)), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::DofBlur>();
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
    
    
        
    // mud::Glow
    {
        static Meta meta = { type<mud::Glow>(), &namspc({ "mud" }), "Glow", sizeof(mud::Glow), TypeClass::Struct };
        static Class cls = { type<mud::Glow>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Glow>(), [](Ref ref, Ref other) { new(&val<mud::Glow>(ref)) mud::Glow(val<mud::Glow>(other)); } }
            },
            // members
            {
                { type<mud::Glow>(), member_address(&mud::Glow::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Glow>(), member_address(&mud::Glow::m_levels_1_4), type<mud::vec4>(), "levels_1_4", var(mud::vec4()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Glow>(), member_address(&mud::Glow::m_levels_5_8), type<mud::vec4>(), "levels_5_8", var(mud::vec4()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Glow>(), member_address(&mud::Glow::m_intensity), type<float>(), "intensity", var(float(0.8f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Glow>(), member_address(&mud::Glow::m_bloom), type<float>(), "bloom", var(float(0.0f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Glow>(), member_address(&mud::Glow::m_bleed_threshold), type<float>(), "bleed_threshold", var(float(1.0f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Glow>(), member_address(&mud::Glow::m_bleed_scale), type<float>(), "bleed_scale", var(float(2.0f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Glow>(), member_address(&mud::Glow::m_bicubic_filter), type<bool>(), "bicubic_filter", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Glow>();
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
    
    
    
        
    // mud::LightShadow
    {
        static Meta meta = { type<mud::LightShadow>(), &namspc({ "mud" }), "LightShadow", sizeof(mud::LightShadow), TypeClass::Struct };
        static Class cls = { type<mud::LightShadow>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::LightShadow>(), [](Ref ref, Ref other) { new(&val<mud::LightShadow>(ref)) mud::LightShadow(val<mud::LightShadow>(other)); } }
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
        
        
        
        
        meta_class<mud::LightShadow>();
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
                { type<mud::Model>(), member_address(&mud::Model::m_radius), type<float>(), "radius", var(float(0.f)), Member::Value }
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
    
    
    
    
    
        
    // mud::ReflectionProbe
    {
        static Meta meta = { type<mud::ReflectionProbe>(), &namspc({ "mud" }), "ReflectionProbe", sizeof(mud::ReflectionProbe), TypeClass::Object };
        static Class cls = { type<mud::ReflectionProbe>(),
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
                { type<mud::ReflectionProbe>(), Address(), type<mud::Node3>(), "node", Ref(type<mud::Node3>()), Member::None },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_visible), type<bool>(), "visible", var(bool(true)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_intensity), type<float>(), "intensity", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_extents), type<mud::vec3>(), "extents", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_shadows), type<bool>(), "shadows", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_dirty), type<bool>(), "dirty", var(bool(true)), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ReflectionProbe>();
    }
    
    
    
    
    
        
    // mud::RenderFilters
    {
        static Meta meta = { type<mud::RenderFilters>(), &namspc({ "mud" }), "RenderFilters", sizeof(mud::RenderFilters), TypeClass::Struct };
        static Class cls = { type<mud::RenderFilters>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::RenderFilters>(), [](Ref ref, Ref other) { new(&val<mud::RenderFilters>(ref)) mud::RenderFilters(val<mud::RenderFilters>(other)); } }
            },
            // members
            {
                { type<mud::RenderFilters>(), member_address(&mud::RenderFilters::m_dof_blur), type<mud::DofBlur>(), "dof_blur", var(mud::DofBlur()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::RenderFilters>(), member_address(&mud::RenderFilters::m_glow), type<mud::Glow>(), "glow", var(mud::Glow()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::RenderFilters>(), member_address(&mud::RenderFilters::m_bcs), type<mud::BCS>(), "bcs", var(mud::BCS()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::RenderFilters>(), member_address(&mud::RenderFilters::m_tonemap), type<mud::Tonemap>(), "tonemap", var(mud::Tonemap()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::RenderFilters>();
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
    
    
    
    
    
    
    
    
        
    // mud::SpaceQuad
    {
        static Meta meta = { type<mud::SpaceQuad>(), &namspc({ "mud" }), "SpaceQuad", sizeof(mud::SpaceQuad), TypeClass::Object };
        static Class cls = { type<mud::SpaceQuad>(),
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
        
        
        
        
        meta_class<mud::SpaceQuad>();
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
    
    
    
    
    
        
    // mud::Tonemap
    {
        static Meta meta = { type<mud::Tonemap>(), &namspc({ "mud" }), "Tonemap", sizeof(mud::Tonemap), TypeClass::Struct };
        static Class cls = { type<mud::Tonemap>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Tonemap>(), [](Ref ref, Ref other) { new(&val<mud::Tonemap>(ref)) mud::Tonemap(val<mud::Tonemap>(other)); } }
            },
            // members
            {
                { type<mud::Tonemap>(), member_address(&mud::Tonemap::m_mode), type<mud::TonemapMode>(), "mode", var(mud::TonemapMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Tonemap>(), member_address(&mud::Tonemap::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Tonemap>(), member_address(&mud::Tonemap::m_exposure), type<float>(), "exposure", var(float(1.0f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Tonemap>(), member_address(&mud::Tonemap::m_white_point), type<float>(), "white_point", var(float(1.0f)), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Tonemap>();
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
    
    
    
        
    // mud::ValueCurve<float>
    {
        static Meta meta = { type<mud::ValueCurve<float>>(), &namspc({ "mud" }), "ValueCurve<float>", sizeof(mud::ValueCurve<float>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<float>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<float>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<float>>(ref)) mud::ValueCurve<float>(  ); }, {} },
                { type<mud::ValueCurve<float>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<float>>(ref)) mud::ValueCurve<float>( val<std::vector<float>>(args[0]) ); }, { { "keys", var(std::vector<float>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<float>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<float>>(ref)) mud::ValueCurve<float>(val<mud::ValueCurve<float>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<float>>(), member_address(&mud::ValueCurve<float>::m_keys), type<std::vector<float>>(), "keys", var(std::vector<float>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueCurve<float>>();
    }
    
    
        
    // mud::ValueCurve<mud::Colour>
    {
        static Meta meta = { type<mud::ValueCurve<mud::Colour>>(), &namspc({ "mud" }), "ValueCurve<mud::Colour>", sizeof(mud::ValueCurve<mud::Colour>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<mud::Colour>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<mud::Colour>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<mud::Colour>>(ref)) mud::ValueCurve<mud::Colour>(  ); }, {} },
                { type<mud::ValueCurve<mud::Colour>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<mud::Colour>>(ref)) mud::ValueCurve<mud::Colour>( val<std::vector<mud::Colour>>(args[0]) ); }, { { "keys", var(std::vector<mud::Colour>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<mud::Colour>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<mud::Colour>>(ref)) mud::ValueCurve<mud::Colour>(val<mud::ValueCurve<mud::Colour>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<mud::Colour>>(), member_address(&mud::ValueCurve<mud::Colour>::m_keys), type<std::vector<mud::Colour>>(), "keys", var(std::vector<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueCurve<mud::Colour>>();
    }
    
    
        
    // mud::ValueCurve<mud::quat>
    {
        static Meta meta = { type<mud::ValueCurve<mud::quat>>(), &namspc({ "mud" }), "ValueCurve<mud::quat>", sizeof(mud::ValueCurve<mud::quat>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<mud::quat>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<mud::quat>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<mud::quat>>(ref)) mud::ValueCurve<mud::quat>(  ); }, {} },
                { type<mud::ValueCurve<mud::quat>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<mud::quat>>(ref)) mud::ValueCurve<mud::quat>( val<std::vector<mud::quat>>(args[0]) ); }, { { "keys", var(std::vector<mud::quat>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<mud::quat>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<mud::quat>>(ref)) mud::ValueCurve<mud::quat>(val<mud::ValueCurve<mud::quat>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<mud::quat>>(), member_address(&mud::ValueCurve<mud::quat>::m_keys), type<std::vector<mud::quat>>(), "keys", var(std::vector<mud::quat>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueCurve<mud::quat>>();
    }
    
    
        
    // mud::ValueCurve<mud::vec3>
    {
        static Meta meta = { type<mud::ValueCurve<mud::vec3>>(), &namspc({ "mud" }), "ValueCurve<mud::vec3>", sizeof(mud::ValueCurve<mud::vec3>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<mud::vec3>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<mud::vec3>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<mud::vec3>>(ref)) mud::ValueCurve<mud::vec3>(  ); }, {} },
                { type<mud::ValueCurve<mud::vec3>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<mud::vec3>>(ref)) mud::ValueCurve<mud::vec3>( val<std::vector<mud::vec3>>(args[0]) ); }, { { "keys", var(std::vector<mud::vec3>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<mud::vec3>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<mud::vec3>>(ref)) mud::ValueCurve<mud::vec3>(val<mud::ValueCurve<mud::vec3>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<mud::vec3>>(), member_address(&mud::ValueCurve<mud::vec3>::m_keys), type<std::vector<mud::vec3>>(), "keys", var(std::vector<mud::vec3>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueCurve<mud::vec3>>();
    }
    
    
        
    // mud::ValueCurve<uint32_t>
    {
        static Meta meta = { type<mud::ValueCurve<uint32_t>>(), &namspc({ "mud" }), "ValueCurve<uint32_t>", sizeof(mud::ValueCurve<uint32_t>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<uint32_t>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<uint32_t>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<uint32_t>>(ref)) mud::ValueCurve<uint32_t>(  ); }, {} },
                { type<mud::ValueCurve<uint32_t>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<uint32_t>>(ref)) mud::ValueCurve<uint32_t>( val<std::vector<uint32_t>>(args[0]) ); }, { { "keys", var(std::vector<uint32_t>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<uint32_t>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<uint32_t>>(ref)) mud::ValueCurve<uint32_t>(val<mud::ValueCurve<uint32_t>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<uint32_t>>(), member_address(&mud::ValueCurve<uint32_t>::m_keys), type<std::vector<uint32_t>>(), "keys", var(std::vector<uint32_t>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueCurve<uint32_t>>();
    }
    
    
        
    // mud::ValueTrack<float>
    {
        static Meta meta = { type<mud::ValueTrack<float>>(), &namspc({ "mud" }), "ValueTrack<float>", sizeof(mud::ValueTrack<float>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<float>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<float>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<float>>(ref)) mud::ValueTrack<float>(  ); }, {} },
                { type<mud::ValueTrack<float>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<float>>(ref)) mud::ValueTrack<float>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<float>>(args[1]), val<mud::ValueCurve<float>>(args[2]), val<mud::ValueCurve<float>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<float>()) }, { "min_curve", var(mud::ValueCurve<float>()) }, { "max_curve", var(mud::ValueCurve<float>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<float>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<float>>(ref)) mud::ValueTrack<float>(val<mud::ValueTrack<float>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<float>>(), member_address(&mud::ValueTrack<float>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<float>>(), member_address(&mud::ValueTrack<float>::m_curve), type<mud::ValueCurve<float>>(), "curve", var(mud::ValueCurve<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<float>>(), member_address(&mud::ValueTrack<float>::m_min_curve), type<mud::ValueCurve<float>>(), "min_curve", var(mud::ValueCurve<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<float>>(), member_address(&mud::ValueTrack<float>::m_max_curve), type<mud::ValueCurve<float>>(), "max_curve", var(mud::ValueCurve<float>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueTrack<float>>();
    }
    
    
        
    // mud::ValueTrack<mud::Colour>
    {
        static Meta meta = { type<mud::ValueTrack<mud::Colour>>(), &namspc({ "mud" }), "ValueTrack<mud::Colour>", sizeof(mud::ValueTrack<mud::Colour>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<mud::Colour>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<mud::Colour>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<mud::Colour>>(ref)) mud::ValueTrack<mud::Colour>(  ); }, {} },
                { type<mud::ValueTrack<mud::Colour>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<mud::Colour>>(ref)) mud::ValueTrack<mud::Colour>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<mud::Colour>>(args[1]), val<mud::ValueCurve<mud::Colour>>(args[2]), val<mud::ValueCurve<mud::Colour>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<mud::Colour>()) }, { "min_curve", var(mud::ValueCurve<mud::Colour>()) }, { "max_curve", var(mud::ValueCurve<mud::Colour>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<mud::Colour>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<mud::Colour>>(ref)) mud::ValueTrack<mud::Colour>(val<mud::ValueTrack<mud::Colour>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<mud::Colour>>(), member_address(&mud::ValueTrack<mud::Colour>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::Colour>>(), member_address(&mud::ValueTrack<mud::Colour>::m_curve), type<mud::ValueCurve<mud::Colour>>(), "curve", var(mud::ValueCurve<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::Colour>>(), member_address(&mud::ValueTrack<mud::Colour>::m_min_curve), type<mud::ValueCurve<mud::Colour>>(), "min_curve", var(mud::ValueCurve<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::Colour>>(), member_address(&mud::ValueTrack<mud::Colour>::m_max_curve), type<mud::ValueCurve<mud::Colour>>(), "max_curve", var(mud::ValueCurve<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueTrack<mud::Colour>>();
    }
    
    
        
    // mud::ValueTrack<mud::quat>
    {
        static Meta meta = { type<mud::ValueTrack<mud::quat>>(), &namspc({ "mud" }), "ValueTrack<mud::quat>", sizeof(mud::ValueTrack<mud::quat>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<mud::quat>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<mud::quat>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<mud::quat>>(ref)) mud::ValueTrack<mud::quat>(  ); }, {} },
                { type<mud::ValueTrack<mud::quat>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<mud::quat>>(ref)) mud::ValueTrack<mud::quat>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<mud::quat>>(args[1]), val<mud::ValueCurve<mud::quat>>(args[2]), val<mud::ValueCurve<mud::quat>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<mud::quat>()) }, { "min_curve", var(mud::ValueCurve<mud::quat>()) }, { "max_curve", var(mud::ValueCurve<mud::quat>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<mud::quat>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<mud::quat>>(ref)) mud::ValueTrack<mud::quat>(val<mud::ValueTrack<mud::quat>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<mud::quat>>(), member_address(&mud::ValueTrack<mud::quat>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::quat>>(), member_address(&mud::ValueTrack<mud::quat>::m_curve), type<mud::ValueCurve<mud::quat>>(), "curve", var(mud::ValueCurve<mud::quat>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::quat>>(), member_address(&mud::ValueTrack<mud::quat>::m_min_curve), type<mud::ValueCurve<mud::quat>>(), "min_curve", var(mud::ValueCurve<mud::quat>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::quat>>(), member_address(&mud::ValueTrack<mud::quat>::m_max_curve), type<mud::ValueCurve<mud::quat>>(), "max_curve", var(mud::ValueCurve<mud::quat>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueTrack<mud::quat>>();
    }
    
    
        
    // mud::ValueTrack<mud::vec3>
    {
        static Meta meta = { type<mud::ValueTrack<mud::vec3>>(), &namspc({ "mud" }), "ValueTrack<mud::vec3>", sizeof(mud::ValueTrack<mud::vec3>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<mud::vec3>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<mud::vec3>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<mud::vec3>>(ref)) mud::ValueTrack<mud::vec3>(  ); }, {} },
                { type<mud::ValueTrack<mud::vec3>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<mud::vec3>>(ref)) mud::ValueTrack<mud::vec3>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<mud::vec3>>(args[1]), val<mud::ValueCurve<mud::vec3>>(args[2]), val<mud::ValueCurve<mud::vec3>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<mud::vec3>()) }, { "min_curve", var(mud::ValueCurve<mud::vec3>()) }, { "max_curve", var(mud::ValueCurve<mud::vec3>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<mud::vec3>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<mud::vec3>>(ref)) mud::ValueTrack<mud::vec3>(val<mud::ValueTrack<mud::vec3>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<mud::vec3>>(), member_address(&mud::ValueTrack<mud::vec3>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::vec3>>(), member_address(&mud::ValueTrack<mud::vec3>::m_curve), type<mud::ValueCurve<mud::vec3>>(), "curve", var(mud::ValueCurve<mud::vec3>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::vec3>>(), member_address(&mud::ValueTrack<mud::vec3>::m_min_curve), type<mud::ValueCurve<mud::vec3>>(), "min_curve", var(mud::ValueCurve<mud::vec3>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::vec3>>(), member_address(&mud::ValueTrack<mud::vec3>::m_max_curve), type<mud::ValueCurve<mud::vec3>>(), "max_curve", var(mud::ValueCurve<mud::vec3>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueTrack<mud::vec3>>();
    }
    
    
        
    // mud::ValueTrack<uint32_t>
    {
        static Meta meta = { type<mud::ValueTrack<uint32_t>>(), &namspc({ "mud" }), "ValueTrack<uint32_t>", sizeof(mud::ValueTrack<uint32_t>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<uint32_t>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<uint32_t>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<uint32_t>>(ref)) mud::ValueTrack<uint32_t>(  ); }, {} },
                { type<mud::ValueTrack<uint32_t>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<uint32_t>>(ref)) mud::ValueTrack<uint32_t>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<uint32_t>>(args[1]), val<mud::ValueCurve<uint32_t>>(args[2]), val<mud::ValueCurve<uint32_t>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<uint32_t>()) }, { "min_curve", var(mud::ValueCurve<uint32_t>()) }, { "max_curve", var(mud::ValueCurve<uint32_t>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<uint32_t>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<uint32_t>>(ref)) mud::ValueTrack<uint32_t>(val<mud::ValueTrack<uint32_t>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<uint32_t>>(), member_address(&mud::ValueTrack<uint32_t>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<uint32_t>>(), member_address(&mud::ValueTrack<uint32_t>::m_curve), type<mud::ValueCurve<uint32_t>>(), "curve", var(mud::ValueCurve<uint32_t>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<uint32_t>>(), member_address(&mud::ValueTrack<uint32_t>::m_min_curve), type<mud::ValueCurve<uint32_t>>(), "min_curve", var(mud::ValueCurve<uint32_t>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<uint32_t>>(), member_address(&mud::ValueTrack<uint32_t>::m_max_curve), type<mud::ValueCurve<uint32_t>>(), "max_curve", var(mud::ValueCurve<uint32_t>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ValueTrack<uint32_t>>();
    }
    
    
    
    
    
    
        
    // mud::ViewerController
    {
        static Meta meta = { type<mud::ViewerController>(), &namspc({ "mud" }), "ViewerController", sizeof(mud::ViewerController), TypeClass::Object };
        static Class cls = { type<mud::ViewerController>(),
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
        
        
        
        
        meta_class<mud::ViewerController>();
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
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_shading), type<mud::Shading>(), "shading", var(mud::Shading()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Viewport>(), member_address(&mud::Viewport::m_filters), type<mud::RenderFilters>(), "filters", Ref(type<mud::RenderFilters>()), Member::Flags(Member::Pointer|Member::Mutable|Member::Link) }
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
    
    
        
    // glTF
    {
        static Meta meta = { type<glTF>(), &namspc({}), "glTF", sizeof(glTF), TypeClass::Struct };
        static Class cls = { type<glTF>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTF>(), [](Ref ref, Ref other) { new(&val<glTF>(ref)) glTF(val<glTF>(other)); } }
            },
            // members
            {
                { type<glTF>(), member_address(&glTF::m_buffers), type<std::vector<glTFBuffer>>(), "buffers", var(std::vector<glTFBuffer>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_buffer_views), type<std::vector<glTFBufferView>>(), "buffer_views", var(std::vector<glTFBufferView>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_accessors), type<std::vector<glTFAccessor>>(), "accessors", var(std::vector<glTFAccessor>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_images), type<std::vector<glTFImage>>(), "images", var(std::vector<glTFImage>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_textures), type<std::vector<glTFTexture>>(), "textures", var(std::vector<glTFTexture>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_materials), type<std::vector<glTFMaterial>>(), "materials", var(std::vector<glTFMaterial>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_meshes), type<std::vector<glTFMesh>>(), "meshes", var(std::vector<glTFMesh>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_nodes), type<std::vector<glTFNode>>(), "nodes", var(std::vector<glTFNode>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_skins), type<std::vector<glTFSkin>>(), "skins", var(std::vector<glTFSkin>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_animations), type<std::vector<glTFAnimation>>(), "animations", var(std::vector<glTFAnimation>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_cameras), type<std::vector<glTFCamera>>(), "cameras", var(std::vector<glTFCamera>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_scenes), type<std::vector<glTFScene>>(), "scenes", var(std::vector<glTFScene>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTF>();
    }
    
    
        
    // glTFAccessor
    {
        static Meta meta = { type<glTFAccessor>(), &namspc({}), "glTFAccessor", sizeof(glTFAccessor), TypeClass::Struct };
        static Class cls = { type<glTFAccessor>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFAccessor>(), [](Ref ref, Ref other) { new(&val<glTFAccessor>(ref)) glTFAccessor(val<glTFAccessor>(other)); } }
            },
            // members
            {
                { type<glTFAccessor>(), member_address(&glTFAccessor::buffer_view), type<int>(), "buffer_view", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::component_type), type<glTFComponentType>(), "component_type", var(glTFComponentType()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::normalized), type<bool>(), "normalized", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::count), type<int>(), "count", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::type), type<glTFType>(), "type", var(glTFType()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::sparse), type<glTFSparse>(), "sparse", var(glTFSparse()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFAccessor>();
    }
    
    
        
    // glTFAnimation
    {
        static Meta meta = { type<glTFAnimation>(), &namspc({}), "glTFAnimation", sizeof(glTFAnimation), TypeClass::Struct };
        static Class cls = { type<glTFAnimation>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFAnimation>(), [](Ref ref, Ref other) { new(&val<glTFAnimation>(ref)) glTFAnimation(val<glTFAnimation>(other)); } }
            },
            // members
            {
                { type<glTFAnimation>(), member_address(&glTFAnimation::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimation>(), member_address(&glTFAnimation::samplers), type<std::vector<glTFAnimationSampler>>(), "samplers", var(std::vector<glTFAnimationSampler>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimation>(), member_address(&glTFAnimation::channels), type<std::vector<glTFAnimationChannel>>(), "channels", var(std::vector<glTFAnimationChannel>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFAnimation>();
    }
    
    
        
    // glTFAnimationChannel
    {
        static Meta meta = { type<glTFAnimationChannel>(), &namspc({}), "glTFAnimationChannel", sizeof(glTFAnimationChannel), TypeClass::Struct };
        static Class cls = { type<glTFAnimationChannel>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFAnimationChannel>(), [](Ref ref, Ref other) { new(&val<glTFAnimationChannel>(ref)) glTFAnimationChannel(val<glTFAnimationChannel>(other)); } }
            },
            // members
            {
                { type<glTFAnimationChannel>(), member_address(&glTFAnimationChannel::sampler), type<int>(), "sampler", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimationChannel>(), member_address(&glTFAnimationChannel::target), type<glTFAnimationTarget>(), "target", var(glTFAnimationTarget()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFAnimationChannel>();
    }
    
    
        
    // glTFAnimationSampler
    {
        static Meta meta = { type<glTFAnimationSampler>(), &namspc({}), "glTFAnimationSampler", sizeof(glTFAnimationSampler), TypeClass::Struct };
        static Class cls = { type<glTFAnimationSampler>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFAnimationSampler>(), [](Ref ref, Ref other) { new(&val<glTFAnimationSampler>(ref)) glTFAnimationSampler(val<glTFAnimationSampler>(other)); } }
            },
            // members
            {
                { type<glTFAnimationSampler>(), member_address(&glTFAnimationSampler::interpolation), type<glTFInterpolation>(), "interpolation", var(glTFInterpolation()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimationSampler>(), member_address(&glTFAnimationSampler::input), type<int>(), "input", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimationSampler>(), member_address(&glTFAnimationSampler::output), type<int>(), "output", var(int()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFAnimationSampler>();
    }
    
    
        
    // glTFAnimationTarget
    {
        static Meta meta = { type<glTFAnimationTarget>(), &namspc({}), "glTFAnimationTarget", sizeof(glTFAnimationTarget), TypeClass::Struct };
        static Class cls = { type<glTFAnimationTarget>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFAnimationTarget>(), [](Ref ref, Ref other) { new(&val<glTFAnimationTarget>(ref)) glTFAnimationTarget(val<glTFAnimationTarget>(other)); } }
            },
            // members
            {
                { type<glTFAnimationTarget>(), member_address(&glTFAnimationTarget::node), type<int>(), "node", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimationTarget>(), member_address(&glTFAnimationTarget::path), type<std::string>(), "path", var(std::string()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFAnimationTarget>();
    }
    
    
        
    // glTFAttributes
    {
        static Meta meta = { type<glTFAttributes>(), &namspc({}), "glTFAttributes", sizeof(glTFAttributes), TypeClass::Struct };
        static Class cls = { type<glTFAttributes>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFAttributes>(), [](Ref ref, Ref other) { new(&val<glTFAttributes>(ref)) glTFAttributes(val<glTFAttributes>(other)); } }
            },
            // members
            {
                { type<glTFAttributes>(), member_address(&glTFAttributes::POSITION), type<int>(), "POSITION", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::NORMAL), type<int>(), "NORMAL", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::TANGENT), type<int>(), "TANGENT", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::TEXCOORD_0), type<int>(), "TEXCOORD_0", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::TEXCOORD_1), type<int>(), "TEXCOORD_1", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::COLOR_0), type<int>(), "COLOR_0", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::JOINTS_0), type<int>(), "JOINTS_0", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::WEIGHTS_0), type<int>(), "WEIGHTS_0", var(int()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFAttributes>();
    }
    
    
        
    // glTFBuffer
    {
        static Meta meta = { type<glTFBuffer>(), &namspc({}), "glTFBuffer", sizeof(glTFBuffer), TypeClass::Struct };
        static Class cls = { type<glTFBuffer>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFBuffer>(), [](Ref ref, Ref other) { new(&val<glTFBuffer>(ref)) glTFBuffer(val<glTFBuffer>(other)); } }
            },
            // members
            {
                { type<glTFBuffer>(), member_address(&glTFBuffer::mime_type), type<std::string>(), "mime_type", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBuffer>(), member_address(&glTFBuffer::uri), type<std::string>(), "uri", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBuffer>(), member_address(&glTFBuffer::byte_length), type<int>(), "byte_length", var(int()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFBuffer>();
    }
    
    
        
    // glTFBufferView
    {
        static Meta meta = { type<glTFBufferView>(), &namspc({}), "glTFBufferView", sizeof(glTFBufferView), TypeClass::Struct };
        static Class cls = { type<glTFBufferView>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFBufferView>(), [](Ref ref, Ref other) { new(&val<glTFBufferView>(ref)) glTFBufferView(val<glTFBufferView>(other)); } }
            },
            // members
            {
                { type<glTFBufferView>(), member_address(&glTFBufferView::buffer), type<int>(), "buffer", var(int(0)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBufferView>(), member_address(&glTFBufferView::byte_offset), type<size_t>(), "byte_offset", var(size_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBufferView>(), member_address(&glTFBufferView::byte_length), type<size_t>(), "byte_length", var(size_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBufferView>(), member_address(&glTFBufferView::byte_stride), type<size_t>(), "byte_stride", var(size_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBufferView>(), member_address(&glTFBufferView::target), type<int>(), "target", var(int(0)), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFBufferView>();
    }
    
    
        
    // glTFCamera
    {
        static Meta meta = { type<glTFCamera>(), &namspc({}), "glTFCamera", sizeof(glTFCamera), TypeClass::Struct };
        static Class cls = { type<glTFCamera>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFCamera>(), [](Ref ref, Ref other) { new(&val<glTFCamera>(ref)) glTFCamera(val<glTFCamera>(other)); } }
            },
            // members
            {
                { type<glTFCamera>(), member_address(&glTFCamera::type), type<std::string>(), "type", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFCamera>(), member_address(&glTFCamera::orthographic), type<glTFOrthographic>(), "orthographic", var(glTFOrthographic()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFCamera>(), member_address(&glTFCamera::perspective), type<glTFPerspective>(), "perspective", var(glTFPerspective()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFCamera>();
    }
    
    
        
    // glTFImage
    {
        static Meta meta = { type<glTFImage>(), &namspc({}), "glTFImage", sizeof(glTFImage), TypeClass::Struct };
        static Class cls = { type<glTFImage>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFImage>(), [](Ref ref, Ref other) { new(&val<glTFImage>(ref)) glTFImage(val<glTFImage>(other)); } }
            },
            // members
            {
                { type<glTFImage>(), member_address(&glTFImage::mime_type), type<std::string>(), "mime_type", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFImage>(), member_address(&glTFImage::uri), type<std::string>(), "uri", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFImage>(), member_address(&glTFImage::buffer_view), type<int>(), "buffer_view", var(int()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFImage>();
    }
    
    
        
    // mud::glTFImport
    {
        static Meta meta = { type<mud::glTFImport>(), &namspc({ "mud" }), "glTFImport", sizeof(mud::glTFImport), TypeClass::Object };
        static Class cls = { type<mud::glTFImport>(),
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
                { type<mud::glTFImport>(), member_address(&mud::glTFImport::m_gltf), type<glTF>(), "gltf", var(glTF()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::glTFImport>();
    }
    
    
        
    // glTFMaterial
    {
        static Meta meta = { type<glTFMaterial>(), &namspc({}), "glTFMaterial", sizeof(glTFMaterial), TypeClass::Struct };
        static Class cls = { type<glTFMaterial>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFMaterial>(), [](Ref ref, Ref other) { new(&val<glTFMaterial>(ref)) glTFMaterial(val<glTFMaterial>(other)); } }
            },
            // members
            {
                { type<glTFMaterial>(), member_address(&glTFMaterial::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::normal_texture), type<glTFTextureInfo>(), "normal_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::occlusion_texture), type<glTFTextureInfo>(), "occlusion_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::emissive_factor), type<mud::vec3>(), "emissive_factor", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::emissive_texture), type<glTFTextureInfo>(), "emissive_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::double_sided), type<bool>(), "double_sided", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::alpha_mode), type<glTFAlphaMode>(), "alpha_mode", var(glTFAlphaMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::pbr_metallic_roughness), type<glTFMaterialPBR>(), "pbr_metallic_roughness", var(glTFMaterialPBR()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFMaterial>();
    }
    
    
        
    // glTFMaterialPBR
    {
        static Meta meta = { type<glTFMaterialPBR>(), &namspc({}), "glTFMaterialPBR", sizeof(glTFMaterialPBR), TypeClass::Struct };
        static Class cls = { type<glTFMaterialPBR>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFMaterialPBR>(), [](Ref ref, Ref other) { new(&val<glTFMaterialPBR>(ref)) glTFMaterialPBR(val<glTFMaterialPBR>(other)); } }
            },
            // members
            {
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::base_color_factor), type<mud::vec4>(), "base_color_factor", var(mud::vec4()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::base_color_texture), type<glTFTextureInfo>(), "base_color_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::metallic_factor), type<float>(), "metallic_factor", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::roughness_factor), type<float>(), "roughness_factor", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::metallic_roughness_texture), type<glTFTextureInfo>(), "metallic_roughness_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFMaterialPBR>();
    }
    
    
        
    // glTFMesh
    {
        static Meta meta = { type<glTFMesh>(), &namspc({}), "glTFMesh", sizeof(glTFMesh), TypeClass::Struct };
        static Class cls = { type<glTFMesh>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFMesh>(), [](Ref ref, Ref other) { new(&val<glTFMesh>(ref)) glTFMesh(val<glTFMesh>(other)); } }
            },
            // members
            {
                { type<glTFMesh>(), member_address(&glTFMesh::primitives), type<std::vector<glTFPrimitive>>(), "primitives", var(std::vector<glTFPrimitive>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMesh>(), member_address(&glTFMesh::weights), type<std::vector<float>>(), "weights", var(std::vector<float>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFMesh>();
    }
    
    
        
    // glTFMorphTarget
    {
        static Meta meta = { type<glTFMorphTarget>(), &namspc({}), "glTFMorphTarget", sizeof(glTFMorphTarget), TypeClass::Struct };
        static Class cls = { type<glTFMorphTarget>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFMorphTarget>(), [](Ref ref, Ref other) { new(&val<glTFMorphTarget>(ref)) glTFMorphTarget(val<glTFMorphTarget>(other)); } }
            },
            // members
            {
                { type<glTFMorphTarget>(), member_address(&glTFMorphTarget::POSITION), type<int>(), "POSITION", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMorphTarget>(), member_address(&glTFMorphTarget::NORMAL), type<int>(), "NORMAL", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMorphTarget>(), member_address(&glTFMorphTarget::TANGENT), type<int>(), "TANGENT", var(int()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFMorphTarget>();
    }
    
    
        
    // glTFNode
    {
        static Meta meta = { type<glTFNode>(), &namspc({}), "glTFNode", sizeof(glTFNode), TypeClass::Struct };
        static Class cls = { type<glTFNode>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFNode>(), [](Ref ref, Ref other) { new(&val<glTFNode>(ref)) glTFNode(val<glTFNode>(other)); } }
            },
            // members
            {
                { type<glTFNode>(), member_address(&glTFNode::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::mesh), type<int>(), "mesh", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::camera), type<int>(), "camera", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::skin), type<int>(), "skin", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::matrix), type<mud::mat4>(), "matrix", var(mud::mat4()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::translation), type<mud::vec3>(), "translation", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::rotation), type<mud::quat>(), "rotation", var(mud::quat()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::scale), type<mud::vec3>(), "scale", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::children), type<std::vector<int>>(), "children", var(std::vector<int>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFNode>();
    }
    
    
        
    // glTFOrthographic
    {
        static Meta meta = { type<glTFOrthographic>(), &namspc({}), "glTFOrthographic", sizeof(glTFOrthographic), TypeClass::Struct };
        static Class cls = { type<glTFOrthographic>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFOrthographic>(), [](Ref ref, Ref other) { new(&val<glTFOrthographic>(ref)) glTFOrthographic(val<glTFOrthographic>(other)); } }
            },
            // members
            {
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::xmag), type<float>(), "xmag", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::ymag), type<float>(), "ymag", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::zfar), type<float>(), "zfar", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::znear), type<float>(), "znear", var(float()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFOrthographic>();
    }
    
    
        
    // glTFPerspective
    {
        static Meta meta = { type<glTFPerspective>(), &namspc({}), "glTFPerspective", sizeof(glTFPerspective), TypeClass::Struct };
        static Class cls = { type<glTFPerspective>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFPerspective>(), [](Ref ref, Ref other) { new(&val<glTFPerspective>(ref)) glTFPerspective(val<glTFPerspective>(other)); } }
            },
            // members
            {
                { type<glTFPerspective>(), member_address(&glTFPerspective::yfov), type<float>(), "yfov", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPerspective>(), member_address(&glTFPerspective::zfar), type<float>(), "zfar", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPerspective>(), member_address(&glTFPerspective::znear), type<float>(), "znear", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPerspective>(), member_address(&glTFPerspective::aspect_ration), type<float>(), "aspect_ration", var(float()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFPerspective>();
    }
    
    
        
    // glTFPrimitive
    {
        static Meta meta = { type<glTFPrimitive>(), &namspc({}), "glTFPrimitive", sizeof(glTFPrimitive), TypeClass::Struct };
        static Class cls = { type<glTFPrimitive>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFPrimitive>(), [](Ref ref, Ref other) { new(&val<glTFPrimitive>(ref)) glTFPrimitive(val<glTFPrimitive>(other)); } }
            },
            // members
            {
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::attributes), type<glTFAttributes>(), "attributes", var(glTFAttributes()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::indices), type<int>(), "indices", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::material), type<int>(), "material", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::mode), type<glTFPrimitiveType>(), "mode", var(glTFPrimitiveType()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::targets), type<std::vector<glTFMorphTarget>>(), "targets", var(std::vector<glTFMorphTarget>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFPrimitive>();
    }
    
    
        
    // glTFSampler
    {
        static Meta meta = { type<glTFSampler>(), &namspc({}), "glTFSampler", sizeof(glTFSampler), TypeClass::Struct };
        static Class cls = { type<glTFSampler>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFSampler>(), [](Ref ref, Ref other) { new(&val<glTFSampler>(ref)) glTFSampler(val<glTFSampler>(other)); } }
            },
            // members
            {
                { type<glTFSampler>(), member_address(&glTFSampler::mag_filter), type<int>(), "mag_filter", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSampler>(), member_address(&glTFSampler::min_filter), type<int>(), "min_filter", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSampler>(), member_address(&glTFSampler::wrap_s), type<int>(), "wrap_s", var(int(10497)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSampler>(), member_address(&glTFSampler::wrap_t), type<int>(), "wrap_t", var(int(10497)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSampler>(), member_address(&glTFSampler::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFSampler>();
    }
    
    
        
    // glTFScene
    {
        static Meta meta = { type<glTFScene>(), &namspc({}), "glTFScene", sizeof(glTFScene), TypeClass::Struct };
        static Class cls = { type<glTFScene>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFScene>(), [](Ref ref, Ref other) { new(&val<glTFScene>(ref)) glTFScene(val<glTFScene>(other)); } }
            },
            // members
            {
                { type<glTFScene>(), member_address(&glTFScene::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFScene>(), member_address(&glTFScene::nodes), type<std::vector<int>>(), "nodes", var(std::vector<int>()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFScene>();
    }
    
    
        
    // glTFSkin
    {
        static Meta meta = { type<glTFSkin>(), &namspc({}), "glTFSkin", sizeof(glTFSkin), TypeClass::Struct };
        static Class cls = { type<glTFSkin>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFSkin>(), [](Ref ref, Ref other) { new(&val<glTFSkin>(ref)) glTFSkin(val<glTFSkin>(other)); } }
            },
            // members
            {
                { type<glTFSkin>(), member_address(&glTFSkin::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSkin>(), member_address(&glTFSkin::skeleton), type<int>(), "skeleton", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSkin>(), member_address(&glTFSkin::joints), type<std::vector<int>>(), "joints", var(std::vector<int>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSkin>(), member_address(&glTFSkin::inverse_bind_matrices), type<int>(), "inverse_bind_matrices", var(int()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFSkin>();
    }
    
    
        
    // glTFSparse
    {
        static Meta meta = { type<glTFSparse>(), &namspc({}), "glTFSparse", sizeof(glTFSparse), TypeClass::Struct };
        static Class cls = { type<glTFSparse>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFSparse>(), [](Ref ref, Ref other) { new(&val<glTFSparse>(ref)) glTFSparse(val<glTFSparse>(other)); } }
            },
            // members
            {
                { type<glTFSparse>(), member_address(&glTFSparse::count), type<int>(), "count", var(int(0)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparse>(), member_address(&glTFSparse::indices), type<glTFSparseIndices>(), "indices", var(glTFSparseIndices()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparse>(), member_address(&glTFSparse::values), type<glTFSparseValues>(), "values", var(glTFSparseValues()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFSparse>();
    }
    
    
        
    // glTFSparseIndices
    {
        static Meta meta = { type<glTFSparseIndices>(), &namspc({}), "glTFSparseIndices", sizeof(glTFSparseIndices), TypeClass::Struct };
        static Class cls = { type<glTFSparseIndices>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFSparseIndices>(), [](Ref ref, Ref other) { new(&val<glTFSparseIndices>(ref)) glTFSparseIndices(val<glTFSparseIndices>(other)); } }
            },
            // members
            {
                { type<glTFSparseIndices>(), member_address(&glTFSparseIndices::buffer_view), type<int>(), "buffer_view", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparseIndices>(), member_address(&glTFSparseIndices::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparseIndices>(), member_address(&glTFSparseIndices::component_type), type<glTFComponentType>(), "component_type", var(glTFComponentType()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFSparseIndices>();
    }
    
    
        
    // glTFSparseValues
    {
        static Meta meta = { type<glTFSparseValues>(), &namspc({}), "glTFSparseValues", sizeof(glTFSparseValues), TypeClass::Struct };
        static Class cls = { type<glTFSparseValues>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFSparseValues>(), [](Ref ref, Ref other) { new(&val<glTFSparseValues>(ref)) glTFSparseValues(val<glTFSparseValues>(other)); } }
            },
            // members
            {
                { type<glTFSparseValues>(), member_address(&glTFSparseValues::buffer_view), type<int>(), "buffer_view", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparseValues>(), member_address(&glTFSparseValues::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFSparseValues>();
    }
    
    
        
    // glTFTexture
    {
        static Meta meta = { type<glTFTexture>(), &namspc({}), "glTFTexture", sizeof(glTFTexture), TypeClass::Struct };
        static Class cls = { type<glTFTexture>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFTexture>(), [](Ref ref, Ref other) { new(&val<glTFTexture>(ref)) glTFTexture(val<glTFTexture>(other)); } }
            },
            // members
            {
                { type<glTFTexture>(), member_address(&glTFTexture::source), type<int>(), "source", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFTexture>(), member_address(&glTFTexture::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFTexture>();
    }
    
    
        
    // glTFTextureInfo
    {
        static Meta meta = { type<glTFTextureInfo>(), &namspc({}), "glTFTextureInfo", sizeof(glTFTextureInfo), TypeClass::Struct };
        static Class cls = { type<glTFTextureInfo>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFTextureInfo>(), [](Ref ref, Ref other) { new(&val<glTFTextureInfo>(ref)) glTFTextureInfo(val<glTFTextureInfo>(other)); } }
            },
            // members
            {
                { type<glTFTextureInfo>(), member_address(&glTFTextureInfo::index), type<int>(), "index", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFTextureInfo>(), member_address(&glTFTextureInfo::scale), type<float>(), "scale", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<glTFTextureInfo>();
    }
    
    
        
    // mud::SpaceSheet
    {
        static Meta meta = { type<mud::SpaceSheet>(), &namspc({ "mud" }), "SpaceSheet", sizeof(mud::SpaceSheet), TypeClass::Object };
        static Class cls = { type<mud::SpaceSheet>(),
            // bases
            { &type<mud::RootSheet>() },
            { base_offset<mud::SpaceSheet, mud::RootSheet>() },
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
        
        
        
        
        meta_class<mud::SpaceSheet>();
    }
    
    
        
    // mud::Viewer
    {
        static Meta meta = { type<mud::Viewer>(), &namspc({ "mud" }), "Viewer", sizeof(mud::Viewer), TypeClass::Object };
        static Class cls = { type<mud::Viewer>(),
            // bases
            { &type<mud::Widget>() },
            { base_offset<mud::Viewer, mud::Widget>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_viewport), type<mud::Viewport>(), "viewport", Ref(type<mud::Viewport>()), Member::None },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_position), type<mud::vec2>(), "position", var(mud::vec2()), Member::Value },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_size), type<mud::vec2>(), "size", var(mud::vec2()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Viewer>();
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
    
    
        
    // mud::BlockReflection
    {
        static Meta meta = { type<mud::BlockReflection>(), &namspc({ "mud" }), "BlockReflection", sizeof(mud::BlockReflection), TypeClass::Object };
        static Class cls = { type<mud::BlockReflection>(),
            // bases
            { &type<mud::GfxBlock>() },
            { base_offset<mud::BlockReflection, mud::GfxBlock>() },
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
        
        
        
        
        meta_class<mud::BlockReflection>();
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
    
    
        
    // mud::BlockBlur
    {
        static Meta meta = { type<mud::BlockBlur>(), &namspc({ "mud" }), "BlockBlur", sizeof(mud::BlockBlur), TypeClass::Object };
        static Class cls = { type<mud::BlockBlur>(),
            // bases
            { &type<mud::GfxBlock>() },
            { base_offset<mud::BlockBlur, mud::GfxBlock>() },
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
        
        
        
        
        meta_class<mud::BlockBlur>();
    }
    
    
        
    // mud::BlockDofBlur
    {
        static Meta meta = { type<mud::BlockDofBlur>(), &namspc({ "mud" }), "BlockDofBlur", sizeof(mud::BlockDofBlur), TypeClass::Object };
        static Class cls = { type<mud::BlockDofBlur>(),
            // bases
            { &type<mud::GfxBlock>() },
            { base_offset<mud::BlockDofBlur, mud::GfxBlock>() },
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
        
        
        
        
        meta_class<mud::BlockDofBlur>();
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
    
    
        
    // mud::BlockGlow
    {
        static Meta meta = { type<mud::BlockGlow>(), &namspc({ "mud" }), "BlockGlow", sizeof(mud::BlockGlow), TypeClass::Object };
        static Class cls = { type<mud::BlockGlow>(),
            // bases
            { &type<mud::GfxBlock>() },
            { base_offset<mud::BlockGlow, mud::GfxBlock>() },
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
        
        
        
        
        meta_class<mud::BlockGlow>();
    }
    
    
        
    // mud::BlockTonemap
    {
        static Meta meta = { type<mud::BlockTonemap>(), &namspc({ "mud" }), "BlockTonemap", sizeof(mud::BlockTonemap), TypeClass::Object };
        static Class cls = { type<mud::BlockTonemap>(),
            // bases
            { &type<mud::GfxBlock>() },
            { base_offset<mud::BlockTonemap, mud::GfxBlock>() },
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
        
        
        
        
        meta_class<mud::BlockTonemap>();
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
    
    
        
    // mud::BlockLight
    {
        static Meta meta = { type<mud::BlockLight>(), &namspc({ "mud" }), "BlockLight", sizeof(mud::BlockLight), TypeClass::Object };
        static Class cls = { type<mud::BlockLight>(),
            // bases
            { &type<mud::DrawBlock>() },
            { base_offset<mud::BlockLight, mud::DrawBlock>() },
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
        
        
        
        
        meta_class<mud::BlockLight>();
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
    
    
        
    // mud::BlockRadiance
    {
        static Meta meta = { type<mud::BlockRadiance>(), &namspc({ "mud" }), "BlockRadiance", sizeof(mud::BlockRadiance), TypeClass::Object };
        static Class cls = { type<mud::BlockRadiance>(),
            // bases
            { &type<mud::DrawBlock>() },
            { base_offset<mud::BlockRadiance, mud::DrawBlock>() },
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
        
        
        
        
        meta_class<mud::BlockRadiance>();
    }
    
    
        
    // mud::BlockShadow
    {
        static Meta meta = { type<mud::BlockShadow>(), &namspc({ "mud" }), "BlockShadow", sizeof(mud::BlockShadow), TypeClass::Object };
        static Class cls = { type<mud::BlockShadow>(),
            // bases
            { &type<mud::DrawBlock>() },
            { base_offset<mud::BlockShadow, mud::DrawBlock>() },
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
        
        
        
        
        meta_class<mud::BlockShadow>();
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
    
    
        
    // mud::SceneViewer
    {
        static Meta meta = { type<mud::SceneViewer>(), &namspc({ "mud" }), "SceneViewer", sizeof(mud::SceneViewer), TypeClass::Object };
        static Class cls = { type<mud::SceneViewer>(),
            // bases
            { &type<mud::Scene>(), &type<mud::Viewer>() },
            { base_offset<mud::SceneViewer, mud::Scene>(), base_offset<mud::SceneViewer, mud::Viewer>() },
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
        
        
        
        
        meta_class<mud::SceneViewer>();
    }
    
    
    

    
        module.m_types.push_back(&type<mud::Animated>());
        module.m_types.push_back(&type<mud::AnimatedTrack>());
        module.m_types.push_back(&type<mud::Animation>());
        module.m_types.push_back(&type<mud::AnimationPlay>());
        module.m_types.push_back(&type<mud::AnimationTrack>());
        module.m_types.push_back(&type<mud::BCS>());
        module.m_types.push_back(&type<mud::Background>());
        module.m_types.push_back(&type<mud::BackgroundMode>());
        module.m_types.push_back(&type<mud::BaseMaterialBlock>());
        module.m_types.push_back(&type<mud::BlendMode>());
        module.m_types.push_back(&type<mud::Bone>());
        module.m_types.push_back(&type<mud::Camera>());
        module.m_types.push_back(&type<mud::CullMode>());
        module.m_types.push_back(&type<mud::DepthDraw>());
        module.m_types.push_back(&type<mud::DepthParams>());
        module.m_types.push_back(&type<mud::DepthTest>());
        module.m_types.push_back(&type<mud::DofBlur>());
        module.m_types.push_back(&type<mud::EmitterDirection>());
        module.m_types.push_back(&type<mud::Environment>());
        module.m_types.push_back(&type<mud::Filter>());
        module.m_types.push_back(&type<mud::FrameBuffer>());
        module.m_types.push_back(&type<mud::Frustum>());
        module.m_types.push_back(&type<mud::FrustumSlice>());
        module.m_types.push_back(&type<mud::GfxBlock>());
        module.m_types.push_back(&type<mud::GfxContext>());
        module.m_types.push_back(&type<mud::GfxSystem>());
        module.m_types.push_back(&type<mud::Glow>());
        module.m_types.push_back(&type<mud::Gnode>());
        module.m_types.push_back(&type<mud::ImmediateDraw>());
        module.m_types.push_back(&type<mud::Interpolation>());
        module.m_types.push_back(&type<mud::IsometricAngle>());
        module.m_types.push_back(&type<mud::Item>());
        module.m_types.push_back(&type<mud::ItemFlag>());
        module.m_types.push_back(&type<mud::ItemShadow>());
        module.m_types.push_back(&type<mud::Joint>());
        module.m_types.push_back(&type<mud::Light>());
        module.m_types.push_back(&type<mud::LightShadow>());
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
        module.m_types.push_back(&type<mud::PrefabNode>());
        module.m_types.push_back(&type<mud::PrefabType>());
        module.m_types.push_back(&type<mud::Program>());
        module.m_types.push_back(&type<mud::Radiance>());
        module.m_types.push_back(&type<mud::ReflectionProbe>());
        module.m_types.push_back(&type<mud::RenderFilters>());
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
        module.m_types.push_back(&type<mud::SpaceQuad>());
        module.m_types.push_back(&type<mud::Sun>());
        module.m_types.push_back(&type<mud::SymbolIndex>());
        module.m_types.push_back(&type<mud::Texture>());
        module.m_types.push_back(&type<mud::TextureChannel>());
        module.m_types.push_back(&type<mud::TextureHint>());
        module.m_types.push_back(&type<mud::TextureSampler>());
        module.m_types.push_back(&type<mud::Tonemap>());
        module.m_types.push_back(&type<mud::TonemapMode>());
        module.m_types.push_back(&type<mud::TrackMode>());
        module.m_types.push_back(&type<mud::Transform>());
        module.m_types.push_back(&type<mud::UnshadedMaterialBlock>());
        module.m_types.push_back(&type<mud::ValueCurve<float>>());
        module.m_types.push_back(&type<mud::ValueCurve<mud::Colour>>());
        module.m_types.push_back(&type<mud::ValueCurve<mud::quat>>());
        module.m_types.push_back(&type<mud::ValueCurve<mud::vec3>>());
        module.m_types.push_back(&type<mud::ValueCurve<uint32_t>>());
        module.m_types.push_back(&type<mud::ValueTrack<float>>());
        module.m_types.push_back(&type<mud::ValueTrack<mud::Colour>>());
        module.m_types.push_back(&type<mud::ValueTrack<mud::quat>>());
        module.m_types.push_back(&type<mud::ValueTrack<mud::vec3>>());
        module.m_types.push_back(&type<mud::ValueTrack<uint32_t>>());
        module.m_types.push_back(&type<mud::ViewerController>());
        module.m_types.push_back(&type<mud::Viewport>());
        module.m_types.push_back(&type<glTF>());
        module.m_types.push_back(&type<glTFAccessor>());
        module.m_types.push_back(&type<glTFAlphaMode>());
        module.m_types.push_back(&type<glTFAnimation>());
        module.m_types.push_back(&type<glTFAnimationChannel>());
        module.m_types.push_back(&type<glTFAnimationSampler>());
        module.m_types.push_back(&type<glTFAnimationTarget>());
        module.m_types.push_back(&type<glTFAttributes>());
        module.m_types.push_back(&type<glTFBuffer>());
        module.m_types.push_back(&type<glTFBufferView>());
        module.m_types.push_back(&type<glTFCamera>());
        module.m_types.push_back(&type<glTFComponentType>());
        module.m_types.push_back(&type<glTFImage>());
        module.m_types.push_back(&type<mud::glTFImport>());
        module.m_types.push_back(&type<glTFInterpolation>());
        module.m_types.push_back(&type<glTFMaterial>());
        module.m_types.push_back(&type<glTFMaterialPBR>());
        module.m_types.push_back(&type<glTFMesh>());
        module.m_types.push_back(&type<glTFMorphTarget>());
        module.m_types.push_back(&type<glTFNode>());
        module.m_types.push_back(&type<glTFOrthographic>());
        module.m_types.push_back(&type<glTFPerspective>());
        module.m_types.push_back(&type<glTFPrimitive>());
        module.m_types.push_back(&type<glTFPrimitiveType>());
        module.m_types.push_back(&type<glTFSampler>());
        module.m_types.push_back(&type<glTFScene>());
        module.m_types.push_back(&type<glTFSkin>());
        module.m_types.push_back(&type<glTFSparse>());
        module.m_types.push_back(&type<glTFSparseIndices>());
        module.m_types.push_back(&type<glTFSparseValues>());
        module.m_types.push_back(&type<glTFTexture>());
        module.m_types.push_back(&type<glTFTextureInfo>());
        module.m_types.push_back(&type<glTFType>());
        module.m_types.push_back(&type<std::vector<glTFAccessor>>());
        module.m_types.push_back(&type<std::vector<glTFAnimation>>());
        module.m_types.push_back(&type<std::vector<glTFAnimationChannel>>());
        module.m_types.push_back(&type<std::vector<glTFAnimationSampler>>());
        module.m_types.push_back(&type<std::vector<glTFBuffer>>());
        module.m_types.push_back(&type<std::vector<glTFBufferView>>());
        module.m_types.push_back(&type<std::vector<glTFCamera>>());
        module.m_types.push_back(&type<std::vector<glTFImage>>());
        module.m_types.push_back(&type<std::vector<glTFMaterial>>());
        module.m_types.push_back(&type<std::vector<glTFMesh>>());
        module.m_types.push_back(&type<std::vector<glTFMorphTarget>>());
        module.m_types.push_back(&type<std::vector<glTFNode>>());
        module.m_types.push_back(&type<std::vector<glTFPrimitive>>());
        module.m_types.push_back(&type<std::vector<glTFScene>>());
        module.m_types.push_back(&type<std::vector<glTFSkin>>());
        module.m_types.push_back(&type<std::vector<glTFTexture>>());
        module.m_types.push_back(&type<std::vector<int>>());
        module.m_types.push_back(&type<std::vector<mud::PrefabNode>>());
        module.m_types.push_back(&type<std::vector<mud::quat>>());
        module.m_types.push_back(&type<mud::SpaceSheet>());
        module.m_types.push_back(&type<mud::Viewer>());
        module.m_types.push_back(&type<mud::DrawBlock>());
        module.m_types.push_back(&type<mud::BlockFilter>());
        module.m_types.push_back(&type<mud::BlockCopy>());
        module.m_types.push_back(&type<mud::BlockReflection>());
        module.m_types.push_back(&type<mud::BlockSky>());
        module.m_types.push_back(&type<mud::BlockBlur>());
        module.m_types.push_back(&type<mud::BlockDofBlur>());
        module.m_types.push_back(&type<mud::BlockResolve>());
        module.m_types.push_back(&type<mud::BlockGlow>());
        module.m_types.push_back(&type<mud::BlockTonemap>());
        module.m_types.push_back(&type<mud::BlockDepth>());
        module.m_types.push_back(&type<mud::BlockLight>());
        module.m_types.push_back(&type<mud::BlockParticles>());
        module.m_types.push_back(&type<mud::BlockRadiance>());
        module.m_types.push_back(&type<mud::BlockShadow>());
        module.m_types.push_back(&type<mud::ParticleEmitter>());
        module.m_types.push_back(&type<mud::RenderTarget>());
        module.m_types.push_back(&type<mud::SceneViewer>());
    
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
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::model(val<mud::Gnode>(args[0]), val<std::string>(args[1]), val<uint32_t>(args[2]), &val<mud::Material>(args[3]), val<size_t>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "name", var(std::string()) }, { "flags", var(uint32_t()), Param::Default }, { "material", Ref(type<mud::Material>()), Param::Flags(Param::Nullable|Param::Default) }, { "instances", var(size_t()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "gfx" }), "model", function_id<mud::Item&(*)(mud::Gnode&, const std::string&, uint32_t, mud::Material*, size_t)>(&mud::gfx::model), func, params, Ref(type<mud::Item>()) });
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
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::viewer(val<mud::Widget>(args[0]), val<mud::Scene>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "scene", Ref(type<mud::Scene>()) } };
            module.m_functions.push_back({ &namspc({ "mud", "ui" }), "viewer", function_id<mud::Viewer&(*)(mud::Widget&, mud::Scene&)>(&mud::ui::viewer), func, params, Ref(type<mud::Viewer>()) });
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::scene_viewer(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()), Param::Default } };
            module.m_functions.push_back({ &namspc({ "mud", "ui" }), "scene_viewer", function_id<mud::SceneViewer&(*)(mud::Widget&, const mud::vec2&)>(&mud::ui::scene_viewer), func, params, Ref(type<mud::SceneViewer>()) });
        }
    }
#endif

}
