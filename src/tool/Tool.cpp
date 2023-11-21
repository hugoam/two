//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.tool;

namespace two
{
	Tool::Tool(ToolContext& context, cstring name, Type& type)
		: m_type(type)
		, m_context(context)
		, m_name(name)
		, m_state(ToolState::Inactive)
	{}

	void Tool::add_option(object<ToolOption> option)
	{
		UNUSED(option);
	}

	void Tool::commit(object<EditorAction> action)
	{
		action->apply();
		m_context.m_action_stack->push(move(action));
	}

	void Tool::activate()
	{
		m_state = ToolState::Active;
	}

	void Tool::deactivate()
	{
		m_state = ToolState::Inactive;
	}

	ViewportTool::ViewportTool(ToolContext& context, cstring name, Type& type)
		: Tool(context, name, type)
	{}

	vector<Transform*> ViewportTool::gather_transforms(span<Ref> objects)
	{
		vector<Transform*> transforms;
		for(Ref object : objects)
		{
			Var transform;
			if(convert(Var(object), type<Transform>(), transform))
				transforms.push_back(&val<Transform>(transform));
		}
		return transforms;
	}

	SpatialTool::SpatialTool(ToolContext& context, cstring name, Type& type)
		: ViewportTool(context, name, type)
	{}

	Colour gizmo_colour(float hue, bool active)
	{
		return Colour::hsl(hue, active ? 0.9f : 0.6f, active ? 0.5f : 0.3f);
	}

	vec3 gizmo_grab_linear(Viewer& viewer, const Transform& space, Axis axis)
	{
		vec3 direction = space.m_rotation * to_vec3(axis);
		vec3 normal = space.m_rotation * c_tangents[axis];
		vec3 projected = plane_segment_intersection(Plane(space.m_position, space.m_position + direction, space.m_position + normal), to_segment(viewer.mouse_ray()));
		return nearest_point_on_line(space.m_position, direction, projected);
	}

	vec3 gizmo_grab_planar(Viewer& viewer, const Transform& space, Axis normal)
	{
		Plane plane(space.m_position, space.m_rotation * to_vec3(normal));
		return plane_segment_intersection(plane, to_segment(viewer.mouse_ray()));
	}

	TransformAction::TransformAction(span<Transform*> targets)
		: m_targets(to_vector(targets))
	{}

	void TransformAction::apply()
	{
		for(Transform* transform : m_targets)
			this->apply(*transform);
	}

	void TransformAction::undo()
	{
		for(Transform* transform : m_targets)
			this->undo(*transform);
	}

	TransformTool::TransformTool(ToolContext& context, cstring name, Type& type)
		: SpatialTool(context, name, type)
	{}

	TransformTool::~TransformTool()
	{}

	bool TransformTool::enabled(span<Ref> selection)
	{
		for(Ref object : selection)
			if(this->test_target(object))
				return true;
		return false;
	}

	void TransformTool::paint(Gnode& parent)
	{
		Gnode& self = gfx::node(parent, m_transform);

		for(auto& gizmo : m_gizmos)
		{
			gizmo->m_handle = gizmo->draw_handle(self);
			gizmo->draw_gizmo(self, &*gizmo == m_current);
		}

#ifdef TWO_DEBUG_TRANSFORM_POINTS
		Gnode& start = gfx::node(parent, m_grab_start);
		gfx::shape(start, Sphere(0.1f), Symbol(Colour::Pink, Colour::None, true));

		Gnode& end = gfx::node(parent, m_grab_end);
		gfx::shape(end, Sphere(0.1f), Symbol(Colour::Pink, Colour::None, true));
#endif
	}

	void TransformTool::refresh()
	{}

	void TransformTool::process(Viewer& viewer, span<Ref> targets)
	{
		Widget& screen = viewer;//= ui::overlay(viewer);

		this->refresh();

		vector<Transform*> transforms = gather_transforms(targets);
		m_transform = average_transforms(transforms);

		if(MouseEvent event = screen.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			if(!m_dragging)
			{
				auto callback = [&](Item* item) { m_current = &this->gizmo(*item); };
				viewer.picker(1).pick_point(viewer.m_viewport, event.m_relative, callback, ItemFlag::Ui);
			}
		}

		if(MouseEvent event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			m_dragging = m_current;
			m_drag_start = event.m_relative;
			m_grab_start = m_current->grab_point(viewer, event.m_relative);
			m_action = this->create_action(transforms);
			event.consume(screen);
		}

		if(MouseEvent event = screen.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			m_grab_end = m_current->grab_point(viewer, event.m_relative);

			m_action->undo();
			m_action->update(m_grab_start, m_grab_end);
			m_action->apply();
			event.consume(screen);
		}

		if(MouseEvent event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			m_dragging = nullptr;
			m_action->undo();
			this->commit(move(m_action));
			event.consume(screen);
		}

		viewer.m_controller->process(static_cast<Viewer&>(screen)); // @HACK @UGLY it's not a viewer !!
		//viewport_picker(viewer, screen, targets);

		this->paint(viewer.m_scene->m_graph.subi(this));
	}

	Gizmo& TransformTool::gizmo(Item& item)
	{
		for(auto& gizmo : m_gizmos)
			if(gizmo->m_handle == &item)
				return *gizmo;

		return *m_gizmos.front();
	}
}
