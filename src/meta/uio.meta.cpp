#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.uio;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/tree.meta.h>
#include <meta/type.meta.h>
#include <meta/ecs.meta.h>
#include <meta/pool.meta.h>
#include <meta/refl.meta.h>
#include <meta/math.meta.h>
#include <meta/lang.meta.h>
#include <meta/ctx.meta.h>
#include <meta/ui.meta.h>
#include <meta/uio.meta.h>
#include <meta/uio.conv.h>
#endif

#include <uio/Api.h>

using namespace two;

void two_EditNestMode__to_string(void* val, string& str) { str = g_enu[type<two::EditNestMode>().m_id]->name(uint32_t((*static_cast<two::EditNestMode*>(val)))); }
void two_EditNestMode__to_value(const string& str, void* val) { (*static_cast<two::EditNestMode*>(val)) = two::EditNestMode(g_enu[type<two::EditNestMode>().m_id]->value(str.c_str())); }
void two_EditorHint__to_string(void* val, string& str) { str = g_enu[type<two::EditorHint>().m_id]->name(uint32_t((*static_cast<two::EditorHint*>(val)))); }
void two_EditorHint__to_value(const string& str, void* val) { (*static_cast<two::EditorHint*>(val)) = two::EditorHint(g_enu[type<two::EditorHint>().m_id]->value(str.c_str())); }
void two_object_edit_inline_0(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::object_edit_inline(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1])); }
void two_object_edit_rows_1(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::object_edit_rows(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1])); }
void two_object_edit_columns_2(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::object_edit_columns(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1])); }
void two_object_edit_table_3(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::object_edit_table(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1])); }
void two_object_edit_expandbox_4(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::object_edit_expandbox(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1])); }
void two_object_edit_5(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::object_edit(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1]), *static_cast<two::EditorHint*>(args[2])); }
void two_entity_edit_6(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::entity_edit(*static_cast<two::Widget*>(args[0]), *static_cast<two::Entity*>(args[1]), *static_cast<two::EditorHint*>(args[2])); }
void two_inspector_7(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::inspector(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1])); }
void two_inspector_8(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::inspector(*static_cast<two::Widget*>(args[0]), *static_cast<two::Entity*>(args[1])); }
void two_inspector_9(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::inspector(*static_cast<two::Widget*>(args[0])); }
void two_multi_inspector_10(span<void*> args, void*& result) { UNUSED(result);  two::multi_inspector(*static_cast<two::Widget*>(args[0]), *static_cast<two::Type*>(args[1]), *static_cast<stl::vector<two::Var>*>(args[2]), *static_cast<size_t*>(args[3])); }
void two_multi_object_edit_11(span<void*> args, void*& result) { UNUSED(result);  two::multi_object_edit(*static_cast<two::Widget*>(args[0]), *static_cast<two::Type*>(args[1]), *static_cast<stl::vector<two::Ref>*>(args[2])); }

namespace two
{
	void two_uio_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::EditNestMode>();
		static Meta meta = { t, &namspc({ "two" }), "EditNestMode", sizeof(two::EditNestMode), TypeClass::Enum };
		static cstring ids[] = { "Inline", "Modal", "Embed" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::EditNestMode vars[] = { two::EditNestMode::Inline, two::EditNestMode::Modal, two::EditNestMode::Embed};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_EditNestMode__to_string,
		                           two_EditNestMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::EditorHint>();
		static Meta meta = { t, &namspc({ "two" }), "EditorHint", sizeof(two::EditorHint), TypeClass::Enum };
		static cstring ids[] = { "Table", "Rows", "Inline" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::EditorHint vars[] = { two::EditorHint::Table, two::EditorHint::Rows, two::EditorHint::Inline};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_EditorHint__to_string,
		                           two_EditorHint__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// two::ScriptEditor
	{
		Type& t = type<two::ScriptEditor>();
		static Meta meta = { t, &namspc({ "two" }), "ScriptEditor", sizeof(two::ScriptEditor), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::EditNestMode>());
		m.m_types.push_back(&type<two::EditorHint>());
		m.m_types.push_back(&type<two::ScriptEditor>());
		{
			static Function f = { &namspc({ "two" }), "object_edit_inline", funcptr<bool(*)(two::Widget&, two::Ref)>(two::object_edit_inline), two_object_edit_inline_0, { { "parent", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "object_edit_rows", funcptr<bool(*)(two::Widget&, two::Ref)>(two::object_edit_rows), two_object_edit_rows_1, { { "parent", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "object_edit_columns", funcptr<bool(*)(two::Widget&, two::Ref)>(two::object_edit_columns), two_object_edit_columns_2, { { "parent", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "object_edit_table", funcptr<bool(*)(two::Widget&, two::Ref)>(two::object_edit_table), two_object_edit_table_3, { { "parent", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "object_edit_expandbox", funcptr<bool(*)(two::Widget&, two::Ref)>(two::object_edit_expandbox), two_object_edit_expandbox_4, { { "parent", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::EditorHint hint_default = two::EditorHint::Table;
			static Function f = { &namspc({ "two" }), "object_edit", funcptr<bool(*)(two::Widget&, two::Ref, two::EditorHint)>(two::object_edit), two_object_edit_5, { { "parent", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable }, { "hint", type<two::EditorHint>(), Param::Default, &hint_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::EditorHint hint_default = two::EditorHint::Table;
			static Function f = { &namspc({ "two" }), "entity_edit", funcptr<bool(*)(two::Widget&, two::Entity, two::EditorHint)>(two::entity_edit), two_entity_edit_6, { { "parent", type<two::Widget>(),  }, { "entity", type<two::Entity>(),  }, { "hint", type<two::EditorHint>(), Param::Default, &hint_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "inspector", funcptr<bool(*)(two::Widget&, two::Ref)>(two::inspector), two_inspector_7, { { "parent", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "inspector", funcptr<bool(*)(two::Widget&, two::Entity)>(two::inspector), two_inspector_8, { { "parent", type<two::Widget>(),  }, { "entity", type<two::Entity>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "inspector", funcptr<bool(*)(two::Widget&)>(two::inspector), two_inspector_9, { { "parent", type<two::Widget>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "multi_inspector", funcptr<void(*)(two::Widget&, two::Type&, stl::vector<two::Var>&, size_t&)>(two::multi_inspector), two_multi_inspector_10, { { "parent", type<two::Widget>(),  }, { "type", type<two::Type>(),  }, { "objects", type<stl::vector<two::Var>>(),  }, { "selected", type<size_t>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "multi_object_edit", funcptr<void(*)(two::Widget&, two::Type&, stl::vector<two::Ref>)>(two::multi_object_edit), two_multi_object_edit_11, { { "parent", type<two::Widget>(),  }, { "type", type<two::Type>(),  }, { "objects", type<stl::vector<two::Ref>>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_uio::two_uio()
		: Module("two::uio", { &two_infra::m(), &two_tree::m(), &two_type::m(), &two_ecs::m(), &two_pool::m(), &two_refl::m(), &two_math::m(), &two_lang::m(), &two_ctx::m(), &two_ui::m() })
	{
		// setup reflection meta data
		two_uio_meta(*this);
	}
}

#ifdef TWO_UIO_MODULE
extern "C"
Module& getModule()
{
	return two_uio::m();
}
#endif
