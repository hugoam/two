//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Unique.h>
#include <obj/EnumArray.h>
#endif
#include <ctx/Generated/Forward.h>
#include <ctx/KeyCode.h>
#include <ctx/InputEvent.h>

#ifndef MUD_CPP_20
#include <vector>
#include <map>
#endif

namespace mud
{
	export_ template <class T_Element>
	struct EventMap
	{
		EventMap() { m_events = {}; m_keyed_events = {}; }
		enum_array<DeviceType, enum_array<EventType, T_Element>> m_events;
		enum_array<DeviceType, enum_array<EventType, std::map<int, T_Element>>> m_keyed_events;

		T_Element& event(DeviceType device_type, EventType event_type) { return m_events[size_t(device_type)][size_t(event_type)]; }
		T_Element& event(DeviceType device_type, EventType event_type, int key) { return m_keyed_events[size_t(device_type)][size_t(event_type)][key]; }
	};

	export_ struct MUD_CTX_EXPORT EventBatch : public EventMap<InputEvent*>
	{
		ControlNode* m_control_node;
		//std::vector<InputEvent*> m_events;
		//EventMap<InputEvent*> m_events;

		EventBatch(ControlNode& control_node) : m_control_node(&control_node) {}
	};

	export_ class MUD_CTX_EXPORT EventDispatcher
	{
	public:
		EventDispatcher(ControlNode* control_node);

		void update();

		ControlNode* dispatchEvent(InputEvent& inputEvent, ControlNode* topReceiver = nullptr);
		void receiveEvent(InputEvent& inputEvent, ControlNode& receiver);

		ControlNode& m_control_node;
		std::vector<EventBatch> m_event_batches;
	};
}
