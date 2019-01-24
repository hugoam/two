//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifdef MUD_CTX_NATIVE

/* mud */
#include <ui/Generated/Types.h>
#include <ui/Render/Context.h>

#include <windows.h>

namespace mud
{
	class MUD_CTX_WIN_EXPORT WinRenderWindow : public RenderWindow
	{
	public:
		WinRenderWindow(const string& name, int width, int height);
		~WinRenderWindow();

		bool nextFrame();

		//WindowHandle createWindow(int32_t _x, int32_t _y, uint32_t _width, uint32_t _height, uint32_t _flags, const char* _title)
		void destroy();
		void setPosition(int32_t x, int32_t y);
		void setSize(uint32_t width, uint32_t height);
		void setTitle(const char* title);
		void toggleWindowFrame();
		void toggleFullscreen();
		void clear();

		void adjust(uint32_t width, uint32_t height, bool windowFrame);

	public:
		HWND m_hwnd;

		RECT m_rect;
		DWORD m_style;
		uint32_t m_oldWidth;
		uint32_t m_oldHeight;
		uint32_t m_frameWidth;
		uint32_t m_frameHeight;
		float m_aspectRatio;

		bool m_frame;

		uint32_t m_minWidth;
		uint32_t m_minHeight;
	};

	class MUD_CTX_WIN_EXPORT WinInputWindow : public InputWindow
	{
	public:
		WinInputWindow();

		void initInput(RenderWindow& renderWindow, Mouse& mouse, Keyboard& keyboard);

		bool nextFrame();

		void resize(size_t width, size_t height);

		void setMousePos(int32_t mx, int32_t my);
		void setMouseLock(bool lock);
		void mouseCapture(bool capture);

	public:
		WinRenderWindow* m_renderWindow;
		HWND m_hwnd;

		Mouse* m_mouse;
		Keyboard* m_keyboard;

		int32_t m_mouse_x;
		int32_t m_mouse_y;
		int32_t m_mouse_z;

		bool m_mouseLock;
	};

	class MUD_CTX_WIN_EXPORT WinContext : public Context
	{
	public:
		WinContext(RenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen);
		~WinContext();

		object_ptr<WinRenderWindow> initialize(const string& name, int width, int height, bool fullScreen);

		WinRenderWindow& m_render;
		WinInputWindow& m_input;
	};

	class WinRenderSystem : public RenderSystem
	{
	public:
		WinRenderSystem(const string& resourcePath);

		virtual object_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen);
		virtual object_ptr<Renderer> createRenderer(Context& context) = 0;
	};

}

#endif
