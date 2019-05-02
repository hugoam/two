//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.tool;
#else
#include <tool/Types.h>
#include <tool/Tools/WorkPlaneTool.h>
#endif

namespace two
{
	WorkPlaneAction::WorkPlaneAction(Plane& workPlane, const Plane& plane)
		: m_workPlane(workPlane)
		, m_startPlane(m_workPlane)
		, m_endPlane(plane)
	{}

	void WorkPlaneAction::apply()
	{
		m_workPlane = m_endPlane;
	}

	void WorkPlaneAction::undo()
	{
		m_workPlane = m_startPlane;
	}

	WorkPlaneTool::WorkPlaneTool(ToolContext& context, cstring name, const Plane& plane)
		: Tool(context, name, type<WorkPlaneTool>())
		, m_plane(plane)
	{}

	void WorkPlaneTool::activate()
	{
		m_action = oconstruct<WorkPlaneAction>(*m_context.m_work_plane, m_plane);
		this->commit(move(m_action));
		m_state = ToolState::Done;
	}
}
