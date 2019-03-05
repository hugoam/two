//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tool;
#else
#include <type/Any.h>
#include <tree/Graph.hpp>
#include <refl/Method.h>
#include <refl/Meta.h>
#include <lang/VisualScript.h>
#include <geom/Geom.hpp>
#include <geom/Intersect.h>
#include <geom/Shapes.h>
#include <ui/Ui.h>
#include <gfx/Gfx.h>
#include <tool/Types.h>
#include <tool/Brush.h>
#endif

namespace mud
{
	Brush::Brush(ToolContext& context, cstring name, Type& type)
		: SpatialTool(context, name, type)
		, m_world_snap(false)
		, m_work_plane(Y3, 0.f)
	{
		this->add_option(oconstruct<PlaneSnapOption>(*this));
		this->add_option(oconstruct<WorldSnapOption>(*this));
	}

	void Brush::process(Viewer& viewer, const vector<Ref>& selection)
	{
		UNUSED(selection);
		Widget& screen = ui::overlay(viewer);

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			m_position = this->raycast_target(viewer, mouse_event);
			m_symbol_position = m_position;
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			this->begin(m_position);
			this->update(m_position);
			this->end();
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			this->begin(m_position);
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			this->update(m_position);
			static_cast<MouseEvent*>(screen.m_events->m_events[DeviceType::MouseLeft][EventType::Dragged])->consume(screen); // @todo this works, and not the next one
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			this->end();
			mouse_event.consume(screen);
		}

		viewer.m_controller->process(static_cast<Viewer&>(screen)); // @HACK @UGLY it's not a viewer !!

		this->paint(viewer.m_scene->m_graph.subi(this));
	}

	vec3 Brush::raycast_target(Viewer& viewer, MouseEvent& mouse_event)
	{
		if(m_world_snap)
		{
#if 0
			Ray ray = viewer.ray(mouse_event.m_relative);
			return as<PhysicWorld>(m_origin.m_world).ground_point(ray);
#endif
			return vec3();
		}
		else
		{
			Ray ray = viewer.m_viewport.ray(mouse_event.m_relative);
			return plane_segment_intersection(m_work_plane, { ray.m_start, ray.m_end });
		}
	}

	PlaneSnapOption::PlaneSnapOption(Brush& tool)
		: ToolOption("PlaneSnap")
		, m_tool(tool)
	{}

	void PlaneSnapOption::activate()
	{
		m_tool.m_world_snap = false;
	}

	void PlaneSnapOption::deactivate()
	{
		m_tool.m_world_snap = true;
	}

	WorldSnapOption::WorldSnapOption(Brush& tool)
		: ToolOption("WorldSnap")
		, m_tool(tool)
	{}

	void WorldSnapOption::activate()
	{
		m_tool.m_world_snap = true;
	}

	void WorldSnapOption::deactivate()
	{
		m_tool.m_world_snap = false;
	}

	PlaceBrush::PlaceBrush(ToolContext& context)
		: Brush(context, "Place", type<PlaceBrush>())
		, m_creator(type<Transform>())
	{
		//m_creator.setPrototype(type<OLight>());
	}

	void PlaceBrush::activate()
	{
		m_creator.injector().m_args[0] = var(size_t(0));
		//m_creator.injector().m_args[1] = Ref(m_origin);
		m_state = ToolState::Active;
	}

	void PlaceBrush::update(const vec3& position)
	{
		UNUSED(position);
		//Entity& entity = m_creator.create<OLight>().m_spatial;
		//entity.set_position(position);
	}

	void PlaceBrush::paint(Gnode& parent)
	{
		UNUSED(parent);
	}

	CircleBrush::CircleBrush(ToolContext& context)
		: Brush(context, "Circle", type<CircleBrush>())
		, m_creator(type<Node3>())
		, m_radius(50.f)
		, m_maxSpotRadius(10.f)
		, m_accumulate(false)
	{
		//m_creator.setPrototype(type<OLight>());
	}

	void CircleBrush::paint(Gnode& parent)
	{
		UNUSED(parent);
		Gnode& self = gfx::node(parent);
		gfx::shape(self, Circle(m_radius, Axis::Y), Symbol(Colour::White, Colour::AlphaGrey));
	}

	void CircleBrush::activate()
	{
		m_creator.injector().m_args[0] = var(size_t(0));
		//m_creator.injector().m_args[1] = Ref(m_origin);
		m_state = ToolState::Active;
	}

	void CircleBrush::update(const vec3& position)
	{
		if(!m_accumulate)
			this->clearStroke(position);

		float side = m_radius * 2.f;
		m_distribution = oconstruct<Poisson>(vec2(side), m_maxSpotRadius);

		vec3 point;
		while(m_distribution->addPoint(m_maxSpotRadius, point))
		{
			vec3 pos(position.x + point.x - m_radius, position.y, position.z + point.y - m_radius);

			if(filter(position, pos))
			{
				//OLight& light = m_creator.create<OLight>();
				//light.m_spatial.set_position(pos);
				//m_stroke.push_back(&light);
			}
		}
	}

	void CircleBrush::clearStroke(const vec3& center)
	{
		UNUSED(center);
#if 0
		for(OLight*& entity : m_stroke)
			if(entity && this->filter(center, entity->m_spatial.m_position))
			{
				entity->m_spatial.m_parent->detach(entity->m_spatial);
				m_creator.destroy(entity);
				entity = nullptr;
			}
#endif
	}

	bool CircleBrush::filter(const vec3& center, vec3& position)
	{
		//return distance2(position, center) <= m_radius * m_radius;
		return length2(center - position) <= m_radius * m_radius;
	}

	ScriptedBrush::ScriptedBrush(ToolContext& context, Script& script)
		: Brush(context, "Scripted Brush", type<ScriptedBrush>())
		, m_call(script)
		, m_script(script)
	{}

	void ScriptedBrush::activate()
	{
		m_state = ToolState::Active;
	}

	void ScriptedBrush::update(const vec3& position)
	{
		m_call.m_args[0] = var(position);
		m_call();
	}

	void ScriptedBrush::paint(Gnode& parent)
	{
		UNUSED(parent);
	}
}
