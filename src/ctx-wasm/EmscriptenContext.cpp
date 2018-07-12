//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <ctx-wasm/EmscriptenContext.h>

#include <obj/Type.h>
//#include <ui/UiWindow.h>
#include <ctx/InputDevice.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <cassert>
#include <string>

namespace mud
{
	using string = std::string;

	MouseButtonCode convert_html5_mouse_button(unsigned short button)
	{
		if(button == 0) return LEFT_BUTTON;
		else if(button == 1) return MIDDLE_BUTTON;
		else if(button == 2) return RIGHT_BUTTON;
		return LEFT_BUTTON;
	}

	// https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
	KeyCode convert_html5_key(const string& string)
	{
		if(string == "Unidentified") return KC_UNASSIGNED;
		else if(string == "Quote") return KC_APOSTROPHE;
		else if(string == "Backquote") return KC_GRAVE;
		else if(string == "Comma") return KC_COMMA;
		else if(string == "Minus") return KC_MINUS;
		else if(string == "Period") return KC_PERIOD;
		else if(string == "Slash") return KC_SLASH;
		else if(string == "Space") return KC_SPACE;
		else if(string == "Enter") return KC_RETURN;
		else if(string == "Escape") return KC_ESCAPE;
		else if(string == "ShiftLeft") return KC_LSHIFT;
		else if(string == "ShiftRight") return KC_RSHIFT;
		else if(string == "ControlLeft") return KC_LCONTROL;
		else if(string == "ControlRight") return KC_RCONTROL;
		else if(string == "AltLeft") return KC_LMENU;
		else if(string == "AltRight") return KC_RMENU;
		else if(string == "MetaLeft") return KC_LWIN;
		else if(string == "MetaRight") return KC_RWIN;
		else if(string == "CapsLock") return KC_CAPITAL;
		else if(string == "Tab") return KC_TAB;
		else if(string == "Digit0") return KC_0;
		else if(string == "Digit1") return KC_1;
		else if(string == "Digit2") return KC_2;
		else if(string == "Digit3") return KC_3;
		else if(string == "Digit4") return KC_4;
		else if(string == "Digit5") return KC_5;
		else if(string == "Digit6") return KC_6;
		else if(string == "Digit7") return KC_7;
		else if(string == "Digit8") return KC_8;
		else if(string == "Digit9") return KC_9;
		else if(string == "Semicolon") return KC_SEMICOLON;
		else if(string == "Equal") return KC_EQUALS;
		else if(string == "KeyA") return KC_A;
		else if(string == "KeyB") return KC_B;
		else if(string == "KeyC") return KC_C;
		else if(string == "KeyD") return KC_D;
		else if(string == "KeyE") return KC_E;
		else if(string == "KeyF") return KC_F;
		else if(string == "KeyG") return KC_G;
		else if(string == "KeyH") return KC_H;
		else if(string == "KeyI") return KC_I;
		else if(string == "KeyJ") return KC_J;
		else if(string == "KeyK") return KC_K;
		else if(string == "KeyL") return KC_L;
		else if(string == "KeyM") return KC_M;
		else if(string == "KeyN") return KC_N;
		else if(string == "KeyO") return KC_O;
		else if(string == "KeyP") return KC_P;
		else if(string == "KeyQ") return KC_Q;
		else if(string == "KeyR") return KC_R;
		else if(string == "KeyS") return KC_S;
		else if(string == "KeyT") return KC_T;
		else if(string == "KeyU") return KC_U;
		else if(string == "KeyV") return KC_V;
		else if(string == "KeyW") return KC_W;
		else if(string == "KeyX") return KC_X;
		else if(string == "KeyY") return KC_Y;
		else if(string == "KeyZ") return KC_Z;
		else if(string == "BracketLeft") return KC_LBRACKET;
		else if(string == "BracketRight") return KC_RBRACKET;
		else if(string == "Backslash") return KC_BACKSLASH;
		else if(string == "Backspace") return KC_BACK;
		else if(string == "Insert") return KC_INSERT;
		else if(string == "Delete") return KC_DELETE;
		else if(string == "ArrowDown") return KC_DOWN;
		else if(string == "ArrowLeft") return KC_LEFT;
		else if(string == "ArrowRight") return KC_RIGHT;
		else if(string == "ArrowUp") return KC_UP;
		else if(string == "End") return KC_END;
		else if(string == "Home") return KC_HOME;
		else if(string == "PageUp") return KC_PGUP;
		else if(string == "PageDown") return KC_PGDOWN;
		else if(string == "ScrollLock") return KC_SCROLL;
		//else if(string == GLFW_KEY_NUM_LOCK) return KC_NUMLOCK;
		//else if(string == GLFW_KEY_PRINT_SCREEN:
		else if(string == "Pause") return KC_PAUSE;
		else if(string == "F1") return KC_F1;
		else if(string == "F2") return KC_F2;
		else if(string == "F3") return KC_F3;
		else if(string == "F4") return KC_F4;
		else if(string == "F5") return KC_F5;
		else if(string == "F6") return KC_F6;
		else if(string == "F7") return KC_F7;
		else if(string == "F8") return KC_F8;
		else if(string == "F9") return KC_F9;
		else if(string == "F10") return KC_F10;
		else if(string == "F11") return KC_F11;
		else if(string == "F12") return KC_F12;
		else if(string == "Numpad0") return KC_NUMPAD0;
		else if(string == "Numpad1") return KC_NUMPAD1;
		else if(string == "Numpad2") return KC_NUMPAD2;
		else if(string == "Numpad3") return KC_NUMPAD3;
		else if(string == "Numpad4") return KC_NUMPAD4;
		else if(string == "Numpad5") return KC_NUMPAD5;
		else if(string == "Numpad6") return KC_NUMPAD6;
		else if(string == "Numpad7") return KC_NUMPAD7;
		else if(string == "Numpad8") return KC_NUMPAD8;
		else if(string == "Numpad9") return KC_NUMPAD9;
		else if(string == "NumpadComma") return KC_NUMPADCOMMA;
		else if(string == "NumpadDivide") return KC_DIVIDE;
		else if(string == "NumpadMultiply") return KC_MULTIPLY;
		else if(string == "NumpadSubtract") return KC_SUBTRACT;
		else if(string == "NumpadAdd") return KC_ADD;
		else if(string == "NumpadEnter") return KC_NUMPADENTER;
		//else if(string == "NumpadEqual") return KC_NUMPADEQUAL;
		//Equal
		else return KC_UNASSIGNED;
	}


