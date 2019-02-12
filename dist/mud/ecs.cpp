#include <mud/ecs.h>
#include <mud/infra.h>
#include <mud/type.h>



#ifdef MUD_MODULES
module mud.ecs;
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
		for(Ref ref : parts)
			this->add_part(ref);
	}
}
#ifndef USE_STL
#ifdef MUD_MODULES
module mud.ecs;
#else
#include <stl/vector.hpp>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_ECS_EXPORT vector<Buffer*>;
	template class MUD_ECS_EXPORT vector<EntityStream*>;
	template class MUD_ECS_EXPORT vector<EntityData>;
	template class MUD_ECS_EXPORT vector<EntityStream>;
	template class MUD_ECS_EXPORT vector<unique<Buffer>>;
}
#endif

#ifdef MUD_MODULES
module mud.ecs;
#else
#endif

namespace mud
{
    // Exported types
    
    
    template <> MUD_ECS_EXPORT Type& type<mud::Complex>() { static Type ty("Complex", sizeof(mud::Complex)); return ty; }
    template <> MUD_ECS_EXPORT Type& type<mud::Entity>() { static Type ty("Entity", sizeof(mud::Entity)); return ty; }
}


#ifdef MUD_MODULES
module mud.ecs;
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
