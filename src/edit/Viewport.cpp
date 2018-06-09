//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.edit;
#else
#include <infra/Vector.h>
#include <uio/Edit/Section.h>
#include <gfx/Item.h>
#include <edit/Types.h>
#include <edit/Viewport.h>
#include <edit/Viewer/Viewer.h>
#include <edit/EditContext.h>
#endif

namespace mud
{
	void viewport_picker(Viewer& viewer, Widget& widget, std::vector<Ref>& selection)
	{
		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			auto callback = [&](Item* item) { vector_select(selection, item->m_node.m_object); };
			viewer.pick_point(mouse_event.m_relative, callback, ITEM_SELECTABLE);
		}

		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseRight, EventType::Stroked))
		{
			//Entity* entity = pick_entity(viewer, mouse_event.m_relative, ITEM_SELECTABLE | ITEM_WORLD_GEOMETRY);
			//context_menu(viewer.m_vision.m_user.m_selector, *entity);
		}
	}

	Viewer& scene_viewport(Widget& parent, Scene& scene, Camera& camera, std::vector<Ref>& selection)
	{
		Viewer& viewer = parent.child_args<Viewer, Scene&>(scene);
		if(viewer.once())
		{
			UNUSED(camera);
			//scene.m_cameras.push_back({ &camera, &viewer.m_camera });
			//viewer.m_controller = make_unique<RTSCameraController>(viewer, camera);
		}

		//viewer.m_controller->process(viewer);
		viewport_picker(viewer, viewer, selection);
		return viewer;
	}
}
