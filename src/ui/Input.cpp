//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <math/VecOps.h>
#include <math/Clamp.h>
#include <ui/Input.h>
#include <ui/Sheet.h>
#include <ui/Container.h>
#include <ui/Structs/Container.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Render/Renderer.h>
#include <ui/Container.h>
#include <ui/Style/Skin.h>
#endif

namespace mud
{
namespace ui
{
	bool drag_float(Widget& parent, float& value, float step)
	{
		string text = truncate_number(to_string(value));
		TextEdit& self = type_in(parent, text, 0, "1234567890.");
		self.m_focus_mode = TextFocusMode::Click;
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			self.clear_focus();
			value += mouse_event.m_delta.x * step;
			return true;
		}
		else if(self.m_changed)
		{
			value = from_string<float>(text);
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
	
	bool vec2_edit(Widget& parent, vec2& vec)
	{
		Widget& self = ui::row(parent);
		StatDef<float> def = { std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), 0.01f };
		bool changed = false;
		changed |= ui::number_input<float>(self, { vec.x, def });
		changed |= ui::number_input<float>(self, { vec.y, def });
		return changed;
	}

	bool vec3_edit(Widget& parent, vec3& vec)
	{
		Widget& self = ui::row(parent);
		StatDef<float> def = { std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), 0.01f };
		bool changed = false;
		changed |= ui::number_input<float>(self, { vec.x, def });
		changed |= ui::number_input<float>(self, { vec.y, def });
		changed |= ui::number_input<float>(self, { vec.z, def });
		return changed;
	}

	bool quat_edit(Widget& parent, quat& quat)
	{
		Widget& self = ui::row(parent);
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		bool changed = false;
		changed |= ui::number_input<float>(self, { quat.x, def });
		changed |= ui::number_input<float>(self, { quat.y, def });
		changed |= ui::number_input<float>(self, { quat.z, def });
		changed |= ui::number_input<float>(self, { quat.w, def });
		return changed;
	}

	void draw_color_wheel(Vg& vg, const vec2& size, float hue, float s, float l)
	{
		vec2 center = size * 0.5f;
		float r1 = (size.x < size.y ? size.x : size.y) * 0.5f - 5.0f;
		float r0 = r1 - 20.0f;

		vg.draw_color_wheel(center, r0, r1);
		vg.draw_color_triangle(center, r0, hue, s, l);
	}

	bool inside_color_wheel(Widget& self, const MouseEvent& event)
	{
		vec2 center = self.m_frame.m_size * 0.5f;
		float r1 = center.x - 5.0f;
		float r0 = r1 - 20.0f;
		float dist = distance(center, event.m_relative);
		return dist <= r1 && dist >= r0;
	}

	void drag_color_wheel(Widget& self, Colour& hsla, const MouseEvent& event)
	{
		vec2 coord = { event.m_relative.x, self.m_frame.m_size.y - event.m_relative.y };
		vec2 center = self.m_frame.m_size * 0.5f;
		float angle = oriented_angle_2d(normalize(coord - center), { 1.f, 0.f });
		hsla.m_h = angle / (c_pi * 2.f);
	}

	bool color_wheel(Widget& parent, Colour& hsla)
	{
		Widget& self = widget(parent, styles().color_wheel);
		self.m_custom_draw = [=](const Frame& frame, const vec4& rect, Vg& vg) { UNUSED(rect); draw_color_wheel(vg, frame.m_size, hsla.m_h, hsla.m_s, hsla.m_l); };
		bool changed = false;

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
		{
			changed = true;
			if(inside_color_wheel(self, mouse_event))
				drag_color_wheel(self, hsla, mouse_event);
		}

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			changed = true;
			drag_color_wheel(self, hsla, mouse_event);
		}

