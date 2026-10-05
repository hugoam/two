//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Frame/Frame.h>
#include <ui/Widget.h>

namespace two
{
	using FrameFilter = bool(*)(Frame&);

#ifndef _MSC_VER
	extern template class PooledNode<Widget>;
#endif

	export_ class refl_ TWO_UI_EXPORT Widget : public PooledNode<Widget>, public ControlNode
	{
	public:
		Widget(PooledGraph<Widget>& graph);
		Widget(Widget* parent);
		virtual ~Widget();

		void reparent(Widget* old);

		meth_ inline bool focused() { return (m_state & FOCUSED) != 0; }
		meth_ inline bool hovered() { return (m_state & HOVERED) != 0; }
		meth_ inline bool pressed() { return (m_state & PRESSED) != 0; }
		meth_ inline bool activated() { return (m_state & ACTIVATED) != 0; }
		meth_ inline bool active() { return (m_state & ACTIVE) != 0; }
		meth_ inline bool selected() { return (m_state & SELECTED) != 0; }
		meth_ inline bool modal() { return (m_state & FOCUSED) != 0; }
		meth_ inline bool closed() { return (m_state & CLOSED) != 0; }
		meth_ inline bool open() { return (m_state & OPEN) != 0; }

		meth_ UiWindow& ui_window();
		meth_ Ui& ui();
		meth_ Widget& parent_modal();

		meth_ void clear();

		void set_content(cstring content);

		meth_ void toggle_state(WidgetState state);

		meth_ inline void disable_state(WidgetState state) { if(m_state & state) this->toggle_state(state); }
		meth_ inline void set_state(WidgetState state, bool enabled) { enabled ? enable_state(state) : disable_state(state); }
		meth_ inline void enable_state(WidgetState state) { if(!(m_state & state)) this->toggle_state(state); }

		// the open state is not skinned: it doesn't update the style
		meth_ inline void set_open(bool open) { m_state = WidgetState(open ? (m_state | OPEN) : (m_state & ~OPEN)); }

		meth_ inline void clear_focus() { this->parent_modal().set_modal(nullptr, device_mask(DeviceType::Keyboard)); }
		meth_ inline void take_focus() { if(!this->modal()) this->take_modal(device_mask(DeviceType::Keyboard)); }
		meth_ inline void yield_focus() { this->yield_modal(); }

		meth_ inline void take_modal(uint32_t device_filter = uint32_t(DeviceMask::All)) { this->parent_modal().set_modal(this, device_filter); }
		meth_ void yield_modal();

		void set_modal(Widget* widget, uint32_t device_filter);

		Widget* pinpoint(vec2 pos);
		Widget* pinpoint(vec2 pos, const FrameFilter& filter);

		//inline bool fits_modifier(InputMod modifier, InputMod mask) { return mask == InputMod::Any || modifier == mask; }
		//
		//meth_ KeyEvent key_event(Key code, EventType event_type, InputMod modifier = InputMod::Any);
		//meth_ KeyEvent key_stroke(Key code, InputMod modifier = InputMod::Any) { return key_event(code, EventType::Stroked, modifier); }
		//meth_ KeyEvent char_stroke(Key code, InputMod modifier = InputMod::Any) { return key_event(translate(code), EventType::Stroked, modifier); }
		//
		//meth_ MouseEvent mouse_event(DeviceType device, EventType event_type, InputMod modifier = InputMod::None, bool consume = true);
		
		void transform_event(InputEvent& event);

		virtual ControlNode* control_event(InputEvent& event) override;
		virtual void receive_event(InputEvent& event) override;
		//virtual ControlNode* propagate_event(InputEvent& event) override;

		// the frame of the widget, its data by node index in the frames of the ui
		attr_ inline Frame& frame();
		attr_ WidgetState m_state = CREATED;
		attr_ uint32_t m_switch = 0;

		using CustomRender = function<void(Widget&, const vec4&, Vg&)>;
		CustomRender m_custom_draw;

		Widget& layer();

		inline bool once() { if((m_state & CREATED) != 0) { disable_state(CREATED); return true; } return false; }
		inline Widget& init(Style& style, bool open = false, Axis length = Axis::None, v2<uint> index = { 0, 0 }) { if(!frame().d_style) { this->set_style(style, length, index); this->set_open(open); } return *this; }

		// --- frame ---
		// the frame of the widget: its layout and its drawing, on the data of frame(), and of the frames of its parents (Frame.cpp)

		void set_style(Style& style, Axis length = Axis::None, v2<uint> index = { 0, 0 });

		// the layer the frame is drawn in: its own, or the one of its parent
		Layer& draw_layer();

		void mark_dirty(DirtyLayout dirty);

		void update_style(bool reset = false);
		void update_state(WidgetState state);
		void update_inkstyle(InkStyle& inkstyle, bool reset = false);

		void set_caption(cstring text);
		void set_icon(Image* image);

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
		inline vec2 absolute_position() { resolve(); return frame().d_absolute; }
		inline vec2 derive_position(const vec2& local) { resolve(); return frame().d_absolute + local * frame().d_scale; }
		inline vec2 derive_position(const vec2& local, Widget& root) { resolve(); root.resolve(); return (frame().d_absolute + local * frame().d_scale - root.frame().d_absolute) / root.frame().d_scale; }

		// from the space of its root, or of an ancestor, to the local space of the frame
		inline vec2 local_position(const vec2& pos) { resolve(); return (pos - frame().d_absolute) / frame().d_scale; }
		inline vec2 integrate_position(const vec2& pos, Widget& root) { resolve(); root.resolve(); return (root.frame().d_absolute + pos * root.frame().d_scale - frame().d_absolute) / frame().d_scale; }

		// the scale of the frame and of its parents up to an ancestor, including it
		inline float derive_scale(Widget& root) { resolve(); root.resolve(); return frame().d_scale / root.frame().d_scale * root.frame().m_scale; }
		inline float absolute_scale() { return this->derive_scale(this->root()); }

		void clamp_to_parent();

		inline bool inside_abs(const vec2& pos) { return frame().inside(this->local_position(pos)); }

		void transfer_pixel_span(Widget& prev, Widget& next, Axis dim, float pixelSpan);

		void relayout();

		void debug_print(bool commit);

		// --- end frame ---
	};

}
