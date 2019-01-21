#pragma once

#ifndef MUD_MODULES
#include <meta/gfx-pbr/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_gfx_pbr_meta(Module& m)
    {
    
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::TonemapMode>(), &namspc({ "mud" }), "TonemapMode", sizeof(mud::TonemapMode), TypeClass::Enum };
        static Enum enu = { type<mud::TonemapMode>(),
            true,
            { "Linear", "Reinhardt", "Filmic", "ACES" },
            { 0, 1, 2, 3 },
            { var(mud::TonemapMode::Linear), var(mud::TonemapMode::Reinhardt), var(mud::TonemapMode::Filmic), var(mud::TonemapMode::ACES) }
        };
        meta_enum<mud::TonemapMode>();
    }
    
    // Sequences
    
    // mud::BCS
    {
        static Meta meta = { type<mud::BCS>(), &namspc({ "mud" }), "BCS", sizeof(mud::BCS), TypeClass::Struct };
        static Class cls = { type<mud::BCS>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::BCS>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::BCS>(ref)) mud::BCS(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::BCS>(), [](Ref ref, Ref other) { new(&val<mud::BCS>(ref)) mud::BCS(val<mud::BCS>(other)); } }
            },
            // members
            {
                { type<mud::BCS>(), member_address(&mud::BCS::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Value, nullptr },
                { type<mud::BCS>(), member_address(&mud::BCS::m_brightness), type<float>(), "brightness", var(float(1.0f)), Member::Value, nullptr },
                { type<mud::BCS>(), member_address(&mud::BCS::m_contrast), type<float>(), "contrast", var(float(1.0f)), Member::Value, nullptr },
                { type<mud::BCS>(), member_address(&mud::BCS::m_saturation), type<float>(), "saturation", var(float(1.0f)), Member::Value, nullptr }
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
    // mud::DofBlur
    {
        static Meta meta = { type<mud::DofBlur>(), &namspc({ "mud" }), "DofBlur", sizeof(mud::DofBlur), TypeClass::Struct };
        static Class cls = { type<mud::DofBlur>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::DofBlur>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::DofBlur>(ref)) mud::DofBlur(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::DofBlur>(), [](Ref ref, Ref other) { new(&val<mud::DofBlur>(ref)) mud::DofBlur(val<mud::DofBlur>(other)); } }
            },
            // members
            {
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Value, nullptr },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_far_distance), type<float>(), "far_distance", var(float(10.f)), Member::Value, nullptr },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_far_transition), type<float>(), "far_transition", var(float(5.f)), Member::Value, nullptr },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_far_radius), type<float>(), "far_radius", var(float(5.f)), Member::Value, nullptr },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_near_distance), type<float>(), "near_distance", var(float(2.f)), Member::Value, nullptr },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_near_transition), type<float>(), "near_transition", var(float(1.f)), Member::Value, nullptr },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_near_radius), type<float>(), "near_radius", var(float(5.f)), Member::Value, nullptr },
                { type<mud::DofBlur>(), member_address(&mud::DofBlur::m_max_coc_radius), type<float>(), "max_coc_radius", var(float(8.f)), Member::Value, nullptr }
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
    // mud::GIProbe
    {
        static Meta meta = { type<mud::GIProbe>(), &namspc({ "mud" }), "GIProbe", sizeof(mud::GIProbe), TypeClass::Object };
        static Class cls = { type<mud::GIProbe>(),
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
        meta_class<mud::GIProbe>();
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
                { type<mud::Glow>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Glow>(ref)) mud::Glow(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Glow>(), [](Ref ref, Ref other) { new(&val<mud::Glow>(ref)) mud::Glow(val<mud::Glow>(other)); } }
            },
            // members
            {
                { type<mud::Glow>(), member_address(&mud::Glow::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Value, nullptr },
                { type<mud::Glow>(), member_address(&mud::Glow::m_levels_1_4), type<mud::vec4>(), "levels_1_4", var(mud::vec4{1.f,0.f,0.f,0.f}), Member::Value, nullptr },
                { type<mud::Glow>(), member_address(&mud::Glow::m_levels_5_8), type<mud::vec4>(), "levels_5_8", var(mud::vec4(Zero4)), Member::Value, nullptr },
                { type<mud::Glow>(), member_address(&mud::Glow::m_intensity), type<float>(), "intensity", var(float(0.4f)), Member::Value, nullptr },
                { type<mud::Glow>(), member_address(&mud::Glow::m_bloom), type<float>(), "bloom", var(float(0.0f)), Member::Value, nullptr },
                { type<mud::Glow>(), member_address(&mud::Glow::m_bleed_threshold), type<float>(), "bleed_threshold", var(float(1.0f)), Member::Value, nullptr },
                { type<mud::Glow>(), member_address(&mud::Glow::m_bleed_scale), type<float>(), "bleed_scale", var(float(2.0f)), Member::Value, nullptr },
                { type<mud::Glow>(), member_address(&mud::Glow::m_bicubic_filter), type<bool>(), "bicubic_filter", var(bool(false)), Member::Value, nullptr }
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
    // mud::LightShadow
    {
        static Meta meta = { type<mud::LightShadow>(), &namspc({ "mud" }), "LightShadow", sizeof(mud::LightShadow), TypeClass::Struct };
        static Class cls = { type<mud::LightShadow>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::LightShadow>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::LightShadow>(ref)) mud::LightShadow(  ); }, {} }
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
    // mud::Lightmap
    {
        static Meta meta = { type<mud::Lightmap>(), &namspc({ "mud" }), "Lightmap", sizeof(mud::Lightmap), TypeClass::Object };
        static Class cls = { type<mud::Lightmap>(),
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
        meta_class<mud::Lightmap>();
    }
    // mud::LightmapAtlas
    {
        static Meta meta = { type<mud::LightmapAtlas>(), &namspc({ "mud" }), "LightmapAtlas", sizeof(mud::LightmapAtlas), TypeClass::Object };
        static Class cls = { type<mud::LightmapAtlas>(),
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
        meta_class<mud::LightmapAtlas>();
    }
    // mud::LightmapItem
    {
        static Meta meta = { type<mud::LightmapItem>(), &namspc({ "mud" }), "LightmapItem", sizeof(mud::LightmapItem), TypeClass::Object };
        static Class cls = { type<mud::LightmapItem>(),
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
        meta_class<mud::LightmapItem>();
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
                { type<mud::ReflectionProbe>(), Address(), type<mud::Node3>(), "node", Ref(type<mud::Node3>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::ReflectionProbe>(object).m_node); } },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_visible), type<bool>(), "visible", var(bool(true)), Member::Value, nullptr },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_intensity), type<float>(), "intensity", var(float(1.f)), Member::Value, nullptr },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_extents), type<mud::vec3>(), "extents", var(mud::vec3(Zero3)), Member::Value, nullptr },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_shadows), type<bool>(), "shadows", var(bool(false)), Member::Value, nullptr },
                { type<mud::ReflectionProbe>(), member_address(&mud::ReflectionProbe::m_dirty), type<bool>(), "dirty", var(bool(true)), Member::Value, nullptr }
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
                { type<mud::RenderFilters>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::RenderFilters>(ref)) mud::RenderFilters(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::RenderFilters>(), [](Ref ref, Ref other) { new(&val<mud::RenderFilters>(ref)) mud::RenderFilters(val<mud::RenderFilters>(other)); } }
            },
            // members
            {
                { type<mud::RenderFilters>(), member_address(&mud::RenderFilters::m_dof_blur), type<mud::DofBlur>(), "dof_blur", var(mud::DofBlur()), Member::Value, nullptr },
                { type<mud::RenderFilters>(), member_address(&mud::RenderFilters::m_glow), type<mud::Glow>(), "glow", var(mud::Glow()), Member::Value, nullptr },
                { type<mud::RenderFilters>(), member_address(&mud::RenderFilters::m_bcs), type<mud::BCS>(), "bcs", var(mud::BCS()), Member::Value, nullptr },
                { type<mud::RenderFilters>(), member_address(&mud::RenderFilters::m_tonemap), type<mud::Tonemap>(), "tonemap", var(mud::Tonemap()), Member::Value, nullptr }
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
    // mud::Tonemap
    {
        static Meta meta = { type<mud::Tonemap>(), &namspc({ "mud" }), "Tonemap", sizeof(mud::Tonemap), TypeClass::Struct };
        static Class cls = { type<mud::Tonemap>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Tonemap>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Tonemap>(ref)) mud::Tonemap(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Tonemap>(), [](Ref ref, Ref other) { new(&val<mud::Tonemap>(ref)) mud::Tonemap(val<mud::Tonemap>(other)); } }
            },
            // members
            {
                { type<mud::Tonemap>(), member_address(&mud::Tonemap::m_mode), type<mud::TonemapMode>(), "mode", var(mud::TonemapMode::Linear), Member::Value, nullptr },
                { type<mud::Tonemap>(), member_address(&mud::Tonemap::m_enabled), type<bool>(), "enabled", var(bool(false)), Member::Value, nullptr },
                { type<mud::Tonemap>(), member_address(&mud::Tonemap::m_exposure), type<float>(), "exposure", var(float(1.0f)), Member::Value, nullptr },
                { type<mud::Tonemap>(), member_address(&mud::Tonemap::m_white_point), type<float>(), "white_point", var(float(1.0f)), Member::Value, nullptr }
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
    // mud::BlockGIBake
    {
        static Meta meta = { type<mud::BlockGIBake>(), &namspc({ "mud" }), "BlockGIBake", sizeof(mud::BlockGIBake), TypeClass::Object };
        static Class cls = { type<mud::BlockGIBake>(),
            // bases
            { &type<mud::DrawBlock>() },
            { base_offset<mud::BlockGIBake, mud::DrawBlock>() },
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
        meta_class<mud::BlockGIBake>();
    }
    // mud::BlockGITrace
    {
        static Meta meta = { type<mud::BlockGITrace>(), &namspc({ "mud" }), "BlockGITrace", sizeof(mud::BlockGITrace), TypeClass::Object };
        static Class cls = { type<mud::BlockGITrace>(),
            // bases
            { &type<mud::DrawBlock>() },
            { base_offset<mud::BlockGITrace, mud::DrawBlock>() },
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
        meta_class<mud::BlockGITrace>();
    }
    // mud::BlockGeometry
    {
        static Meta meta = { type<mud::BlockGeometry>(), &namspc({ "mud" }), "BlockGeometry", sizeof(mud::BlockGeometry), TypeClass::Object };
        static Class cls = { type<mud::BlockGeometry>(),
            // bases
            { &type<mud::DrawBlock>() },
            { base_offset<mud::BlockGeometry, mud::DrawBlock>() },
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
        meta_class<mud::BlockGeometry>();
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
    // mud::BlockLightmap
    {
        static Meta meta = { type<mud::BlockLightmap>(), &namspc({ "mud" }), "BlockLightmap", sizeof(mud::BlockLightmap), TypeClass::Object };
        static Class cls = { type<mud::BlockLightmap>(),
            // bases
            { &type<mud::DrawBlock>() },
            { base_offset<mud::BlockLightmap, mud::DrawBlock>() },
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
        meta_class<mud::BlockLightmap>();
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
    // mud::BlockReflection
    {
        static Meta meta = { type<mud::BlockReflection>(), &namspc({ "mud" }), "BlockReflection", sizeof(mud::BlockReflection), TypeClass::Object };
        static Class cls = { type<mud::BlockReflection>(),
            // bases
            { &type<mud::DrawBlock>() },
            { base_offset<mud::BlockReflection, mud::DrawBlock>() },
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
        m.m_types.push_back(&type<mud::BCS>());
        m.m_types.push_back(&type<mud::DofBlur>());
        m.m_types.push_back(&type<mud::GIProbe>());
        m.m_types.push_back(&type<mud::Glow>());
        m.m_types.push_back(&type<mud::LightShadow>());
        m.m_types.push_back(&type<mud::Lightmap>());
        m.m_types.push_back(&type<mud::LightmapAtlas>());
        m.m_types.push_back(&type<mud::LightmapItem>());
        m.m_types.push_back(&type<mud::ReflectionProbe>());
        m.m_types.push_back(&type<mud::RenderFilters>());
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
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::gi_probe(val<mud::Gnode>(args[0]), val<uint16_t>(args[1]), val<mud::vec3>(args[2]))); };
            vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "subdiv", var(uint16_t()) }, { "extents", var(mud::vec3()) } };
            static Function f = { &namspc({ "mud", "gfx" }), "gi_probe", funcptr<mud::GIProbe&(*)(mud::Gnode&, uint16_t, const mud::vec3&)>(&mud::gfx::gi_probe), func, params, Ref(type<mud::GIProbe>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::lightmap(val<mud::Gnode>(args[0]), val<uint32_t>(args[1]), val<float>(args[2]), val<string>(args[3]))); };
            vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "resolution", var(uint32_t()) }, { "density", var(float(8.f)), Param::Default }, { "save_path", var(string("")), Param::Default } };
            static Function f = { &namspc({ "mud", "gfx" }), "lightmap", funcptr<mud::LightmapAtlas&(*)(mud::Gnode&, uint32_t, float, const string&)>(&mud::gfx::lightmap), func, params, Ref(type<mud::LightmapAtlas>()) };
            m.m_functions.push_back(&f);
        }
    }
}
