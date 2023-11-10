#pragma once

#include <two/ctx.h>



#ifdef TWO_PLATFORM_EMSCRIPTEN


#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#ifndef TWO_CTX_WASM_EXPORT
#define TWO_CTX_WASM_EXPORT
#endif

namespace two
{
	class TWO_CTX_WASM_EXPORT EmContext : public Context
	{
	public:
		EmContext(RenderSystem& renderSystem, const string& name, uvec2 size, bool fullscreen, bool main);

		void create_context(const string& name);
		virtual void init_input(Mouse& mouse, Keyboard& keyboard) override;

		virtual bool begin_frame() override;
		virtual void end_frame() override;

		virtual void lock_mouse(bool locked) override;

		void resize();

		void update_mouse_lock();

		bool inject_mouse_move(const EmscriptenMouseEvent& mouseEvent);

		bool inject_mouse_down(const EmscriptenMouseEvent& mouseEvent);
		bool inject_mouse_up(const EmscriptenMouseEvent& mouseEvent);

		bool inject_wheel(const EmscriptenWheelEvent& mouseEvent);

		bool inject_key_up(const EmscriptenKeyboardEvent& keyEvent);
		bool inject_key_down(const EmscriptenKeyboardEvent& keyEvent);
		bool inject_key_press(const EmscriptenKeyboardEvent& keyEvent);

		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_window;

		Mouse* m_mouse;
		Keyboard* m_keyboard;
	};
}

#endif
