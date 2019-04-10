#include <mud/tree.refl.h>
#include <mud/lang.refl.h>
#include <mud/uio.refl.h>
#include <mud/pool.refl.h>
#include <mud/ui.refl.h>
#include <mud/uio.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.refl.h>
#include <mud/ctx.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>
#include <mud/ecs.refl.h>


#ifdef MUD_MODULES
module mud.uio;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace mud;

void mud_EditNestMode__to_string(void* val, string& str) { str = g_enu[type<mud::EditNestMode>().m_id]->name(uint32_t((*static_cast<mud::EditNestMode*>(val)))); }
void mud_EditNestMode__to_value(const string& str, void* val) { (*static_cast<mud::EditNestMode*>(val)) = mud::EditNestMode(g_enu[type<mud::EditNestMode>().m_id]->value(str.c_str())); }
void mud_EditorHint__to_string(void* val, string& str) { str = g_enu[type<mud::EditorHint>().m_id]->name(uint32_t((*static_cast<mud::EditorHint*>(val)))); }
void mud_EditorHint__to_value(const string& str, void* val) { (*static_cast<mud::EditorHint*>(val)) = mud::EditorHint(g_enu[type<mud::EditorHint>().m_id]->value(str.c_str())); }
void mud_object_edit_inline_0(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::object_edit_inline(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_object_edit_rows_1(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::object_edit_rows(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_object_edit_columns_2(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::object_edit_columns(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_object_edit_table_3(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::object_edit_table(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_object_edit_expandbox_4(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::object_edit_expandbox(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_object_edit_5(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::object_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1]), *static_cast<mud::EditorHint*>(args[2])); }
void mud_entity_edit_6(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::entity_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Entity*>(args[1]), *static_cast<mud::EditorHint*>(args[2])); }
void mud_inspector_7(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::inspector(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_inspector_8(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::inspector(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Entity*>(args[1])); }
void mud_inspector_9(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::inspector(*static_cast<mud::Widget*>(args[0])); }
void mud_multi_inspector_10(span<void*> args, void*& result) { UNUSED(result);  mud::multi_inspector(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Type*>(args[1]), *static_cast<stl::vector<mud::Var>*>(args[2]), *static_cast<size_t*>(args[3])); }
void mud_multi_object_edit_11(span<void*> args, void*& result) { UNUSED(result);  mud::multi_object_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Type*>(args[1]), *static_cast<stl::vector<mud::Ref>*>(args[2])); }

namespace mud
{
	void mud_uio_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::EditNestMode>();
		static Meta meta = { t, &namspc({ "mud" }), "EditNestMode", sizeof(mud::EditNestMode), TypeClass::Enum };
		static cstring ids[] = { "Inline", "Modal", "Embed" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::EditNestMode vars[] = { mud::EditNestMode::Inline, mud::EditNestMode::Modal, mud::EditNestMode::Embed};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_EditNestMode__to_string,
		                           mud_EditNestMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::EditorHint>();
		static Meta meta = { t, &namspc({ "mud" }), "EditorHint", sizeof(mud::EditorHint), TypeClass::Enum };
		static cstring ids[] = { "Table", "Rows", "Inline" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::EditorHint vars[] = { mud::EditorHint::Table, mud::EditorHint::Rows, mud::EditorHint::Inline};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_EditorHint__to_string,
		                           mud_EditorHint__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// mud::ScriptEditor
	{
		Type& t = type<mud::ScriptEditor>();
		static Meta meta = { t, &namspc({ "mud" }), "ScriptEditor", sizeof(mud::ScriptEditor), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::EditNestMode>());
		m.m_types.push_back(&type<mud::EditorHint>());
		m.m_types.push_back(&type<mud::ScriptEditor>());
		{
			static Function f = { &namspc({ "mud" }), "object_edit_inline", nullptr, mud_object_edit_inline_0, { { "parent", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "object_edit_rows", nullptr, mud_object_edit_rows_1, { { "parent", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "object_edit_columns", nullptr, mud_object_edit_columns_2, { { "parent", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "object_edit_table", nullptr, mud_object_edit_table_3, { { "parent", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "object_edit_expandbox", nullptr, mud_object_edit_expandbox_4, { { "parent", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::EditorHint hint_default = mud::EditorHint::Table;
			static Function f = { &namspc({ "mud" }), "object_edit", nullptr, mud_object_edit_5, { { "parent", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable }, { "hint", type<mud::EditorHint>(), Param::Default, &hint_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::EditorHint hint_default = mud::EditorHint::Table;
			static Function f = { &namspc({ "mud" }), "entity_edit", nullptr, mud_entity_edit_6, { { "parent", type<mud::Widget>(),  }, { "entity", type<mud::Entity>(),  }, { "hint", type<mud::EditorHint>(), Param::Default, &hint_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "inspector", nullptr, mud_inspector_7, { { "parent", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "inspector", nullptr, mud_inspector_8, { { "parent", type<mud::Widget>(),  }, { "entity", type<mud::Entity>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "inspector", nullptr, mud_inspector_9, { { "parent", type<mud::Widget>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "multi_inspector", nullptr, mud_multi_inspector_10, { { "parent", type<mud::Widget>(),  }, { "type", type<mud::Type>(),  }, { "objects", type<stl::vector<mud::Var>>(),  }, { "selected", type<size_t>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "multi_object_edit", nullptr, mud_multi_object_edit_11, { { "parent", type<mud::Widget>(),  }, { "type", type<mud::Type>(),  }, { "objects", type<stl::vector<mud::Ref>>(),  } }, g_qvoid };
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
