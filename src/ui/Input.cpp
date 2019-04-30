//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <math/Vec.hpp>
#include <ui/Input.h>
#include <ui/Input.hpp>
#include <ui/Sheet.h>
#include <ui/Container.h>
#include <ui/ContainerStruct.h>
#include <ui/UiRoot.h>
#include <ui/UiRenderer.h>
#include <ui/Container.h>
#include <ui/Style/Skin.h>
#endif

#include <iostream>

namespace mud
{
namespace ui
{
	template bool slider_input(Widget& parent, AutoStat<int> value);
	template bool slider_input(Widget& parent, AutoStat<float> value);

	template bool number_input(Widget& parent, AutoStat<int> value);
	//template bool number_input(Widget& parent, AutoStat<float> value);

	//template bool input(Widget& parent, bool& value);
	template bool input(Widget& parent, int& value);
	template bool input(Widget& parent, float& value);
	//template bool input(Widget& parent, string& value);

	bool drag_float(Widget& parent, float& value, float step)
	{
		string text = truncate_number(to_string(value));
		TextEdit& self = type_in(parent, text, 0, "1234567890.");
		self.m_focus_mode = TextFocusMode::Click;
		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			self.clear_focus();
			value += event.m_delta.x * step;
			return true;
		}
		else if(self.m_changed)
		{
			value = to_value<float>(text);
			return true;
		}
		return false;
	}

	bool flag_input(Widget& parent, uint32_t& value, uint8_t shift)
	{
		Widget& self = widget(parent, styles().input_bool);
		bool enabled = (value & (1 << shift)) != 0;
		bool changed = checkbox(self, enabled).activated();
		if(enabled)
			value |= (1 << shift);
		else
			value &= ~(1 << shift);
		return changed;
	}

	bool float2_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		UNUSED(labels); // @todo
		Widget& self = ui::row(parent);
		bool changed = false;
		for(size_t i = 0; i < 2; ++i)
			changed |= ui::number_input<float>(self, { vals[i], def });
		return changed;
	}

	bool float3_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		UNUSED(labels); // @todo
		Widget& self = ui::row(parent);
		bool changed = false;
		for(size_t i = 0; i < 3; ++i)
			changed |= ui::number_input<float>(self, { vals[i], def });
		return changed;
	}

	bool float4_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		UNUSED(labels); // @todo
		Widget& self = ui::row(parent);
		bool changed = false;
		for(size_t i = 0; i < 4; ++i)
			changed |= ui::number_input<float>(self, { vals[i], def });
		return changed;
	}

	bool float2_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		Widget& self = ui::row(parent);
		bool changed = ui::float2_input(self, labels, vals, def);
		ui::label(self, label);
		return changed;
	}

	bool float3_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		Widget& self = ui::row(parent);
		bool changed = ui::float3_input(self, labels, vals, def);
		ui::label(self, label);
		return changed;
	}

	bool float4_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		Widget& self = ui::row(parent);
		bool changed = ui::float4_input(self, labels, vals, def);
		ui::label(self, label);
		return changed;
	}

	bool vec2_edit(Widget& parent, vec2& vec)
	{
		return float2_input(parent, {}, vec.f);
	}

	bool vec3_edit(Widget& parent, vec3& vec)
	{
		return float3_input(parent, {}, vec.f);
	}

	bool quat_edit(Widget& parent, quat& quat)
	{
		return float4_input(parent, {}, quat.f, { 0.f, 1.f, 0.01f });
	}

	constexpr float color_wheel_padding = 5.0f;
	constexpr float color_wheel_thickness = 20.0f;

	void draw_color_wheel(Vg& vg, const vec2& size, float hue, float s, float l)
	{
		const vec2 center = size * 0.5f;
		const float r1 = (size.x < size.y ? size.x : size.y) * 0.5f - color_wheel_padding;
		const float r0 = r1 - color_wheel_thickness;

		vg.draw_color_wheel(center, r0, r1);
		vg.draw_color_triangle(center, r0, hue, s, l);
	}

	bool inside_color_wheel(Widget& self, const MouseEvent& event)
	{
		const vec2 center = self.m_frame.m_size * 0.5f;
		const float r1 = center.x - color_wheel_padding;
		const float r0 = r1 - color_wheel_thickness;
		const float dist = distance(center, event.m_relative);
		return dist <= r1 && dist >= r0;
	}

	void drag_color_wheel(Widget& self, ColourHSL& hsla, const MouseEvent& event)
	{
		const vec2 coord = { event.m_relative.x, self.m_frame.m_size.y - event.m_relative.y };
		const vec2 center = self.m_frame.m_size * 0.5f;
		const vec2 vec = normalize(coord - center);
		const float angle = oriented_angle_2d(vec, vec2(1.f, 0.f));
		hsla.h = angle / c_2pi;
	}

	bool color_wheel(Widget& parent, ColourHSL& hsla)
	{
		Widget& self = widget(parent, styles().color_wheel);
		self.m_custom_draw = [=](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect);
			draw_color_wheel(vg, frame.m_size, hsla.h, hsla.s, hsla.l);
		};
		bool changed = false;

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
		{
			changed = true;
			if(inside_color_wheel(self, event))
				drag_color_wheel(self, hsla, event);
		}

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			changed = true;
			drag_color_wheel(self, hsla, event);
		}

		return changed;
	}

	bool color_edit_hsl(Widget& parent, const Colour& colour, ColourHSL& hsla)
	{
		static cstring columns[2] = { "field", "value" };
		Widget& self = table(parent, { columns, 2 }, {}); // , { 0.3f, 0.7f }
		color_display_field(self, "color", colour);

		bool changed = false;
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		changed |= slider_field<float>(self, "hue", { hsla.h, def });
		changed |= slider_field<float>(self, "saturation", { hsla.s, def });
		changed |= slider_field<float>(self, "lightness", { hsla.l, def });

		return changed;
	}

	bool color_edit_simple(Widget& parent, Colour& value)
	{
		Widget& self = widget(parent, styles().input_color);
		color_slab(self, styles().color_slab, value);

		bool changed = false;
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		changed |= slider_input<float>(self, { value.r, def });
		changed |= slider_input<float>(self, { value.g, def });
		changed |= slider_input<float>(self, { value.b, def });

		return changed;
	}

	bool color_edit(Widget& parent, Colour& value)
	{
		ColourHSL hsla = to_hsla(value);
		Widget& self = stack(parent);
		bool changed = false;
		changed |= color_wheel(self, hsla);
		changed |= color_edit_hsl(self, value, hsla);
		value = to_rgba(hsla);
		return changed;
	}

	bool color_popup(Widget& parent, Colour& value, bool& open)
	{
		Widget& self = popup(parent, styles().color_popup, PopupFlags(size_t(PopupFlags::Clamp) | size_t(PopupFlags::AutoModal)));
		open &= self.m_open;
		return color_edit(self, value);
	}

	Widget& color_slab(Widget& parent, Style& style, const Colour& value)
	{
		Widget& self = button(parent, style);//styles().color_slab);
		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect);
			vg.draw_rect({ vec2(0.f), frame.m_size }, value, frame.d_inkstyle->m_corner_radius);
		};
		return self;
	}

	Widget& color_display(Widget& parent, const Colour& value)
	{
		return color_slab(parent, styles().color_display, value);
	}

	bool color_toggle_edit(Widget& parent, Colour& value)
	{
		Widget& self = color_slab(parent, styles().color_toggle, value);
		if(self.activated())
			self.m_open = !self.m_open;
		if(self.m_open)
			return color_popup(self, value, self.m_open);
		return false;
	}

