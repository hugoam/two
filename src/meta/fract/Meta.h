#pragma once

#ifndef MUD_MODULES
#include <meta/fract/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_fract_meta(Module& m)
    {
    
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::PatternSampling>(), &namspc({ "mud" }), "PatternSampling", sizeof(mud::PatternSampling), TypeClass::Enum };
        static Enum enu = { type<mud::PatternSampling>(),
            true,
            { "X", "XY", "Depth" },
            { 0, 1, 2 },
            { var(mud::PatternSampling::X), var(mud::PatternSampling::XY), var(mud::PatternSampling::Depth) }
        };
        meta_enum<mud::PatternSampling>();
    }
    
    // Sequences
    {
        static Meta meta = { type<std::vector<mud::Image256>>(), &namspc({}), "std::vector<mud::Image256>", sizeof(std::vector<mud::Image256>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Image256>>() };
        cls.m_content = &type<mud::Image256>();
        meta_sequence<std::vector<mud::Image256>, mud::Image256>();
    }
    
    // mud::Circlifier
    {
        static Meta meta = { type<mud::Circlifier>(), &namspc({ "mud" }), "Circlifier", sizeof(mud::Circlifier), TypeClass::Struct };
        static Class cls = { type<mud::Circlifier>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Circlifier>(), [](Ref ref, array<Var> args) { new(&val<mud::Circlifier>(ref)) mud::Circlifier( val<mud::Image256>(args[0]) ); }, { { "image", var(mud::Image256()) } } }
            },
            // copy constructor
            {
                { type<mud::Circlifier>(), [](Ref ref, Ref other) { new(&val<mud::Circlifier>(ref)) mud::Circlifier(val<mud::Circlifier>(other)); } }
            },
            // members
            {
            },
            // methods
            {
                { type<mud::Circlifier>(), "compute", member_address<std::vector<mud::Circle>(mud::Circlifier::*)(const mud::Colour&, float)>(&mud::Circlifier::compute), [](Ref object, array<Var> args, Var& result) { val<std::vector<mud::Circle>>(result) = val<mud::Circlifier>(object).compute(val<mud::Colour>(args[0]), val<float>(args[1])); }, { { "colour", var(mud::Colour()) }, { "scale", var(float(1.f)), Param::Default } }, var(std::vector<mud::Circle>()) }
            },
            // static members
            {
            }
        };
        meta_class<mud::Circlifier>();
    }
    // mud::Fract
    {
        static Meta meta = { type<mud::Fract>(), &namspc({ "mud" }), "Fract", sizeof(mud::Fract), TypeClass::Object };
        static Class cls = { type<mud::Fract>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Fract>(), [](Ref ref, array<Var> args) { new(&val<mud::Fract>(ref)) mud::Fract( val<size_t>(args[0]) ); }, { { "num_tabs", var(size_t(75)), Param::Default } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Fract>(), member_address(&mud::Fract::m_num_tabs), type<size_t>(), "nutabs", var(size_t()), Member::Value, nullptr }
            },
            // methods
            {
                { type<mud::Fract>(), "generate", member_address<void(mud::Fract::*)(size_t)>(&mud::Fract::generate), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).generate(val<size_t>(args[0])); }, { { "num_tabs", var(size_t(75)), Param::Default } }, Var() },
                { type<mud::Fract>(), "regen", member_address<void(mud::Fract::*)()>(&mud::Fract::regen), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Fract>(object).regen(); }, {}, Var() },
                { type<mud::Fract>(), "render", member_address<void(mud::Fract::*)(const mud::Rect&, const mud::Pattern&, mud::uvec2, mud::Image256&)>(&mud::Fract::render), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).render(val<mud::Rect>(args[0]), val<mud::Pattern>(args[1]), val<mud::uvec2>(args[2]), val<mud::Image256>(args[3])); }, { { "rect", var(mud::Rect()) }, { "pattern", var(mud::Pattern()) }, { "resolution", var(mud::uvec2()) }, { "output_image", var(mud::Image256()), Param::Output } }, Var() },
                { type<mud::Fract>(), "render_whole", member_address<void(mud::Fract::*)(const mud::Pattern&, mud::uvec2, mud::Image256&)>(&mud::Fract::render_whole), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).render_whole(val<mud::Pattern>(args[0]), val<mud::uvec2>(args[1]), val<mud::Image256>(args[2])); }, { { "pattern", var(mud::Pattern()) }, { "resolution", var(mud::uvec2()) }, { "output_image", var(mud::Image256()), Param::Output } }, Var() },
                { type<mud::Fract>(), "render_grid", member_address<void(mud::Fract::*)(mud::uvec2, const mud::Pattern&, mud::uvec2, std::vector<mud::Image256>&)>(&mud::Fract::render_grid), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).render_grid(val<mud::uvec2>(args[0]), val<mud::Pattern>(args[1]), val<mud::uvec2>(args[2]), val<std::vector<mud::Image256>>(args[3])); }, { { "size", var(mud::uvec2()) }, { "pattern", var(mud::Pattern()) }, { "resolution", var(mud::uvec2()) }, { "output_images", var(std::vector<mud::Image256>()), Param::Output } }, Var() }
            },
            // static members
            {
            }
        };
        init_pool<mud::Fract>();
        meta_class<mud::Fract>();
    }
    // mud::FractSample
    {
        static Meta meta = { type<mud::FractSample>(), &namspc({ "mud" }), "FractSample", sizeof(mud::FractSample), TypeClass::Object };
        static Class cls = { type<mud::FractSample>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::FractSample>(), [](Ref ref, array<Var> args) { new(&val<mud::FractSample>(ref)) mud::FractSample( val<mud::Fract>(args[0]), val<mud::Rect>(args[1]), val<mud::uvec2>(args[2]) ); }, { { "fract", Ref(type<mud::Fract>()) }, { "rect", var(mud::Rect()) }, { "resolution", var(mud::uvec2()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::FractSample>(), Address(), type<mud::Fract>(), "fract", Ref(type<mud::Fract>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::FractSample>(object).m_fract); } },
                { type<mud::FractSample>(), member_address(&mud::FractSample::m_rect), type<mud::Rect>(), "rect", var(mud::Rect()), Member::Value, nullptr },
                { type<mud::FractSample>(), member_address(&mud::FractSample::m_resolution), type<mud::uvec2>(), "resolution", var(mud::uvec2()), Member::Value, nullptr }
            },
            // methods
            {
                { type<mud::FractSample>(), "render", member_address<void(mud::FractSample::*)(const mud::Pattern&, mud::Image256&)>(&mud::FractSample::render), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::FractSample>(object).render(val<mud::Pattern>(args[0]), val<mud::Image256>(args[1])); }, { { "pattern", var(mud::Pattern()) }, { "outputImage", var(mud::Image256()), Param::Output } }, Var() }
            },
            // static members
            {
            }
        };
        init_pool<mud::FractSample>();
        meta_class<mud::FractSample>();
    }
    // mud::FractTab
    {
        static Meta meta = { type<mud::FractTab>(), &namspc({ "mud" }), "FractTab", sizeof(mud::FractTab), TypeClass::Struct };
        static Class cls = { type<mud::FractTab>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::FractTab>(), [](Ref ref, Ref other) { new(&val<mud::FractTab>(ref)) mud::FractTab(val<mud::FractTab>(other)); } }
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
        meta_class<mud::FractTab>();
    }
    // mud::Pattern
    {
        static Meta meta = { type<mud::Pattern>(), &namspc({ "mud" }), "Pattern", sizeof(mud::Pattern), TypeClass::Struct };
        static Class cls = { type<mud::Pattern>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Pattern>(), [](Ref ref, array<Var> args) { new(&val<mud::Pattern>(ref)) mud::Pattern( val<mud::Palette>(args[0]), val<mud::PatternSampling>(args[1]), val<float>(args[2]), val<size_t>(args[3]) ); }, { { "palette", var(mud::Palette()) }, { "sampling", var(mud::PatternSampling()) }, { "precision", var(float(1.f)), Param::Default }, { "step", var(size_t(1)), Param::Default } } },
                { type<mud::Pattern>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Pattern>(ref)) mud::Pattern(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Pattern>(), [](Ref ref, Ref other) { new(&val<mud::Pattern>(ref)) mud::Pattern(val<mud::Pattern>(other)); } }
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
        meta_class<mud::Pattern>();
    }
        m.m_types.push_back(&type<mud::Circlifier>());
        m.m_types.push_back(&type<mud::Fract>());
        m.m_types.push_back(&type<mud::FractSample>());
        m.m_types.push_back(&type<mud::FractTab>());
        m.m_types.push_back(&type<mud::Pattern>());
        m.m_types.push_back(&type<mud::PatternSampling>());
        m.m_types.push_back(&type<std::vector<mud::Image256>>());
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::generate_fract(val<mud::uvec2>(args[0]), val<mud::Pattern>(args[1]), val<mud::Image256>(args[2])); };
            std::vector<Param> params = { { "resolution", var(mud::uvec2()) }, { "pattern", var(mud::Pattern()) }, { "output_image", var(mud::Image256()), Param::Output } };
            static Function f = { &namspc({ "mud" }), "generate_fract", function_id<void(*)(mud::uvec2, const mud::Pattern&, mud::Image256&)>(&mud::generate_fract), func, params, Var() };
            m.m_functions.push_back(&f);
        }
    }
}
