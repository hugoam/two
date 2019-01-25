//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <refl/Member.h>
#include <refl/Meta.h>
#include <refl/System.h>
#endif

namespace mud
{
	Static::Static(Type& parent_type, cstring name, Ref value)
		: m_parent_type(&parent_type)
		, m_name(name)
		, m_value(value)
	{}

	Member::Member(Type& object_type, Address address, Type& type, cstring name, Ref default_value, Flags flags, MemberGet get)
		: m_index(0)
		, m_object_type(&object_type)
		, m_address(address)
		, m_type(&type)
		, m_name(name)
		, m_default_value(default_value)
		, m_flags(flags)
		, m_get(get)
	{
		m_offset = *reinterpret_cast<size_t*>(m_address.value);
	}

	Member::~Member()
	{}
}
