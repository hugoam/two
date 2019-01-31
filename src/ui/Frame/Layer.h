//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <ui/Frame/Frame.h>

#ifndef MUD_CPP_20
#include <stdint.h>
#endif

namespace mud
{
	export_ class refl_ MUD_UI_EXPORT Layer
	{
	public:
		Layer(Frame& frame);
		~Layer();

		enum Redraw
		{
			NO_REDRAW = 0,
			REDRAW = 1,
			FORCE_REDRAW = 2
		};

		size_t z() const;

		bool master() { return d_parentLayer == nullptr; }
		bool redraw() const { return d_redraw >= REDRAW; }
		bool forceRedraw() const { return d_redraw >= FORCE_REDRAW; }

		void setRedraw() { if(d_redraw < REDRAW) d_redraw = REDRAW; }
		void setForceRedraw() { d_redraw = FORCE_REDRAW; }

		void endRedraw() { d_redraw = NO_REDRAW; }

		void addLayer(Layer& layer);
		void removeLayer(Layer& layer);

		void moveToTop();

		void reindex();
		void reorder();

		template <class T_Visitor>
		void visit(const T_Visitor& visitor)
		{
			visitor(*this);
			for(Layer* layer : d_sublayers)
				layer->visit(visitor);
		}

	public:
		Frame& m_frame;
		Layer* d_parentLayer = nullptr;
		size_t d_index = SIZE_MAX;
		size_t d_z = 0;

		Redraw d_redraw = REDRAW;
		size_t d_handle = SIZE_MAX;

		vector<Layer*> d_sublayers;
	};
}
