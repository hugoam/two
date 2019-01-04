//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Colour.h>
#include <math/Vec.h>
#endif
#include <ui/Frame/Dim.h>

#ifndef MUD_CPP_20
#include <vector>
#include <string>
#endif

namespace mud
{
	using string = std::string;
	using cstring = const char*;

	export_ struct refl_ MUD_UI_EXPORT Layout
	{
	public:
		constr_ Layout() {}
		constr_ Layout(cstring name) : m_name(name) {}

		template <class T_Initializer>
		Layout(T_Initializer func) { func(*this); }

		attr_ string m_name = "";
		attr_ LayoutSolver m_solver = FRAME_SOLVER;
		attr_ Dim2<AutoLayout> m_layout = { AUTO_LAYOUT, AUTO_LAYOUT };
		attr_ Flow m_flow = FLOW;
		attr_ Space m_space = SHEET;
		attr_ Clipping m_clipping = NOCLIP;
		attr_ Opacity m_opacity = CLEAR;
		attr_ Dim2<Align> m_align = { Left, Left };
		attr_ vec2 m_span = vec2(1.f);
		attr_ vec2 m_size = vec2(0.f);
		attr_ vec4 m_padding = vec4(0.f);
		attr_ vec2 m_margin = vec2(0.f);
		attr_ vec2 m_spacing = vec2(0.f);
		attr_ Dim2<Pivot> m_pivot = { FORWARD, FORWARD };
		attr_ int m_zorder = 0;
		attr_ bool m_no_grid = false;

		attr_ std::vector<Space> m_grid_division;
		attr_ std::vector<float> m_table_division;

		attr_ size_t m_updated = 0;
	};
}
