#pragma once

#include <two/math.h>
#include <two/ctx.h>
#include <two/infra.h>
#include <two/type.h>



//#ifdef TWO_CTX_GLFW

#ifndef TWO_CTX_GLFW_EXPORT
#define TWO_CTX_GLFW_EXPORT TWO_IMPORT
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





#ifndef TWO_CTX_GLFW_EXPORT
#define TWO_CTX_GLFW_EXPORT TWO_IMPORT
#endif

namespace two
{
    class GlfwContext;
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif


namespace two
{
    // Exported types
    
    export_ template <> TWO_CTX_GLFW_EXPORT Type& type<two::GlfwContext>();
}
