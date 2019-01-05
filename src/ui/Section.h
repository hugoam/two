//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Strung.h>
#include <ui/Structs/Widget.h>
#endif
#include <ui/Forward.h>

namespace mud
{
	using Callback = std::function<void()>;

	export_ struct MUD_UI_EXPORT SectionAction
	{
		string m_name;
		Callback m_action;
	};

	using ActionList = std::vector<SectionAction>;

	export_ struct MUD_UI_EXPORT Section : public Widget
	{
		Section(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_toolbar = nullptr;
	};

	export_ MUD_UI_EXPORT Section& section(Widget& parent, cstring name, const ActionList& actions = {}, bool no_toolbar = false);
}
