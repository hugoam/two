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

	Frame::Frame()
		: UiRect()
	{}

	Frame::~Frame()
	{}

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

	void Widget::set_style(Style& style, Axis length, v2<uint> index)
	{
		m_frame.d_style = &style;
		m_frame.d_layout = &style.m_layout;
		m_frame.d_index = index;
		m_frame.d_length_override = length;

		this->update_style();
	}

	Layer& Widget::draw_layer()
	{
		return m_frame.m_layer ? *m_frame.m_layer : this->parent()->draw_layer();
	}

	// a frame to lay out lays out the whole tree, from its root, and a frame to redraw redraws its layer
	void Widget::mark_dirty(DirtyLayout dirty)
	{
		if(dirty == DIRTY_LAYOUT)
		{
			m_frame.set_dirty(DIRTY_LAYOUT);
			this->root().m_frame.set_dirty(DIRTY_LAYOUT);
		}
		else if(dirty == DIRTY_REDRAW)
		{
			Widget* widget = this;
			while(widget && !widget->m_frame.m_layer)
				widget = widget->parent();
			if(widget)
			{
				widget->m_frame.m_layer->setRedraw();
				widget->m_frame.m_layer->setForceRedraw(); // @ kludge for nodes in canvas when moving the canvas window
			}
		}
	}

	void Widget::update_style(bool reset)
	{
		m_frame.d_layout = &m_frame.d_style->m_layout;

		InkStyle& inkstyle = m_frame.d_style->state_skin(m_state);
		this->update_inkstyle(inkstyle, reset);

		m_frame.m_opacity = m_frame.d_layout->m_opacity;
		m_frame.m_size = m_frame.d_layout->m_size == vec2(0.f) ? m_frame.m_size : m_frame.d_layout->m_size;

		UNUSED(reset);
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Widget::update_state(WidgetState state)
	{
		InkStyle& inkstyle = m_frame.d_style->state_skin(state);
		this->update_inkstyle(inkstyle);
	}

	void Widget::update_inkstyle(InkStyle& inkstyle, bool reset)
	{
		if(m_frame.d_inkstyle == &inkstyle && !reset) return;
		//printf("[debug] Update inkstyle %s\n", inkstyle.m_name.c_str());
		m_frame.d_inkstyle = &inkstyle;
		this->mark_dirty(DIRTY_REDRAW);
		this->set_icon(m_frame.d_inkstyle->m_image);
		if(m_frame.d_caption != "")
			m_frame.size_caption();
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

	void Widget::set_caption(cstring text)
	{
		if(m_frame.d_caption == text)
			return;
		m_frame.d_caption = text;
		m_frame.m_size = vec2(0.f);
		m_frame.size_caption();
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Widget::set_icon(Image* image)
	{
		if(m_frame.d_icon == image)
			return;
		m_frame.d_icon = image;
		m_frame.m_size = vec2(0.f);
		m_frame.m_content = image ? vec2(image->d_size) : vec2(0.f);
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Widget::set_size(Axis dim, float size)
	{
		if(m_frame.m_size[dim] == size) return;
		m_frame.m_size[dim] = size;
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Widget::set_span(Axis dim, float span)
	{
		if(m_frame.m_span[dim] == span) return;
		m_frame.m_span[dim] = span;
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Widget::set_position(Axis dim, float position)
	{
		if(m_frame.m_position[dim] == position) return;
		m_frame.m_position[dim] = position;
		++Frame::s_epoch;
		this->mark_dirty(DIRTY_REDRAW);
	}

	void Widget::set_scale(float scale)
	{
		if(m_frame.m_scale == scale) return;
		m_frame.m_scale = scale;
		++Frame::s_epoch;
		this->mark_dirty(DIRTY_REDRAW);
	}

	// a frame resolves its parent first, which is cached in turn: a frame resolves once for the current positions
	void Widget::resolve()
	{
		if(m_frame.d_epoch == Frame::s_epoch)
			return;
		if(Widget* parent = this->parent())
		{
			parent->resolve();
			m_frame.d_absolute = parent->m_frame.d_absolute + m_frame.m_position * parent->m_frame.d_scale;
			m_frame.d_scale = parent->m_frame.d_scale * m_frame.m_scale;
		}
		else
		{
			m_frame.d_absolute = vec2(0.f);
			m_frame.d_scale = 1.f;
		}
		m_frame.d_epoch = Frame::s_epoch;
	}

	void Widget::clamp_to_parent()
	{
		Widget& clip = this->root();
		const vec2 position = this->derive_position(vec2(0.f), clip);

		for(Axis dim : { Axis::X, Axis::Y })
		{
			m_frame.m_size[dim] = min(clip.m_frame.m_size[dim], m_frame.m_size[dim]);

			const float overflow = position[dim] + m_frame.m_size[dim] - clip.m_frame.m_size[dim];
			this->set_position(dim, m_frame.m_position[dim] - max(0.f, overflow));
		}
	}

	vec4 Frame::content_rect() const
	{
		return { floor(d_inkstyle->m_margin.pos),
				 floor(m_size - rect_sum(d_inkstyle->m_margin)) };
	}

	bool Frame::inside(const vec2& pos) const
	{
		return (pos.x >= 0.f && pos.x <= m_size.x
			 && pos.y >= 0.f && pos.y <= m_size.y);
	}

	void Widget::transfer_pixel_span(Widget& prev, Widget& next, Axis dim, float pixelSpan)
	{
		float pixspan = 1.f / m_frame.m_size[dim];
		float offset = pixelSpan * pixspan;

		prev.set_span(dim, max(0.01f, prev.m_frame.m_span[dim] + offset));
		next.set_span(dim, max(0.01f, next.m_frame.m_span[dim] - offset));
		this->mark_dirty(DIRTY_LAYOUT);
	}

	void Widget::relayout()
	{
		if(m_frame.clearDirty() < DIRTY_LAYOUT)
			return;

		static LayoutTree tree;
		tree.build(*this);
		tree.solve();
		tree.clear_dirty();
		tree.apply();
	}

	void Widget::debug_print(bool commit)
	{
		Widget* parent = this->parent();
		while(parent)
		{
			printf("  ");
			parent = parent->parent();
		}
		printf("FRAME: %s ", m_frame.d_style->m_name.c_str());
		if(commit)
			printf("\n");
	}
}
