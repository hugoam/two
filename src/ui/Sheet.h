//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <ui/Widget.h>
#include <ui/Button.h>
#include <ui/Style/Styles.h>

namespace mud
{
namespace ui
{
	struct DragPoint
	{
		Frame* prev = nullptr;
		Frame* next = nullptr;
	};

	_func_ inline Widget& row(Widget& parent) { return widget(parent, styles().row); }
	_func_ inline Widget& header(Widget& parent) { return widget(parent, styles().header); }
	_func_ inline Widget& div(Widget& parent) { return widget(parent, styles().div); }
	_func_ inline Widget& stack(Widget& parent) { return widget(parent, styles().stack); }
	_func_ inline Widget& sheet(Widget& parent) { return widget(parent, styles().sheet); }
	_func_ inline Widget& board(Widget& parent) { return widget(parent, styles().board); }
	_func_ inline Widget& layout(Widget& parent) { return widget(parent, styles().layout); }
	_func_ inline Widget& screen(Widget& parent) { return widget(parent, styles().screen); }
	_func_ inline Widget& decal(Widget& parent) { return widget(parent, styles().decal); }
	_func_ inline Widget& overlay(Widget& parent) { return widget(parent, styles().overlay); }

	_func_ inline Widget& title_header(Widget& parent, cstring title)
	{
		Widget& self = ui::header(parent);
		ui::label(self, title);
		return self;
	}

	export_ MUD_UI_EXPORT _func_ Widget& dummy(Widget& parent, const vec2& size);

	export_ MUD_UI_EXPORT Widget& layout_span(Widget& parent, float span);

	export_ MUD_UI_EXPORT Widget& popup(Widget& parent, Style& style, PopupFlags flags);
	export_ MUD_UI_EXPORT Widget& popup(Widget& parent, Style& style, const vec2& size, PopupFlags flags);
	export_ MUD_UI_EXPORT Widget& popup_at(Widget& parent, Style& style, const vec2& position, PopupFlags flags);

	_func_ inline Widget& popup(Widget& parent, PopupFlags flags) { return popup(parent, styles().popup, flags); }
	_func_ inline Widget& popup(Widget& parent, const vec2& size, PopupFlags flags = PopupFlags::None) { return popup(parent, styles().popup, size, flags); }
	_func_ inline Widget& popup_at(Widget& parent, const vec2& position, PopupFlags flags = PopupFlags::None) { return popup_at(parent, styles().popup, position, flags); }

	_func_ inline Widget& modal(Widget& parent) { return popup(parent, styles().modal, PopupFlags::Modal); }
	_func_ inline Widget& modal(Widget& parent, const vec2& size) { return popup(parent, styles().modal, size, PopupFlags::Modal); }

	_func_ export_ MUD_UI_EXPORT Widget& auto_modal(Widget& parent, uint32_t mode);
	_func_ export_ MUD_UI_EXPORT Widget& auto_modal(Widget& parent, uint32_t mode, const vec2& size);

	_func_ MUD_UI_EXPORT Widget* context(Widget& parent, uint32_t mode, PopupFlags flags = PopupFlags::None);

	MUD_UI_EXPORT DragPoint grid_sheet_logic(Widget& self, Dim dim);
	export_ MUD_UI_EXPORT Widget& grid_sheet(Widget& parent, Style& style, Dim dim);
	export_ MUD_UI_EXPORT Widget& grid_sheet(Widget& parent, Style& style, Dim dim, array<float> spans);
}
}
