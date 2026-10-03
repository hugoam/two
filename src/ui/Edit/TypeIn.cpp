//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	TextEdit::TextEdit(Widget* parent, void* identity, bool editor, string allowed_chars)
		: Widget(parent, identity)
		, m_editor(editor)
		, m_text(m_frame)
		, m_string(m_text.m_text)
		, m_dirty(0, uint(m_string.size()))
		, m_allowed_chars(allowed_chars)
	{
		m_palette = OkaidaPalette();
	}

	TextEdit::~TextEdit()
	{}

	size_t TextEdit::visible_lines() const
	{
		const Frame& scroll_frame = m_frame;
		float height = scroll_frame.m_size.y - 20.0f;
		return size_t(floor(height / m_text.line_height()));
	}

	vec2 TextEdit::frame_size()
	{
		auto count_digits = [](int number) { int digits = 0; do { number /= 10; digits++; } while(number != 0); return digits; };
		const int digits = count_digits(int(m_text.m_text_rows.size()));
		const vec2 offset = { m_text.line_height() * float(digits) * 0.7f, 0.f };

		return offset + m_text.compute_text_size() + rect_sum(m_frame.d_inkstyle->m_padding);
	}

	void TextEdit::update_style()
	{
		m_text.update_style();

		if(m_editor)
		{
			m_text.m_text_paint.m_font = "consolas";
			m_text.m_text_paint.m_size = 14.f;
		}

		auto count_digits = [](int number) { int digits = 0; do { number /= 10; digits++; } while (number != 0); return digits; };
		int digits = count_digits(int(m_text.m_text_rows.size()));

		vec2 padding = floor(m_frame.d_inkstyle->m_padding.pos);
		if(m_editor)
			m_text_offset = padding + vec2(m_text.line_height() * float(digits) * 0.7f, 0.f);
		else
			m_text_offset = padding;
	}

	void TextEdit::set_text(const string& text)
	{
		if(m_string == text) return;

		m_text.set_text(text);

		m_selection.m_cursor = m_text.to_cursor(min(size_t(m_selection.m_cursor), text.size()));
		m_selection.m_start = min(size_t(m_selection.m_start), text.size());
		m_selection.m_end = min(size_t(m_selection.m_end), text.size());

		warn("undo/redo won't work after this\n");
		//mUndoBuffer.clear();

		mark_dirty(0, m_string.size());
	}

	void TextEdit::changed()
	{
		m_changed = true;
	}

	void TextEdit::mark_dirty(size_t start, size_t end)
	{
		m_dirty[0] = min<uint>(m_dirty[0], uint(start));
		m_dirty[1] = max<uint>(m_dirty[1], uint(end));
		m_text.break_text_rows();
		this->changed();
	}

	void TextEdit::clear(size_t start, size_t end)
	{
		remove_if(m_text.m_sections, [&](Text::ColorSection& section) { return section.m_end >= start && section.m_start <= end; });
	}

	void TextEdit::shift(size_t start, int offset)
	{
		for(Text::ColorSection& section : m_text.m_sections)
		{
			if(section.m_start > start)
				section.m_start += offset;
			if(section.m_end > start)
				section.m_end += offset;
		}
	}

	void TextEdit::insert(size_t index, const string& text)
	{
		this->shift(index, int(text.size()));
		m_string.insert(index, text);
		this->mark_dirty(line_begin(m_string, index), line_end(m_string, index + text.size()));
		m_follow_cursor = true;
	}

	void TextEdit::insert(size_t index, const string& text, size_t cursor, Action& action)
	{
		action.mAdded = text;
		action.mAddedStart = index;
		action.mAddedEnd = index + text.size();

		this->insert(index, text);
		this->cursor(cursor);
	}

	void TextEdit::erase(size_t start, size_t end)
	{
		if(end == start) return;
		this->clear(start, end);
		this->shift(start, int(start - end));
		m_string.erase(start, end - start);
		this->mark_dirty(line_begin(m_string, start), line_end(m_string, start));
		m_follow_cursor = true;
	}

	void TextEdit::erase(size_t start, size_t end, size_t cursor, Action& action)
	{
		action.mRemoved = m_string.substr(start, end - start);
		action.mRemovedStart = start;
		action.mRemovedEnd = end;

		this->erase(start, end);
		this->cursor(cursor);
	}

	void TextEdit::enter()
	{
		if(allowed('\n'))
		{
			this->insert('\n');
			m_entered = true;
		}
	}

	void TextEdit::escape()
	{
		if(m_completing)
			m_completing = false;
		else
			this->yield_focus();
	}

	void TextEdit::erase_selected(Action& action)
	{
		erase(m_selection.m_start, m_selection.m_end, m_selection.m_start, action);
	}

	void TextEdit::erase()
	{
		if(m_string.empty()) return;

		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);
			else
				erase(m_selection.m_cursor, m_selection.m_cursor + 1, m_selection.m_cursor, action);
		});
	}

	void TextEdit::backspace()
	{
		if(m_string.empty()) return;

		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);
			else if(m_selection.m_cursor > 0)
				erase(m_selection.m_cursor - 1, m_selection.m_cursor, m_selection.m_cursor - 1, action);
		});

		m_completing = m_completing && !is_separator(m_string[m_selection.m_cursor - 1]);
	}

	void TextEdit::insert(unsigned char c)
	{
		if(c == 0 || (!isprint(c) && !isspace(c)) || !allowed(c)) return;
		if(c == '\r') c = '\n';

		char last = m_selection.m_cursor < m_string.size() ? m_string[m_selection.m_cursor - 1] : 0;
		m_completing &= !is_separator(c);
		m_completing |= (last == 0 || is_separator(last)) && !is_separator(c);

		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);

			char cc = c;
			insert(m_selection.m_cursor, string(&cc, 1), m_selection.m_cursor + 1, action);
		});
	}

	void TextEdit::insert(const string& text)
	{
		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);

			insert(m_selection.m_cursor, text, m_selection.m_cursor + text.size(), action);
		});
	}

	string TextEdit::selected_text() const
	{
		return m_string.substr(m_selection.m_start, m_selection.m_end - m_selection.m_start);
	}

	void TextEdit::copy()
	{
		Clipboard& clipboard = this->ui_window().m_clipboard;
		if(has_selection())
			clipboard = { selected_text(), false };
		else
			clipboard = { text_line(m_string, m_selection.m_cursor), true };
	}

	void TextEdit::cut()
	{
		if(m_read_only) return;

		CommitAction([&](Action& action)
		{
			copy();
			if(has_selection())
				erase_selected(action);
			else
				erase(line_begin(m_string, m_selection.m_cursor), line_end(m_string, m_selection.m_cursor) + 1, m_selection.m_cursor, action);
		});
	}

	void TextEdit::paste()
	{
		Clipboard& clipboard = this->ui_window().m_clipboard;
		if(clipboard.m_text.empty()) return;

		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);

			if(clipboard.m_line_mode)
				insert(line_begin(m_string, m_selection.m_cursor), clipboard.m_text, m_selection.m_cursor + clipboard.m_text.size(), action);
			else
				insert(m_selection.m_cursor, clipboard.m_text, m_selection.m_cursor + clipboard.m_text.size(), action);
		});

		m_entered = true;
	}

	void TextEdit::select(size_t first, size_t second, bool word_mode)
	{
		m_selection.m_start = min(first, second);
		m_selection.m_end = max(first, second);

		m_completing = false;
		m_follow_cursor = true;

		if(word_mode)
		{
			m_selection.m_start = word_begin(m_string, m_selection.m_start);
			m_selection.m_end = word_end(m_string, m_selection.m_end);
		}
	}

	void TextEdit::cursor(size_t caret, bool word_mode)
	{
		this->select(caret, caret, word_mode);
		m_selection.m_cursor = m_text.to_cursor(word_mode ? m_selection.m_end : caret);
	}

	void TextEdit::move_select(TextCursor dest, bool select, bool word_mode)
	{
		if(select)
		{
			if(m_select_from.m_index == SIZE_MAX)
				m_select_from = m_selection.m_cursor;
			this->select(m_select_from, dest, select && word_mode);
		}
		else
		{
			m_select_from = {};
			this->select(dest, dest, select && word_mode);
		}

		m_selection.m_cursor = dest;
		m_follow_cursor = true;
	}

	void TextEdit::move_up(bool select)
	{
		this->move_select(m_text.clamp_cursor(ivec2(m_selection.m_cursor.m_grid_index) - ivec2(0, 1)), select);
	}

	void TextEdit::move_down(bool select)
	{
		this->move_select(m_text.clamp_cursor(ivec2(m_selection.m_cursor.m_grid_index) + ivec2(0, 1)), select);
	}

	void TextEdit::move_page_up(bool select)
	{
		this->move_select(m_text.clamp_cursor(ivec2(m_selection.m_cursor.m_grid_index) - ivec2(0, int(visible_lines()) - 4)), select);
	}

	void TextEdit::move_page_down(bool select)
	{
		this->move_select(m_text.clamp_cursor(ivec2(m_selection.m_cursor.m_grid_index) + ivec2(0, int(visible_lines()) - 4)), select);
	}

	void TextEdit::move_left(size_t count, bool select, bool word_mode)
	{
		this->move_select(m_text.clamp_cursor(int(m_selection.m_cursor - count)), select, select && word_mode);
	}

	void TextEdit::move_right(size_t count, bool select, bool word_mode)
	{
		this->move_select(m_text.clamp_cursor(int(m_selection.m_cursor + count)), select, select && word_mode);
	}
	
	void TextEdit::move_top(bool select)
	{
		this->move_select(m_text.to_cursor(0U), select);
	}

	void TextEdit::move_bottom(bool select)
	{
		this->move_select(m_text.to_cursor(m_string.size()), select);
	}

	void TextEdit::move_home(bool select)
	{
		this->move_select(m_text.to_cursor(line_begin(m_string, m_selection.m_cursor)), select);
	}

	void TextEdit::move_end(bool select)
	{
		this->move_select(m_text.to_cursor(line_end(m_string, m_selection.m_cursor)), select);
	}

	void TextEdit::select_none()
	{
		this->cursor(0U);
	}

	void TextEdit::select_all()
	{
		this->select(0U, m_string.size());
	}

	void TextEdit::select_word()
	{
		this->select(word_begin(m_string, m_selection.m_cursor), word_end(m_string, m_selection.m_cursor));
	}

	void TextEdit::AddUndo(Action& aValue)
	{
		m_undo_stack.resize(m_undo_index + 1);
		m_undo_stack.back() = aValue;
		++m_undo_index;
	}

	void TextEdit::update()
	{
		m_changed = false;
		m_entered = false;

		EventType event_focus = m_focus_mode == TextFocusMode::Press ? EventType::Pressed
																	 : EventType::Stroked;
		if(!this->focused())
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, event_focus, InputMod::None, false))
			{
				take_focus();
				this->cursor(0);
			}

		bool shift = this->ui().m_keyboard.m_shift;
		bool ctrl = this->ui().m_keyboard.m_ctrl;
		bool alt = this->ui().m_keyboard.m_alt;
		
		if(MouseEvent event = this->mouse_event(DeviceType::Mouse, EventType::Heartbeat))
		{
			size_t index = m_text.char_at(event.m_relative - m_text_offset);
			m_hovered_word = word_at(m_string, index);
			if(m_hovered_word != "")
			{
				m_hovered_word_rect = m_text.interval_rect(word_begin(m_string, index), word_end(m_string, index));
				m_hovered_word_rect = { m_hovered_word_rect.pos + m_text_offset, m_hovered_word_rect.size };
			}

			this->ui().m_cursor_style = &ui::cursor_styles().caret;
		}
		
		if(!m_completing && !ctrl && !alt && this->key_stroke(Key::Up))
			move_up(shift);
		else if(!m_completing && !ctrl && !alt && this->key_stroke(Key::Down))
			move_down(shift);
		else if(!alt && this->key_stroke(Key::Left))
			move_left(1U, shift, ctrl);
		else if(!alt && this->key_stroke(Key::Right))
			move_right(1U, shift, ctrl);
		else if(!alt && this->key_stroke(Key::PageUp))
			move_page_up(shift);
		else if(!alt && this->key_stroke(Key::PageDown))
			move_page_down(shift);
		else if(ctrl && !alt && this->key_stroke(Key::Home))
			move_top(shift);
		else if(ctrl && !alt && this->key_stroke(Key::End))
			move_bottom(shift);
		else if(!ctrl && !alt && this->key_stroke(Key::Home))
			move_home(shift);
		else if(!ctrl && !alt && this->key_stroke(Key::End))
			move_end(shift);
		else if(!m_read_only && this->key_stroke(Key::Delete))
			erase();
		else if(!m_read_only && this->key_stroke(Key::Back))
			backspace();
		else if(this->key_stroke(Key::Insert, InputMod::None))
			m_selection.m_insert_mode = !m_selection.m_insert_mode;
		else if(this->key_stroke(Key::Insert, InputMod::Ctrl)
			 || this->char_stroke(Key::C, InputMod::Ctrl))
			copy();
		else if(!m_read_only && (this->key_stroke(Key::Insert, InputMod::Shift)
							  || this->char_stroke(Key::V, InputMod::Ctrl)))
			paste();
		else if(this->char_stroke(Key::X, InputMod::Ctrl)
			 || this->key_stroke(Key::Delete, InputMod::Shift))
			cut();
		else if(this->char_stroke(Key::A, InputMod::Ctrl))
			select_all();
		else if(key_stroke(Key::Return))
			enter();
		else if(key_stroke(Key::Escape))
			escape();
		else if(key_stroke(Key::Tab) && !m_completing)
			insert(string(m_tab_size, ' '));
		else if(!m_read_only && (!ctrl || alt))
		{
			KeyEvent stroke = key_stroke(Key::Unassigned);
			if(stroke)
				insert(stroke.m_char);
		}
		
		if(!m_read_only && (this->char_stroke(Key::Z, InputMod::Ctrl)
						 || this->key_stroke(Key::Back, InputMod::Alt)))
			undo();
		if(!m_read_only && this->char_stroke(Key::Y, InputMod::Ctrl))
			redo();

		Clipboard& clipboard = this->ui_window().m_clipboard;
		if(clipboard.m_pasted.size() > 0)
		{
			clipboard.m_text = pop(clipboard.m_pasted);
			clipboard.m_line_mode = false;
			this->paste();
		}

		if(this->focused() && !shift && !alt)
		{
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			{
				m_select_from = m_text.cursor_at(event.m_relative - m_text_offset);
				this->cursor(m_select_from, ctrl);
			}
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::Pressed, InputMod::Ctrl))
			{
				m_select_from = m_text.cursor_at(event.m_relative - m_text_offset);
				m_word_selection_mode = true;
				this->cursor(m_select_from, true);
			}
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::Released))
			{
				if(!focused())
					this->select_all();
			}
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::DoubleStroked))
			{
				TextCursor cursor = m_text.cursor_at(event.m_relative - m_text_offset);
				this->cursor(cursor, true);
			}
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			{
				TextCursor cursor = m_text.cursor_at(event.m_relative - m_text_offset);
				this->select(m_select_from, cursor, m_word_selection_mode);
				m_selection.m_cursor = cursor;
			}
		}

		if(!this->mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			m_word_selection_mode = false;

		m_frame.layer().setForceRedraw(); // TextEdit must redraw each frame
	}

	void TextEdit::update_scroll(Frame& frame, Frame& content)
	{
		if(MouseEvent event = this->mouse_event(DeviceType::MouseMiddle, EventType::Moved))
		{
			float overflow = content.m_size.y - frame.m_size.y;
			content.m_position.y += event.m_deltaZ * 22.f * 3.f;
			content.m_position.y = min(0.f, max(content.m_position.y, -overflow));
		}

		if(m_follow_cursor)
		{
			scroll_to_cursor(frame, content);
			m_follow_cursor = false;
		}
	}

	void TextEdit::render(Vg& vg)
	{
		if(m_editor)
			recolorize();

		if(m_editor)
			vg.draw_rect(vec4(vec2(0.f), m_frame.m_size), palette_paint(m_palette, Text::Background));
		//else
		//	vg.draw_background(m_frame, { m_frame.m_position, m_frame.m_size }, {}, {});

		const vec2 padding = floor(m_frame.d_inkstyle->m_padding.pos);

		if(this->focused())
			draw_text_selection(vg, m_frame, padding, m_text_offset, m_text, m_selection, m_palette, m_editor);
		if(m_editor)
			draw_editor_text(vg, m_frame, padding, m_text_offset, m_text, m_palette);
		else
			draw_text(vg, padding, m_text);
	}

	void TextEdit::undo()
	{
		if(CanUndo())
			m_undo_stack[--m_undo_index].Undo(this);
	}

	void TextEdit::redo()
	{
		if(CanRedo())
			m_undo_stack[m_undo_index++].Redo(this);
	}

	void TextEdit::recolorize()
	{
		if(m_dirty[0] == UINT32_MAX) return;
		//colorize(0, m_string.size());
		colorize(m_dirty[0], m_dirty[1]);
		m_dirty = { UINT32_MAX, 0 };
	}

	void TextEdit::colorize(size_t from, size_t to)
	{
		if(m_string.empty())
			return;

		if(m_language == nullptr)
		{
			m_text.m_sections.clear();
			m_text.m_sections.push_back({ 0, m_string.size(), Text::Default });
			return;
		}

		std::match_results<const char*> results;

		const size_t begin = line_begin(m_string, from);
		const size_t end = line_end(m_string, to);

		bool preproc = false;

		const char* first = &m_string.front();
		const char* start = first + begin;
		const char* last = first + end;

		// remove all sections that overlap range to colorize, and get iterator to insert the new ones
		remove_if(m_text.m_sections, [=](Text::ColorSection& section) { return section.m_start >= begin && section.m_end <= end; });
		auto start_section = find_if(m_text.m_sections, [=](const Text::ColorSection& section) { return section.m_start >= begin; });

		for(const char* current = start; current != last; ++current)
		{
			for(auto& token_color : m_language->m_regex_tokens)
			{
				if(std::regex_search<const char*>(current, last, results, token_color.token, std::regex_constants::match_continuous))
				{
					auto match = *results.begin();
					string name = m_string.substr(match.first - first, match.second - match.first);
					PaletteIndex color = token_color.color;

					//if(color == uint16_t(CodePalette::Word))
					{
						if(!m_language->m_case_sensitive)
							std::transform(name.begin(), name.end(), name.begin(), [](char c) { return char(toupper(c)); });
						
						if(!preproc)
						{
							if(m_language->m_keywords.find(name) != m_language->m_keywords.end())
								color = uint16_t(CodePalette::Keyword);
							else if(m_language->m_identifiers.find(name) != m_language->m_identifiers.end())
								color = uint16_t(CodePalette::Identifier);
							else if(m_language->m_preproc_identifiers.find(name) != m_language->m_preproc_identifiers.end())
								color = uint16_t(CodePalette::PreprocIdentifier);
						}
						else
						{
							if(m_language->m_preproc_identifiers.find(name) != m_language->m_preproc_identifiers.end())
								color = uint16_t(CodePalette::PreprocIdentifier);
							else
								color = uint16_t(CodePalette::Word);
						}
					}
					//else
					if(color == uint16_t(CodePalette::Preprocessor))
					{
						preproc = true;
					}

					const Text::ColorSection section = { size_t(match.first - first), size_t(match.second - first), color };
					start_section = m_text.m_sections.insert(start_section, section);
					start_section++;

					current += name.size() - 1;
					break;
				}
			}

			if(*current == '\n')
				preproc = false;
		}
	}

	void TextEdit::scroll_to_cursor(Frame& frame, Frame& content)
	{
		const vec2 margin = vec2(0.f);

		const vec4 cursor_rect = m_text.cursor_rect(m_selection.m_cursor);
		const vec2 cursor_min = cursor_rect.pos - margin;
		const vec2 cursor_max = cursor_min + cursor_rect.size + margin;

		const vec2 frame_min = -content.m_position;
		const vec2 frame_max = -content.m_position + frame.m_size;

		const vec2 delta_neg = max(vec2(0.f), frame_min - cursor_min);
		const vec2 delta_pos = min(vec2(0.f), frame_max - cursor_max);

		content.set_position(content.m_position + delta_neg);
		content.set_position(content.m_position + delta_pos);
	}

	void TextEdit::Action::Undo(TextEdit * aEditor)
	{
		if(!mAdded.empty())
			aEditor->erase(mAddedStart, mAddedEnd);

		if(!mRemoved.empty())
			aEditor->insert(mRemovedStart, mRemoved);
		
		aEditor->m_selection = mBefore;
		aEditor->m_follow_cursor = true;

	}

	void TextEdit::Action::Redo(TextEdit * aEditor)
	{
		if(!mRemoved.empty())
			aEditor->erase(mRemovedStart, mRemovedEnd);

		if(!mAdded.empty())
			aEditor->insert(mAddedStart, mAdded);

		aEditor->m_selection = mAfter;
		aEditor->m_follow_cursor = true;
	}


