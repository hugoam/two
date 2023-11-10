//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <type/Ref.h>
#include <type/Unique.h>
#include <math/Timer.h>
#include <ctx/InputDispatcher.h>
#include <ctx/InputDevice.h>
#endif
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
		DropAction(Widget* target, Ref object, DropState state) : m_target(target), m_object(object), m_state(state) {}
		Widget* m_target = nullptr;
		Ref m_object = {};
		DropState m_state = DropState::None;
	};

	export_ class refl_ TWO_UI_EXPORT Ui : public Widget, public EventDispatcher
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
		UiWindow& m_window;
		Keyboard m_keyboard;
		Mouse m_mouse;

		Style* m_cursor_style = nullptr;
		Widget* m_hovered = nullptr;
		DropAction m_drop = {};
		Clock m_tooltip_clock;
	};
}
