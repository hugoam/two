//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <tree/Node.h>
#include <infra/Array.h>
#include <ctx/ControlNode.h>
#include <ctx/InputEvent.h>
#endif
#include <ui/Forward.h>
#include <ui/Frame/Frame.h>
#include <ui/Widget.h>

#ifndef MUD_CPP_20
#include <functional>
#endif

namespace mud
{
	using CustomRenderer = std::function<void(const Frame&, const vec4&, Vg&)>;

	using FrameFilter = std::function<bool(Frame&)>;

	export_ class refl_ MUD_UI_EXPORT Widget : public Graph<Widget>, public ControlNode
	{
	public:
		Widget();
		Widget(Widget* parent, void* identity);
		~Widget();

		attr_ bool focused() { return (m_state & FOCUSED) != 0; }
		attr_ bool hovered() { return (m_state & HOVERED) != 0; }
		attr_ bool pressed() { return (m_state & PRESSED) != 0; }
		attr_ bool activated() { return (m_state & ACTIVATED) != 0; }
		attr_ bool selected() { return (m_state & SELECTED) != 0; }
		attr_ bool modal() { return (m_state & FOCUSED) != 0; }
		attr_ bool closed() { return (m_state & CLOSED) != 0; }

		meth_ Widget& begin();

		UiWindow& ui_window();
		RootSheet& root_sheet();
		Widget& parent_modal();

		void set_content(cstring content);

		void toggle_state(WidgetState state);

		void disable_state(WidgetState state) { if(m_state & state) this->toggle_state(state); }
		void set_state(WidgetState state, bool enabled) { enabled ? enable_state(state) : disable_state(state); }
		void enable_state(WidgetState state) { if(!(m_state & state)) this->toggle_state(state); }

		void clear_focus() { this->parent_modal().set_modal(nullptr, device_mask(DeviceType::Keyboard)); }
		void take_focus() { this->take_modal(device_mask(DeviceType::Keyboard)); }
		void yield_focus() { this->yield_modal(); }

		void take_modal(uint32_t device_filter = uint32_t(DeviceMask::All)) { this->parent_modal().set_modal(this, device_filter); }
		void yield_modal() { this->parent_modal().set_modal(nullptr, 0); }

		void set_modal(Widget* widget, uint32_t device_filter);

		Widget* pinpoint(vec2 pos);
		Widget* pinpoint(vec2 pos, const FrameFilter& filter);

		inline bool fits_modifier(InputModifier modifier, InputModifier mask) { return mask == InputModifier::Any || modifier == mask; }

		KeyEvent key_event(KeyCode code, EventType event_type, InputModifier modifier = InputModifier::Any);
		KeyEvent key_event(KeyCode code, InputModifier modifier = InputModifier::Any) { return key_event(code, EventType::Stroked, modifier); }

		MouseEvent mouse_event(DeviceType device, EventType event_type, InputModifier modifier = InputModifier::None, bool consume = true);
		
		void transform_event(InputEvent& event);
		ControlNode* control_event(InputEvent& event);
		void receive_event(InputEvent& event);
		ControlNode* propagate_event(InputEvent& event);

		attr_ Frame m_frame;
		WidgetState m_state = CREATED;
		uint32_t m_switch = 0;
		attr_ size_t m_index = 0;
		attr_ bool m_open = false;
		attr_ Widget* m_body = nullptr;
		CustomRenderer m_custom_draw = {};

		Widget& layer();

		bool once() { if((m_state & CREATED) != 0) { disable_state(CREATED); return true; } return false; }
		Widget& init(Style& style, bool open = false, Dim length = DIM_NONE, Dim2<size_t> index = { 0, 0 }) { if(!m_frame.d_style) { m_frame.solver(style, length, index); m_open = open; } return *this; }
	};

namespace ui
{
	export_ template <class T>
	inline T& twidget(Widget& parent, Style& style, bool open = false, Dim length = DIM_NONE, Dim2<size_t> index = { 0, 0 })
	{
		T& self = parent.sub<T>(&style); self.init(style, open, length, index); return self;
	}
}
}
