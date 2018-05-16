//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Colour.h>
#include <math/Vec.h>
#include <ui/Frame/Dim.h>
#include <ui/Style/9Sprite.h>
#include <ui/Style/Paint.h>

#include <functional>
#include <string>

namespace mud
{
	using string = std::string;

	using CustomRenderer = std::function<void(const Frame&, VgRenderer&)>;

	struct _refl_ MUD_UI_EXPORT InkStyle
	{
	public:
		_constr_ InkStyle(const string& name = "")
			: m_name(name), m_empty(true), m_background_colour(Colour::None), m_border_colour(Colour::None), m_image_colour(Colour::None), m_text_colour(Colour::None)
			, m_text_font("dejavu"), m_text_size(14.f), m_text_break(true), m_text_wrap(false)
			, m_border_width(0.f), m_corner_radius(), m_weak_corners(false), m_padding(0.f), m_margin(0.f)
			, m_align(LEFT, LEFT), m_linear_gradient(0.f), m_linear_gradient_dim(DIM_Y)
			, m_image(nullptr), m_overlay(nullptr), m_tile(nullptr), m_hover_cursor(nullptr)
		{}

		void prepare()
		{
			if(!m_background_colour.null() || !m_text_colour.null() || !m_border_colour.null() || m_image || !m_image_skin.null() || m_custom_draw)
				m_empty = false;
		}

		_attr_ _mut_ string m_name;
		_attr_ _mut_ bool m_empty;
		_attr_ _mut_ Colour m_background_colour;
		_attr_ _mut_ Colour m_border_colour;
		_attr_ _mut_ Colour m_image_colour;
		_attr_ _mut_ Colour m_text_colour;
		_attr_ _mut_ string m_text_font;
		_attr_ _mut_ float m_text_size;
		_attr_ _mut_ bool m_text_break;
		_attr_ _mut_ bool m_text_wrap;
		_attr_ _mut_ vec4 m_border_width;
		_attr_ _mut_ vec4 m_corner_radius;
		_attr_ _mut_ bool m_weak_corners;
		_attr_ _mut_ vec4 m_padding;
		_attr_ _mut_ vec4 m_margin;
		_attr_ _mut_ Dim2<Align> m_align;
		_attr_ _mut_ vec2 m_linear_gradient;
		_attr_ _mut_ Dim m_linear_gradient_dim;
		_attr_ _mut_ Image* m_image;
		_attr_ _mut_ Image* m_overlay;
		_attr_ _mut_ Image* m_tile;
		_attr_ _mut_ ImageSkin m_image_skin;
		_attr_ _mut_ Shadow m_shadow;
		_attr_ _mut_ Colour m_shadow_colour;
		_attr_ _mut_ Style* m_hover_cursor;
		/*_attr_*/ CustomRenderer m_custom_draw;

		WidgetState m_state;
	};
}
