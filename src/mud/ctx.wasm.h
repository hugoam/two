#pragma once

#include <mud/ctx.h>
//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net


#ifdef MUD_PLATFORM_EMSCRIPTEN


#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#ifndef MUD_CTX_WASM_EXPORT
#define MUD_CTX_WASM_EXPORT
#endif

namespace mud
{
	class MUD_CTX_WASM_EXPORT EmContext : public Context
	{
	public:
		EmContext(RenderSystem& renderSystem, cstring name, int width, int height, bool full_screen);

		void init_context();
		virtual void init_input(Mouse& mouse, Keyboard& keyboard) final;
		virtual void reset(uint16_t width, uint16_t height) override;

		virtual bool next_frame() final;

		virtual void lock_mouse(bool locked) final;

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
