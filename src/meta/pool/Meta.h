#pragma once

#ifndef MUD_MODULES
#include <meta/pool/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_pool_meta(Module& m)
    {
    UNUSED(m);
    
    // Base Types
    
    // Enums
    
    // Sequences
    
    // mud::HandlePool
    {
        static Meta meta = { type<mud::HandlePool>(), &namspc({ "mud" }), "HandlePool", sizeof(mud::HandlePool), TypeClass::Object };
        static Class cls = { type<mud::HandlePool>(),
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
        meta_class<mud::HandlePool>();
    }
    // mud::Pool
    {
        static Meta meta = { type<mud::Pool>(), &namspc({ "mud" }), "Pool", sizeof(mud::Pool), TypeClass::Object };
        static Class cls = { type<mud::Pool>(),
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
        meta_class<mud::Pool>();
    }
        m.m_types.push_back(&type<mud::HandlePool>());
        m.m_types.push_back(&type<mud::Pool>());
    }
}
