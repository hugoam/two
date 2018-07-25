//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <infra/Vector.h>
#include <obj/Any.h>
#include <refl/System.h>
#include <pool/ObjectPool.h>
#include <lang/Script.h>
#include <lang/VisualScript.h>
#include <lang/Lua.h>
#include <ui/Input.h>
#include <uio/Types.h>
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

	void ScriptEditor::open(Script& script)
	{
		vector_add(m_scripts, &script);
	}

	void ScriptEditor::close(Script& script)
	{
		vector_remove(m_scripts, &script);
	}

	VisualScript& ScriptEditor::create_visual(cstring name)
	{
		VisualScript& script = GlobalPool::me().pool<VisualScript>().construct(name);
		this->open(script);
		return script;
	}

	LuaScript& ScriptEditor::create_script(cstring name)
	{
		LuaScript& script = GlobalPool::me().pool<LuaScript>().construct(name);
		script.m_interpreter = m_interpreter;
		this->open(script);
		return script;
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

	void script_edit_code(Widget& parent, LuaScript& script, ActionList actions)
	{
		actions.push_back({ "Run", [&] { script({}); } });
		Section& self = section(parent, script.m_name.c_str(), actions);

		std::vector<string> known_words = meta_words();
		TextEdit& edit = ui::code_edit(*self.m_body, script.m_script, 0, &known_words);
		UNUSED(edit);

		//script_edit_hover(edit);
	}

	void script_edit(Widget& parent, LuaScript& script, ActionList actions)
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

			if(script.m_type.is<VisualScript>())
				visual_script_edit(*tab, as<VisualScript>(script), script_actions);
			else if(script.m_type.is<LuaScript>())
				script_edit(*tab, as<LuaScript>(script), script_actions);
		}
	}

	void script_editor(Widget& parent, ScriptEditor& editor)
	{
		enum Modes { OPEN = 1 << 0 };

		ActionList actions = {
			{ "New Script", [&] { editor.create_script(("Untitled " + to_string(editor.m_scripts.size())).c_str()); } },
			{ "New Visual Script", [&] { editor.create_visual(("Untitled " + to_string(editor.m_scripts.size())).c_str()); } }
		};

		Section& self = section(parent, "Script Editor", actions);

		if(ui::modal_button(self, *self.m_toolbar, "Open Script", OPEN))
		{
			Widget& modal = ui::auto_modal(self, OPEN, { 600, 400 });
			Ref result = Ref(type<Script>());
			if(object_selector(*modal.m_body, result))
			{
				editor.open(val<Script>(result));
				self.m_switch &= ~OPEN;
			}
		}

		Tabber& tabber = ui::tabber(*self.m_body);
		for(Script* script : editor.m_scripts)
			script_tab(tabber, editor, *script);
	}

}
