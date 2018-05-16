//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

//#ifdef MUD_CTX_GLFW

#include <ctx/Generated/Forward.h>
#include <ctx/Context.h>

struct GLFWwindow;

#ifndef MUD_GLFW_EXPORT
#define MUD_GLFW_EXPORT
#endif

namespace mud
{
	class _refl_ MUD_GLFW_EXPORT GlfwContext : public Context
	{
	public:
		GlfwContext(RenderSystem& render_system, cstring name, int width, int height, bool full_screen, bool auto_swap = true);
		~GlfwContext();

		void init_context();
		virtual void init_input(Mouse& mouse, Keyboard& keyboard) final;

		virtual bool next_frame() final;

		virtual void reset(size_t width, size_t height) final;

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

#ifdef MUD_RENDERER_GL
	class GlfwRenderSystem : public RenderSystem
	{
	public:
		GlfwRenderSystem(const string& resourcePath);

		virtual object_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen);
		virtual object_ptr<Renderer> createRenderer(Context& context);
	};
#endif
}

