//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/map.h>
#include <type/Unique.h>
#include <infra/EnumArray.h>
#endif
#include <ctx/Forward.h>
#include <ctx/KeyCode.h>
#include <ctx/InputEvent.h>

namespace mud
{
	export_ template <class T>
	struct EventMap
	{
		enum_array<DeviceType, enum_array<EventType, T>> m_events = {};
		enum_array<DeviceType, enum_array<EventType, map<int, T>>> m_keyed_events = {};

		void clear() { *this = {}; }
	};

	export_ struct MUD_CTX_EXPORT EventBatch : public EventMap<InputEvent*>
	{
		ControlNode* m_control_node = nullptr;
	};

	export_ class MUD_CTX_EXPORT EventDispatcher
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
