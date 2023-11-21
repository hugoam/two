//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Frame/Dim.h>
#include <ui/Style/Paint.h>

namespace two
{
	export_ struct TWO_UI_EXPORT TextGlyph
	{
		const char* m_position;
		vec4 m_rect;
	};

	export_ struct TWO_UI_EXPORT TextRow
	{
		const char* m_start;
		const char* m_end;
		size_t m_start_index;
		size_t m_end_index;
		vec4 m_rect;

		vector<TextGlyph> m_glyphs;
	};

	export_ inline TextRow text_row(const char* str, const char* start, const char* end, const vec4& rect)
	{
		return { start, end, size_t(start - str), size_t(end - str), rect, {} };
	}

	TWO_UI_EXPORT bool is_separator(char c);

	TWO_UI_EXPORT size_t word_begin(const string& text, size_t index);
	TWO_UI_EXPORT size_t word_end(const string& text, size_t index);
	TWO_UI_EXPORT string word_at(const string& text, size_t index);

	TWO_UI_EXPORT size_t line_begin(const string& text, size_t index);
	TWO_UI_EXPORT size_t line_end(const string& text, size_t index);

	TWO_UI_EXPORT string text_line(const string& text, size_t index);
	TWO_UI_EXPORT size_t text_column(const string& text, size_t index);

	TWO_UI_EXPORT void replace_tabs(string& text, size_t tab_size = 4);

	export_ struct refl_ TWO_UI_EXPORT TextCursor
	{
		TextCursor() {}
		TextCursor(size_t index, uvec2 grid_index) : m_index(index), m_grid_index(grid_index) {}

		bool operator==(const TextCursor& other) const { return m_index == other.m_index && m_grid_index == other.m_grid_index; }

		operator size_t() const { return size_t(m_index); }

		size_t m_index = SIZE_MAX;
		uvec2 m_grid_index = { UINT_MAX, UINT_MAX };
	};

	export_ struct refl_ TWO_UI_EXPORT TextSelection
	{
		TextSelection() {}
		TextSelection(TextCursor cursor, size_t start, size_t end, bool insert_mode) : m_cursor(cursor), m_start(start), m_end(end), m_insert_mode(insert_mode) {}
		TextCursor m_cursor;
		size_t m_start = SIZE_MAX;
		size_t m_end = SIZE_MAX;
		bool m_insert_mode = false;
	};

	using PaletteIndex = uint16_t;
	using ColourPalette = span<uint32_t>;

	export_ enum class TextMarkerKind
	{
		Error,
	};

	export_ struct refl_ TWO_UI_EXPORT TextMarker
	{
		TextMarkerKind m_type;
		size_t m_line;
		size_t m_column;
		string m_message;
		PaletteIndex m_colour;
		PaletteIndex m_highlight;
	};

	export_ class refl_ TWO_UI_EXPORT Text
	{
	public:
		Text(Frame& frame);

		void update_style();

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

		vector<TextRow> m_text_rows;

		TextPaint m_text_paint;

		struct ColorSection
		{
			size_t m_start;
			size_t m_end;
			PaletteIndex m_colour;
		};

		vector<ColorSection> m_sections;

		vector<TextMarker> m_markers;

	public:
		static Vg* s_vg;
	};

	TWO_UI_EXPORT Colour palette_colour(const ColourPalette& palette, PaletteIndex color_index);
	TWO_UI_EXPORT Paint palette_paint(const ColourPalette& palette, PaletteIndex color_index);
	TWO_UI_EXPORT TextPaint palette_text_paint(const Text& text, const ColourPalette& palette, PaletteIndex color_index);

	TWO_UI_EXPORT void draw_text(Vg& vg, const vec2& padding, const Text& text);
	TWO_UI_EXPORT void draw_editor_text(Vg& vg, const Frame& frame, const vec2& padding, const vec2& text_offset, const Text& text, const ColourPalette& palette);
	TWO_UI_EXPORT void draw_text_selection(Vg& vg, const Frame& frame, const vec2& padding, const vec2& text_offset, const Text& text, const TextSelection& selection, const ColourPalette& palette, bool current_line);
}
