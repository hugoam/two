//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	Ui::Ui(UiWindow& window)
		: Widget(static_cast<PooledGraph<Widget>&>(*this))
		, EventDispatcher()
		, m_frames(this->add_array<Frame>())
		, m_caches(this->add_array<FrameCache>())
		, m_window(window)
		, m_keyboard(*this)
		, m_mouse(*this, m_keyboard)
	{
		this->init(styles().ui);
		this->layer();

		//if(!params.m_parent)
			this->update_style(true);
	}

	// the widgets go before the dispatcher and the devices they refer to when they're released
	Ui::~Ui()
	{
		Widget::clear();
	}

	Widget& Ui::begin()
	{
		return Widget::begin();
	}

	void Ui::input_frame()
	{
		Widget* hovered = &this->control(m_mouse.heartbeat().m_receiver);
		if(hovered != m_hovered)
		{
			m_tooltip_clock.step();
			m_hovered = hovered;
		}

		m_drop = {};
	}

	void Ui::render_frame()
	{
		if(!m_window.m_context.m_mouse_lock)
		{
			Widget& cursor = ui::cursor(key(), *this, m_mouse.m_pos, m_cursor_style ? *m_cursor_style : ui::cursor_styles().cursor);
			cursor.draw_layer().setForceRedraw();
		}

		m_cursor_style = &ui::cursor_styles().cursor;

		this->relayout();
	}

	ControlId Ui::route(InputEvent& event)
	{
		static_assert(ControlId::none == PooledGraph<Widget>::none);

		Widget* widget = this;
		while(true)
		{
			widget->transform_event(event);

			ModalControl* control = widget->find_state<ModalControl>();
			if(control && control->m_modal && (control->m_mask & device_mask(event.m_deviceType)) != 0)
			{
				widget = &this->control(control->m_modal);
				continue;
			}

			if(event.m_deviceType >= DeviceType::Mouse)
			{
				Widget* pinned = widget->pinpoint(static_cast<MouseEvent&>(event).m_relative);
				if(pinned && pinned != widget)
				{
					widget = pinned;
					continue;
				}
			}

			return widget->control_id();
		}
	}

	void Ui::receive(InputEvent& event, ControlId receiver)
	{
		if(event.m_consumer) return;
		this->control(receiver).transform_event(event);
	}

	void Ui::clear_events()
	{
		m_mouse.m_events.clear();
		m_keyboard.m_events.clear();

		EventDispatcher::update();
	}

	void Ui::reset_styles()
	{
		Widget::visit([](Widget& widget, bool& visit)
		{
			UNUSED(visit);
			widget.update_style(true);
		});
	}
}
