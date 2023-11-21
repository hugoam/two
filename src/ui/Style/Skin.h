//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Frame/Dim.h>
#include <ui/Style/9Sprite.h>
#include <ui/Style/Paint.h>

namespace two
{
	using CustomDraw = void(*)(const Frame&, const vec4&, Vg&);

	export_ struct refl_ TWO_UI_EXPORT InkStyle
	{
	public:
		constr_ InkStyle() {}
		constr_ InkStyle(const string& name) : m_name(name) {}

		template <class T_Initializer>
		InkStyle(T_Initializer func) { func(*this); }

		void prepare()
		{
			if(!m_background_colour.null() || !m_text_colour.null() || !m_border_colour.null() || m_image || !m_image_skin.null() || m_custom_draw)
				m_empty = false;
		}

		attr_ string m_name = "";
		attr_ bool m_empty = true;
		attr_ Colour m_background_colour = Colour::None;
		attr_ Colour m_border_colour = Colour::None;
		attr_ Colour m_image_colour = Colour::None;
		attr_ Colour m_text_colour = Colour::None;
		attr_ string m_text_font = "dejavu";
		attr_ float m_text_size = 13.f;
		attr_ bool m_text_break = false;
		attr_ bool m_text_wrap = false;
		attr_ vec4 m_border_width = vec4(0.f);
		attr_ vec4 m_corner_radius = vec4(0.f);
		attr_ bool m_weak_corners = false;
		attr_ vec4 m_padding = vec4(0.f);
		attr_ vec4 m_margin = vec4(0.f);
		attr_ v2<Align> m_align = { Align::Left, Align::Left };
		attr_ vec2 m_linear_gradient = vec2(0.f);
		attr_ Axis m_linear_gradient_dim = Axis::Y;
		attr_ v2<bool> m_stretch = { false, false };
		attr_ Image* m_image = nullptr;
		attr_ Image* m_overlay = nullptr;
		attr_ Image* m_tile = nullptr;
		attr_ ImageSkin m_image_skin;
		attr_ Shadow m_shadow;
		attr_ Colour m_shadow_colour;
		attr_ Style* m_hover_cursor = nullptr;
		/*attr_*/ CustomDraw m_custom_draw = nullptr;
	};

	inline TextPaint text_paint(InkStyle& inkstyle)
	{
		return { inkstyle.m_text_font.c_str(), inkstyle.m_text_colour, inkstyle.m_text_size, inkstyle.m_align, inkstyle.m_text_break, inkstyle.m_text_wrap };
	}
}
