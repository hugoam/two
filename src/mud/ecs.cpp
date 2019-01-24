#pragma once

#include <mud/ecs.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.proto;
#else
#endif

namespace mud
{
	Complex::Complex(uint32_t id, Type& type)
		: m_id(index(type, id, Ref(this, type)))
		, m_type(type)
		, m_prototype(proto(type))
		, m_parts(m_prototype.m_parts.size())
	{}

	Complex::Complex(uint32_t id, Type& type, const vector<Ref>& parts)
		: Complex(id, type)
	{
		this->setup(parts);
	}

	Complex::~Complex()
	{
		unindex(m_type, m_id);
	}

	void Complex::setup(const vector<Ref>& parts)
	{
		for (Ref ref : parts)
			this->add_part(ref);
	}
}


#ifdef MUD_MODULES
module mud.proto;
#else
#endif

namespace mud
{
	ECS* s_ecs[256] = {};

	template <> Type& type<EntityRef>() { static Type ty("EntityRef"); return ty; }

	void Entity::destroy()
	{
		if(m_handle != UINT32_MAX)
			s_ecs[m_ecs]->destroy(m_handle);
	}
}


#ifdef MUD_MODULES
module mud.proto;
#else
#endif

namespace mud
{
	vector<Prototype*> g_prototypes = vector<Prototype*>(c_max_types);

	Prototype::Prototype(Type& type, vector<Type*> parts)
		: m_type(type)
		, m_hash_parts(c_max_types)
	{
		g_prototypes[type.m_id] = this;
		for (Type* part : parts)
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

#ifdef MUD_MODULES
module mud.ecs;
#else
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_ECS_EXPORT Type& type<mud::Complex>() { static Type ty("Complex", sizeof(mud::Complex)); return ty; }
    template <> MUD_ECS_EXPORT Type& type<mud::Entity>() { static Type ty("Entity", sizeof(mud::Entity)); return ty; }
    template <> MUD_ECS_EXPORT Type& type<mud::Prototype>() { static Type ty("Prototype", sizeof(mud::Prototype)); return ty; }
}
