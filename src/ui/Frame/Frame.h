//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Frame/UiRect.h>

namespace two
{
	using cstring = const char*;

	enum DirtyLayout : unsigned int
	{
		CLEAN,				// the frame doesn't need update
		DIRTY_REDRAW,		// the frame needs to be redrawn: its layer is redrawn right away
		DIRTY_LAYOUT		// the frame needs to be laid out: the whole tree is laid out from its root
	};

	export_ class refl_ TWO_UI_EXPORT Frame : public UiRect
	{
	public:
		Frame(Frame* parent, Widget& widget);
		virtual ~Frame();

		bool empty() const;

		inline bool opaque() const { return m_opacity == Opacity::Opaque; }
		inline bool hollow() const { return m_opacity == Opacity::Hollow; }

		void set_caption(cstring text);
		void set_icon(Image* image);
		Image* icon() const;
		cstring caption() const;

		void size_caption();

		Frame& root();
		Layer& layer();

		void init(Style& style, Axis length = Axis::None, v2<uint> index = { 0, 0 });

		DirtyLayout clearDirty() { DirtyLayout dirty = d_dirty; d_dirty = CLEAN; return dirty; }
		void set_dirty(DirtyLayout dirty) { if(dirty > d_dirty) d_dirty = dirty; }
		void mark_dirty(DirtyLayout dirty);

		void update_style(bool reset = false);
		void update_state(WidgetState state);
		void update_inkstyle(InkStyle& inkstyle, bool reset = false);

		void set_size(Axis dim, float size);
		void set_span(Axis dim, float span);
		void set_position(Axis dim, float position);
		void set_scale(float scale);

		inline void set_position(const vec2& pos) { set_position(Axis::X, pos.x), set_position(Axis::Y, pos.y); }
		inline void set_size(const vec2& size) { set_size(Axis::X, size.x); set_size(Axis::Y, size.y); }

		// the position and the scale of the frame in the space of its root, inherited from its parents:
		// they are cached until a frame moves or scales, and resolved for all the frames in one pass by the layout
		void resolve();

		// from the local space of the frame to the space of its root, or of an ancestor
		inline vec2 absolute_position() { resolve(); return d_absolute; }
		inline vec2 derive_position(const vec2& local) { resolve(); return d_absolute + local * d_scale; }
		inline vec2 derive_position(const vec2& local, Frame& root) { resolve(); root.resolve(); return (d_absolute + local * d_scale - root.d_absolute) / root.d_scale; }

		// from the space of its root, or of an ancestor, to the local space of the frame
		inline vec2 local_position(const vec2& pos) { resolve(); return (pos - d_absolute) / d_scale; }
		inline vec2 integrate_position(const vec2& pos, Frame& root) { resolve(); root.resolve(); return (root.d_absolute + pos * root.d_scale - d_absolute) / d_scale; }

		// the scale of the frame and of its parents up to an ancestor, including it
		inline float derive_scale(Frame& root) { resolve(); root.resolve(); return d_scale / root.d_scale * root.m_scale; }
		inline float absolute_scale() { return this->derive_scale(root()); }

		void clamp_to_parent();

		vec4 content_rect() const;

		bool inside(const vec2& pos);
		bool inside_abs(const vec2& pos) { return this->inside(local_position(pos)); }

		bool first(const Frame& frame);
		bool last(const Frame& frame);

		void transfer_pixel_span(Frame& prev, Frame& next, Axis dim, float pixelSpan);

		void relayout();

		void debug_print(bool commit);

	public:
		Widget& d_widget;
		Frame* d_parent;
		DirtyLayout d_dirty = DIRTY_LAYOUT;

		vec2 d_absolute = vec2(0.f);	// the position of the frame in the space of its root
		float d_scale = 1.f;			// the scale of the frame and of its parents, below the root
		uint64_t d_epoch = 0;			// the positions and scales the cache was resolved with: valid while it's the current one

		// the current positions and scales: changes whenever a frame moves, scales, or changes parent
		static uint64_t s_epoch;
		v2<uint> d_index = { 0, 0 };
		Axis d_length_override = Axis::None;	// the flow axis given explicitly, overriding the one of the style
		Axis d_length = Axis::None;				// the flow axis, as resolved by the last layout
		span<float> d_columns;					// the weights of the columns, for a table

		Opacity m_opacity = Opacity::Clear;

		Style* d_style = nullptr;
		Layout* d_layout = nullptr;
		InkStyle* d_inkstyle = nullptr;

	public:
		string d_caption = "";
		Image* d_icon = nullptr;

		unique<Layer> m_layer;
		unique<Text> m_text;

		static Vg* s_vg;
	};
}
