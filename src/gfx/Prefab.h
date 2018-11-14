//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <refl/Method.h>
#include <geom/Aabb.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>
#include <gfx/Importer.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ enum class refl_ PrefabType : unsigned int
	{
		None,
		Item,
		Model,
		Shape,
		Particles,
		Light
	};

	export_ struct refl_ MUD_GFX_EXPORT PrefabNode
	{
		PrefabNode();

		attr_ Transform m_transform = {};
		attr_ Ref m_object = {};
		attr_ PrefabType m_prefab_type = PrefabType::None;
		attr_ Call m_call = {};
		attr_ std::vector<PrefabNode> m_nodes;

		void draw(Gnode& parent);
	};

	export_ class refl_ MUD_GFX_EXPORT Prefab
	{
	public:
		Prefab(cstring name);

		attr_ string m_name;
		attr_ PrefabNode m_node;

		std::vector<Node3> m_nodes;
		std::vector<Item> m_items;

		Aabb m_aabb;
	};

	export_ MUD_GFX_EXPORT Prefab& import_prefab(GfxSystem& gfx_system, ModelFormat format, const string& name, const ImportConfig& config);
	export_ MUD_GFX_EXPORT void destroy_prefab(GfxSystem& gfx_system, Prefab& prefab);
}
