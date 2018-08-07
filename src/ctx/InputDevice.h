//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#endif
#include <ctx/Forward.h>
#include <ctx/KeyCode.h>
#include <ctx/InputDispatcher.h>

#ifndef MUD_CPP_20
#include <vector>
#include <array>
#endif

namespace mud
{
	export_ class MUD_CTX_EXPORT InputDevice
	{
	public:
		InputDevice(EventDispatcher& dispatcher);

		EventDispatcher& m_dispatcher;
	};

	export_ class MUD_CTX_EXPORT Keyboard : public InputDevice
	{
	public:
		Keyboard(EventDispatcher& dispatcher);

		void dispatch_event(KeyEvent evt);

		InputModifier modifiers();

		void key_pressed(Key key, char c);
		void key_released(Key key, char c);
		void key_stroke(Key key, char c);
		void key_char(Key key, char c);

		bool m_shift = false;
		bool m_ctrl = false;
		bool m_alt = false;

		std::vector<KeyEvent> m_events;
	};

	export_ class MUD_CTX_EXPORT MouseButton : public InputDevice
	{
	public:
		MouseButton(Mouse& mouse, DeviceType deviceType);

		void pressed(vec2 pos);
		void pressed(vec2 pos, InputModifier modifiers);
		void released(vec2 pos);

		void drag_start(MouseEvent& mouse_event);
		void drag_end(MouseEvent& mouse_event);
		void drag(MouseEvent& mouse_event);
		void click(MouseEvent& mouse_event);

		Mouse& m_mouse;
		DeviceType m_deviceType;

		ControlNode* m_pressed = nullptr;
		bool m_dragging = false;

		MouseEvent m_pressed_event = {};
	};

	export_ class MUD_CTX_EXPORT Mouse : public InputDevice
	{
	public:
		Mouse(EventDispatcher& dispatcher, Keyboard& keyboard);

		MouseEvent& dispatch_event(MouseEvent evt);
		MouseEvent& dispatch_secondary(MouseEvent evt, ControlNode* pressed, vec2 pressed_pos, ControlNode* target = nullptr);

		MouseEvent& heartbeat();
		void moved(vec2 pos, vec2* offset = nullptr);
		void wheeled(vec2 pos, float amount);

		void fix_press(ControlNode& node);

	public:
		Keyboard& m_keyboard;
		vec2 m_pos;
		vec2 m_last_pos;
		std::array<MouseButton, 3> m_buttons;

		std::vector<MouseEvent> m_events;
	};
}
