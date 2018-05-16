//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Util/Timer.h>
#include <ui/Generated/Forward.h>
#include <ui/Structs/Widget.h>
#include <ctx/InputDispatcher.h>
#include <ctx/InputDevice.h>

namespace mud
{
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
		Clock m_tooltip_clock;

		object_ptr<UiRenderTarget> m_target;
	};
}
