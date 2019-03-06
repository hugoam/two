//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.type;
#else
#include <type/Cls.h>
#include <type/Proto.h>
#endif

namespace mud
{
	vector<Prototype*> g_prototypes = vector<Prototype*>(c_max_types);

	Prototype::Prototype(Type& type, span<Type*> parts)
		: m_type(type)
		, m_hash_parts(c_max_types)
	{
		g_prototypes[type.m_id] = this;
		for(Type* part : parts)
			this->add_part(*part);
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
}
