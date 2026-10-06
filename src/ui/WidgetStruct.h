//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Frame/Frame.h>
#include <ui/Frame/Layer.h>
#include <ui/Widget.h>

namespace two
{
	using FrameFilter = bool(*)(Frame&);

	// the custom drawing of a widget, in place of the drawing of its frame: a state of its node
	export_ struct CustomRender
	{
		using Draw = function<void(Widget&, const vec4&, Vg&)>;
		Draw m_draw;
	};

	// the modality of a widget, a state of its node: the widget it took its modality from, and the widget it gave it to for the devices of the mask
	export_ struct ModalControl
	{
		ControlId m_parent;
		ControlId m_modal;
		uint32_t m_mask = 0;
	};

	// the state of a widget, by node index next to its frame: its WidgetState flags, and its switch, bits it keeps for its user from one frame to the next
	export_ struct refl_ TWO_UI_EXPORT WidgetData
	{
		attr_ WidgetState m_state = CREATED;
		attr_ uint32_t m_switch = 0;
	};

#ifndef _MSC_VER
	extern template class PooledNode<Widget>;
#endif

	export_ class refl_ TWO_UI_EXPORT Widget : public PooledNode<Widget>
	{
	public:
		Widget(PooledGraph<Widget>& graph);
		Widget(Widget* parent);

		// the bookkeeping of the widget as a node, called by the graph
		// a top node changed parent: its frame and its layers follow it
		void reparent(Widget* old);
		// the node is going away, its states are still there: it lets go of what refers to it
		void release();

		meth_ inline bool focused() { return (data().m_state & FOCUSED) != 0; }
		meth_ inline bool hovered() { return (data().m_state & HOVERED) != 0; }
		meth_ inline bool pressed() { return (data().m_state & PRESSED) != 0; }
		meth_ inline bool activated() { return (data().m_state & ACTIVATED) != 0; }
		meth_ inline bool active() { return (data().m_state & ACTIVE) != 0; }
		meth_ inline bool selected() { return (data().m_state & SELECTED) != 0; }
		meth_ inline bool modal() { return (data().m_state & FOCUSED) != 0; }
		meth_ inline bool closed() { return (data().m_state & CLOSED) != 0; }
		meth_ inline bool open() { return (data().m_state & OPEN) != 0; }

		meth_ UiWindow& ui_window();
		meth_ Ui& ui();
		meth_ Widget& parent_modal();

		meth_ void clear();

		void set_content(cstring content);

		meth_ void toggle_state(WidgetState state);

		meth_ inline void disable_state(WidgetState state) { if(data().m_state & state) this->toggle_state(state); }
		meth_ inline void set_state(WidgetState state, bool enabled) { enabled ? enable_state(state) : disable_state(state); }
		meth_ inline void enable_state(WidgetState state) { if(!(data().m_state & state)) this->toggle_state(state); }

		// the open state is not skinned: it doesn't update the style
		meth_ inline void set_open(bool open) { data().m_state = WidgetState(open ? (data().m_state | OPEN) : (data().m_state & ~OPEN)); }

		meth_ inline void clear_focus() { this->parent_modal().set_modal(nullptr, device_mask(DeviceType::Keyboard)); }
		meth_ inline void take_focus() { if(!this->modal()) this->take_modal(device_mask(DeviceType::Keyboard)); }
		meth_ inline void yield_focus() { this->yield_modal(); }

		meth_ inline void take_modal(uint32_t device_filter = uint32_t(DeviceMask::All)) { this->parent_modal().set_modal(this, device_filter); }
		meth_ void yield_modal();

		void set_modal(Widget* widget, uint32_t device_filter);

		Widget* pinpoint(vec2 pos);
		Widget* pinpoint(vec2 pos, const FrameFilter& filter);

		// the widget as a node of the tree the ui dispatches the events in
		inline ControlId control_id() const { return ControlId(m_index); }

		meth_ KeyEvent key_event(Key code, EventType event_type, InputMod modifier = InputMod::Any);
		meth_ KeyEvent key_stroke(Key code, InputMod modifier = InputMod::Any) { return key_event(code, EventType::Stroked, modifier); }
		meth_ KeyEvent char_stroke(Key code, InputMod modifier = InputMod::Any) { return key_event(translate(code), EventType::Stroked, modifier); }

		meth_ MouseEvent mouse_event(DeviceType device, EventType event_type, InputMod modifier = InputMod::None, bool consume = true);
		
		void transform_event(InputEvent& event);

		// the frame of the widget, its data by node index in the frames of the ui
		attr_ inline Frame& frame();
		inline FrameCache& cache();
		attr_ inline WidgetData& data();

		// the custom drawing of the widget, created on first use
		inline CustomRender::Draw& custom_draw() { return this->state<CustomRender>().m_draw; }

		inline bool once() { if((data().m_state & CREATED) != 0) { disable_state(CREATED); return true; } return false; }
		// a widget is initialized when it's declared the first time, right after the graph created its node: its parent is laid out again with it
		inline Widget& init(Style& style, bool open = false, Axis length = Axis::None, v2<uint> index = { 0, 0 })
		{
			if(!frame().d_style)
			{
				if(Widget* parent = this->parent())
					parent->mark_dirty(DIRTY_LAYOUT);
				this->set_style(style, length, index);
				this->set_open(open);
			}
			return *this;
		}

		// --- frame ---
		// the frame of the widget: its layout and its drawing, on the data of frame(), and of the frames of its parents (Frame.cpp)

		void set_style(Style& style, Axis length = Axis::None, v2<uint> index = { 0, 0 });

		// the layers: a widget with a layer, a state of its node, is drawn in it with its descendants (Layer.cpp)

		// gives the widget its own layer, drawn in the layer of its parent
		Widget& layer();
		// the widget whose layer the frame is drawn in: itself, or the one of its parent
		Widget& layer_widget();
		Layer& draw_layer();

		void add_sublayer(Widget& widget, Layer& sublayer);
		void remove_sublayer(Widget& widget, Layer& sublayer);
		void reindex_layers();
		void reorder_layers();
		void move_layer_to_top();

		// visits the widgets with a layer, from this one, each before the layers drawn in its layer
		template <class T_Visitor>
		inline void visit_layers(const T_Visitor& visitor)
		{
			Layer& layer = *this->find_state<Layer>();
			visitor(*this, layer);
			for(uint32_t node : layer.d_sublayers)
				m_graph->node(node).visit_layers(visitor);
		}

		// the layer of the widget leaves the layer it's drawn in
		void release_layer();

		void mark_dirty(DirtyLayout dirty);

		void update_style(bool reset = false);
		void update_state(WidgetState state);
		void update_inkstyle(InkStyle& inkstyle, bool reset = false);

		void set_caption(cstring text);
		void set_icon(Image* image);
		void size_caption(const string& caption);

		// whether the frame draws content of its own, which it's sized by: a caption, an icon or a text
		bool has_content();

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
		inline vec2 absolute_position() { resolve(); return cache().d_absolute; }
		inline vec2 derive_position(const vec2& local) { resolve(); return cache().d_absolute + local * cache().d_scale; }
		inline vec2 derive_position(const vec2& local, Widget& root) { resolve(); root.resolve(); return (cache().d_absolute + local * cache().d_scale - root.cache().d_absolute) / root.cache().d_scale; }

		// from the space of its root, or of an ancestor, to the local space of the frame
		inline vec2 local_position(const vec2& pos) { resolve(); return (pos - cache().d_absolute) / cache().d_scale; }
		inline vec2 integrate_position(const vec2& pos, Widget& root) { resolve(); root.resolve(); return (root.cache().d_absolute + pos * root.cache().d_scale - cache().d_absolute) / cache().d_scale; }

		// the scale of the frame and of its parents up to an ancestor, including it
		inline float derive_scale(Widget& root) { resolve(); root.resolve(); return cache().d_scale / root.cache().d_scale * root.frame().m_scale; }
		inline float absolute_scale() { return this->derive_scale(this->root()); }

		void clamp_to_parent();

		inline bool inside_abs(const vec2& pos) { return frame().inside(this->local_position(pos)); }

		void transfer_pixel_span(Widget& prev, Widget& next, Axis dim, float pixelSpan);

		void relayout();

		void debug_print(bool commit);

		// --- end frame ---
	};

	// a handle to a widget, kept from one frame to the next: the graph of the widget, and its node index packed with the generation of the index
	// it resolves to the widget while it's there, and to nothing once it's gone, even if another widget took its index
	export_ struct refl_ struct_ TWO_UI_EXPORT WidgetHandle
	{
		WidgetHandle() {}
		WidgetHandle(Widget* widget) : m_graph(widget ? widget->m_graph : nullptr), m_handle(widget ? widget->m_graph->handle(widget->m_index) : 0) {}
		WidgetHandle(Widget& widget) : WidgetHandle(&widget) {}

		PooledGraph<Widget>* m_graph = nullptr;
		uint32_t m_handle = 0;

		// the widget, or null if it's gone
		inline Widget* get() const { return m_graph ? m_graph->resolve(m_handle) : nullptr; }

		attr_ inline Widget& widget() const { return *this->get(); }

		inline Widget* operator->() const { return this->get(); }
		inline Widget& operator*() const { return *this->get(); }
		explicit operator bool() const { return this->get() != nullptr; }
		bool operator==(const WidgetHandle& other) const { return m_handle == other.m_handle && m_graph == other.m_graph; }
	};
}