	EmContext::EmContext(RenderSystem& render_system, cstring name, int width, int height, bool full_screen)
		: Context(render_system, name, width, height, full_screen)
	{
#ifdef MUD_RENDERER_BGFX
		// bgfx creates the context itself
		double canvas_width, canvas_height;
		emscripten_get_element_css_size("canvas", &canvas_width, &canvas_height);
		emscripten_set_canvas_element_size("#canvas", int(canvas_width), int(canvas_height));

		m_width = int(canvas_width);
		m_height = int(canvas_height);
#else
		this->init_context();
#endif

		emscripten_set_resize_callback(0, this, true, [](int, const EmscriptenUiEvent* event, void* w) { static_cast<EmContext*>(w)->resize(); return EM_BOOL(true); });

		emscripten_set_mousemove_callback(0, this, true, [](int, const EmscriptenMouseEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_mouse_move(*event)); });

		emscripten_set_mousedown_callback(0, this, true, [](int, const EmscriptenMouseEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_mouse_down(*event)); });
		emscripten_set_mouseup_callback(0, this, true, [](int, const EmscriptenMouseEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_mouse_up(*event)); });

		emscripten_set_wheel_callback(0, this, true, [](int, const EmscriptenWheelEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_wheel(*event)); });

		emscripten_set_keydown_callback(0, this, true, [](int, const EmscriptenKeyboardEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_key_down(*event)); });
		emscripten_set_keyup_callback(0, this, true, [](int, const EmscriptenKeyboardEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_key_up(*event)); });
		emscripten_set_keypress_callback(0, this, true, [](int, const EmscriptenKeyboardEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_key_press(*event)); });

	}

	void EmContext::init_context()
	{
		EmscriptenWebGLContextAttributes attrs;
		emscripten_webgl_init_context_attributes(&attrs);
		attrs.depth = 1;
		attrs.stencil = 1;
		attrs.antialias = 1;
#ifdef MUD_WEBGL2
		attrs.majorVersion = 2;
#else
		attrs.majorVersion = 1;
#endif
		attrs.minorVersion = 0;
		attrs.enableExtensionsByDefault = 1;

		m_window = emscripten_webgl_create_context("canvas", &attrs);

		emscripten_set_canvas_element_size("#canvas", m_width, m_height);
		emscripten_webgl_make_context_current(m_window);
	}

	void EmContext::init_input(Mouse& mouse, Keyboard& keyboard)
	{
		m_mouse = &mouse;
		m_keyboard = &keyboard;
	}

	void EmContext::reset(uint16_t width, uint16_t height)
	{
		UNUSED(width); UNUSED(height);
	}

	bool EmContext::next_frame()
	{
		return true;
	}

	void EmContext::lock_mouse(bool locked)
	{

	}

	void EmContext::resize()
	{
		double width, height;
		emscripten_get_element_css_size("canvas", &width, &height);
		emscripten_set_canvas_element_size("#canvas", int(width), int(height));

		m_width = width;
		m_height = height;
	}

	bool EmContext::inject_mouse_move(const EmscriptenMouseEvent& mouseEvent)
	{
		vec2 size = { float(m_width), float(m_height) };
		m_cursor = max(vec2(0.f), min(size, vec2{ float(mouseEvent.canvasX), float(mouseEvent.canvasY) }));
		m_mouse->moved(m_cursor);
		return true;
	}

	bool EmContext::inject_mouse_down(const EmscriptenMouseEvent& mouseEvent)
	{
		m_mouse->m_buttons[convert_html5_mouse_button(mouseEvent.button)].pressed({ float(mouseEvent.canvasX), float(mouseEvent.canvasY) });
		return true;
	}

	bool EmContext::inject_mouse_up(const EmscriptenMouseEvent& mouseEvent)
	{
		m_mouse->m_buttons[convert_html5_mouse_button(mouseEvent.button)].released({ float(mouseEvent.canvasX), float(mouseEvent.canvasY) });
		return true;
	}

	bool EmContext::inject_key_down(const EmscriptenKeyboardEvent& keyEvent)
	{
		if(!keyEvent.repeat)
			m_keyboard->key_pressed(convert_html5_key(keyEvent.code), keyEvent.key[0]);
		return keyEvent.key[1] != 0; // can't consume if printable value aka key as length one (or we wouldn't receive key_press event)
	}

	bool EmContext::inject_key_up(const EmscriptenKeyboardEvent& keyEvent)
	{
		m_keyboard->key_released(convert_html5_key(keyEvent.code), keyEvent.key[0]);
		return true;
	}

	bool EmContext::inject_key_press(const EmscriptenKeyboardEvent& keyEvent)
	{
		m_keyboard->key_stroke(convert_html5_key(keyEvent.code), keyEvent.key[0]);
		if(keyEvent.key[1] == 0)
			m_keyboard->key_char(KC_UNASSIGNED, keyEvent.key[0]);
		return true;
	}

	bool EmContext::inject_wheel(const EmscriptenWheelEvent& wheelEvent)
	{
		m_mouse->wheeled(m_cursor, -wheelEvent.deltaY);
		return true;
	}
}
