//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Colour.h>
#include <math/Vec.h>
#include <ui/Frame/Dim.h>

#ifndef MUD_CPP_20
#include <vector>
#include <string>
#endif

namespace mud
{
	using string = std::string;
	using cstring = const char*;

	export_ struct _refl_ MUD_UI_EXPORT Layout
	{
	public:
		_constr_ Layout() {}
		_constr_ Layout(cstring name) : m_name(name) {}

		template <class T_Initializer>
		Layout(T_Initializer func) { func(*this); }

		_attr_ _mut_ string m_name = "";
		_attr_ _mut_ LayoutSolver m_solver = FRAME_SOLVER;
		_attr_ _mut_ Dim2<AutoLayout> m_layout = { AUTO_LAYOUT, AUTO_LAYOUT };
		_attr_ _mut_ Flow m_flow = FLOW;
		_attr_ _mut_ Space m_space = SHEET;
		_attr_ _mut_ Clipping m_clipping = NOCLIP;
		_attr_ _mut_ Opacity m_opacity = CLEAR;
		_attr_ _mut_ Dim2<Align> m_align = { LEFT, LEFT };
		_attr_ _mut_ vec2 m_span = vec2(1.f);
		_attr_ _mut_ vec2 m_size = vec2(0.f);
		_attr_ _mut_ vec4 m_padding = vec4(0.f);
		_attr_ _mut_ vec2 m_margin = vec2(0.f);
		_attr_ _mut_ vec2 m_spacing = vec2(0.f);
		_attr_ _mut_ Dim2<Pivot> m_pivot = { FORWARD, FORWARD };
		_attr_ _mut_ int m_zorder = 0;

		_attr_ _mut_ std::vector<Space> m_grid_division;
		_attr_ _mut_ std::vector<float> m_table_division;

		_attr_ _mut_ size_t m_updated = 0;
	};
}
