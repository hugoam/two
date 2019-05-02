//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.ecs;
#else
#include <ecs/Entity.h>
#include <ecs/ECS.h>
#include <ecs/ECS.hpp>
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
