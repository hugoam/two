//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.refl;
#else
#include <refl/Member.h>
#include <refl/Meta.h>
#include <refl/System.h>
#endif

namespace two
{
	Static::Static() {}
	Static::Static(Type& parent_type, cstring name, Ref value)
		: m_parent_type(&parent_type)
		, m_name(name)
		, m_value(value)
	{}

	Member::Member() {}
	Member::Member(Type& object_type, size_t offset, Type& type, cstring name, const void* default_value, Flags flags, MemberGet get)
		: m_index(0)
		, m_object_type(&object_type)
		, m_offset(offset)
		, m_type(&type)
		, m_name(name)
		, m_default_value((void*)default_value, type)
		, m_flags(flags)
		, m_get(get)
	{}

	Member::~Member()
	{}
}
