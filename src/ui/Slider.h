//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Button.h>

namespace mud
{
namespace ui
{
	export_ struct MUD_UI_EXPORT SliderState
	{
		float m_pre_span;
		float m_knob_span;
		float m_post_span;
	};

	export_ struct MUD_UI_EXPORT SliderMetrics
	{
		SliderMetrics(float min, float max, float step_length = 1.f, float knob_length = 0.f);

		float m_min;
		float m_max;
		float m_range;
		float m_step_length;
		float m_knob_length;

		float m_num_steps;

		float offset(float cursor) const;
		float cursor(float value, float cursor) const;

		SliderState compute(float value);
	};

	export_ MUD_UI_EXPORT bool slider(Widget& parent, Style& style, float& value, SliderMetrics metrics, Axis dim = Axis::X, bool relative = false, bool fill = true, Style* knob_style = nullptr);
	export_ MUD_UI_EXPORT bool slider(Widget& parent, float& value, SliderMetrics metrics, Axis dim = Axis::X, bool relative = false, bool fill = true, Style* knob_style = nullptr);
}
}
