//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.proto;
#else
#include <type/Indexer.h>
#include <ecs/Entity.h>
#include <ecs/Proto.h>
#endif

namespace mud
{
	ECS* s_ecs[256] = {};

	template <> Type& type<EntityRef>() { static Type ty("EntityRef"); return ty; }

	Complex::Complex(Id id, Type& type)
		: m_id(index(type, id, Ref(this, type)))
		, m_type(type)
		, m_prototype(proto(type))
		, m_parts(m_prototype.m_parts.size())
	{}

	Complex::Complex(Id id, Type& type, const std::vector<Ref>& parts)
		: Complex(id, type)
	{
		this->setup(parts);
	}

	Complex::~Complex()
	{
		unindex(m_type, m_id);
	}

	void Complex::setup(const std::vector<Ref>& parts)
	{
		for (Ref ref : parts)
			this->add_part(ref);
	}
}
