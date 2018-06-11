

#pragma once

#ifndef MUD_MODULES
#include <meta/procgen-gfx/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_procgen_gfx_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    
    // Sequences
    
    
    
        
    // mud::TileModel
    {
        static Meta meta = { type<mud::TileModel>(), &namspc({ "mud" }), "TileModel", sizeof(mud::TileModel), TypeClass::Struct };
        static Class cls = { type<mud::TileModel>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::TileModel>(), [](Ref ref, Ref other) { new(&val<mud::TileModel>(ref)) mud::TileModel(val<mud::TileModel>(other)); } }
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
        
        
        
        
        meta_class<mud::TileModel>();
    }
    
    
        
    // mud::Tileblock
    {
        static Meta meta = { type<mud::Tileblock>(), &namspc({ "mud" }), "Tileblock", sizeof(mud::Tileblock), TypeClass::Object };
        static Class cls = { type<mud::Tileblock>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Tileblock>(), [](Ref ref, array<Var> args) { new(&val<mud::Tileblock>(ref)) mud::Tileblock( val<mud::uvec3>(args[0]), val<mud::vec3>(args[1]), val<mud::WaveTileset>(args[2]) ); }, { { "size", var(mud::uvec3()) }, { "period", var(mud::vec3()) }, { "tileset", var(mud::WaveTileset()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Tileblock>(), member_address(&mud::Tileblock::m_size), type<mud::uvec3>(), "size", var(mud::uvec3()), Member::Value },
                { type<mud::Tileblock>(), member_address(&mud::Tileblock::m_period), type<mud::vec3>(), "period", var(mud::vec3()), Member::Value },
                { type<mud::Tileblock>(), member_address(&mud::Tileblock::m_aabb), type<mud::Aabb>(), "aabb", var(mud::Aabb()), Member::Value }
            },
            // methods
            {
                { type<mud::Tileblock>(), "reset", member_address(&mud::Tileblock::reset), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Tileblock>(object).reset(); }, {}, Var() },
                { type<mud::Tileblock>(), "observe", member_address(&mud::Tileblock::observe), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Tileblock>(object).observe(); }, {}, Var() },
                { type<mud::Tileblock>(), "propagate", member_address(&mud::Tileblock::propagate), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Tileblock>(object).propagate(); }, {}, Var() },
                { type<mud::Tileblock>(), "solve", member_address(&mud::Tileblock::solve), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Tileblock>(object).solve(val<size_t>(args[0])); }, { { "limit", var(size_t()), Param::Default } }, Var() },
                { type<mud::Tileblock>(), "update", member_address(&mud::Tileblock::update), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Tileblock>(object).update(val<mud::Wave>(args[0])); }, { { "wave", var(mud::Wave()) } }, Var() }
            },
            // static members
            {
            }
        };
        
        
        init_pool<mud::Tileblock>(); 
        
        meta_class<mud::Tileblock>();
    }
    

    
        m.m_types.push_back(&type<mud::TileModel>());
        m.m_types.push_back(&type<mud::Tileblock>());
    
    }
}
