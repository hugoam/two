//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	Widget& Widget::layer()
	{
		if(this->find_state<Layer>())
			return *this;
		Layer& layer = this->state<Layer>();
		if(Widget* parent = this->parent())
			parent->layer_widget().add_sublayer(*this, layer);
		return *this;
	}

	// the node is going away: its layer leaves the layer it's drawn in, unless that one is gone already, its node released first
	void Widget::release_layer()
	{
		Layer* layer = this->find_state<Layer>();
		if(layer && !layer->master())
			if(m_graph->find_state<Layer>(layer->d_parent))
				m_graph->node(layer->d_parent).remove_sublayer(*this, *layer);
	}

	Widget& Widget::layer_widget()
	{
		return this->find_state<Layer>() ? *this : this->parent()->layer_widget();
	}

	Layer& Widget::draw_layer()
	{
		return *this->layer_widget().find_state<Layer>();
	}

	void Widget::reindex_layers()
	{
		Layer& layer = *this->find_state<Layer>();
		for(size_t i = 0; i < layer.d_sublayers.size(); ++i)
			m_graph->node(layer.d_sublayers[i]).find_state<Layer>()->d_index = i;
	}

	void Widget::reorder_layers()
	{
		auto z = [&](uint32_t node) -> size_t
		{
			Widget& widget = m_graph->node(node);
			const Layout& layout = *widget.frame().d_layout;
			return layout.m_zorder ? layout.m_zorder : widget.find_state<Layer>()->d_z;
		};

		auto lower = [&](uint32_t first, uint32_t second)
		{
			if(z(first) == z(second))
				return m_graph->node(first).find_state<Layer>()->d_index < m_graph->node(second).find_state<Layer>()->d_index;
			else
				return z(first) < z(second);
		};

		Layer& layer = *this->find_state<Layer>();
		std::sort(layer.d_sublayers.begin(), layer.d_sublayers.end(), lower);
		this->reindex_layers();
	}

	void Widget::add_sublayer(Widget& widget, Layer& sublayer)
	{
		Layer& layer = *this->find_state<Layer>();
		sublayer.d_parent = m_index;
		sublayer.d_index = layer.d_sublayers.size();
		layer.d_sublayers.push_back(widget.m_index);
		this->reorder_layers();
	}

	void Widget::remove_sublayer(Widget& widget, Layer& sublayer)
	{
		Layer& layer = *this->find_state<Layer>();
		remove(layer.d_sublayers, widget.m_index);
		sublayer.d_parent = Layer::none;
		this->reindex_layers();
		this->reorder_layers();
	}

	void Widget::move_layer_to_top()
	{
		Layer& layer = *this->find_state<Layer>();
		Widget& parent = m_graph->node(layer.d_parent);
		parent.remove_sublayer(*this, layer);
		parent.add_sublayer(*this, layer);
	}
}
