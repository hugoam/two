//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <ui/Structs/Widget.h>
#include <ui/Frame/Caption.h>
#include <ui/Style/Paint.h>

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <memory>
#include <cinttypes>
#include <climits>
//#include <inttypes.h>
#endif

namespace mud
{
	using string = std::string;

	MUD_UI_EXPORT bool is_separator(char c);

	MUD_UI_EXPORT size_t word_begin(const string& text, size_t index);
	MUD_UI_EXPORT size_t word_end(const string& text, size_t index);
	MUD_UI_EXPORT string word_at(const string& text, size_t index);

	MUD_UI_EXPORT size_t line_begin(const string& text, size_t index);
	MUD_UI_EXPORT size_t line_end(const string& text, size_t index);

	MUD_UI_EXPORT void replace_tabs(string& text, size_t tab_size = 4);

	export_ struct _refl_ MUD_UI_EXPORT TextCursor
	{
		TextCursor() {}
		TextCursor(size_t index, uvec2 grid_index) : m_index(index), m_grid_index(grid_index) {}

		bool operator==(const TextCursor& other) const { return m_index == other.m_index && m_grid_index == other.m_grid_index; }

		operator size_t() const { return size_t(m_index); }

		size_t m_index = SIZE_MAX;
		uvec2 m_grid_index = { UINT_MAX, UINT_MAX };
	};

	export_ struct _refl_ MUD_UI_EXPORT TextSelection
	{
		TextSelection() {}
		TextSelection(TextCursor cursor, size_t start, size_t end, bool insert_mode) : m_cursor(cursor), m_start(start), m_end(end), m_insert_mode(insert_mode) {}
		TextCursor m_cursor;
		size_t m_start = SIZE_MAX;
		size_t m_end = SIZE_MAX;
		bool m_insert_mode = false;
	};

	using PaletteIndex = uint16_t;
	using ColourPalette = array<uint32_t>;

	export_ class _refl_ MUD_UI_EXPORT Text
	{
	public:
		Text(Frame& frame);

		void set_lines(size_t lines);
		void set_text(const string& text);

		float line_height() const;
		float compute_height() const;
		float compute_width() const;
		vec2 compute_text_size();

		void break_text_rows();

		vec4 interval_rect(const TextRow& row, size_t start, size_t end) const;
		vec4 interval_rect(size_t start, size_t end) const;

		size_t text_row_index(size_t index) const;
		const TextRow& text_row_at(size_t index) const;

		size_t char_at(const vec2& pos) const;
		TextCursor cursor_at(const vec2& pos) const;

		TextCursor to_cursor(size_t index) const;
		TextCursor to_cursor(const uvec2& grid_index) const;

		TextCursor clamp_cursor(int index) const;
		TextCursor clamp_cursor(const ivec2& grid_index) const;

		vec4 cursor_rect(size_t index) const;

		enum Palette : uint8_t
		{
			Default = 0,
			Background,
			Cursor,
			Selection,
			LineNumber,
			CurrentLineFill,
			CurrentLineFillInactive,
			CurrentLineEdge,
			Count
		};

	public:
		Frame& m_frame;
		string m_text;
		size_t m_num_lines;

		std::vector<TextRow> m_text_rows;

		TextPaint m_text_paint;

		struct ColorSection
		{
			const char* m_start;
			const char* m_end;
			PaletteIndex m_colour;
		};

		std::vector<ColorSection> m_sections;

	public:
		static VgRenderer* s_renderer;
	};

	enum class CodePalette : unsigned char
	{
		Keyword = Text::Palette::Count,
		Number,
		String,
		CharLiteral,
		Punctuation,
		Preprocessor,
		Identifier,
		KnownIdentifier,
		PreprocIdentifier,
		Comment,
		ErrorMarker,
		Breakpoint,
		Count
	};

	enum class TextFocusMode : unsigned int
	{
		Press,
		Click
	};

