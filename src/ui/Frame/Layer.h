//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Frame/Frame.h>

namespace two
{
	// the layer of a widget, a state of its node: the widget and its descendants are drawn in it, except the ones with their own layer
	// the layers are ordered under the layer they are drawn in, its sublayers, which are referred to by the index of their node
	export_ class refl_ TWO_UI_EXPORT Layer
	{
	public:
		static constexpr uint32_t none = UINT32_MAX;

		enum Redraw
		{
			NO_REDRAW = 0,
			REDRAW = 1,
			FORCE_REDRAW = 2
		};

		bool master() const { return d_parent == none; }
		bool redraw() const { return d_redraw >= REDRAW; }
		bool forceRedraw() const { return d_redraw >= FORCE_REDRAW; }

		void setRedraw() { if(d_redraw < REDRAW) d_redraw = REDRAW; }
		void setForceRedraw() { d_redraw = FORCE_REDRAW; }

		void endRedraw() { d_redraw = NO_REDRAW; }

	public:
		uint32_t d_parent = none;		// the node of the layer this layer is drawn in, none for the master layer
		size_t d_index = SIZE_MAX;
		size_t d_z = 0;

		Redraw d_redraw = REDRAW;
		size_t d_handle = SIZE_MAX;

		vector<uint32_t> d_sublayers;	// the nodes of the layers drawn in this layer, in their order
	};
}
