//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <ui/Style/Style.h>

namespace mud
{
	struct MUD_UI_EXPORT Styles
	{
		Styles();

		void setup(UiWindow& window);

		Style widget; Style wedge; Style root_sheet; Style item; Style control; Style spacer; Style filler; Style drag_handle;
		Style div; Style row; Style stack; Style sheet; Style flex; Style list; Style header; Style board; Style layout;
		Style screen; Style decal; Style overlay; Style gridsheet; Style wrap_control; Style label; Style title; Style text;
		Style button; Style wrap_button; Style multi_button; Style toggle; Style checkbox;
		Style dummy; Style tooltip; Style rectangle; Style type_in; Style type_zone; Style text_edit; Style caret; Style figure;
		Style radio_switch; Style radio_switch_h; Style radio_choice; Style radio_choice_item;
		Style slider; Style slider_knob; Style slider_display; Style fill_bar; Style number_input;
		Style slider_input; Style field_input; Style input_bool; Style input_string; Style input_color;
		Style color_wheel; Style color_slab; Style color_display; Style color_toggle;
		Style scrollsheet; Style scroll_zone; Style scroll_surface; Style scroll_plan; Style table; Style table_head; Style column_header;
		Style popup; Style modal; Style color_popup;
	};

	MUD_UI_EXPORT Styles& styles();
}
