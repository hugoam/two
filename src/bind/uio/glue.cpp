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
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// ScriptEditor
	void EMSCRIPTEN_KEEPALIVE mud_ScriptEditor___destroy__(mud::ScriptEditor* self) {
		delete self;
	}
	// EditNestMode
	mud::EditNestMode EMSCRIPTEN_KEEPALIVE mud_EditNestMode_Inline() {
		return mud::EditNestMode::Inline;
	}
	mud::EditNestMode EMSCRIPTEN_KEEPALIVE mud_EditNestMode_Modal() {
		return mud::EditNestMode::Modal;
	}
	mud::EditNestMode EMSCRIPTEN_KEEPALIVE mud_EditNestMode_Embed() {
		return mud::EditNestMode::Embed;
	}
	// EditorHint
	mud::EditorHint EMSCRIPTEN_KEEPALIVE mud_EditorHint_Table() {
		return mud::EditorHint::Table;
	}
	mud::EditorHint EMSCRIPTEN_KEEPALIVE mud_EditorHint_Rows() {
		return mud::EditorHint::Rows;
	}
	mud::EditorHint EMSCRIPTEN_KEEPALIVE mud_EditorHint_Inline() {
		return mud::EditorHint::Inline;
	}
	
}


