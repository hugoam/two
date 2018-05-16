//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui/Slider.h>
#include <ui/Button.h>
#include <ui/Style/Styles.h>

#include <obj/String/StringConvert.h>

#include <ui/Structs/Widget.h>
#include <ctx/InputDevice.h>

namespace mud
{
namespace ui
{
	SliderMetrics::SliderMetrics(float min, float max, float step_length, float knob_length)
		: m_min(min)
		, m_max(max)
		, m_step_length(step_length)
		, m_knob_length(knob_length)
	{
		m_range = m_max + m_knob_length - m_min;
		m_num_steps = m_range / m_step_length + 1;
	}

	float SliderMetrics::offset(float cursor) const
	{
		return cursor / m_range;
	}

	float SliderMetrics::cursor(float value, float offset) const
	{
		int prev_step = int((value - m_min) / m_step_length);
		int step = int(round(offset * (m_num_steps - 1.f)));
		if(step != prev_step)
			return m_min + step * m_step_length;
		return value;
	}

	SliderState SliderMetrics::compute(float value)
	{
		SliderState state;
		state.m_knob_span = m_knob_length / m_range;
		state.m_pre_span = (value - m_min) / m_range;
		state.m_post_span = 1.f - state.m_pre_span - state.m_knob_span;
		return state;
	}

	bool slider_cursor(Frame& slider, Frame& knob, Dim dim, const MouseEvent& mouse_event, float& value, const SliderMetrics& metrics, bool relative)
	{
		if(relative)
		{
			float delta = mouse_event.m_delta[dim] / slider.m_size[dim];
			float cursor = min(1.f, max(0.f, metrics.offset(value) + delta));
			value = metrics.cursor(value, cursor);
		}
		else
		{
			vec2 position = slider.local_position(mouse_event.m_pos);
			float offset = -knob.m_size[dim] / 2.f;
			float cursor = min(slider.m_size[dim]/* - knob.m_size[dim]*/, max(0.f, position[dim] + offset)) / slider.m_size[dim];
			value = metrics.cursor(value, cursor);
		}
		return true;
	}

	bool slider_logic(Widget& self, Frame& slider, Frame& filler, Frame& knob, float& value, const SliderMetrics& metrics, Dim dim, bool relative)
	{
		bool changed = false;

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			changed |= slider_cursor(slider, knob, dim, mouse_event, value, metrics, relative);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
			self.enableState(PRESSED);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			changed |= slider_cursor(slider, knob, dim, mouse_event, value, metrics, relative);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
			self.disableState(PRESSED);

		return changed;
	}

	bool slider(Widget& parent, Style& style, float& value, SliderMetrics metrics, Dim dim, bool relative, bool fill, Style* knob_style)
	{
		Widget& self = widget(parent, style, false, dim);

		SliderState state = metrics.compute(value);
		Widget& filler = spanner(self, fill ? styles().filler : styles().spacer, dim, state.m_pre_span);
		Widget& button = spanner(self, knob_style ? *knob_style : styles().slider_knob, dim, state.m_knob_span);
		spanner(self, styles().spacer, dim, state.m_post_span);
		
		bool changed = false;
		changed |= slider_logic(self, self.m_frame, filler.m_frame, button.m_frame, value, metrics, dim, false);
		changed |= slider_logic(button, self.m_frame, filler.m_frame, button.m_frame, value, metrics, dim, relative);
		return changed;
	}

	bool slider(Widget& parent, float& value, SliderMetrics metrics, Dim dim, bool relative, bool fill, Style* knob_style)
	{
		return slider(parent, styles().slider, value, metrics, dim, relative, fill, knob_style);
	}
}
}
