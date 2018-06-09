

#pragma once

#ifndef MUD_MODULES
#include <meta/15_script/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void ex_15_script_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    
    // Sequences
    
    
    
        
    // GameObject
    {
        static Meta meta = { type<GameObject>(), &namspc({}), "GameObject", sizeof(GameObject), TypeClass::Object };
        static Class cls = { type<GameObject>(),
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
                { type<GameObject>(), member_address(&GameObject::m_index), type<uint32_t>(), "index", var(uint32_t()), Member::Value },
                { type<GameObject>(), member_address(&GameObject::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<GameObject>();
    }
    

    
        m.m_types.push_back(&type<GameObject>());
    
    }
}
