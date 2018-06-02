//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#else
#include <cstdio>
#endif

#ifdef MUD_MODULES
module mud.ctx;
#else
#include <ctx/InputDispatcher.h>
#include <ctx/InputDevice.h>
#include <ctx/ControlNode.h>
#endif

namespace mud
{
	EventDispatcher::EventDispatcher(ControlNode* control_node)
		: m_control_node(*control_node)
	{
		m_event_batches.reserve(100);
	}

	void EventDispatcher::update()
	{
		for(EventBatch& event_batch : m_event_batches)
			event_batch.m_control_node->m_events = nullptr;

		m_event_batches.clear();
	}

	void EventDispatcher::receiveEvent(InputEvent& event, ControlNode& receiver)
	{
		if(!receiver.m_events)
		{
			m_event_batches.emplace_back(receiver);
			receiver.m_events = &m_event_batches.back();
		}

		receiver.m_events->event(event.m_deviceType, event.m_eventType) = &event;
		if(event.m_key != -1)
			receiver.m_events->event(event.m_deviceType, event.m_eventType, event.m_key) = &event;
	}

	ControlNode* EventDispatcher::dispatchEvent(InputEvent& event, ControlNode* topReceiver)
	{
		event.m_receiver = topReceiver ? topReceiver : m_control_node.controlEvent(event);

		// @todo dispatch to all receivers from the lowest controller to the top : problem is declaration order is bottom-up so in the wrong order
		event.m_receiver->receiveEvent(event); // @kludge to call transformEvent
		this->receiveEvent(event, *event.m_receiver);
		return event.m_receiver;
	}
}
