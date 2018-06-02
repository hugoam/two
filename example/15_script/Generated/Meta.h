

#pragma once

#include <15_script/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>

namespace mud
{
    
#ifdef _15_SCRIPT_REFLECTION_IMPL
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
#endif

}
