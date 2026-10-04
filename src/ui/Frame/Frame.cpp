//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	template struct v2<bool>;
	template struct v2<AutoLayout>;
	template struct v2<Sizing>;
	template struct v2<Align>;
	template struct v2<Pivot>;

	template <> string to_string<DirtyLayout>(const DirtyLayout& dirty) { if(dirty == CLEAN) return "CLEAN"; else if(dirty == DIRTY_REDRAW) return "DIRTY_REDRAW"; else return "DIRTY_LAYOUT"; }

	Vg* Frame::s_vg = nullptr;
	uint64_t Frame::s_epoch = 1;

	Frame::Frame(Frame* parent, Widget& widget)
		: UiRect()
		, d_widget(widget)
		, d_parent(parent)
	{
		if(parent)
		{
			parent->mark_dirty(DIRTY_LAYOUT);
			//d_index[d_parent->d_length] = d_widget.d_index;
		}
	}

	Frame::~Frame()
	{
		if(d_parent)
		{
			d_parent->mark_dirty(DIRTY_LAYOUT);
			d_parent = nullptr;
		}
	}

	bool Frame::empty() const
	{
		return d_caption == "" && d_icon == nullptr && !m_text;
	}

	Image* Frame::icon() const
	{
		return d_icon;
	}

	cstring Frame::caption() const
	{
		return d_caption.c_str();
	}

	void Frame::init(Style& style, Axis length, v2<uint> index)
	{
		d_style = &style;
		d_layout = &style.m_layout;
		d_index = index;
		d_length_override = length;

		this->update_style();
	}

	Frame& Frame::root()
	{
		return d_widget.m_root ? d_widget.m_root->m_frame : *this;
	}

	Layer& Frame::layer()
	{
		return m_layer ? *m_layer : d_parent->layer();
	}

	// a frame to lay out lays out the whole tree, from its root, and a frame to redraw redraws its layer
	void Frame::mark_dirty(DirtyLayout dirty)
	{
		if(dirty == DIRTY_LAYOUT)
		{
			this->set_dirty(DIRTY_LAYOUT);
			this->root().set_dirty(DIRTY_LAYOUT);
		}
		else if(dirty == DIRTY_REDRAW)
		{
			Frame* frame = this;
			while(frame && !frame->m_layer)
				frame = frame->d_parent;
			if(frame)
			{
				frame->m_layer->setRedraw();
				frame->m_layer->setForceRedraw(); // @ kludge for nodes in canvas when moving the canvas window
			}
		}
	}

	void Frame::update_style(bool reset)
	{
		d_layout = &d_style->m_layout;

		InkStyle& inkstyle = d_style->state_skin(d_widget.m_state);
		this->update_inkstyle(inkstyle, reset);

		m_opacity = d_layout->m_opacity;
		m_size = d_layout->m_size == vec2(0.f) ? m_size : d_layout->m_size;

		UNUSED(reset);
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::update_state(WidgetState state)
	{
		InkStyle& inkstyle = d_style->state_skin(state);
		this->update_inkstyle(inkstyle);
	}

	void Frame::update_inkstyle(InkStyle& inkstyle, bool reset)
	{
		if(d_inkstyle == &inkstyle && !reset) return;
		//printf("[debug] Update inkstyle %s\n", inkstyle.m_name.c_str());
		d_inkstyle = &inkstyle;
		this->mark_dirty(DIRTY_REDRAW);
		this->set_icon(d_inkstyle->m_image);
		if(d_caption != "")
			this->size_caption();
	}

	void Frame::size_caption()
	{
		if(d_caption != "")
		{
			TextPaint paint = text_paint(*d_inkstyle);
			m_content = s_vg->text_size(d_caption.c_str(), d_caption.size(), paint);
		}
		else
			m_content = vec2(0.f);
	}

	void Frame::set_caption(cstring text)
	{
		if(d_caption == text)
			return;
		d_caption = text;
		m_size = vec2(0.f);
		this->size_caption();
		mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_icon(Image* image)
	{
		if(d_icon == image)
			return;
		d_icon = image;
		m_size = vec2(0.f);
		m_content = image ? vec2(image->d_size) : vec2(0.f);
		mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_size(Axis dim, float size)
	{
		if(m_size[dim] == size) return;
		m_size[dim] = size;
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_span(Axis dim, float span)
	{
		if(m_span[dim] == span) return;
		m_span[dim] = span;
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_position(Axis dim, float position)
	{
		if(m_position[dim] == position) return;
		m_position[dim] = position;
		++s_epoch;
		this->mark_dirty(DIRTY_REDRAW);
	}

	void Frame::set_scale(float scale)
	{
		if(m_scale == scale) return;
		m_scale = scale;
		++s_epoch;
		this->mark_dirty(DIRTY_REDRAW);
	}

	// a frame resolves its parent first, which is cached in turn: a frame resolves once for the current positions
	void Frame::resolve()
	{
		if(d_epoch == s_epoch)
			return;
		if(d_parent)
		{
			d_parent->resolve();
			d_absolute = d_parent->d_absolute + m_position * d_parent->d_scale;
			d_scale = d_parent->d_scale * m_scale;
		}
		else
		{
			d_absolute = vec2(0.f);
			d_scale = 1.f;
		}
		d_epoch = s_epoch;
	}

	void Frame::clamp_to_parent()
	{
		Frame& clip = this->root();
		const vec2 position = this->derive_position(vec2(0.f), clip);

		for(Axis dim : { Axis::X, Axis::Y })
		{
			m_size[dim] = min(clip.m_size[dim], m_size[dim]);

			const float overflow = position[dim] + m_size[dim] - clip.m_size[dim];
			this->set_position(dim, m_position[dim] - max(0.f, overflow));
		}
	}

	vec4 Frame::content_rect() const
	{
		return { floor(d_inkstyle->m_margin.pos),
				 floor(m_size - rect_sum(d_inkstyle->m_margin)) };
	}

	bool Frame::inside(const vec2& pos)
	{
		return (pos.x >= 0.f && pos.x <= m_size.x
			 && pos.y >= 0.f && pos.y <= m_size.y);
	}

	bool Frame::first(const Frame& frame)
	{
		return d_widget.is_first(frame.d_widget);
	}

	bool Frame::last(const Frame& frame)
	{
		return d_widget.is_last(frame.d_widget);
	}

	void Frame::transfer_pixel_span(Frame& prev, Frame& next, Axis dim, float pixelSpan)
	{
		float pixspan = 1.f / this->m_size[dim];
		float offset = pixelSpan * pixspan;

		prev.set_span(dim, max(0.01f, prev.m_span[dim] + offset));
		next.set_span(dim, max(0.01f, next.m_span[dim] - offset));
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::relayout()
	{
		if(this->clearDirty() < DIRTY_LAYOUT)
			return;

		static LayoutTree tree;
		tree.build(*this);
		tree.solve();
		tree.clear_dirty();
		tree.apply();
	}

	void Frame::debug_print(bool commit)
	{
		Frame* parent = this->d_parent;
		while(parent)
		{
			printf("  ");
			parent = parent->d_parent;
		}
		printf("FRAME: %s ", d_style->m_name.c_str());
		if(commit)
			printf("\n");
	}
}
