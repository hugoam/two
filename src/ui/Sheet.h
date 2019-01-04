//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Widget.h>
#include <ui/Button.h>
#include <ui/Style/Styles.h>

namespace mud
{
namespace ui
{
	export_ struct DragPoint
	{
		Frame* prev = nullptr;
		Frame* next = nullptr;
	};

	export_ func_ inline Widget& row(Widget& parent) { return widget(parent, styles().row); }
	export_ func_ inline Widget& header(Widget& parent) { return widget(parent, styles().header); }
	export_ func_ inline Widget& div(Widget& parent) { return widget(parent, styles().div); }
	export_ func_ inline Widget& stack(Widget& parent) { return widget(parent, styles().stack); }
	export_ func_ inline Widget& sheet(Widget& parent) { return widget(parent, styles().sheet); }
	export_ func_ inline Widget& board(Widget& parent) { return widget(parent, styles().board); }
	export_ func_ inline Widget& layout(Widget& parent) { return widget(parent, styles().layout); }
	export_ func_ inline Widget& screen(Widget& parent) { return widget(parent, styles().screen); }
	export_ func_ inline Widget& decal(Widget& parent) { return widget(parent, styles().decal); }
	export_ func_ inline Widget& overlay(Widget& parent) { return widget(parent, styles().overlay); }

	export_ func_ inline Widget& title_header(Widget& parent, cstring title)
	{
		Widget& self = ui::header(parent);
		ui::label(self, title);
		return self;
	}

	export_ MUD_UI_EXPORT func_ Widget& dummy(Widget& parent, const vec2& size);

	export_ MUD_UI_EXPORT Widget& layout_span(Widget& parent, float span);

	export_ MUD_UI_EXPORT Widget& popup(Widget& parent, Style& style, PopupFlags flags);
	export_ MUD_UI_EXPORT Widget& popup(Widget& parent, Style& style, const vec2& size, PopupFlags flags);
	export_ MUD_UI_EXPORT Widget& popup_at(Widget& parent, Style& style, const vec2& position, PopupFlags flags);

	export_ func_ inline Widget& popup(Widget& parent, PopupFlags flags) { return popup(parent, styles().popup, flags); }
	export_ func_ inline Widget& popup(Widget& parent, const vec2& size, PopupFlags flags = PopupFlags::None) { return popup(parent, styles().popup, size, flags); }
	export_ func_ inline Widget& popup_at(Widget& parent, const vec2& position, PopupFlags flags = PopupFlags::None) { return popup_at(parent, styles().popup, position, flags); }

	export_ func_ inline Widget& modal(Widget& parent) { return popup(parent, styles().modal, PopupFlags::Modal); }
	export_ func_ inline Widget& modal(Widget& parent, const vec2& size) { return popup(parent, styles().modal, size, PopupFlags::Modal); }

	export_ func_ MUD_UI_EXPORT Widget& auto_modal(Widget& parent, uint32_t mode);
	export_ func_ MUD_UI_EXPORT Widget& auto_modal(Widget& parent, uint32_t mode, const vec2& size);

	export_ func_ MUD_UI_EXPORT Widget* context(Widget& parent, uint32_t mode, PopupFlags flags = PopupFlags::None);

	export_ MUD_UI_EXPORT DragPoint grid_sheet_logic(Widget& self, Dim dim);
	export_ MUD_UI_EXPORT Widget& grid_sheet(Widget& parent, Style& style, Dim dim);
	export_ MUD_UI_EXPORT Widget& grid_sheet(Widget& parent, Style& style, Dim dim, array<float> spans);
}
}
