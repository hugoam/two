//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <ui/Style/Style.h>

#include <string>

struct dirent;

namespace mud
{
	using string = std::string;

namespace ui
{
	struct FileStyles
	{
		FileStyles();
		Style dir; Style file;
	};

	MUD_UI_EXPORT FileStyles& file_styles();

	MUD_UI_EXPORT _func_ Widget& dir_item(Widget& parent, cstring name);
	MUD_UI_EXPORT _func_ Widget& file_item(Widget& parent, cstring name);
	MUD_UI_EXPORT _func_ Widget& file_list(Widget& parent, string& path);

	MUD_UI_EXPORT _func_ Widget& file_browser(Widget& parent, string& path);

	MUD_UI_EXPORT _func_ Widget& dir_node(Widget& parent, cstring path, cstring name, bool collapsed);
	MUD_UI_EXPORT _func_ Widget& file_node(Widget& parent, cstring name);
	MUD_UI_EXPORT _func_ Widget& file_tree(Widget& parent, cstring path);
}
}