		return changed;
	}

	bool color_edit_hsl(Widget& parent, const Colour& colour, Colour& hsla)
	{
		static cstring columns[2] = { "field", "value" };
		Widget& self = table(parent, { columns, 2 }, {}); // , { 0.3f, 0.7f }
		color_display_field(self, "color", colour);

		bool changed = false;
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		changed |= slider_field<float>(self, "hue", { hsla.m_h, def });
		changed |= slider_field<float>(self, "saturation", { hsla.m_s, def });
		changed |= slider_field<float>(self, "lightness", { hsla.m_l, def });

		return changed;
	}

	bool color_edit_simple(Widget& parent, Colour& value)
	{
		Widget& self = widget(parent, styles().input_color);
		color_slab(self, styles().color_slab, value);

		bool changed = false;
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		changed |= slider_input<float>(self, { value.m_r, def });
		changed |= slider_input<float>(self, { value.m_g, def });
		changed |= slider_input<float>(self, { value.m_b, def });

		return changed;
	}

	bool color_edit(Widget& parent, Colour& value)
	{
		Colour hsla = rgba_to_hsla(value);
		Widget& self = stack(parent);
		bool changed = false;
		changed |= color_wheel(self, hsla);
		changed |= color_edit_hsl(self, value, hsla);
		value = hsla_to_rgba(hsla);
		return changed;
	}

	bool color_popup(Widget& parent, Colour& value, bool& open)
	{
		Widget& self = popup(parent, styles().color_popup, PopupFlags(size_t(PopupFlags::Clamp) | size_t(PopupFlags::Modal)));
		open &= self.m_open;
		return color_edit(self, value);
	}

	Widget& color_slab(Widget& parent, Style& style, const Colour& value)
	{
		Widget& self = button(parent, style);//styles().color_slab);
		self.m_custom_draw = [=](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect);
			vg.draw_rect({ Zero2, frame.m_size }, { value }, frame.d_inkstyle->m_corner_radius);
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
		Curve(const vec2& size, float min, float max, array<float> values, array<float> points)
			: m_min(min), m_max(max), m_values(values), m_points(points)
		{
			m_scale = size * vec2{ 1.f, max - min };
		}

		float m_min;
		float m_max;
		array<float> m_values;
		array<float> m_points;
		vec2 m_scale;

		vec2 point(size_t i)
		{
			float t = m_points.size() > 0 ? m_points[i] : i / float(m_values.size() - 1);
			return m_scale * vec2{ t, (m_values[i] - m_min) };
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
		float distance = 100.f;
		Paint paint = { colour, 1.f };

		for(size_t i = 0; i < curve.m_values.size() - 1; ++i)
		{
			vec2 begin = curve.point(i);
			vec2 end = curve.point(i + 1);
			vg.path_bezier(begin, begin + vec2{ distance, 0.f }, end - vec2{ distance, 0.f }, end, false);
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

	bool curve_graph(Widget& parent, array<float> values, array<float> points)
	{
		const float lowest = 0.f;
		const float highest = 1.f;

		Widget& self = widget(parent, styles().curve_graph);
		Curve curve = { rect_size(self.m_frame.content_rect()), lowest, highest, values, points };
		
		static size_t hovered = SIZE_MAX;
		static size_t dragged = SIZE_MAX;

		if(self.root_sheet().m_hovered == &self)
			hovered = curve.point_at(self.m_frame.local_position(self.root_sheet().m_mouse.m_pos));

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			dragged = curve.point_at(mouse_event.m_relative);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			if(dragged != SIZE_MAX)
			{
				vec2 delta = mouse_event.m_delta / curve.m_scale;
				curve.m_values[dragged] = std::clamp(curve.m_values[dragged] + delta.y, lowest, highest);
			}

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Released))
			dragged = SIZE_MAX;

		self.m_custom_draw = [=](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(frame); UNUSED(rect);
			Curve curve = { rect_size(rect), 0.f, 1.f, values, points };
			vg.draw_rect(rect, { Colour::DarkGrey });
			draw_curve(Colour::NeonGreen, curve, hovered, vg);
			draw_points(Colour::NeonGreen, curve, hovered, vg);
		};

		return false;
	}

	bool curve_edit(Widget& parent, array<float> values, array<float> points)
	{
		Widget& self = widget(parent, styles().curve_input);
		curve_graph(self, values, points);
		return false;
	}

	bool curve_edit(Widget& parent, array<Colour> values, array<float> points)
	{
		UNUSED(parent); UNUSED(values); UNUSED(points);
		return false;
	}
}
}
