//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.ui;
#else
#include <infra/Reverse.h>
#include <math/Vec.hpp>
#include <ui/Frame/Solver.h>
#include <ui/Style/Style.h>
#include <ui/WidgetStruct.h>
#include <ui/Frame/Caption.h>
#include <ui/Frame/Layer.h>
#endif

#include <cstdio>

#define DEBUG_BOUNDS 0
#define DEBUG_LAYOUT 0

namespace two
{
	void collect_solvers(Frame& frame, SolverVector& solvers, DirtyLayout dirtyTop)
	{
		if(dirtyTop >= DIRTY_FORCE_LAYOUT)
			frame.set_dirty(DIRTY_FORCE_LAYOUT);
		else if(dirtyTop >= DIRTY_LAYOUT)
			//frame.set_dirty(DIRTY_PARENT);
			frame.set_dirty(DIRTY_LAYOUT); // @kludge because relayout with DIRTY_PARENT isn't always correct due to size / content issue

		if(!frame.d_dirty)
			return;

		//this->debugPrintDepth();
		//printf(" >> %s %s\n", d_style->m_name.c_str(), to_string(d_dirty).c_str());

		if(frame.d_dirty >= DIRTY_PARENT)
		{
			frame.m_solver->collect(solvers);
		}

		if(frame.d_dirty >= DIRTY_REDRAW)
		{
			frame.layer().setRedraw();
			frame.layer().setForceRedraw(); // @ kludge for nodes in canvas when moving the canvas window
		}

		for(auto& widget : frame.d_widget.m_nodes)
			collect_solvers(widget->m_frame, solvers, frame.d_dirty);

		frame.clearDirty();
	}

	void relayout(SolverVector& solvers)
	{
		//for(FrameSolver* solver : solvers)
		//	solver->sync();

		for(FrameSolver* solver : reverse_adapt(solvers))
			solver->compute();

		for(FrameSolver* solver : solvers)
			solver->layout();

		for(FrameSolver* solver : solvers)
			solver->read();
	}

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

	FrameSolver::FrameSolver()
	{}

	FrameSolver::FrameSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: d_frame(frame)
		, d_parent(solver)
		, d_layout(layout)
		, m_solvers{ solver ? &solver->solver(*this, Axis::X) : nullptr, solver ? &solver->solver(*this, Axis::Y) : nullptr }
		, d_grid(solver ? solver->grid() : nullptr)
	{
		if(d_layout)
			this->applySpace();
	}

	FrameSolver& FrameSolver::solver(FrameSolver& frame, Axis dim)
	{
		if(dim == d_length && d_grid && frame.d_frame && frame.d_parent != d_grid) // && !d_layout->m_no_grid
			return d_grid->solver(frame, dim);
		return *this;
	}

	void FrameSolver::applySpace(Axis length)
	{
		const Space& space = d_layout->m_space;

		if(length != Axis::None)
			d_length = length;
		else if(space.direction == FlowAxis::Flip)
			d_length = flip(d_parent->d_length);
		else if(space.direction == FlowAxis::Same)
			d_length = d_parent->d_length;
		else if(space.direction == FlowAxis::Reading)
			d_length = Axis::X;
		else if(space.direction == FlowAxis::Paragraph)
			d_length = Axis::Y;

		d_depth = flip(d_length);

		d_sizing[d_length] = space.sizingLength;
		d_sizing[d_depth] = space.sizingDepth;
	}

	void FrameSolver::collect(SolverVector& solvers)
	{
		this->reset();
		this->sync();
		solvers.push_back(this);
	}

	void FrameSolver::sync()
	{
		if(d_frame)
			d_frame->sync_solver(*this);
	}

	void FrameSolver::compute()
	{
		if(!d_parent) return;
		m_solvers[Axis::X]->compute(*this, Axis::X);
		m_solvers[Axis::Y]->compute(*this, Axis::Y);

#if DEBUG_BOUNDS
		if(!d_frame) return;
		d_frame->debug_print(false);
		printf(" layout measured content size %i , %i\n", int(d_content.x), int(d_content.y));
#endif
	}

