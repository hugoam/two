#include <two/ctx.wasm.h>
#include <two/math.h>
#include <two/ctx.h>
#include <two/type.h>



//#include <ui/UiWindow.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <cassert>
#include <cstdio>

#include <stl/string.h>

namespace two
{
	using string = string;

	static void log_error(EMSCRIPTEN_RESULT result)
	{
		string message;
		if(result == EMSCRIPTEN_RESULT_DEFERRED)
			message = "The requested operation cannot be completed now for web security reasons, and has been deferred for completion in the next event handler.";
		else if(result == EMSCRIPTEN_RESULT_NOT_SUPPORTED)
			message = "The given operation is not supported by this browser or the target element.This value will be returned at the time the callback is registered if the operation is not supported.";
		else if(result == EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED)
			message = "The requested operation could not be completed now for web security reasons.It failed because the user requested the operation not be deferred.";
		else if(result == EMSCRIPTEN_RESULT_INVALID_TARGET)
			message = "The operation failed because the specified target element is invalid.";
		else if(result == EMSCRIPTEN_RESULT_UNKNOWN_TARGET)
			message = "The operation failed because the specified target element was not found.";
		else if(result == EMSCRIPTEN_RESULT_INVALID_PARAM)
			message = "The operation failed because an invalid parameter was passed to the function.";
		else if(result == EMSCRIPTEN_RESULT_FAILED)
			message = "Generic failure result message, returned if no specific result is available.";
		else if(result == EMSCRIPTEN_RESULT_NO_DATA)
			message = "The operation failed because no data is currently available.";

		printf("[ERROR] html5 - %s\n", message.c_str());
	}

	MouseButtonCode convert_html5_mouse_button(unsigned short button)
	{
		if(button == 0) return LEFT_BUTTON;
		else if(button == 1) return MIDDLE_BUTTON;
		else if(button == 2) return RIGHT_BUTTON;
		return LEFT_BUTTON;
	}

	// https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
	Key convert_html5_key(const string& string)
	{
		if(string == "Unidentified") return Key::Unassigned;
		else if(string == "Quote") return Key::Apostrophe;
		else if(string == "Backquote") return Key::Grave;
		else if(string == "Comma") return Key::Comma;
		else if(string == "Minus") return Key::Minus;
		else if(string == "Period") return Key::Period;
		else if(string == "Slash") return Key::Slash;
		else if(string == "Space") return Key::Space;
		else if(string == "Enter") return Key::Return;
		else if(string == "Escape") return Key::Escape;
		else if(string == "ShiftLeft") return Key::LeftShift;
		else if(string == "ShiftRight") return Key::RightShift;
		else if(string == "ControlLeft") return Key::LeftControl;
		else if(string == "ControlRight") return Key::RightControl;
		else if(string == "AltLeft") return Key::LeftAlt;
		else if(string == "AltRight") return Key::RightAlt;
		else if(string == "MetaLeft") return Key::LeftWin;
		else if(string == "MetaRight") return Key::RightWin;
		else if(string == "CapsLock") return Key::Capital;
		else if(string == "Tab") return Key::Tab;
		else if(string == "Digit0") return Key::Num0;
		else if(string == "Digit1") return Key::Num1;
		else if(string == "Digit2") return Key::Num2;
		else if(string == "Digit3") return Key::Num3;
		else if(string == "Digit4") return Key::Num4;
		else if(string == "Digit5") return Key::Num5;
		else if(string == "Digit6") return Key::Num6;
		else if(string == "Digit7") return Key::Num7;
		else if(string == "Digit8") return Key::Num8;
		else if(string == "Digit9") return Key::Num9;
		else if(string == "Semicolon") return Key::Semicolon;
		else if(string == "Equal") return Key::Equals;
		else if(string == "KeyA") return Key::A;
		else if(string == "KeyB") return Key::B;
		else if(string == "KeyC") return Key::C;
		else if(string == "KeyD") return Key::D;
		else if(string == "KeyE") return Key::E;
		else if(string == "KeyF") return Key::F;
		else if(string == "KeyG") return Key::G;
		else if(string == "KeyH") return Key::H;
		else if(string == "KeyI") return Key::I;
		else if(string == "KeyJ") return Key::J;
		else if(string == "KeyK") return Key::K;
		else if(string == "KeyL") return Key::L;
		else if(string == "KeyM") return Key::M;
		else if(string == "KeyN") return Key::N;
		else if(string == "KeyO") return Key::O;
		else if(string == "KeyP") return Key::P;
		else if(string == "KeyQ") return Key::Q;
		else if(string == "KeyR") return Key::R;
		else if(string == "KeyS") return Key::S;
		else if(string == "KeyT") return Key::T;
		else if(string == "KeyU") return Key::U;
		else if(string == "KeyV") return Key::V;
		else if(string == "KeyW") return Key::W;
		else if(string == "KeyX") return Key::X;
		else if(string == "KeyY") return Key::Y;
		else if(string == "KeyZ") return Key::Z;
		else if(string == "BracketLeft") return Key::LeftBracket;
		else if(string == "BracketRight") return Key::RightBracket;
		else if(string == "Backslash") return Key::Backslash;
		else if(string == "Backspace") return Key::Back;
		else if(string == "Insert") return Key::Insert;
		else if(string == "Delete") return Key::Delete;
		else if(string == "ArrowDown") return Key::Down;
		else if(string == "ArrowLeft") return Key::Left;
		else if(string == "ArrowRight") return Key::Right;
		else if(string == "ArrowUp") return Key::Up;
		else if(string == "End") return Key::End;
		else if(string == "Home") return Key::Home;
		else if(string == "PageUp") return Key::PageUp;
		else if(string == "PageDown") return Key::PageDown;
		else if(string == "ScrollLock") return Key::ScrollLock;
		//else if(string == GLFW_KEY_NUM_LOCK) return Key::NumLock;
		//else if(string == GLFW_KEY_PRINT_SCREEN:
		else if(string == "Pause") return Key::Pause;
		else if(string == "F1") return Key::F1;
		else if(string == "F2") return Key::F2;
		else if(string == "F3") return Key::F3;
		else if(string == "F4") return Key::F4;
		else if(string == "F5") return Key::F5;
		else if(string == "F6") return Key::F6;
		else if(string == "F7") return Key::F7;
		else if(string == "F8") return Key::F8;
		else if(string == "F9") return Key::F9;
		else if(string == "F10") return Key::F10;
		else if(string == "F11") return Key::F11;
		else if(string == "F12") return Key::F12;
		else if(string == "Numpad0") return Key::Numpad0;
		else if(string == "Numpad1") return Key::Numpad1;
		else if(string == "Numpad2") return Key::Numpad2;
		else if(string == "Numpad3") return Key::Numpad3;
		else if(string == "Numpad4") return Key::Numpad4;
		else if(string == "Numpad5") return Key::Numpad5;
		else if(string == "Numpad6") return Key::Numpad6;
		else if(string == "Numpad7") return Key::Numpad7;
		else if(string == "Numpad8") return Key::Numpad8;
		else if(string == "Numpad9") return Key::Numpad9;
		else if(string == "NumpadComma") return Key::NumpadComma;
		else if(string == "NumpadDivide") return Key::Divide;
		else if(string == "NumpadMultiply") return Key::Multiply;
		else if(string == "NumpadSubtract") return Key::Subtract;
		else if(string == "NumpadAdd") return Key::Add;
		else if(string == "NumpadEnter") return Key::NumpadEnter;
		//else if(string == "NumpadEqual") return Key::NUMPADEQUAL;
		//Equal
		else return Key::Unassigned;
	}

