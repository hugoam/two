//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Unique.h>
#include <obj/Type.h>
#include <proto/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	/*	A Prototype represent a fixed layout of parts for an object, allowing for fast part query 
			It is a broader definition of a type, different from the C++ class, it defines a finite object
			with a finite set of capabilities, which is a sum of components : its parts

			The parts are members of a prototype, whereas additionnal components are called plugs, 
			and are not part of the object in itself : they can be here or not here, whereas the parts are always here
	*/

	export_ class refl_ MUD_PROTO_EXPORT Prototype
	{
	public:
		Prototype(Class& cls);

		Type& m_type;
		Type& m_stem;
		std::vector<Type*> m_parts;

		void add_part(Type& type);

		inline bool has_part(Type& type) { return (m_hash_parts[type.m_id] != 0); }
		inline int part_index(Type& type) { return m_hash_parts[type.m_id]; }

	protected:
		std::vector<size_t> m_hash_parts;
	};

	export_ extern MUD_PROTO_EXPORT std::vector<unique_ptr<Prototype>> g_prototypes;

	export_ MUD_PROTO_EXPORT Prototype& proto(Type& type);

	export_ template <class T>
	inline Prototype& proto() { return proto(type<T>()); }
}
