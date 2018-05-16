//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui/Controller/Controller.h>

#include <ui/Structs/RootSheet.h>

#include <ctx/InputDevice.h>

namespace mud
{
	EventDispatch::EventDispatch()
	{}

	void EventDispatch::process(Widget& widget)
	{
		if(!widget.m_events) return;

		KeyEvent* key_down_event = static_cast<KeyEvent*>(widget.m_events->m_events[size_t(DeviceType::Keyboard)][size_t(EventType::Pressed)]);
		if(key_down_event)
		{
			if(m_key_down_handlers.find(key_down_event->m_code) != m_key_down_handlers.end())
				m_key_down_handlers[key_down_event->m_code]();
		}

		KeyEvent* key_up_event = static_cast<KeyEvent*>(widget.m_events->m_events[size_t(DeviceType::Keyboard)][size_t(EventType::Released)]);
		if(key_up_event)
		{
			if(m_key_up_handlers.find(key_up_event->m_code) != m_key_up_handlers.end())
				m_key_up_handlers[key_up_event->m_code]();
		}
	}
}
