

#pragma once

#ifndef MUD_MODULES
#include <meta/ctx/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_ctx_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    
    // Sequences
    
    
    
        
    // mud::Context
    {
        static Meta meta = { type<mud::Context>(), &namspc({ "mud" }), "Context", sizeof(mud::Context), TypeClass::Object };
        static Class cls = { type<mud::Context>(),
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
        
        
        
        
        meta_class<mud::Context>();
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    // mud::RenderSystem
    {
        static Meta meta = { type<mud::RenderSystem>(), &namspc({ "mud" }), "RenderSystem", sizeof(mud::RenderSystem), TypeClass::Object };
        static Class cls = { type<mud::RenderSystem>(),
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
        
        
        
        
        meta_class<mud::RenderSystem>();
    }
    
    
    

    
        m.m_types.push_back(&type<mud::Context>());
        m.m_types.push_back(&type<mud::RenderSystem>());
    
    }
}
