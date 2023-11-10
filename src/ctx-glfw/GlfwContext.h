//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

//#ifdef TWO_CTX_GLFW

#ifndef TWO_MODULES
#include <ctx/Forward.h>
#include <ctx/Context.h>
#endif

#ifndef TWO_CTX_GLFW_EXPORT
#define TWO_CTX_GLFW_EXPORT TWO_IMPORT
#endif

#ifndef TWO_MODULES
extern "C" {
	typedef struct GLFWwindow GLFWwindow;
}
#endif

namespace two
{
	export_ class refl_ TWO_CTX_GLFW_EXPORT GlfwContext : public Context
	{
	public:
		GlfwContext(RenderSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main = true, bool autoswap = true);
		~GlfwContext();

		void init_context();
		virtual void init_input(Mouse& mouse, Keyboard& keyboard) override;

		virtual bool begin_frame() override;
		virtual void end_frame() override;

		virtual void lock_mouse(bool locked) override;

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

