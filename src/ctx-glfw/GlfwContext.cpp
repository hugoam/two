//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


module;
#include <infra/Cpp20.h>
#include <ctx-glfw/Glfw.h>
module two.ctx.glfw;

void glfw_error(int error, const char* desc)
{
	two::error("ctx glfw - GLFW %d: %s", error, desc);
}

namespace two
{
	MouseButtonCode convert_glfw_button(int button)
	{
		if(button == GLFW_MOUSE_BUTTON_LEFT)
			return LEFT_BUTTON;
		else if(button == GLFW_MOUSE_BUTTON_RIGHT)
			return RIGHT_BUTTON;
		else if(button == GLFW_MOUSE_BUTTON_MIDDLE)
			return MIDDLE_BUTTON;
		else
			return LEFT_BUTTON;
	}

	Key convert_glfw_key(int key)
	{
		switch(key)
		{
		case GLFW_KEY_UNKNOWN: return Key::Unassigned;
		case GLFW_KEY_SPACE: return Key::Space;
		case GLFW_KEY_APOSTROPHE: return Key::Apostrophe;
		case GLFW_KEY_COMMA: return Key::Comma;
		case GLFW_KEY_MINUS: return Key::Minus;
		case GLFW_KEY_PERIOD: return Key::Period;
		case GLFW_KEY_SLASH: return Key::Slash;
		case GLFW_KEY_0: return Key::Num0;
		case GLFW_KEY_1: return Key::Num1;
		case GLFW_KEY_2: return Key::Num2;
		case GLFW_KEY_3: return Key::Num3;
		case GLFW_KEY_4: return Key::Num4;
		case GLFW_KEY_5: return Key::Num5;
		case GLFW_KEY_6: return Key::Num6;
		case GLFW_KEY_7: return Key::Num7;
		case GLFW_KEY_8: return Key::Num8;
		case GLFW_KEY_9: return Key::Num9;
		case GLFW_KEY_SEMICOLON: return Key::Semicolon;
		case GLFW_KEY_EQUAL: return Key::Equals;
		case GLFW_KEY_A: return Key::A;
		case GLFW_KEY_B: return Key::B;
		case GLFW_KEY_C: return Key::C;
		case GLFW_KEY_D: return Key::D;
		case GLFW_KEY_E: return Key::E;
		case GLFW_KEY_F: return Key::F;
		case GLFW_KEY_G: return Key::G;
		case GLFW_KEY_H: return Key::H;
		case GLFW_KEY_I: return Key::I;
		case GLFW_KEY_J: return Key::J;
		case GLFW_KEY_K: return Key::K;
		case GLFW_KEY_L: return Key::L;
		case GLFW_KEY_M: return Key::M;
		case GLFW_KEY_N: return Key::N;
		case GLFW_KEY_O: return Key::O;
		case GLFW_KEY_P: return Key::P;
		case GLFW_KEY_Q: return Key::Q;
		case GLFW_KEY_R: return Key::R;
		case GLFW_KEY_S: return Key::S;
		case GLFW_KEY_T: return Key::T;
		case GLFW_KEY_U: return Key::U;
		case GLFW_KEY_V: return Key::V;
		case GLFW_KEY_W: return Key::W;
		case GLFW_KEY_X: return Key::X;
		case GLFW_KEY_Y: return Key::Y;
		case GLFW_KEY_Z: return Key::Z;
		case GLFW_KEY_LEFT_BRACKET: return Key::LeftBracket;
		case GLFW_KEY_BACKSLASH: return Key::Backslash;
		case GLFW_KEY_RIGHT_BRACKET: return Key::RightBracket;
			//case GLFW_KEY_GRAVE_ACCENT: 
			//case GLFW_KEY_WORLD_1: 
			//case GLFW_KEY_WORLD_2: 

		case GLFW_KEY_ESCAPE: return Key::Escape;
		case GLFW_KEY_ENTER: return Key::Return;
		case GLFW_KEY_TAB: return Key::Tab;
		case GLFW_KEY_BACKSPACE: return Key::Back;
		case GLFW_KEY_INSERT: return Key::Insert;
		case GLFW_KEY_DELETE: return Key::Delete;
		case GLFW_KEY_RIGHT: return Key::Right;
		case GLFW_KEY_LEFT: return Key::Left;
		case GLFW_KEY_DOWN: return Key::Down;
		case GLFW_KEY_UP: return Key::Up;
		case GLFW_KEY_PAGE_UP: return Key::PageUp;
		case GLFW_KEY_PAGE_DOWN: return Key::PageDown;
		case GLFW_KEY_HOME: return Key::Home;
		case GLFW_KEY_END: return Key::End;
		case GLFW_KEY_CAPS_LOCK: return Key::Capital;
			//case GLFW_KEY_SCROLL_LOCK:
		case GLFW_KEY_NUM_LOCK: return Key::Numlock;
			//case GLFW_KEY_PRINT_SCREEN:
		case GLFW_KEY_PAUSE: return Key::Pause;
		case GLFW_KEY_F1: return Key::F1;
		case GLFW_KEY_F2: return Key::F2;
		case GLFW_KEY_F3: return Key::F3;
		case GLFW_KEY_F4: return Key::F4;
		case GLFW_KEY_F5: return Key::F5;
		case GLFW_KEY_F6: return Key::F6;
		case GLFW_KEY_F7: return Key::F7;
		case GLFW_KEY_F8: return Key::F8;
		case GLFW_KEY_F9: return Key::F9;
		case GLFW_KEY_F10: return Key::F10;
		case GLFW_KEY_F11: return Key::F11;
		case GLFW_KEY_F12: return Key::F12;
		case GLFW_KEY_F13: return Key::F13;
		case GLFW_KEY_F14: return Key::F14;
		case GLFW_KEY_F15: return Key::F15;
		case GLFW_KEY_KP_0: return Key::Numpad0;
		case GLFW_KEY_KP_1: return Key::Numpad1;
		case GLFW_KEY_KP_2: return Key::Numpad2;
		case GLFW_KEY_KP_3: return Key::Numpad3;
		case GLFW_KEY_KP_4: return Key::Numpad4;
		case GLFW_KEY_KP_5: return Key::Numpad5;
		case GLFW_KEY_KP_6: return Key::Numpad6;
		case GLFW_KEY_KP_7: return Key::Numpad7;
		case GLFW_KEY_KP_8: return Key::Numpad8;
		case GLFW_KEY_KP_9: return Key::Numpad9;
		case GLFW_KEY_KP_DECIMAL: return Key::NumpadComma;
		case GLFW_KEY_KP_DIVIDE: return Key::Divide;
		case GLFW_KEY_KP_MULTIPLY: return Key::Multiply;
		case GLFW_KEY_KP_SUBTRACT: return Key::Subtract;
		case GLFW_KEY_KP_ADD: return Key::Add;
		case GLFW_KEY_KP_ENTER: return Key::NumpadEnter;
		case GLFW_KEY_KP_EQUAL: return Key::NumpadEnter;
		case GLFW_KEY_LEFT_SHIFT: return Key::LeftShift;
		case GLFW_KEY_LEFT_CONTROL: return Key::LeftControl;
		case GLFW_KEY_LEFT_ALT: return Key::LeftAlt;
		case GLFW_KEY_LEFT_SUPER: return Key::LeftWin;
		case GLFW_KEY_RIGHT_SHIFT: return Key::RightShift;
		case GLFW_KEY_RIGHT_CONTROL: return Key::RightControl;
		case GLFW_KEY_RIGHT_ALT: return Key::RightAlt;
		case GLFW_KEY_RIGHT_SUPER: return Key::RightWin;
			//case GLFW_KEY_MENU:
		default: return Key::Unassigned;
		}
	}

