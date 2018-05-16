//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <edit/Generated/Types.h>
#include <edit/Tools/ScaleTool.h>

#include <geom/Shapes.h>
#include <geom/Intersect.h>

#include <gfx/Widget/Viewer.h>

namespace mud
{
	ScaleAction::ScaleAction(const std::vector<Transform*>& targets)
		: TransformAction(targets)
		, m_scale_offset(Zero3)
	{}

	void ScaleAction::apply(Transform& transform)
	{
		transform.m_scale += m_scale_offset;
	}

	void ScaleAction::undo(Transform& transform)
	{
		transform.m_scale += -m_scale_offset;
	}

	void ScaleAction::update(const vec3& start, const vec3& end)
	{
		m_scale_offset = end - start;
	}

 	ScaleTool::ScaleTool(ToolContext& context)
		: TransformTool(context, "Scale", type<ScaleTool>())
	{
		m_gizmos.push_back(linear_gizmo(Axis::X, X3, Y3, Colour::Red));
		m_gizmos.push_back(linear_gizmo(Axis::Y, Y3, Z3, Colour::Green));
		m_gizmos.push_back(linear_gizmo(Axis::Z, Z3, X3, Colour::Blue));
		m_current = &m_gizmos.front();
	}

	Gizmo ScaleTool::linear_gizmo(Axis axis, vec3 dir, vec3 normal, Colour colour)
	{
		auto grab_point = [this, dir, normal ](Viewer& viewer)
		{
			Ray ray = viewer.mouse_ray();
			vec3 projected = plane_segment_intersection(m_center, m_center + dir, m_center + normal, ray.m_start, ray.m_end);
			vec3 result = nearest_point_on_line(m_center, dir, projected);
			return result;
		};

		return Gizmo{ Symbol(Colour::None, colour), Cylinder(0.01f, 1.f, axis), nullptr, false, grab_point };
	}

	object_ptr<TransformAction> ScaleTool::create_action(const std::vector<Transform*>& targets)
	{
		return make_object<ScaleAction>(targets);
	}

}
