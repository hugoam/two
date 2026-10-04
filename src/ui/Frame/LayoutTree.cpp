//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	Space Space::preset(Preset preset)
	{
		if     (preset == Preset::Sheet)  return { FlowAxis::Paragraph,	Sizing::Wrap,   Sizing::Wrap };
		else if(preset == Preset::Flex)	  return { FlowAxis::Same,	    Sizing::Wrap,   Sizing::Wrap };
		else if(preset == Preset::Item)   return { FlowAxis::Reading,   Sizing::Shrink, Sizing::Shrink };
		else if(preset == Preset::Unit)   return { FlowAxis::Paragraph, Sizing::Shrink, Sizing::Shrink };
		else if(preset == Preset::Block)  return { FlowAxis::Paragraph, Sizing::Fixed,  Sizing::Fixed };
		else if(preset == Preset::Line)   return { FlowAxis::Reading,   Sizing::Wrap,   Sizing::Shrink };
		else if(preset == Preset::Stack)  return { FlowAxis::Paragraph, Sizing::Shrink, Sizing::Wrap };
		else if(preset == Preset::Div)    return { FlowAxis::Flip,      Sizing::Wrap,   Sizing::Shrink };
		else if(preset == Preset::Spacer) return { FlowAxis::Same,      Sizing::Wrap,   Sizing::Shrink };
		else if(preset == Preset::Board)  return { FlowAxis::Reading,   Sizing::Expand, Sizing::Expand };
		else if(preset == Preset::Layout) return { FlowAxis::Paragraph, Sizing::Expand, Sizing::Expand };
		else 							  return { FlowAxis::Paragraph, Sizing::Wrap,   Sizing::Wrap };
	}

	table<Align, float> c_align_space = { { 0.f, 0.5f, 1.f, 0.f, 1.f } };
	table<Align, float> c_align_extent = { { 0.f, 0.5f, 1.f, 1.f, 0.f } };

	static Axis flow_axis(FlowAxis direction, Axis explicit_length, Axis parent_length)
	{
		if(explicit_length != Axis::None) return explicit_length;
		else if(direction == FlowAxis::Flip) return flip(parent_length);
		else if(direction == FlowAxis::Same) return parent_length;
		else if(direction == FlowAxis::Reading) return Axis::X;
		else if(direction == FlowAxis::Paragraph) return Axis::Y;
		else return Axis::None;
	}

	static void set_sizing(LayoutNode& node, const Space& space)
	{
		if(node.length == Axis::None)
		{
			node.sizing = { space.sizingDepth, space.sizingDepth };
			return;
		}
		node.sizing[node.length] = space.sizingLength;
		node.sizing[flip(node.length)] = space.sizingDepth;
	}

	LayoutNode LayoutTree::node(const Layout& layout, Axis length, Axis parent_length) const
	{
		LayoutNode node;
		node.solver = layout.m_solver;
		node.flow = layout.m_flow;
		node.autolayout = layout.m_layout;
		node.align = layout.m_align;
		node.padding = layout.m_padding;
		node.margin = layout.m_margin;
		node.spacing = layout.m_spacing;
		node.no_grid = layout.m_no_grid;
		node.length = flow_axis(layout.m_space.direction, length, parent_length);
		set_sizing(node, layout.m_space);
		return node;
	}

	// a fixed node has the size of its own content, or keeps its size if it has none
	void LayoutTree::read_frame(LayoutNode& node, Frame& frame) const
	{
		node.frame = &frame;
		node.position = frame.m_position;
		node.span = frame.m_span;

		const vec2 pad = { node.pad(Axis::X), node.pad(Axis::Y) };
		const vec2 own = frame.empty() ? frame.m_size - pad : frame.m_content + rect_sum(frame.d_inkstyle->m_padding);
		for(Axis dim : { Axis::X, Axis::Y })
		{
			node.content[dim] = node.sizing[dim] == Sizing::Fixed ? own[dim] : 0.f;
			node.size[dim] = node.sizing[dim] == Sizing::Fixed ? own[dim] + pad[dim] : frame.m_size[dim];
		}
	}

	void LayoutTree::build(Frame& root)
	{
		m_nodes.clear();
		this->add_frame(root, 0);

		// the root is laid out by whoever owns it: it only lends its size to its children
		LayoutNode& node = m_nodes[0];
		node.content = vec2(0.f);
		node.size = root.m_size;
	}

	uint32_t LayoutTree::add_root(const Layout& layout, const vec2& size)
	{
		m_nodes.clear();
		LayoutNode root = this->node(layout, Axis::None, Axis::Y);
		root.size = size;
		m_nodes.push_back(root);
		return 0;
	}

	uint32_t LayoutTree::add(uint32_t parent, const Layout& layout, Frame* frame)
	{
		const uint32_t index = uint32_t(m_nodes.size());
		LayoutNode node = this->node(layout, Axis::None, m_nodes[parent].length);
		node.frame_parent = parent;
		node.container = { parent, parent };
		if(frame)
			this->read_frame(node, *frame);
		m_nodes.push_back(node);
		return index;
	}

	// a child is laid out by its parent frame, except:
	// - the children of a grid are laid out by the line of the grid they are on
	// - the children of the rows of a table are laid out by their column along the row
	uint32_t LayoutTree::container(uint32_t parent, Frame& frame, Axis dim) const
	{
		const LayoutNode& p = m_nodes[parent];
		if(p.solver == Solver::Grid && p.length != Axis::None)
		{
			const uint line = frame.d_index[p.length];
			return line < p.virtuals ? parent + 1 + line : parent;
		}

		const uint32_t grand = p.frame_parent;
		const LayoutNode& g = m_nodes[grand];
		if(parent > 0 && dim == p.length && g.solver == Solver::Table && !p.no_grid)
		{
			const uint column = frame.d_widget.m_sibling;
			return column + 1 < g.virtuals ? grand + 2 + column : grand;
		}

		return parent;
	}

	void LayoutTree::add_frame(Frame& frame, uint32_t parent)
	{
		if(!frame.d_layout)
			return;

		const uint32_t index = uint32_t(m_nodes.size());
		const bool root = index == 0;

		LayoutNode node = this->node(*frame.d_layout, frame.d_length_override, root ? Axis::Y : m_nodes[parent].length);
		node.frame_parent = parent;
		node.container = root ? v2<uint32_t>(0, 0) : v2<uint32_t>(this->container(parent, frame, Axis::X), this->container(parent, frame, Axis::Y));
		this->read_frame(node, frame);

		m_nodes.push_back(node);
		this->add_virtuals(index);

		for(Widget& child : frame.d_widget.children())
			this->add_frame(child.m_frame, index);
	}

	void LayoutTree::add_virtuals(uint32_t index)
	{
		Frame& frame = *m_nodes[index].frame;
		Layout& layout = *frame.d_layout;

		auto add = [&](uint32_t container, Axis length) -> LayoutNode&
		{
			LayoutNode node;
			node.frame_parent = index;
			node.container = { container, container };
			node.length = length;
			m_nodes.push_back(node);
			return m_nodes.back();
		};

		const uint32_t first = uint32_t(m_nodes.size());

		if(layout.m_solver == Solver::Grid)
		{
			// a line of a grid spans the grid along the reading direction
			for(const Space& space : layout.m_grid_division)
			{
				LayoutNode& line = add(index, Axis::X);
				set_sizing(line, space);
			}
		}
		else if(layout.m_solver == Solver::Table)
		{
			// the columns of a table are laid out in sequence in an overlay spanning the table
			LayoutNode& overlay = add(index, Axis::X);
			overlay.flow = LayoutFlow::Overlay;
			overlay.sizing = { Sizing::Wrap, Sizing::Wrap };
			overlay.spacing = vec2(2.f);

			const uint32_t overlay_index = first;
			Widget& widget = frame.d_widget;
			span<float> weights = widget.is_type<Table>(widget) ? span<float>(static_cast<Table&>(widget).m_weights) : span<float>(layout.m_table_division);
			for(float weight : weights)
			{
				LayoutNode& column = add(overlay_index, Axis::Y);
				column.sizing = { Sizing::Wrap, Sizing::Wrap };
				column.autolayout = { AutoLayout::Layout, AutoLayout::None };
				column.span = { weight, 0.f };
			}
		}

		m_nodes[index].virtuals = uint32_t(m_nodes.size()) - first;
	}

	void LayoutTree::solve()
	{
		m_first.assign(m_nodes.size(), v2<uint32_t>(0, 0));
		m_next.assign(m_nodes.size(), v2<uint32_t>(0, 0));
		m_frozen.assign(m_nodes.size(), false);

		this->measure(Axis::X);
		this->arrange(Axis::X);
		this->measure(Axis::Y);
		this->arrange(Axis::Y);
		this->accumulate();
	}

	// along the flow, a node takes at least its minimum, and the nodes that grow share the space left by their span:
	// a fixed node takes its size, a shrinking node its content, a wrapping node its content or more, an expanding node any size
	static float minimum(const LayoutNode& n, Axis dim)
	{
		if(n.sizing[dim] == Sizing::Fixed)
			return n.size[dim];
		else if(n.sizing[dim] == Sizing::Expand)
			return 0.f;
		else
			return n.content[dim] + n.pad(dim);
	}

	static bool grows(const LayoutNode& n, Axis dim)
	{
		return n.sizing[dim] >= Sizing::Wrap;
	}

	// across the flow, or out of it, a node is sized in the space of its container alone
	static float fit(const LayoutNode& n, Axis dim, float space)
	{
		if(n.sizing[dim] == Sizing::Shrink)
			return n.content[dim] + n.pad(dim);
		else if(n.sizing[dim] == Sizing::Wrap)
			return max(n.content[dim] + n.pad(dim), space);
		else if(n.sizing[dim] == Sizing::Expand)
			return space;
		else
			return n.size[dim];
	}

	// bottom-up: the children of a node all come after it, so when it's reached they are measured, and it can measure its content
	// along the flow, the content is the minimums of the flowing children in sequence, across it the largest of them
	void LayoutTree::measure(Axis dim)
	{
		for(uint32_t i = uint32_t(m_nodes.size()); i-- > 0;)
		{
			LayoutNode& p = m_nodes[i];
			if(p.solver != Solver::Frame && p.sizing[dim] != Sizing::Fixed)
			{
				const bool along = dim == p.length;
				float sequence = 0.f;
				float largest = 0.f;
				uint32_t count = 0;
				for(uint32_t c = m_first[i][dim]; c; c = m_next[c][dim])
				{
					const LayoutNode& n = m_nodes[c];
					const float bounds = minimum(n, dim) + n.margin[dim] * 2.f;
					if(n.flow > LayoutFlow::Overlay)
						continue;
					else if(along && n.flow == LayoutFlow::Flow)
						sequence += bounds, ++count;
					else if(n.sizing[dim] != Sizing::Expand)
						largest = max(largest, bounds);
				}
				const float spacings = count > 1 ? float(count - 1) * p.spacing[dim] : 0.f;
				p.content[dim] = max(sequence + spacings, largest);
			}

			// linked in front of the children of its container, which end up in order
			if(i > 0)
			{
				const uint32_t container = p.container[dim];
				m_next[i][dim] = m_first[container][dim];
				m_first[container][dim] = i;
			}
		}
	}

	// the flowing children take their minimum, and their margins and the spacing between them,
	// then the children that grow share the space left by their span: a wrapping child whose share is less than its content keeps its content,
	// and the others share what remains, until every share holds: when the space is short, the wrapping children give way to each other
	void LayoutTree::distribute(uint32_t container, Axis dim, float space)
	{
		const LayoutNode& p = m_nodes[container];

		float left = space;
		float spans = 0.f;
		uint32_t count = 0;
		for(uint32_t c = m_first[container][dim]; c; c = m_next[c][dim])
		{
			LayoutNode& n = m_nodes[c];
			if(n.flow != LayoutFlow::Flow)
				continue;

			++count;
			left -= n.margin[dim] * 2.f;
			if(grows(n, dim))
			{
				spans += n.span[dim];
				m_frozen[c] = false;
			}
			else
			{
				n.size[dim] = minimum(n, dim);
				left -= n.size[dim];
			}
		}
		left -= count > 1 ? float(count - 1) * p.spacing[dim] : 0.f;

		bool freezing = true;
		while(freezing && spans > 0.f)
		{
			freezing = false;
			for(uint32_t c = m_first[container][dim]; c; c = m_next[c][dim])
			{
				LayoutNode& n = m_nodes[c];
				if(n.flow != LayoutFlow::Flow || !grows(n, dim) || m_frozen[c])
					continue;

				const float least = minimum(n, dim);
				if(left * n.span[dim] / spans < least)
				{
					n.size[dim] = least;
					m_frozen[c] = true;
					left -= least;
					spans -= n.span[dim];
					freezing = true;
				}
			}
		}

		for(uint32_t c = m_first[container][dim]; c; c = m_next[c][dim])
		{
			LayoutNode& n = m_nodes[c];
			if(n.flow == LayoutFlow::Flow && grows(n, dim) && !m_frozen[c])
				n.size[dim] = spans > 0.f ? left * n.span[dim] / spans : 0.f;
		}
	}

	// the flowing children are placed one after the other: the space left after them shifts each one by the fraction of its alignment
	void LayoutTree::sequence(uint32_t container, Axis dim, float space)
	{
		const LayoutNode& p = m_nodes[container];

		float used = 0.f;
		uint32_t count = 0;
		for(uint32_t c = m_first[container][dim]; c; c = m_next[c][dim])
		{
			const LayoutNode& n = m_nodes[c];
			if(n.flow == LayoutFlow::Flow)
				used += n.extent(dim), ++count;
		}
		used += count > 1 ? float(count - 1) * p.spacing[dim] : 0.f;
		const float leftover = max(0.f, space - used);

		float cursor = p.padding[uint(dim)];
		for(uint32_t c = m_first[container][dim]; c; c = m_next[c][dim])
		{
			LayoutNode& n = m_nodes[c];
			if(n.flow != LayoutFlow::Flow)
				continue;
			n.position[dim] = cursor + n.margin[dim] + leftover * c_align_space[n.align[dim]];
			n.positioned[dim] = true;
			cursor += n.extent(dim) + p.spacing[dim];
		}
	}

	// top-down: a container is sized and positioned before its children, which it then sizes and positions all together
	void LayoutTree::arrange(Axis dim)
	{
		for(LayoutNode& n : m_nodes)
			n.positioned[dim] = false;

		for(uint32_t i = 0; i < uint32_t(m_nodes.size()); ++i)
		{
			const LayoutNode& p = m_nodes[i];
			if(p.solver == Solver::Frame || !m_first[i][dim])
				continue;

			const bool along = dim == p.length;
			const float space = p.space(dim);

			// the spans of the growing children are normalized, so that they read as fractions of the space they share
			if(along)
			{
				float spans = 0.f;
				for(uint32_t c = m_first[i][dim]; c; c = m_next[c][dim])
					if(m_nodes[c].flow == LayoutFlow::Flow && grows(m_nodes[c], dim))
						spans += m_nodes[c].span[dim];
				for(uint32_t c = m_first[i][dim]; c; c = m_next[c][dim])
					if(m_nodes[c].flow == LayoutFlow::Flow && grows(m_nodes[c], dim) && spans > 0.f)
						m_nodes[c].span[dim] /= spans;
			}

			if(p.autolayout[dim] >= AutoLayout::Size)
			{
				if(along)
					this->distribute(i, dim, space);
				for(uint32_t c = m_first[i][dim]; c; c = m_next[c][dim])
				{
					LayoutNode& n = m_nodes[c];
					if(!(along && n.flow == LayoutFlow::Flow))
						n.size[dim] = fit(n, dim, space - n.margin[dim] * 2.f);
				}
			}

			if(p.autolayout[dim] >= AutoLayout::Layout)
			{
				if(along)
					this->sequence(i, dim, space);
				for(uint32_t c = m_first[i][dim]; c; c = m_next[c][dim])
				{
					LayoutNode& n = m_nodes[c];
					if(n.flow > LayoutFlow::Align || (along && n.flow == LayoutFlow::Flow))
						continue;
					const bool flow = n.flow == LayoutFlow::Flow;
					const Align align = n.align[dim];
					const float offset = space * c_align_space[align] - n.extent(dim) * c_align_extent[align];
					n.position[dim] = (flow ? p.padding[uint(dim)] + n.margin[dim] : 0.f) + offset;
					n.positioned[dim] = true;
				}
			}
		}
	}

	// a node positioned by its container is relative to it, otherwise it's relative to its parent frame
	void LayoutTree::accumulate()
	{
		m_absolute.resize(m_nodes.size());
		m_absolute[0] = vec2(0.f);
		for(uint32_t i = 1; i < uint32_t(m_nodes.size()); ++i)
		{
			const LayoutNode& n = m_nodes[i];
			for(Axis dim : { Axis::X, Axis::Y })
			{
				const uint32_t base = n.positioned[dim] ? n.container[dim] : n.frame_parent;
				m_absolute[i][dim] = m_absolute[base][dim] + n.position[dim];
			}
		}
	}

	vec2 LayoutTree::local_position(uint32_t index) const
	{
		return m_absolute[index] - m_absolute[m_nodes[index].frame_parent];
	}

	void LayoutTree::apply()
	{
		m_nodes[0].frame->d_length = m_nodes[0].length;
		for(uint32_t i = 1; i < uint32_t(m_nodes.size()); ++i)
		{
			const LayoutNode& n = m_nodes[i];
			if(!n.frame) continue;
			n.frame->d_length = n.length;
			n.frame->set_position(this->local_position(i));
			n.frame->set_size(n.size);
			n.frame->m_span = n.span;
		}
	}

	void LayoutTree::clear_dirty()
	{
		for(uint32_t i = 1; i < uint32_t(m_nodes.size()); ++i)
		{
			Frame* frame = m_nodes[i].frame;
			if(!frame) continue;
			frame->layer().setRedraw();
			frame->layer().setForceRedraw(); // @ kludge for nodes in canvas when moving the canvas window
			frame->clearDirty();
		}
	}
}
