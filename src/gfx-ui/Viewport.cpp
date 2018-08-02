//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx.ui;
#else
#include <infra/Vector.h>
#include <uio/Edit/Section.h>
#include <gfx/Item.h>
#include <gfx-ui/Types.h>
#include <gfx-ui/Viewport.h>
#include <gfx-ui/Viewer.h>
#endif

namespace mud
{
	void viewport_picker(Viewer& viewer, Widget& widget, std::vector<Ref>& selection)
	{
		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::Mouse, EventType::Moved, InputModifier::None, false))
		{
			auto callback = [&](Item* item) { viewer.m_hovered = item != nullptr ? item->m_node.m_object : Ref(); };
			viewer.picker(0).pick_point(viewer.m_viewport, mouse_event.m_relative, callback, ITEM_SELECTABLE);
		}

		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			if(viewer.m_hovered)
				vector_select(selection, viewer.m_hovered);
		}

		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseRight, EventType::Stroked))
		{
			//Entity* entity = pick_entity(viewer, mouse_event.m_relative, ITEM_SELECTABLE | ITEM_WORLD_GEOMETRY);
			//context_menu(viewer.m_vision.m_user.m_selector, *entity);
		}
	}

	Viewer& scene_viewport(Widget& parent, Scene& scene, Camera& camera, std::vector<Ref>& selection)
	{
		Viewer& viewer = parent.suba<Viewer, Scene&>(scene);
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
