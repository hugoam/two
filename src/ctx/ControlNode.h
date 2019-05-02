//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stdint.h>
#include <ctx/Forward.h>
#include <ctx/InputEvent.h>

namespace two
{
	export_ struct ModalControl
	{
		ControlNode* m_parent = nullptr;
		ControlNode* m_modal = nullptr;
		uint32_t m_mask = 0;
	};

	export_ class refl_ TWO_CTX_EXPORT ControlNode
	{
	public:
		virtual ControlNode* control_event(InputEvent& event) = 0;
		virtual ControlNode* propagate_event(InputEvent& inputEvent) = 0;
		virtual void receive_event(InputEvent& inputEvent) = 0;

		virtual void take_modal(uint32_t device_filter = uint32_t(DeviceMask::All)) = 0;
		virtual void yield_modal() = 0;

		EventBatch* m_events = nullptr;
		ModalControl m_control = {};
	};
}
