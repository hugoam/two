#include <two/infra.h>

module;
module two.ctx;

namespace two
{
    // Exported types
    template <> TWO_CTX_EXPORT Type& type<two::Key>() { static Type ty("Key", sizeof(two::Key)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::MouseButtonCode>() { static Type ty("MouseButtonCode", sizeof(two::MouseButtonCode)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::InputMod>() { static Type ty("InputMod", sizeof(two::InputMod)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::DeviceType>() { static Type ty("DeviceType", sizeof(two::DeviceType)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::EventType>() { static Type ty("EventType", sizeof(two::EventType)); return ty; }
    
    
    template <> TWO_CTX_EXPORT Type& type<two::RenderSystem>() { static Type ty("RenderSystem", sizeof(two::RenderSystem)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::Context>() { static Type ty("Context", sizeof(two::Context)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::InputEvent>() { static Type ty("InputEvent", sizeof(two::InputEvent)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::MouseEvent>() { static Type ty("MouseEvent", type<two::InputEvent>(), sizeof(two::MouseEvent)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::KeyEvent>() { static Type ty("KeyEvent", type<two::InputEvent>(), sizeof(two::KeyEvent)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::ControlNode>() { static Type ty("ControlNode", sizeof(two::ControlNode)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::Keyboard>() { static Type ty("Keyboard", sizeof(two::Keyboard)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::Mouse>() { static Type ty("Mouse", sizeof(two::Mouse)); return ty; }
}

module;
module two.ctx;

namespace two
{
	RenderSystem::RenderSystem(const string& resource_path, bool manual_render)
		: m_resource_path(resource_path)
		, m_manual_render(manual_render)
	{}

	Context::Context(RenderSystem& render_system, const string& title, const uvec2& size, bool fullscreen, bool main)
		: m_render_system(render_system)
		, m_resource_path(render_system.m_resource_path)
		, m_title(title)
		, m_size(size)
		, m_fb_size(size)
		, m_fullscreen(fullscreen)
		, m_is_main(main)
	{}

	Context::~Context()
	{}

}

module;
module two.ctx;

namespace two
{
	EventDispatcher::EventDispatcher(ControlNode* control_node)
		: m_control_node(*control_node)
	{
		m_event_batches.resize(100);
	}

	void EventDispatcher::update()
	{
		for(size_t i = 0; i < m_top; ++i)
		{
			m_event_batches[i].clear();

			if(m_event_batches[i].m_control_node)
			{
				m_event_batches[i].m_control_node->m_events = nullptr;
				m_event_batches[i].m_control_node = nullptr;
			}
		}

		m_top = 0;
	}

	void EventDispatcher::receive_event(InputEvent& event, ControlNode& receiver)
	{
		if(!receiver.m_events)
		{
			receiver.m_events = &m_event_batches[m_top++];
			receiver.m_events->m_control_node = &receiver;
		}

		receiver.m_events->m_events[event.m_deviceType][event.m_eventType] = &event;
		if(event.m_key != -1)
			receiver.m_events->m_keyed_events[event.m_deviceType][event.m_eventType][event.m_key] = &event;
	}

	ControlNode* EventDispatcher::dispatch_event(InputEvent& event, ControlNode* topReceiver)
	{
		event.m_receiver = topReceiver ? topReceiver : m_control_node.control_event(event);

		// @todo dispatch to all receivers from the lowest controller to the top : problem is declaration order is bottom-up so in the wrong order
		event.m_receiver->receive_event(event); // @kludge to call transform_event
		this->receive_event(event, *event.m_receiver);
		return event.m_receiver;
	}
}

module;
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
#ifndef USE_STL
module two.ctx;

namespace stl
{
	using namespace two;
	template class TWO_CTX_EXPORT vector<EventBatch>;
	template class TWO_CTX_EXPORT vector<KeyEvent>;
	template class TWO_CTX_EXPORT vector<MouseEvent>;
	template class TWO_CTX_EXPORT unordered_map<int, InputEvent*>;
}
#endif
