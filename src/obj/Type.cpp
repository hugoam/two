//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#endif

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Type.h>
#include <obj/Vector.h>
#include <obj/Indexer.h>
//#include <proto/Proto.h>
#endif

namespace mud
{
	using string = std::string;

	const unsigned int c_max_types = 1000U;

#ifdef MUD_CONTAINER_TYPES_2
	std::vector<Type> g_vector_types = std::vector<Type>(1000U);
	std::vector<Type> g_array_types = std::vector<Type>(1000U);
#endif

	bool Address::operator==(const Address& other) const
	{
		return strncmp(value, other.value, 16) == 0;
	}

	static size_t s_type_index = 2;

	Type::Type(int)
		: m_id(1)
		, m_type(*this)
		, m_kind(TypeKind::Type)
		, m_name("Type")
	{}

	Type::Type()
		: m_id(0)
		, m_type(*this)
		, m_kind(TypeKind::Type)
		, m_name("")
	{}

	Type::Type(const char* name, TypeKind kind)
		: m_id(s_type_index++)
		//, m_type(kind == TypeKind::Prototype ? Prototype::type() : Type::type())
		, m_type(Type::type())
		, m_kind(kind)
		, m_name(name)
	{
		printf("DEBUG: Type %s %i\n", name, int(m_id));

		if(strcmp(name, "INVALID") == 0)
			printf("WARNING: Invalid type created, this means an lref was created for a type which isn't exported\n");
	}
	
	Type::Type(const char* name, Type& base, TypeKind kind)
		: Type(name, kind)
	{
		m_base = &base;
	}

	Type::~Type()
	{}

	bool Type::is(Type& type) const
	{
		if(&type == this)
			return true;
		else if(m_base)
			return m_base->is(type);
		else
			return false;
	}
}
