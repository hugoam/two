//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ctx-glfw/GlfwContext.h>

#include <ctx/KeyCode.h>
#include <ctx/InputDevice.h>

#include <GLFW/glfw3.h>

#if defined MUD_PLATFORM_WINDOWS
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3native.h>
	#undef max
	#undef min

#elif defined MUD_PLATFORM_LINUX
	#define GLFW_EXPOSE_NATIVE_X11
	#define GLFW_EXPOSE_NATIVE_GLX
	#include <GLFW/glfw3native.h>
#endif

void glfw_error(int error, const char* desc)
{
	printf("ERROR: GLFW %d: %s\n", error, desc);
}

namespace mud
{
	MouseButtonCode convertGlfwButton(int button)
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

	KeyCode convertGlfwKey(int key)
	{
		switch(key)
		{
		case GLFW_KEY_UNKNOWN: return KC_UNASSIGNED;
		case GLFW_KEY_SPACE: return KC_SPACE;
		case GLFW_KEY_APOSTROPHE: return KC_APOSTROPHE;
		case GLFW_KEY_COMMA: return KC_COMMA;
		case GLFW_KEY_MINUS: return KC_MINUS;
		case GLFW_KEY_PERIOD: return KC_PERIOD;
		case GLFW_KEY_SLASH: return KC_SLASH;
		case GLFW_KEY_0: return KC_0;
		case GLFW_KEY_1: return KC_1;
		case GLFW_KEY_2: return KC_2;
		case GLFW_KEY_3: return KC_3;
		case GLFW_KEY_4: return KC_4;
		case GLFW_KEY_5: return KC_5;
		case GLFW_KEY_6: return KC_6;
		case GLFW_KEY_7: return KC_7;
		case GLFW_KEY_8: return KC_8;
		case GLFW_KEY_9: return KC_9;
		case GLFW_KEY_SEMICOLON: return KC_SEMICOLON;
		case GLFW_KEY_EQUAL: return KC_EQUALS;
		case GLFW_KEY_A: return KC_A;
		case GLFW_KEY_B: return KC_B;
		case GLFW_KEY_C: return KC_C;
		case GLFW_KEY_D: return KC_D;
		case GLFW_KEY_E: return KC_E;
		case GLFW_KEY_F: return KC_F;
		case GLFW_KEY_G: return KC_G;
		case GLFW_KEY_H: return KC_H;
		case GLFW_KEY_I: return KC_I;
		case GLFW_KEY_J: return KC_J;
		case GLFW_KEY_K: return KC_K;
		case GLFW_KEY_L: return KC_L;
		case GLFW_KEY_M: return KC_M;
		case GLFW_KEY_N: return KC_N;
		case GLFW_KEY_O: return KC_O;
		case GLFW_KEY_P: return KC_P;
		case GLFW_KEY_Q: return KC_Q;
		case GLFW_KEY_R: return KC_R;
		case GLFW_KEY_S: return KC_S;
		case GLFW_KEY_T: return KC_T;
		case GLFW_KEY_U: return KC_U;
		case GLFW_KEY_V: return KC_V;
		case GLFW_KEY_W: return KC_W;
		case GLFW_KEY_X: return KC_X;
		case GLFW_KEY_Y: return KC_Y;
		case GLFW_KEY_Z: return KC_Z;
		case GLFW_KEY_LEFT_BRACKET: return KC_LBRACKET;
		case GLFW_KEY_BACKSLASH: return KC_BACKSLASH;
		case GLFW_KEY_RIGHT_BRACKET: return KC_RBRACKET;
			//case GLFW_KEY_GRAVE_ACCENT: 
			//case GLFW_KEY_WORLD_1: 
			//case GLFW_KEY_WORLD_2: 

		case GLFW_KEY_ESCAPE: return KC_ESCAPE;
		case GLFW_KEY_ENTER: return KC_RETURN;
		case GLFW_KEY_TAB: return KC_TAB;
		case GLFW_KEY_BACKSPACE: return KC_BACK;
		case GLFW_KEY_INSERT: return KC_INSERT;
		case GLFW_KEY_DELETE: return KC_DELETE;
		case GLFW_KEY_RIGHT: return KC_RIGHT;
		case GLFW_KEY_LEFT: return KC_LEFT;
		case GLFW_KEY_DOWN: return KC_DOWN;
		case GLFW_KEY_UP: return KC_UP;
		case GLFW_KEY_PAGE_UP: return KC_PGUP;
		case GLFW_KEY_PAGE_DOWN: return KC_PGDOWN;
		case GLFW_KEY_HOME: return KC_HOME;
		case GLFW_KEY_END: return KC_END;
		case GLFW_KEY_CAPS_LOCK: return KC_CAPITAL;
			//case GLFW_KEY_SCROLL_LOCK:
		case GLFW_KEY_NUM_LOCK: return KC_NUMLOCK;
			//case GLFW_KEY_PRINT_SCREEN:
		case GLFW_KEY_PAUSE: return KC_PAUSE;
		case GLFW_KEY_F1: return KC_F1;
		case GLFW_KEY_F2: return KC_F2;
		case GLFW_KEY_F3: return KC_F3;
		case GLFW_KEY_F4: return KC_F4;
		case GLFW_KEY_F5: return KC_F5;
		case GLFW_KEY_F6: return KC_F6;
		case GLFW_KEY_F7: return KC_F7;
		case GLFW_KEY_F8: return KC_F8;
		case GLFW_KEY_F9: return KC_F9;
		case GLFW_KEY_F10: return KC_F10;
		case GLFW_KEY_F11: return KC_F11;
		case GLFW_KEY_F12: return KC_F12;
		case GLFW_KEY_F13: return KC_F13;
		case GLFW_KEY_F14: return KC_F14;
		case GLFW_KEY_F15: return KC_F15;
		case GLFW_KEY_KP_0: return KC_NUMPAD0;
		case GLFW_KEY_KP_1: return KC_NUMPAD1;
		case GLFW_KEY_KP_2: return KC_NUMPAD2;
		case GLFW_KEY_KP_3: return KC_NUMPAD3;
		case GLFW_KEY_KP_4: return KC_NUMPAD4;
		case GLFW_KEY_KP_5: return KC_NUMPAD5;
		case GLFW_KEY_KP_6: return KC_NUMPAD6;
		case GLFW_KEY_KP_7: return KC_NUMPAD7;
		case GLFW_KEY_KP_8: return KC_NUMPAD8;
		case GLFW_KEY_KP_9: return KC_NUMPAD9;
		case GLFW_KEY_KP_DECIMAL: return KC_NUMPADCOMMA;
		case GLFW_KEY_KP_DIVIDE: return KC_DIVIDE;
		case GLFW_KEY_KP_MULTIPLY: return KC_MULTIPLY;
		case GLFW_KEY_KP_SUBTRACT: return KC_SUBTRACT;
		case GLFW_KEY_KP_ADD: return KC_ADD;
		case GLFW_KEY_KP_ENTER: return KC_NUMPADENTER;
		case GLFW_KEY_KP_EQUAL: return KC_NUMPADENTER;
		case GLFW_KEY_LEFT_SHIFT: return KC_LSHIFT;
		case GLFW_KEY_LEFT_CONTROL: return KC_LCONTROL;
		case GLFW_KEY_LEFT_ALT: return KC_LMENU;
		case GLFW_KEY_LEFT_SUPER: return KC_LWIN;
		case GLFW_KEY_RIGHT_SHIFT: return KC_RSHIFT;
		case GLFW_KEY_RIGHT_CONTROL: return KC_RCONTROL;
		case GLFW_KEY_RIGHT_ALT: return KC_RMENU;
		case GLFW_KEY_RIGHT_SUPER: return KC_RWIN;
			//case GLFW_KEY_MENU:
		default: return KC_UNASSIGNED;
		}
	}

