//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <tool/Forward.h>
#include <tool/Tool.h>

namespace two
{
	export_ class refl_ TWO_TOOL_EXPORT RotateAction : public TransformAction
	{
	public:
		RotateAction(span<Transform*> targets, const vec3& axis);

		virtual void apply(Transform& transform) final;
		virtual void undo(Transform& transform) final;

		virtual void update(const vec3& start, const vec3& end);

	private:
		vec3 m_axis;
		float m_angle;
	};

	export_ class refl_ TWO_TOOL_EXPORT RotateTool final : public TransformTool
	{
	public:
		RotateTool(ToolContext& context);

		unique<Gizmo> rotation_gizmo(Axis axis, float hue);

		virtual object<TransformAction> create_action(span<Transform*> transforms);
	};
}
