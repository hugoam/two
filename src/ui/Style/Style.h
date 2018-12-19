//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>

#ifndef MUD_CPP_20
#include <memory>
#endif

namespace mud
{
	using cstring = const char*;
	using std::unique_ptr;

	using LayoutDef = void(*)(Layout&);
	using InkStyleDef = void(*)(InkStyle&);
	using StyleDef = void(*)(Style&);

	export_ class refl_ MUD_UI_EXPORT Style
	{
	public:
		Style(cstring name, Style* base, LayoutDef layout, InkStyleDef skin = nullptr, StyleDef style = nullptr);
		Style(cstring name, Style& base, LayoutDef layout, InkStyleDef skin = nullptr, StyleDef style = nullptr) : Style(name, &base, layout, skin, style) {}
		~Style();

		Style(const Style& other);
		Style& operator=(const Style& other);
		
		void prepare();

		InkStyle& state_skin(WidgetState state);
		InkStyle& decline_skin(WidgetState state);

		attr_ Style* m_base;
		attr_ cstring name();
		attr_ Layout& layout();
		attr_ InkStyle& skin();
		
		struct Impl;
		unique_ptr<Impl> m_impl;
	};

	export_ MUD_UI_EXPORT void style_minimal(UiWindow& ui_window);
}
