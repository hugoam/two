//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.uio;

namespace two
{
	DispatchSelector::DispatchSelector()
	{}

	void complex_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection)
	{
		Member& complex = cls(*indexer.m_type).member("complex");

		Widget& self = ui::sheet(parent);
		for(Ref component : indexer.m_objects)
			if(component)
			{
				Ref object = complex.cast_get(component);
				Widget& item = object_item(self, object);
				if(selection)
					ui::multiselect_logic(item, object, *selection);
			}
	}

	void object_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection)
	{
		Widget& self = ui::sheet(parent);
		for(Ref object : indexer.m_objects)
			if(object)
			{
				Widget& item = object_item(self, object);
				if(selection)
					ui::multiselect_logic(item, object, *selection);
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
			string title = "Select " + string(type(result).m_name);
			Widget& modal = ui::auto_modal(parent, PICK, { 600, 400 });
			
			Widget& self = *ui::scroll_sheet(*modal.m_body).m_body;
			changed = object_selector(self, indexer(type(result)), result);
			if(ui::button(*modal.m_body, "Done").activated())
				screen.m_switch &= ~PICK;
		}
		return changed;
	}
}
