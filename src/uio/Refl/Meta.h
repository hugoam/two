

#pragma once

#ifndef MUD_MODULES
#include <uio/Refl/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void muduio_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::EditorHint>(), &namspc({ "mud" }), "EditorHint", sizeof(mud::EditorHint), TypeClass::Enum };
        static Enum enu = { type<mud::EditorHint>(),
            true,
            { "Table", "Rows", "Inline" },
            { 0, 1, 2 },
            { var(EditorHint::Table), var(EditorHint::Rows), var(EditorHint::Inline) }
        };
        meta_enum<mud::EditorHint>();
    }
    
    
    // Sequences
    
    
    
    
    
    
        
    // mud::ScriptEditor
    {
        static Meta meta = { type<mud::ScriptEditor>(), &namspc({ "mud" }), "ScriptEditor", sizeof(mud::ScriptEditor), TypeClass::Object };
        static Class cls = { type<mud::ScriptEditor>(),
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
        
        
        
        
        meta_class<mud::ScriptEditor>();
    }
    
    
    

    
        m.m_types.push_back(&type<mud::EditorHint>());
        m.m_types.push_back(&type<mud::ScriptEditor>());
    
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_inline(val<mud::Widget>(args[0]), args[1]); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
            static Function f = { &namspc({ "mud" }), "object_edit_inline", function_id<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_inline), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_rows(val<mud::Widget>(args[0]), args[1]); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
            static Function f = { &namspc({ "mud" }), "object_edit_rows", function_id<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_rows), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_columns(val<mud::Widget>(args[0]), args[1]); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
            static Function f = { &namspc({ "mud" }), "object_edit_columns", function_id<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_columns), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_table(val<mud::Widget>(args[0]), args[1]); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
            static Function f = { &namspc({ "mud" }), "object_edit_table", function_id<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_table), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_expandbox(val<mud::Widget>(args[0]), args[1]); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
            static Function f = { &namspc({ "mud" }), "object_edit_expandbox", function_id<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_expandbox), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit(val<mud::Widget>(args[0]), args[1], val<mud::EditorHint>(args[2])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable }, { "hint", var(mud::EditorHint()), Param::Default } };
            static Function f = { &namspc({ "mud" }), "object_edit", function_id<bool(*)(mud::Widget&, mud::Ref, mud::EditorHint)>(&mud::object_edit), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::inspector(val<mud::Widget>(args[0]), args[1]); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
            static Function f = { &namspc({ "mud" }), "inspector", function_id<bool(*)(mud::Widget&, mud::Ref)>(&mud::inspector), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::inspector(val<mud::Widget>(args[0])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud" }), "inspector", function_id<bool(*)(mud::Widget&)>(&mud::inspector), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::multi_inspector(val<mud::Widget>(args[0]), val<mud::Type>(args[1]), val<std::vector<mud::Var>>(args[2]), val<size_t>(args[3])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "type", Ref(type<mud::Type>()) }, { "objects", var(std::vector<mud::Var>()) }, { "selected", var(size_t()) } };
            static Function f = { &namspc({ "mud" }), "multi_inspector", function_id<void(*)(mud::Widget&, mud::Type&, std::vector<mud::Var>&, size_t&)>(&mud::multi_inspector), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::multi_object_edit(val<mud::Widget>(args[0]), val<mud::Type>(args[1]), val<std::vector<mud::Ref>>(args[2])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "type", Ref(type<mud::Type>()) }, { "objects", var(std::vector<mud::Ref>()) } };
            static Function f = { &namspc({ "mud" }), "multi_object_edit", function_id<void(*)(mud::Widget&, mud::Type&, std::vector<mud::Ref>)>(&mud::multi_object_edit), func, params, Var() };
            m.m_functions.push_back(&f);
        }
    }
}
