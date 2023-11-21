//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ctx;


namespace two
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
		, m_buttons{ { *this, DeviceType::MouseLeft },
					 { *this, DeviceType::MouseRight },
					 { *this, DeviceType::MouseMiddle } }
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
		MouseEvent& event = dispatch_event(MouseEvent(DeviceType::Mouse, EventType::Heartbeat, m_pos));
		m_last_pos = m_pos;
		m_pos = event.m_pos;
		for(MouseButton& button : m_buttons)
			if(button.m_dragging)
				button.drag(event);
		return event;
	}

	void Mouse::moved(vec2 pos, vec2* offset)
	{
		m_pos = offset ? m_pos + *offset : pos;

		MouseEvent& event = dispatch_event(MouseEvent(DeviceType::Mouse, EventType::Moved, pos));
		
		const float drag_threshold = 3.f;

		for(MouseButton& button : m_buttons)
			if(button.m_pressed && !button.m_dragging)
			{
				vec2 delta = event.m_pos - button.m_pressed_event.m_pos;
				if(abs(delta.x) > drag_threshold || abs(delta.y) > drag_threshold)
					button.drag_start(event);
			}
	}

	void Mouse::wheeled(vec2 pos, float amount)
	{
		MouseEvent& event = dispatch_event(MouseEvent(DeviceType::MouseMiddle, EventType::Moved, pos, m_keyboard.modifiers()));
		event.m_deltaZ = amount;
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
		MouseEvent& event = m_mouse.dispatch_event(MouseEvent(m_deviceType, EventType::Pressed, pos, modifiers));

		m_pressed = m_dispatcher.dispatch_event(event);
		m_pressed_event = event;
	}

	void MouseButton::pressed(vec2 pos)
	{
		this->pressed(pos, m_mouse.m_keyboard.modifiers());
	}

	void MouseButton::released(vec2 pos)
	{
		MouseEvent& event = m_mouse.dispatch_event(MouseEvent(m_deviceType, EventType::Released, pos, m_pressed_event.m_modifiers));

		if(m_dragging)
			this->drag_end(event);
		else
			this->click(event);

		m_pressed = nullptr;
	}

	void MouseButton::drag_start(MouseEvent& mouse_event)
	{
		m_mouse.dispatch_secondary(MouseEvent(m_deviceType, EventType::DragStarted, mouse_event), m_pressed, m_pressed_event.m_pos);

		this->drag(mouse_event);
		//m_ui.m_cursor.lock();
		m_dragging = true;
	}

	void MouseButton::drag_end(MouseEvent& mouse_event)
	{
		m_dragging = false;
		//m_ui.m_cursor.unlock();
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

	InputContext::InputContext()
		: EventDispatcher(this)
		, m_keyboard(*this)
		, m_mouse(*this, m_keyboard)
	{}

	void InputContext::init(Context& context)
	{
		context.init_input(m_mouse, m_keyboard);
	}

	void InputContext::begin_frame()
	{}

	void InputContext::end_frame()
	{
		m_mouse.m_events.clear();
		m_keyboard.m_events.clear();

		EventDispatcher::update();
	}

	ControlNode* InputContext::control_event(InputEvent& event)
	{
		UNUSED(event);
		return this;
	}

	void InputContext::receive_event(InputEvent& inputEvent)
	{
		UNUSED(inputEvent);
	}

	KeyEvent ControlNode::key_event(Key code, EventType event_type, InputMod modifier)
	{
		if(!m_events) return KeyEvent();
		KeyEvent* event = static_cast<KeyEvent*>(m_events->m_keyed_events[DeviceType::Keyboard][event_type][int(code)]);
		return event && fits_modifier(event->m_modifiers, modifier) ? *event : KeyEvent();
	}

	MouseEvent ControlNode::mouse_event(DeviceType device, EventType event_type, InputMod modifier, bool consume)
	{
		if(!m_events) return MouseEvent();
		MouseEvent* event = static_cast<MouseEvent*>(m_events->m_events[device][event_type]);
		if(event && fits_modifier(event->m_modifiers, modifier))
		{
			MouseEvent result = *event;;
			if(consume)
				event->consume(*this);
			return result;
		}
		return MouseEvent();
	}
}
