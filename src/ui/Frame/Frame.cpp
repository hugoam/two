//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <infra/String.h>
#include <ui/Frame/Frame.h>
#include <ui/Structs/Widget.h>
#include <ui/Frame/Solver.h>
#include <ui/Frame/Layer.h>
#include <ui/Style/Style.h>
#include <ui/Style/Skin.h>
#include <ui/Render/Renderer.h>
#endif

#include <cstdio>

namespace mud
{
	template <> string to_string<DirtyLayout>(const DirtyLayout& dirty) { if(dirty == CLEAN) return "CLEAN"; else if(dirty == DIRTY_REDRAW) return "DIRTY_REDRAW"; else if(dirty == DIRTY_PARENT) return "DIRTY_PARENT"; else if(dirty == DIRTY_LAYOUT) return "DIRTY_LAYOUT"; else if(dirty == DIRTY_FORCE_LAYOUT) return "DIRTY_FORCE_LAYOUT"; else /*if(dirty == DIRTY_STRUCTURE)*/ return "DIRTY_STRUCTURE"; }

	Vg* Frame::s_vg = nullptr;

	struct Frame::Content
	{
		string d_caption = "";
		Image* d_icon = nullptr;
	};

	Frame::Frame(Frame* parent, Widget& widget)
		: UiRect()
		, d_widget(widget)
		, d_parent(parent)
	{
		if(parent)
		{
			parent->mark_dirty(DIRTY_FORCE_LAYOUT);
			//d_index[d_parent->d_length] = d_widget.d_index;
		}
	}

	Frame::~Frame()
	{
		if(d_parent)
		{
			d_parent->mark_dirty(DIRTY_FORCE_LAYOUT);
			d_parent = nullptr;
		}
	}

	bool Frame::empty() const
	{
		return !d_content || (d_content->d_caption == "" && d_content->d_icon == nullptr);
	}

	Image* Frame::icon() const
	{
		return d_content->d_icon;
	}

	cstring Frame::caption() const
	{
		return d_content->d_caption.c_str();
	}

	FrameSolver& Frame::solver(Style& style, Dim length, Dim2<size_t> index)
	{
		d_style = &style;
		d_layout = &style.layout();
		d_index = index;

		this->update_style();

		LayoutSolver type = d_layout->m_solver;
		FrameSolver* solver = d_parent ? d_parent->m_solver.get() : nullptr;

		if(type == FRAME_SOLVER)
			m_solver = make_object<FrameSolver>(solver, d_layout, this);
		else if(type == ROW_SOLVER)
			m_solver = make_object<RowSolver>(solver, d_layout, this);
		else if(type == GRID_SOLVER)
			m_solver = make_object<GridSolver>(solver, d_layout, this);
		else if(type == TABLE_SOLVER)
			m_solver = make_object<TableSolver>(solver, d_layout, this);

		m_solver->applySpace(length);
		return *m_solver;
	}

	Frame& Frame::root()
	{
		return d_parent ? d_parent->root() : *this;
	}

	Layer& Frame::layer()
	{
		return m_layer ? *m_layer : d_parent->layer();
	}

	void Frame::mark_dirty(DirtyLayout dirty)
	{
		this->set_dirty(dirty);
		if(dirty == DIRTY_FORCE_LAYOUT)
			dirty = DIRTY_LAYOUT;
		Frame* parent = this->d_parent;
		while(parent)
		{
			parent->set_dirty(dirty);
			parent = parent->d_parent;
		}
	}

