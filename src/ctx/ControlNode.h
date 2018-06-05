//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Limits.h>
#endif
#include <ctx/Generated/Forward.h>

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

	export_ class MUD_CTX_EXPORT ControlNode
	{
	public:
		ControlNode() {}
		virtual ControlNode* controlEvent(InputEvent& inputEvent) = 0;
		virtual ControlNode* propagateEvent(InputEvent& inputEvent) = 0;
		virtual void receiveEvent(InputEvent& inputEvent) = 0;

		EventBatch* m_events = nullptr;
		ModalControl m_control = {};
	};
}
