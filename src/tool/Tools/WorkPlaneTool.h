//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <tool/Forward.h>
#include <tool/Tool.h>

namespace two
{
	export_ class refl_ WorkPlaneAction : public EditorAction
	{
	public:
		WorkPlaneAction(Plane& workPlane, const Plane& plane);

		virtual void apply() final;
		virtual void undo() final;

	private:
		Plane& m_workPlane;
		Plane m_startPlane;
		Plane m_endPlane;
	};

	export_ class refl_ WorkPlaneTool final : public Tool
	{
	public:
		WorkPlaneTool(ToolContext& context, cstring name, const Plane& plane);

		virtual void activate() final;

	private:
		object<WorkPlaneAction> m_action;
		Plane m_plane;
	};

	inline unique<WorkPlaneTool> xy_work_plane_tool(ToolContext& context) { return make_unique<WorkPlaneTool>(context, "XY Work Plane", Plane{ vec3(0.f), x3, y3 }); }
	inline unique<WorkPlaneTool> yz_work_plane_tool(ToolContext& context) { return make_unique<WorkPlaneTool>(context, "YZ Work Plane", Plane{ vec3(0.f), y3, z3 }); }
	inline unique<WorkPlaneTool> xz_work_plane_tool(ToolContext& context) { return make_unique<WorkPlaneTool>(context, "XZ Work Plane", Plane{ vec3(0.f), x3, z3 }); }
}
