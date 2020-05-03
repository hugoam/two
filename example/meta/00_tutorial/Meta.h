

#pragma once

#ifndef MUD_MODULES
#include <meta/00_tutorial/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void _00_tutorial_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<ShapeType>(), &namspc({}), "ShapeType", sizeof(ShapeType), TypeClass::Enum };
        static Enum enu = { type<ShapeType>(),
            true,
            { "Circle", "Sphere", "Cube" },
            { 0, 1, 2 },
            { var(ShapeType::Circle), var(ShapeType::Sphere), var(ShapeType::Cube) }
        };
        meta_enum<ShapeType>();
    }
    
    
    // Sequences
    
    
    
        
    // MyObject
    {
        static Meta meta = { type<MyObject>(), &namspc({}), "MyObject", sizeof(MyObject), TypeClass::Object };
        static Class cls = { type<MyObject>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<MyObject>(), [](Ref ref, array<Var> args) { new(&val<MyObject>(ref)) MyObject( val<ShapeType>(args[0]), val<two::Colour>(args[1]) ); }, { { "shape", var(ShapeType()) }, { "colour", var(two::Colour()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<MyObject>(), member_address(&MyObject::m_visible), type<bool>(), "visible", var(bool(true)), Member::Value, nullptr },
                { type<MyObject>(), member_address(&MyObject::m_number), type<int>(), "number", var(int(0)), Member::Value, nullptr },
                { type<MyObject>(), member_address(&MyObject::m_name), type<std::string>(), "name", var(std::string()), Member::Value, nullptr },
                { type<MyObject>(), member_address(&MyObject::m_shape), type<ShapeType>(), "shape", var(ShapeType()), Member::Value, nullptr },
                { type<MyObject>(), member_address(&MyObject::m_position), type<two::vec3>(), "position", var(two::vec3()), Member::Value, nullptr },
                { type<MyObject>(), member_address(&MyObject::m_colour), type<two::Colour>(), "colour", var(two::Colour()), Member::Value, nullptr },
                { type<MyObject>(), member_address(&MyObject::m_floats), type<std::vector<float>>(), "floats", var(std::vector<float>()), Member::Value, nullptr }
            },
            // methods
            {
                { type<MyObject>(), "method", member_address(&MyObject::method), [](Ref object, array<Var> args, Var& result) { UNUSED(args);val<int>(result) = val<MyObject>(object).method(); }, {}, var(int()) }
            },
            // static members
            {
            }
        };
        
        
        init_pool<MyObject>(); 
        
        meta_class<MyObject>();
    }
    
    

    
        m.m_types.push_back(&type<MyObject>());
        m.m_types.push_back(&type<ShapeType>());
    
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  ::foo(val<int>(args[0])); };
            std::vector<Param> params = { { "arg", var(int()) } };
            static Function f = { &namspc({}), "foo", function_id<void(*)(int)>(&::foo), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  ::bar(val<MyObject>(args[0])); };
            std::vector<Param> params = { { "object", Ref(type<MyObject>()) } };
            static Function f = { &namspc({}), "bar", function_id<void(*)(MyObject&)>(&::bar), func, params, Var() };
            m.m_functions.push_back(&f);
        }
    }
}
