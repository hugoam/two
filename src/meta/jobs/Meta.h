#pragma once

#ifndef MUD_MODULES
#include <meta/jobs/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_jobs_meta(Module& m)
    {
    
    // Base Types
    
    // Enums
    
    // Sequences
    
    // mud::JobSystem
    {
        static Meta meta = { type<mud::JobSystem>(), &namspc({ "mud" }), "JobSystem", sizeof(mud::JobSystem), TypeClass::Object };
        static Class cls = { type<mud::JobSystem>(),
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
        meta_class<mud::JobSystem>();
    }
        m.m_types.push_back(&type<mud::JobSystem>());
    }
}
