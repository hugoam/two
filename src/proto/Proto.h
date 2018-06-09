//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Forward.h>
#include <obj/Type.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	struct ProtoPart
	{
		ProtoPart(Type* type = nullptr, size_t index = 0) : m_type(type), m_index(index) {}
		Type* m_type = nullptr;
		size_t m_index = 0;
	};

	/*	A Prototype represent a fixed layout of parts for an object, allowing for fast part query 
			It is a broader definition of a type, different from the C++ class, it defines a finite object
			with a finite set of capabilities, which is a sum of components : its parts

			The parts are members of a prototype, whereas additionnal components are called plugs, 
			and are not part of the object in itself : they can be here or not here, whereas the parts are always here
	*/

	export_ class refl_ MUD_OBJ_EXPORT Prototype : public Type
	{
	public:
		Prototype(const char* name, Type& stem, const std::vector<Type*>& parts);

		Type& m_stem;
		std::vector<Type*> m_parts;

		inline void add_part(Type& type) { m_hash_parts[type.m_id] = { &type, m_parts.size() }; m_parts.push_back(&type); }
		inline bool has_part(Type& type) { return (m_hash_parts[type.m_id].m_type != nullptr); }
		inline int part_index(Type& type) { return m_hash_parts[type.m_id].m_index; }

		static Type& type() { static Type ty("Prototype", Type::type()); return ty; }

	protected:
		std::vector<ProtoPart> m_hash_parts;
	};

	export_ template <class T>
	Prototype& proto();

	template <> inline Type& type<Prototype>() { return Prototype::type(); }
}
