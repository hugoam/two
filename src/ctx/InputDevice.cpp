//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <algorithm>
#include <cstdio>
#endif

#ifdef MUD_MODULES
module mud.ctx;
#else
#include <ctx/InputDevice.h>
#include <ctx/InputEvent.h>
#include <ctx/ControlNode.h>
#endif


namespace mud
{
	InputDevice::InputDevice(EventDispatcher& dispatcher)
		: m_dispatcher(dispatcher) // ui.m_controller
	{}

	Keyboard::Keyboard(EventDispatcher& dispatcher)
		: InputDevice(dispatcher)
	{
		m_events.reserve(100);
	}

	void Keyboard::update_modifiers(bool shift, bool ctrl, bool alt)
	{
		m_shift = shift;
		m_ctrl = ctrl;
		m_alt = alt;
	}

	InputMod Keyboard::modifiers()
	{
		return InputMod(0 | (m_shift ? uint32_t(InputMod::Shift) : 0)
						  | (m_ctrl  ? uint32_t(InputMod::Ctrl)  : 0)
						  | (m_alt   ? uint32_t(InputMod::Alt)   : 0));
	}

	void Keyboard::dispatch_event(KeyEvent evt)
	{
		m_events.push_back(evt);
		m_dispatcher.dispatch_event(m_events.back());
	}

