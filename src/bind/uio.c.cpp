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

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// ScriptEditor
	mud::Type* DECL mud_ScriptEditor__type() {
		return &mud::type<mud::ScriptEditor>();
	}
	void DECL mud_ScriptEditor__destroy(mud::ScriptEditor* self) {
		delete self;
	}
	bool DECL mud_object_edit_inline_2(mud::Widget* parent, void* object, mud::Type* object_type) {
		return mud::object_edit_inline(*parent, { object, *object_type });
	}
	bool DECL mud_object_edit_rows_2(mud::Widget* parent, void* object, mud::Type* object_type) {
		return mud::object_edit_rows(*parent, { object, *object_type });
	}
	bool DECL mud_object_edit_columns_2(mud::Widget* parent, void* object, mud::Type* object_type) {
		return mud::object_edit_columns(*parent, { object, *object_type });
	}
	bool DECL mud_object_edit_table_2(mud::Widget* parent, void* object, mud::Type* object_type) {
		return mud::object_edit_table(*parent, { object, *object_type });
	}
	bool DECL mud_object_edit_expandbox_2(mud::Widget* parent, void* object, mud::Type* object_type) {
		return mud::object_edit_expandbox(*parent, { object, *object_type });
	}
	bool DECL mud_object_edit_2(mud::Widget* parent, void* object, mud::Type* object_type) {
		return mud::object_edit(*parent, { object, *object_type });
	}
	bool DECL mud_object_edit_3(mud::Widget* parent, void* object, mud::Type* object_type, mud::EditorHint hint) {
		return mud::object_edit(*parent, { object, *object_type }, hint);
	}
	bool DECL mud_entity_edit_2(mud::Widget* parent, mud::Entity* entity) {
		return mud::entity_edit(*parent, *entity);
	}
	bool DECL mud_entity_edit_3(mud::Widget* parent, mud::Entity* entity, mud::EditorHint hint) {
		return mud::entity_edit(*parent, *entity, hint);
	}
	bool DECL mud_inspector_1(mud::Widget* parent) {
		return mud::inspector(*parent);
	}
	bool DECL mud_inspector_2(mud::Widget* parent, void* object, mud::Type* object_type) {
		return mud::inspector(*parent, { object, *object_type });
	}
	// EditNestMode
	mud::EditNestMode DECL mud_EditNestMode_Inline() {
		return mud::EditNestMode::Inline;
	}
	mud::EditNestMode DECL mud_EditNestMode_Modal() {
		return mud::EditNestMode::Modal;
	}
	mud::EditNestMode DECL mud_EditNestMode_Embed() {
		return mud::EditNestMode::Embed;
	}
	// EditorHint
	mud::EditorHint DECL mud_EditorHint_Table() {
		return mud::EditorHint::Table;
	}
	mud::EditorHint DECL mud_EditorHint_Rows() {
		return mud::EditorHint::Rows;
	}
	mud::EditorHint DECL mud_EditorHint_Inline() {
		return mud::EditorHint::Inline;
	}
	
}


