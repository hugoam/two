

#pragma once

#include <ctx/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>

namespace mud
{
    
#ifdef MUD_CTX_REFLECTION_IMPL
    void ctx_meta(Module& module)
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
    

    
        module.m_types.push_back(&type<mud::Context>());
        module.m_types.push_back(&type<mud::RenderSystem>());
    
    }
#endif

}
