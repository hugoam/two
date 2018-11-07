

#pragma once

#ifndef MUD_MODULES
#include <meta/type/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_type_meta(Module& m)
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
    
    // Sequences
    {
        static Meta meta = { type<std::vector<mud::Ref>>(), &namspc({}), "std::vector<mud::Ref>", sizeof(std::vector<mud::Ref>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Ref>>() };
        cls.m_content = &type<mud::Ref>();
        meta_sequence<std::vector<mud::Ref>, mud::Ref>();
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
                { type<mud::Index>(), "me", Ref(&mud::Index::me) }
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
                { type<mud::Indexer>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Indexer>(object).m_type); } },
                { type<mud::Indexer>(), member_address(&mud::Indexer::m_objects), type<std::vector<mud::Ref>>(), "objects", var(std::vector<mud::Ref>()), Member::Value, nullptr }
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
                { type<mud::Type>(), member_address(&mud::Type::m_id), type<mud::Id>(), "id", var(mud::Id()), Member::Value, nullptr },
                { type<mud::Type>(), member_address(&mud::Type::m_name), type<cstring>(), "name", var(cstring()), Member::Value, nullptr },
                { type<mud::Type>(), member_address(&mud::Type::m_base), type<mud::Type>(), "base", Ref(type<mud::Type>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
    

    
        m.m_types.push_back(&type<mud::Index>());
        m.m_types.push_back(&type<mud::Indexer>());
        m.m_types.push_back(&type<mud::Ref>());
        m.m_types.push_back(&type<mud::Type>());
        m.m_types.push_back(&type<mud::Var>());
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
        m.m_types.push_back(&type<std::vector<mud::Ref>>());
        m.m_types.push_back(&type<unsigned char>());
        m.m_types.push_back(&type<unsigned int>());
        m.m_types.push_back(&type<unsigned long>());
        m.m_types.push_back(&type<unsigned long long>());
        m.m_types.push_back(&type<unsigned short>());
        m.m_types.push_back(&type<void>());
    
        {
            auto func = [](array<Var> args, Var& result) {  result = mud::indexed(val<mud::Type>(args[0]), val<uint32_t>(args[1])); };
            std::vector<Param> params = { { "type", Ref(type<mud::Type>()) }, { "id", var(uint32_t()) } };
            static Function f = { &namspc({ "mud" }), "indexed", function_id<mud::Ref(*)(mud::Type&, uint32_t)>(&mud::indexed), func, params, Ref() };
            m.m_functions.push_back(&f);
        }
    }
}
