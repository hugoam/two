//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <obj/Vector.h>
#include <obj/System/System.h>
#include <obj/Memory/ObjectPool.h>
#include <lang/Script.h>
#include <lang/VisualScript.h>
#include <lang/Lua.h>
#include <ui/Input.h>
#include <uio/Generated/Types.h>
#include <uio/Edit/Script.h>
#include <uio/Edit/Canvas.h>
#include <uio/Edit/Indexer.h>
#include <uio/Edit/Reflection.h>
#include <uio/Unode.h>
#endif

namespace mud
{
	ScriptEditor::ScriptEditor()
	{}

	ScriptEditor::~ScriptEditor()
	{}

	void ScriptEditor::open(VisualScript& script)
	{
		vector_add(m_visual_scripts, &script);
	}

	VisualScript& ScriptEditor::create_visual(cstring name)
	{
		VisualScript& script = GlobalPool::me().pool<VisualScript>().construct(name);
		return script;
	}

	void ScriptEditor::close(VisualScript& script)
	{
		vector_remove(m_visual_scripts, &script);
	}

	void ScriptEditor::open(Script& script)
	{
		vector_add(m_scripts, &script);
	}

	Script& ScriptEditor::create_script(cstring name)
	{
		Script& script = GlobalPool::me().pool<Script>().construct(name);
		script.m_interpreter = m_interpreter;
		vector_add(m_scripts, &script);
		return script;
	}

	void ScriptEditor::close(Script& script)
	{
		vector_remove(m_scripts, &script);
	}

	std::vector<string> lua_words()
	{
		return { "print" };
	}

	std::vector<string> meta_words()
	{
		std::vector<string> symbols = vector_convert<string>(System::instance().meta_symbols());
		vector_extend(symbols, lua_words());
		return symbols;
	}

	void script_edit_output(Widget& parent, LuaInterpreter& lua)
	{
		Widget& self = ui::sheet(parent);
		ui::title_header(self, "Lua output");

		static string output = "";
		output = lua.flush();

		//Widget& self = widget(parent, styles().text_edit);;
		//TextEdit& edit = text_box(*scroll_sheet.m_body, styles().type_zone, text, true, lines);

		ui::text_box(self, styles().type_in, output, true, 5);
	}

	void script_edit_hover(TextEdit& edit)
	{
		if(edit.m_hovered_word != "")
		{
			vec2 hover_at = rect_offset(edit.m_hovered_word_rect) + vec2{ 0.f, rect_h(edit.m_hovered_word_rect) };

			//ui::rectangle(edit, edit.m_hovered_word_rect);

			if(Function* function = system().find_function(edit.m_hovered_word.c_str()))
			{
				Widget& popup = ui::popup_at(edit, hover_at, ui::PopupFlags::None);
				meta_synopsis(popup, *function);
			}
			else if(Type* type = system().find_type(edit.m_hovered_word.c_str()))
			{
				Widget& popup = ui::popup_at(edit, hover_at, ui::PopupFlags::None);
				meta_synopsis(popup, *type);
			}
			else
				ui::tooltip(edit, hover_at, edit.m_hovered_word.c_str());

			if(MouseEvent mouse_event = edit.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			{
			}
		}
	}

#if 0
	Widget& error_tooltip(Widget& parent)
	{
		Widget* tooltip = ui::tooltip();
		ui::label("Error at line %d:", errorIt->first); // Colour(1.0f, 0.2f, 0.2f, 1.0f)
		ui::label("%s", errorIt->second.c_str()); // Colour(1.0f, 1.0f, 0.2f, 1.0f)
	}
#endif

	void script_edit_code(Widget& parent, Script& script, ActionList actions)
	{
		actions.push_back({ "Run", [&] { script({}); } });
		Section& self = section(parent, script.m_name.c_str(), actions);

		std::vector<string> known_words = meta_words();
		TextEdit& edit = ui::code_edit(*self.m_body, script.m_script, 0, &known_words);
		UNUSED(edit);

		//script_edit_hover(edit);
	}

	void script_edit(Widget& parent, Script& script, ActionList actions)
	{
		Widget& span_0 = ui::layout_span(parent, 0.8f);
		script_edit_code(span_0, script, actions);
		Widget& span_1 = ui::layout_span(parent, 0.2f);
		script_edit_output(span_1, *script.m_interpreter);
	}

	void script_tab(Tabber& parent, ScriptEditor& editor, Script& script)
	{
		if(Widget* tab = ui::tab(parent, script.m_name.c_str()))
		{
			ActionList script_actions = {
				{ "Close", [&] { editor.close(script); } }
			};
			script_edit(*tab, script, script_actions);
		}
	}

	enum ScriptEditorModes
	{
		OPEN_SCRIPT = 1 << 0,
	};

	void script_editor(Widget& parent, ScriptEditor& editor)
	{
		ActionList actions = {
			//{ "Open Script", [&] { Ref result = object_picker(parent.root(), type<Script>()); if(result) editor.open(result.val<Script>()); } },
			{ "New Script", [&] { editor.create_script(("Untitled " + to_string(editor.m_scripts.size())).c_str()); } },

			//{ "Open Visual Script", [&] { Ref result = object_picker(parent.root(), type<VisualScript>()); if(result) editor.open(result.val<VisualScript>()); } },
			{ "New Visual Script", [&] { editor.create_visual(("Untitled " + to_string(editor.m_visual_scripts.size())).c_str()); } }
		};

		Section& self = section(parent, "Script Editor", actions);

		if(ui::modal_button(self, *self.m_toolbar, "Open Script", OPEN_SCRIPT))
		{
			Widget& modal = ui::auto_modal(self, OPEN_SCRIPT, { 600, 400 });
			Ref result = Ref(type<Script>());
			if(object_selector(modal, result))
			{
				editor.open(val<Script>(result));
				self.m_switch &= ~OPEN_SCRIPT;
			}
		}

		Tabber& tabber = ui::tabber(*self.m_body);

		for(Script* script : editor.m_visual_scripts)
			script_tab(tabber, editor, *script);

		for(Script* script : editor.m_scripts)
			script_tab(tabber, editor, *script);
	}

}
