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
#include <tool/Tools/TranslateTool.h>
#include <gfx-ui/Viewer.h>
#endif

namespace mud
{
	TranslateAction::TranslateAction(array<Transform*> targets)
		: TransformAction(targets)
		, m_translation(Zero3)
	{}

	void TranslateAction::apply(Transform& transform)
	{
		transform.m_position += m_translation;
	}

	void TranslateAction::undo(Transform& transform)
	{
		transform.m_position += -m_translation;
	}

	void TranslateAction::update(const vec3& start, const vec3& end)
	{
		m_translation = end - start;
	}

 	TranslateTool::TranslateTool(ToolContext& context)
		: TransformTool(context, "Translate", type<TranslateTool>())
	{
		m_gizmos.push_back(linear_gizmo(Axis::X, 0.f));
		m_gizmos.push_back(linear_gizmo(Axis::Y, 1.f / 3.f));
		m_gizmos.push_back(linear_gizmo(Axis::Z, 2.f / 3.f));
		m_gizmos.push_back(planar_gizmo(Axis::X, 0.f));
		m_gizmos.push_back(planar_gizmo(Axis::Y, 1.f / 3.f));
		m_gizmos.push_back(planar_gizmo(Axis::Z, 2.f / 3.f));
		m_current = &*m_gizmos.front();
	}

	Item& translate_1d_gizmo(Gnode& parent, Axis axis, Colour colour, float radius, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, to_vec3(axis), ZeroQuat);
		return gfx::shape(node, Cylinder(radius, 1.f, axis), Symbol(colour, Colour::None, true), flags);
	}

	Item& translate_2d_gizmo(Gnode& parent, Axis axis, Colour colour, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, 0.5f * (c_tangents[uint(axis)] + c_binormals[uint(axis)]), ZeroQuat);
		return gfx::shape(node, Quad(0.3f, c_tangents[uint(axis)], c_binormals[uint(axis)]), Symbol(colour, Colour::None, true, true), flags);
	}

	class TranslateLinearGizmo : public TransformGizmo
	{
	public:
		TranslateLinearGizmo(TransformTool& tool, Axis axis, float hue) : TransformGizmo(tool, axis, hue) {}

		virtual vec3 grab_point(Viewer& viewer, const vec2& pos) { UNUSED(pos); return gizmo_grab_linear(viewer, m_tool.m_transform, m_axis); };

		virtual Item* draw_handle(Gnode& parent) { return &translate_1d_gizmo(parent, m_axis, Colour::Invisible, 0.05f, ItemFlag::Ui); };
		virtual void draw_gizmo(Gnode& parent, bool active) { translate_1d_gizmo(parent, m_axis, gizmo_colour(m_hue, active), 0.02f); };
	};

	class TranslatePlanarGizmo : public TransformGizmo
	{
	public:
		TranslatePlanarGizmo(TransformTool& tool, Axis axis, float hue) : TransformGizmo(tool, axis, hue) {}

		virtual vec3 grab_point(Viewer& viewer, const vec2& pos) { UNUSED(pos); return gizmo_grab_planar(viewer, m_tool.m_transform, m_axis); };

		virtual Item* draw_handle(Gnode& parent) { return &translate_2d_gizmo(parent, m_axis, Colour::Invisible, ItemFlag::Ui); };
		virtual void draw_gizmo(Gnode& parent, bool active) { translate_2d_gizmo(parent, m_axis, gizmo_colour(m_hue, active)); };;
	};

	unique<Gizmo> TranslateTool::linear_gizmo(Axis axis, float hue)
	{
		return make_unique<TranslateLinearGizmo>(*this, axis, hue);
	}

	unique<Gizmo> TranslateTool::planar_gizmo(Axis normal, float hue)
	{
		return make_unique<TranslatePlanarGizmo>(*this, normal, hue);
	}

	object<TransformAction> TranslateTool::create_action(array<Transform*> targets)
	{
		return oconstruct<TranslateAction>(targets);
	}

}
