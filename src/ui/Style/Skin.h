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

	using CustomRenderer = std::function<void(const Frame&, const vec4&, VgRenderer&)>;

	export_ struct _refl_ MUD_UI_EXPORT InkStyle
	{
	public:
		_constr_ InkStyle() {}
		_constr_ InkStyle(cstring name) : m_name(name) {}

		template <class T_Initializer>
		InkStyle(T_Initializer func) { func(*this); }

		void prepare()
		{
			if(!m_background_colour.null() || !m_text_colour.null() || !m_border_colour.null() || m_image || !m_image_skin.null() || m_custom_draw)
				m_empty = false;
		}

		_attr_ _mut_ string m_name = "";
		_attr_ _mut_ bool m_empty = true;
		_attr_ _mut_ Colour m_background_colour = Colour::None;
		_attr_ _mut_ Colour m_border_colour = Colour::None;
		_attr_ _mut_ Colour m_image_colour = Colour::None;
		_attr_ _mut_ Colour m_text_colour = Colour::None;
		_attr_ _mut_ string m_text_font = "dejavu";
		_attr_ _mut_ float m_text_size = 14.f;
		_attr_ _mut_ bool m_text_break = false;
		_attr_ _mut_ bool m_text_wrap = false;
		_attr_ _mut_ vec4 m_border_width = vec4(0.f);
		_attr_ _mut_ vec4 m_corner_radius = vec4(0.f);
		_attr_ _mut_ bool m_weak_corners = false;
		_attr_ _mut_ vec4 m_padding = vec4(0.f);
		_attr_ _mut_ vec4 m_margin = vec4(0.f);
		_attr_ _mut_ Dim2<Align> m_align = { LEFT, LEFT };
		_attr_ _mut_ vec2 m_linear_gradient = vec2(0.f);
		_attr_ _mut_ Dim m_linear_gradient_dim = DIM_Y;
		_attr_ _mut_ Image* m_image = nullptr;
		_attr_ _mut_ Image* m_overlay = nullptr;
		_attr_ _mut_ Image* m_tile = nullptr;
		_attr_ _mut_ ImageSkin m_image_skin;
		_attr_ _mut_ Shadow m_shadow;
		_attr_ _mut_ Colour m_shadow_colour;
		_attr_ _mut_ Style* m_hover_cursor = nullptr;
		/*_attr_*/ CustomRenderer m_custom_draw;

		WidgetState m_state;
	};
}
