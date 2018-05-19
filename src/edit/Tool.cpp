//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <edit/Generated/Types.h>
#include <edit/Tool.h>

#include <geom/Intersect.h>
#include <edit/ActionStack.h>

#include <ui/Sheet.h>
#include <ctx/InputDevice.h>

#include <gfx/Widget/Viewer.h>
#include <gfx/Item.h>
#include <gfx/Gfx.h>
#include <obj/Any.h>

namespace mud
{
	Tool::Tool(ToolContext& context, cstring name, Type& type)
		: m_type(type)
		, m_context(context)
		, m_name(name)
		, m_state(ToolState::Inactive)
	{}

	void Tool::add_option(object_ptr<ToolOption> option)
	{
		UNUSED(option);
	}

	void Tool::commit(object_ptr<EditorAction> action)
	{
		action->apply();
		m_context.m_action_stack->push(std::move(action));
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

	SpatialTool::SpatialTool(ToolContext& context, cstring name, Type& type)
		: ViewportTool(context, name, type)
	{}

	//TransformAction::TransformAction(const std::vector<Transform*>& targets)
	//	: m_targets(targets)
	//{}

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
		: ViewportTool(context, name, type)
		, m_center(Zero3)
	{}

	TransformTool::~TransformTool()
	{}

	bool TransformTool::enabled(const std::vector<Ref>& selection)
	{
		for(Ref object : selection)
			if(this->test_target(object))
				return true;
		return false;
	}

	void TransformTool::paint(Gnode& parent)
	{
		Gnode& self = gfx::node(parent, {}, m_center);

		for(Gizmo& gizmo : m_gizmos)
		{
			if(&gizmo == m_current)
				gizmo.m_item = &gfx::shape(self, gizmo.m_shape, Symbol(Colour::White), ITEM_UI);
			else
				gizmo.m_item = &gfx::shape(self, gizmo.m_shape, gizmo.m_symbol, ITEM_UI);
		}
	}

	void TransformTool::refresh()
	{
	}

	void TransformTool::process(Viewer& viewer, const std::vector<Ref>& targets)
	{
		Widget& screen = ui::overlay(viewer);

		this->refresh();

		std::vector<Transform*> transforms;
		for(Ref object : targets)
			if(object.type().is<Transform>())
				transforms.push_back(&val<Transform>(object));

		m_center = Zero3;
		for(Transform* transform : transforms)
			m_center += transform->m_position;
		//m_center /= transforms.size();
		m_center = m_center / float(transforms.size());

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			if(!m_dragging)
			{
				// @todo highlight gizmo
				auto callback = [&](Item* item) { m_current = &this->gizmo(*item); };
				viewer.pick_point(mouse_event.m_relative, callback, ITEM_UI);
			}
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			m_dragging = m_current;
			m_grab_start = m_current->m_grab_point(viewer);
			m_action = this->create_action(transforms);
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			m_grab_end = m_current->m_grab_point(viewer);

			m_action->undo();
			m_action->update(m_grab_start, m_grab_end);
			m_action->apply();
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			m_dragging = nullptr;
			m_action->undo();
			this->commit(std::move(m_action));
			mouse_event.consume(screen);
		}

		viewer.m_controller->process(static_cast<Viewer&>(screen)); // @HACK @UGLY it's not a viewer !!
		//viewport_picker(viewer, screen, targets);

		this->paint(viewer.m_scene->m_graph.sub(this));
	}

	Gizmo& TransformTool::gizmo(Item& item)
	{
		for(Gizmo& gizmo : m_gizmos)
			if(gizmo.m_item == &item)
				return gizmo;

		return m_gizmos.front();
	}
}