	void FrameSolver::layout()
	{
		if(!d_parent) return;
		m_solvers[Axis::X]->layout(*this, Axis::X);
		m_solvers[Axis::Y]->layout(*this, Axis::Y);

#if DEBUG_LAYOUT
		if(!d_frame) return;
		d_frame->debug_print(false);
		printf(" size %i , %i ", int(m_size.x), int(m_size.y));
		printf(" position %i , %i\n", int(m_position.x), int(m_position.y));
#endif
	}

	void FrameSolver::read()
	{
		if(d_frame)
			d_frame->read_solver(*this);
	}

	void FrameSolver::compute(FrameSolver& frame, Axis dim)
	{
		UNUSED(frame); UNUSED(dim);
	}

	void FrameSolver::layout(FrameSolver& frame, Axis dim)
	{
		UNUSED(frame); UNUSED(dim);
	}

	RowSolver::RowSolver()
	{}

	RowSolver::RowSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: FrameSolver(solver, layout, frame)
	{}

	void RowSolver::compute(FrameSolver& frame, Axis dim)
	{
		if(dim == d_length && frame.flow() && frame.d_sizing[d_length] >= Sizing::Wrap)
			d_total_span += frame.m_span[d_length];

		if(!frame.sizeflow())
			return;

		if(frame.d_sizing[dim] <= Sizing::Wrap)
			this->measure(frame, dim);

		if(frame.d_sizing[dim] <= Sizing::Shrink && frame.flow() && dim == d_length)
			m_space_content[dim] += frame.dbounds(dim);

		if(dim == d_length && frame.d_sizing[d_length] >= Sizing::Wrap)
			d_content_expand = true;
	}

	void RowSolver::measure(FrameSolver& frame, Axis dim)
	{
		if(dim == d_length && frame.flow())
		{
			d_content[dim] += frame.dbounds(dim) + (d_count++ ? this->spacing() : 0.f);
			d_spacing[dim] += frame.dmargin(dim) * 2.f + (d_count++ ? this->spacing() : 0.f);
		}
		else
			d_content[dim] = max(d_content[dim], frame.dbounds(dim));
	}

	void RowSolver::layout(FrameSolver& frame, Axis dim)
	{
		if(dim == d_length && frame.flow() && frame.d_sizing[d_length] >= Sizing::Wrap)
			frame.m_span[d_length] = frame.m_span[d_length] / d_total_span;

		this->resize(frame, dim);

		if(frame.posflow())
			this->position(frame, dim);
	}

	void RowSolver::resize(FrameSolver& frame, Axis dim)
	{
		if(d_layout->m_layout[dim] < AutoLayout::Size)
			return;

		float space = this->dspace(dim);
		//bool hasSpace = space > d_content[dim]; // @todo: implement scarcity check, current behavior when scarce is wrong
		if(dim == d_length && frame.flow())
		{
			float spacings = d_spacing[dim];
			space -= (m_space_content[dim] + spacings);
			space *= frame.m_span[d_length];
		}
		else
		{
			space -= frame.dmargin(dim) * 2.f;
		}

		float content = frame.dcontent(dim);

		Sizing sizing = frame.d_sizing[dim];
		if(sizing == Sizing::Shrink)
			frame.m_size[dim] = content;
		else if(sizing == Sizing::Wrap)
			frame.m_size[dim] = max(content, space);
		else if(sizing == Sizing::Expand)
			frame.m_size[dim] = space;
	}

	void RowSolver::position(FrameSolver& frame, Axis dim)
	{
		if(d_layout->m_layout[dim] < AutoLayout::Layout)
			return;

		float space = this->dspace(dim);

		if(dim == d_length && frame.flow())
			frame.m_position[dim] = this->positionSequence(frame, d_content_expand ? 0.f : space - d_content[d_length]);
		else
			frame.m_position[dim] = this->positionFree(frame, dim, space);

		if(dim == d_length && frame.flow())
			d_prev = &frame;
	}

