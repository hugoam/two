//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#endif
#include <ctx/Forward.h>
#include <ctx/KeyCode.h>

namespace mud
{
	export_ enum class InputModifier : unsigned int
	{
		None = 0,
		Shift = 1 << 0,
		Ctrl = 1 << 1,
		Alt = 1 << 2,
		Any = Shift | Ctrl | Alt
	};

	export_ enum class DeviceType : unsigned int
	{
		None = 0,
		Keyboard = 1,
		Mouse = 2,
		MouseLeft = 3,
		MouseRight = 4,
		MouseMiddle = 5,
		Count = 6
	};

	export_ constexpr uint32_t device_mask(DeviceType device_type) { return (1 << uint32_t(device_type)); }

	export_ enum class DeviceMask : unsigned int
	{
		AllMouse = device_mask(DeviceType::Mouse) | device_mask(DeviceType::MouseLeft) | device_mask(DeviceType::MouseRight) | device_mask(DeviceType::MouseMiddle),
		All = device_mask(DeviceType::Keyboard) | AllMouse
	};

	export_ enum class EventType : unsigned int
	{
		None = 0,
		Heartbeat = 1,
		Moved = 2,
		Pressed = 3,
		Released = 4,
		Stroked = 5,
		DoubleStroked = 6,
		Dragged = 7,
		DraggedTarget = 8,
		DragStarted = 9,
		DragEnded = 10,
		Dropped = 11,
		Count = 12
	};

	export_ struct MUD_CTX_EXPORT InputEvent
	{
		DeviceType m_deviceType = DeviceType::None;
		EventType m_eventType = EventType::None;
		ControlNode* m_receiver = nullptr;
		ControlNode* m_consumer = nullptr;
		bool m_abort = false;
		InputModifier m_modifiers = InputModifier::None;
		int m_key = -1;

		InputEvent() {}
		InputEvent(DeviceType deviceType, EventType eventType, InputModifier modifiers = InputModifier::None) : m_deviceType(deviceType), m_eventType(eventType), m_modifiers(modifiers) {}
		virtual ~InputEvent() {}

		InputEvent& consume(ControlNode& consumer) { m_consumer = &consumer; return *this; }
		operator bool() { return m_deviceType != DeviceType::None && m_consumer == nullptr; }

		virtual void dispatch(Mouse& mouse, Keyboard& keyboard) { UNUSED(mouse); UNUSED(keyboard); }
	};

	export_ struct MUD_CTX_EXPORT MouseEvent : public InputEvent
	{
		vec2 m_pos = { 0.f, 0.f };
		vec2 m_relative = { 0.f, 0.f };
		vec2 m_delta = { 0.f, 0.f };
		float m_deltaZ = 0.f;
		vec2 m_pressed = { 0.f, 0.f };
		ControlNode* m_target = nullptr;

		MouseButtonCode m_button = NO_BUTTON;

		MouseEvent() : InputEvent() {}
		MouseEvent(DeviceType deviceType, EventType eventType, vec2 pos, InputModifier modifiers = InputModifier::None)
			: InputEvent(deviceType, eventType, modifiers), m_pos(pos)
		{
			if(deviceType == DeviceType::MouseLeft)
				m_button = LEFT_BUTTON;
			else if(deviceType == DeviceType::MouseRight)
				m_button = RIGHT_BUTTON;
			else if(deviceType == DeviceType::MouseMiddle)
				m_button = MIDDLE_BUTTON;
		}

		MouseEvent(DeviceType deviceType, EventType eventType, MouseEvent& source)
			: MouseEvent(deviceType, eventType, source.m_pos, source.m_modifiers)
		{
			m_relative = source.m_relative; m_delta = source.m_delta; m_pressed = source.m_pressed;
		}

		MouseEvent& consume(ControlNode& consumer) { m_consumer = &consumer; return *this; }
	};

	export_ struct MUD_CTX_EXPORT KeyEvent : public InputEvent
	{
		Key m_code;
		char m_char;

		KeyEvent() : InputEvent() {}
		KeyEvent(DeviceType deviceType, EventType eventType, Key code, char c, InputModifier modifiers)
			: InputEvent(deviceType, eventType, modifiers), m_code(code), m_char(c)
		{
			m_key = int(code);
		}
	};
}
