

#pragma once

#ifndef MUD_MODULES
#include <meta/proto/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_proto_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    
    // Sequences
    
    
    
        
    // mud::Complex
    {
        static Meta meta = { type<mud::Complex>(), &namspc({ "mud" }), "Complex", sizeof(mud::Complex), TypeClass::Object };
        static Class cls = { type<mud::Complex>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Complex>(), [](Ref ref, array<Var> args) { new(&val<mud::Complex>(ref)) mud::Complex( val<mud::Id>(args[0]), val<mud::Type>(args[1]) ); }, { { "id", var(mud::Id()) }, { "type", Ref(type<mud::Type>()) } } },
                { type<mud::Complex>(), [](Ref ref, array<Var> args) { new(&val<mud::Complex>(ref)) mud::Complex( val<mud::Id>(args[0]), val<mud::Type>(args[1]), val<std::vector<mud::Ref>>(args[2]) ); }, { { "id", var(mud::Id()) }, { "type", Ref(type<mud::Type>()) }, { "parts", var(std::vector<mud::Ref>()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Complex>(), member_address(&mud::Complex::m_id), type<mud::Id>(), "id", var(mud::Id()), Member::Value, nullptr },
                { type<mud::Complex>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Complex>(object).m_type); } },
                { type<mud::Complex>(), Address(), type<mud::Prototype>(), "prototype", Ref(type<mud::Prototype>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Complex>(object).m_prototype); } }
            },
            // methods
            {
                { type<mud::Complex>(), "setup", member_address(&mud::Complex::setup), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Complex>(object).setup(val<std::vector<mud::Ref>>(args[0])); }, { { "parts", var(std::vector<mud::Ref>()) } }, Var() },
                { type<mud::Complex>(), "add_part", member_address(&mud::Complex::add_part), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Complex>(object).add_part(args[0]); }, { { "part", Ref(), Param::Nullable } }, Var() },
                { type<mud::Complex>(), "has_part", member_address(&mud::Complex::has_part), [](Ref object, array<Var> args, Var& result) { val<bool>(result) = val<mud::Complex>(object).has_part(val<mud::Type>(args[0])); }, { { "type", Ref(type<mud::Type>()) } }, var(bool()) },
                { type<mud::Complex>(), "part", member_address(&mud::Complex::part), [](Ref object, array<Var> args, Var& result) { result = val<mud::Complex>(object).part(val<mud::Type>(args[0])); }, { { "type", Ref(type<mud::Type>()) } }, Ref() },
                { type<mud::Complex>(), "try_part", member_address(&mud::Complex::try_part), [](Ref object, array<Var> args, Var& result) { result = val<mud::Complex>(object).try_part(val<mud::Type>(args[0])); }, { { "type", Ref(type<mud::Type>()) } }, Ref() }
            },
            // static members
            {
            }
        };
        
        
        init_pool<mud::Complex>(); 
        
        meta_class<mud::Complex>();
    }
    
    
        
    // mud::Prototype
    {
        static Meta meta = { type<mud::Prototype>(), &namspc({ "mud" }), "Prototype", sizeof(mud::Prototype), TypeClass::Object };
        static Class cls = { type<mud::Prototype>(),
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
        
        
        
        
        meta_class<mud::Prototype>();
    }
    
    
    

    
        m.m_types.push_back(&type<mud::Complex>());
        m.m_types.push_back(&type<mud::Prototype>());
    
    }
}
