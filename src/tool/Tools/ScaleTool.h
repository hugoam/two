//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <tool/Forward.h>
#include <tool/Tool.h>

namespace two
{
	export_ class refl_ TWO_TOOL_EXPORT ScaleAction : public TransformAction
	{
	public:
		ScaleAction(span<Transform*> targets);

		virtual void apply(Transform& transform) override;
		virtual void undo(Transform& transform) override;

		virtual void update(const vec3& start, const vec3& end) override;

	protected:
		vec3 m_scale_offset;
	};

	export_ class refl_ TWO_TOOL_EXPORT ScaleTool final : public TransformTool
	{
	public:
		ScaleTool(ToolContext& context);

		unique<Gizmo> linear_gizmo(Axis axis, float hue);
		unique<Gizmo> planar_gizmo(Axis normal, float hue);
		unique<Gizmo> uniform_gizmo();

		virtual object<TransformAction> create_action(span<Transform*> transforms);
	};

}
