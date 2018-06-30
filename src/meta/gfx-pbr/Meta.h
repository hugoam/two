

#pragma once

#ifndef MUD_MODULES
#include <meta/gfx-pbr/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
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
    

    
        m.m_types.push_back(&type<mud::BCS>());
        m.m_types.push_back(&type<mud::DofBlur>());
        m.m_types.push_back(&type<mud::Glow>());
        m.m_types.push_back(&type<mud::LightShadow>());
        m.m_types.push_back(&type<mud::ReflectionProbe>());
        m.m_types.push_back(&type<mud::RenderFilters>());
        m.m_types.push_back(&type<mud::Tonemap>());
        m.m_types.push_back(&type<mud::TonemapMode>());
        m.m_types.push_back(&type<mud::BlockBlur>());
        m.m_types.push_back(&type<mud::BlockDofBlur>());
        m.m_types.push_back(&type<mud::BlockGlow>());
        m.m_types.push_back(&type<mud::BlockReflection>());
        m.m_types.push_back(&type<mud::BlockTonemap>());
        m.m_types.push_back(&type<mud::BlockLight>());
        m.m_types.push_back(&type<mud::BlockRadiance>());
        m.m_types.push_back(&type<mud::BlockShadow>());
    
    }
}
