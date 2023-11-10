//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/map.h>
#include <type/Unique.h>
#include <stl/table.h>
#endif
#include <ctx/Forward.h>
#include <ctx/KeyCode.h>
#include <ctx/InputEvent.h>

namespace two
{
	export_ template <class T>
	struct EventMap
	{
		table<DeviceType, table<EventType, T>> m_events = {};
#ifdef TWO_MODULES
		table<DeviceType, table<EventType, unordered_map<int, T>>> m_keyed_events = {};
#else
		table<DeviceType, table<EventType, map<int, T>>> m_keyed_events = {};
#endif

		void clear() { *this = {}; }
	};

	export_ struct TWO_CTX_EXPORT EventBatch : public EventMap<InputEvent*>
	{
		ControlNode* m_control_node = nullptr;
	};

	export_ class TWO_CTX_EXPORT EventDispatcher
	{
	public:
		EventDispatcher(ControlNode* control_node);

		void update();

		ControlNode* dispatch_event(InputEvent& event, ControlNode* top_receiver = nullptr);
		void receive_event(InputEvent& event, ControlNode& receiver);

		ControlNode& m_control_node;
		vector<EventBatch> m_event_batches;
		size_t m_top = 0;
	};
}
