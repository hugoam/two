//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <ui/Structs/Widget.h>
#endif
#include <ui/Forward.h>

namespace mud
{
	export_ struct MUD_UI_EXPORT Section : public Widget
	{
		Section(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_toolbar = nullptr;
	};

	export_ MUD_UI_EXPORT Section& section(Widget& parent, cstring name, bool no_toolbar = false);
	export_ MUD_UI_EXPORT bool section_action(Section& parent, cstring name);
}
