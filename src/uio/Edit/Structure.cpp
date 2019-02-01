//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/string.h>
#include <stl/algorithm.h>
#include <refl/Meta.h>
#include <refl/Member.h>
#include <refl/Convert.h>
#include <refl/Sequence.h>
#include <ui/Structs/Container.h>
#include <uio/Edit/Structure.h>
#include <ui/Section.h>
#include <uio/Object.h>
#endif

namespace mud
{
	void structure_node(Widget& parent, Ref object, vector<Ref>& selection)
	{
		TreeNode& self = ui::tree_node(parent, { object_icon(object).c_str(), object_name(object).c_str() }, false, false);
		
		self.set_state(SELECTED, has(selection, object));
		
		if(self.m_header->activated())
			select(selection, object);
		
		//object_item(self, object);

		for(auto& member : cls(object).m_members)
			if(member.is_structure() && is_iterable(*member.m_type))
			{
				Var value = member.get(object);
				iter(value).iterate(value, [&](Ref element) {
					structure_node(self, element, selection);
				});
			}
	}

	void structure_view(Widget& parent, Ref object, vector<Ref>& selection)
	{
		ScrollSheet& sheet = ui::scroll_sheet(parent);
		Widget& tree = ui::tree(*sheet.m_body);
		structure_node(tree, object, selection);
	}
}
