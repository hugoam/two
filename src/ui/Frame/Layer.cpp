//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <infra/Vector.h>
#include <infra/Reverse.h>
#include <ui/Frame/Layer.h>
#include <ui/Sheet.h>
#include <ui/Style/Layout.h>
#endif

#include <algorithm>

namespace mud
{
	Layer::Layer(Frame& frame)
		: m_frame(frame)
		, d_parentLayer(frame.d_parent ? &frame.d_parent->layer() : nullptr)
	{
		if(d_parentLayer)
			d_parentLayer->addLayer(*this);
	}

	Layer::~Layer()
	{
		if(d_parentLayer)
			d_parentLayer->removeLayer(*this);
	}

	size_t Layer::z() const
	{
		return m_frame.d_style->layout().m_zorder ? m_frame.d_style->layout().m_zorder : d_z;
	}

	void Layer::reindex()
	{
		for(size_t i = 0; i < d_sublayers.size(); ++i)
			d_sublayers[i]->d_index = i;
	}

	void Layer::reorder()
	{
		std::sort(d_sublayers.begin(), d_sublayers.end(), [](Layer* first, Layer* second) { if(first->z() < second->z()) return true; else if(first->z() > second->z()) return false; return first->d_index < second->d_index; });
		this->reindex();
	}
	
	void Layer::addLayer(Layer& layer)
	{
		layer.d_index = d_sublayers.size();
		d_sublayers.push_back(&layer);
		this->reorder();
	}

	void Layer::removeLayer(Layer& layer)
	{
		vector_remove(d_sublayers, &layer);
		this->reindex();
		this->reorder();
	}

	void Layer::moveToTop()
	{
		d_parentLayer->removeLayer(*this);
		d_parentLayer->addLayer(*this);
	}
}
