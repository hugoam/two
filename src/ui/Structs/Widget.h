//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/function.h>
#include <tree/Node.h>
#ifdef _MSC_VER
#include <tree/Node.hpp>
#endif
#include <infra/Array.h>
#include <ctx/ControlNode.h>
#include <ctx/InputEvent.h>
#endif
#include <ui/Forward.h>
#include <ui/Frame/Frame.h>
#include <ui/Widget.h>

namespace mud
{
	using FrameFilter = bool(*)(Frame&);

#ifndef _MSC_VER
	export_ extern template class Graph<Widget>;
#endif

	export_ class refl_ MUD_UI_EXPORT Widget : public Graph<Widget>, public ControlNode
	{
	public:
		Widget();
		Widget(Widget* parent, void* identity);
		~Widget();

		meth_ bool focused() { return (m_state & FOCUSED) != 0; }
		meth_ bool hovered() { return (m_state & HOVERED) != 0; }
		meth_ bool pressed() { return (m_state & PRESSED) != 0; }
		meth_ bool activated() { return (m_state & ACTIVATED) != 0; }
		meth_ bool selected() { return (m_state & SELECTED) != 0; }
		meth_ bool modal() { return (m_state & FOCUSED) != 0; }
		meth_ bool closed() { return (m_state & CLOSED) != 0; }

		meth_ UiWindow& ui_window();
		meth_ Ui& ui();
		meth_ Widget& parent_modal();

		void set_content(cstring content);

		meth_ void toggle_state(WidgetState state);

		meth_ void disable_state(WidgetState state) { if (m_state & state) this->toggle_state(state); }
		meth_ void set_state(WidgetState state, bool enabled) { enabled ? enable_state(state) : disable_state(state); }
		meth_ void enable_state(WidgetState state) { if(!(m_state & state)) this->toggle_state(state); }

		meth_ void clear_focus() { this->parent_modal().set_modal(nullptr, device_mask(DeviceType::Keyboard)); }
		meth_ void take_focus() { if(!this->modal()) this->take_modal(device_mask(DeviceType::Keyboard)); }
		meth_ void yield_focus() { this->yield_modal(); }

		meth_ void take_modal(uint32_t device_filter = uint32_t(DeviceMask::All)) { this->parent_modal().set_modal(this, device_filter); }
		meth_ void yield_modal() { this->parent_modal().set_modal(nullptr, 0); }

		void set_modal(Widget* widget, uint32_t device_filter);

		Widget* pinpoint(vec2 pos);
		Widget* pinpoint(vec2 pos, const FrameFilter& filter);

		inline bool fits_modifier(InputMod modifier, InputMod mask) { return mask == InputMod::Any || modifier == mask; }

		meth_ KeyEvent key_event(Key code, EventType event_type, InputMod modifier = InputMod::Any);
		meth_ KeyEvent key_stroke(Key code, InputMod modifier = InputMod::Any) { return key_event(code, EventType::Stroked, modifier); }
		meth_ KeyEvent char_stroke(Key code, InputMod modifier = InputMod::Any) { return key_event(translate(code), EventType::Stroked, modifier); }

		meth_ MouseEvent mouse_event(DeviceType device, EventType event_type, InputMod modifier = InputMod::None, bool consume = true);
		
		void transform_event(InputEvent& event);
		ControlNode* control_event(InputEvent& event);
		void receive_event(InputEvent& event);
		ControlNode* propagate_event(InputEvent& event);

		attr_ Frame m_frame;
		attr_ WidgetState m_state = CREATED;
		attr_ uint32_t m_switch = 0;
		attr_ size_t m_index = 0;
		attr_ bool m_open = false;
		attr_ Widget* m_body = nullptr;

		using CustomRender = function<void(const Frame&, const vec4&, Vg&)>;
		CustomRender m_custom_draw;

		Widget& layer();

		bool once() { if((m_state & CREATED) != 0) { disable_state(CREATED); return true; } return false; }
		Widget& init(Style& style, bool open = false, Dim length = DIM_NONE, Dim2<size_t> index = { 0, 0 }) { if(!m_frame.d_style) { m_frame.solver(style, length, index); m_open = open; } return *this; }
	};

namespace ui
{
	export_ template <class T>
	inline T& twidget(Widget& parent, Style& style, bool open = false, Dim length = DIM_NONE, Dim2<size_t> index = { 0, 0 })
	{
		T& self = parent.subi<T>(&style); self.init(style, open, length, index); return self;
	}
}
}
