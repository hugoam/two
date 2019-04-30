//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <stl/math.h>
#include <math/Vec.hpp>
#include <ui/Frame/Caption.h>
#include <ui/Frame/Frame.h>
#include <ui/Style/Skin.h>
#include <ui/UiRenderer.h>
#endif

#include <cstdio>

namespace mud
{
	bool is_separator(char c)
	{
		string separators = " .,:;+-*=~!()[]{}'\"\t\n";
		return separators.find(c) != string::npos;
	}

	size_t word_begin(const string& text, size_t index)
	{
		size_t begin = SIZE_MAX;
		for(int pos = int(index); pos >= 0 && !is_separator(text[pos]); --pos)
			begin = size_t(pos);
		return begin;
	}

	size_t word_end(const string& text, size_t index)
	{
		size_t end = SIZE_MAX;
		for(size_t pos = index; pos < text.size() && !is_separator(text[pos]); ++pos)
			end = pos;
		return end;
	}

	string word_at(const string& text, size_t index)
	{
		size_t begin = word_begin(text, index);
		size_t end = word_end(text, index);
		return (begin != SIZE_MAX && end != SIZE_MAX) ? text.substr(begin, end + 1 - begin) : "";
	}

	size_t line_begin(const string& text, size_t index)
	{
		size_t begin = index;
		for(; text[begin - 1] != '\n' && begin > 0; --begin)
			;
		return begin;

	}

	size_t line_end(const string& text, size_t index)
	{
		size_t end = index;
		for(; text[end] != '\n' && end < text.size() - 1; ++end)
			;
		return end;
	}

	string text_line(const string& text, size_t index)
	{
		size_t begin = line_begin(text, index);
		size_t end = line_end(text, index);
		return text.substr(begin, end + 1 - begin);
	}

	size_t text_column(const string& text, size_t index)
	{
		return index - line_begin(text, index);
	}

	void replace_tabs(string& text, size_t tab_size)
	{
		for(size_t i = 0; i < text.size(); ++i)
			if(text[i] == '\t')
			{
				size_t num = tab_size - i % tab_size;
				for(size_t j = num; j > 0; --j)
					text.push_back(' ');
				i += num;
			}
	}

	Vg* Text::s_vg = nullptr;

	Text::Text(Frame& frame)
		: m_frame(frame)
		, m_text()
		, m_num_lines(0)
	{}

	inline TextPaint style_text_paint(InkStyle& inkstyle)
	{
		return { inkstyle.m_text_font.c_str(), inkstyle.m_text_colour, inkstyle.m_text_size, inkstyle.m_align, inkstyle.m_text_break, inkstyle.m_text_wrap };
	}

	void Text::update_style()
	{
		m_text_paint = style_text_paint(*m_frame.d_inkstyle);
	}

	void Text::set_lines(size_t lines)
	{
		m_num_lines = lines;
		//d_frame.mark_dirty(DIRTY_LAYOUT);
	}

	void Text::set_text(const string& text)
	{
		if(m_text == text) return;
		m_text = text;
		this->break_text_rows();
	}

	float Text::line_height() const
	{
		return s_vg->line_height(m_text_paint);
	}

	vec2 Text::compute_text_size()
	{
		return { compute_width(), compute_height() };
	}

	float Text::compute_height() const
	{
		if(m_num_lines)
			return line_height() * m_num_lines;
		else if(!m_text_rows.empty())
			return m_text_rows.back().m_rect.y + m_text_rows.back().m_rect.height;
		else
			return 0.f;
	}

	float Text::compute_width() const
	{
		float result = 0.f;
		for(const TextRow& row : m_text_rows)
			result = max(result, row.m_rect.width);
		return result;
	}

	void Text::break_text_rows()
	{
		const vec2 padded_size = floor(m_frame.m_size - rect_sum(m_frame.d_inkstyle->m_padding));

		if(!m_text.empty())
			s_vg->break_text(m_text.c_str(), m_text.size(), padded_size, m_text_paint, m_text_rows);
		else
			m_text_rows.clear();

		//return offset +  + rect_sum(m_frame.d_inkstyle->m_padding);
		m_frame.m_content = this->compute_text_size();
		m_frame.mark_dirty(DIRTY_LAYOUT);
	}

