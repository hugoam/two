//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/string.h>
#include <ui/Forward.h>
#include <ui/Style/Style.h>

struct dirent;

namespace mud
{
namespace ui
{
	export_ struct FileStyles
	{
		void reset();
		Style dir; Style file;
	};

	export_ MUD_UI_EXPORT FileStyles& file_styles();

	export_ MUD_UI_EXPORT func_ Widget& dir_item(Widget& parent, const string& name);
	export_ MUD_UI_EXPORT func_ Widget& file_item(Widget& parent, const string& name);
	export_ MUD_UI_EXPORT func_ Widget& file_list(Widget& parent, string& path);

	export_ MUD_UI_EXPORT func_ Widget& file_browser(Widget& parent, string& path);

	export_ MUD_UI_EXPORT func_ Widget& dir_node(Widget& parent, const string& path, const string& name, bool collapsed);
	export_ MUD_UI_EXPORT func_ Widget& file_node(Widget& parent, const string& name);
	export_ MUD_UI_EXPORT func_ Widget& file_tree(Widget& parent, const string& path);
}
}
