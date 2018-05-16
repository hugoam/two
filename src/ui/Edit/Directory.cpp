//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui/Edit/Directory.h>
#include <ui/Button.h>
#include <ui/Structs/Widget.h>
#include <ui/Structs/Container.h>
#include <ui/Style/Styles.h>

#include <obj/Vector.h>

#include <functional>

#include <dirent.h>

namespace mud
{
namespace ui
{
	Widget& dir_item(Widget& parent, cstring name)
	{
		carray<cstring, 2> elements = { "(folder_20)" , name };
		return multi_button(parent, file_styles().dir, elements);
	}

	Widget& file_item(Widget& parent, cstring name)
	{
		carray<cstring, 2> elements = { "(file_20)" , name };
		return multi_button(parent, file_styles().file, elements);
	}

	void iterate_directory(const string& path, std::function<void(cstring)> on_dir, std::function<void(cstring)> on_file)
	{
		DIR* dir = opendir(path.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR)
				on_dir(ent->d_name);

		rewinddir(dir);

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
				on_file(ent->d_name);

		closedir(dir);
	}

	Widget& file_list(Widget& parent, string& path)
	{
		Widget& self = widget(parent, styles().wedge);//file_styles().directory);
		auto on_dir = [&](cstring dir)
		{
			if(string(dir) == ".") return;
			Widget& item = dir_item(self, dir);
			if(item.activated())
			{
				if(string(dir) == "..")
					path = path.substr(0, path.rfind("/"));
				else
					path = path + "/" + dir;
			}
		};

		auto on_file = [&](cstring file)
		{
			file_item(self, file);
		};

		iterate_directory(path, on_dir, on_file);
		return self;
	}

	Widget& file_browser(Widget& parent, string& path)
	{
		Widget& self = widget(parent, styles().wedge);// styles().file_browser);
		file_list(self, path);
		return self;
	}

	Widget& dir_node(Widget& parent, cstring path, cstring name, bool open)
	{
		carray<cstring, 2> elements = { "(folder_20)", name };
		Widget& self = tree_node(parent, elements, false, open);
		if(!self.m_body) return self;

		auto on_dir = [&](cstring dir)
		{
			if(string(dir) == "." || string(dir) == "..") return;
			dir_node(*self.m_body, (string(path) + "/" + dir).c_str(), dir, false);
		};

		auto on_file = [&](cstring file)
		{
			file_node(*self.m_body, file);
		};

		iterate_directory(path, on_dir, on_file);
		return self;
	}

	Widget& file_node(Widget& parent, cstring name)
	{
		carray<cstring, 2> elements = { "(file_20)", name };
		Widget& self = tree_node(parent, elements, true, false);
		return self;
	}
	
	Widget& file_tree(Widget& parent, cstring path)
	{
		Widget& self = tree(parent);
		dir_node(self, path, path, false);
		return self;
	}
}
}
