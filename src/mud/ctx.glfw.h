#pragma once

#include <mud/math.h>
#include <mud/ctx.h>
#include <mud/infra.h>
#include <mud/type.h>


//#ifdef MUD_CTX_GLFW

#ifndef MUD_MODULES

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
		GlfwContext(RenderSystem& render_system, const string& name, int width, int height, bool full_screen, bool auto_swap = true);
		~GlfwContext();

		void init_context();
		virtual void init_input(Mouse& mouse, Keyboard& keyboard) final;
		virtual void reset(uint16_t width, uint16_t height) override;

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





#ifndef MUD_CTX_GLFW_EXPORT
#define MUD_CTX_GLFW_EXPORT MUD_IMPORT
#endif

namespace mud
{
    class GlfwContext;
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stdint.h>
#include <stl/vector.h>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_CTX_GLFW_EXPORT Type& type<mud::GlfwContext>();
}
