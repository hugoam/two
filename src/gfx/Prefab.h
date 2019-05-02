//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
//#include <refl/Method.h>
#include <geom/Aabb.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>
#include <gfx/Importer.h>

namespace two
{
#ifdef TWO_PREFABNODE
	export_ enum class refl_ PrefabType : unsigned int
	{
		None,
		Item,
		Model,
		Shape,
		Flare,
		Light
	};

	export_ struct refl_ TWO_GFX_EXPORT PrefabNode
	{
		PrefabNode();

		attr_ Transform m_transform = {};
		attr_ Ref m_object = {};
		attr_ PrefabType m_prefab_type = PrefabType::None;
		attr_ Call m_call = {};
		attr_ vector<PrefabNode> m_nodes;

		void draw(Gnode& parent);
	};
#endif

	export_ class refl_ TWO_GFX_EXPORT Prefab
	{
	public:
		Prefab(const string& name);

		attr_ string m_name;
#ifdef TWO_PREFABNODE
		attr_ PrefabNode m_node;
#endif

		meth_ void add(Scene& scene, Mime* mime = nullptr);

		vector<Node3> m_nodes;
		struct Elem { uint32_t node; Item item; };
		vector<Elem> m_items;

		Aabb m_aabb;

		vector<Animation*> m_anims;
	};

	export_ TWO_GFX_EXPORT Prefab& import_prefab(GfxSystem& gfx, ModelFormat format, const string& name, const ImportConfig& config);
	export_ TWO_GFX_EXPORT void destroy_prefab(GfxSystem& gfx, Prefab& prefab);
}
