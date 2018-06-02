//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Reflect/Method.h>
#include <gfx/Generated/Forward.h>
#include <gfx/Node3.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ enum class _refl_ PrefabType : unsigned int
	{
		None,
		Item,
		Model,
		Shape,
		Particles,
		Light
	};

	export_ struct _refl_ MUD_GFX_EXPORT PrefabNode
	{
		PrefabNode() {}

		_attr_ _mut_ Transform m_transform = {};
		_attr_ _mut_ Ref m_object = {};
		_attr_ _mut_ PrefabType m_prefab_type = PrefabType::None;
		_attr_ _mut_ Call m_call = {};
		_attr_ _mut_ std::vector<PrefabNode> m_nodes;

		void draw(Gnode& parent);
	};

	export_ class _refl_ MUD_GFX_EXPORT Prefab
	{
	public:
		Prefab(cstring name) : m_name(name) {}

		_attr_ strung m_name;
		_attr_ _mut_ PrefabNode m_node;
	};
}
