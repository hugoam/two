//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/algorithm.h>
#include <stl/hash_base.hpp>
#include <infra/Vector.h>
#include <infra/ToString.h>
#include <math/Vec.hpp>
#include <type/Any.h>
#include <refl/System.h>
#include <pool/ObjectPool.hpp>
#include <lang/Script.h>
#include <lang/VisualScript.h>
#include <lang/Lua.h>
#include <lang/Wren.h>
#include <ui/Input.h>
#include <ui/Edit/TypeIn.h>
#include <ui/Edit/Lang.h>
#include <uio/Types.h>
#include <uio/ScriptEdit.h>
#include <uio/Canvas.h>
#include <uio/IndexerEdit.h>
#include <uio/ReflEdit.h>
#endif

namespace mud
{
	ScriptEditor::ScriptEditor()
	{
		set_meta_palette(TextEdit::OkaidaPalette());
	}

	ScriptEditor::~ScriptEditor()
	{}

	void ScriptEditor::reset_interpreters(LuaInterpreter& lua, WrenInterpreter& wren)
	{
		m_lua = &lua;
		m_wren = &wren;

		for(Script* script : m_scripts)
			if(TextScript* text_script = try_as<TextScript>(*script))
			{
				if(text_script->m_language == Language::Lua)
					text_script->m_interpreter = m_lua;
				else if(text_script->m_language == Language::Wren)
					text_script->m_interpreter = m_wren;
			}
	}

	void ScriptEditor::open(Script& script)
	{
		add(m_scripts, &script);
	}

	void ScriptEditor::close(Script& script)
	{
		remove(m_scripts, &script);
	}

	TextScript& ScriptEditor::create_script(const string& name, Language language, Signature signature)
	{
		TextScript& script = global_pool<TextScript>().construct(name, language, signature);
		if(language == Language::Lua)
			script.m_interpreter = m_lua;
		else if(language == Language::Wren)
			script.m_interpreter = m_wren;
		this->open(script);
		return script;
	}

	VisualScript& ScriptEditor::create_visual(const string& name, Signature signature)
	{
		VisualScript& script = global_pool<VisualScript>().construct(name, signature);
		this->open(script);
		return script;
	}

	vector<string> lua_words()
	{
		return { "print" };
	}

	vector<string> meta_words()
	{
		vector<string> symbols = convert<string, cstring>(System::instance().meta_symbols());
		extend(symbols, lua_words());
		return symbols;
	}

	void script_edit_output(Widget& parent, Interpreter& interpreter)
	{
		Widget& self = ui::sheet(parent);
		ui::title_header(self, "Output");

		static string output = "";
		output = interpreter.flush();

		ui::text_box(self, styles().type_in, output, true, 5);
	}

	void script_edit_hover(TextEdit& edit)
	{
		if(edit.m_hovered_word != "")
		{
			vec2 hover_at = edit.m_hovered_word_rect.pos + vec2(0.f, edit.m_hovered_word_rect.height);

			//ui::rectangle(edit, edit.m_hovered_word_rect);
			
			Function* function = system().find_function(edit.m_hovered_word.c_str());
			Type* type = system().find_type(edit.m_hovered_word.c_str());
			Type* lowertype = system().find_type(to_lower(edit.m_hovered_word).c_str());

			if(function || type || lowertype)
			{
				if(Widget* popup = ui::hoverbox(edit, hover_at))
				{
					if(function)
						meta_synopsis(*popup, *function);
					else if(type || lowertype)
						meta_synopsis(*popup, type ? *type : *lowertype);
				}
			}
		
			if(MouseEvent event = edit.mouse_event(DeviceType::MouseRight, EventType::Stroked))
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

	Section& script_edit_code(Widget& parent, TextScript& script)
	{
		//auto run = [&] { script({}); };
		auto reload = [&] { script.m_dirty = true; };
		//actions.push_back({ "Run",  });
		Section& self = section(parent, script.m_name.c_str());

		if(section_action(self, "Reload"))
			reload();

		vector<string> known_words = meta_words();
		TextEdit& edit = ui::code_edit(*self.m_body, script.m_script, 0, &known_words);
		
		if(script.m_language == Language::Lua)
			edit.m_language = &LanguageLua();
		else if(script.m_language == Language::Wren)
			edit.m_language = &LanguageWren();
		
		if(edit.char_stroke(Key::S, InputMod::Ctrl))
			reload();

		if(edit.m_entered)
			script.m_script = ui::auto_indent(edit);

		edit.m_text.m_markers.clear();
		for(const auto& line_error : script.m_compile_errors)
		{
			const ScriptError& error = line_error.second;
			edit.m_text.m_markers.push_back({ TextMarkerKind::Error, error.m_line, error.m_column, error.m_message, uint16_t(CodePalette::Error), uint16_t(CodePalette::ErrorMarker) });
		}

		for(const auto& line_error : script.m_runtime_errors)
		{
			const ScriptError& error = line_error.second;
			edit.m_text.m_markers.push_back({ TextMarkerKind::Error, error.m_line, error.m_column, error.m_message, uint16_t(CodePalette::Error), uint16_t(CodePalette::ErrorMarker) });
		}

		script_edit_hover(edit);

		return self;
	}

	Section& script_edit(Widget& parent, TextScript& script)
	{
		return script_edit_code(parent, script);
		//Widget& span_0 = ui::layout_span(parent, 0.8f);
		//script_edit_code(span_0, script, actions);
		//Widget& span_1 = ui::layout_span(parent, 0.2f);
		//script_edit_output(span_1, *script.m_interpreter);
	}

	void script_tab(Tabber& parent, ScriptEditor& editor, Script& script)
	{
		if(Widget* tab = ui::tab(parent, script.m_name.c_str()))
		{
			Section& edit = script.m_type.is<VisualScript>()
				? visual_script_edit(*tab, as<VisualScript>(script))
				: script_edit(*tab, as<TextScript>(script));

			if(section_action(edit, "Close"))
				editor.close(script);
		}
	}

	void script_editor(Widget& parent, ScriptEditor& editor)
	{
		enum Modes { Open = 1 << 0, Browse = 1 << 1 };

		Section& self = section(parent, "Script Editor");

		if(section_action(self, "New Script"))
			editor.create_script("Untitled " + to_string(editor.m_scripts.size()), Language::Lua);
		if(section_action(self, "New Visual Script"))
			editor.create_visual("Untitled " + to_string(editor.m_scripts.size()));

		if(ui::modal_button(self, *self.m_toolbar, "Open Script", Open))
		{
			Widget& modal = ui::auto_modal(self, Open, { 600, 400 });
			Ref result = Ref(type<Script>());
			if(object_selector(*modal.m_body, result))
			{
				editor.open(val<Script>(result));
				self.m_switch &= ~Open;
			}
		}

		if(ui::modal_button(self, *self.m_toolbar, "Browse API", Browse))
		{
			Widget& modal = ui::auto_modal(self, Browse, { 600, 600 });
			meta_browser(*modal.m_body);
			if(ui::button(*modal.m_body, "Close").activated())
				self.m_switch &= ~Browse;
		}

		Tabber& tabber = ui::tabber(*self.m_body);
		for(Script* script : editor.m_scripts)
			script_tab(tabber, editor, *script);
	}

}
