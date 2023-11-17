//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.gfx.ui;

namespace two
{
	SpaceViewport::SpaceViewport(Widget* parent, void* identity, Scene& scene)
		: Viewer(parent, identity, scene)
	{}

	ControlNode* SpaceViewport::control_event(InputEvent& inputEvent)
	{
		if(inputEvent.m_deviceType < DeviceType::Mouse)
			return this;

		//MouseEvent& event = static_cast<MouseEvent&>(inputEvent);
		//Item* item = this->pick_point(event.m_relative, ItemFlag::Ui);
		//return item ? &val<SpaceSheet>(item->m_node->m_object) : m_parent;
		return nullptr;
	}
}
