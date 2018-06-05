//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Array.h>
#endif
#include <ui/Generated/Forward.h>
#include <ui/Sheet.h>

namespace mud
{
namespace ui
{
	struct DockStyles
	{
		DockStyles();
		Style docktab; Style placeholder; Style docksection; Style dockline; Style dockspace; Style docktoggle; Style dockdiv; Style docktabs; Style dockbar;
		//Style dockdiv; Style dockbox;
	};

	MUD_UI_EXPORT DockStyles& dock_styles();

	export_ MUD_UI_EXPORT Widget& dockline(Widget& parent, uint16_t index, Dim dim);
	MUD_UI_EXPORT Tabber& docksection(Widget& parent);

	export_ MUD_UI_EXPORT _func_ Dockspace& dockspace(Widget& parent, Docksystem& docksystem);
	export_ MUD_UI_EXPORT _func_ Dockbar& dockbar(Widget& parent, Docksystem& docksystem);

	export_ MUD_UI_EXPORT _func_ Widget* dockitem(Widget& parent, Docksystem& docksystem, Dock& dock);

	MUD_UI_EXPORT Widget* dockitem(Docker& docker, cstring name, array<uint16_t> dockid = {});
}
}
