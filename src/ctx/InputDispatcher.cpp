//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ctx;

namespace two
{
	EventDispatcher::EventDispatcher()
	{
		m_received.reserve(100);
	}

	void EventDispatcher::update()
	{
		m_received.clear();
	}

	ControlId EventDispatcher::dispatch_event(InputEvent& event, ControlId top_receiver)
	{
		event.m_receiver = top_receiver ? top_receiver : this->route(event);

		// @todo dispatch to all receivers from the lowest controller to the top : problem is declaration order is bottom-up so in the wrong order
		this->receive(event, event.m_receiver); // @kludge to call transform_event
		m_received.push_back({ event.m_receiver, &event });
		return event.m_receiver;
	}

	InputEvent* EventDispatcher::received(ControlId receiver, DeviceType device, EventType type)
	{
		for(size_t i = m_received.size(); i-- > 0;)
		{
			const Received& received = m_received[i];
			if(received.m_receiver == receiver && received.m_event->m_deviceType == device && received.m_event->m_eventType == type)
				return received.m_event;
		}
		return nullptr;
	}

	InputEvent* EventDispatcher::received(ControlId receiver, DeviceType device, EventType type, int key)
	{
		for(size_t i = m_received.size(); i-- > 0;)
		{
			const Received& received = m_received[i];
			if(received.m_receiver == receiver && received.m_event->m_deviceType == device && received.m_event->m_eventType == type
			&& received.m_event->m_key == key)
				return received.m_event;
		}
		return nullptr;
	}

	void EventDispatcher::forget(ControlId receiver)
	{
		remove_if(m_received, [&](const Received& received) { return received.m_receiver == receiver; });
	}
}
