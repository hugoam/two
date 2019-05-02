//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <math/Vec.hpp>
#endif
#include <tool/Forward.h>
#include <tool/Tool.h>

namespace two
{
	export_ class refl_ ViewAction : public EditorAction
	{
	public:
		ViewAction(Camera& camera, const vec3& eye, const vec3& target);

		virtual void apply() final;
		virtual void undo() final;

		enum State
		{
			START = 0,
			End = 1
		};

	private:
		Camera& m_camera;

		vec3 m_eye[2];
		vec3 m_target[2];
	};

	export_ class refl_ FrameViewTool final : public ViewportTool
	{
	public:
		FrameViewTool(ToolContext& context);

		virtual void activate() final;
	};

	export_ class refl_ ViewTool final : public ViewportTool
	{
	public:
		ViewTool(ToolContext& context, cstring name, const vec3& offset);

		ViewTool(const ViewTool& other) = default;
		ViewTool& operator=(const ViewTool& other) = default;

		virtual void activate() final;

		vec3 m_offset;
	};

	struct ViewTools
	{
		ViewTools(ToolContext& context) : m_context(context) {}
		ToolContext& m_context;
		ViewTool m_top		= { m_context, "Top View",	   Y3 };
		ViewTool m_bottom	= { m_context, "Bottom View", -Y3 };
		ViewTool m_front	= { m_context, "Front View",  -Z3 };
		ViewTool m_back		= { m_context, "Back View",	   Z3 };
		ViewTool m_left		= { m_context, "Left View",	   X3 };
		ViewTool m_right	= { m_context, "Right View",  -X3 };
	};
}