namespace ui
{
	bool filter(const string& filter, const string& value)
	{
		for(size_t i = 0; i < filter.size(); ++i)
			if(std::tolower(filter[i], std::locale()) != std::tolower(value[i], std::locale()))
				return false;
		return true;
	}

	TextEdit& text_box(Widget& parent, Style& style, string& text, bool editor, size_t lines, const string& allowed_chars)
	{
		TextEdit& self = parent.suba<TextEdit, bool, string>(editor, allowed_chars);
		self.init(style);

		if(lines > 0)
			self.m_text.set_lines(lines);

		self.update_style();

		self.set_text(text);
		self.update();
		text = self.m_string;

		const vec2 size = self.frame_size();
		ui::dummy(self, size);

		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg) { UNUSED(frame); UNUSED(rect); self.render(vg); };

		return self;
	}

	TextEdit& type_in(Widget& parent, string& text, size_t lines, const string& allowed_chars)
	{
		Widget& self = widget(parent, styles().type_in);
		TextEdit& edit = text_box(self, styles().type_in, text, false, lines, allowed_chars);
		return edit;
	}

	void autocomplete_popup(TextEdit& edit, string& text, const string& current_word, size_t cursor, size_t word_start, span<cstring> completions)
	{
		const vec4 word_rect = edit.m_text.interval_rect(word_start, cursor - 1);
		const vec2 popup_position = edit.m_text_offset + word_rect.pos + vec2(0.f, word_rect.height);

		static uint32_t current = 0;

		const bool selected = ui::popdown(edit, completions, current, popup_position, PopupFlags::None); //auto_complete_style

		if(edit.key_stroke(Key::Up))
			current = max(current - 1, uint32_t(0));

		if(edit.key_stroke(Key::Down))
			current = min(current + 1, uint32_t(completions.size()) - 1);

		if(edit.key_stroke(Key::Tab) || selected)
		{
			edit.insert(string(completions[current]).substr(current_word.size()));
			edit.m_text.break_text_rows();
			edit.m_completing = false;
			text = edit.m_string;
		}
	}

	TextEdit& text_edit(Widget& parent, string& text, size_t lines, vector<string>* vocabulary)
	{
		Widget& self = widget(parent, styles().text_edit);
		ScrollSheet& scroll_sheet = ui::scroll_sheet(self);
		TextEdit& edit = text_box(*scroll_sheet.m_body, styles().type_zone, text, true, lines);

		edit.update_scroll(scroll_sheet.m_scroll_zone->m_frame, scroll_sheet.m_body->m_frame);

		if(vocabulary && edit.m_completing && !edit.has_selection())
		{
			const size_t cursor = edit.m_selection.m_cursor;
			const size_t begin = word_begin(edit.m_string, cursor - 1);

			const string current_word = begin == SIZE_MAX ? "" : edit.m_string.substr(begin, cursor - begin);
			if(current_word != "")
			{
				vector<cstring> completions;
				for(const string& word : *vocabulary)
				{
					//if(word.find(current_word) != string::npos)
					// if current word is fits the beginning of word
					if(word.substr(0, current_word.size()).compare(current_word) == 0)
						completions.push_back(word.c_str());
					//if(word.compare(0, current_word.size(), current_word) == 0)
					//	completions.push_back(word.c_str());
				}

				if(!completions.empty())
					autocomplete_popup(edit, text, current_word, cursor, begin, completions);
			}
		}

		return edit;
	}

	TextEdit& code_edit(Widget& parent, string& text, size_t lines, vector<string>* vocabulary)
	{
		return text_edit(parent, text, lines, vocabulary);
	}

	string auto_indent(TextEdit& edit)
	{
		string text = edit.m_string;
		text.reserve(text.size() * 2);

		int level = 0;
		size_t row = 0;
		size_t cursor_row = edit.m_selection.m_cursor.m_grid_index.y;
		int cursor_offset  = 0;

		auto process_line = [&](const char* line, size_t i)
		{
			const char* c = line;
			while(*c == ' ')
				c++;

			int current = *c == '}' ? level - 1 : level;
			for(; c - line > current * 4; c--)
			{
				text.erase(c - 1 - &text.front(), 1);
				if(cursor_row == i)
					cursor_offset--;
			}
			for(; c - line < current * 4; c++)
			{
				text.insert(c - &text.front(), " ");
				if(cursor_row == i)
					cursor_offset++;
			}

			for(; *c != '\n'; ++c)
			{
				if(*c == '{') level++;
				if(*c == '}') level--;
			}
			return c;
		};

		for(const char* c = &text.front(); c < &text.back(); ++c)
		{
			c = process_line(c, row++);
		}

		edit.cursor(edit.m_selection.m_cursor + cursor_offset);

		return text;
	}
}
}
