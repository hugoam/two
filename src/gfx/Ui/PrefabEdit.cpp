//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <gfx/Generated/Types.h>
#include <gfx/Ui/PrefabEdit.h>

#include <obj/Any.h>
#include <obj/String/StringConvert.h>
#include <obj/Reflect/Convert.h>
#include <obj/System/System.h>

#include <ui/Structs/Container.h>
#include <uio/Unode.h>

#include <uio/Edit/Inspector.h>
#include <uio/Edit/Method.h>

#include <gfx/Prefab.h>
#include <gfx/Gfx.h>

namespace mud
{
	TreeNode& prefab_structure(Widget& parent, PrefabNode& node, PrefabNode*& selected)
	{
		TreeNode& self = ui::tree_node(parent, to_string(var(node.m_prefab_type)).c_str());

		if(self.m_header->activated())
			selected = &node;

		self.m_header->setState(ACTIVE, selected == &node);

		for(PrefabNode& child : node.m_nodes)
		{
			TreeNode& structure = prefab_structure(*self.m_body, child, selected);
			if(ui::button(*structure.m_header, "X").activated())
			{
				//node.m_nodes.push_back({});
			}
		}

		return self;
	}

	Widget& prefab_inspector(Widget& parent, PrefabNode& node)
	{
		Widget& self = ui::sheet(parent);

		static cstring types[6] = { "None", "Item", "Model", "Shape", "Particles", "Light" };
		static std::vector<Function*> functions = { nullptr, &function(gfx::item), &function(gfx::model), &function(gfx::shape), &function(&gfx::particles), &function(gfx::light) };

		static cstring columns[2] = { "field", "value" };
		Widget& table = ui::table(self, { columns, 2 }, {});
 
		Widget& row = ui::row(table);
		ui::label(row, "type");
		if(ui::dropdown_input(row, { types, 6 }, (size_t&)node.m_prefab_type))
			node.m_call = { *functions[size_t(node.m_prefab_type)] };

		object_edit(table, &node.m_transform, EditorHint::Rows);
		if(node.m_call.m_callable)
			call_edit(table, node.m_call);

		return self;
	}

	PrefabNode* prefab_edit(Widget& parent, GfxSystem& system, PrefabNode& node)
	{
		UNUSED(system);
		Widget& self = ui::sheet(parent);

		static PrefabNode* selected = nullptr;

		ui::label(self, "Prefab graph");
		prefab_structure(self, node, selected);

		if(ui::button(self, "Add").activated())
		{
			node.m_nodes.push_back({});
			selected = &node.m_nodes.back();
		}

		ui::label(self, "Prefab node");
		if(selected)
			prefab_inspector(self, *selected);

		return selected;
	}
}