	void Keyboard::key_char(char c)
	{
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Stroked, Key::Unassigned, c, InputMod::None));
	}

	void Keyboard::key_pressed(Key key, Key translated)
	{
		m_shift |= key == Key::LeftShift || key == Key::RightShift;
		m_ctrl |= key == Key::LeftControl || key == Key::RightControl;
		m_alt |= key == Key::LeftAlt || key == Key::RightAlt;

		this->key_pressed(key, translated, modifiers());
	}

	void Keyboard::key_pressed(Key key, Key translated, InputMod mods)
	{
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Pressed, key, char(0), mods));
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Pressed, translated, char(0), mods));
	}

	void Keyboard::key_released(Key key, Key translated)
	{
		m_shift &= !(key == Key::LeftShift || key == Key::RightShift);
		m_ctrl &= !(key == Key::LeftControl || key == Key::RightControl);
		m_alt &= !(key == Key::LeftAlt || key == Key::RightAlt);

		this->key_released(key, translated, modifiers());
	}

	void Keyboard::key_released(Key key, Key translated, InputMod mods)
	{
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Released, key, char(0), mods));
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Released, translated, char(0), mods));
	}

	void Keyboard::key_stroke(Key key, Key translated)
	{
		this->key_stroke(key, translated, modifiers());
	}

	void Keyboard::key_stroke(Key key, Key translated, InputMod mods)
	{
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Stroked, key, char(0), mods));
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Stroked, translated, char(0), mods));
	}

	Mouse::Mouse(EventDispatcher& dispatcher, Keyboard& keyboard)
		: InputDevice(dispatcher)
		, m_keyboard(keyboard)
		, m_last_pos(0.f, 0.f)
		, m_buttons{ { MouseButton{ *this, DeviceType::MouseLeft },
					   MouseButton{ *this, DeviceType::MouseRight },
					   MouseButton{ *this, DeviceType::MouseMiddle } } }
	{
		m_events.reserve(100);
	}

	MouseEvent& Mouse::dispatch_event(MouseEvent input_event)
	{
		input_event.m_delta = m_pos - m_last_pos;
		m_events.push_back(input_event);
		m_dispatcher.dispatch_event(m_events.back());
		return m_events.back();
	}

	MouseEvent& Mouse::dispatch_secondary(MouseEvent input_event, ControlNode* pressed, vec2 pressed_pos, ControlNode* target)
	{
		input_event.m_pressed = pressed_pos;
		input_event.m_target = target;
		m_events.push_back(input_event);
		m_dispatcher.dispatch_event(m_events.back(), pressed);
		return m_events.back();
	}

	MouseEvent& Mouse::heartbeat()
	{
		MouseEvent& mouse_event = dispatch_event(MouseEvent(DeviceType::Mouse, EventType::Heartbeat, m_pos));
		m_last_pos = m_pos;
		m_pos = mouse_event.m_pos;
		for(MouseButton& button : m_buttons)
			if(button.m_dragging)
				button.drag(mouse_event);
		return mouse_event;
	}

	void Mouse::moved(vec2 pos, vec2* offset)
	{
		m_pos = offset ? m_pos + *offset : pos;

		MouseEvent& mouse_event = dispatch_event(MouseEvent(DeviceType::Mouse, EventType::Moved, pos));
		
		const float drag_threshold = 3.f;

		for(MouseButton& button : m_buttons)
			if(button.m_pressed && !button.m_dragging)
			{
				vec2 delta = mouse_event.m_pos - button.m_pressed_event.m_pos;
				if (std::abs(delta.x) > drag_threshold || std::abs(delta.y) > drag_threshold)
					button.drag_start(mouse_event);
			}
	}

	void Mouse::wheeled(vec2 pos, float amount)
	{
		MouseEvent& mouse_event = dispatch_event(MouseEvent(DeviceType::MouseMiddle, EventType::Moved, pos, m_keyboard.modifiers()));
		mouse_event.m_deltaZ = amount;
	}

	void Mouse::fix_press(ControlNode& node)
	{
		for(MouseButton& button : m_buttons)
			button.m_pressed = &node;
	}

	MouseButton::MouseButton(Mouse& mouse, DeviceType deviceType)
		: InputDevice(mouse.m_dispatcher)
		, m_mouse(mouse)
		, m_deviceType(deviceType)
	{}

	void MouseButton::pressed(vec2 pos, InputMod modifiers)
	{
		MouseEvent& mouse_event = m_mouse.dispatch_event(MouseEvent(m_deviceType, EventType::Pressed, pos, modifiers));

		m_pressed = m_dispatcher.dispatch_event(mouse_event);
		m_pressed_event = mouse_event;
	}

	void MouseButton::pressed(vec2 pos)
	{
		this->pressed(pos, m_mouse.m_keyboard.modifiers());
	}

	void MouseButton::released(vec2 pos)
	{
		MouseEvent& mouse_event = m_mouse.dispatch_event(MouseEvent(m_deviceType, EventType::Released, pos, m_pressed_event.m_modifiers));

		if(m_dragging)
			this->drag_end(mouse_event);
		else
			this->click(mouse_event);

		m_pressed = nullptr;
	}

	void MouseButton::drag_start(MouseEvent& mouse_event)
	{
		m_mouse.dispatch_secondary(MouseEvent(m_deviceType, EventType::DragStarted, mouse_event), m_pressed, m_pressed_event.m_pos);

		this->drag(mouse_event);
		//m_root_sheet.m_cursor.lock();
		m_dragging = true;
	}

	void MouseButton::drag_end(MouseEvent& mouse_event)
	{
		m_dragging = false;
		//m_root_sheet.m_cursor.unlock();
		this->drag(mouse_event);

		MouseEvent& drop = m_mouse.dispatch_event(MouseEvent(m_deviceType, EventType::Dropped, mouse_event.m_pos, m_pressed_event.m_modifiers));
		m_mouse.dispatch_secondary(MouseEvent(m_deviceType, EventType::DragEnded, mouse_event), m_pressed, m_pressed_event.m_pos, drop.m_receiver);
	}

	void MouseButton::drag(MouseEvent& mouse_event)
	{
		MouseEvent& drop = m_mouse.dispatch_event(MouseEvent(m_deviceType, EventType::DraggedTarget, mouse_event.m_pos, m_pressed_event.m_modifiers));
		m_mouse.dispatch_secondary(MouseEvent(m_deviceType, EventType::Dragged, mouse_event), m_pressed, m_pressed_event.m_pos, drop.m_receiver);
	}

	void MouseButton::click(MouseEvent& mouse_event)
	{
		m_mouse.dispatch_secondary(MouseEvent(m_deviceType, EventType::Stroked, mouse_event), m_pressed, m_pressed_event.m_pos);
	}
}
