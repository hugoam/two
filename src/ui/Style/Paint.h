//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Frame/Dim.h>

namespace two
{
	using cstring = const char*;

	export_ struct refl_ TWO_UI_EXPORT Shadow
	{
	public:
		constr_ Shadow(float xpos, float ypos, float blur, float spread, Colour colour = Colour::AlphaBlack)
			: d_xpos(xpos), d_ypos(ypos), d_blur(blur), d_spread(spread), d_colour(colour), d_pos(xpos, ypos), d_null(false), d_radius(spread + blur)
		{}

		constr_ Shadow()
			: d_null(true)
		{}

		attr_ float d_xpos;
		attr_ float d_ypos;
		attr_ float d_blur;
		attr_ float d_spread;
		attr_ Colour d_colour;

		vec2 d_pos;
		bool d_null;
		float d_radius;
	};

	export_ struct refl_ TWO_UI_EXPORT Paint
	{
		Paint() {}
		Paint(Colour fill_colour) : m_fill_colour(fill_colour), m_stroke_colour(Colour::None), m_stroke_width(0.f) {}
		Paint(Colour stroke_colour, float stroke_width) : m_fill_colour(Colour::None), m_stroke_colour(stroke_colour), m_stroke_width(stroke_width) {}
		Paint(Colour fill_colour, Colour stroke_colour, float stroke_width) : m_fill_colour(fill_colour), m_stroke_colour(stroke_colour), m_stroke_width(stroke_width) {}
		attr_ Colour m_fill_colour;
		attr_ Colour m_stroke_colour;
		attr_ float m_stroke_width;
	};

	export_ struct refl_ TWO_UI_EXPORT TextPaint
	{
		attr_ cstring m_font;
		attr_ Colour m_colour;
		attr_ float m_size;
		attr_ v2<Align> m_align;
		attr_ bool m_text_break;
		attr_ bool m_text_wrap;
	};

	export_ struct refl_ TWO_UI_EXPORT Gradient
	{
		attr_ Colour m_start;
		attr_ Colour m_end;
	};
}
