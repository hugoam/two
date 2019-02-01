//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Type.h>
#include <math/Stat.hpp>
#include <math/Colour.h>
#include <math/Math.h>
#endif
#include <ui/Forward.h>
#include <ui/Style/Styles.h>
#include <ui/Sheet.h>
#include <ui/Slider.h>
#include <ui/Edit/TypeIn.h>

namespace mud
{
namespace ui
{
	export_ template <class T>
	bool slider_input_dim(Widget& parent, AutoStat<T> value, Dim dim)
	{
		Widget& self = widget(parent, styles().slider_input);
		SliderMetrics metrics = { float(value.min()), float(value.max()), float(value.step()) };
		float slider_value = float(value);
		bool changed = slider(self, slider_value, metrics, dim);
		value.ref() = T(slider_value);
		item(self, styles().slider_display, truncate_number(to_string(slider_value)));
		return changed;
	}

	export_ template <class T>
	bool slider_input(Widget& parent, AutoStat<T> value)
	{
		return slider_input_dim(parent, value, DIM_X);
	}

	export_ template <class T>
	bool is_scalar() { return type<T>().template is<float>() || type<T>().template is<double>(); }

	export_ template <class T>
	bool number_type_in(Widget& parent, T& value)
	{
		string text = truncate_number(to_string(value));
		TextEdit& self = type_in(parent, text, 0, is_scalar<T>() ? "1234567890." : "1234567890");
		if(self.m_changed)
		{
			value = to_value<T>(text);
			return true;
		}
		return false;
	}

	export_ template <class T>
	bool number_input(Widget& parent, AutoStat<T> value)
	{
		Widget& self = widget(parent, styles().number_input);
		bool changed = false;

		changed |= number_type_in<T>(self, value.ref());
		if(button(self, "+").activated())
		{
			changed = true;
			value.increment();
		}
		if(button(self, "-").activated())
		{
			changed |= true;
			value.decrement();
		}

		return changed;
	}

	export_ template <>
	inline bool number_input(Widget& parent, AutoStat<float> value)
	{
		return drag_float(parent, value.ref(), value.step());
	}

	export_ template <class T>
	inline bool input(Widget& parent, T& value)
	{
		return number_input(parent, AutoStat<T>{ value, StatDef<T>{} });
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
