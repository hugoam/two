//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/WidgetStruct.h>
#include <ui/Frame/Caption.h>
#include <ui/Style/Paint.h>

namespace two
{
	enum class CodePalette : unsigned char
	{
		Word = Text::Palette::Count,
		Keyword,
		Number,
		String,
		CharLiteral,
		Punctuation,
		Operator,
		Preprocessor,
		Variable,
		Identifier,
		Function,
		Parameter,
		Field,
		PreprocIdentifier,
		Comment,
		Error,
		ErrorMarker,
		Breakpoint,
		Count
	};

	enum class TextFocusMode : unsigned int
	{
		Press,
		Click
	};

	// the text being edited by a text box, kept in the state of its widget
	export_ class refl_ TWO_UI_EXPORT TextEdit : public NodeState
	{
	public:
		class Action
		{
		public:
			void Undo(TextEdit* aEditor, Widget& self);
			void Redo(TextEdit* aEditor, Widget& self);

			string mAdded;
			size_t mAddedStart;
			size_t mAddedEnd;

			string mRemoved;
			size_t mRemovedStart;
			size_t mRemovedEnd;

			TextSelection mBefore;
			TextSelection mAfter;
		};

		using Callback = string(*)(const string&);

	public:
		TextEdit(bool editor, string allowed_chars);
		~TextEdit();

		bool m_editor;
		Text m_text;
		TextSelection m_selection;
		string& m_string;

		bool m_changed = false;
		bool m_entered = false;

		void update_style(Widget& self);
		vec2 frame_size(Widget& self);

		void update(Widget& self);
		void update_scroll(Widget& self, Widget& frame, Widget& content);
		void render(Widget& self, Vg& vg);
		vec2 visible_range(Widget& self);

		void set_text(Widget& self, const string& text);

		void erase(Widget& self, size_t start, size_t end);
		void erase(Widget& self, size_t start, size_t end, size_t cursor, Action& action);

		void insert(Widget& self, size_t index, const string& text);
		void insert(Widget& self, size_t index, const string& text, size_t cursor, Action& action);

		void erase_selected(Widget& self, Action& action);

		void enter(Widget& self);
		void escape(Widget& self);
		void erase(Widget& self);
		void backspace(Widget& self);
		void insert(Widget& self, unsigned char c);
		void insert(Widget& self, const string& text);

		void copy(Widget& self);
		void cut(Widget& self);
		void paste(Widget& self);

		void undo(Widget& self);
		void redo(Widget& self);

		void changed();

		size_t visible_lines(Widget& self) const;

		bool has_selection() const { return m_selection.m_end > m_selection.m_start; }

		string selected_text() const;

		void cursor(size_t index, bool word_mode = false);
		void select(size_t first, size_t second, bool word_mode = false);

		void move_select(TextCursor dest, bool select, bool word_mode = false);

		void select_none();
		void select_all();
		void select_word();

		void scroll_to_cursor(Widget& frame, Widget& content);

		void move_right(size_t count, bool select = false, bool word_mode = false);
		void move_left(size_t count, bool select = false, bool word_mode = false);
		void move_up(bool select = false);
		void move_down(bool select = false);
		void move_page_up(Widget& self, bool select = false);
		void move_page_down(Widget& self, bool select = false);
		void move_top(bool select = false);
		void move_bottom(bool select = false);
		void move_home(bool select = false);
		void move_end(bool select = false);

		bool allowed(char c) { return m_allowed_chars.empty() || m_allowed_chars.find(c) != string::npos; }

		void clear(size_t start, size_t end);
		void shift(size_t start, int offset);

		void recolorize();
		void colorize(size_t start, size_t end);
		void mark_dirty(Widget& self, size_t start, size_t end);

		uvec2 m_dirty;

		template <class T_Func>
		void CommitAction(T_Func func)
		{
			Action action;
			action.mBefore = m_selection;

			func(action);

			action.mAfter = m_selection;
			AddUndo(action);
		}

	public:
		TextFocusMode m_focus_mode = TextFocusMode::Press;
		bool m_read_only = false;
		string m_allowed_chars;

		TextCursor m_select_from;

		vec2 m_text_offset;

		string m_hovered_word = "";
		vec4 m_hovered_word_rect = vec4(0.f);

		using AllowChar = bool(*)(char); AllowChar m_allow_char;

		int m_tab_size = 4;
		bool m_completing = false;
		bool m_follow_cursor = false;
		bool m_word_selection_mode = false;

		ColourPalette m_palette;

		static vector<uint32_t>& DarkPalette();
		static vector<uint32_t>& OkaidaPalette();
		static vector<uint32_t>& VisualStudioPalette();

		// the palette text edits are created with: a theme can set it, e.g style_vs_dark()
		static ColourPalette s_default_palette;

	public:
		bool CanUndo() const { return m_undo_index > 0; }
		bool CanRedo() const { return m_undo_index < (int)m_undo_stack.size(); }

	public:
		void AddUndo(Action& aValue);
		
		vector<Action> m_undo_stack;
		int m_undo_index = 0;

		LanguageDefinition* m_language = nullptr;
	};

namespace ui
{
	export_ TWO_UI_EXPORT bool filter(const string& filter, const string& value);

	// a text box: the widget of the text, and the text edit in its state
	export_ struct TextBox
	{
		Widget& self;
		TextEdit& edit;
	};

	export_ TWO_UI_EXPORT TextBox text_box(NodeKey id, Widget& parent, Style& style, string& text, bool editor = false, size_t lines = 1, const string& allowed_chars = "");
	export_ TWO_UI_EXPORT TextBox type_in(NodeKey id, Widget& parent, string& text, size_t lines = 1, const string& allowed_chars = "");
	export_ TWO_UI_EXPORT TextBox text_edit(NodeKey id, Widget& parent, string& text, size_t lines = 1, vector<string>* vocabulary = nullptr);
	export_ TWO_UI_EXPORT TextBox code_edit(NodeKey id, Widget& parent, string& text, size_t lines = 1, vector<string>* vocabulary = nullptr);

	export_ TWO_UI_EXPORT string auto_indent(TextEdit& edit);
}
}
