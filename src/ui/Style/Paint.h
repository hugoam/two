//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Colour.h>
#include <math/Vec.h>
#include <ui/Generated/Forward.h>
#include <ui/Frame/Dim.h>

namespace mud
{
	struct _refl_ MUD_UI_EXPORT Shadow
	{
	public:
		_constr_ Shadow(float xpos, float ypos, float blur, float spread, Colour colour = Colour::AlphaBlack)
			: d_xpos(xpos), d_ypos(ypos), d_blur(blur), d_spread(spread), d_colour(colour), d_pos(xpos, ypos), d_null(false), d_radius(spread + blur)
		{}

		_constr_ Shadow()
			: d_null(true)
		{}

		_attr_ _mut_ float d_xpos;
		_attr_ _mut_ float d_ypos;
		_attr_ _mut_ float d_blur;
		_attr_ _mut_ float d_spread;
		_attr_ _mut_ Colour d_colour;

		vec2 d_pos;
		bool d_null;
		float d_radius;
	};

	struct _refl_ MUD_UI_EXPORT Paint
	{
		Paint(Colour fill_colour) : m_fill_colour(fill_colour), m_stroke_colour(Colour::None), m_stroke_width(0.f) {}
		Paint(Colour stroke_colour, float stroke_width) : m_fill_colour(Colour::None), m_stroke_colour(stroke_colour), m_stroke_width(stroke_width) {}
		Paint(Colour fill_colour, Colour stroke_colour, float stroke_width) : m_fill_colour(fill_colour), m_stroke_colour(stroke_colour), m_stroke_width(stroke_width) {}
		_attr_ _mut_ Colour m_fill_colour;
		_attr_ _mut_ Colour m_stroke_colour;
		_attr_ _mut_ float m_stroke_width;
	};

	struct _refl_ MUD_UI_EXPORT TextPaint
	{
		_attr_ _mut_ cstring m_font;
		_attr_ _mut_ Colour m_colour;
		_attr_ _mut_ float m_size;
		_attr_ _mut_ Dim2<Align> m_align;
		_attr_ _mut_ bool m_text_break;
		_attr_ _mut_ bool m_text_wrap;
	};

	struct _refl_ MUD_UI_EXPORT Gradient
	{
		_attr_ _mut_ Colour m_start;
		_attr_ _mut_ Colour m_end;
	};
}
