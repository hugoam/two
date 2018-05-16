//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <edit/Generated/Types.h>
#include <edit/Tools/RotateTool.h>

#include <geom/Shapes.h>
#include <geom/Intersect.h>

#include <gfx/Widget/Viewer.h>

namespace mud
{
	RotateAction::RotateAction(const std::vector<Transform*>& targets, const vec3& axis)
		: TransformAction(targets)
		, m_axis(axis)
		, m_angle(0.f)
	{}

	void RotateAction::apply(Transform& transform)
	{
		transform.m_rotation *= angle_axis(m_angle, m_axis);
	}

	void RotateAction::undo(Transform& transform)
	{
		transform.m_rotation *= angle_axis(-m_angle, m_axis);
	}

	void RotateAction::update(const vec3& start, const vec3& end)
	{
		// @kludge : why negative axis ?
		m_angle = oriented_angle(normalize(start), normalize(end), -m_axis); 
	}

	RotateTool::RotateTool(ToolContext& context)
		: TransformTool(context, "Rotate", type<RotateTool>())
	{
		m_gizmos.push_back(rotation_gizmo(Axis::X, X3, Z3, Y3, Colour::Red));
		m_gizmos.push_back(rotation_gizmo(Axis::Y, Y3, X3, Z3, Colour::Green));
		m_gizmos.push_back(rotation_gizmo(Axis::Z, Z3, X3, Y3, Colour::Blue));
		m_current = &m_gizmos.front();
	}

	Gizmo RotateTool::rotation_gizmo(Axis axis, vec3 dir, vec3 p1, vec3 p2, Colour colour)
	{
		auto grab_point = [this, dir, p1, p2](Viewer& viewer)
		{
			Ray ray = viewer.mouse_ray();
			vec3 result = plane_segment_intersection(m_center, m_center + p1, m_center + p2, ray.m_start, ray.m_end);
			return result - m_center;
		};

		return Gizmo{ Symbol(colour, Colour::None), Circle(1.f, axis), nullptr, false, grab_point };
	}

	object_ptr<TransformAction> RotateTool::create_action(const std::vector<Transform*>& targets)
	{
		vec3 axis = m_current == &m_gizmos[0] ? X3
				  : m_current == &m_gizmos[1] ? Y3
											  : Z3;
		return make_object<RotateAction>(targets, axis);
	}

}

