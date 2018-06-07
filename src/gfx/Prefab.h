//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Reflect/Method.h>
#endif
#include <gfx/Generated/Forward.h>
#include <gfx/Node3.h>

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
		PrefabNode() {}

		attr_ mut_ Transform m_transform = {};
		attr_ mut_ Ref m_object = {};
		attr_ mut_ PrefabType m_prefab_type = PrefabType::None;
		attr_ mut_ Call m_call = {};
		attr_ mut_ std::vector<PrefabNode> m_nodes;

		void draw(Gnode& parent);
	};

	export_ class refl_ MUD_GFX_EXPORT Prefab
	{
	public:
		Prefab(cstring name) : m_name(name) {}

		attr_ string m_name;
		attr_ mut_ PrefabNode m_node;
	};
}
