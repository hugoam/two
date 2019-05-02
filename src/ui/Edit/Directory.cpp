//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#include <infra/File.h>
#include <ui/Edit/Directory.h>
#include <ui/Button.h>
#include <ui/WidgetStruct.h>
#include <ui/ContainerStruct.h>
#include <ui/Style/Styles.h>
#endif

namespace two
{
namespace ui
{
	Widget& dir_item(Widget& parent, const string& name)
	{
		return multi_button(parent, file_styles().dir, { "(folder_20)" , name.c_str() });
	}

	Widget& file_item(Widget& parent, const string& name)
	{
		return multi_button(parent, file_styles().file, { "(file_20)" , name.c_str() });
	}

	Widget& file_list(Widget& parent, string& path)
	{
		Widget& self = widget(parent, styles().wedge);//file_styles().directory);

		auto on_dir = [&](const string& dir)
		{
			if(dir == ".") return;
			Widget& item = dir_item(self, dir.c_str());
			if(item.activated())
			{
				if(dir == "..")
					path = path.substr(0, path.rfind("/"));
				else
					path = path + "/" + dir;
			}
		};

		auto on_file = [&](const string& file)
		{
			file_item(self, file.c_str());
		};

		visit_folders(path, on_dir, false);
		visit_files(path, on_file);
		return self;
	}

	Widget& file_browser(Widget& parent, string& path)
	{
		Widget& self = widget(parent, styles().wedge);// styles().file_browser);
		file_list(self, path);
		return self;
	}

	Widget& dir_node(Widget& parent, const string& path, const string& name, bool open)
	{
		cstring elements[] = { "(folder_20)", name.c_str() };
		Widget& self = tree_node(parent, elements, false, open);
		if(!self.m_body) return self;

		auto on_dir = [&](const string& dir)
		{
			dir_node(*self.m_body, path + "/" + dir, dir, false);
		};

		auto on_file = [&](const string& file)
		{
			file_node(*self.m_body, file.c_str());
		};

		visit_folders(path, on_dir);
		visit_files(path, on_file);
		return self;
	}

	Widget& file_node(Widget& parent, const string& name)
	{
		Widget& self = tree_node(parent, { "(file_20)", name.c_str() }, true, false);
		return self;
	}
	
	Widget& file_tree(Widget& parent, const string& path)
	{
		Widget& self = tree(parent);
		dir_node(self, path, path, false);
		return self;
	}
}
}
