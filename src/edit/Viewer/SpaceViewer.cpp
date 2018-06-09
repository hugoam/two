//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.edit;
#else
#include <ctx/InputDevice.h>
#include <gfx/Camera.h>
#include <gfx/Item.h>
#include <edit/Viewer/SpaceViewer.h>
#include <edit/Viewer/SpaceSheet.h>
#endif

namespace mud
{
	SpaceViewport::SpaceViewport(Widget* parent, void* identity, Scene& scene)
		: Viewer(parent, identity, scene)
	{}

	ControlNode* SpaceViewport::controlEvent(InputEvent& inputEvent)
	{
		if(inputEvent.m_deviceType < DeviceType::Mouse)
			return this;

		//MouseEvent& mouse_event = static_cast<MouseEvent&>(inputEvent);
		//Item* item = this->pick_point(mouse_event.m_relative, ITEM_UI);
		//return item ? &val<SpaceSheet>(item->m_node.m_object) : m_parent;
		return nullptr;
	}
}
