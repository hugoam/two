//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <obj/Util/Timer.h>
#include <ui/Generated/Forward.h>
#include <ui/Structs/Widget.h>
#include <ctx/InputDispatcher.h>
#include <ctx/InputDevice.h>

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

	class _refl_ MUD_UI_EXPORT RootSheet : public Widget, public EventDispatcher
	{
	public:
		RootSheet(UiWindow& window);
		~RootSheet();

		void next_frame(size_t tick, size_t delta);

		void clear_events();

		void destroy(Widget& widget);

	public:
		UiWindow& m_window;
		Keyboard m_keyboard;
		Mouse m_mouse;

		Style* m_cursor_style = nullptr;
		Widget* m_hovered = nullptr;
		DropAction m_drop = {};
		Clock m_tooltip_clock;

		object_ptr<UiTarget> m_target;
	};
}
