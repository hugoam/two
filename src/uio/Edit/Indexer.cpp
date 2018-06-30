//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <string>
#endif

#ifdef MUD_MODULES
module mud.uio;
#else
#include <obj/Indexer.h>
#include <refl/Meta.h>
#include <ui/Structs/Container.h>
#include <ui/Structs/Window.h>
#include <uio/Object.h>
#include <uio/Edit/Indexer.h>
#endif

namespace mud
{
	DispatchSelector::DispatchSelector()
	{}

	using string = std::string;

	void object_indexer(Widget& parent, Indexer& indexer)
	{
		Widget& self = ui::sheet(parent);
		for(size_t id = 0; id < indexer.m_objects.size(); ++id)
			if(indexer.m_objects[id].m_value)
			{
				object_item(self, indexer.m_objects[id]);
			}
	}

	bool generic_object_selector(Widget& parent, Indexer& indexer, Ref& result)
	{
		bool changed = false;
		Widget& self = ui::sheet(parent);
		for(size_t id = 0; id < indexer.m_objects.size(); ++id)
			if(indexer.m_objects[id].m_value)
			{
				if(object_item(self, indexer.m_objects[id], result))
				{
					result = indexer.m_objects[id];
					changed = true;
				}
			}
		return changed;
	}

	bool object_selector(Widget& parent, Indexer& indexer, Ref& result)
	{
		if(DispatchSelector::me().check(result))
			return DispatchSelector::me().dispatch(result, parent);
		else
			return generic_object_selector(parent, indexer, result);
	}

	void object_indexer_modal(Widget& parent, Indexer& indexer)
	{
		Widget& self = ui::select_list(parent);
		object_indexer(self, indexer);
	}

	bool object_selector(Widget& parent, Ref& result)
	{
		Widget& self = ui::sheet(parent);
		return object_selector(self, indexer(type(result)), result);
	}

	bool object_selector_modal(Widget& screen, Widget& parent, Ref& result)
	{
		enum Modes { PICK = 1 << 0 };

		bool changed = false;
		if(ui::modal_button(screen, parent, ".", PICK))
		{
			Widget& window = ui::window(parent.root(), ("Select " + string(type(result).m_name)).c_str());
			if(window.m_body)
			{
				Widget& self = *ui::scroll_sheet(*window.m_body).m_body;
				changed = object_selector(self, indexer(type(result)), result);
				if(ui::button(self, "Done").activated())
					screen.m_switch &= ~PICK;
			}
			else
				screen.m_switch &= ~PICK;
		}
		return changed;
	}
}
