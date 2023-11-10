//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#include <cfloat>

#ifdef TWO_MODULES
module two.ui;
#else
#include <tree/Graph.hpp>
#include <math/Vec.hpp>
#include <ui/ScrollSheet.h>
#include <ui/ContainerStruct.h>
#include <ui/Frame/Frame.h>
#include <ui/UiRenderer.h>
#include <ui/Style/Paint.h>
#endif

namespace two
{
namespace ui
{
	void draw_grid(const Frame& frame, float frequency, const Paint& paint, Vg& vg)
	{
		float start = frequency;

		for(float val = start; val < frame.m_size.x; val += frequency)
		{
			vg.path_line({ val, 0.f }, { val, frame.m_size.y });
			vg.stroke(paint);
		}
		for(float val = start; val < frame.m_size.y; val += frequency)
		{
			vg.path_line({ 0.f, val }, { frame.m_size.x, val });
			vg.stroke(paint);
		}

		vg.stroke(paint);
	}

	void draw_grid(const Frame& frame, const vec4& rect, Vg& vg)
	{
		UNUSED(rect);
		static const Paint main_paint = Paint(Colour(0.162f), 1.f);
		static const Paint second_paint = Paint(Colour(0.094f), 0.5f);

		draw_grid(frame, 20.0f, second_paint, vg);
		draw_grid(frame, 100.f, main_paint, vg);
	}

	void scroll_plan_drag(Frame& scroll_zone, Frame& scroll_plan, const MouseEvent& event)
	{
		const vec2 position = scroll_plan.m_position + event.m_delta;
		const vec2 overflow = (scroll_plan.m_size * scroll_plan.m_scale) - scroll_zone.m_size;
		scroll_plan.set_position(min(vec2(0.f), max(position, -overflow)));
		//m_frame.mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void scroll_plan_drag(ScrollSheet& scroll_sheet, const MouseEvent& mouse_event)
	{
		return scroll_plan_drag(scroll_sheet.m_scroll_zone->m_frame, scroll_sheet.m_body->m_frame, mouse_event);
	}

	void scroll_plan_zoom(Frame& scroll_zone, Frame& scroll_plan, const MouseEvent& mouse_event, bool clamped)
	{
		const float delta_scale = mouse_event.m_deltaZ > 0.f ? 1.2f : 0.8333f;
		scroll_plan.m_scale = scroll_plan.m_scale * delta_scale;

		if(clamped)
		{
			const vec2 min_scale = scroll_zone.m_size / scroll_plan.m_size;
			scroll_plan.m_scale = max(scroll_plan.m_scale, max(min_scale.x, min_scale.y));
		}

		const vec2 relative = mouse_event.m_pos - scroll_plan.absolute_position();
		const vec2 offset = relative - relative * delta_scale;
		const vec2 position = offset + scroll_plan.m_position;

		if(clamped)
			scroll_plan.set_position(min(vec2(0.f), position));
		else
			scroll_plan.set_position(position);
	}

	void scroll_plan_zoom(ScrollSheet& scroll_sheet, const MouseEvent& mouse_event, bool clamped)
	{
		return scroll_plan_zoom(scroll_sheet.m_scroll_zone->m_frame, scroll_sheet.m_body->m_frame, mouse_event, clamped);
	}

	ScrollSheet& scroll_sheet(Widget& parent, Style& style, Style* surface_style)
	{
		ScrollSheet& self = twidget<ScrollSheet>(parent, style);
		self.m_scroll_zone = &widget(self, styles().scroll_zone, false, Axis::None, { 0, 0 });
		self.m_body = &widget(*self.m_scroll_zone, surface_style ? *surface_style : styles().scroll_surface);

		scrollbar(self, self.m_scroll_zone->m_frame, self.m_body->m_frame, Axis::X, { 0, 1 });
		scrollbar(self, self.m_scroll_zone->m_frame, self.m_body->m_frame, Axis::Y, { 1, 0 });

#if 0
		if(MouseEvent event = self.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
		{
			self.m_body->m_frame.set_position(Axis::X, self.m_body->m_frame.m_position[Axis::X] - event.m_delta.x);
			self.m_body->m_frame.set_position(Axis::Y, self.m_body->m_frame.m_position[Axis::Y] - event.m_delta.y);
			self.m_body->m_frame.set_position(Axis::Y, self.m_body->m_frame.m_position[Axis::Y] - 10.f * mouse_event.m_deltaZ);
		}
#endif

		return self;
	}

	ScrollSheet& scroll_plan(Widget& parent, Style& style)
	{
		static const bool clamped = true;

		ScrollSheet& self = scroll_sheet(parent, style, &styles().scroll_plan);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseMiddle, EventType::Dragged))
			scroll_plan_drag(self, event);
		if(MouseEvent event = self.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
			scroll_plan_zoom(self, event, clamped);
		
		return self;
	}

	void autofit_scroll_plan(ScrollSheet& scroll_sheet, span<Widget*> elements)
	{
		if(elements.size() == 0)
			return;

		Frame& scroll_plan = scroll_sheet.m_body->m_frame;

		const float margin = 1000.f;
		vec2 bounds_min = vec2(FLT_MAX);
		vec2 bounds_max = vec2(FLT_MIN);

		for(Widget* widget : elements)
		{
			bounds_min = min(widget->m_frame.m_position, bounds_min);
			bounds_max = max(widget->m_frame.m_position + widget->m_frame.m_size, bounds_max);
			//offset = min(vec2(widget->m_frame.m_position - margin));
		}

		vec2 offset = vec2(margin) - bounds_min;
		const vec2 remainder = mod(offset, vec2(100.f));
		offset = offset - remainder;

		for(Widget* widget : elements)
			widget->m_frame.m_position += offset;

		scroll_plan.m_position += -offset * scroll_plan.m_scale;

		const vec2 bounds = bounds_max + 2.f * margin - bounds_min;
		scroll_plan.m_size = bounds;
	}

	Widget& scrollable(Widget& parent)
	{
		return *scroll_sheet(parent).m_body;
	}
}
}