	GlfwContext::GlfwContext(RenderSystem& render_system, cstring name, int width, int height, bool full_screen, bool auto_swap)
		: Context(render_system, name, width, height, full_screen)
		, m_gl_window(nullptr)
		, m_auto_swap(auto_swap)
	{
		this->init_context();
	}

	GlfwContext::~GlfwContext()
	{
		glfwTerminate();
	}

	void GlfwContext::init_context()
	{
		printf("INFO: Creating GLFW context. GLFW version %i.%i\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);

		glfwSetErrorCallback(glfw_error);

		if(!glfwInit())
		{
			printf("ERROR: Failed to init GLFW.\n");
			return;
		}

#if defined MUD_RENDERER_BGFX && GLFW_VERSION_MINOR > 1
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#elif not defined MUD_RENDERER_BGFX
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
		//glfwWindowHint(GLFW_DECORATED, 0);

		m_gl_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

		if(!m_gl_window)
		{
			glfwTerminate();
			return;
		}

		glfwSetWindowUserPointer(m_gl_window, this);
		glfwMakeContextCurrent(m_gl_window);

		glfwSwapInterval(0);
		glfwSetTime(0);

#if defined MUD_PLATFORM_LINUX || defined MUD_PLATFORM_BSD
		m_native_handle = (void*)(uintptr_t)glfwGetX11Window(m_gl_window);
		m_native_target = glfwGetX11Display();
#elif defined MUD_PLATFORM_OSX
		m_native_handle = glfwGetCocoaWindow(m_gl_window);
#elif defined MUD_PLATFORM_WINDOWS
		m_native_handle = glfwGetWin32Window(m_gl_window);
#endif
	}

	bool GlfwContext::next_frame()
	{
		this->update_size();

		glfwPollEvents();

		if(m_auto_swap)
			glfwSwapBuffers(m_gl_window);

		return !glfwWindowShouldClose(m_gl_window);
	}

	void GlfwContext::update_size()
	{
		int width, height;
		int fbWidth, fbHeight;
		glfwGetWindowSize(m_gl_window, &width, &height);
		glfwGetFramebufferSize(m_gl_window, &fbWidth, &fbHeight);

		// Calculate pixel ration for hi-dpi devices.
		// float pxRatio = (float)fbWidth / (float)winWidth;

		m_width = width;
		m_height = height;
	}

	void GlfwContext::init_input(Mouse& mouse, Keyboard& keyboard)
	{
		m_mouse = &mouse;
		m_keyboard = &keyboard;

		glfwSetKeyCallback(m_gl_window, [](GLFWwindow* w, int key, int scancode, int action, int mods) { static_cast<GlfwContext*>(glfwGetWindowUserPointer(w))->inject_key(key, scancode, action, mods); });
		glfwSetCharCallback(m_gl_window, [](GLFWwindow* w, unsigned int c) { static_cast<GlfwContext*>(glfwGetWindowUserPointer(w))->inject_char(c); });
		glfwSetMouseButtonCallback(m_gl_window, [](GLFWwindow* w, int button, int action, int mods) { static_cast<GlfwContext*>(glfwGetWindowUserPointer(w))->inject_mouse_button(button, action, mods); });
		glfwSetCursorPosCallback(m_gl_window, [](GLFWwindow* w, double x, double y) { static_cast<GlfwContext*>(glfwGetWindowUserPointer(w))->inject_mouse_move(x, y); });
		glfwSetScrollCallback(m_gl_window, [](GLFWwindow* w, double x, double y) { static_cast<GlfwContext*>(glfwGetWindowUserPointer(w))->inject_wheel(x, y); });

		//glfwSetInputMode(m_glWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	void GlfwContext::reset(size_t width, size_t height)
	{
		UNUSED(width); UNUSED(height);
	}

	void GlfwContext::inject_mouse_move(double x, double y)
	{
		vec2 size = { float(m_width), float(m_height) };
		m_cursor = max(vec2(0.f), min(size, vec2{ float(x), float(y) }));

		m_mouse->moved(m_cursor);
	}

	void GlfwContext::inject_mouse_button(int button, int action, int mods)
	{
		UNUSED(mods);
		if(action == GLFW_PRESS)
			m_mouse->m_buttons[convertGlfwButton(button)].pressed(m_cursor);
		else if(action == GLFW_RELEASE)
			m_mouse->m_buttons[convertGlfwButton(button)].released(m_cursor);
	}

	void GlfwContext::inject_key(int key, int scancode, int action, int mods)
	{
		UNUSED(scancode); UNUSED(mods);
		if(action == GLFW_PRESS)
			m_keyboard->key_pressed(convertGlfwKey(key), char(0));
		else if(action == GLFW_RELEASE)
			m_keyboard->key_released(convertGlfwKey(key), char(0));
		else if(action == GLFW_REPEAT)
			m_keyboard->key_stroke(convertGlfwKey(key), char(0));
	}

	void GlfwContext::inject_char(unsigned int codepoint, int mods)
	{
		UNUSED(codepoint); UNUSED(mods);
		m_keyboard->key_char(KC_UNASSIGNED, char(codepoint));
	}

	void GlfwContext::inject_wheel(double x, double y)
	{
		m_mouse->wheeled(m_cursor, float(x + y));
	}

}
#ifdef MUD_RENDERER_GL
#include <ui/Backend/Gl/GlRenderer.h>

namespace mud
{
	GlfwRenderSystem::GlfwRenderSystem(const string& resourcePath)
		: RenderSystem(resourcePath, true)
	{}

	object_ptr<Context> GlfwRenderSystem::createContext(const string& name, int width, int height, bool fullScreen)
	{
		return make_object<GlfwContext>(*this, name, width, height, fullScreen, true);
	}

	object_ptr<Renderer> GlfwRenderSystem::createRenderer(Context& context)
	{
		return make_object<GlRenderer>(m_resource_path, true);
	}
}
#endif