	Key translate_glfw_key(int key, int scancode)
	{
		const char* name = glfwGetKeyName(key, scancode);
		if(name == nullptr) return translate(convert_glfw_key(key));
		else if(name == string("a")) return translate(Key::A);
		else if(name == string("z")) return translate(Key::Z);
		else if(name == string("q")) return translate(Key::Q);
		else if(name == string("w")) return translate(Key::W);
		else return translate(convert_glfw_key(key));
	}

	GlfwContext::GlfwContext(RenderSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main, bool autoswap)
		: Context(gfx, name, size, fullscreen, main)
		, m_gl_window(nullptr)
		, m_auto_swap(autoswap)
	{
		this->init_context();
	}

	GlfwContext::~GlfwContext()
	{
		glfwTerminate();
	}

	void GlfwContext::init_context()
	{
		info("ctx glfw - creating GLFW context. GLFW version %i.%i", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);

		glfwSetErrorCallback(glfw_error);

		if(!glfwInit())
		{
			error("ctx glfw - failed to init GLFW.");
			return;
		}

#if defined TWO_RENDERER_BGFX && GLFW_VERSION_MINOR > 1
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#elif not defined TWO_RENDERER_BGFX
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
		//glfwWindowHint(GLFW_DECORATED, 0);

		m_gl_window = glfwCreateWindow(int(m_size.x), int(m_size.y), m_title.c_str(), NULL, NULL);

		if(!m_gl_window)
		{
			glfwTerminate();
			return;
		}

		glfwSetWindowUserPointer(m_gl_window, this);
		glfwMakeContextCurrent(m_gl_window);

		glfwSwapInterval(0);
		glfwSetTime(0);

#if defined TWO_PLATFORM_LINUX || defined TWO_PLATFORM_BSD
		m_native_handle = (void*)(uintptr_t)glfwGetX11Window(m_gl_window);
		m_native_target = glfwGetX11Display();
#elif defined TWO_PLATFORM_OSX
		m_native_handle = glfwGetCocoaWindow(m_gl_window);
#elif defined TWO_PLATFORM_WINDOWS
		m_native_handle = glfwGetWin32Window(m_gl_window);
#endif
	}

