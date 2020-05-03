

#pragma once

#ifndef MUD_MODULES
#include <meta/15_script/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void _15_script_meta(Module& m)
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
                { type<GameObject>(), member_address(&GameObject::m_index), type<uint32_t>(), "index", var(uint32_t()), Member::Value, nullptr },
                { type<GameObject>(), member_address(&GameObject::m_colour), type<two::Colour>(), "colour", var(two::Colour()), Member::Value, nullptr }
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
