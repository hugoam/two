//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Var.h>
#include <ui/Generated/Forward.h>
#include <ui/Style/Style.h>

#ifndef MUD_CPP_20
#include <string>
#include <map>
#include <vector>
#endif

namespace mud
{
	using string = std::string;

	export_ class MUD_UI_EXPORT Options
	{
	public:
		std::vector<Var> m_fields;

		void set(size_t index, const Var& value);
		void merge(const Options& other);
		void apply(Ref object);
	};

	using StyleMap = std::map<string, Options>;

	export_ class _refl_ MUD_UI_EXPORT Styler
	{
	public:
		Styler(UiWindow& ui_window);

		UiWindow& m_uiWindow;
		std::map<string, Options> m_layout_definitions;
		std::map<string, Options> m_skin_definitions;

		void init();
		void clear();
		void setup();

		void load(Style& style, StyleMap& layout_defs, StyleMap& skin_defs);
		void define(Style& style, StyleMap& layout_defs, StyleMap& skin_defs);

		static std::map<string, Style*> s_styles;
	};
}
