//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

//#ifdef TWO_CTX_NATIVE

#ifndef TWO_CTX_WIN_EXPORT
#define TWO_CTX_WIN_EXPORT TWO_IMPORT
#endif

#include <windows.h>

#undef near
#undef far
#undef min
#undef max

#undef OPAQUE

namespace two
{
	class TWO_CTX_WIN_EXPORT WinContext : public Context
	{
	public:
		WinContext(RenderSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main = true);
		~WinContext();

		virtual void init_input(Mouse& mouse, Keyboard& keyboard) override;

		virtual bool begin_frame() override;
		virtual void end_frame() override;

		virtual void lock_mouse(bool locked) override;

		void move(const ivec2& pos);
		void resize(const uvec2& size);
		void set_title(const char* title);
		void toggle_frame();
		void toggle_fullscreen();
		void clear();

		void adjust(uint32_t width, uint32_t height, bool frame);

		void set_cursor(const ivec2& pos);
		void capture_mouse(bool capture);

	public:
		HWND m_hwnd = nullptr;

		RECT m_rect;
		DWORD m_style;
		uvec2 m_old_size;
		uvec2 m_frame;
		float m_aspect;

		bool m_has_frame;

		uvec2 m_min_size;

		Mouse* m_mouse = nullptr;
		Keyboard* m_keyboard = nullptr;
	};
}

//#endif