	size_t Text::char_at(const vec2& pos) const
	{
		const char* start = m_text.c_str();
		const char* end = start + m_text.size();// - 1;

		size_t imarker = 0;
		size_t line = 0;
		float offset = 0.f;
		float line_height = s_vg->line_height(m_text_paint);

		for(const TextRow& row : m_text_rows)
		{
			if(imarker < m_markers.size() && m_markers[imarker].m_line == line)
			{
				offset += line_height;
				imarker++;
			}

			if(pos.y < offset + row.m_rect.y + row.m_rect.height) // pos.y >= row.m_rect.y && 
			{
				for(const TextGlyph& glyph : row.m_glyphs)
					if(pos.x < glyph.m_rect.x + glyph.m_rect.width * 0.5f) // pos.x >= glyph.m_rect.x &&
						return glyph.m_position - start;

				return row.m_end - start;
			}

			line++;
		}

		return end - start;
	}

	vec4 Text::interval_rect(const TextRow& row, size_t start, size_t end) const
	{
		const TextGlyph& start_glyph = row.m_glyphs[start - row.m_start_index];
		const TextGlyph& end_glyph = row.m_glyphs[end - row.m_start_index];

		return { start_glyph.m_rect.x, row.m_rect.y, end_glyph.m_rect.x + end_glyph.m_rect.width - start_glyph.m_rect.x, row.m_rect.height };
	}

	vec4 Text::interval_rect(size_t start, size_t end) const
	{
		const TextRow& row = this->text_row_at(start);
		return this->interval_rect(row, start, end);
	}

	TextCursor Text::cursor_at(const vec2& pos) const
	{
		size_t index = this->char_at(pos);
		return this->to_cursor(index);
	}

	vec4 Text::cursor_rect(size_t index) const
	{
		const TextRow& row = text_row_at(index);

		if(index != row.m_end_index)
		{
			size_t offset = row.m_start - m_text.c_str();
			return row.m_glyphs[index - offset].m_rect;
		}
		else
		{
			return { vec2(row.m_rect.x + row.m_rect.width, row.m_rect.y), vec2(1.f, line_height()) };
		}
	}

	size_t Text::text_row_index(size_t index) const
	{
		for(size_t i = 0; i < m_text_rows.size(); ++i)
			if(index <= m_text_rows[i].m_end_index)
				return i;
		return 0;
	}

	const TextRow& Text::text_row_at(size_t index) const
	{
		return m_text_rows[text_row_index(index)];
	}

	TextCursor Text::to_cursor(size_t index) const
	{
		size_t row = this->text_row_index(index);
		size_t column = m_text_rows.empty() ? 0U : index - m_text_rows[row].m_start_index;
		return { index, { uint(column), uint(row) } };
	}

	TextCursor Text::to_cursor(const uvec2& grid_index) const
	{
		size_t index = m_text_rows[grid_index.y].m_start_index + grid_index.x;
		return { index, grid_index };
	}

	TextCursor Text::clamp_cursor(int index) const
	{
		int clamped = max(0, min(int(m_text.size()) - 1, index));
		return to_cursor(clamped);
	}

	TextCursor Text::clamp_cursor(const ivec2& grid_index) const
	{
		int line = max(0, min(int(m_text_rows.size()) - 1, grid_index.y));
		int column = m_text_rows.empty() ? 0 : min(int(m_text_rows[line].m_glyphs.size()), grid_index.x);
		size_t index = m_text_rows[line].m_start_index + column;
		return { index, uvec2(grid_index) };
		//return to_cursor({ uint(column), uint(line) });
	}

	Colour palette_colour(const ColourPalette& palette, PaletteIndex color_index)
	{
		return rgba(palette[color_index]);
	}

	Paint palette_paint(const ColourPalette& palette, PaletteIndex color_index)
	{
		return { rgba(palette[color_index]) };
	}

	TextPaint palette_text_paint(const Text& text, const ColourPalette& palette, PaletteIndex color_index)
	{
		TextPaint paint = text.m_text_paint;
		paint.m_colour = rgba(palette[color_index]);
		return paint;
	}

	void draw_text(Vg& vg, const vec2& padding, const Text& text)
	{
		for(const TextRow& row : text.m_text_rows)
			vg.draw_text(padding + row.m_rect.pos, row.m_start, row.m_end, text.m_text_paint);
	}

