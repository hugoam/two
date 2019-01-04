//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <string>
#endif

#ifdef MUD_MODULES
module mud.uio;
#else
#include <infra/Vector.h>
#include <refl/Meta.h>
#include <refl/Member.h>
#include <refl/Convert.h>
#include <refl/Sequence.h>
#include <ui/Structs/Container.h>
#include <uio/Edit/Structure.h>
#include <uio/Unode.h>
#include <uio/Edit/Section.h>
#include <uio/Object.h>
#endif

namespace mud
{
	using string = std::string;

	void structure_node(Widget& parent, Ref object, std::vector<Ref>& selection)
	{
		TreeNode& self = ui::tree_node(parent, carray<cstring, 2>{ object_icon(object).c_str(), object_name(object).c_str() }, false, false);
		
		self.set_state(SELECTED, vector_has(selection, object));
		
		if(self.m_header->activated())
			vector_select(selection, object);
		
		//object_item(self, object);

		for(auto& member : cls(object).m_members)
			if(member.is_structure() && (member.cls().m_is_iterable || member.cls().m_iterable))
			{
				Var value = member.get(object);
				iterate_sequence(value, [&](Ref element) {
					structure_node(self, element, selection);
				});
			}
	}

	void structure_view(Widget& parent, Ref object, std::vector<Ref>& selection)
	{
		ScrollSheet& sheet = ui::scroll_sheet(parent);
		Widget& tree = ui::tree(*sheet.m_body);
		structure_node(tree, object, selection);
	}
}