	Key translate_html5_key(const string& string, char c)
	{
		if(c == 'a' || c == 'A') return translate(Key::A);
		if(c == 'z' || c == 'Z') return translate(Key::Z);
		if(c == 'q' || c == 'Q') return translate(Key::Q);
		if(c == 'w' || c == 'W') return translate(Key::W);
		else return translate(convert_html5_key(string));
	}

	EmContext::EmContext(RenderSystem& render_system, const string& name, uvec2 size, bool fullscreen, bool main)
		: Context(render_system, name, size, fullscreen)
	{
#ifdef TWO_RENDERER_BGFX
		const bool create = !main;
#else
		const bool create = false;
#endif
		if(!create)
		{
			// bgfx creates the context itself
			double canvas_width, canvas_height;
			emscripten_get_element_css_size("#canvas", &canvas_width, &canvas_height);
			emscripten_set_canvas_element_size("#canvas", int(canvas_width), int(canvas_height));

			m_size = { uint(canvas_width), uint(canvas_height) };
			m_fb_size = m_size;
		}
		else
		{
			m_native_handle = (void*)m_title.c_str();
			//this->create_context(name);
		}

		emscripten_set_resize_callback(0, this, true, [](int, const EmscriptenUiEvent* event, void* w) { UNUSED(event); static_cast<EmContext*>(w)->resize(); return EM_BOOL(true); });

		emscripten_set_mousemove_callback("#canvas", this, true, [](int, const EmscriptenMouseEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_mouse_move(*event)); });

		emscripten_set_mousedown_callback("#canvas", this, true, [](int, const EmscriptenMouseEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_mouse_down(*event)); });
		emscripten_set_mouseup_callback("#canvas", this, true, [](int, const EmscriptenMouseEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_mouse_up(*event)); });

		emscripten_set_wheel_callback("#canvas", this, true, [](int, const EmscriptenWheelEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_wheel(*event)); });

#ifdef KEYS_INPUT_CANVAS_ONLY
		const char* keys_target = "#canvas";
