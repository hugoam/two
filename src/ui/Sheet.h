//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Widget.h>
#include <ui/Button.h>
#include <ui/Style/Styles.h>

namespace two
{
namespace ui
{
	export_ struct DragPoint
	{
		Frame* prev = nullptr;
		Frame* next = nullptr;
	};

	export_ func_ inline Widget& row(NodeKey id, Widget& parent) { return widget(id, parent, styles().row); }
	export_ func_ inline Widget& header(NodeKey id, Widget& parent) { return widget(id, parent, styles().header); }
	export_ func_ inline Widget& div(NodeKey id, Widget& parent) { return widget(id, parent, styles().div); }
	export_ func_ inline Widget& stack(NodeKey id, Widget& parent) { return widget(id, parent, styles().stack); }
	export_ func_ inline Widget& sheet(NodeKey id, Widget& parent) { return widget(id, parent, styles().sheet); }
	export_ func_ inline Widget& board(NodeKey id, Widget& parent) { return widget(id, parent, styles().board); }
	export_ func_ inline Widget& layout(NodeKey id, Widget& parent) { return widget(id, parent, styles().layout); }
	export_ func_ inline Widget& indent(NodeKey id, Widget& parent) { return widget(id, parent, styles().indent); }
	export_ func_ inline Widget& screen(NodeKey id, Widget& parent) { return widget(id, parent, styles().screen); }
	export_ func_ inline Widget& decal(NodeKey id, Widget& parent) { return widget(id, parent, styles().decal); }
	export_ func_ inline Widget& overlay(NodeKey id, Widget& parent) { return widget(id, parent, styles().overlay); }

	export_ func_ inline Widget& title_header(NodeKey id, Widget& parent, cstring title)
	{
		Widget& self = ui::header(id, parent);
		ui::label(key(), self, title);
		return self;
	}

	export_ TWO_UI_EXPORT func_ Widget& dummy(NodeKey id, Widget& parent, const vec2& size);

	export_ TWO_UI_EXPORT Widget& layout_span(NodeKey id, Widget& parent, float span);

	export_ TWO_UI_EXPORT Widget& popup(NodeKey id, Widget& parent, Style& style, PopupFlags flags);
	export_ TWO_UI_EXPORT Widget& popup(NodeKey id, Widget& parent, Style& style, const vec2& size, PopupFlags flags);
	export_ TWO_UI_EXPORT Widget& popup_at(NodeKey id, Widget& parent, Style& style, const vec2& position, PopupFlags flags);

	export_ func_ inline Widget& popup(NodeKey id, Widget& parent, PopupFlags flags) { return popup(id, parent, styles().popup, flags); }
	export_ func_ inline Widget& popup(NodeKey id, Widget& parent, const vec2& size, PopupFlags flags = ui::PopupFlags::None) { return popup(id, parent, styles().popup, size, flags); }
	export_ func_ inline Widget& popup_at(NodeKey id, Widget& parent, const vec2& position, PopupFlags flags = ui::PopupFlags::None) { return popup_at(id, parent, styles().popup, position, flags); }

	export_ func_ inline Widget& modal(NodeKey id, Widget& parent) { return popup(id, parent, styles().modal, PopupFlags::Modal); }
	export_ func_ inline Widget& modal(NodeKey id, Widget& parent, const vec2& size) { return popup(id, parent, styles().modal, size, PopupFlags::Modal); }

	export_ func_ TWO_UI_EXPORT Widget& auto_modal(NodeKey id, Widget& parent, uint32_t mode);
	export_ func_ TWO_UI_EXPORT Widget& auto_modal(NodeKey id, Widget& parent, uint32_t mode, const vec2& size);

	export_ func_ TWO_UI_EXPORT Widget* context(NodeKey id, Widget& parent, uint32_t mode, PopupFlags flags = ui::PopupFlags::None);

	export_ TWO_UI_EXPORT DragPoint grid_sheet_logic(Widget& self, Axis dim);
	export_ TWO_UI_EXPORT Widget& grid_sheet(NodeKey id, Widget& parent, Style& style, Axis dim);
	export_ TWO_UI_EXPORT Widget& grid_sheet(NodeKey id, Widget& parent, Style& style, Axis dim, span<float> spans);
}
}
