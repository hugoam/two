//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Style/Style.h>

struct dirent;

namespace two
{
namespace ui
{
	export_ struct FileStyles
	{
		void reset();
		Style dir; Style file;
	};

	export_ TWO_UI_EXPORT FileStyles& file_styles();

	export_ TWO_UI_EXPORT func_ Widget& dir_item(Widget& parent, const string& name);
	export_ TWO_UI_EXPORT func_ Widget& file_item(Widget& parent, const string& name);
	export_ TWO_UI_EXPORT func_ Widget& file_list(Widget& parent, string& path);

	export_ TWO_UI_EXPORT func_ Widget& file_browser(Widget& parent, string& path);

	export_ TWO_UI_EXPORT func_ Widget& dir_node(Widget& parent, const string& path, const string& name, bool collapsed);
	export_ TWO_UI_EXPORT func_ Widget& file_node(Widget& parent, const string& name);
	export_ TWO_UI_EXPORT func_ Widget& file_tree(Widget& parent, const string& path);
}
}
