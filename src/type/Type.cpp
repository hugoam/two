//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.type;
#else
#include <cstring>
#include <cstdio>
#include <stl/vector.h>
#include <stl/string.h>
#include <infra/Log.h>
#include <type/Type.h>
#include <type/Vector.h>
#include <type/Indexer.h>
//#include <ecs/Proto.h>
#endif

namespace two
{
	bool Address::operator==(const Address& other) const
	{
		return strncmp(value, other.value, 16) == 0;
	}

	Index Index::me;

	static uint32_t s_type_index = 2;

	Type::Type(int)
		: m_id(1)
		, m_name("Type")
	{}

	Type::Type()
		: m_id(0)
		, m_name("")
	{}

	Type::Type(const char* name, size_t size)
		: m_id(s_type_index++)
		, m_name(name)
		, m_size(size)
	{
		//printf("[debug] Type %s %i\n", name, int(m_id));

		if(strcmp(name, "INVALID") == 0)
			warn("Invalid type created, this means an lref was created for a type which isn't exported\n");
	}
	
	Type::Type(const char* name, Type& base, size_t size)
		: Type(name, size)
	{
		m_base = &base;
	}

	Type::~Type()
	{}

	bool Type::is(const Type& type) const
	{
		if(&type == this)
			return true;
		else if(m_base)
			return m_base->is(type);
		else
			return false;
	}
}
