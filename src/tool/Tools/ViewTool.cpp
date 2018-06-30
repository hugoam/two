//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tool;
#else
#include <gfx/Camera.h>
#include <tool/Types.h>
#include <tool/Tools/ViewTool.h>
#endif

namespace mud
{
	ViewAction::ViewAction(Camera& camera, const vec3& offset)
		: m_camera(camera)
		, m_eye_position{ camera.m_node.m_position, offset }
	{}

	void ViewAction::apply()
	{
		m_camera.m_node.m_position = m_eye_position[END];
	}

	void ViewAction::undo()
	{
		m_camera.m_node.m_position = m_eye_position[START];
	}

	ViewTool::ViewTool(ToolContext& context, cstring name, const vec3& offset)
		: ViewportTool(context, name, type<ViewTool>())
		, m_offset(offset)
	{}

	void ViewTool::activate()
	{
		this->commit(make_object<ViewAction>(*m_context.m_camera, m_offset));
		m_state = ToolState::Done;
	}
}
