

#pragma once

#ifndef MUD_MODULES
#include <meta/lang/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_lang_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::Language>(), &namspc({ "mud" }), "Language", sizeof(mud::Language), TypeClass::Enum };
        static Enum enu = { type<mud::Language>(),
            true,
            { "Cpp", "Lua", "Wren" },
            { 0, 1, 2 },
            { var(mud::Language::Cpp), var(mud::Language::Lua), var(mud::Language::Wren) }
        };
        meta_enum<mud::Language>();
    }
    
    
    // Sequences
    
    
    
        
    // mud::Interpreter
    {
        static Meta meta = { type<mud::Interpreter>(), &namspc({ "mud" }), "Interpreter", sizeof(mud::Interpreter), TypeClass::Object };
        static Class cls = { type<mud::Interpreter>(),
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
        
        
        
        
        meta_class<mud::Interpreter>();
    }
    
    
        
    // mud::Pipe
    {
        static Meta meta = { type<mud::Pipe>(), &namspc({ "mud" }), "Pipe", sizeof(mud::Pipe), TypeClass::Object };
        static Class cls = { type<mud::Pipe>(),
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
        
        
        
        
        meta_class<mud::Pipe>();
    }
    
    
        
    // mud::Process
    {
        static Meta meta = { type<mud::Process>(), &namspc({ "mud" }), "Process", sizeof(mud::Process), TypeClass::Object };
        static Class cls = { type<mud::Process>(),
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
                { type<mud::Process>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Process>(object).m_type); } }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Process>();
    }
    
    
        
    // mud::ScriptClass
    {
        static Meta meta = { type<mud::ScriptClass>(), &namspc({ "mud" }), "ScriptClass", sizeof(mud::ScriptClass), TypeClass::Object };
        static Class cls = { type<mud::ScriptClass>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ScriptClass>(), [](Ref ref, array<Var> args) { new(&val<mud::ScriptClass>(ref)) mud::ScriptClass( val<std::string>(args[0]), val<std::vector<mud::Type*>>(args[1]) ); }, { { "name", var(std::string()) }, { "parts", var(std::vector<mud::Type*>()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::ScriptClass>(), member_address(&mud::ScriptClass::m_type), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None, nullptr },
                //{ type<mud::ScriptClass>(), member_address(&mud::ScriptClass::m_class), type<mud::Class>(), "class", Ref(type<mud::Class>()), Member::None, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        //init_pool<mud::ScriptClass>(); 
        
        meta_class<mud::ScriptClass>();
    }
    
    
        
    // mud::StreamBranch
    {
        static Meta meta = { type<mud::StreamBranch>(), &namspc({ "mud" }), "StreamBranch", sizeof(mud::StreamBranch), TypeClass::Object };
        static Class cls = { type<mud::StreamBranch>(),
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
        
        
        
        
        meta_class<mud::StreamBranch>();
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    // mud::Valve
    {
        static Meta meta = { type<mud::Valve>(), &namspc({ "mud" }), "Valve", sizeof(mud::Valve), TypeClass::Object };
        static Class cls = { type<mud::Valve>(),
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
        
        
        
        
        meta_class<mud::Valve>();
    }
    
    
        
    // mud::Script
    {
        static Meta meta = { type<mud::Script>(), &namspc({ "mud" }), "Script", sizeof(mud::Script), TypeClass::Object };
        static Class cls = { type<mud::Script>(),
            // bases
            { &type<mud::Callable>() },
            { base_offset<mud::Script, mud::Callable>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Script>(), member_address(&mud::Script::m_index), type<uint32_t>(), "index", var(uint32_t()), Member::Value, nullptr },
                { type<mud::Script>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Script>(object).m_type); } },
                { type<mud::Script>(), member_address(&mud::Script::m_name), type<std::string>(), "name", var(std::string()), Member::Value, nullptr },
                { type<mud::Script>(), member_address(&mud::Script::m_locked), type<bool>(), "locked", var(bool()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Script>();
    }
    
    
        
    // mud::Stream
    {
        static Meta meta = { type<mud::Stream>(), &namspc({ "mud" }), "Stream", sizeof(mud::Stream), TypeClass::Object };
        static Class cls = { type<mud::Stream>(),
            // bases
            { &type<mud::StreamBranch>() },
            { base_offset<mud::Stream, mud::StreamBranch>() },
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
        
        
        
        
        meta_class<mud::Stream>();
    }
    
    
        
    // mud::LuaInterpreter
    {
        static Meta meta = { type<mud::LuaInterpreter>(), &namspc({ "mud" }), "LuaInterpreter", sizeof(mud::LuaInterpreter), TypeClass::Object };
        static Class cls = { type<mud::LuaInterpreter>(),
            // bases
            { &type<mud::Interpreter>() },
            { base_offset<mud::LuaInterpreter, mud::Interpreter>() },
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
        
        
        
        
        meta_class<mud::LuaInterpreter>();
    }
    
    
        
    // mud::WrenInterpreter
    {
        static Meta meta = { type<mud::WrenInterpreter>(), &namspc({ "mud" }), "WrenInterpreter", sizeof(mud::WrenInterpreter), TypeClass::Object };
        static Class cls = { type<mud::WrenInterpreter>(),
            // bases
            { &type<mud::Interpreter>() },
            { base_offset<mud::WrenInterpreter, mud::Interpreter>() },
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
        
        
        
        
        meta_class<mud::WrenInterpreter>();
    }
    
    
        
    // mud::TextScript
    {
        static Meta meta = { type<mud::TextScript>(), &namspc({ "mud" }), "TextScript", sizeof(mud::TextScript), TypeClass::Object };
        static Class cls = { type<mud::TextScript>(),
            // bases
            { &type<mud::Script>() },
            { base_offset<mud::TextScript, mud::Script>() },
            // constructors
            {
                { type<mud::TextScript>(), [](Ref ref, array<Var> args) { new(&val<mud::TextScript>(ref)) mud::TextScript( val<cstring>(args[0]), val<mud::Language>(args[1]), val<mud::Signature>(args[2]) ); }, { { "name", var(cstring()) }, { "language", var(mud::Language()) }, { "signature", Ref(type<mud::Signature>()), Param::Default } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::TextScript>(), member_address(&mud::TextScript::m_language), type<mud::Language>(), "language", var(mud::Language()), Member::Value, nullptr },
                { type<mud::TextScript>(), member_address(&mud::TextScript::m_script), type<std::string>(), "script", var(std::string()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        init_pool<mud::TextScript>(); 
        
        meta_class<mud::TextScript>();
    }
    
    
        
    // mud::VisualScript
    {
        static Meta meta = { type<mud::VisualScript>(), &namspc({ "mud" }), "VisualScript", sizeof(mud::VisualScript), TypeClass::Object };
        static Class cls = { type<mud::VisualScript>(),
            // bases
            { &type<mud::Script>() },
            { base_offset<mud::VisualScript, mud::Script>() },
            // constructors
            {
                { type<mud::VisualScript>(), [](Ref ref, array<Var> args) { new(&val<mud::VisualScript>(ref)) mud::VisualScript( val<cstring>(args[0]), val<mud::Signature>(args[1]) ); }, { { "name", var(cstring()) }, { "signature", Ref(type<mud::Signature>()), Param::Default } } }
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
        
        
        init_pool<mud::VisualScript>(); 
        
        meta_class<mud::VisualScript>();
    }
    
    
        
    // mud::ProcessFunction
    {
        static Meta meta = { type<mud::ProcessFunction>(), &namspc({ "mud" }), "ProcessFunction", sizeof(mud::ProcessFunction), TypeClass::Object };
        static Class cls = { type<mud::ProcessFunction>(),
            // bases
            { &type<mud::ProcessCallable>() },
            { base_offset<mud::ProcessFunction, mud::ProcessCallable>() },
            // constructors
            {
                { type<mud::ProcessFunction>(), [](Ref ref, array<Var> args) { new(&val<mud::ProcessFunction>(ref)) mud::ProcessFunction( val<mud::VisualScript>(args[0]), val<mud::Function>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "function", Ref(type<mud::Function>()) } } }
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
        
        
        init_pool<mud::ProcessFunction>(); 
        
        meta_class<mud::ProcessFunction>();
    }
    
    
        
    // mud::ProcessMethod
    {
        static Meta meta = { type<mud::ProcessMethod>(), &namspc({ "mud" }), "ProcessMethod", sizeof(mud::ProcessMethod), TypeClass::Object };
        static Class cls = { type<mud::ProcessMethod>(),
            // bases
            { &type<mud::ProcessCallable>() },
            { base_offset<mud::ProcessMethod, mud::ProcessCallable>() },
            // constructors
            {
                { type<mud::ProcessMethod>(), [](Ref ref, array<Var> args) { new(&val<mud::ProcessMethod>(ref)) mud::ProcessMethod( val<mud::VisualScript>(args[0]), val<mud::Method>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "method", Ref(type<mud::Method>()) } } }
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
        
        
        init_pool<mud::ProcessMethod>(); 
        
        meta_class<mud::ProcessMethod>();
    }
    
    
        
    // mud::ProcessScript
    {
        static Meta meta = { type<mud::ProcessScript>(), &namspc({ "mud" }), "ProcessScript", sizeof(mud::ProcessScript), TypeClass::Object };
        static Class cls = { type<mud::ProcessScript>(),
            // bases
            { &type<mud::ProcessCallable>() },
            { base_offset<mud::ProcessScript, mud::ProcessCallable>() },
            // constructors
            {
                { type<mud::ProcessScript>(), [](Ref ref, array<Var> args) { new(&val<mud::ProcessScript>(ref)) mud::ProcessScript( val<mud::VisualScript>(args[0]), val<mud::VisualScript>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "target", Ref(type<mud::VisualScript>()) } } }
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
        
        
        init_pool<mud::ProcessScript>(); 
        
        meta_class<mud::ProcessScript>();
    }
    
    
        
    // mud::ProcessCallable
    {
        static Meta meta = { type<mud::ProcessCallable>(), &namspc({ "mud" }), "ProcessCallable", sizeof(mud::ProcessCallable), TypeClass::Object };
        static Class cls = { type<mud::ProcessCallable>(),
            // bases
            { &type<mud::Process>() },
            { base_offset<mud::ProcessCallable, mud::Process>() },
            // constructors
            {
                { type<mud::ProcessCallable>(), [](Ref ref, array<Var> args) { new(&val<mud::ProcessCallable>(ref)) mud::ProcessCallable( val<mud::VisualScript>(args[0]), val<mud::Callable>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "callable", Ref(type<mud::Callable>()) } } }
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
        
        
        init_pool<mud::ProcessCallable>(); 
        
        meta_class<mud::ProcessCallable>();
    }
    
    
        
    // mud::ProcessCreate
    {
        static Meta meta = { type<mud::ProcessCreate>(), &namspc({ "mud" }), "ProcessCreate", sizeof(mud::ProcessCreate), TypeClass::Object };
        static Class cls = { type<mud::ProcessCreate>(),
            // bases
            { &type<mud::Process>() },
            { base_offset<mud::ProcessCreate, mud::Process>() },
            // constructors
            {
                { type<mud::ProcessCreate>(), [](Ref ref, array<Var> args) { new(&val<mud::ProcessCreate>(ref)) mud::ProcessCreate( val<mud::VisualScript>(args[0]), val<mud::Type>(args[1]), val<mud::Constructor>(args[2]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "type", Ref(type<mud::Type>()) }, { "constructor", Ref(type<mud::Constructor>()) } } }
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
        
        
        init_pool<mud::ProcessCreate>(); 
        
        meta_class<mud::ProcessCreate>();
    }
    
    
        
    // mud::ProcessDisplay
    {
        static Meta meta = { type<mud::ProcessDisplay>(), &namspc({ "mud" }), "ProcessDisplay", sizeof(mud::ProcessDisplay), TypeClass::Object };
        static Class cls = { type<mud::ProcessDisplay>(),
            // bases
            { &type<mud::Process>() },
            { base_offset<mud::ProcessDisplay, mud::Process>() },
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
        
        
        
        
        meta_class<mud::ProcessDisplay>();
    }
    
    
        
    // mud::ProcessGetMember
    {
        static Meta meta = { type<mud::ProcessGetMember>(), &namspc({ "mud" }), "ProcessGetMember", sizeof(mud::ProcessGetMember), TypeClass::Object };
        static Class cls = { type<mud::ProcessGetMember>(),
            // bases
            { &type<mud::Process>() },
            { base_offset<mud::ProcessGetMember, mud::Process>() },
            // constructors
            {
                { type<mud::ProcessGetMember>(), [](Ref ref, array<Var> args) { new(&val<mud::ProcessGetMember>(ref)) mud::ProcessGetMember( val<mud::VisualScript>(args[0]), val<mud::Member>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "member", Ref(type<mud::Member>()) } } }
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
        
        
        init_pool<mud::ProcessGetMember>(); 
        
        meta_class<mud::ProcessGetMember>();
    }
    
    
        
    // mud::ProcessSetMember
    {
        static Meta meta = { type<mud::ProcessSetMember>(), &namspc({ "mud" }), "ProcessSetMember", sizeof(mud::ProcessSetMember), TypeClass::Object };
        static Class cls = { type<mud::ProcessSetMember>(),
            // bases
            { &type<mud::Process>() },
            { base_offset<mud::ProcessSetMember, mud::Process>() },
            // constructors
            {
                { type<mud::ProcessSetMember>(), [](Ref ref, array<Var> args) { new(&val<mud::ProcessSetMember>(ref)) mud::ProcessSetMember( val<mud::VisualScript>(args[0]), val<mud::Member>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "member", Ref(type<mud::Member>()) } } }
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
        
        
        init_pool<mud::ProcessSetMember>(); 
        
        meta_class<mud::ProcessSetMember>();
    }
    
    
        
    // mud::ProcessValue
    {
        static Meta meta = { type<mud::ProcessValue>(), &namspc({ "mud" }), "ProcessValue", sizeof(mud::ProcessValue), TypeClass::Object };
        static Class cls = { type<mud::ProcessValue>(),
            // bases
            { &type<mud::Process>() },
            { base_offset<mud::ProcessValue, mud::Process>() },
            // constructors
            {
                { type<mud::ProcessValue>(), [](Ref ref, array<Var> args) { new(&val<mud::ProcessValue>(ref)) mud::ProcessValue( val<mud::VisualScript>(args[0]), val<mud::Var>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "value", Ref(type<mud::Var>()) } } }
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
        
        
        init_pool<mud::ProcessValue>(); 
        
        meta_class<mud::ProcessValue>();
    }
    
    
        
    // mud::ProcessInput
    {
        static Meta meta = { type<mud::ProcessInput>(), &namspc({ "mud" }), "ProcessInput", sizeof(mud::ProcessInput), TypeClass::Object };
        static Class cls = { type<mud::ProcessInput>(),
            // bases
            { &type<mud::Process>(), &type<mud::Param>() },
            { base_offset<mud::ProcessInput, mud::Process>(), base_offset<mud::ProcessInput, mud::Param>() },
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
        
        
        
        
        meta_class<mud::ProcessInput>();
    }
    
    
        
    // mud::ProcessOutput
    {
        static Meta meta = { type<mud::ProcessOutput>(), &namspc({ "mud" }), "ProcessOutput", sizeof(mud::ProcessOutput), TypeClass::Object };
        static Class cls = { type<mud::ProcessOutput>(),
            // bases
            { &type<mud::Process>(), &type<mud::Param>() },
            { base_offset<mud::ProcessOutput, mud::Process>(), base_offset<mud::ProcessOutput, mud::Param>() },
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
        
        
        
        
        meta_class<mud::ProcessOutput>();
    }
    

    
        m.m_types.push_back(&type<mud::Interpreter>());
        m.m_types.push_back(&type<mud::Language>());
        m.m_types.push_back(&type<mud::Pipe>());
        m.m_types.push_back(&type<mud::Process>());
        m.m_types.push_back(&type<mud::ScriptClass>());
        m.m_types.push_back(&type<mud::StreamBranch>());
        m.m_types.push_back(&type<mud::Valve>());
        m.m_types.push_back(&type<mud::Script>());
        m.m_types.push_back(&type<mud::Stream>());
        m.m_types.push_back(&type<mud::LuaInterpreter>());
        m.m_types.push_back(&type<mud::WrenInterpreter>());
        m.m_types.push_back(&type<mud::TextScript>());
        m.m_types.push_back(&type<mud::VisualScript>());
        m.m_types.push_back(&type<mud::ProcessFunction>());
        m.m_types.push_back(&type<mud::ProcessMethod>());
        m.m_types.push_back(&type<mud::ProcessScript>());
        m.m_types.push_back(&type<mud::ProcessCallable>());
        m.m_types.push_back(&type<mud::ProcessCreate>());
        m.m_types.push_back(&type<mud::ProcessDisplay>());
        m.m_types.push_back(&type<mud::ProcessGetMember>());
        m.m_types.push_back(&type<mud::ProcessSetMember>());
        m.m_types.push_back(&type<mud::ProcessValue>());
        m.m_types.push_back(&type<mud::ProcessInput>());
        m.m_types.push_back(&type<mud::ProcessOutput>());
    
    }
}
