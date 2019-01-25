#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#include <meta/type/Module.h>
#include <meta/ecs/Module.h>
#include <meta/pool/Module.h>
#include <meta/refl/Module.h>
#include <meta/math/Module.h>
#include <meta/lang/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/uio/Convert.h>
#endif

#include <uio/Api.h>

namespace mud
{
	void mud_uio_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		static Meta meta = { type<mud::EditNestMode>(), &namspc({ "mud" }), "EditNestMode", sizeof(mud::EditNestMode), TypeClass::Enum };
		static Enum enu = { type<mud::EditNestMode>(),
			true,
			{ "Inline", "Modal", "Embed" },
			{ 0, 1, 2 },
			{ var(mud::EditNestMode::Inline), var(mud::EditNestMode::Modal), var(mud::EditNestMode::Embed) }
		};
		meta_enum<mud::EditNestMode>();
	}
	{
		static Meta meta = { type<mud::EditorHint>(), &namspc({ "mud" }), "EditorHint", sizeof(mud::EditorHint), TypeClass::Enum };
		static Enum enu = { type<mud::EditorHint>(),
			true,
			{ "Table", "Rows", "Inline" },
			{ 0, 1, 2 },
			{ var(mud::EditorHint::Table), var(mud::EditorHint::Rows), var(mud::EditorHint::Inline) }
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
		m.m_types.push_back(&type<mud::EditNestMode>());
		m.m_types.push_back(&type<mud::EditorHint>());
		m.m_types.push_back(&type<mud::ScriptEditor>());
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_inline(val<mud::Widget>(args[0]), args[1]); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
			static Function f = { &namspc({ "mud" }), "object_edit_inline", funcptr<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_inline), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_rows(val<mud::Widget>(args[0]), args[1]); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
			static Function f = { &namspc({ "mud" }), "object_edit_rows", funcptr<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_rows), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_columns(val<mud::Widget>(args[0]), args[1]); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
			static Function f = { &namspc({ "mud" }), "object_edit_columns", funcptr<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_columns), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_table(val<mud::Widget>(args[0]), args[1]); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
			static Function f = { &namspc({ "mud" }), "object_edit_table", funcptr<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_table), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit_expandbox(val<mud::Widget>(args[0]), args[1]); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
			static Function f = { &namspc({ "mud" }), "object_edit_expandbox", funcptr<bool(*)(mud::Widget&, mud::Ref)>(&mud::object_edit_expandbox), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::object_edit(val<mud::Widget>(args[0]), args[1], val<mud::EditorHint>(args[2])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable }, { "hint", var(mud::EditorHint::Table), Param::Default } };
			static Function f = { &namspc({ "mud" }), "object_edit", funcptr<bool(*)(mud::Widget&, mud::Ref, mud::EditorHint)>(&mud::object_edit), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::entity_edit(val<mud::Widget>(args[0]), val<mud::Entity>(args[1]), val<mud::EditorHint>(args[2])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "entity", var(mud::Entity()) }, { "hint", var(mud::EditorHint::Table), Param::Default } };
			static Function f = { &namspc({ "mud" }), "entity_edit", funcptr<bool(*)(mud::Widget&, mud::Entity, mud::EditorHint)>(&mud::entity_edit), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::inspector(val<mud::Widget>(args[0]), args[1]); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
			static Function f = { &namspc({ "mud" }), "inspector", funcptr<bool(*)(mud::Widget&, mud::Ref)>(&mud::inspector), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::inspector(val<mud::Widget>(args[0]), val<mud::Entity>(args[1])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "entity", var(mud::Entity()) } };
			static Function f = { &namspc({ "mud" }), "inspector", funcptr<bool(*)(mud::Widget&, mud::Entity)>(&mud::inspector), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::inspector(val<mud::Widget>(args[0])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud" }), "inspector", funcptr<bool(*)(mud::Widget&)>(&mud::inspector), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::multi_inspector(val<mud::Widget>(args[0]), val<mud::Type>(args[1]), val<vector<mud::Var>>(args[2]), val<size_t>(args[3])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "type", Ref(type<mud::Type>()) }, { "objects", var(vector<mud::Var>()) }, { "selected", var(size_t()) } };
			static Function f = { &namspc({ "mud" }), "multi_inspector", funcptr<void(*)(mud::Widget&, mud::Type&, vector<mud::Var>&, size_t&)>(&mud::multi_inspector), func, params, Var() };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::multi_object_edit(val<mud::Widget>(args[0]), val<mud::Type>(args[1]), val<vector<mud::Ref>>(args[2])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "type", Ref(type<mud::Type>()) }, { "objects", var(vector<mud::Ref>()) } };
			static Function f = { &namspc({ "mud" }), "multi_object_edit", funcptr<void(*)(mud::Widget&, mud::Type&, vector<mud::Ref>)>(&mud::multi_object_edit), func, params, Var() };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_uio::mud_uio()
		: Module("mud::uio", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_ecs::m(), &mud_pool::m(), &mud_refl::m(), &mud_math::m(), &mud_lang::m(), &mud_ctx::m(), &mud_ui::m() })
	{
		// setup reflection meta data
		mud_uio_meta(*this);
	}
}

#ifdef MUD_UIO_MODULE
extern "C"
Module& getModule()
{
		return mud_uio::m();
}
#endif
