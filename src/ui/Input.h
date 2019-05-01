//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/traits.h>
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
	bool slider_input(Widget& parent, T& value, StatDef<T> def = {}, Axis dim = Axis::X);

	export_ template <class T>
	bool number_type_in(Widget& parent, T& value);

	export_ template <class T>
	bool number_input(Widget& parent, T& value, StatDef<T> def = {});

	export_ template <class T>
	bool drag_input(Widget& parent, T& value, StatDef<T> def = {}) { return number_input<T>(parent, value, def); }

	export_ MUD_UI_EXPORT func_ bool drag_float(Widget& parent, float& value, float step = 0.1f);
	
	export_ template <class T>
	inline enable_if<!is_number<T>, bool> input(Widget& parent, T& value);

	export_ template <class T>
	inline enable_if<is_number<T>, bool> input(Widget& parent, T& value, StatDef<T> def = {});

	export_ MUD_UI_EXPORT func_ bool float2_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f });
	export_ MUD_UI_EXPORT func_ bool float3_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f });
	export_ MUD_UI_EXPORT func_ bool float4_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f });

	//export_ MUD_UI_EXPORT func_ bool float2_slider(Widget& parent, span<cstring> labels, span<float> vals);
	//export_ MUD_UI_EXPORT func_ bool float3_slider(Widget& parent, span<cstring> labels, span<float> vals);
	//export_ MUD_UI_EXPORT func_ bool float4_slider(Widget& parent, span<cstring> labels, span<float> vals);

	export_ MUD_UI_EXPORT func_ bool float2_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def);
	export_ MUD_UI_EXPORT func_ bool float3_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def);
	export_ MUD_UI_EXPORT func_ bool float4_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def);

	export_ MUD_UI_EXPORT func_ bool vec2_edit(Widget& parent, vec2& vec);
	export_ MUD_UI_EXPORT func_ bool vec3_edit(Widget& parent, vec3& vec);
	export_ MUD_UI_EXPORT func_ bool quat_edit(Widget& parent, quat& quat);

	export_ MUD_UI_EXPORT Widget& color_slab(Widget& parent, Style& style, const Colour& value);
	export_ MUD_UI_EXPORT bool color_edit_hsl(Widget& parent, const Colour& colour, ColourHSL& value);
	export_ MUD_UI_EXPORT func_ Widget& color_display(Widget& parent, const Colour& value);
	export_ MUD_UI_EXPORT func_ bool color_edit(Widget& parent, Colour& value);
	export_ MUD_UI_EXPORT func_ bool color_edit_simple(Widget& parent, Colour& value);
	export_ MUD_UI_EXPORT func_ bool color_toggle_edit(Widget& parent, Colour& value);

	export_ MUD_UI_EXPORT func_ bool curve_graph(Widget& parent, span<float> values, span<float> points = {});

	export_ MUD_UI_EXPORT func_ bool curve_edit(Widget& parent, span<float> values, span<float> points = {});

	export_ MUD_UI_EXPORT bool curve_edit(Widget& parent, span<Colour> values, span<float> points = {});

	export_ MUD_UI_EXPORT bool flag_input(Widget& parent, uint32_t& value, uint8_t shift);

	export_ template <class T_Input>
	bool do_field(T_Input input, Widget& parent, cstring name, bool reverse)
	{
		Widget& self = row(parent);
		if(!reverse) label(self, name);
		bool changed = input(self);
		if(reverse) label(self, name);
		return changed;
	}

	export_ template <class T>
	inline enable_if<!is_number<T>, bool> field(Widget& parent, cstring name, T& value, bool reverse = false) { return do_field([&](Widget& self) { return input<T>(self, value); }, parent, name, reverse); }

	export_ template <class T>
	inline enable_if<is_number<T>, bool> field(Widget& parent, cstring name, T& value, StatDef<T> def = {}, bool reverse = false) { return do_field([&](Widget& self) { return number_input<T>(self, value, def); }, parent, name, reverse); }
	
	export_ template <class T>
	inline bool drag_field(Widget& parent, cstring name, T& value, StatDef<T> def = {}, bool reverse = false) { return do_field([&](Widget& self) { return drag_input<T>(self, value, def); }, parent, name, reverse); }

	export_ template <class T>
	inline bool slider_field(Widget& parent, cstring name, T& value, StatDef<T> def = {}, bool reverse = false) { return do_field([&](Widget& self) { return slider_input<T>(self, value, def); }, parent, name, reverse); }

	export_ func_ inline bool flag_field(Widget& parent, cstring name, uint32_t& value, uint8_t shift, bool reverse = false) { return do_field([&](Widget& self) { return flag_input(self, value, shift); }, parent, name, reverse); }
	export_ func_ inline bool radio_field(Widget& parent, cstring name, span<cstring> choices, uint32_t& value, Axis dim = Axis::X, bool reverse = false) { return do_field([&](Widget& self) { return radio_switch(self, choices, value, dim); }, parent, name, reverse); }
	export_ func_ inline bool dropdown_field(Widget& parent, cstring name, span<cstring> choices, uint32_t& value, bool reverse = false) { return do_field([&](Widget& self) { return dropdown_input(self, choices, value); }, parent, name, reverse); }
	export_ func_ inline bool typedown_field(Widget& parent, cstring name, span<cstring> choices, uint32_t& value, bool reverse = false) { return do_field([&](Widget& self) { return typedown_input(self, choices, value); }, parent, name, reverse); }
	export_ func_ inline bool color_field(Widget& parent, cstring name, Colour& value, bool reverse = false) { return do_field([&](Widget& self) { return color_toggle_edit(self, value); }, parent, name, reverse); }
	export_ func_ inline void color_display_field(Widget& parent, cstring name, const Colour& value, bool reverse = false) { do_field([&](Widget& self) { color_display(self, value); return false; }, parent, name, reverse); }

	export_ func_ extern template bool input<int>(Widget& parent, int& value, StatDef<int> def);
	export_ func_ extern template bool input<float>(Widget& parent, float& value, StatDef<float> def);

	inline void field_label(Widget& parent, cstring field, cstring value)
	{
		Widget& self = row(parent);
		label(self, field);
		label(self, value);
	}
}
}
