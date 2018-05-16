//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <uio/Edit/Indexer.h>

#include <obj/Indexer.h>
#include <obj/Reflect/Meta.h>

#include <ui/Structs/Container.h>
#include <ui/Structs/Window.h>

#include <string>

namespace mud
{
	struct MUD_UIO_EXPORT ObjectPickerState : public NodeState
	{
		Ref m_selected = {};
	};

	using string = std::string;

	void object_indexer(Widget& parent, Indexer& indexer)
	{
		//ui::list(parent);
		Widget& self = ui::sheet(parent);
		for(size_t id = 0; id < indexer.m_objects.size(); ++id)
			if(indexer.m_objects[id].m_value)
			{
				object_hook(self, indexer.m_objects[id]);
			}
	}

	Ref object_selector(Widget& parent, Indexer& indexer)
	{
		Ref selected = {};
		//ui::list(parent);
		Widget& self = ui::sheet(parent);
		for(size_t id = 0; id < indexer.m_objects.size(); ++id)
			if(indexer.m_objects[id].m_value)
			{
				if(object_trigger(self, indexer.m_objects[id]))
					selected = indexer.m_objects[id];
			}
		return selected;
	}

	void object_indexer_modal(Widget& parent, Indexer& indexer)
	{
		Widget& self = ui::select_list(parent);
		object_indexer(self, indexer);
	}

	Ref object_picker(Widget& parent, Type& type)
	{
		//ui::list(parent);
		Widget& self = ui::sheet(parent);
		return object_selector(self, indexer(type));
	}

	Ref object_picker_modal(Widget& parent, Type& type)
	{
		Widget& window = ui::window(parent.root(), ("Select " + string(type.m_meta->m_name)).c_str());
		Widget& self = *ui::scroll_sheet(*window.m_body).m_body;
		Ref selected = object_selector(self, indexer(type));
		bool closed = !window.m_body || ui::button(self, "Done").activated();
		//if(closed || selected)
		//	self.close();
		return selected;

		//bool done = modal_dialog(parent, "Select " + type.m_name);
		//return done ? selected : Ref{};
		//return selected;
	}
}
