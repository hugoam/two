//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <edit/Generated/Forward.h>
#include <edit/Tool.h>

#include <vector>

namespace mud
{
	class _refl_ MUD_EDIT_EXPORT ScaleAction : public TransformAction
	{
	public:
		ScaleAction(const std::vector<Transform*>& targets);

		virtual void apply(Transform& transform) override;
		virtual void undo(Transform& transform) override;

		virtual void update(const vec3& start, const vec3& end) override;

	protected:
		vec3 m_scale_offset;
	};

	class _refl_ MUD_EDIT_EXPORT ScaleTool : public TransformTool
	{
	public:
		ScaleTool(ToolContext& context);

		Gizmo linear_gizmo(Axis axis, float hue);
		Gizmo planar_gizmo(Axis normal, float hue);
		Gizmo uniform_gizmo();

		virtual object_ptr<TransformAction> create_action(const std::vector<Transform*>& transforms);
	};

}
