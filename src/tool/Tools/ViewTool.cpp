//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.tool;

namespace two
{
	ViewAction::ViewAction(Camera& camera, const vec3& eye, const vec3& target)
		: m_camera(camera)
		, m_eye{ camera.m_eye, eye }
		, m_target{ camera.m_target, target }
	{}

	void ViewAction::apply()
	{
		m_camera.m_eye = m_eye[End];
		m_camera.m_target = m_target[End];
	}

	void ViewAction::undo()
	{
		m_camera.m_eye = m_eye[START];
		m_camera.m_target = m_target[START];
	}

	FrameViewTool::FrameViewTool(ToolContext& context)
		: ViewportTool(context, "Frame", type<ViewTool>())
	{}

	void FrameViewTool::activate()
	{
		vec3 vision = m_context.m_camera->m_target - m_context.m_camera->m_eye;
		vector<Transform*> transforms = gather_transforms(*m_context.m_selection);
		Transform transform = average_transforms(transforms);
		this->commit(oconstruct<ViewAction>(*m_context.m_camera, transform.m_position - vision, transform.m_position));
		m_state = ToolState::Done;
	}

	ViewTool::ViewTool(ToolContext& context, cstring name, const vec3& offset)
		: ViewportTool(context, name, type<ViewTool>())
		, m_offset(offset)
	{}

	void ViewTool::activate()
	{
		vec3 target = m_context.m_camera->m_target;
		this->commit(oconstruct<ViewAction>(*m_context.m_camera, target + m_offset, target));
		m_state = ToolState::Done;
	}
}
