#include <two/ecs.h>
#include <two/infra.h>
#include <two/type.h>



#ifdef TWO_MODULES
module two.ecs;
#else
#endif

namespace two
{
	Complex::Complex(uint32_t id, Type& type)
		: m_id(index(type, id, Ref(this, type)))
		, m_type(type)
		, m_prototype(proto(type))
		, m_parts(m_prototype.m_parts.size())
	{}

	Complex::Complex(uint32_t id, Type& type, span<Ref> parts)
		: Complex(id, type)
	{
		this->setup(parts);
	}

	Complex::~Complex()
	{
		unindex(m_type, m_id);
	}

	void Complex::setup(span<Ref> parts)
	{
		for(Ref ref : parts)
			this->add_part(ref);
	}
}
#ifndef USE_STL
#ifdef TWO_MODULES
module two.ecs;
#else
#include <stl/vector.hpp>
#endif

namespace stl
{
	using namespace two;
	template class TWO_ECS_EXPORT vector<Buffer*>;
	template class TWO_ECS_EXPORT vector<EntityStream*>;
	template class TWO_ECS_EXPORT vector<EntityStream>;
	template class TWO_ECS_EXPORT vector<unique<Buffer>>;
}
#endif

#ifdef TWO_MODULES
module two.ecs;
#else
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_ECS_EXPORT Type& type<two::Entity>() { static Type ty("Entity", sizeof(two::Entity)); return ty; }
    template <> TWO_ECS_EXPORT Type& type<two::Entt>() { static Type ty("Entt", sizeof(two::Entt)); return ty; }
    template <> TWO_ECS_EXPORT Type& type<two::OEntt>() { static Type ty("OEntt", type<two::Entt>(), sizeof(two::OEntt)); return ty; }
    template <> TWO_ECS_EXPORT Type& type<two::Complex>() { static Type ty("Complex", sizeof(two::Complex)); return ty; }
}


#ifdef TWO_MODULES
module two.ecs;
#else
#endif

namespace two
{
	ECS* s_ecs[256] = {};

	template <> Type& type<EntityRef>() { static Type ty("EntityRef"); return ty; }

	void Entity::destroy()
	{
		if(m_handle != UINT32_MAX)
			s_ecs[m_ecs]->destroy(*this);
	}

	OEntt::~OEntt()
	{
		if(m_handle != UINT32_MAX)
			m_ecs->destroy(m_handle);
	}
}
