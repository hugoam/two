//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Colour.h>
#include <math/Vec.h>
#endif
#include <ui/Frame/Dim.h>
#include <ui/Style/9Sprite.h>
#include <ui/Style/Paint.h>

#ifndef MUD_CPP_20
#include <functional>
#include <string>
#endif

namespace mud
{
	using string = std::string;

	using CustomRenderer = std::function<void(const Frame&, const vec4&, Vg&)>;

	export_ struct refl_ MUD_UI_EXPORT InkStyle
	{
	public:
		constr_ InkStyle() {}
		constr_ InkStyle(cstring name) : m_name(name) {}

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
		attr_ float m_text_size = 14.f;
		attr_ bool m_text_break = false;
		attr_ bool m_text_wrap = false;
		attr_ vec4 m_border_width = vec4(0.f);
		attr_ vec4 m_corner_radius = vec4(0.f);
		attr_ bool m_weak_corners = false;
		attr_ vec4 m_padding = vec4(0.f);
		attr_ vec4 m_margin = vec4(0.f);
		attr_ Dim2<Align> m_align = { LEFT, LEFT };
		attr_ vec2 m_linear_gradient = vec2(0.f);
		attr_ Dim m_linear_gradient_dim = DIM_Y;
		attr_ Dim2<bool> m_stretch = { false, false };
		attr_ Image* m_image = nullptr;
		attr_ Image* m_overlay = nullptr;
		attr_ Image* m_tile = nullptr;
		attr_ ImageSkin m_image_skin;
		attr_ Shadow m_shadow;
		attr_ Colour m_shadow_colour;
		attr_ Style* m_hover_cursor = nullptr;
		/*attr_*/ CustomRenderer m_custom_draw;

		WidgetState m_state;
	};
}
