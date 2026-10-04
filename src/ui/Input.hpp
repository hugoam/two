//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Input.h>
#include <ui/Slider.h>
#include <ui/Edit/TypeIn.h>
#include <ui/Style/Styles.h>

namespace two
{
namespace ui
{
	export_ template <class T>
	bool slider_input(NodeKey id, Widget& parent, T& value, StatDef<T> def, Axis dim)
	{
		Widget& self = widget(id, parent, styles().slider_input);
		const SliderMetrics metrics = { float(def.m_min), float(def.m_max), float(def.m_step) };
		float slider_value = float(value);
		const bool changed = slider(key(), self, slider_value, metrics, dim);
		value = T(slider_value);
		item(key(), self, styles().slider_display, truncate_number(to_string(slider_value)));
		return changed;
	}

	export_ template <class T>
	bool number_type_in(NodeKey id, Widget& parent, T& value)
	{
		string text = truncate_number(to_string(value));
		TextEdit& self = type_in(id, parent, text, 0, is_float<T> ? "1234567890." : "1234567890");
		if(self.m_changed)
		{
			value = to_value<T>(text);
			return true;
		}
		return false;
	}

	export_ template <class T>
	bool number_input(NodeKey id, Widget& parent, T& value, StatDef<T> def)
	{
		Widget& self = widget(id, parent, styles().number_input);
		bool changed = false;

		changed |= number_type_in<T>(key(), self, value);
		if(button(key(), self, "+").activated())
		{
			changed = true;
			def.increment(value);
		}
		if(button(key(), self, "-").activated())
		{
			changed |= true;
			def.decrement(value);
		}

		return changed;
	}

	template <>
	inline bool number_input(NodeKey id, Widget& parent, float& value, StatDef<float> def)
	{
		return drag_float(id, parent, value, def.m_step);
	}

	export_ template <class T>
	inline enable_if<is_number<T>, bool> input(NodeKey id, Widget& parent, T& value, StatDef<T> def)
	{
		return number_input(id, parent, value, def);
	}

	template <>
	inline bool input(NodeKey id, Widget& parent, bool& value)
	{
		Widget& self = widget(id, parent, styles().input_bool);
		return checkbox(key(), self, value).activated();
	}

	template <>
	inline bool input(NodeKey id, Widget& parent, string& value)
	{
		Widget& self = widget(id, parent, styles().input_string);
		return text_box(key(), self, styles().type_in, value, false, 1).m_changed;
	}

	template <>
	inline bool input(NodeKey id, Widget& parent, int& value, StatDef<int> def) { return number_input(id, parent, value, def); }

	template <>
	inline bool input(NodeKey id, Widget& parent, float& value, StatDef<float> def) { return number_input(id, parent, value, def); }

	template <>
	inline bool field(NodeKey id, Widget& parent, cstring name, bool& value, bool reverse) { return do_field(id, [&](Widget& self) { return input<bool>(key(), self, value); }, parent, name, reverse); }

	template <>
	inline bool field(NodeKey id, Widget& parent, cstring name, string& value, bool reverse) { return do_field(id, [&](Widget& self) { return input<string>(key(), self, value); }, parent, name, reverse); }

	template <>
	inline bool field(NodeKey id, Widget& parent, cstring name, int& value, StatDef<int> def, bool reverse) { return do_field(id, [&](Widget& self) { return number_input<int>(key(), self, value, def); }, parent, name, reverse); }

	template <>
	inline bool field(NodeKey id, Widget& parent, cstring name, float& value, StatDef<float> def, bool reverse) { return do_field(id, [&](Widget& self) { return number_input<float>(key(), self, value, def); }, parent, name, reverse); }

	template <>
	inline bool input(NodeKey id, Widget& parent, vec3& value) { return vec3_edit(id, parent, value); }

	template <>
	inline bool input(NodeKey id, Widget& parent, quat& value) { return quat_edit(id, parent, value); }

	template <>
	inline bool input(NodeKey id, Widget& parent, Colour& value) { return color_toggle_edit(id, parent, value); }
}
}
