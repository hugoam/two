//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tool;
#else
#include <math/Axes.h>
#include <geom/Shapes.h>
#include <geom/Intersect.h>
#include <gfx/Gfx.h>
#include <gfx/Item.h>
#include <tool/Types.h>
#include <tool/Tools/RotateTool.h>
#include <gfx-ui/Viewer.h>
#endif

namespace mud
{
	RotateAction::RotateAction(span<Transform*> targets, const vec3& axis)
		: TransformAction(targets)
		, m_axis(axis)
		, m_angle(0.f)
	{}

	void RotateAction::apply(Transform& transform)
	{
		transform.m_rotation = transform.m_rotation * angle_axis(m_angle, m_axis);
	}

	void RotateAction::undo(Transform& transform)
	{
		transform.m_rotation = transform.m_rotation * angle_axis(-m_angle, m_axis);
	}

	void RotateAction::update(const vec3& start, const vec3& end)
	{
		// @kludge : why negative axis ?
		m_angle = oriented_angle(normalize(start), normalize(end), m_axis); 
	}

	RotateTool::RotateTool(ToolContext& context)
		: TransformTool(context, "Rotate", type<RotateTool>())
	{
		m_gizmos.push_back(rotation_gizmo(Axis::X, 0.f));
		m_gizmos.push_back(rotation_gizmo(Axis::Y, 1.f / 3.f));
		m_gizmos.push_back(rotation_gizmo(Axis::Z, 2.f / 3.f));
		m_current = &*m_gizmos.front();
	}

	Item& rotate_gizmo(Gnode& parent, Axis axis, Colour colour, float ring_radius, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, vec3(0.f), ZeroQuat);
		return gfx::shape(node, Torus(1.f, ring_radius, axis), Symbol(colour, Colour::None, true, true), ItemFlag::Render | flags);
	}

	class RotationGizmo : public TransformGizmo
	{
	public:
		RotationGizmo(TransformTool& tool, Axis axis, float hue) : TransformGizmo(tool, axis, hue) {}

		virtual vec3 grab_point(Viewer& viewer, const vec2& pos) { UNUSED(pos); return gizmo_grab_planar(viewer, m_tool.m_transform, m_axis) - m_tool.m_transform.m_position; };

		virtual Item* draw_handle(Gnode& parent) { return &rotate_gizmo(parent, m_axis, Colour::Invisible, 0.05f, ItemFlag::Ui); };
		virtual void draw_gizmo(Gnode& parent, bool active) { rotate_gizmo(parent, m_axis, gizmo_colour(m_hue, active), 0.01f); };
	};

	unique<Gizmo> RotateTool::rotation_gizmo(Axis axis, float hue)
	{
		return make_unique<RotationGizmo>(*this, axis, hue);
	}

	object<TransformAction> RotateTool::create_action(span<Transform*> targets)
	{
		vec3 axis = m_current == &*m_gizmos[0] ? -X3
				  : m_current == &*m_gizmos[1] ?  Y3
											   : -Z3;
		return oconstruct<RotateAction>(targets, axis);
	}

}

