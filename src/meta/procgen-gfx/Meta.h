

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
    
    
    
    
        
    // mud::WfcBlock
    {
        static Meta meta = { type<mud::WfcBlock>(), &namspc({ "mud" }), "WfcBlock", sizeof(mud::WfcBlock), TypeClass::Object };
        static Class cls = { type<mud::WfcBlock>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::WfcBlock>(), [](Ref ref, array<Var> args) { new(&val<mud::WfcBlock>(ref)) mud::WfcBlock( val<mud::vec3>(args[0]), val<mud::uvec3>(args[1]), val<mud::vec3>(args[2]), val<mud::WaveTileset>(args[3]), val<bool>(args[4]) ); }, { { "position", var(mud::vec3()) }, { "size", var(mud::uvec3()) }, { "scale", var(mud::vec3()) }, { "tileset", var(mud::WaveTileset()) }, { "auto_solve", var(bool(false)), Param::Default } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::WfcBlock>(), member_address(&mud::WfcBlock::m_position), type<mud::vec3>(), "position", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::WfcBlock>(), member_address(&mud::WfcBlock::m_size), type<mud::uvec3>(), "size", var(mud::uvec3()), Member::Value, nullptr },
                { type<mud::WfcBlock>(), member_address(&mud::WfcBlock::m_scale), type<mud::vec3>(), "scale", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::WfcBlock>(), member_address(&mud::WfcBlock::m_aabb), type<mud::Aabb>(), "aabb", var(mud::Aabb()), Member::Value, nullptr }
            },
            // methods
            {
                { type<mud::WfcBlock>(), "reset", member_address(&mud::WfcBlock::reset), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::WfcBlock>(object).reset(); }, {}, Var() },
                { type<mud::WfcBlock>(), "observe", member_address(&mud::WfcBlock::observe), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::WfcBlock>(object).observe(); }, {}, Var() },
                { type<mud::WfcBlock>(), "propagate", member_address(&mud::WfcBlock::propagate), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::WfcBlock>(object).propagate(); }, {}, Var() },
                { type<mud::WfcBlock>(), "solve", member_address(&mud::WfcBlock::solve), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::WfcBlock>(object).solve(val<size_t>(args[0])); }, { { "limit", var(size_t()), Param::Default } }, Var() },
                { type<mud::WfcBlock>(), "update", member_address(&mud::WfcBlock::update), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::WfcBlock>(object).update(val<mud::Wave>(args[0])); }, { { "wave", var(mud::Wave()) } }, Var() }
            },
            // static members
            {
            }
        };
        
        
        init_pool<mud::WfcBlock>(); 
        
        meta_class<mud::WfcBlock>();
    }
    

    
        m.m_types.push_back(&type<mud::TileModel>());
        m.m_types.push_back(&type<mud::WfcBlock>());
    
    }
}