namespace
{
	struct Curve
	{
		Curve(const vec2& size, float min, float max, span<float> values, span<float> points)
			: m_min(min), m_max(max), m_values(values), m_points(points)
		{
			m_scale = size * vec2(1.f, max - min);
		}

		float m_min;
		float m_max;
		span<float> m_values;
		span<float> m_points;
		vec2 m_scale;

		vec2 point(size_t i)
		{
			float t = m_points.size() > 0 ? m_points[i] : i / float(m_values.size() - 1);
			return m_scale * vec2(t, (m_values[i] - m_min));
		}

		size_t point_at(vec2 position)
		{
			const float margin = 8.f;
			for(size_t i = 0; i < m_values.size(); ++i)
				if(distance(point(i), position) < margin)
					return i;
			return SIZE_MAX;
		}
	};
}

	void draw_curve(const Colour& colour, Curve& curve, size_t hovered, Vg& vg)
	{
		UNUSED(hovered);
		float distance = 100.f;
		Paint paint = { colour, 1.f };

		for(size_t i = 0; i < curve.m_values.size() - 1; ++i)
		{
			vec2 begin = curve.point(i);
			vec2 end = curve.point(i + 1);
			vg.path_bezier(begin, begin + vec2(distance, 0.f), end - vec2(distance, 0.f), end, false);
			vg.stroke(paint);
		}
	}

	void draw_points(const Colour& colour, Curve& curve, size_t hovered, Vg& vg)
	{
		Paint paint = { colour, 1.f };

		for(size_t i = 0; i < curve.m_values.size(); ++i)
		{
			vg.path_circle(curve.point(i), 5.f);
			vg.stroke(hovered == i ? Paint{ Colour::White, 1.f } : paint);
		}
	}

	bool curve_graph(Widget& parent, span<float> values, span<float> points)
	{
		const float lowest = 0.f;
		const float highest = 1.f;

		Widget& self = widget(parent, styles().curve_graph);
		Curve curve = { self.m_frame.content_rect().size, lowest, highest, values, points };
		
		static size_t hovered = SIZE_MAX;
		static size_t dragged = SIZE_MAX;

		if(self.ui().m_hovered == &self)
			hovered = curve.point_at(self.m_frame.local_position(self.ui().m_mouse.m_pos));

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			dragged = curve.point_at(event.m_relative);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			if(dragged != SIZE_MAX)
			{
				vec2 delta = event.m_delta / curve.m_scale;
				curve.m_values[dragged] = clamp(curve.m_values[dragged] + delta.y, lowest, highest);
			}

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Released))
			dragged = SIZE_MAX;

		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(frame); UNUSED(rect);
			Curve curve = { rect.size, 0.f, 1.f, values, points };
			vg.draw_rect(rect, { Colour::DarkGrey });
			draw_curve(Colour::NeonGreen, curve, hovered, vg);
			draw_points(Colour::NeonGreen, curve, hovered, vg);
		};

		return false;
	}

	bool curve_edit(Widget& parent, span<float> values, span<float> points)
	{
		Widget& self = widget(parent, styles().curve_input);
		curve_graph(self, values, points);
		return false;
	}

	bool curve_edit(Widget& parent, span<Colour> values, span<float> points)
	{
		UNUSED(parent); UNUSED(values); UNUSED(points);
		return false;
	}
}
}
