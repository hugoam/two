//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
#else
#include <ui/Controller/Controller.h>
#include <ui/UiRoot.h>
#include <ctx/InputDevice.h>
#endif

namespace two
{
	EventDispatch::EventDispatch()
	{}

	void EventDispatch::process(Widget& widget)
	{
		if(!widget.m_events) return;

		KeyEvent* key_down_event = static_cast<KeyEvent*>(widget.m_events->m_events[DeviceType::Keyboard][EventType::Pressed]);
		if(key_down_event)
		{
			if(m_key_down_handlers.find(key_down_event->m_code) != m_key_down_handlers.end())
				m_key_down_handlers[key_down_event->m_code]();
		}

		KeyEvent* key_up_event = static_cast<KeyEvent*>(widget.m_events->m_events[DeviceType::Keyboard][EventType::Released]);
		if(key_up_event)
		{
			if(m_key_up_handlers.find(key_up_event->m_code) != m_key_up_handlers.end())
				m_key_up_handlers[key_up_event->m_code]();
		}
	}
}
