

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
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Complex>(), member_address(&mud::Complex::m_id), type<mud::Id>(), "id", var(mud::Id()), Member::Value },
                { type<mud::Complex>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Link },
                { type<mud::Complex>(), Address(), type<mud::Prototype>(), "prototype", Ref(type<mud::Prototype>()), Member::Link }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
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
