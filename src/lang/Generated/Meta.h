

#pragma once

#ifndef MUD_MODULES
#include <lang/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>
#endif

namespace mud
{
    template <> MUD_LANG_EXPORT Type& type<mud::Process::State>();
    
#ifdef MUD_LANG_REFLECTION_IMPL
    void lang_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    
    // Sequences
    
    
    
        
    // mud::LuaInterpreter
    {
        static Meta meta = { type<mud::LuaInterpreter>(), &namspc({ "mud" }), "LuaInterpreter", sizeof(mud::LuaInterpreter), TypeClass::Object };
        static Class cls = { type<mud::LuaInterpreter>(),
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
        
        
        
        
        meta_class<mud::LuaInterpreter>();
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
                { type<mud::Process>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None }
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
    
    
        
    // mud::ProcessFunction
    {
        static Meta meta = { type<mud::ProcessFunction>(), &namspc({ "mud" }), "ProcessFunction", sizeof(mud::ProcessFunction), TypeClass::Object };
        static Class cls = { type<mud::ProcessFunction>(),
            // bases
            { &type<mud::ProcessCallable>() },
            { base_offset<mud::ProcessFunction, mud::ProcessCallable>() },
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
                { type<mud::Script>(), member_address(&mud::Script::m_index), type<uint32_t>(), "index", var(uint32_t()), Member::Value },
                { type<mud::Script>(), member_address(&mud::Script::m_name), type<std::string>(), "name", var(std::string()), Member::Value },
                { type<mud::Script>(), member_address(&mud::Script::m_locked), type<bool>(), "locked", var(bool()), Member::Value }
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
    
    
        
    // mud::LuaScript
    {
        static Meta meta = { type<mud::LuaScript>(), &namspc({ "mud" }), "LuaScript", sizeof(mud::LuaScript), TypeClass::Object };
        static Class cls = { type<mud::LuaScript>(),
            // bases
            { &type<mud::Script>() },
            { base_offset<mud::LuaScript, mud::Script>() },
            // constructors
            {
                { type<mud::LuaScript>(), [](Ref ref, array<Var> args) { new(&val<mud::LuaScript>(ref)) mud::LuaScript( val<cstring>(args[0]), val<mud::Signature>(args[1]) ); }, { { "name", var(cstring()) }, { "signature", Ref(type<mud::Signature>()), Param::Default } } }
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
        
        
        init_pool<mud::LuaScript>(); 
        
        meta_class<mud::LuaScript>();
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
    

    
        m.m_types.push_back(&type<mud::LuaInterpreter>());
        m.m_types.push_back(&type<mud::Pipe>());
        m.m_types.push_back(&type<mud::Process>());
        m.m_types.push_back(&type<mud::StreamBranch>());
        m.m_types.push_back(&type<mud::Valve>());
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
        m.m_types.push_back(&type<mud::Script>());
        m.m_types.push_back(&type<mud::Stream>());
        m.m_types.push_back(&type<mud::LuaScript>());
        m.m_types.push_back(&type<mud::VisualScript>());
    
    }
#endif

}
