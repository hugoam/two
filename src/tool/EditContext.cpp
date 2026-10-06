//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.tool;

namespace two
{
	EditContext::EditContext(GfxSystem& gfx)
		: m_gfx(gfx)
		, m_undo_tool(m_tool_context)
		, m_redo_tool(m_tool_context)
		, m_work_plane() //vec3(0.f, 10.f, 0.f), Entity::FrontVector, Entity::RightVector)
		, m_translate_tool(m_tool_context)
		, m_rotate_tool(m_tool_context)
		, m_scale_tool(m_tool_context)
		, m_view_tools(m_tool_context)
		//, m_place_brush(m_tool_context)
	{
		m_tool_context.m_action_stack = &m_action_stack;
	}

	EditContext::~EditContext()
	{}

	void EditContext::set_tool(ViewportTool& tool, ViewerHandle viewer)
	{
		UNUSED(viewer);
		m_tool = &tool;
		m_spatial_tool = try_as<SpatialTool>(tool);
	}

	void brush_preview(Widget parent, Brush& brush)
	{
		UNUSED(brush);
		Widget self = ui::stack(key(), parent);
		UNUSED(self);
	}

	void brush_options(Widget parent, Brush& brush)
	{
		brush_preview(parent, brush);
		object_edit(parent, Ref(&brush));
	}

	void current_brush_edit(Widget parent, EditContext& context)
	{
		Widget self = section(key(), parent, "Current Brush");
		if(context.m_brush)
			brush_options(self, *context.m_brush);
	}

	bool edit_tool(Widget parent, Tool& tool, cstring icon)
	{
		Widget self = ui::toolbutton(key(), parent, icon);
		self.set_state(ACTIVE, tool.m_state == ToolState::Active);
		return self.activated();
	}
		
	void tools_transform(Widget toolbar, EditContext& context)
	{
		//if(edit_tool(toolbar, "(empty)"))
		//	context.m_tool = nullptr;
		if(edit_tool(toolbar, context.m_undo_tool, "(undo)"))
			context.m_undo_tool.activate();
		if(edit_tool(toolbar, context.m_redo_tool, "(redo)"))
			context.m_redo_tool.activate();
		if(edit_tool(toolbar, context.m_translate_tool, "(translate)"))
			context.set_tool(context.m_translate_tool, context.m_viewer);
		if(edit_tool(toolbar, context.m_rotate_tool, "(rotate)"))
			context.set_tool(context.m_rotate_tool, context.m_viewer);
		if(edit_tool(toolbar, context.m_scale_tool, "(scale)"))
			context.set_tool(context.m_scale_tool, context.m_viewer);

		for(auto& brush : context.m_custom_brushes)
			if(edit_tool(toolbar, *brush, brush->m_name.c_str()))
			{
				context.set_tool(*brush, context.m_viewer);
				context.m_brush = brush.get();
			}
	}

	void edit_transform(Widget parent, EditContext& context)
	{
		Widget self = ui::toolbar(key(), parent);
		tools_transform(self, context);

		if(context.m_brush)
			brush_options(parent, *context.m_brush);
	}

	void console_view(Widget parent, LuaInterpreter& lua)
	{
		static string feed = "console v0.1";
		static string line = "type lua code here";
		static string command = "";

		ui::console(key(), parent, feed, line, command, 18);
		if(command != "")
		{
			lua.call(command.c_str());
			feed += "\n<< " + lua.flush();
			command = "";
		}
	}

	void object_editor(Widget parent, const Selection& selection)
	{
		Section self = section(key(), parent, "Inspector");

		if(!selection.objects.empty() && selection.objects[0])
		{
			Ref selected = selection.objects[0];
			Widget sheet = ui::widget(key(selected.m_value), self.body, styles().sheet);
			object_edit(sheet, selected);
		}
		else if(!selection.entities.empty() && selection.entities[0])
		{
			Entity selected = selection.entities[0];
			Widget sheet = ui::widget(key(selected.m_handle), self.body, styles().sheet);
			entity_edit(sheet, selected);
		}
	}

	void edit_tools(Widget screen, DockerHandle docker, EditContext& context)
	{
		context.m_tool_context.m_action_stack = &context.m_action_stack;
		context.m_tool_context.m_work_plane = &context.m_work_plane;

		//if(Widget dock = ui::dockitem(dockbar, "Library", { 0 }))
		//	library_section(section, { &type<World>(), &type<Entity>() }, game.m_selection);
		if(Widget dock = ui::dockitem(docker, "Inspect", { 2U }))
			object_editor(*dock, context.m_selection);
		if(Widget dock = ui::dockitem(docker, "Edit", { 3U }))
			edit_transform(*dock, context);
		if(Widget dock = ui::dockitem(docker, "Script", { 4U }))
			script_editor(*dock, context.m_script_editor);
		//if(Widget dock = ui::dockitem(context.m_dockbar, "VisualScript", { 5U }))
		//	visual_script_edit(self, shell.m_editor.m_script_editor);
		if(Widget dock = ui::dockitem(docker, "Gfx", { 6U }))
			edit_gfx(*dock, context.m_gfx);
		if(Widget dock = ui::dockitem(docker, "Ui", { 7U }))
			ui_debug(*dock, screen);

		if(context.m_spatial_tool && context.m_viewer.find_viewer())
			context.m_spatial_tool->process(context.m_viewer, context.m_selection.objects);
	}

	void edit_tools(Widget screen, EditContext& context)
	{
		edit_tools(screen, context.m_dockbar, context);
	}

	void edit_context(Widget parent, EditContext& context, bool tools)
	{
		Widget board = ui::board(key(), parent);
		context.m_screen = ui::board(key(), board);
		context.m_dockbar = ui::dockbar(key(), board, context.m_docksystem);

		if(tools)
			edit_tools(*context.m_screen, context);
	}
}