	float RowSolver::positionFree(FrameSolver& frame, Axis dim, float space)
	{
		Align align = frame.dalign(dim);// == d_length ? Axis::X : Axis::Y);
		float alignOffset = space * c_align_space[align] - frame.dextent(dim) * c_align_extent[align];
		return (frame.flow() ? dpadding(dim) + frame.dmargin(dim) : 0.f) + alignOffset;
	}

	float RowSolver::positionSequence(FrameSolver& frame, float space)
	{
		auto alignSequence = [&](FrameSolver& frame, float space) { return space * c_align_space[frame.dalign(d_length)]; };
		if(d_prev)
			return d_prev->doffset(d_length) - alignSequence(*d_prev, space) + this->spacing() + alignSequence(frame, space);
		else
			return dpadding(d_length) + frame.dmargin(d_length) + alignSequence(frame, space);
	}

	CustomSolver::CustomSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: RowSolver(solver, layout, frame)
	{}

	void CustomSolver::collect(SolverVector& solvers)
	{
		FrameSolver::collect(solvers);

		for(auto& solver : m_solvers)
			solver->collect(solvers);
	}

	static Layout& gridOverlayStyle()
	{
		static Layout style;
		//style.m_space = { FlowAxis::Reading, Sizing::Expand, Sizing::Expand };
		style.m_space = { FlowAxis::Reading, Sizing::Wrap, Sizing::Wrap };
		style.m_flow = LayoutFlow::Overlay;
		style.m_spacing = { 2.f, 2.f };
		return style;
	}

	static Layout& columnSolverStyle()
	{
		static Layout style;
		//style.m_space = { FlowAxis::Paragraph, Sizing::Expand, Sizing::Expand };
		style.m_space = { FlowAxis::Paragraph, Sizing::Wrap, Sizing::Wrap };
		style.m_layout = { AutoLayout::Layout, AutoLayout::None };
		return style;
	}

	TableSolver::TableSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: CustomSolver(solver, layout, frame)
	{
		this->divide(layout->m_table_division);
	}

	void TableSolver::divide(span<float> columns)
	{
		m_solvers.clear();
		m_solvers.push_back(construct<RowSolver>(this, &gridOverlayStyle()));
		for(size_t i = 0; i < columns.size(); ++i)
		{
			m_solvers.push_back(construct<RowSolver>(m_solvers.front().get(), &columnSolverStyle()));
			m_solvers.back()->m_span = { columns[i], 0.f };
		}
	}

	void TableSolver::update(span<float> columns)
	{
		if(m_solvers.size() != columns.size() + 1)
			return divide(columns);

		for(size_t i = 0; i < columns.size(); ++i)
			m_solvers[1 + i]->m_span[d_depth] = columns[i];
	}

	FrameSolver& TableSolver::solver(FrameSolver& frame, Axis dim)
	{
		UNUSED(dim);
		if(frame.d_frame && frame.d_parent != this && !frame.d_parent->d_layout->m_no_grid)
		{
			//size_t column0 = frame.d_frame->dindex(d_depth);
			size_t column = frame.d_frame->d_widget.m_index;
			frame.d_frame->d_index[d_depth] = column;
			return 1 + column < m_solvers.size() ? *m_solvers[1 + column] : *this;
		}
		return *this;
	}

	LineSolver::LineSolver(FrameSolver* solver, Space space)
		: RowSolver(solver, nullptr)
		, d_layout()
	{
		d_layout.m_space = space;
		d_layout.m_space.direction = FlowAxis::Reading;
		FrameSolver::d_layout = &d_layout;
		this->applySpace();
	}

	GridSolver::GridSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: CustomSolver(solver, layout, frame)
	{
		this->divide(layout->m_grid_division);
	}

	void GridSolver::divide(span<Space> lines)
	{
		m_solvers.clear();
		for(size_t i = 0; i < lines.size(); ++i)
			m_solvers.push_back(construct<LineSolver>(this, lines[i]));
	}

	FrameSolver& GridSolver::solver(FrameSolver& frame, Axis dim)
	{
		UNUSED(dim);
		if(frame.d_frame)
		{
			size_t row = frame.d_frame->d_index[d_length];
			return *m_solvers[row];
		}
		return *this;
	}
}
