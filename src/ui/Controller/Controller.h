//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>

namespace two
{
	export_ struct TWO_UI_EXPORT KeyCombo
	{
		KeyCombo(Key key) : m_modifier(InputMod::Any), m_key(key) {}
		KeyCombo(InputMod modifier, Key key) : m_modifier(modifier), m_key(key) {}
		InputMod m_modifier;
		Key m_key;
		uint32_t value() const { return uint32_t(m_modifier) << 24 | uint32_t(m_key); }
		explicit operator uint32_t() const { return value(); }
	};

	inline size_t hash(const KeyCombo& value)
	{
		return value.value();
	}

	inline bool operator<(const KeyCombo& lhs, const KeyCombo& rhs) { return lhs.value() < rhs.value(); }
	inline bool operator==(const KeyCombo& lhs, const KeyCombo& rhs) { return lhs.value() == rhs.value(); }

	using KeyHandler = void(*)();

	export_ class TWO_UI_EXPORT EventDispatch
	{
	public:
		EventDispatch();

		virtual void process(Widget& widget);
		
		//EventMap<KeyHandler> m_handlers;

		map<KeyCombo, KeyHandler> m_key_down_handlers;
		map<KeyCombo, KeyHandler> m_key_up_handlers;
	};
}
