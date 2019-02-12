#include <mud/ui.h>


#include <ui/Config.h>
#include <ui/Context/Windows/WindowsContext.h>

#include <mudobj/Iterable/Iterable.h>
#include <ui/Input/InputDevice.h>

#include <windows.h>
#include <windowsx.h>

namespace mud
{
	static LRESULT CALLBACK wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);

	struct WindowHolder
	{
		void add(WinContext& window) { m_windows.push_back(&window); }
		void remove(WinContext& window) { vector_remove(m_windows, &window); }
		WinContext* find(HWND hwnd) { for(WinContext* window : m_windows) if(window->m_render.m_hwnd == hwnd) return window; return nullptr; }

		vector<WinContext*> m_windows;

		static WindowHolder& instance() { static WindowHolder instance; return instance; }
	};

	struct TranslateKeyModifiers
	{
		int m_vk;
		InputModifier m_modifier;
	};

	static const TranslateKeyModifiers s_translateKeyModifiers[6] =
	{
		{ VK_LMENU,    INPUT_ALT },
		{ VK_RMENU,    INPUT_ALT },
		{ VK_LCONTROL, INPUT_CTRL },
		{ VK_RCONTROL, INPUT_CTRL },
		{ VK_LSHIFT,   INPUT_SHIFT },
		{ VK_RSHIFT,   INPUT_SHIFT },
		//{ VK_LWIN,     Modifier::LeftMeta },
		//{ VK_RWIN,     Modifier::RightMeta },
	};

	MouseButtonCode mouseButton(uint32_t code)
	{
		if(code == WM_LBUTTONDOWN
		|| code == WM_LBUTTONUP) return LEFT_BUTTON;
		if(code == WM_MBUTTONDOWN
		|| code == WM_MBUTTONUP) return MIDDLE_BUTTON;
		if(code == WM_RBUTTONDOWN
		|| code == WM_RBUTTONUP) return RIGHT_BUTTON;
	}

	static uint8_t translateKeyModifiers()
	{
		uint8_t modifiers = 0;
		for(const TranslateKeyModifiers& modifier : s_translateKeyModifiers)
			modifiers |= 0 > GetKeyState(modifier.m_vk) ? modifier.m_modifier : INPUT_NO_MOD;
		return modifiers;
	}

	struct KeyDispatch
	{
		KeyDispatch()
		{
			memset(m_translateKey, 0, sizeof(m_translateKey));
			m_translateKey[VK_ESCAPE] = KC_ESCAPE;
			m_translateKey[VK_RETURN] = KC_RETURN;
			m_translateKey[VK_TAB] = KC_TAB;
			m_translateKey[VK_BACK] = KC_BACK;
			m_translateKey[VK_SPACE] = KC_SPACE;
			m_translateKey[VK_UP] = KC_UP;
			m_translateKey[VK_DOWN] = KC_DOWN;
			m_translateKey[VK_LEFT] = KC_LEFT;
			m_translateKey[VK_RIGHT] = KC_RIGHT;
			m_translateKey[VK_INSERT] = KC_INSERT;
			m_translateKey[VK_DELETE] = KC_DELETE;
			m_translateKey[VK_HOME] = KC_HOME;
			m_translateKey[VK_END] = KC_END;
			m_translateKey[VK_PRIOR] = KC_PGUP;
			m_translateKey[VK_NEXT] = KC_PGDOWN;
			//s_translateKey[VK_SNAPSHOT] = Key::Print;
			m_translateKey[VK_OEM_PLUS] = KC_ADD;
			m_translateKey[VK_OEM_MINUS] = KC_SUBTRACT;
			m_translateKey[VK_OEM_4] = KC_LBRACKET;
			m_translateKey[VK_OEM_6] = KC_RBRACKET;
			m_translateKey[VK_OEM_1] = KC_SEMICOLON;
			//s_translateKey[VK_OEM_7] = Key::Quote;
			m_translateKey[VK_OEM_COMMA] = KC_COMMA;
			m_translateKey[VK_OEM_PERIOD] = KC_PERIOD;
			m_translateKey[VK_DECIMAL] = KC_PERIOD;
			m_translateKey[VK_OEM_2] = KC_SLASH;
			m_translateKey[VK_OEM_5] = KC_BACKSLASH;
			//s_translateKey[VK_OEM_3] = Key::Tilde;
			m_translateKey[VK_F1] = KC_F1;
			m_translateKey[VK_F2] = KC_F2;
			m_translateKey[VK_F3] = KC_F3;
			m_translateKey[VK_F4] = KC_F4;
			m_translateKey[VK_F5] = KC_F5;
			m_translateKey[VK_F6] = KC_F6;
			m_translateKey[VK_F7] = KC_F7;
			m_translateKey[VK_F8] = KC_F8;
			m_translateKey[VK_F9] = KC_F9;
			m_translateKey[VK_F10] = KC_F10;
			m_translateKey[VK_F11] = KC_F11;
			m_translateKey[VK_F12] = KC_F12;
			m_translateKey[VK_NUMPAD0] = KC_NUMPAD0;
			m_translateKey[VK_NUMPAD1] = KC_NUMPAD1;
			m_translateKey[VK_NUMPAD2] = KC_NUMPAD2;
			m_translateKey[VK_NUMPAD3] = KC_NUMPAD3;
			m_translateKey[VK_NUMPAD4] = KC_NUMPAD4;
			m_translateKey[VK_NUMPAD5] = KC_NUMPAD5;
			m_translateKey[VK_NUMPAD6] = KC_NUMPAD6;
			m_translateKey[VK_NUMPAD7] = KC_NUMPAD7;
			m_translateKey[VK_NUMPAD8] = KC_NUMPAD8;
			m_translateKey[VK_NUMPAD9] = KC_NUMPAD9;
			m_translateKey[uint8_t('0')] = KC_0;
			m_translateKey[uint8_t('1')] = KC_1;
			m_translateKey[uint8_t('2')] = KC_2;
			m_translateKey[uint8_t('3')] = KC_3;
			m_translateKey[uint8_t('4')] = KC_4;
			m_translateKey[uint8_t('5')] = KC_5;
			m_translateKey[uint8_t('6')] = KC_6;
			m_translateKey[uint8_t('7')] = KC_7;
			m_translateKey[uint8_t('8')] = KC_8;
			m_translateKey[uint8_t('9')] = KC_9;
			m_translateKey[uint8_t('A')] = KC_A;
			m_translateKey[uint8_t('B')] = KC_B;
			m_translateKey[uint8_t('C')] = KC_C;
			m_translateKey[uint8_t('D')] = KC_D;
			m_translateKey[uint8_t('E')] = KC_E;
			m_translateKey[uint8_t('F')] = KC_F;
			m_translateKey[uint8_t('G')] = KC_G;
			m_translateKey[uint8_t('H')] = KC_H;
			m_translateKey[uint8_t('I')] = KC_I;
			m_translateKey[uint8_t('J')] = KC_J;
			m_translateKey[uint8_t('K')] = KC_K;
			m_translateKey[uint8_t('L')] = KC_L;
			m_translateKey[uint8_t('M')] = KC_M;
			m_translateKey[uint8_t('N')] = KC_N;
			m_translateKey[uint8_t('O')] = KC_O;
			m_translateKey[uint8_t('P')] = KC_P;
			m_translateKey[uint8_t('Q')] = KC_Q;
			m_translateKey[uint8_t('R')] = KC_R;
			m_translateKey[uint8_t('S')] = KC_S;
			m_translateKey[uint8_t('T')] = KC_T;
			m_translateKey[uint8_t('U')] = KC_U;
			m_translateKey[uint8_t('V')] = KC_V;
			m_translateKey[uint8_t('W')] = KC_W;
			m_translateKey[uint8_t('X')] = KC_X;
			m_translateKey[uint8_t('Y')] = KC_Y;
			m_translateKey[uint8_t('Z')] = KC_Z;
		}

		KeyCode m_translateKey[256];

		static KeyDispatch& instance() { static KeyDispatch instance; return instance; }
	};

	static KeyCode translateKey(WPARAM _wparam)
	{
		return (KeyCode)KeyDispatch::instance().m_translateKey[_wparam & 0xff];
	}

	WinRenderWindow::WinRenderWindow(const string& name, int width, int height)
		: RenderWindow(name, width, height)
		, m_frame(true)
		, m_oldWidth(width)
		, m_oldHeight(height)
	{
		HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);
		m_hwnd = CreateWindowA("bgfx", name.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, width, height, NULL, NULL, instance, 0);

		m_nativeHandle = m_hwnd;

		this->clear();
		this->setSize(width, height);
		//m_eventQueue.postWindowEvent(handle, hwnd);
	}

	WinRenderWindow::~WinRenderWindow()
	{
		//while(bgfx::RenderFrame::NoContext != bgfx::renderFrame()) {};

		DestroyWindow(m_hwnd);
	}

	bool WinRenderWindow::nextFrame()
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

	void WinRenderWindow::destroy()
	{
		m_shutdown = true;
	}

	void WinRenderWindow::setPosition(int32_t x, int32_t y)
	{
		SetWindowPos(m_hwnd, 0, x, y, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE);
	}

	void WinRenderWindow::setSize(uint32_t width, uint32_t height)
	{
		this->adjust(width, height, true);
	}

	void WinRenderWindow::setTitle(const char* title)
	{
		SetWindowTextA(m_hwnd, title);
	}

	void WinRenderWindow::toggleWindowFrame()
	{
		if(m_frame)
		{
			m_oldWidth = m_width;
			m_oldHeight = m_height;
		}

		this->adjust(m_oldWidth, m_oldHeight, !m_frame);
	}

	void WinRenderWindow::toggleFullscreen()
	{
		
	}

	void WinRenderWindow::clear()
	{
		RECT rect;
		GetWindowRect(m_hwnd, &rect);
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HDC hdc = GetDC(m_hwnd);
		SelectObject(hdc, brush);
		FillRect(hdc, &rect, brush);
	}

	void WinRenderWindow::adjust(uint32_t width, uint32_t height, bool windowFrame)
	{
		m_width = width;
		m_height = height;
		m_aspectRatio = float(width) / float(height);

		ShowWindow(m_hwnd, SW_SHOWNORMAL);
		RECT rect;
		RECT newrect = { 0, 0, (LONG)width, (LONG)height };
		DWORD style = WS_POPUP | WS_SYSMENU;

		if(m_frame)
		{
			GetWindowRect(m_hwnd, &m_rect);
			m_style = GetWindowLong(m_hwnd, GWL_STYLE);
		}

		if(windowFrame)
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
			m_aspectRatio = float(newrect.right - newrect.left) / float(newrect.bottom - newrect.top);
		}

		SetWindowLong(m_hwnd, GWL_STYLE, style);
		uint32_t prewidth = newrect.right - newrect.left;
		uint32_t preheight = newrect.bottom - newrect.top;
		AdjustWindowRect(&newrect, style, FALSE);
		m_frameWidth = (newrect.right - newrect.left) - prewidth;
		m_frameHeight = (newrect.bottom - newrect.top) - preheight;
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

		if(!windowFrame)
		{
			float aspectRatio = 1.0f / m_aspectRatio;
			width = max(m_minWidth, width);
			height = uint32_t(float(width)*aspectRatio);

			left = newrect.left + (newrect.right - newrect.left - width) / 2;
			top = newrect.top + (newrect.bottom - newrect.top - height) / 2;
		}

		SetWindowPos(m_hwnd, HWND_TOP, left, top, width, height, SWP_SHOWWINDOW);
		ShowWindow(m_hwnd, SW_RESTORE);

		m_frame = windowFrame;
	}

	WinInputWindow::WinInputWindow()
		: m_hwnd(nullptr)
		, m_mouse(nullptr)
		, m_keyboard(nullptr)
		, m_mouseLock(false)
		, m_mouse_z(0)
	{}

	void WinInputWindow::initInput(RenderWindow& renderWindow, Mouse& mouse, Keyboard& keyboard)
	{
		m_renderWindow = &as<WinRenderWindow>(renderWindow);
		m_hwnd = m_renderWindow->m_hwnd;
		m_mouse = &mouse;
		m_keyboard = &keyboard;
	}

	bool WinInputWindow::nextFrame()
	{
		return true;
	}

	void WinInputWindow::resize(size_t width, size_t height)
	{}


	void WinInputWindow::setMousePos(int32_t mx, int32_t my)
	{
		POINT pt = { mx, my };
		ClientToScreen(m_hwnd, &pt);
		SetCursorPos(pt.x, pt.y);
	}

	void WinInputWindow::setMouseLock(bool lock)
	{
		if(m_mouseLock)
		{
			if(lock)
			{
				m_mouse_x = m_renderWindow->m_width / 2;
				m_mouse_y = m_renderWindow->m_height / 2;
				ShowCursor(false);
				setMousePos(m_mouse_x, m_mouse_y);
			}
			else
			{
				setMousePos(m_mouse_x, m_mouse_y);
				ShowCursor(true);
			}

			m_mouseLock = m_hwnd;
		}
	}
	
	void WinInputWindow::mouseCapture(bool capture)
	{
		if(capture)
			SetCapture(m_hwnd);
		else
			ReleaseCapture();
	}

	WinContext::WinContext(RenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen)
		: Context(renderSystem, initialize(name, width, height, fullScreen), make_object<WinInputWindow>())
		, m_render(as<WinRenderWindow>(*Context::m_renderWindow))
		, m_input(as<WinInputWindow>(*Context::m_inputWindow))
	{
		WindowHolder::instance().add(*this);

		//winSetHwnd(m_hwnd[0]);

		//bgfx::renderFrame();

	}

	WinContext::~WinContext()
	{
		WindowHolder::instance().remove(*this);
	}

	object_ptr<WinRenderWindow> WinContext::initialize(const string& name, int width, int height, bool fullScreen)
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

		return make_object<WinRenderWindow>(name, width, height);
	}

	WinRenderSystem::WinRenderSystem(const string& resourcePath)
		: RenderSystem(resourcePath, true)
	{}

	object_ptr<Context> WinRenderSystem::createContext(const string& name, int width, int height, bool fullScreen)
	{
		return make_object<WinContext>(*this, name, width, height, fullScreen);
	}

	LRESULT CALLBACK wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
	{
		WinContext* context = WindowHolder::instance().find(_hwnd);

		if(context == nullptr)
			return DefWindowProc(_hwnd, _id, _wparam, _lparam);

		WinRenderWindow& render = context->m_render;
		WinInputWindow& input = context->m_input;

		switch(_id)
		{
		case WM_DESTROY:
			break;
		case WM_QUIT:
		case WM_CLOSE:
			render.destroy();
			return 0;
		case WM_SIZING:
		{
			RECT& rect = *(RECT*)_lparam;
			uint32_t width = rect.right - rect.left - render.m_frameWidth;
			uint32_t height = rect.bottom - rect.top - render.m_frameHeight;

			// Recalculate size according to aspect ratio
			switch(_wparam)
			{
			case WMSZ_LEFT:
			case WMSZ_RIGHT:
			{
				float aspectRatio = 1.0f / render.m_aspectRatio;
				width = max(render.m_minWidth, width);
				height = uint32_t(float(width)*aspectRatio);
			}
			break;

			default:
			{
				float aspectRatio = render.m_aspectRatio;
				height = max(render.m_minHeight, height);
				width = uint32_t(float(height)*aspectRatio);
			}
			break;
			}

			// Recalculate position using different anchor points
			switch(_wparam)
			{
			case WMSZ_TOPLEFT:
				rect.left = rect.right - width - render.m_frameWidth;
				rect.top = rect.bottom - height - render.m_frameHeight;
				break;

			case WMSZ_TOP:
			case WMSZ_TOPRIGHT:
				rect.right = rect.left + width + render.m_frameWidth;
				rect.top = rect.bottom - height - render.m_frameHeight;
				break;

			case WMSZ_LEFT:
			case WMSZ_BOTTOMLEFT:
				rect.left = rect.right - width - render.m_frameWidth;
				rect.bottom = rect.top + height + render.m_frameHeight;
				break;

			default:
				rect.right = rect.left + width + render.m_frameWidth;
				rect.bottom = rect.top + height + render.m_frameHeight;
				break;
			}

			render.setSize(width, height);
		}
		return 0;

		case WM_SIZE:
		{
			uint32_t width = GET_X_LPARAM(_lparam);
			uint32_t height = GET_Y_LPARAM(_lparam);
			render.setSize(width, height);
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

			if(input.m_mouseLock)
			{
				mx -= input.m_mouse_x;
				my -= input.m_mouse_y;

				if(0 == mx && 0 == my)
				{
					break;
				}

				input.setMousePos(mx, my);
			}

			input.m_mouse->dispatchMouseMoved({ float(mx), float(my) });
		}
		break;

		case WM_MOUSEWHEEL:
		{
			POINT pt = { GET_X_LPARAM(_lparam), GET_Y_LPARAM(_lparam) };
			ScreenToClient(_hwnd, &pt);
			int32_t mx = pt.x;
			int32_t my = pt.y;
			input.m_mouse_z += GET_WHEEL_DELTA_WPARAM(_wparam) / WHEEL_DELTA;
			input.m_mouse->dispatchMouseWheeled({ float(mx), float(my) }, input.m_mouse_z);
		}
		break;

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			input.mouseCapture(true);
			int32_t mx = GET_X_LPARAM(_lparam);
			int32_t my = GET_Y_LPARAM(_lparam);
			input.m_mouse->dispatchMousePressed({ float(mx), float(my) }, mouseButton(_id));
		}
		break;

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			input.mouseCapture(false);
			int32_t mx = GET_X_LPARAM(_lparam);
			int32_t my = GET_Y_LPARAM(_lparam);
			input.m_mouse->dispatchMouseReleased({ float(mx), float(my) }, mouseButton(_id));
		}
		break;

		//case WM_LBUTTONDBLCLK:
		//case WM_MBUTTONDBLCLK:
		//case WM_RBUTTONDBLCLK:
		//break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			uint8_t modifiers = translateKeyModifiers();
			KeyCode key = translateKey(_wparam);
			printf("key down\n");
			input.m_keyboard->dispatchKeyPressed(key, '0');
		}
		break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			uint8_t modifiers = translateKeyModifiers();
			KeyCode key = translateKey(_wparam);

			/*if(Key::Print == key && 0x3 == ((uint32_t)(_lparam) >> 30))
			{
				// VK_SNAPSHOT doesn't generate keydown event. Fire on down event when previous
				// key state bit is set to 1 and transition state bit is set to 1.
				//
				// http://msdn.microsoft.com/en-us/library/windows/desktop/ms646280%28v=vs.85%29.aspx
				m_eventQueue.postKeyEvent(handle, key, modifiers, true);
			}*/

			printf("key released\n");
			input.m_keyboard->dispatchKeyReleased(key, '0');
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
