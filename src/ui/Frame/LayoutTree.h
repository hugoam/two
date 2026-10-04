//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Frame/Frame.h>
#include <ui/Style/Layout.h>

namespace two
{
	// the tracks a frame lays out its children on: the lines of a grid, the columns of a table
	export_ enum class LayoutTracks : uint8_t
	{
		None,
		Lines,		// the children of the grid are laid out by the line given by their index
		Columns		// the cells of the rows of the table are laid out by the column given by their index in the row
	};

	// a node of the layout tree: either a frame, or a virtual node inserted after its frame, the lines of a grid or the columns of a table
	// on each axis, a node is laid out by its container: its parent frame, a line of its parent grid, or a column of the table it's a cell of
	// the nodes are stored in depth-first order: the container of a node, on each axis, always comes before it
	export_ struct LayoutNode
	{
		Frame* frame = nullptr;
		uint32_t frame_parent = 0;			// the node of the parent frame, which the position of the frame is relative to
		v2<uint32_t> container = { 0, 0 };	// the node laying out this node, on each axis
		uint32_t virtuals = 0;				// the number of virtual nodes following this node: its tracks
		LayoutTracks tracks = LayoutTracks::None;
		uint32_t row_of = 0;				// the table this node is a row of, 0 if none
		Axis track = Axis::None;			// for the column of a table, the axis it's laid out in sequence along

		LayoutFlow flow = LayoutFlow::Flow;
		v2<AutoLayout> autolayout = { AutoLayout::Layout, AutoLayout::Layout };
		v2<Align> align = { Align::Left, Align::Left };
		vec4 padding = vec4(0.f);
		vec2 margin = vec2(0.f);
		vec2 spacing = vec2(0.f);

		Axis length = Axis::None;
		v2<Sizing> sizing = { Sizing::Shrink, Sizing::Shrink };

		vec2 content = vec2(0.f);
		vec2 size = vec2(0.f);
		vec2 position = vec2(0.f);
		vec2 span = vec2(1.f);
		v2<bool> positioned = { false, false };

		inline float pad(Axis dim) const { return padding[uint(dim)] + padding[uint(dim) + 2]; }
		inline float extent(Axis dim) const { return size[dim] + margin[dim] * 2.f; }
		inline float space(Axis dim) const { return size[dim] - pad(dim); }
	};

	// lays out a tree of frames in a few linear passes over flat arrays, per axis:
	// measure the content of each container bottom-up, then size and position each node top-down
	export_ class TWO_UI_EXPORT LayoutTree
	{
	public:
		// a tree of frames, from its root
		void build(Frame& root);

		// a tree built by hand: a root lending its size, then nodes laid out by their parent, each optionally laying out a frame
		uint32_t add_root(const Layout& layout, const vec2& size);
		uint32_t add(uint32_t parent, const Layout& layout, Frame* frame = nullptr);

		void solve();
		void apply();
		void clear_dirty();

		// the position of a node, relative to the root
		vec2 absolute(uint32_t index) const { return m_absolute[index]; }

		vector<LayoutNode> m_nodes;
		vector<v2<uint32_t>> m_first;	// the first of the nodes laid out by a node, on each axis, 0 if none
		vector<v2<uint32_t>> m_next;	// the next of the nodes laid out by the same container, on each axis, 0 if none
		vector<uint8_t> m_frozen;		// whether a growing node keeps its minimum, its share being less
		vector<Layer*> m_layers;		// the layer each frame is drawn in
		vector<vec2> m_absolute;

	private:
		LayoutNode node(const Layout& layout, Axis length, Axis parent_length) const;
		void read_frame(LayoutNode& node, Frame& frame) const;
		void add_frame(Frame& frame, uint32_t parent);
		void add_virtuals(uint32_t index);
		uint32_t container(uint32_t parent, Frame& frame, Axis dim) const;
		vec2 local_position(uint32_t index) const;

		void measure(Axis dim);
		void distribute(uint32_t container, Axis dim, float space);
		void sequence(uint32_t container, Axis dim, float space);
		void arrange(Axis dim);
		void accumulate();
	};
}
