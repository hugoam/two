//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/WidgetStruct.h>

namespace two
{
	enum class DropState : unsigned int
	{
		None,
		Preview,
		Done
	};

	struct DropAction
	{
		DropAction() {}
		DropAction(WidgetHandle target, Ref object, DropState state) : m_target(target), m_object(object), m_state(state) {}
		WidgetHandle m_target = nullptr;
		Ref m_object = {};
		DropState m_state = DropState::None;
	};

	export_ class refl_ TWO_UI_EXPORT Ui : public PooledGraph<Widget>, public Widget, public EventDispatcher
	{
	public:
		Ui(UiWindow& window);
		~Ui();

		meth_ Widget& begin();

		void input_frame();
		void render_frame();

		void clear_events();

		meth_ void reset_styles();

	public:
		// the frames of the widgets, by node index: declared first, the root's frame is used from the constructor
		TNodeArray<Frame>& m_frames;

		UiWindow& m_window;
		Keyboard m_keyboard;
		Mouse m_mouse;

		Style* m_cursor_style = nullptr;
		WidgetHandle m_hovered = nullptr;
		DropAction m_drop = {};
		Clock m_tooltip_clock;
	};

	inline Frame& Widget::frame() { return static_cast<Ui&>(*m_graph).m_frames[m_index]; }
}
