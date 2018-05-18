//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Config.h>
#include <obj/Type.h>

#include <obj/Proto.h>
#include <obj/Indexer.h>
#include <obj/Reflect/Meta.h>

#include <string.h>
#include <stdio.h>

namespace mud
{
	bool Address::operator==(const Address& other) const
	{
		return strncmp(value, other.value, 16) == 0;
	}

	size_t typeIndex = 2;

	Type::Type(int)
		: m_id(1)
		, m_type(*this)
		, m_kind(TypeKind::Type)
		, m_name("Type")
		, m_base(nullptr)
		, m_meta(nullptr)
	{}

	Type::Type(const char* name, TypeKind kind)
		: m_id(typeIndex++)
		, m_type(kind == TypeKind::Prototype ? Prototype::type() : Type::type())
		, m_kind(kind)
		, m_name(name)
		, m_base(nullptr)
		, m_meta(nullptr)
	{
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
