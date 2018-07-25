

#pragma once

#ifndef MUD_MODULES
#include <meta/refl/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_refl_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::TypeClass>(), &namspc({ "mud" }), "TypeClass", sizeof(mud::TypeClass), TypeClass::Enum };
        static Enum enu = { type<mud::TypeClass>(),
            true,
            { "None", "Object", "Struct", "Complex", "Sequence", "BaseType", "Enum" },
            { 0, 1, 2, 3, 4, 5, 6 },
            { var(mud::TypeClass::None), var(mud::TypeClass::Object), var(mud::TypeClass::Struct), var(mud::TypeClass::Complex), var(mud::TypeClass::Sequence), var(mud::TypeClass::BaseType), var(mud::TypeClass::Enum) }
        };
        meta_enum<mud::TypeClass>();
    }
    
    
    // Sequences
    {
        static Meta meta = { type<std::vector<mud::Function*>>(), &namspc({}), "std::vector<mud::Function*>", sizeof(std::vector<mud::Function*>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Function*>>() };
        cls.m_content = &type<mud::Function>();
        meta_sequence<std::vector<mud::Function*>, mud::Function*>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::Module*>>(), &namspc({}), "std::vector<mud::Module*>", sizeof(std::vector<mud::Module*>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Module*>>() };
        cls.m_content = &type<mud::Module>();
        meta_sequence<std::vector<mud::Module*>, mud::Module*>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::Type*>>(), &namspc({}), "std::vector<mud::Type*>", sizeof(std::vector<mud::Type*>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Type*>>() };
        cls.m_content = &type<mud::Type>();
        meta_sequence<std::vector<mud::Type*>, mud::Type*>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::Var>>(), &namspc({}), "std::vector<mud::Var>", sizeof(std::vector<mud::Var>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Var>>() };
        cls.m_content = &type<mud::Var>();
        meta_sequence<std::vector<mud::Var>, mud::Var>();
    }
    
    
    
    
        
    // mud::Call
    {
        static Meta meta = { type<mud::Call>(), &namspc({ "mud" }), "Call", sizeof(mud::Call), TypeClass::Struct };
        static Class cls = { type<mud::Call>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Call>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Call>(ref)) mud::Call(  ); }, {} },
                { type<mud::Call>(), [](Ref ref, array<Var> args) { new(&val<mud::Call>(ref)) mud::Call( val<mud::Callable>(args[0]), val<std::vector<mud::Var>>(args[1]) ); }, { { "callable", Ref(type<mud::Callable>()) }, { "arguments", var(std::vector<mud::Var>()) } } }
            },
            // copy constructor
            {
                { type<mud::Call>(), [](Ref ref, Ref other) { new(&val<mud::Call>(ref)) mud::Call(val<mud::Call>(other)); } }
            },
            // members
            {
                { type<mud::Call>(), member_address(&mud::Call::m_arguments), type<std::vector<mud::Var>>(), "arguments", var(std::vector<mud::Var>()), Member::Value, nullptr },
                { type<mud::Call>(), member_address(&mud::Call::m_result), type<mud::Var>(), "result", Ref(type<mud::Var>()), Member::None, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Call>();
    }
    
    
        
    // mud::Callable
    {
        static Meta meta = { type<mud::Callable>(), &namspc({ "mud" }), "Callable", sizeof(mud::Callable), TypeClass::Object };
        static Class cls = { type<mud::Callable>(),
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
        
        
        
        
        meta_class<mud::Callable>();
    }
    
    
        
    // mud::Class
    {
        static Meta meta = { type<mud::Class>(), &namspc({ "mud" }), "Class", sizeof(mud::Class), TypeClass::Object };
        static Class cls = { type<mud::Class>(),
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
        
        
        
        
        meta_class<mud::Class>();
    }
    
    
        
    // mud::Convert
    {
        static Meta meta = { type<mud::Convert>(), &namspc({ "mud" }), "Convert", sizeof(mud::Convert), TypeClass::Object };
        static Class cls = { type<mud::Convert>(),
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
        
        
        
        
        meta_class<mud::Convert>();
    }
    
    
        
    // mud::Creator
    {
        static Meta meta = { type<mud::Creator>(), &namspc({ "mud" }), "Creator", sizeof(mud::Creator), TypeClass::Object };
        static Class cls = { type<mud::Creator>(),
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
                { type<mud::Creator>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Creator>(object).m_type); } },
                { type<mud::Creator>(), member_address(&mud::Creator::m_construct), type<bool>(), "construct", var(bool()), Member::Value, nullptr },
                { type<mud::Creator>(), member_address(&mud::Creator::m_prototype), type<mud::Type>(), "prototype", Ref(type<mud::Type>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Creator>(), member_address(&mud::Creator::injector), type<mud::Injector>(), "injector", Ref(type<mud::Injector>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Creator>(object).injector()); } }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Creator>();
    }
    
    
        
    // mud::Enum
    {
        static Meta meta = { type<mud::Enum>(), &namspc({ "mud" }), "Enum", sizeof(mud::Enum), TypeClass::Object };
        static Class cls = { type<mud::Enum>(),
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
        
        
        
        
        meta_class<mud::Enum>();
    }
    
    
    
        
    // mud::Member
    {
        static Meta meta = { type<mud::Member>(), &namspc({ "mud" }), "Member", sizeof(mud::Member), TypeClass::Object };
        static Class cls = { type<mud::Member>(),
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
        
        
        
        
        meta_class<mud::Member>();
    }
    
    
        
    // mud::Meta
    {
        static Meta meta = { type<mud::Meta>(), &namspc({ "mud" }), "Meta", sizeof(mud::Meta), TypeClass::Object };
        static Class cls = { type<mud::Meta>(),
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
        
        
        
        
        meta_class<mud::Meta>();
    }
    
    
        
    // mud::Module
    {
        static Meta meta = { type<mud::Module>(), &namspc({ "mud" }), "Module", sizeof(mud::Module), TypeClass::Object };
        static Class cls = { type<mud::Module>(),
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
                { type<mud::Module>(), member_address(&mud::Module::m_name), type<cstring>(), "name", var(cstring()), Member::Value, nullptr },
                { type<mud::Module>(), member_address(&mud::Module::m_types), type<std::vector<mud::Type*>>(), "types", var(std::vector<mud::Type*>()), Member::Value, nullptr },
                { type<mud::Module>(), member_address(&mud::Module::m_functions), type<std::vector<mud::Function*>>(), "functions", var(std::vector<mud::Function*>()), Member::Value, nullptr },
                { type<mud::Module>(), member_address(&mud::Module::m_path), type<cstring>(), "path", var(cstring()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Module>();
    }
    
    
        
    // mud::Namespace
    {
        static Meta meta = { type<mud::Namespace>(), &namspc({ "mud" }), "Namespace", sizeof(mud::Namespace), TypeClass::Object };
        static Class cls = { type<mud::Namespace>(),
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
        
        
        
        
        meta_class<mud::Namespace>();
    }
    
    
        
    // mud::Param
    {
        static Meta meta = { type<mud::Param>(), &namspc({ "mud" }), "Param", sizeof(mud::Param), TypeClass::Object };
        static Class cls = { type<mud::Param>(),
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
        
        
        
        
        meta_class<mud::Param>();
    }
    
    
    
        
    // mud::Signature
    {
        static Meta meta = { type<mud::Signature>(), &namspc({ "mud" }), "Signature", sizeof(mud::Signature), TypeClass::Object };
        static Class cls = { type<mud::Signature>(),
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
        
        
        
        
        meta_class<mud::Signature>();
    }
    
    
        
    // mud::Static
    {
        static Meta meta = { type<mud::Static>(), &namspc({ "mud" }), "Static", sizeof(mud::Static), TypeClass::Object };
        static Class cls = { type<mud::Static>(),
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
        
        
        
        
        meta_class<mud::Static>();
    }
    
    
        
    // mud::System
    {
        static Meta meta = { type<mud::System>(), &namspc({ "mud" }), "System", sizeof(mud::System), TypeClass::Object };
        static Class cls = { type<mud::System>(),
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
                { type<mud::System>(), member_address(&mud::System::m_modules), type<std::vector<mud::Module*>>(), "modules", var(std::vector<mud::Module*>()), Member::Value, nullptr },
                { type<mud::System>(), member_address(&mud::System::m_types), type<std::vector<mud::Type*>>(), "types", var(std::vector<mud::Type*>()), Member::Value, nullptr },
                { type<mud::System>(), member_address(&mud::System::m_functions), type<std::vector<mud::Function*>>(), "functions", var(std::vector<mud::Function*>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::System>();
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    // mud::Constructor
    {
        static Meta meta = { type<mud::Constructor>(), &namspc({ "mud" }), "Constructor", sizeof(mud::Constructor), TypeClass::Object };
        static Class cls = { type<mud::Constructor>(),
            // bases
            { &type<mud::Callable>() },
            { base_offset<mud::Constructor, mud::Callable>() },
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
        
        
        
        
        meta_class<mud::Constructor>();
    }
    
    
        
    // mud::CopyConstructor
    {
        static Meta meta = { type<mud::CopyConstructor>(), &namspc({ "mud" }), "CopyConstructor", sizeof(mud::CopyConstructor), TypeClass::Object };
        static Class cls = { type<mud::CopyConstructor>(),
            // bases
            { &type<mud::Callable>() },
            { base_offset<mud::CopyConstructor, mud::Callable>() },
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
        
        
        
        
        meta_class<mud::CopyConstructor>();
    }
    
    
        
    // mud::Destructor
    {
        static Meta meta = { type<mud::Destructor>(), &namspc({ "mud" }), "Destructor", sizeof(mud::Destructor), TypeClass::Object };
        static Class cls = { type<mud::Destructor>(),
            // bases
            { &type<mud::Callable>() },
            { base_offset<mud::Destructor, mud::Callable>() },
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
        
        
        
        
        meta_class<mud::Destructor>();
    }
    
    
        
    // mud::Function
    {
        static Meta meta = { type<mud::Function>(), &namspc({ "mud" }), "Function", sizeof(mud::Function), TypeClass::Object };
        static Class cls = { type<mud::Function>(),
            // bases
            { &type<mud::Callable>() },
            { base_offset<mud::Function, mud::Callable>() },
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
        
        
        
        
        meta_class<mud::Function>();
    }
    
    
        
    // mud::Method
    {
        static Meta meta = { type<mud::Method>(), &namspc({ "mud" }), "Method", sizeof(mud::Method), TypeClass::Object };
        static Class cls = { type<mud::Method>(),
            // bases
            { &type<mud::Callable>() },
            { base_offset<mud::Method, mud::Callable>() },
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
        
        
        
        
        meta_class<mud::Method>();
    }
    
    
        
    // mud::Injector
    {
        static Meta meta = { type<mud::Injector>(), &namspc({ "mud" }), "Injector", sizeof(mud::Injector), TypeClass::Object };
        static Class cls = { type<mud::Injector>(),
            // bases
            { &type<mud::Call>() },
            { base_offset<mud::Injector, mud::Call>() },
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
        
        
        
        
        meta_class<mud::Injector>();
    }
    

    
        m.m_types.push_back(&type<mud::Call>());
        m.m_types.push_back(&type<mud::Callable>());
        m.m_types.push_back(&type<mud::Class>());
        m.m_types.push_back(&type<mud::Convert>());
        m.m_types.push_back(&type<mud::Creator>());
        m.m_types.push_back(&type<mud::Enum>());
        m.m_types.push_back(&type<mud::Member>());
        m.m_types.push_back(&type<mud::Meta>());
        m.m_types.push_back(&type<mud::Module>());
        m.m_types.push_back(&type<mud::Namespace>());
        m.m_types.push_back(&type<mud::Param>());
        m.m_types.push_back(&type<mud::Signature>());
        m.m_types.push_back(&type<mud::Static>());
        m.m_types.push_back(&type<mud::System>());
        m.m_types.push_back(&type<mud::TypeClass>());
        m.m_types.push_back(&type<std::vector<mud::Function*>>());
        m.m_types.push_back(&type<std::vector<mud::Module*>>());
        m.m_types.push_back(&type<std::vector<mud::Type*>>());
        m.m_types.push_back(&type<std::vector<mud::Var>>());
        m.m_types.push_back(&type<mud::Constructor>());
        m.m_types.push_back(&type<mud::CopyConstructor>());
        m.m_types.push_back(&type<mud::Destructor>());
        m.m_types.push_back(&type<mud::Function>());
        m.m_types.push_back(&type<mud::Method>());
        m.m_types.push_back(&type<mud::Injector>());
    
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(args); result = Ref(&mud::system()); };
            std::vector<Param> params = {};
            static Function f = { &namspc({ "mud" }), "system", function_id<mud::System&(*)()>(&mud::system), func, params, Ref(type<mud::System>()) };
            m.m_functions.push_back(&f);
        }
    }
}
