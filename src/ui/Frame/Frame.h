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

	// the frame of a widget: the data of its layout and of its drawing, which knows nothing of the other frames
	// what involves its parent or its root (dirtying, layers, absolute positions) is done by the widget
	export_ class refl_ TWO_UI_EXPORT Frame : public UiRect
	{
	public:
		Frame();
		~Frame();

		inline bool opaque() const { return m_opacity == Opacity::Opaque; }
		inline bool hollow() const { return m_opacity == Opacity::Hollow; }

		vec4 content_rect() const;

		bool inside(const vec2& pos) const;

	public:
		v2<uint> d_index = { 0, 0 };
		Axis d_length_override = Axis::None;	// the flow axis given explicitly, overriding the one of the style
		Axis d_length = Axis::None;				// the flow axis, as resolved by the last layout

		Opacity m_opacity = Opacity::Clear;

		Style* d_style = nullptr;
		Layout* d_layout = nullptr;
		InkStyle* d_inkstyle = nullptr;

		static Vg* s_vg;
	};

	// what the layout and the positions of a frame derive from it and its parents, by node index next to the frames
	export_ struct TWO_UI_EXPORT FrameCache
	{
		DirtyLayout clearDirty() { DirtyLayout dirty = d_dirty; d_dirty = CLEAN; return dirty; }
		void set_dirty(DirtyLayout dirty) { if(dirty > d_dirty) d_dirty = dirty; }

		DirtyLayout d_dirty = DIRTY_LAYOUT;

		vec2 d_absolute = vec2(0.f);	// the position of the frame in the space of its root
		float d_scale = 1.f;			// the scale of the frame and of its parents, below the root
		uint64_t d_epoch = 0;			// the positions and scales the cache was resolved with: valid while it's the current one

		// the current positions and scales: changes whenever a frame moves, scales, or changes parent
		static uint64_t s_epoch;
	};

	// the caption and the icon of a widget, which its frame draws and is sized by: a state of its node, only the widgets with a caption or an icon have one
	// a widget showing a text has it as a state of its node too
	export_ struct FrameContent
	{
		string m_caption;
		Image* m_icon = nullptr;
	};
}
