

#pragma once

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>
#endif

namespace mud
{
    template <> MUD_OBJ_EXPORT Type& type<mud::Param::Flags>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Member::Flags>();
    
#ifdef MUD_OBJ_REFLECTION_IMPL
    void obj_meta(Module& m)
    {   
    // Base Types
    {
        static Meta meta = { type<bool>(), &namspc({}), "bool", sizeof(bool), TypeClass::BaseType };
        meta_basetype<bool>();
    }
    
    {
        static Meta meta = { type<char>(), &namspc({}), "char", sizeof(char), TypeClass::BaseType };
        meta_basetype<char>();
    }
    
    {
        static Meta meta = { type<cstring>(), &namspc({}), "cstring", sizeof(cstring), TypeClass::BaseType };
        meta_basetype<cstring>();
    }
    
    {
        static Meta meta = { type<double>(), &namspc({}), "double", sizeof(double), TypeClass::BaseType };
        meta_basetype<double>();
    }
    
    {
        static Meta meta = { type<float>(), &namspc({}), "float", sizeof(float), TypeClass::BaseType };
        meta_basetype<float>();
    }
    
    {
        static Meta meta = { type<int>(), &namspc({}), "int", sizeof(int), TypeClass::BaseType };
        meta_basetype<int>();
    }
    
    {
        static Meta meta = { type<long>(), &namspc({}), "long", sizeof(long), TypeClass::BaseType };
        meta_basetype<long>();
    }
    
    {
        static Meta meta = { type<long long>(), &namspc({}), "long long", sizeof(long long), TypeClass::BaseType };
        meta_basetype<long long>();
    }
    
    {
        static Meta meta = { type<short>(), &namspc({}), "short", sizeof(short), TypeClass::BaseType };
        meta_basetype<short>();
    }
    
    {
        static Meta meta = { type<std::string>(), &namspc({}), "std::string", sizeof(std::string), TypeClass::BaseType };
        meta_basetype<std::string>();
    }
    
    {
        static Meta meta = { type<unsigned char>(), &namspc({}), "unsigned char", sizeof(unsigned char), TypeClass::BaseType };
        meta_basetype<unsigned char>();
    }
    
    {
        static Meta meta = { type<unsigned int>(), &namspc({}), "unsigned int", sizeof(unsigned int), TypeClass::BaseType };
        meta_basetype<unsigned int>();
    }
    
    {
        static Meta meta = { type<unsigned long>(), &namspc({}), "unsigned long", sizeof(unsigned long), TypeClass::BaseType };
        meta_basetype<unsigned long>();
    }
    
    {
        static Meta meta = { type<unsigned long long>(), &namspc({}), "unsigned long long", sizeof(unsigned long long), TypeClass::BaseType };
        meta_basetype<unsigned long long>();
    }
    
    {
        static Meta meta = { type<unsigned short>(), &namspc({}), "unsigned short", sizeof(unsigned short), TypeClass::BaseType };
        meta_basetype<unsigned short>();
    }
    
    {
        static Meta meta = { type<void>(), &namspc({}), "void", 0, TypeClass::BaseType };
        meta_basetype<void>();
    }
    
    
    // Enums
    {
        static Meta meta = { type<mud::TypeClass>(), &namspc({ "mud" }), "TypeClass", sizeof(mud::TypeClass), TypeClass::Enum };
        static Enum enu = { type<mud::TypeClass>(),
            true,
            { "None", "Object", "Struct", "Complex", "Sequence", "BaseType", "Enum" },
            { 0, 1, 2, 3, 4, 5, 6 },
            { var(TypeClass::None), var(TypeClass::Object), var(TypeClass::Struct), var(TypeClass::Complex), var(TypeClass::Sequence), var(TypeClass::BaseType), var(TypeClass::Enum) }
        };
        meta_enum<mud::TypeClass>();
    }
    
    {
        static Meta meta = { type<mud::TypeKind>(), &namspc({ "mud" }), "TypeKind", sizeof(mud::TypeKind), TypeClass::Enum };
        static Enum enu = { type<mud::TypeKind>(),
            true,
            { "Type", "Prototype" },
            { 0, 1 },
            { var(TypeKind::Type), var(TypeKind::Prototype) }
        };
        meta_enum<mud::TypeKind>();
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
        static Meta meta = { type<std::vector<mud::Prototype*>>(), &namspc({}), "std::vector<mud::Prototype*>", sizeof(std::vector<mud::Prototype*>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Prototype*>>() };
        cls.m_content = &type<mud::Prototype>();
        meta_sequence<std::vector<mud::Prototype*>, mud::Prototype*>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::Ref>>(), &namspc({}), "std::vector<mud::Ref>", sizeof(std::vector<mud::Ref>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Ref>>() };
        cls.m_content = &type<mud::Ref>();
        meta_sequence<std::vector<mud::Ref>, mud::Ref>();
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
                { type<mud::Call>(), member_address(&mud::Call::m_arguments), type<std::vector<mud::Var>>(), "arguments", var(std::vector<mud::Var>()), Member::Value },
                { type<mud::Call>(), member_address(&mud::Call::m_result), type<mud::Var>(), "result", Ref(type<mud::Var>()), Member::None }
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
    
    
    
        
    // mud::Complex
    {
        static Meta meta = { type<mud::Complex>(), &namspc({ "mud" }), "Complex", sizeof(mud::Complex), TypeClass::Object };
        static Class cls = { type<mud::Complex>(),
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
                { type<mud::Complex>(), member_address(&mud::Complex::m_id), type<mud::Id>(), "id", var(mud::Id()), Member::Value },
                { type<mud::Complex>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None },
                { type<mud::Complex>(), Address(), type<mud::Prototype>(), "prototype", Ref(type<mud::Prototype>()), Member::None }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Complex>();
    }
    
    
        
    // mud::Construct
    {
        static Meta meta = { type<mud::Construct>(), &namspc({ "mud" }), "Construct", sizeof(mud::Construct), TypeClass::Object };
        static Class cls = { type<mud::Construct>(),
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
                { type<mud::Construct>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Construct>();
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
                { type<mud::Creator>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None },
                { type<mud::Creator>(), member_address(&mud::Creator::m_construct), type<bool>(), "construct", var(bool()), Member::Value },
                { type<mud::Creator>(), member_address(&mud::Creator::m_prototype), type<mud::Type>(), "prototype", Ref(type<mud::Type>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Creator>(), member_address(&mud::Creator::injector), type<mud::Injector>(), "injector", Ref(type<mud::Injector>()), Member::None }
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
    
    
    
    
        
    // mud::Index
    {
        static Meta meta = { type<mud::Index>(), &namspc({ "mud" }), "Index", sizeof(mud::Index), TypeClass::Object };
        static Class cls = { type<mud::Index>(),
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
                { type<mud::Index>(), "indexer", member_address(&mud::Index::indexer), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::Index>(object).indexer(val<mud::Type>(args[0]))); }, { { "type", Ref(type<mud::Type>()) } }, Ref(type<mud::Indexer>()) }
            },
            // static members
            {
                { type<mud::Index>(), "instance", Ref(&mud::Index::instance) }
            }
        };
        
        
        
        
        meta_class<mud::Index>();
    }
    
    
        
    // mud::Indexer
    {
        static Meta meta = { type<mud::Indexer>(), &namspc({ "mud" }), "Indexer", sizeof(mud::Indexer), TypeClass::Object };
        static Class cls = { type<mud::Indexer>(),
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
                { type<mud::Indexer>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None },
                { type<mud::Indexer>(), member_address(&mud::Indexer::m_objects), type<std::vector<mud::Ref>>(), "objects", var(std::vector<mud::Ref>()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Indexer>();
    }
    
    
        
    // mud::Injector
    {
        static Meta meta = { type<mud::Injector>(), &namspc({ "mud" }), "Injector", sizeof(mud::Injector), TypeClass::Object };
        static Class cls = { type<mud::Injector>(),
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
                { type<mud::Injector>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None }
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
                { type<mud::Module>(), member_address(&mud::Module::m_name), type<cstring>(), "name", var(cstring()), Member::Value },
                { type<mud::Module>(), member_address(&mud::Module::m_types), type<std::vector<mud::Type*>>(), "types", var(std::vector<mud::Type*>()), Member::Value },
                { type<mud::Module>(), member_address(&mud::Module::m_functions), type<std::vector<mud::Function*>>(), "functions", var(std::vector<mud::Function*>()), Member::Value },
                { type<mud::Module>(), member_address(&mud::Module::m_path), type<cstring>(), "path", var(cstring()), Member::Value }
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
    
    
    
    
        
    // mud::None
    {
        static Meta meta = { type<mud::None>(), &namspc({ "mud" }), "None", sizeof(mud::None), TypeClass::Object };
        static Class cls = { type<mud::None>(),
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
        
        
        
        
        meta_class<mud::None>();
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
    
    
    
        
    // mud::Ref
    {
        static Meta meta = { type<mud::Ref>(), &namspc({ "mud" }), "Ref", sizeof(mud::Ref), TypeClass::Object };
        static Class cls = { type<mud::Ref>(),
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
        
        
        
        
        meta_class<mud::Ref>();
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
                { type<mud::System>(), member_address(&mud::System::m_modules), type<std::vector<mud::Module*>>(), "modules", var(std::vector<mud::Module*>()), Member::Value },
                { type<mud::System>(), member_address(&mud::System::m_types), type<std::vector<mud::Type*>>(), "types", var(std::vector<mud::Type*>()), Member::Value },
                { type<mud::System>(), member_address(&mud::System::m_prototypes), type<std::vector<mud::Prototype*>>(), "prototypes", var(std::vector<mud::Prototype*>()), Member::Value },
                { type<mud::System>(), member_address(&mud::System::m_functions), type<std::vector<mud::Function*>>(), "functions", var(std::vector<mud::Function*>()), Member::Value }
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
    
    
        
    // mud::Time
    {
        static Meta meta = { type<mud::Time>(), &namspc({ "mud" }), "Time", sizeof(mud::Time), TypeClass::Struct };
        static Class cls = { type<mud::Time>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Time>(), [](Ref ref, array<Var> args) { new(&val<mud::Time>(ref)) mud::Time( val<double>(args[0]) ); }, { { "value", var(double()) } } }
            },
            // copy constructor
            {
                { type<mud::Time>(), [](Ref ref, Ref other) { new(&val<mud::Time>(ref)) mud::Time(val<mud::Time>(other)); } }
            },
            // members
            {
                { type<mud::Time>(), member_address(&mud::Time::m_value), type<double>(), "value", var(double()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Time>();
    }
    
    
        
    // mud::TimeSpan
    {
        static Meta meta = { type<mud::TimeSpan>(), &namspc({ "mud" }), "TimeSpan", sizeof(mud::TimeSpan), TypeClass::Struct };
        static Class cls = { type<mud::TimeSpan>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::TimeSpan>(), [](Ref ref, array<Var> args) { new(&val<mud::TimeSpan>(ref)) mud::TimeSpan( val<mud::Time>(args[0]), val<mud::Time>(args[1]) ); }, { { "s", var(mud::Time()) }, { "e", var(mud::Time()) } } }
            },
            // copy constructor
            {
                { type<mud::TimeSpan>(), [](Ref ref, Ref other) { new(&val<mud::TimeSpan>(ref)) mud::TimeSpan(val<mud::TimeSpan>(other)); } }
            },
            // members
            {
                { type<mud::TimeSpan>(), member_address(&mud::TimeSpan::start), type<mud::Time>(), "start", var(mud::Time()), Member::Value },
                { type<mud::TimeSpan>(), member_address(&mud::TimeSpan::end), type<mud::Time>(), "end", var(mud::Time()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::TimeSpan>();
    }
    
    
        
    // mud::Type
    {
        static Meta meta = { type<mud::Type>(), &namspc({ "mud" }), "Type", sizeof(mud::Type), TypeClass::Object };
        static Class cls = { type<mud::Type>(),
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
                { type<mud::Type>(), member_address(&mud::Type::m_id), type<mud::Id>(), "id", var(mud::Id()), Member::Value },
                { type<mud::Type>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None },
                { type<mud::Type>(), member_address(&mud::Type::m_kind), type<mud::TypeKind>(), "kind", var(mud::TypeKind()), Member::Value },
                { type<mud::Type>(), member_address(&mud::Type::m_name), type<cstring>(), "name", var(cstring()), Member::Value },
                { type<mud::Type>(), member_address(&mud::Type::m_base), type<mud::Type>(), "base", Ref(type<mud::Type>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Type>(), member_address(&mud::Type::m_meta), type<mud::Meta>(), "meta", Ref(type<mud::Meta>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Type>(), member_address(&mud::Type::m_class), type<mud::Class>(), "class", Ref(type<mud::Class>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Type>(), member_address(&mud::Type::m_enum), type<mud::Enum>(), "enum", Ref(type<mud::Enum>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Type>(), member_address(&mud::Type::m_convert), type<mud::Convert>(), "convert", Ref(type<mud::Convert>()), Member::Flags(Member::Pointer|Member::Link) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Type>();
    }
    
    
    
    
    
        
    // mud::Var
    {
        static Meta meta = { type<mud::Var>(), &namspc({ "mud" }), "Var", sizeof(mud::Var), TypeClass::Object };
        static Class cls = { type<mud::Var>(),
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
        
        
        
        
        meta_class<mud::Var>();
    }
    
    
        
    // mud::array<float>
    {
        static Meta meta = { type<mud::array<float>>(), &namspc({ "mud" }), "array<float>", sizeof(mud::array<float>), TypeClass::Struct };
        static Class cls = { type<mud::array<float>>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::array<float>>(), [](Ref ref, Ref other) { new(&val<mud::array<float>>(ref)) mud::array<float>(val<mud::array<float>>(other)); } }
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
        
        
        
        
        meta_class<mud::array<float>>();
    }
    
    
        
    // mud::array<mud::cstring>
    {
        static Meta meta = { type<mud::array<mud::cstring>>(), &namspc({ "mud" }), "array<mud::cstring>", sizeof(mud::array<mud::cstring>), TypeClass::Struct };
        static Class cls = { type<mud::array<mud::cstring>>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::array<mud::cstring>>(), [](Ref ref, Ref other) { new(&val<mud::array<mud::cstring>>(ref)) mud::array<mud::cstring>(val<mud::array<mud::cstring>>(other)); } }
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
        
        
        
        
        meta_class<mud::array<mud::cstring>>();
    }
    
    
        
    // mud::strung
    {
        static Meta meta = { type<mud::strung>(), &namspc({ "mud" }), "strung", sizeof(mud::strung), TypeClass::Struct };
        static Class cls = { type<mud::strung>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::strung>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::strung>(ref)) mud::strung(  ); }, {} },
                { type<mud::strung>(), [](Ref ref, array<Var> args) { new(&val<mud::strung>(ref)) mud::strung( val<cstring>(args[0]) ); }, { { "str", var(cstring()) } } }
            },
            // copy constructor
            {
                { type<mud::strung>(), [](Ref ref, Ref other) { new(&val<mud::strung>(ref)) mud::strung(val<mud::strung>(other)); } }
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
        
        
        
        
        meta_class<mud::strung>();
    }
    
    
    
        
    // mud::Prototype
    {
        static Meta meta = { type<mud::Prototype>(), &namspc({ "mud" }), "Prototype", sizeof(mud::Prototype), TypeClass::Object };
        static Class cls = { type<mud::Prototype>(),
            // bases
            { &type<mud::Type>() },
            { base_offset<mud::Prototype, mud::Type>() },
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
        
        
        
        
        meta_class<mud::Prototype>();
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
    

    
        m.m_types.push_back(&type<mud::Call>());
        m.m_types.push_back(&type<mud::Callable>());
        m.m_types.push_back(&type<mud::Class>());
        m.m_types.push_back(&type<mud::Complex>());
        m.m_types.push_back(&type<mud::Construct>());
        m.m_types.push_back(&type<mud::Convert>());
        m.m_types.push_back(&type<mud::Creator>());
        m.m_types.push_back(&type<mud::Enum>());
        m.m_types.push_back(&type<mud::Index>());
        m.m_types.push_back(&type<mud::Indexer>());
        m.m_types.push_back(&type<mud::Injector>());
        m.m_types.push_back(&type<mud::Member>());
        m.m_types.push_back(&type<mud::Meta>());
        m.m_types.push_back(&type<mud::Module>());
        m.m_types.push_back(&type<mud::Namespace>());
        m.m_types.push_back(&type<mud::None>());
        m.m_types.push_back(&type<mud::Param>());
        m.m_types.push_back(&type<mud::Pool>());
        m.m_types.push_back(&type<mud::Ref>());
        m.m_types.push_back(&type<mud::Signature>());
        m.m_types.push_back(&type<mud::Static>());
        m.m_types.push_back(&type<mud::System>());
        m.m_types.push_back(&type<mud::Time>());
        m.m_types.push_back(&type<mud::TimeSpan>());
        m.m_types.push_back(&type<mud::Type>());
        m.m_types.push_back(&type<mud::TypeClass>());
        m.m_types.push_back(&type<mud::TypeKind>());
        m.m_types.push_back(&type<mud::Var>());
        m.m_types.push_back(&type<mud::array<float>>());
        m.m_types.push_back(&type<mud::array<mud::cstring>>());
        m.m_types.push_back(&type<bool>());
        m.m_types.push_back(&type<char>());
        m.m_types.push_back(&type<cstring>());
        m.m_types.push_back(&type<double>());
        m.m_types.push_back(&type<float>());
        m.m_types.push_back(&type<int>());
        m.m_types.push_back(&type<long>());
        m.m_types.push_back(&type<long long>());
        m.m_types.push_back(&type<short>());
        m.m_types.push_back(&type<std::string>());
        m.m_types.push_back(&type<std::vector<mud::Function*>>());
        m.m_types.push_back(&type<std::vector<mud::Module*>>());
        m.m_types.push_back(&type<std::vector<mud::Prototype*>>());
        m.m_types.push_back(&type<std::vector<mud::Ref>>());
        m.m_types.push_back(&type<std::vector<mud::Type*>>());
        m.m_types.push_back(&type<std::vector<mud::Var>>());
        m.m_types.push_back(&type<mud::strung>());
        m.m_types.push_back(&type<unsigned char>());
        m.m_types.push_back(&type<unsigned int>());
        m.m_types.push_back(&type<unsigned long>());
        m.m_types.push_back(&type<unsigned long long>());
        m.m_types.push_back(&type<unsigned short>());
        m.m_types.push_back(&type<void>());
        m.m_types.push_back(&type<mud::Prototype>());
        m.m_types.push_back(&type<mud::Constructor>());
        m.m_types.push_back(&type<mud::CopyConstructor>());
        m.m_types.push_back(&type<mud::Destructor>());
        m.m_types.push_back(&type<mud::Function>());
        m.m_types.push_back(&type<mud::Method>());
    
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(args); result = Ref(&mud::system()); };
            std::vector<Param> params = {};
            static Function f = { &namspc({ "mud" }), "system", function_id<mud::System&(*)()>(&mud::system), func, params, Ref(type<mud::System>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = mud::indexed(val<mud::Type>(args[0]), val<uint32_t>(args[1])); };
            std::vector<Param> params = { { "type", Ref(type<mud::Type>()) }, { "id", var(uint32_t()) } };
            static Function f = { &namspc({ "mud" }), "indexed", function_id<mud::Ref(*)(mud::Type&, uint32_t)>(&mud::indexed), func, params, Ref() };
            m.m_functions.push_back(&f);
        }
    }
#endif

}
