//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.proto;
#else
#include <type/Cls.h>
#include <refl/Class.h>
#include <ecs/Proto.h>
#endif

namespace mud
{
	vector<unique_ptr<Prototype>> g_prototypes = vector<unique_ptr<Prototype>>(c_max_types);

	Type& proto_stem(Class& cls)
	{
		for(Member& member : cls.m_members)
			if(member.is_component())
				return *member.m_type;
	}

	Prototype::Prototype(Class& cls)
		: m_type(*cls.m_type)
		, m_stem(proto_stem(cls))
		, m_hash_parts(c_max_types)
	{
		for(Member& member : cls.m_members)
			if(member.is_component())
				this->add_part(*member.m_type);
		this->add_part(m_type);
	}

	void Prototype::add_part(Type& type)
	{
		Type* base = &type;
		while(base)
		{
			m_hash_parts[base->m_id] = m_parts.size();
			base = base->m_base;
		}
		m_parts.push_back(&type);
	}

	Prototype& proto(Type& type)
	{
		if(g_prototypes[type.m_id])
			g_prototypes[type.m_id] = make_unique<Prototype>(cls(type));
		return *g_prototypes[type.m_id];
	}
}
