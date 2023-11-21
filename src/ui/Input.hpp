//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
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
	bool slider_input(Widget& parent, T& value, StatDef<T> def, Axis dim)
	{
		Widget& self = widget(parent, styles().slider_input);
		const SliderMetrics metrics = { float(def.m_min), float(def.m_max), float(def.m_step) };
		float slider_value = float(value);
		const bool changed = slider(self, slider_value, metrics, dim);
		value = T(slider_value);
		item(self, styles().slider_display, truncate_number(to_string(slider_value)));
		return changed;
	}

	export_ template <class T>
	bool number_type_in(Widget& parent, T& value)
	{
		string text = truncate_number(to_string(value));
		TextEdit& self = type_in(parent, text, 0, is_float<T> ? "1234567890." : "1234567890");
		if(self.m_changed)
		{
			value = to_value<T>(text);
			return true;
		}
		return false;
	}

	export_ template <class T>
	bool number_input(Widget& parent, T& value, StatDef<T> def)
	{
		Widget& self = widget(parent, styles().number_input);
		bool changed = false;

		changed |= number_type_in<T>(self, value);
		if(button(self, "+").activated())
		{
			changed = true;
			def.increment(value);
		}
		if(button(self, "-").activated())
		{
			changed |= true;
			def.decrement(value);
		}

		return changed;
	}

	export_ template <>
	inline bool number_input(Widget& parent, float& value, StatDef<float> def)
	{
		return drag_float(parent, value, def.m_step);
	}

	export_ template <class T>
	inline enable_if<is_number<T>, bool> input(Widget& parent, T& value, StatDef<T> def)
	{
		return number_input(parent, value, def);
	}

	export_ template <>
	inline bool input(Widget& parent, bool& value)
	{
		Widget& self = widget(parent, styles().input_bool);
		return checkbox(self, value).activated();
	}

	export_ template <>
	inline bool input(Widget& parent, string& value)
	{
		Widget& self = widget(parent, styles().input_string);
		return text_box(self, styles().type_in, value, false, 1).m_changed;
	}

	export_ template <>
	inline bool input(Widget& parent, vec3& value) { return vec3_edit(parent, value); }

	export_ template <>
	inline bool input(Widget& parent, quat& value) { return quat_edit(parent, value); }

	export_ template <>
	inline bool input(Widget& parent, Colour& value) { return color_toggle_edit(parent, value); }
}
}
