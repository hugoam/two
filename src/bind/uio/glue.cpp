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


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// ScriptEditor
	void EMSCRIPTEN_KEEPALIVE ScriptEditor___destroy__(mud::ScriptEditor* self) {
		delete self;
	}
	// EditNestMode
	mud::EditNestMode EMSCRIPTEN_KEEPALIVE EditNestMode_Inline() {
		return mud::EditNestMode::Inline;
	}
	mud::EditNestMode EMSCRIPTEN_KEEPALIVE EditNestMode_Modal() {
		return mud::EditNestMode::Modal;
	}
	mud::EditNestMode EMSCRIPTEN_KEEPALIVE EditNestMode_Embed() {
		return mud::EditNestMode::Embed;
	}
	// EditorHint
	mud::EditorHint EMSCRIPTEN_KEEPALIVE EditorHint_Table() {
		return mud::EditorHint::Table;
	}
	mud::EditorHint EMSCRIPTEN_KEEPALIVE EditorHint_Rows() {
		return mud::EditorHint::Rows;
	}
	mud::EditorHint EMSCRIPTEN_KEEPALIVE EditorHint_Inline() {
		return mud::EditorHint::Inline;
	}
	
}


