//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	EventDispatch::EventDispatch()
	{}

	void EventDispatch::process(Widget& widget)
	{
		KeyEvent* key_down_event = static_cast<KeyEvent*>(widget.ui().received(widget.control_id(), DeviceType::Keyboard, EventType::Pressed));
		if(key_down_event)
		{
			if(m_key_down_handlers.find(key_down_event->m_code) != m_key_down_handlers.end())
				m_key_down_handlers[key_down_event->m_code]();
		}

		KeyEvent* key_up_event = static_cast<KeyEvent*>(widget.ui().received(widget.control_id(), DeviceType::Keyboard, EventType::Released));
		if(key_up_event)
		{
			if(m_key_up_handlers.find(key_up_event->m_code) != m_key_up_handlers.end())
				m_key_up_handlers[key_up_event->m_code]();
		}
	}
}
