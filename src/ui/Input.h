//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Button.h>
#include <ui/Sheet.h>

namespace two
{
namespace ui
{
	export_ template <class T>
	bool slider_input(NodeKey id, Widget parent, T& value, StatDef<T> def = {}, Axis dim = Axis::X);

	export_ template <class T>
	bool number_type_in(NodeKey id, Widget parent, T& value);

	export_ template <class T>
	bool number_input(NodeKey id, Widget parent, T& value, StatDef<T> def = {});

	export_ template <class T>
	bool drag_input(NodeKey id, Widget parent, T& value, StatDef<T> def = {}) { return number_input<T>(id, parent, value, def); }

	export_ TWO_UI_EXPORT func_ bool drag_float(NodeKey id, Widget parent, float& value, float step = 0.1f);
	
	export_ template <class T>
	enable_if<!is_number<T>, bool> input(NodeKey id, Widget parent, T& value);

	export_ template <class T>
	enable_if<is_number<T>, bool> input(NodeKey id, Widget parent, T& value, StatDef<T> def = {});

	export_ TWO_UI_EXPORT func_ bool float2_input(NodeKey id, Widget parent, span<cstring> labels, span<float> vals, StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f });
	export_ TWO_UI_EXPORT func_ bool float3_input(NodeKey id, Widget parent, span<cstring> labels, span<float> vals, StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f });
	export_ TWO_UI_EXPORT func_ bool float4_input(NodeKey id, Widget parent, span<cstring> labels, span<float> vals, StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f });

	//export_ TWO_UI_EXPORT func_ bool float2_slider(NodeKey id, Widget parent, span<cstring> labels, span<float> vals);
	//export_ TWO_UI_EXPORT func_ bool float3_slider(NodeKey id, Widget parent, span<cstring> labels, span<float> vals);
	//export_ TWO_UI_EXPORT func_ bool float4_slider(NodeKey id, Widget parent, span<cstring> labels, span<float> vals);

	export_ TWO_UI_EXPORT func_ bool float2_slider(NodeKey id, Widget parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def);
	export_ TWO_UI_EXPORT func_ bool float3_slider(NodeKey id, Widget parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def);
	export_ TWO_UI_EXPORT func_ bool float4_slider(NodeKey id, Widget parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def);

	export_ TWO_UI_EXPORT func_ bool vec2_edit(NodeKey id, Widget parent, vec2& vec);
	export_ TWO_UI_EXPORT func_ bool vec3_edit(NodeKey id, Widget parent, vec3& vec);
	export_ TWO_UI_EXPORT func_ bool quat_edit(NodeKey id, Widget parent, quat& quat);

	export_ TWO_UI_EXPORT Widget color_slab(NodeKey id, Widget parent, Style& style, const Colour& value);
	export_ TWO_UI_EXPORT bool color_edit_hsl(NodeKey id, Widget parent, const Colour& colour, ColourHSL& value);
	export_ TWO_UI_EXPORT func_ Widget color_display(NodeKey id, Widget parent, const Colour& value);
	export_ TWO_UI_EXPORT func_ bool color_edit(NodeKey id, Widget parent, Colour& value);
	export_ TWO_UI_EXPORT func_ bool color_edit_simple(NodeKey id, Widget parent, Colour& value);
	export_ TWO_UI_EXPORT func_ bool color_toggle_edit(NodeKey id, Widget parent, Colour& value);

	export_ TWO_UI_EXPORT func_ bool curve_graph(NodeKey id, Widget parent, span<float> values, span<float> points = {});

	export_ TWO_UI_EXPORT func_ bool curve_edit(NodeKey id, Widget parent, span<float> values, span<float> points = {});

	export_ TWO_UI_EXPORT bool curve_edit(NodeKey id, Widget parent, span<Colour> values, span<float> points = {});

	export_ TWO_UI_EXPORT bool flag_input(NodeKey id, Widget parent, uint32_t& value, uint8_t shift);

	export_ template <class T_Input>
	bool do_field(NodeKey id, T_Input input, Widget parent, cstring name, bool reverse)
	{
		Widget self = row(id, parent);
		if(!reverse) label(key(), self, name);
		bool changed = input(self);
		if(reverse) label(key(), self, name);
		return changed;
	}

	export_ template <class T>
	inline enable_if<!is_number<T>, bool> field(NodeKey id, Widget parent, cstring name, T& value, bool reverse = false) { return do_field(id, [&](Widget self) { return input<T>(key(), self, value); }, parent, name, reverse); }

	export_ template <class T>
	inline enable_if<is_number<T>, bool> field(NodeKey id, Widget parent, cstring name, T& value, StatDef<T> def = {}, bool reverse = false) { return do_field(id, [&](Widget self) { return number_input<T>(key(), self, value, def); }, parent, name, reverse); }
	
	export_ template <class T>
	inline bool drag_field(NodeKey id, Widget parent, cstring name, T& value, StatDef<T> def = {}, bool reverse = false) { return do_field(id, [&](Widget self) { return drag_input<T>(key(), self, value, def); }, parent, name, reverse); }

	export_ template <class T>
	inline bool slider_field(NodeKey id, Widget parent, cstring name, T& value, StatDef<T> def = {}, bool reverse = false) { return do_field(id, [&](Widget self) { return slider_input<T>(key(), self, value, def); }, parent, name, reverse); }

	export_ func_ inline bool flag_field(NodeKey id, Widget parent, cstring name, uint32_t& value, uint8_t shift, bool reverse = false) { return do_field(id, [&](Widget self) { return flag_input(key(), self, value, shift); }, parent, name, reverse); }
	export_ func_ inline bool radio_field(NodeKey id, Widget parent, cstring name, span<cstring> choices, uint32_t& value, Axis dim = Axis::X, bool reverse = false) { return do_field(id, [&](Widget self) { return radio_switch(key(), self, choices, value, dim); }, parent, name, reverse); }
	export_ func_ inline bool dropdown_field(NodeKey id, Widget parent, cstring name, span<cstring> choices, uint32_t& value, bool reverse = false) { return do_field(id, [&](Widget self) { return dropdown_input(key(), self, choices, value); }, parent, name, reverse); }
	export_ func_ inline bool typedown_field(NodeKey id, Widget parent, cstring name, span<cstring> choices, uint32_t& value, bool reverse = false) { return do_field(id, [&](Widget self) { return typedown_input(key(), self, choices, value); }, parent, name, reverse); }
	export_ func_ inline bool color_field(NodeKey id, Widget parent, cstring name, Colour& value, bool reverse = false) { return do_field(id, [&](Widget self) { return color_toggle_edit(key(), self, value); }, parent, name, reverse); }
	export_ func_ inline void color_display_field(NodeKey id, Widget parent, cstring name, const Colour& value, bool reverse = false) { do_field(id, [&](Widget self) { color_display(key(), self, value); return false; }, parent, name, reverse); }

	template <> func_ bool input<bool>(NodeKey id, Widget parent, bool& value);
	template <> func_ bool input<string>(NodeKey id, Widget parent, string& value);

	template <> func_ bool input<int>(NodeKey id, Widget parent, int& value, StatDef<int> def);
	template <> func_ bool input<float>(NodeKey id, Widget parent, float& value, StatDef<float> def);

	template <> func_ bool field<bool>(NodeKey id, Widget parent, cstring name, bool& value, bool reverse);
	template <> func_ bool field<string>(NodeKey id, Widget parent, cstring name, string& value, bool reverse);
	template <> func_ bool field<int>(NodeKey id, Widget parent, cstring name, int& value, StatDef<int> def, bool reverse);
	template <> func_ bool field<float>(NodeKey id, Widget parent, cstring name, float& value, StatDef<float> def, bool reverse);

	export_ inline void field_label(NodeKey id, Widget parent, cstring field, cstring value)
	{
		Widget self = row(id, parent);
		label(key(), self, field);
		label(key(), self, value);
	}
}
}
