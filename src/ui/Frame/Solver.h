//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Frame/Frame.h>
#include <ui/Style/Layout.h>

namespace two
{
	using SolverVector = vector<FrameSolver*>;

	void collect_solvers(Frame& frame, SolverVector& solvers, DirtyLayout dirtyTop);
	void relayout(SolverVector& solvers);

	export_ class refl_ TWO_UI_EXPORT FrameSolver : public UiRect
	{
	public:
		FrameSolver();
		FrameSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);
		virtual ~FrameSolver() {}

		inline bool flow() { return d_layout->m_flow == LayoutFlow::Flow; }
		inline bool posflow() { return d_layout->m_flow <= LayoutFlow::Align; }
		inline bool sizeflow() { return d_layout->m_flow <= LayoutFlow::Overlay; }

		inline float dpadding(Axis dim) { return d_layout->m_padding[size_t(dim)]; }
		inline float dbackpadding(Axis dim) { return d_layout->m_padding[size_t(dim) + 2]; }
		inline float dmargin(Axis dim) { return d_layout->m_margin[dim]; }

		inline Align dalign(Axis dim) { return d_layout->m_align[dim]; }

		inline float dcontent(Axis dim) { return d_content[dim] + dpadding(dim) + dbackpadding(dim); }
		inline float dbounds(Axis dim) { return dcontent(dim) + dmargin(dim) * 2.f; }

		inline float dextent(Axis dim) { return m_size[dim] + dmargin(dim) * 2.f; }
		inline float doffset(Axis dim) { return m_position[dim] + m_size[dim] + dmargin(dim); }
		inline float dspace(Axis dim) { return m_size[dim] - dpadding(dim) - dbackpadding(dim); }

		//inline float spacing(FrameSolver& frame) { return d_prev ? d_layout->m_spacing[d_length] : 0.f; }
		inline float spacing() { return d_layout->m_spacing[d_length]; }

		void setup(const vec2& position, const vec2& size, const vec2& span, const vec2* content)
		{
			m_position = position;
			m_span = span;
			m_size = size;

			if(d_sizing.x == Sizing::Fixed) d_content.x = (content ? content->x : m_size.x - dpadding(Axis::X) - dbackpadding(Axis::X));
			if(d_sizing.y == Sizing::Fixed) d_content.y = (content ? content->y : m_size.y - dpadding(Axis::Y) - dbackpadding(Axis::Y));
			if(d_sizing.x == Sizing::Fixed) m_size.x = d_content.x + dpadding(Axis::X) + dbackpadding(Axis::X);
			if(d_sizing.y == Sizing::Fixed) m_size.y = d_content.y + dpadding(Axis::Y) + dbackpadding(Axis::Y);
		}

		void reset(bool partial = false)
		{
			m_size = { 0.f, 0.f };
			if(!partial)
				d_content = { 0.f, 0.f };
			d_spacing = { 0.f, 0.f };
			m_space_content = { 0.f, 0.f };
			d_content_expand = false;
			d_total_span = 0.f;
			d_prev = nullptr;
			d_count = 0;
		}

		void applySpace(Axis length = Axis::None);

		virtual void collect(SolverVector& solvers);

		virtual FrameSolver& solver(FrameSolver& frame, Axis dim);
		virtual FrameSolver* grid() { return nullptr; }

		void sync();
		void compute();
		void layout();
		void read();

		virtual void compute(FrameSolver& frame, Axis dim);
		virtual void layout(FrameSolver& frame, Axis dim);

	public:
		Frame* d_frame;
		FrameSolver* d_parent;
		Layout* d_layout;

		table<Axis, FrameSolver*> m_solvers;
		//FrameSolver* m_solvers[2];
		FrameSolver* d_grid;

		Axis d_length = Axis::None;
		Axis d_depth = Axis::None;

		v2<Sizing> d_sizing = { Sizing::Shrink, Sizing::Shrink };

		vec2 d_content = { 0.f, 0.f };
		vec2 d_spacing = { 0.f, 0.f };
		vec2 m_space_content = { 0.f, 0.f };
		bool d_content_expand = false;
		float d_total_span;

		v2<uint> d_index;

		FrameSolver* d_prev = nullptr;
		size_t d_count = 0;
	};

	export_ class refl_ TWO_UI_EXPORT RowSolver : public FrameSolver
	{
	public:
		RowSolver();
		RowSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		virtual void compute(FrameSolver& frame, Axis dim);
		virtual void layout(FrameSolver& frame, Axis dim);

	protected:
		void measure(FrameSolver& frame, Axis dim);
		void resize(FrameSolver& frame, Axis dim);
		void position(FrameSolver& frame, Axis dim);

		float positionFree(FrameSolver& frame, Axis dim, float space);
		float positionSequence(FrameSolver& frame, float space);
	};

	export_ class TWO_UI_EXPORT CustomSolver : public RowSolver
	{
	public:
		CustomSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		CustomSolver(const CustomSolver& other) = delete;
		CustomSolver& operator=(const CustomSolver& other) = delete;

		virtual void collect(SolverVector& solvers);

	protected:
		vector<unique<FrameSolver>> m_solvers;
	};

	export_ class refl_ TWO_UI_EXPORT TableSolver : public CustomSolver
	{
	public:
		TableSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		void divide(span<float> spans);
		void update(span<float> spans);

		virtual FrameSolver& solver(FrameSolver& frame, Axis dim);
		virtual FrameSolver* grid() { return this; }
	};

	export_ class refl_ TWO_UI_EXPORT LineSolver : public RowSolver
	{
	public:
		LineSolver(FrameSolver* solver, Space space);
		LineSolver(const LineSolver& other) = delete; // @kludge for clang modules bug
		LineSolver& operator=(const LineSolver& other) = delete;
		
		Layout d_layout;
	};

	export_ class refl_ TWO_UI_EXPORT GridSolver : public CustomSolver
	{
	public:
		GridSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		void divide(span<Space> spaces);

		virtual FrameSolver& solver(FrameSolver& frame, Axis dim);
	};
}
