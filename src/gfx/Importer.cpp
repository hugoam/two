//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <gfx/Cpp20.h>
module two.gfx;

namespace two
{
	Import::Import(GfxSystem& gfx, const string& filepath, const ImportConfig& config)
		: m_gfx(gfx), m_config(config)
	{
		m_path = file_directory(filepath);
		m_file = file_name(filepath);
	}

	bool ImportConfig::filter_element(const string& name) const
	{
		for(const string& filter : m_exclude_elements)
			if(name.find(filter) != string::npos)
			{
				return true;
			}

		for(const string& filter : m_include_elements)
			if(name.find(filter) == string::npos)
			{
				return true;
			}

		return false;
	}

	bool ImportConfig::filter_material(const string& name) const
	{
		for(const string& filter : m_exclude_materials)
			if(name.find(filter) != string::npos)
			{
				return true;
			}

		for(const string& filter : m_include_materials)
			if(name.find(filter) == string::npos)
			{
				return true;
			}

		return false;
	}

	void import_to_prefab(GfxSystem& gfx, Prefab& prefab, Import& state, uint32_t flags)
	{
		UNUSED(gfx);
		prefab.m_nodes.reserve(state.m_items.size());
		prefab.m_items.reserve(state.m_items.size());

		prefab.m_aabb = {};

		for(const Node3& node : state.m_nodes)
		{
			prefab.m_nodes.push_back({ node });
		}

		for(Import::Item& item : state.m_items)
		{
			Model& model = *item.model;
			Node3& node = prefab.m_nodes[item.node];
			prefab.m_items.push_back({ item.node, Item(node, model, ItemFlag::Default | flags) });

			prefab.m_aabb.merge(transform_aabb(model.m_aabb, node.m_transform));

			// special hack for occluders
			if(model.m_items[0].m_mesh->m_material && model.m_items[0].m_mesh->m_material->m_name == "occluder")
				prefab.m_items.back().item.m_flags = ItemFlag::Occluder;
		}

		for(Animation* anim : state.m_animations)
			prefab.m_anims.push_back(anim);
	}
}
