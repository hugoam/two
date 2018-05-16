//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Colour.h>
#include <math/Vec.h>
#include <ui/Frame/Dim.h>

/* std */
#include <vector>
#include <string>

namespace mud
{
	using string = std::string;

	struct _refl_ MUD_UI_EXPORT Layout
	{
	public:
		_constr_ Layout(const string& name = "")
			: m_name(name), m_solver(FRAME_SOLVER), m_layout(AUTO_LAYOUT, AUTO_LAYOUT), m_flow(FLOW), m_space(SHEET)
			, m_clipping(NOCLIP), m_opacity(CLEAR), m_align(LEFT, LEFT)
			, m_span(1.f), m_size(0.f), m_padding(0.f), m_margin(0.f), m_spacing(0.f)
			, m_pivot(FORWARD, FORWARD), m_zorder(0), m_updated(0)
		{}

		Layout(cstring name, const Args& args);

		_attr_ _mut_ string m_name;
		_attr_ _mut_ LayoutSolver m_solver;
		_attr_ _mut_ Dim2<AutoLayout> m_layout;
		_attr_ _mut_ Flow m_flow;
		_attr_ _mut_ Space m_space;
		_attr_ _mut_ Clipping m_clipping;
		_attr_ _mut_ Opacity m_opacity;
		_attr_ _mut_ Dim2<Align> m_align;
		_attr_ _mut_ vec2 m_span;
		_attr_ _mut_ vec2 m_size;
		_attr_ _mut_ vec4 m_padding;
		_attr_ _mut_ vec2 m_margin;
		_attr_ _mut_ vec2 m_spacing;
		_attr_ _mut_ Dim2<Pivot> m_pivot;
		_attr_ _mut_ int m_zorder;

		_attr_ _mut_ std::vector<Space> m_grid_division;
		_attr_ _mut_ std::vector<float> m_table_division;

		_attr_ _mut_ size_t m_updated;
	};
}
