//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <math/Vec.h>
#endif
#include <ctx/Forward.h>
#include <ctx/KeyCode.h>
#include <ctx/InputDispatcher.h>

namespace mud
{
	export_ class MUD_CTX_EXPORT InputDevice
	{
	public:
		InputDevice(EventDispatcher& dispatcher);

		EventDispatcher& m_dispatcher;
	};

	export_ class refl_ MUD_CTX_EXPORT Keyboard : public InputDevice
	{
	public:
		Keyboard(EventDispatcher& dispatcher);

		void dispatch_event(KeyEvent evt);

		void update_modifiers(bool shift, bool ctrl, bool alt);
		InputMod modifiers();

		void key_pressed(Key key, Key translated);
		void key_pressed(Key key, Key translated, InputMod mods);
		void key_released(Key key, Key translated);
		void key_released(Key key, Key translated, InputMod mods);
		void key_stroke(Key key, Key translated);
		void key_stroke(Key key, Key translated, InputMod mods);
		void key_char(char c);

		bool m_shift = false;
		bool m_ctrl = false;
		bool m_alt = false;

		vector<KeyEvent> m_events;
	};

	export_ class MUD_CTX_EXPORT MouseButton : public InputDevice
	{
	public:
		MouseButton(Mouse& mouse, DeviceType deviceType);

		void pressed(vec2 pos);
		void pressed(vec2 pos, InputMod modifiers);
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

	export_ class refl_ MUD_CTX_EXPORT Mouse : public InputDevice
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
		MouseButton m_buttons[3];

		vector<MouseEvent> m_events;
	};
}
