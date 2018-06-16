//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <infra/Vector.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Frame/Layer.h>
#include <ui/Render/Renderer.h>
#include <ui/Cursor.h>
#include <ui/Controller/Controller.h>
#include <ui/UiWindow.h>
#endif

namespace mud
{
	RootSheet::RootSheet(UiWindow& window)
		: Widget()//{ params, &type<RootSheet>(), MASTER_LAYER })
		, EventDispatcher(this)
		, m_window(window)
		, m_keyboard(*this)
		, m_mouse(*this, m_keyboard)
	{
		this->init(styles().root_sheet);
		this->layer();

		//if(!params.m_parent)
			m_frame.update_style(true);
	}

	RootSheet::~RootSheet()
	{}

	void RootSheet::input_frame()
	{
		Widget* hovered = static_cast<Widget*>(m_mouse.heartbeat().m_receiver);
		if(hovered != m_hovered)
		{
			m_tooltip_clock.step();
			m_hovered = hovered;
		}

		m_drop = {};

		//ui::cursor(*this, m_mouse.m_pos, m_cursor_style ? *m_cursor_style : ui::cursor_styles().cursor);
	}

	void RootSheet::render_frame()
	{
		m_frame.relayout();
	}

	void RootSheet::clear_events()
	{
		m_mouse.m_events.clear();
		m_keyboard.m_events.clear();

		EventDispatcher::update();
	}
}