	void GlfwContext::lock_mouse(bool locked)
	{
		m_mouse_lock = locked;
		if(locked)
			glfwSetInputMode(m_gl_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(m_gl_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	bool GlfwContext::begin_frame()
	{
		this->update_size();

		glfwPollEvents();

		return !glfwWindowShouldClose(m_gl_window);
	}

	void GlfwContext::end_frame()
	{
		if(m_auto_swap)
			glfwSwapBuffers(m_gl_window);
	}

	void GlfwContext::update_size()
	{
		int width, height;
		int fb_width, fb_height;
		glfwGetWindowSize(m_gl_window, &width, &height);
		glfwGetFramebufferSize(m_gl_window, &fb_width, &fb_height);

		// Calculate pixel ration for hi-dpi devices.
		m_pixel_ratio = (float)fb_width / (float)width;

		m_size = { uint(width), uint(height) };
		m_fb_size = { uint(fb_width), uint(fb_height) };
	}

	void GlfwContext::init_input(Mouse& mouse, Keyboard& keyboard)
	{
		m_mouse = &mouse;
		m_keyboard = &keyboard;

		static auto getw = [](GLFWwindow* w) { return static_cast<GlfwContext*>(glfwGetWindowUserPointer(w)); };
		glfwSetKeyCallback(m_gl_window, [](GLFWwindow* w, int key, int scancode, int action, int mods) { getw(w)->inject_key(key, scancode, action, mods); });
		glfwSetCharCallback(m_gl_window, [](GLFWwindow* w, unsigned int c) { getw(w)->inject_char(c); });
		glfwSetMouseButtonCallback(m_gl_window, [](GLFWwindow* w, int button, int action, int mods) { getw(w)->inject_mouse_button(button, action, mods); });
		glfwSetCursorPosCallback(m_gl_window, [](GLFWwindow* w, double x, double y) { getw(w)->inject_mouse_move(x, y); });
		glfwSetScrollCallback(m_gl_window, [](GLFWwindow* w, double x, double y) { getw(w)->inject_wheel(x, y); });

		//glfwSetInputMode(m_glWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	void GlfwContext::inject_mouse_move(double x, double y)
	{
		//printf("glfw: mouse move %f, %f\n", float(x), float(y));
		if(m_mouse_lock)
			m_cursor = { float(x), float(y) };
		else
			m_cursor = max(vec2(0.f), min(vec2(m_fb_size), vec2(float(x), float(y))));
		m_mouse->moved(m_cursor);
	}

	void GlfwContext::inject_mouse_button(int button, int action, int mods)
	{
		UNUSED(mods);
		if(action == GLFW_PRESS)
			m_mouse->m_buttons[convert_glfw_button(button)].pressed(m_cursor);
		else if(action == GLFW_RELEASE)
			m_mouse->m_buttons[convert_glfw_button(button)].released(m_cursor);
	}

	void GlfwContext::inject_key(int key, int scancode, int action, int mods)
	{
		UNUSED(mods);
		if(action == GLFW_PRESS)
		{
			m_keyboard->key_pressed(convert_glfw_key(key), translate_glfw_key(key, scancode));
			m_keyboard->key_stroke(convert_glfw_key(key), translate_glfw_key(key, scancode));
		}
		else if(action == GLFW_RELEASE)
			m_keyboard->key_released(convert_glfw_key(key), translate_glfw_key(key, scancode));
		else if(action == GLFW_REPEAT)
			m_keyboard->key_stroke(convert_glfw_key(key), translate_glfw_key(key, scancode));
	}

	void GlfwContext::inject_char(unsigned int codepoint, int mods)
	{
		UNUSED(mods);
		m_keyboard->key_char(char(codepoint));
	}

	void GlfwContext::inject_wheel(double x, double y)
	{
		m_mouse->wheeled(m_cursor, float(x + y));
	}

}
