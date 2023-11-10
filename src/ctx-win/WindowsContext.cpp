//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <stl/algorithm.h>
#include <math/Vec.hpp>
#include <ctx/InputDevice.h>
#include <ctx-win/WindowsContext.h>
//#include <ui/UiWindow.h>

#include <windows.h>
#include <windowsx.h>

#undef min
#undef max

#include <stl/vector.hpp>

namespace two
{
	static LRESULT CALLBACK wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);

	struct WindowHolder
	{
		void add(WinContext& window) { m_windows.push_back(&window); }
		void remove(WinContext& window) { two::remove(m_windows, &window); }
		WinContext* find(HWND hwnd) { for(WinContext* window : m_windows) if(window->m_hwnd == hwnd) return window; return nullptr; }

		vector<WinContext*> m_windows;

		static WindowHolder& instance() { static WindowHolder instance; return instance; }
	};

	struct TranslateKeyModifiers
	{
		int m_vk;
		InputMod m_modifier;
	};

	static const TranslateKeyModifiers s_translateKeyModifiers[6] =
	{
		{ VK_LMENU,    InputMod::Alt },
		{ VK_RMENU,    InputMod::Alt },
		{ VK_LCONTROL, InputMod::Ctrl },
		{ VK_RCONTROL, InputMod::Ctrl },
		{ VK_LSHIFT,   InputMod::Shift },
		{ VK_RSHIFT,   InputMod::Shift },
		//{ VK_LWIN,     Modifier::LeftMeta },
		//{ VK_RWIN,     Modifier::RightMeta },
	};

	MouseButtonCode mouse_button(uint32_t code)
	{
		if(code == WM_LBUTTONDOWN
		|| code == WM_LBUTTONUP) return LEFT_BUTTON;
		if(code == WM_MBUTTONDOWN
		|| code == WM_MBUTTONUP) return MIDDLE_BUTTON;
		if(code == WM_RBUTTONDOWN
		|| code == WM_RBUTTONUP) return RIGHT_BUTTON;
		return LEFT_BUTTON;
	}

	static uint8_t key_modifiers()
	{
		uint8_t modifiers = 0;
		for(const TranslateKeyModifiers& modifier : s_translateKeyModifiers)
			modifiers |= uint8_t(0 > GetKeyState(modifier.m_vk) ? modifier.m_modifier : InputMod::None);
		return modifiers;
	}

	struct KeyDispatch
	{
		KeyDispatch()
		{
			memset(m_translateKey, 0, sizeof(m_translateKey));
			m_translateKey[VK_ESCAPE] = Key::Escape;
			m_translateKey[VK_RETURN] = Key::Return;
			m_translateKey[VK_TAB] = Key::Tab;
			m_translateKey[VK_BACK] = Key::Back;
			m_translateKey[VK_SPACE] = Key::Space;
			m_translateKey[VK_UP] = Key::Up;
			m_translateKey[VK_DOWN] = Key::Down;
			m_translateKey[VK_LEFT] = Key::Left;
			m_translateKey[VK_RIGHT] = Key::Right;
			m_translateKey[VK_INSERT] = Key::Insert;
			m_translateKey[VK_DELETE] = Key::Delete;
			m_translateKey[VK_HOME] = Key::Home;
			m_translateKey[VK_END] = Key::End;
			m_translateKey[VK_PRIOR] = Key::PageUp;
			m_translateKey[VK_NEXT] = Key::PageDown;
			//s_translateKey[VK_SNAPSHOT] = Key::Print;
			m_translateKey[VK_OEM_PLUS] = Key::Add;
			m_translateKey[VK_OEM_MINUS] = Key::Subtract;
			m_translateKey[VK_OEM_4] = Key::LeftBracket;
			m_translateKey[VK_OEM_6] = Key::RightBracket;
			m_translateKey[VK_OEM_1] = Key::Semicolon;
			//s_translateKey[VK_OEM_7] = Key::Quote;
			m_translateKey[VK_OEM_COMMA] = Key::Comma;
			m_translateKey[VK_OEM_PERIOD] = Key::Period;
			m_translateKey[VK_DECIMAL] = Key::Period;
			m_translateKey[VK_OEM_2] = Key::Slash;
			m_translateKey[VK_OEM_5] = Key::Backslash;
			//s_translateKey[VK_OEM_3] = Key::Tilde;
			m_translateKey[VK_F1] = Key::F1;
			m_translateKey[VK_F2] = Key::F2;
			m_translateKey[VK_F3] = Key::F3;
			m_translateKey[VK_F4] = Key::F4;
			m_translateKey[VK_F5] = Key::F5;
			m_translateKey[VK_F6] = Key::F6;
			m_translateKey[VK_F7] = Key::F7;
			m_translateKey[VK_F8] = Key::F8;
			m_translateKey[VK_F9] = Key::F9;
			m_translateKey[VK_F10] = Key::F10;
			m_translateKey[VK_F11] = Key::F11;
			m_translateKey[VK_F12] = Key::F12;
			m_translateKey[VK_NUMPAD0] = Key::Numpad0;
			m_translateKey[VK_NUMPAD1] = Key::Numpad1;
			m_translateKey[VK_NUMPAD2] = Key::Numpad2;
			m_translateKey[VK_NUMPAD3] = Key::Numpad3;
			m_translateKey[VK_NUMPAD4] = Key::Numpad4;
			m_translateKey[VK_NUMPAD5] = Key::Numpad5;
			m_translateKey[VK_NUMPAD6] = Key::Numpad6;
			m_translateKey[VK_NUMPAD7] = Key::Numpad7;
			m_translateKey[VK_NUMPAD8] = Key::Numpad8;
			m_translateKey[VK_NUMPAD9] = Key::Numpad9;
			m_translateKey[uint8_t('0')] = Key::Num0;
			m_translateKey[uint8_t('1')] = Key::Num1;
			m_translateKey[uint8_t('2')] = Key::Num2;
			m_translateKey[uint8_t('3')] = Key::Num3;
			m_translateKey[uint8_t('4')] = Key::Num4;
			m_translateKey[uint8_t('5')] = Key::Num5;
			m_translateKey[uint8_t('6')] = Key::Num6;
			m_translateKey[uint8_t('7')] = Key::Num7;
			m_translateKey[uint8_t('8')] = Key::Num8;
			m_translateKey[uint8_t('9')] = Key::Num9;
			m_translateKey[uint8_t('A')] = Key::A;
			m_translateKey[uint8_t('B')] = Key::B;
			m_translateKey[uint8_t('C')] = Key::C;
			m_translateKey[uint8_t('D')] = Key::D;
			m_translateKey[uint8_t('E')] = Key::E;
			m_translateKey[uint8_t('F')] = Key::F;
			m_translateKey[uint8_t('G')] = Key::G;
			m_translateKey[uint8_t('H')] = Key::H;
			m_translateKey[uint8_t('I')] = Key::I;
			m_translateKey[uint8_t('J')] = Key::J;
			m_translateKey[uint8_t('K')] = Key::K;
			m_translateKey[uint8_t('L')] = Key::L;
			m_translateKey[uint8_t('M')] = Key::M;
			m_translateKey[uint8_t('N')] = Key::N;
			m_translateKey[uint8_t('O')] = Key::O;
			m_translateKey[uint8_t('P')] = Key::P;
			m_translateKey[uint8_t('Q')] = Key::Q;
			m_translateKey[uint8_t('R')] = Key::R;
			m_translateKey[uint8_t('S')] = Key::S;
			m_translateKey[uint8_t('T')] = Key::T;
			m_translateKey[uint8_t('U')] = Key::U;
			m_translateKey[uint8_t('V')] = Key::V;
			m_translateKey[uint8_t('W')] = Key::W;
			m_translateKey[uint8_t('X')] = Key::X;
			m_translateKey[uint8_t('Y')] = Key::Y;
			m_translateKey[uint8_t('Z')] = Key::Z;
		}

		Key m_translateKey[256];

		static KeyDispatch& instance() { static KeyDispatch instance; return instance; }
	};

	Key convert_key(WPARAM _wparam)
	{
		return (Key)KeyDispatch::instance().m_translateKey[_wparam & 0xff];
	}

	Key translate_key(WPARAM _wparam)
	{
		const char* name = nullptr; //glfwGetKeyName(key, scancode);
		if(name == nullptr) return translate(convert_key(_wparam));
		else if(name == string("a")) return translate(Key::A);
		else if(name == string("z")) return translate(Key::Z);
		else if(name == string("q")) return translate(Key::Q);
		else if(name == string("w")) return translate(Key::W);
		else return translate(convert_key(_wparam));
	}

	WinContext::WinContext(RenderSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main)
		: Context(gfx, name, size, fullscreen, main)
		, m_has_frame(true)
		, m_old_size(size)
	{
		if(WindowHolder::instance().m_windows.empty())
		{
			SetDllDirectoryA(".");

			HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);

			WNDCLASSEXA wnd = {};
			wnd.cbSize = sizeof(wnd);
			wnd.style = CS_HREDRAW | CS_VREDRAW;
			wnd.lpfnWndProc = wndProc;
			wnd.hInstance = instance;
			wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
			wnd.lpszClassName = "bgfx";
			wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			RegisterClassExA(&wnd);
		}

		WindowHolder::instance().add(*this);

		HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);
		m_hwnd = CreateWindowA("bgfx", name.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, size.x, size.y, NULL, NULL, instance, 0);

		m_native_handle = m_hwnd;

		this->clear();
		this->resize(size);
		//m_eventQueue.postWindowEvent(handle, hwnd);
	}

	WinContext::~WinContext()
	{
		WindowHolder::instance().remove(*this);

		//while(bgfx::RenderFrame::NoContext != bgfx::renderFrame()) {};

		DestroyWindow(m_hwnd);
	}

	bool WinContext::begin_frame()
	{
		MSG msg;
		msg.message = WM_NULL;

		WaitForInputIdle(GetCurrentProcess(), 16);

		while(0 != PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return !m_shutdown;
	}

	void WinContext::end_frame()
	{}

	void WinContext::move(const ivec2& pos)
	{
		SetWindowPos(m_hwnd, 0, pos.x, pos.y, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE);
	}

	void WinContext::resize(const uvec2& size)
	{
		this->adjust(size.x, size.y, true);
	}

	void WinContext::set_title(const char* title)
	{
		SetWindowTextA(m_hwnd, title);
	}

	void WinContext::toggle_frame()
	{
		if(m_has_frame)
		{
			m_old_size = m_size;
		}

		this->adjust(m_old_size.x, m_old_size.y, !m_has_frame);
	}

	void WinContext::toggle_fullscreen()
	{}

	void WinContext::clear()
	{
		RECT rect;
		GetWindowRect(m_hwnd, &rect);
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HDC hdc = GetDC(m_hwnd);
		SelectObject(hdc, brush);
		FillRect(hdc, &rect, brush);
	}

	void WinContext::adjust(uint32_t width, uint32_t height, bool frame)
	{
		m_size = uvec2(width, height);
		m_aspect = float(width) / float(height);

		ShowWindow(m_hwnd, SW_SHOWNORMAL);
		RECT rect;
		RECT newrect = { 0, 0, (LONG)width, (LONG)height };
		DWORD style = WS_POPUP | WS_SYSMENU;

		if(m_has_frame)
		{
			GetWindowRect(m_hwnd, &m_rect);
			m_style = GetWindowLong(m_hwnd, GWL_STYLE);
		}

		if(frame)
		{
			rect = m_rect;
			style = m_style;
		}
		else
		{
			HMONITOR monitor = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi;
			mi.cbSize = sizeof(mi);
			GetMonitorInfo(monitor, &mi);
			newrect = mi.rcMonitor;
			rect = mi.rcMonitor;
			m_aspect = float(newrect.right - newrect.left) / float(newrect.bottom - newrect.top);
		}

		SetWindowLong(m_hwnd, GWL_STYLE, style);
		uint32_t prewidth = newrect.right - newrect.left;
		uint32_t preheight = newrect.bottom - newrect.top;
		AdjustWindowRect(&newrect, style, FALSE);
		m_frame.x = (newrect.right - newrect.left) - prewidth;
		m_frame.y = (newrect.bottom - newrect.top) - preheight;
		UpdateWindow(m_hwnd);

		if(rect.left == -32000
			|| rect.top == -32000)
		{
			rect.left = 0;
			rect.top = 0;
		}

		int32_t left = rect.left;
		int32_t top = rect.top;
		width = (newrect.right - newrect.left);
		height = (newrect.bottom - newrect.top);

		if(!frame)
		{
			float aspect = 1.0f / m_aspect;
			width = max(m_min_size.x, width);
			height = uint32_t(float(width)*aspect);

			left = newrect.left + (newrect.right - newrect.left - width) / 2;
			top = newrect.top + (newrect.bottom - newrect.top - height) / 2;
		}

		SetWindowPos(m_hwnd, HWND_TOP, left, top, width, height, SWP_SHOWWINDOW);
		ShowWindow(m_hwnd, SW_RESTORE);

		m_has_frame = frame;
	}

	void WinContext::init_input(Mouse& mouse, Keyboard& keyboard)
	{
		m_mouse = &mouse;
		m_keyboard = &keyboard;
	}

	void WinContext::set_cursor(const ivec2& pos)
	{
		POINT pt = { pos.x, pos.y };
		ClientToScreen(m_hwnd, &pt);
		SetCursorPos(pt.x, pt.y);
	}

	void WinContext::lock_mouse(bool locked)
	{
		if(m_mouse_lock)
		{
			if(locked)
			{
				m_cursor = vec2(m_size) / 2.f;
				ShowCursor(false);
				set_cursor(ivec2(m_cursor));
			}
			else
			{
				set_cursor(ivec2(m_cursor));
				ShowCursor(true);
			}

			//m_mouse_lock = m_hwnd;
		}
	}
	
	void WinContext::capture_mouse(bool capture)
	{
		if(capture)
			SetCapture(m_hwnd);
		else
			ReleaseCapture();
	}

	LRESULT CALLBACK wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
	{
		WinContext* context = WindowHolder::instance().find(_hwnd);

		if(context == nullptr)
			return DefWindowProc(_hwnd, _id, _wparam, _lparam);

		switch(_id)
		{
		case WM_DESTROY:
			break;
		case WM_QUIT:
		case WM_CLOSE:
			context->m_shutdown = true;
			return 0;
		case WM_SIZING:
		{
			RECT& rect = *(RECT*)_lparam;
			uint32_t width = rect.right - rect.left - context->m_frame.x;
			uint32_t height = rect.bottom - rect.top - context->m_frame.y;

			// Recalculate size according to aspect ratio
			switch(_wparam)
			{
			case WMSZ_LEFT:
			case WMSZ_RIGHT:
			{
				float aspectRatio = 1.0f / context->m_aspect;
				width = max(context->m_min_size.x, width);
				height = uint32_t(float(width)*aspectRatio);
			}
			break;

			default:
			{
				float aspectRatio = context->m_aspect;
				height = max(context->m_min_size.y, height);
				width = uint32_t(float(height)*aspectRatio);
			}
			break;
			}

			// Recalculate position using different anchor points
			switch(_wparam)
			{
			case WMSZ_TOPLEFT:
				rect.left = rect.right - width - context->m_frame.x;
				rect.top = rect.bottom - height - context->m_frame.y;
				break;

			case WMSZ_TOP:
			case WMSZ_TOPRIGHT:
				rect.right = rect.left + width + context->m_frame.x;
				rect.top = rect.bottom - height - context->m_frame.y;
				break;

			case WMSZ_LEFT:
			case WMSZ_BOTTOMLEFT:
				rect.left = rect.right - width - context->m_frame.x;
				rect.bottom = rect.top + height + context->m_frame.y;
				break;

			default:
				rect.right = rect.left + width + context->m_frame.x;
				rect.bottom = rect.top + height + context->m_frame.y;
				break;
			}

			context->resize(uvec2(width, height));
		}
		return 0;

		case WM_SIZE:
		{
			uint32_t width = GET_X_LPARAM(_lparam);
			uint32_t height = GET_Y_LPARAM(_lparam);
			context->resize(uvec2(width, height));
		}
		break;

		case WM_SYSCOMMAND:
			switch(_wparam)
			{
			case SC_MINIMIZE:
			case SC_RESTORE:
			{
				HWND parent = GetWindow(_hwnd, GW_OWNER);
				if(NULL != parent)
				{
					PostMessage(parent, _id, _wparam, _lparam);
				}
			}
			}
			break;

		case WM_MOUSEMOVE:
		{
			int32_t mx = GET_X_LPARAM(_lparam);
			int32_t my = GET_Y_LPARAM(_lparam);

			if(context->m_mouse_lock)
			{
				mx -= int(context->m_cursor.x);
				my -= int(context->m_cursor.y);

				if(0 == mx && 0 == my)
				{
					break;
				}

				context->set_cursor(ivec2(mx, my));
			}

			context->m_mouse->moved(vec2(float(mx), float(my)));
		}
		break;

		case WM_MOUSEWHEEL:
		{
			POINT pt = { GET_X_LPARAM(_lparam), GET_Y_LPARAM(_lparam) };
			ScreenToClient(_hwnd, &pt);
			int32_t mx = pt.x;
			int32_t my = pt.y;
			int amount = GET_WHEEL_DELTA_WPARAM(_wparam) / WHEEL_DELTA;
			context->m_mouse->wheeled(vec2(float(mx), float(my)), float(amount));
		}
		break;

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			context->capture_mouse(true);
			int32_t mx = GET_X_LPARAM(_lparam);
			int32_t my = GET_Y_LPARAM(_lparam);
			context->m_mouse->m_buttons[mouse_button(_id)].pressed(vec2(float(mx), float(my)));
		}
		break;

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			context->capture_mouse(false);
			int32_t mx = GET_X_LPARAM(_lparam);
			int32_t my = GET_Y_LPARAM(_lparam);
			context->m_mouse->m_buttons[mouse_button(_id)].released(vec2(float(mx), float(my)));
		}
		break;

		//case WM_LBUTTONDBLCLK:
		//case WM_MBUTTONDBLCLK:
		//case WM_RBUTTONDBLCLK:
		//break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			uint8_t modifiers = key_modifiers();
			context->m_keyboard->key_pressed(convert_key(_wparam), translate_key(_wparam));
		}
		break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			uint8_t modifiers = key_modifiers();

			/*if(Key::Print == key && 0x3 == ((uint32_t)(_lparam) >> 30))
			{
				// VK_SNAPSHOT doesn't generate keydown event. Fire on down event when previous
				// key state bit is set to 1 and transition state bit is set to 1.
				//
				// http://msdn.microsoft.com/en-us/library/windows/desktop/ms646280%28v=vs.85%29.aspx
				m_eventQueue.postKeyEvent(handle, key, modifiers, true);
			}*/

			//printf("key released\n");
			context->m_keyboard->key_released(convert_key(_wparam), translate_key(_wparam)); // '0');
		}
		break;

		case WM_CHAR:
		{
			uint8_t utf8[4] = {};
			uint8_t len = (uint8_t)WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)&_wparam, 1, (LPSTR)utf8, 4, NULL, NULL);
			if(0 != len)
			{
				//m_eventQueue.postCharEvent(handle, len, utf8);
			}
		}
		break;
		
		default:
			break;
		}

		return DefWindowProc(_hwnd, _id, _wparam, _lparam);
	}

}
