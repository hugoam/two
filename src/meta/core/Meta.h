#pragma once

#ifndef MUD_MODULES
#include <meta/core/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_core_meta(Module& m)
    {
    
    // Base Types
    
    // Enums
    
    // Sequences
    
    // mud::Shell
    {
        static Meta meta = { type<mud::Shell>(), &namspc({ "mud" }), "Shell", sizeof(mud::Shell), TypeClass::Object };
        static Class cls = { type<mud::Shell>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Shell>(), [](Ref ref, array<Var> args) { new(&val<mud::Shell>(ref)) mud::Shell( val<const char*>(args[0]), val<int>(args[1]), val<char*[]>(args[2]) ); }, { { "resource_path", Ref(type<const char*>()), Param::Nullable }, { "argc", var(int()) }, { "argv", var(char*[]()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Shell>(), member_address(&mud::Shell::m_exec_path), type<std::string>(), "exec_path", var(std::string()), Member::Value, nullptr },
                { type<mud::Shell>(), member_address(&mud::Shell::m_resource_path), type<std::string>(), "resource_path", var(std::string()), Member::Value, nullptr },
                { type<mud::Shell>(), member_address(&mud::Shell::m_job_system), type<mud::JobSystem>(), "job_system", Ref(type<mud::JobSystem>()), Member::NonMutable, nullptr },
                { type<mud::Shell>(), member_address(&mud::Shell::m_gfx_system), type<mud::GfxSystem>(), "gfx_system", Ref(type<mud::GfxSystem>()), Member::NonMutable, nullptr },
                { type<mud::Shell>(), member_address(&mud::Shell::m_editor), type<mud::ShellContext>(), "editor", var(mud::ShellContext()), Member::Value, nullptr },
                { type<mud::Shell>(), member_address(&mud::Shell::m_ui), type<mud::Ui>(), "ui", Ref(type<mud::Ui>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        init_pool<mud::Shell>();
        meta_class<mud::Shell>();
    }
    // mud::ShellContext
    {
        static Meta meta = { type<mud::ShellContext>(), &namspc({ "mud" }), "ShellContext", sizeof(mud::ShellContext), TypeClass::Struct };
        static Class cls = { type<mud::ShellContext>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ShellContext>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ShellContext>(ref)) mud::ShellContext(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::ShellContext>(), [](Ref ref, Ref other) { new(&val<mud::ShellContext>(ref)) mud::ShellContext(val<mud::ShellContext>(other)); } }
            },
            // members
            {
                { type<mud::ShellContext>(), member_address(&mud::ShellContext::m_screen), type<mud::Widget>(), "screen", Ref(type<mud::Widget>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::ShellContext>(), member_address(&mud::ShellContext::m_dockbar), type<mud::Dockbar>(), "dockbar", Ref(type<mud::Dockbar>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::ShellContext>();
    }
        m.m_types.push_back(&type<mud::Shell>());
        m.m_types.push_back(&type<mud::ShellContext>());
    }
}
