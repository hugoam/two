//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
namespace ui
{
	Widget dir_item(NodeKey id, Widget parent, const string& name)
	{
		return multi_button(id, parent, file_styles().dir, { "(folder_20)" , name.c_str() });
	}

	Widget file_item(NodeKey id, Widget parent, const string& name)
	{
		return multi_button(id, parent, file_styles().file, { "(file_20)" , name.c_str() });
	}

	Widget file_list(NodeKey id, Widget parent, string& path)
	{
		Widget self = widget(id, parent, styles().wedge);//file_styles().directory);

		auto on_dir = [&](const string& dir)
		{
			if(dir == ".") return;
			Widget item = dir_item(key(), self, dir.c_str());
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
			file_item(key(), self, file.c_str());
		};

		visit_folders(path, on_dir, false);
		visit_files(path, on_file);
		return self;
	}

	Widget file_browser(NodeKey id, Widget parent, string& path)
	{
		Widget self = widget(id, parent, styles().wedge);// styles().file_browser);
		file_list(key(), self, path);
		return self;
	}

	Widget dir_node(NodeKey id, Widget parent, const string& path, const string& name, bool open)
	{
		cstring elements[] = { "(folder_20)", name.c_str() };
		TreeNode self = tree_node(id, parent, elements, false, open);
		if(!self.body) return self;

		auto on_dir = [&](const string& dir)
		{
			dir_node(key(), *self.body, path + "/" + dir, dir, false);
		};

		auto on_file = [&](const string& file)
		{
			file_node(key(), *self.body, file.c_str());
		};

		visit_folders(path, on_dir);
		visit_files(path, on_file);
		return self;
	}

	Widget file_node(NodeKey id, Widget parent, const string& name)
	{
		Widget self = tree_node(id, parent, { "(file_20)", name.c_str() }, true, false);
		return self;
	}
	
	Widget file_tree(NodeKey id, Widget parent, const string& path)
	{
		Widget self = tree(id, parent);
		dir_node(key(), self, path, path, false);
		return self;
	}
}
}
