//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
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
		return m_frame.d_layout->m_zorder ? m_frame.d_layout->m_zorder : d_z;
	}

	void Layer::reindex()
	{
		for(size_t i = 0; i < d_sublayers.size(); ++i)
			d_sublayers[i]->d_index = i;
	}

	void Layer::reorder()
	{
		auto lower = [](Layer* first, Layer* second)
		{
			if(first->z() == second->z())
				return first->d_index < second->d_index;
			else
				return first->z() < second->z();
		};

		std::sort(d_sublayers.begin(), d_sublayers.end(), lower);
		//quicksort<Layer*>(d_sublayers, lower);
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
		remove(d_sublayers, &layer);
		this->reindex();
		this->reorder();
	}

	void Layer::moveToTop()
	{
		d_parentLayer->removeLayer(*this);
		d_parentLayer->addLayer(*this);
	}
}
