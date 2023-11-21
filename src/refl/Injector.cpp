//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.refl;

namespace two
{
	Injector::Injector(const Constructor& constructor)
		: Call(constructor)
		, m_object_type(*constructor.m_object_type)
		, m_constructor(constructor)
#ifdef TWO_ECS_PROTO
		, m_proto(is<Prototype>(type) ? &as<Prototype>(type) : nullptr)
#endif
	{
#ifdef TWO_ECS_PROTO
		if(m_proto && &constructor == &cls(type).m_constructors[int(ConstructorIndex::ProtoParts)])
		{
			// we are a combined constructor
			size_t offset = cls(*m_proto->m_stem).m_constructors[int(ConstructorIndex::Default)].m_params.size();
			for(Type* part : m_proto->m_parts)
			{
				m_partIndex.push_back(offset);
				offset += cls(*part).m_constructors[int(ConstructorIndex::Default)].m_params.size();
			}
		}
#endif
	}

	Injector::Injector(Type& type, ConstructorIndex index)
		: Injector(cls(type).m_constructors[int(index)])
	{}

	Injector::Injector(Type& type, size_t arguments)
		: Injector(*cls(type).constructor(arguments))
	{}

	void Injector::inject(Var& value)
	{
		//m_constructor(value, to_array(m_args, 1));
	}

	Ref Injector::inject(Pool& pool)
	{
		Ref ref = pool.alloc();
		//m_constructor.m_call(ref, to_array(m_args, 1));
		return ref;
	}

	Var Injector::injectvar()
	{
		Var value = meta(m_object_type).m_empty_var;
		this->inject(value);
		return value;
	}

	Ref Injector::injectpool()
	{
		Pool& pool = *g_pools[m_object_type.m_id];
		return this->inject(pool);
	}

	void Injector::destroy(Ref object)
	{
		Pool& pool = *g_pools[m_object_type.m_id];
		pool.destroy(object);
	}

#ifdef TWO_ECS_PROTO
	span<Var> Injector::args(Type& type)
	{
		size_t index = m_partIndex[m_proto->part_index(type)];
		return to_array(m_args, index);
	}
#endif

	Creator::Creator(Type& type)
		: m_type(type)
#ifdef TWO_ECS_PROTO
		, m_construct(cls(type).m_prototypes.size() > 0)
		, m_prototype(m_construct ? cls(type).m_prototypes[0] : nullptr)
#else
		, m_construct(false)
		, m_prototype(nullptr)
#endif
		, m_injector(oconstruct<Injector>(m_prototype ? *m_prototype : type))
	{}

	void Creator::set_prototype(Type& prototype)
	{
		m_prototype = &prototype;
		m_injector = oconstruct<Injector>(*m_prototype);
	}
}
