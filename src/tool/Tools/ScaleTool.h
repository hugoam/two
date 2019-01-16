//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#endif
#include <tool/Forward.h>
#include <tool/Tool.h>

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT ScaleAction : public TransformAction
	{
	public:
		ScaleAction(array<Transform*> targets);

		virtual void apply(Transform& transform) override;
		virtual void undo(Transform& transform) override;

		virtual void update(const vec3& start, const vec3& end) override;

	protected:
		vec3 m_scale_offset;
	};

	export_ class refl_ MUD_TOOL_EXPORT ScaleTool final : public TransformTool
	{
	public:
		ScaleTool(ToolContext& context);

		unique_ptr<Gizmo> linear_gizmo(Axis axis, float hue);
		unique_ptr<Gizmo> planar_gizmo(Axis normal, float hue);
		unique_ptr<Gizmo> uniform_gizmo();

		virtual object_ptr<TransformAction> create_action(array<Transform*> transforms);
	};

}
