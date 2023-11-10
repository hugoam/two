//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <math/Colour.h>
#include <math/Vec.h>
#endif
#include <ui/Frame/Dim.h>

namespace two
{
	export_ struct refl_ TWO_UI_EXPORT Layout
	{
	public:
		constr_ Layout() {}
		constr_ Layout(const string& name) : m_name(name) {}

		template <class T_Initializer>
		Layout(T_Initializer func) { func(*this); }

		attr_ string m_name = "";
		attr_ Solver m_solver = Solver::Frame;
		attr_ v2<AutoLayout> m_layout = { AutoLayout::Layout, AutoLayout::Layout };
		attr_ LayoutFlow m_flow = LayoutFlow::Flow;
		attr_ Space m_space = Preset::Sheet;
		attr_ Clip m_clipping = Clip::None;
		attr_ Opacity m_opacity = Opacity::Clear;
		attr_ v2<Align> m_align = { Align::Left, Align::Left };
		attr_ vec2 m_span = vec2(1.f);
		attr_ vec2 m_size = vec2(0.f);
		attr_ vec4 m_padding = vec4(0.f);
		attr_ vec2 m_margin = vec2(0.f);
		attr_ vec2 m_spacing = vec2(0.f);
		attr_ v2<Pivot> m_pivot = { Pivot::Forward, Pivot::Forward };
		attr_ int m_zorder = 0;
		attr_ bool m_no_grid = false;

		attr_ vector<Space> m_grid_division;
		attr_ vector<float> m_table_division;

		attr_ size_t m_updated = 0;
	};
}