#else
		const char* keys_target = nullptr;
#endif
		emscripten_set_keydown_callback(keys_target, this, true, [](int, const EmscriptenKeyboardEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_key_down(*event)); });
		emscripten_set_keyup_callback(keys_target, this, true, [](int, const EmscriptenKeyboardEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_key_up(*event)); });
		emscripten_set_keypress_callback(keys_target, this, true, [](int, const EmscriptenKeyboardEvent* event, void* w) { return EM_BOOL(static_cast<EmContext*>(w)->inject_key_press(*event)); });

	}

	void EmContext::create_context(const string& name)
	{
		EmscriptenWebGLContextAttributes attrs;
		emscripten_webgl_init_context_attributes(&attrs);
		attrs.depth = 1;
		attrs.stencil = 1;
		attrs.antialias = 1;
#ifdef TWO_WEBGL2
		attrs.majorVersion = 2;
#else
		attrs.majorVersion = 1;
#endif
		attrs.minorVersion = 0;
		attrs.enableExtensionsByDefault = 1;

		const string id = name;//"#" + name;
		
		printf("[debug] create webgl context on canvas %s\n", id.c_str());
		auto context = emscripten_webgl_create_context(id.c_str(), &attrs);
		if(context == 0 || context < 0)
		{
			log_error((EMSCRIPTEN_RESULT)context);
			return;
		}

		m_window = context;

		emscripten_set_canvas_element_size(id.c_str(), m_size.x, m_size.y);
		emscripten_webgl_make_context_current(m_window);
	}

	void EmContext::init_input(Mouse& mouse, Keyboard& keyboard)
	{
		m_mouse = &mouse;
		m_keyboard = &keyboard;
	}

	bool EmContext::begin_frame()
	{
		// polling is actually done when yielding control to Emscripten in the main loop (which I find a bit lousy design since it's implicit)
		return true;
	}

	void EmContext::end_frame()
	{}

	void EmContext::lock_mouse(bool locked)
	{
		m_mouse_lock = locked;
		if(locked == false)
			emscripten_exit_pointerlock();
	}

	void EmContext::resize()
	{
		double width, height;
		emscripten_get_element_css_size("#canvas", &width, &height);
		emscripten_set_canvas_element_size("#canvas", int(width), int(height));

		m_size = { uint(width), uint(height) };
		m_fb_size = m_size;
	}

	bool EmContext::inject_mouse_move(const EmscriptenMouseEvent& mouseEvent)
	{
		m_cursor = max(vec2(0.f), min(vec2(m_size), vec2(float(mouseEvent.canvasX), float(mouseEvent.canvasY))));
		vec2 movement = { float(mouseEvent.movementX), float(mouseEvent.movementY) };
		m_mouse->moved(m_cursor, m_mouse_lock ? &movement : nullptr);
		return true;
	}

	void EmContext::update_mouse_lock()
	{
		if(m_mouse_lock)
		{
			EmscriptenPointerlockChangeEvent pointer_lock;
			emscripten_get_pointerlock_status(&pointer_lock);
			if (!pointer_lock.isActive)
				emscripten_request_pointerlock("#canvas", EM_TRUE);
		}
	}

	bool EmContext::inject_mouse_down(const EmscriptenMouseEvent& mouseEvent)
	{
		this->update_mouse_lock();
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
		m_keyboard->update_modifiers(keyEvent.shiftKey, keyEvent.ctrlKey, keyEvent.altKey);
		if(!keyEvent.repeat)
			m_keyboard->key_pressed(convert_html5_key(keyEvent.code), translate_html5_key(keyEvent.code, keyEvent.key[0]), m_keyboard->modifiers());
		return false;
	}

	bool EmContext::inject_key_up(const EmscriptenKeyboardEvent& keyEvent)
	{
		m_keyboard->update_modifiers(keyEvent.shiftKey, keyEvent.ctrlKey, keyEvent.altKey);
		m_keyboard->key_released(convert_html5_key(keyEvent.code), translate_html5_key(keyEvent.code, keyEvent.key[0]), m_keyboard->modifiers());
		return true;
	}

	bool EmContext::inject_key_press(const EmscriptenKeyboardEvent& keyEvent)
	{
		m_keyboard->update_modifiers(keyEvent.shiftKey, keyEvent.ctrlKey, keyEvent.altKey);
		m_keyboard->key_stroke(convert_html5_key(keyEvent.code), translate_html5_key(keyEvent.code, keyEvent.key[0]), m_keyboard->modifiers());
		if(keyEvent.key[1] == 0)
			m_keyboard->key_char(keyEvent.key[0]);
		return true;
	}

	bool EmContext::inject_wheel(const EmscriptenWheelEvent& wheelEvent)
	{
		m_mouse->wheeled(m_cursor, -wheelEvent.deltaY);
		return true;
	}
}