	void Frame::update_style(bool reset)
	{
		d_layout = &d_style->layout();
		m_opacity = d_layout->m_opacity;
		m_size = d_layout->m_size == Zero2 ? m_size : d_layout->m_size;

		this->update_inkstyle(d_style->state_skin(d_widget.m_state));

		reset ? this->mark_dirty(DIRTY_FORCE_LAYOUT) : this->mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::update_state(WidgetState state)
	{
		InkStyle& inkstyle = d_style->state_skin(state);
		this->update_inkstyle(inkstyle);
	}

	void Frame::update_inkstyle(InkStyle& inkstyle)
	{
		bool skin_image = d_inkstyle && d_inkstyle->m_image;
		if(d_inkstyle == &inkstyle) return;
		//printf("INFO: Update inkstyle %s\n", inkstyle.m_name.c_str());
		d_inkstyle = &inkstyle;
		this->mark_dirty(DIRTY_REDRAW);

		if(d_inkstyle->m_image || skin_image)
			this->set_icon(d_inkstyle->m_image);
	}

	void Frame::set_caption(cstring text)
	{
		if(!d_content)
			d_content = make_unique<Content>();
		if(d_content->d_caption == text)
			return;
		d_content->d_caption = text;
		if(d_content->d_caption != "")
		{
			TextPaint paint = text_paint(*d_inkstyle);
			m_content = s_vg->text_size(d_content->d_caption.c_str(), d_content->d_caption.size(), paint);
		}
		else
			m_content = Zero2;
		mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_icon(Image* image)
	{
		if(!d_content)
			d_content = make_unique<Content>();
		if(d_content->d_icon == image)
			return;
		d_content->d_icon = image;
		m_content = image ? vec2{ image->d_size } : Zero2;
		mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_size(Dim dim, float size)
	{
		if(m_size[dim] == size) return;
		m_size[dim] = size;
		this->mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::set_span(Dim dim, float span)
	{
		if(m_span[dim] == span) return;
		m_span[dim] = span;
		this->mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::set_position(Dim dim, float position)
	{
		if(m_position[dim] == position) return;
		m_position[dim] = position;
		this->mark_dirty(DIRTY_REDRAW);
	}

	void Frame::integrate_position(Frame& root, vec2& global)
	{
		if(this == &root) return;
		d_parent->integrate_position(root, global);
		global = (global - m_position) / m_scale;
	}

	void Frame::derive_position(Frame& root, vec2& local)
	{
		if(this == &root) return;
		local = m_position + local * m_scale;
		d_parent->derive_position(root, local);
	}

	float Frame::derive_scale(Frame& root)
	{
		if(this == &root)
			return m_scale;
		else 
			return d_parent->derive_scale(root) * m_scale;
	}

	Frame* clip_parent(Frame& frame)
	{
		Frame* parent = frame.d_parent;
		while(parent->d_layout->m_clipping != CLIP)
			parent = parent->d_parent;
		return parent;
	}

	void Frame::clamp_to_parent()
	{
		//Frame* clip = clip_parent(*this);
		Frame* clip = &this->root();
		vec2 position = this->derive_position(Zero2, *clip);

		for(Dim dim : { DIM_X, DIM_Y })
		{
			m_size[dim] = min(clip->m_size[dim], m_size[dim]);

			float overflow = position[dim] + m_size[dim] - clip->m_size[dim];
			m_position[dim] -= max(0.f, overflow);
		}
	}

	vec4 Frame::content_rect() const
	{
		return { floor(rect_offset(d_inkstyle->m_margin)),
				 floor(m_size - rect_sum(d_inkstyle->m_margin)) };
	}

	bool Frame::inside(const vec2& pos)
	{
		return (pos.x >= 0.f && pos.x <= m_size.x
			 && pos.y >= 0.f && pos.y <= m_size.y);
	}

	bool Frame::first(const Frame& frame)
	{
		return frame.d_widget.m_index == 0;
	}

	bool Frame::last(const Frame& frame)
	{
		return frame.d_widget.m_index == d_widget.m_nodes.size() - 1;
	}

	void Frame::transfer_pixel_span(Frame& prev, Frame& next, Dim dim, float pixelSpan)
	{
		float pixspan = 1.f / this->m_size[dim];
		float offset = pixelSpan * pixspan;

		prev.set_span(dim, max(0.01f, prev.m_span[dim] + offset));
		next.set_span(dim, max(0.01f, next.m_span[dim] - offset));
		this->mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::relayout()
	{
		DirtyLayout dirty = this->clearDirty();
		if(!dirty) return;

		SolverVector solvers;
		for(auto& widget : d_widget.m_nodes)
			collect_solvers(widget->m_frame, solvers, dirty);

		m_solver->reset();
		m_solver->m_size = m_size;

		mud::relayout(solvers);
	}

	void Frame::sync_solver(FrameSolver& solver)
	{
		vec2 content = m_content + rect_sum(d_inkstyle->m_padding);
		solver.setup(m_position, m_size, m_span, m_content != Zero2 ? &content : nullptr);

		if(d_dirty == DIRTY_PARENT)
		{
			// @bug this causes a bug in the relayout if we want to implement scarce behavior for wrap frames, since here the content is instead just the unpadded size
			solver.d_content = m_size - rect_sum(solver.d_layout->m_padding);
		}
	}

	void fix_position(Frame& frame, Dim dim, FrameSolver* solver)
	{
		// @todo should be while but it causes a bug with nested tables
		if(solver->m_solvers[dim] && solver->m_solvers[dim]->d_frame != frame.d_parent)
		{
			if(!solver->m_solvers[dim]->d_frame)
				frame.m_position[dim] += solver->m_solvers[dim]->m_position[dim];
			solver = solver->m_solvers[dim];
		}
	}

	void Frame::read_solver(FrameSolver& solver)
	{
		this->set_position(solver.m_position);
		this->set_size(solver.m_size);
		m_span = solver.m_span;

		fix_position(*this, DIM_X, &solver);
		fix_position(*this, DIM_Y, &solver);
	}

	void Frame::debug_print(bool commit)
	{
		Frame* parent = this->d_parent;
		while(parent)
		{
			printf("  ");
			parent = parent->d_parent;
		}
		printf("FRAME: %s ", d_style->name());
		if(commit)
			printf("\n");
	}
}
