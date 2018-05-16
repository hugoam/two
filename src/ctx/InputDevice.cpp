//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ctx/InputDevice.h>

#include <ctx/InputEvent.h>
#include <ctx/ControlNode.h>

#include <algorithm>
#include <stdio.h>

namespace mud
{
	InputDevice::InputDevice(EventDispatcher& dispatcher)
		: m_dispatcher(dispatcher) // root_sheet.m_controller
	{}

	Keyboard::Keyboard(EventDispatcher& dispatcher)
		: InputDevice(dispatcher)
	{
		m_events.reserve(100);
	}

	InputModifier Keyboard::modifiers()
	{
		return InputModifier(0 | (m_shift ? uint32_t(InputModifier::Shift) : 0)
							   | (m_ctrl ? uint32_t(InputModifier::Ctrl) : 0)
							   | (m_alt ? uint32_t(InputModifier::Alt) : 0));
	}

	void Keyboard::dispatch_event(KeyEvent evt)
	{
		m_events.push_back(evt);
		m_dispatcher.dispatchEvent(m_events.back());
	}

	void Keyboard::key_char(KeyCode key, char c)
	{
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Stroked, key, c, InputModifier::None));
	}

	void Keyboard::key_pressed(KeyCode key, char c)
	{
		m_shift |= key == KC_LSHIFT || key == KC_RSHIFT;
		m_ctrl |= key == KC_LCONTROL || key == KC_RCONTROL;
		m_alt |= key == KC_LMENU || key == KC_RMENU;

		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Pressed, key, c, modifiers()));
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Stroked, key, c, modifiers()));
	}

	void Keyboard::key_released(KeyCode key, char c)
	{
		m_shift &= !(key == KC_LSHIFT || key == KC_RSHIFT);
		m_ctrl &= !(key == KC_LCONTROL || key == KC_RCONTROL);
		m_alt &= !(key == KC_LMENU || key == KC_RMENU);

		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Released, key, c, modifiers()));
	}

	void Keyboard::key_stroke(KeyCode key, char c)
	{
		dispatch_event(KeyEvent(DeviceType::Keyboard, EventType::Stroked, key, c, modifiers()));
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
		input_event.m_delta = input_event.m_pos - m_last_pos;
		//if(input_event.m_delta.x > 0 || input_event.m_delta.y > 0)
		//	printf("Mouse :: delta %i, %i\n", int(input_event.m_delta.x), int(input_event.m_delta.y));
		//input_event.m_modifiers = m_keyboard.modifiers();
		m_events.push_back(input_event);
		m_dispatcher.dispatchEvent(m_events.back());
		return m_events.back();
	}

	MouseEvent& Mouse::dispatch_secondary(MouseEvent input_event, ControlNode* pressed, vec2 pressed_pos)
	{
		input_event.m_pressed = pressed_pos;
		input_event.m_target = m_dispatcher.m_control_node.controlEvent(input_event);
		m_events.push_back(input_event);
		m_dispatcher.dispatchEvent(m_events.back(), pressed);
		return m_events.back();
	}

	MouseEvent& Mouse::heartbeat()
	{
		return dispatch_event(MouseEvent(DeviceType::Mouse, EventType::Heartbeat, m_last_pos));
	}

	void Mouse::moved(vec2 pos)
	{
		MouseEvent& mouse_event = dispatch_event(MouseEvent(DeviceType::Mouse, EventType::Moved, pos));
		m_last_pos = mouse_event.m_pos;

		for(MouseButton& button : m_buttons)
			button.moved(mouse_event);
	}

	void Mouse::wheeled(vec2 pos, float amount)
	{
		MouseEvent& mouse_event = dispatch_event(MouseEvent(DeviceType::MouseMiddle, EventType::Moved, pos, m_keyboard.modifiers()));
		mouse_event.m_deltaZ = amount;
	}

	MouseButton::MouseButton(Mouse& mouse, DeviceType deviceType)
		: InputDevice(mouse.m_dispatcher)
		, m_mouse(mouse)
		, m_deviceType(deviceType)
	{}

	void MouseButton::moved(MouseEvent& mouse_event)
	{
		const float threshold = 3.f;
		vec2 delta = mouse_event.m_pos - m_pressed_event.m_pos;

		if(m_dragging)
			this->drag_move(mouse_event);
		else if(m_pressed && (std::abs(delta.x) > threshold || std::abs(delta.y) > threshold))
			this->drag_start(mouse_event);
	}

	void MouseButton::pressed(vec2 pos, InputModifier modifiers)
	{
		MouseEvent& mouse_event = m_mouse.dispatch_event(MouseEvent(m_deviceType, EventType::Pressed, pos, modifiers));

		m_pressed = m_dispatcher.dispatchEvent(mouse_event);
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
		this->drag_move(mouse_event);
		//m_root_sheet.m_cursor.lock();

		m_dragging = true;
	}

	void MouseButton::drag_end(MouseEvent& mouse_event)
	{
		m_dragging = false;
		//m_root_sheet.m_cursor.unlock();
		this->drag_move(mouse_event);
		m_mouse.dispatch_secondary(MouseEvent(m_deviceType, EventType::DragEnded, mouse_event), m_pressed, m_pressed_event.m_pos);
	}

	void MouseButton::drag_move(MouseEvent& mouse_event)
	{
		m_mouse.dispatch_secondary(MouseEvent(m_deviceType, EventType::Dragged, mouse_event), m_pressed, m_pressed_event.m_pos);
	}

	void MouseButton::click(MouseEvent& mouse_event)
	{
		m_mouse.dispatch_secondary(MouseEvent(m_deviceType, EventType::Stroked, mouse_event), m_pressed, m_pressed_event.m_pos);
	}
}
