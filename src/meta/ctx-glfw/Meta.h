

#pragma once

#ifndef MUD_MODULES
#include <meta/ctx-glfw/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_ctx_glfw_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    
    // Sequences
    
    
    
        
    // mud::GlfwContext
    {
        static Meta meta = { type<mud::GlfwContext>(), &namspc({ "mud" }), "GlfwContext", sizeof(mud::GlfwContext), TypeClass::Object };
        static Class cls = { type<mud::GlfwContext>(),
            // bases
            { &type<mud::Context>() },
            { base_offset<mud::GlfwContext, mud::Context>() },
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
        
        
        
        
        meta_class<mud::GlfwContext>();
    }
    

    
        m.m_types.push_back(&type<mud::GlfwContext>());
    
    }
}
