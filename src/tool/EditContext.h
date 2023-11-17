//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <tool/Forward.h>
#include <tool/Tool.h>
#include <tool/Brush.h>

#include <tool/Tools/TranslateTool.h>
#include <tool/Tools/RotateTool.h>
#include <tool/Tools/ScaleTool.h>
#include <tool/Tools/CopyTool.h>
#include <tool/Tools/ViewTool.h>


#include <tool/ActionStack.h>

namespace two
{
	export_ struct refl_ TWO_TOOL_EXPORT Selection
	{
		vector<Ref> objects;
		vector<Entity> entities;
	};

	export_ class refl_ TWO_TOOL_EXPORT EditContext
    {
    public:
		EditContext(GfxSystem& gfx);
        ~EditContext();

		void set_tool(ViewportTool& tool, Viewer& viewer);

		GfxSystem& m_gfx;

		Selection m_selection;

		ActionStack m_action_stack;
		ToolContext m_tool_context;

		attr_ UndoTool m_undo_tool;
		attr_ RedoTool m_redo_tool;

		attr_ Plane m_work_plane;
		attr_ TranslateTool m_translate_tool;
		attr_ RotateTool m_rotate_tool;
		attr_ ScaleTool m_scale_tool;

		ViewTools m_view_tools;

		//PlaceBrush m_place_brush;

		attr_ Viewer* m_viewer = nullptr;
		attr_ ViewportTool* m_tool = nullptr;
		attr_ SpatialTool* m_spatial_tool = nullptr;
		attr_ Brush* m_brush = nullptr;

		vector<unique<Brush>> m_custom_brushes;

		ScriptEditor m_script_editor;

		Docksystem m_docksystem;
		Dockbar* m_dockbar = nullptr;
		Widget* m_screen = nullptr;
    };

	TWO_TOOL_EXPORT void brush_preview(Widget& parent, Brush& brush);
	TWO_TOOL_EXPORT void brush_options(Widget& parent, Brush& brush);
	TWO_TOOL_EXPORT void current_brush_edit(Widget& parent, EditContext& context);

	TWO_TOOL_EXPORT void object_editor(Widget& parent, const Selection& selection);

	TWO_TOOL_EXPORT void tools_transform(Widget& toolbar, EditContext& context);
	TWO_TOOL_EXPORT void edit_transform(Widget& parent, EditContext& context);
	TWO_TOOL_EXPORT void edit_tools(Widget& screen, Docker& docker, EditContext& context);
	TWO_TOOL_EXPORT void edit_tools(Widget& screen, EditContext& context);
	TWO_TOOL_EXPORT void edit_context(Widget& parent, EditContext& context, bool tools = false);
}
