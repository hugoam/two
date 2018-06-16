//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Ref.h>
#include <obj/Unique.h>
#include <math/Timer.h>
#include <ctx/InputDispatcher.h>
#include <ctx/InputDevice.h>
#endif
#include <ui/Forward.h>
#include <ui/Structs/Widget.h>

namespace mud
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

	export_ class refl_ MUD_UI_EXPORT RootSheet : public Widget, public EventDispatcher
	{
	public:
		RootSheet(UiWindow& window);
		~RootSheet();

		void input_frame();
		void render_frame();

		void clear_events();

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