	void draw_editor_text(Vg& vg, const Frame& frame, const vec2& padding, const vec2& text_offset, const Text& text, const ColourPalette& palette)
	{
		char line_number[16];

		size_t line = 0;
		size_t isection = 0;
		size_t imarker = 0;

		vec2 offset = vec2(0.f);
		float line_height = vg.line_height(text.m_text_paint);

		for(const TextRow& row : text.m_text_rows)
		{
			while(isection < text.m_sections.size() && text.m_sections[isection].m_end < row.m_start_index)
				isection++;

			snprintf(line_number, 16, "%6d", int(++line));
			vg.draw_text(padding + offset + row.m_rect.pos, line_number, nullptr, palette_text_paint(text, palette, Text::LineNumber));

			while(isection < text.m_sections.size() && text.m_sections[isection].m_start < row.m_end_index)
			{
				const Text::ColorSection& section = text.m_sections[isection];

				const size_t start = max(section.m_start, row.m_start_index);
				const size_t end = min(section.m_end, row.m_end_index);
				const vec2 position = offset + text_offset + row.m_glyphs[start - row.m_start_index].m_rect.pos;
				vg.draw_text(floor(position) + vec2(0.f, 0.5f), &text.m_text.front() + start, &text.m_text.front() + end, palette_text_paint(text, palette, section.m_colour));

				if(section.m_end <= row.m_end_index)
					isection++;
				else
					break;
			}

			if(imarker < text.m_markers.size() && text.m_markers[imarker].m_line == line)
			{
				const vec4 rect = { offset + padding + vec2(0.f, row.m_rect.y + line_height), vec2(frame.m_size.x, text.line_height()) };
				const vec2 position = offset + text_offset + row.m_rect.pos + line_height;

				vg.draw_rect(rect, palette_paint(palette, text.m_markers[imarker].m_highlight));
				vg.draw_text(floor(position) + vec2(0.f, 2.5f), text.m_markers[imarker].m_message.c_str(), nullptr, palette_text_paint(text, palette, text.m_markers[imarker].m_colour));

				offset += vec2(0.f, line_height);

				imarker++;
			}
		}
	}

	void draw_text_selection(Vg& vg, const Frame& frame, const vec2& padding, const vec2& text_offset, const Text& text, const TextSelection& selection, const ColourPalette& palette, bool current_line)
	{
		if(text.m_text_rows.empty())
			return;

		const float line_height = vg.line_height(text.m_text_paint);

		size_t line = 0;
		size_t imarker = 0;
		vec2 offset = vec2(0.f);

		for(const TextRow& row : text.m_text_rows)
		{
			line++;

			if(selection.m_start != selection.m_end && row.m_end_index > selection.m_start && row.m_start_index < selection.m_end)
			{
				if(row.m_glyphs.empty())
				{
					vg.draw_rect({ offset + text_offset + row.m_rect.pos, vec2(5.f, row.m_rect.height) }, palette_paint(palette, Text::Selection));
					continue;
				}

				const size_t select_start = max(row.m_start_index, size_t(selection.m_start));
				const size_t select_end = min(row.m_end_index, size_t(selection.m_end));

				const vec4 row_rect = text.interval_rect(row, select_start, select_end - 1);
				vg.draw_rect({ offset + text_offset + row_rect.pos, row_rect.size }, palette_paint(palette, Text::Selection));
			}

			if(selection.m_cursor >= row.m_start_index && selection.m_cursor <= row.m_end_index)
			{
				if(current_line && selection.m_start == selection.m_end)
				{
					bool focused = false;
					vec4 rect = { offset + padding + vec2(0.f, row.m_rect.y), vec2(frame.m_size.x, text.line_height()) };
					vg.draw_rect(rect, { palette_colour(palette, focused ? Text::CurrentLineFill : Text::CurrentLineFillInactive),
										 palette_colour(palette, Text::CurrentLineEdge), 1.0f });
				}

				static Clock blink_clock;
				static bool caret_visible = true;
				if(blink_clock.read() > 0.4f)
				{
					caret_visible = !caret_visible;
					blink_clock.step();
				}

				if(caret_visible)
				{
					vec4 cursor_rect = text.cursor_rect(selection.m_cursor);
					if(!selection.m_insert_mode)
					{
						cursor_rect.x -= 1.f;
						cursor_rect.z = 1.f;
					}
					vg.draw_rect({ offset + text_offset + cursor_rect.pos, cursor_rect.size }, palette_paint(palette, Text::Cursor));
				}
			}

			if(imarker < text.m_markers.size() && text.m_markers[imarker].m_line == line)
			{
				offset += vec2(0.f, line_height);
				imarker++;
			}
		}
	}
}
