//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <ui/Structs/Dock.h>
#include <uio/Edit/Script.h>
#endif

#include <tool/Forward.h>
#include <tool/Tool.h>

#include <tool/Tools/TranslateTool.h>
#include <tool/Tools/RotateTool.h>
#include <tool/Tools/ScaleTool.h>
#include <tool/Tools/CopyTool.h>
#include <tool/Tools/ViewTool.h>


#include <tool/ActionStack.h>

namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT EditContext : public NonCopy
    {
    public:
		EditContext(GfxSystem& gfx_system);
        ~EditContext();

		void set_tool(ViewportTool& tool, Viewer& viewer);

		GfxSystem& m_gfx_system;

		std::vector<Ref> m_selection;

		ActionStack m_action_stack;
		ToolContext m_tool_context;

		UndoTool m_undo_tool;
		RedoTool m_redo_tool;

		Plane m_work_plane;
		TranslateTool m_translate_tool;
		RotateTool m_rotate_tool;
		ScaleTool m_scale_tool;

		Viewer* m_viewer = nullptr;
		ViewportTool* m_tool = nullptr;
		SpatialTool* m_spatial_tool = nullptr;
		Brush* m_brush = nullptr;

		std::vector<unique_ptr<Brush>> m_custom_brushes;

		ScriptEditor m_script_editor;

		Docksystem m_docksystem;
		Dockbar* m_dockbar = nullptr;
		Widget* m_screen = nullptr;
    };

	MUD_TOOL_EXPORT void brush_preview(Widget& parent, Brush& brush);
	MUD_TOOL_EXPORT void brush_options(Widget& parent, Brush& brush);
	MUD_TOOL_EXPORT void current_brush_edit(Widget& parent, EditContext& context);

	MUD_TOOL_EXPORT void object_editor(Widget& parent, const std::vector<Ref>& selection);

	MUD_TOOL_EXPORT void tools_transform(Widget& toolbar, EditContext& context);
	MUD_TOOL_EXPORT void edit_transform(Widget& parent, EditContext& context);
	MUD_TOOL_EXPORT void edit_tools(Widget& screen, Docker& docker, EditContext& context);
	MUD_TOOL_EXPORT void edit_tools(Widget& screen, EditContext& context);
	MUD_TOOL_EXPORT void edit_context(Widget& parent, EditContext& context, bool tools = false);
}
