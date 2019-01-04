//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ctx/Forward.h>
#include <ctx/InputEvent.h>

#ifndef MUD_CPP_20
#include <cstdint>
#endif

namespace mud
{
	export_ struct ModalControl
	{
		ControlNode* m_parent;
		ControlNode* m_modal;
		uint32_t m_mask;

		ModalControl() : m_parent(nullptr), m_modal(nullptr), m_mask(0) {}
		ModalControl(ControlNode* parent, ControlNode* modal, uint32_t mask = UINT32_MAX) : m_parent(parent), m_modal(modal), m_mask(mask) {}
	};

	export_ class refl_ MUD_CTX_EXPORT ControlNode
	{
	public:
		ControlNode() {}

		virtual ControlNode* control_event(InputEvent& event) = 0;
		virtual ControlNode* propagate_event(InputEvent& inputEvent) = 0;
		virtual void receive_event(InputEvent& inputEvent) = 0;

		virtual void take_modal(uint32_t device_filter = uint32_t(DeviceMask::All)) = 0;
		virtual void yield_modal() = 0;

		EventBatch* m_events = nullptr;
		ModalControl m_control = {};
	};
}
