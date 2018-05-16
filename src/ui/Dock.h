//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
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

	MUD_UI_EXPORT Widget& dockline(Widget& parent, size_t index, Dim dim);
	MUD_UI_EXPORT Tabber& docksection(Widget& parent);

	MUD_UI_EXPORT _func_ Dockspace& dockspace(Widget& parent, Docksystem& docksystem);
	MUD_UI_EXPORT _func_ Dockbar& dockbar(Widget& parent, Docksystem& docksystem);

	MUD_UI_EXPORT _func_ Widget* dockitem(Widget& parent, Docksystem& docksystem, Dock& dock);

	MUD_UI_EXPORT Widget* dockitem(Docker& docker, cstring name, array<size_t> dockid = {});
}
}
