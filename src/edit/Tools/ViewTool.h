//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <math/Math.h>
#include <edit/Generated/Forward.h>
#include <edit/Tool.h>

namespace mud
{
	class _refl_ ViewAction : public EditorAction
	{
	public:
		ViewAction(Camera& camera, const vec3& offset);

		virtual void apply() final;
		virtual void undo() final;

		enum State
		{
			START = 0,
			END = 1
		};

	private:
		Camera& m_camera;

		vec3 m_eye_position[2];
	};

	class _refl_ ViewTool : public ViewportTool
	{
	public:
		ViewTool(ToolContext& context, cstring name, const vec3& offset);

		virtual ToolState start(Viewer& viewer) final;

		vec3 m_offset;
	};

	inline unique_ptr<ViewTool> top_view_tool(ToolContext& context) { return make_unique<ViewTool>(context, "Top View", Y3); }
	inline unique_ptr<ViewTool> bottom_view_tool(ToolContext& context) { return make_unique<ViewTool>(context, "Bottom View", -Y3); }

	inline unique_ptr<ViewTool> front_view_tool(ToolContext& context) { return make_unique<ViewTool>(context, "Front View", -Z3); }
	inline unique_ptr<ViewTool> back_view_tool(ToolContext& context) { return make_unique<ViewTool>(context, "Back View", Z3); }

	inline unique_ptr<ViewTool> left_view_tool(ToolContext& context) { return make_unique<ViewTool>(context, "Left View", X3); }
	inline unique_ptr<ViewTool> right_view_tool(ToolContext& context) { return make_unique<ViewTool>(context, "Right View", -X3); }
}
