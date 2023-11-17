//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Style/Style.h>

namespace two
{
	export_ struct TWO_UI_EXPORT Styles
	{
		void setup(UiWindow& window);
		void reset();

		Style widget; Style wedge; Style ui; Style unit; Style item; Style control; Style wrap_control; Style spacer; Style separator; Style filler; Style drag_handle;
		Style div; Style row; Style stack; Style sheet; Style flex; Style list; Style header; Style board; Style layout; Style indent;
		Style screen; Style decal; Style overlay; Style gridsheet; Style sequence; Style element;
		Style label; Style title; Style message; Style text; Style bullet; Style button; Style wrap_button; Style multi_button; Style toggle; Style checkbox; Style checkmark;
		Style dummy; Style tooltip; Style rectangle; Style viewport; Style type_in; Style text_edit; Style type_zone; Style caret; Style image; Style image_stretch;
		Style radio_switch; Style radio_switch_h; Style radio_choice; Style radio_choice_item;
		Style slider; Style slider_knob; Style slider_display; Style fill_bar; Style number_input;
		Style slider_input; Style field_input; Style curve_graph; Style curve_input; Style input_bool; Style input_string; Style input_color;
		Style color_wheel; Style color_slab; Style color_display; Style color_toggle;
		Style scrollsheet; Style scroll_zone; Style scroll_surface; Style scroll_plan; Style table; Style table_head; Style column_header;
		Style popup; Style modal; Style color_popup;
	};

	export_ TWO_UI_EXPORT Styles& styles();

	extern map<string, Style*> g_styles;
}
