//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <ui/Button.h>

namespace mud
{
namespace ui
{
	struct MUD_UI_EXPORT SliderState
	{
		float m_pre_span;
		float m_knob_span;
		float m_post_span;
	};

	struct MUD_UI_EXPORT SliderMetrics
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

	MUD_UI_EXPORT bool slider(Widget& parent, Style& style, float& value, SliderMetrics metrics, Dim dim = DIM_X, bool relative = false, bool fill = true, Style* knob_style = nullptr);
	MUD_UI_EXPORT bool slider(Widget& parent, float& value, SliderMetrics metrics, Dim dim = DIM_X, bool relative = false, bool fill = true, Style* knob_style = nullptr);
}
}
