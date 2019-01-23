//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <type/Unique.h>
#include <type/Type.h>
#include <ecs/Forward.h>

namespace mud
{
	/*	A Prototype represent a fixed layout of parts for an object, allowing for fast part query 
			It is a broader definition of a type, different from the C++ class, it defines a finite object
			with a finite set of capabilities, which is a sum of components : its parts

			The parts are members of a prototype, whereas additionnal components are called plugs, 
			and are not part of the object in itself : they can be here or not here, whereas the parts are always here
	*/

	export_ class refl_ MUD_ECS_EXPORT Prototype
	{
	public:
		Prototype(Type& type, vector<Type*> parts);

		Type& m_type;
		vector<Type*> m_parts;

		void add_part(Type& type);

		inline bool has_part(Type& type) { return (m_hash_parts[type.m_id] != 0); }
		inline size_t part_index(Type& type) { return m_hash_parts[type.m_id]; }

	protected:
		vector<size_t> m_hash_parts;
	};

	export_ extern MUD_ECS_EXPORT vector<Prototype*> g_prototypes;

	inline Prototype& proto(Type& type) { return *g_prototypes[type.m_id]; }
}
