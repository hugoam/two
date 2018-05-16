//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <uio/Edit/Structure.h>

#include <obj/Vector.h>

#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Member.h>
#include <obj/Reflect/Convert.h>
#include <obj/Reflect/Sequence.h>

#include <uio/Unode.h>
#include <uio/Edit/Section.h>
#include <ui/Structs/Container.h>

#include <string>

namespace mud
{
	using string = std::string;

	static string object_name(Ref object)
	{
		return object ? to_name(object.type(), object) : "null";
	}

	static string object_icon(Ref object)
	{
		return object ? "(" + string(meta(object).m_name) + ")" : "";
	}

	Widget& structure_widget(Widget& parent)
	{
		ScrollSheet& sheet = ui::scroll_sheet(parent);
		ui::tree(*sheet.m_body);
		return sheet;
	}

	Widget& structure_node_widget(Widget& parent, Ref object, std::vector<Ref>& selection)
	{
		string name = object_name(object);
		TreeNode& self = ui::tree_node(parent, name.c_str(), false, false);
		self.setState(SELECTED, vector_has(selection, object));
		if(self.m_header->activated())
			vector_select(selection, object);
		return self;
	}

	void structure_node(Widget& parent, Ref object, std::vector<Ref>& selection)
	{
		Widget& self = structure_node_widget(parent, object, selection);
		//node.refresh(structure_node_refresh, object, selection);

		object_hook(self, object);

		for(auto& member : cls(object).m_members)
			if(member.cls().m_iterable && member.is_structure())
			{
				Var value = member.get(object);
				iterate_sequence(value, [&](Ref element) {
					structure_node(self, element, selection);
				});
			}
	}

	void structure_view(Widget& parent, Ref object, std::vector<Ref>& selection)
	{
		Widget& self = section(parent, "Structure");
		structure_node(self, object, selection);
	}
}
