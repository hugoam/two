//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Stat.h>
#include <math/Colour.h>
//#include <math/Math.h>
#endif
#include <ui/Forward.h>
#include <ui/Button.h>
#include <ui/Sheet.h>

namespace mud
{
namespace ui
{
	export_ template <class T>
	bool slider_input_dim(Widget& parent, AutoStat<T> value, Dim dim = DIM_X);

	export_ template <class T>
	bool slider_input(Widget& parent, AutoStat<T> value);

	export_ template <class T>
	bool number_type_in(Widget& parent, T& value);

	export_ template <class T>
	bool number_input(Widget& parent, AutoStat<T> value);

	export_ MUD_UI_EXPORT func_ bool drag_float(Widget& parent, float& value, float step = 0.1f);

	export_ template <class T>
	inline bool input(Widget& parent, T& value);

	export_ MUD_UI_EXPORT func_ bool vec2_edit(Widget& parent, vec2& vec);
	export_ MUD_UI_EXPORT func_ bool vec3_edit(Widget& parent, vec3& vec);
	export_ MUD_UI_EXPORT func_ bool quat_edit(Widget& parent, quat& quat);

	export_ MUD_UI_EXPORT Widget& color_slab(Widget& parent, Style& style, const Colour& value);
	export_ MUD_UI_EXPORT func_ bool color_edit_hsl(Widget& parent, const Colour& colour, Colour& value);
	export_ MUD_UI_EXPORT func_ Widget& color_display(Widget& parent, const Colour& value);
	export_ MUD_UI_EXPORT func_ bool color_edit(Widget& parent, Colour& value);
	export_ MUD_UI_EXPORT func_ bool color_edit_simple(Widget& parent, Colour& value);
	export_ MUD_UI_EXPORT func_ bool color_toggle_edit(Widget& parent, Colour& value);

	export_ MUD_UI_EXPORT func_ bool curve_graph(Widget& parent, array<float> values, array<float> points = {});

	export_ MUD_UI_EXPORT func_ bool curve_edit(Widget& parent, array<float> values, array<float> points = {});

	export_ MUD_UI_EXPORT bool curve_edit(Widget& parent, array<Colour> values, array<float> points = {});

	export_ MUD_UI_EXPORT bool flag_input(Widget& parent, uint32_t& value, uint8_t shift);

	export_ template <class T_Input>
	bool field(T_Input input, Widget& parent, cstring name, bool reverse)
	{
		Widget& self = row(parent);
		if(!reverse) label(self, name);
		bool changed = input(self);
		if(reverse) label(self, name);
		return changed;
	}

	export_ template <class T>
	inline bool input_field(Widget& parent, cstring name, T& value, bool reverse = false) { return field([&](Widget& self) { return input<T>(self, value); }, parent, name, reverse); }

	export_ template <class T>
	inline bool number_field(Widget& parent, cstring name, AutoStat<T> value, bool reverse = false) { return field([&](Widget& self) { return number_input<T>(self, value); }, parent, name, reverse); }

	export_ template <class T>
	inline bool slider_field(Widget& parent, cstring name, AutoStat<T> value, bool reverse = false) { return field([&](Widget& self) { return slider_input<T>(self, value); }, parent, name, reverse); }

	export_ func_ inline bool flag_field(Widget& parent, cstring name, uint32_t& value, uint8_t shift, bool reverse = false) { return field([&](Widget& self) { return flag_input(self, value, shift); }, parent, name, reverse); }
	export_ func_ inline bool radio_field(Widget& parent, cstring name, array<cstring> choices, uint32_t& value, Dim dim = DIM_X, bool reverse = false) { return field([&](Widget& self) { return radio_switch(self, choices, value, dim); }, parent, name, reverse); }
	export_ func_ inline bool dropdown_field(Widget& parent, cstring name, array<cstring> choices, uint32_t& value, bool reverse = false) { return field([&](Widget& self) { return dropdown_input(self, choices, value); }, parent, name, reverse); }
	export_ func_ inline bool typedown_field(Widget& parent, cstring name, array<cstring> choices, uint32_t& value, bool reverse = false) { return field([&](Widget& self) { return typedown_input(self, choices, value); }, parent, name, reverse); }
	export_ func_ inline bool color_field(Widget& parent, cstring name, Colour& value, bool reverse = false) { return field([&](Widget& self) { return color_toggle_edit(self, value); }, parent, name, reverse); }
	export_ func_ inline void color_display_field(Widget& parent, cstring name, const Colour& value, bool reverse = false) { field([&](Widget& self) { color_display(self, value); return false; }, parent, name, reverse); }

	inline void field_label(Widget& parent, cstring field, cstring value)
	{
		Widget& self = row(parent);
		label(self, field);
		label(self, value);
	}
}
}
