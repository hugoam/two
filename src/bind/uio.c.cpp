#include <infra/Api.h>
#include <tree/Api.h>
#include <type/Api.h>
#include <ecs/Api.h>
#include <pool/Api.h>
#include <refl/Api.h>
#include <math/Api.h>
#include <lang/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>
#include <uio/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// ScriptEditor
	two::Type* DECL two_ScriptEditor__type() {
		return &two::type<two::ScriptEditor>();
	}
	void DECL two_ScriptEditor__destroy(two::ScriptEditor* self) {
		delete self;
	}
	bool DECL two_object_edit_inline_2(two::Widget* parent, void* object, two::Type* object_type) {
		return two::object_edit_inline(*parent, { object, *object_type });
	}
	bool DECL two_object_edit_rows_2(two::Widget* parent, void* object, two::Type* object_type) {
		return two::object_edit_rows(*parent, { object, *object_type });
	}
	bool DECL two_object_edit_columns_2(two::Widget* parent, void* object, two::Type* object_type) {
		return two::object_edit_columns(*parent, { object, *object_type });
	}
	bool DECL two_object_edit_table_2(two::Widget* parent, void* object, two::Type* object_type) {
		return two::object_edit_table(*parent, { object, *object_type });
	}
	bool DECL two_object_edit_expandbox_2(two::Widget* parent, void* object, two::Type* object_type) {
		return two::object_edit_expandbox(*parent, { object, *object_type });
	}
	bool DECL two_object_edit_2(two::Widget* parent, void* object, two::Type* object_type) {
		return two::object_edit(*parent, { object, *object_type });
	}
	bool DECL two_object_edit_3(two::Widget* parent, void* object, two::Type* object_type, two::EditorHint hint) {
		return two::object_edit(*parent, { object, *object_type }, hint);
	}
	bool DECL two_entity_edit_2(two::Widget* parent, two::Entity* entity) {
		return two::entity_edit(*parent, *entity);
	}
	bool DECL two_entity_edit_3(two::Widget* parent, two::Entity* entity, two::EditorHint hint) {
		return two::entity_edit(*parent, *entity, hint);
	}
	bool DECL two_inspector_1(two::Widget* parent) {
		return two::inspector(*parent);
	}
	bool DECL two_inspector_2(two::Widget* parent, void* object, two::Type* object_type) {
		return two::inspector(*parent, { object, *object_type });
	}
	// EditNestMode
	two::EditNestMode DECL two_EditNestMode_Inline() {
		return two::EditNestMode::Inline;
	}
	two::EditNestMode DECL two_EditNestMode_Modal() {
		return two::EditNestMode::Modal;
	}
	two::EditNestMode DECL two_EditNestMode_Embed() {
		return two::EditNestMode::Embed;
	}
	// EditorHint
	two::EditorHint DECL two_EditorHint_Table() {
		return two::EditorHint::Table;
	}
	two::EditorHint DECL two_EditorHint_Rows() {
		return two::EditorHint::Rows;
	}
	two::EditorHint DECL two_EditorHint_Inline() {
		return two::EditorHint::Inline;
	}
	
}


