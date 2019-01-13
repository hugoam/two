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
	void DECL mud_ScriptEditor__destroy(mud::ScriptEditor* self) {
		delete self;
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