	export_ class _refl_ MUD_UI_EXPORT TextEdit : public Widget
	{
	public:
		class Action
		{
		public:
			void Undo(TextEdit* aEditor);
			void Redo(TextEdit* aEditor);

			string mAdded;
			size_t mAddedStart;
			size_t mAddedEnd;

			string mRemoved;
			size_t mRemovedStart;
			size_t mRemovedEnd;

			TextSelection mBefore;
			TextSelection mAfter;
		};

		using Callback = std::function<string(const string&)>;

	public:
		TextEdit(Widget* parent, void* identity, bool editor, string allowed_chars);
		~TextEdit();

		bool m_editor;
		Text m_text;
		TextSelection m_selection;
		string& m_string;

		bool m_changed = false;

		void update_style();

		void update();
		void render(VgRenderer& renderer);

		void set_text(const string& text);

		void erase(size_t start, size_t end);
		void erase(size_t start, size_t end, size_t cursor, Action& action);

		void insert(size_t index, const string& text);
		void insert(size_t index, const string& text, size_t cursor, Action& action);

		void erase_selected(Action& action) { erase(m_selection.m_start, m_selection.m_end, m_selection.m_start, action); }

		void enter();
		void erase();
		void backspace();
		void insert(unsigned char c);
		void insert(const string& text);

		void copy();
		void cut();
		void paste();

		void undo();
		void redo();

		void changed();

		size_t visible_lines() const;

		bool has_selection() const { return m_selection.m_end > m_selection.m_start; }

		string selected_text() const { return m_string.substr(m_selection.m_start, m_selection.m_end - m_selection.m_start); }

		void cursor(size_t index);
		void select(size_t index, bool word_mode = false);
		void select(size_t first, size_t second, bool word_mode = false);

		void move_select(TextCursor dest, bool select, bool word_mode = false);

		void select_none();
		void select_all();
		void select_word();

		void scroll_to_cursor();

		void move_right(size_t count, bool select = false, bool word_mode = false);
		void move_left(size_t count, bool select = false, bool word_mode = false);
		void move_up(bool select = false);
		void move_down(bool select = false);
		void move_page_up(bool select = false);
		void move_page_down(bool select = false);
		void move_top(bool select = false);
		void move_bottom(bool select = false);
		void move_home(bool select = false);
		void move_end(bool select = false);

		bool allowed(char c) { return m_allowed_chars.empty() || m_allowed_chars.find(c) != string::npos; }

		void shift(size_t start, size_t offset);

		void recolorize();
		void colorize(size_t start, size_t end);
		void mark_dirty(size_t start, size_t end);

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
		vec4 m_hovered_word_rect = Zero4;

		std::function<bool(char)> m_allow_char;

		int m_tab_size = 4;
		bool m_completing = false;
		bool m_follow_cursor = false;
		bool m_word_selection_mode = false;

		ColourPalette m_palette;

		static std::vector<uint32_t>& GetDarkPalette();

	public:
		bool CanUndo() const { return mUndoIndex > 0; }
		bool CanRedo() const { return mUndoIndex < (int)mUndoStack.size(); }

	public:
		void AddUndo(Action& aValue);
		
		std::vector<Action> mUndoStack;
		int mUndoIndex = 0;

		unique_ptr<LanguageDefinition> m_language;
	};

namespace ui
{
	MUD_UI_EXPORT bool filter(const string& filter, const string& value);

	MUD_UI_EXPORT _func_ TextEdit& text_box(Widget& parent, Style& style, string& text, bool editor = false, size_t lines = 1, const string& allowed_chars = "");
	MUD_UI_EXPORT _func_ TextEdit& type_in(Widget& parent, string& text, size_t lines = 1, const string& allowed_chars = "");
	MUD_UI_EXPORT _func_ TextEdit& text_edit(Widget& parent, string& text, size_t lines = 1, std::vector<string>* vocabulary = nullptr);
	MUD_UI_EXPORT _func_ TextEdit& code_edit(Widget& parent, string& text, size_t lines = 1, std::vector<string>* vocabulary = nullptr);
}
}
