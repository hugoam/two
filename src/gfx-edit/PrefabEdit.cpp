//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.gfx.edit;

namespace two
{
#if 0
	TreeNode prefab_node(Widget& parent, PrefabNode* parent_node, PrefabNode& node, PrefabNode*& selected)
	{
		TreeNode self = ui::tree_node(key(), parent, to_string(var(node.m_prefab_type)).c_str());

		if(self.header.activated())
			selected = &node;

		self.header.set_state(ACTIVE, selected == &node);

		if(ui::button(key(), self.header, "+").activated())
		{
			node.m_nodes.push_back({});
			selected = &node.m_nodes.back();
		}
		if(ui::button(key(), self.header, "X").activated())
		{
			if(selected == &node)
				selected = parent_node;
			vector_remove_object(parent_node->m_nodes, node);
			return self;
		}

		for(PrefabNode& child : node.m_nodes)
			prefab_node(*self.body, &node, child, selected);

		return self;
	}

	void prefab_structure(Widget& parent, PrefabNode& node, PrefabNode*& selected)
	{
		Section self = section(key(), parent, "Prefab Graph");
		prefab_node(self.body, nullptr, node, selected);
	}

	Widget& prefab_inspector(Widget& parent, PrefabNode& node)
	{
		Section self = section(key(), parent, "Prefab Inspector");

		static cstring types[6] = { "None", "Item", "Model", "Shape", "Flare", "Light" };
		static vector<Function*> functions = { nullptr, &function(gfx::item), &function(gfx::model), &function(gfx::shape), &function(&gfx::particles), &function(gfx::light) };

		static cstring columns[2] = { "field", "value" };
		Widget& table = ui::table(key(), self.body, { columns, 2 }, {});

		Widget& row = ui::row(key(), table);
		ui::label(key(), row, "type");
		if(ui::dropdown_input(key(), row, { types, 6 }, (uint32_t&)node.m_prefab_type))
			node.m_call = { *functions[size_t(node.m_prefab_type)] };

		object_edit(table, Ref(&node.m_transform), EditorHint::Rows);
		if(node.m_call.m_callable)
			call_edit(table, node.m_call);

		return self;
	}

	void prefab_edit(Widget& parent, GfxSystem& gfx, PrefabNode& node, PrefabNode*& selected)
	{
		UNUSED(gfx);
		Widget& self = ui::sheet(key(), parent);

		prefab_structure(self, node, selected);

		if(selected)
			prefab_inspector(self, *selected);
	}
#endif
}
