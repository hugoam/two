//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

//#ifdef MUD_CTX_GLFW

#ifndef MUD_MODULES
#include <ctx/Forward.h>
#include <ctx/Context.h>

struct GLFWwindow;
#endif

#ifndef MUD_CTX_GLFW_EXPORT
#define MUD_CTX_GLFW_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class refl_ MUD_CTX_GLFW_EXPORT GlfwContext : public Context
	{
	public:
		GlfwContext(RenderSystem& render_system, const string& name, uvec2 size, bool full_screen, bool auto_swap = true);
		~GlfwContext();

		void init_context();
		virtual void init_input(Mouse& mouse, Keyboard& keyboard) final;

		virtual bool next_frame() final;

		virtual void lock_mouse(bool locked) final;

		void inject_mouse_move(double x, double y);
		void inject_mouse_button(int button, int action, int mods);
		void inject_key(int key, int scancode, int action, int mods);
		void inject_char(unsigned int codepoint, int mods = 0);
		void inject_wheel(double x, double y);

		void update_size();

		GLFWwindow* m_gl_window = nullptr;
		bool m_auto_swap;

		Mouse* m_mouse = nullptr;
		Keyboard* m_keyboard = nullptr;
	};
}

