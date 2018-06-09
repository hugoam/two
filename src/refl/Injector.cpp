//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <obj/Types.h>
//#include <proto/Proto.h>
#include <refl/Injector.h>
#include <refl/Class.h>
#include <refl/Injector.h>
#include <pool/ObjectPool.h>
#endif

namespace mud
{
	Injector::Injector(Type& type, const Constructor& constructor)
		: m_type(type)
		, m_constructor(constructor)
		, m_args(m_constructor.m_arguments)
#ifdef MUD_PROTO
		, m_proto(is<Prototype>(type) ? &as<Prototype>(type) : nullptr)
#endif
	{
		if(cls(type).m_constructors.empty())
			return;

#ifdef MUD_PROTO
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
		: Injector(type, cls(type).m_constructors[int(index)])
	{}

	Injector::Injector(Type& type, size_t arguments)
		: Injector(type, *cls(type).constructor(arguments))
	{}

	void Injector::inject(Var& value)
	{
		m_constructor.m_call(value, to_array(m_args, 1));
	}

	Ref Injector::inject(Pool& pool)
	{
		Ref ref = pool.alloc();
		m_constructor.m_call(ref, to_array(m_args, 1));
		return ref;
	}

	Var Injector::injectvar()
	{
		Var value = meta(m_type).m_empty_var();
		this->inject(value);
		return value;
	}

	Ref Injector::injectpool()
	{
		Pool& pool = GlobalPool::me().pool(m_type);
		return this->inject(pool);
	}

#ifdef MUD_PROTO
	array<Var> Injector::args(Type& type)
	{
		size_t index = m_partIndex[m_proto->part_index(type)];
		return to_array(m_args, index);
	}
#endif

	Creator::Creator(Type& type)
		: m_type(type)
#ifdef MUD_PROTO
		, m_construct(cls(type).m_prototypes.size() > 0)
		, m_prototype(m_construct ? cls(type).m_prototypes[0] : nullptr)
#else
		, m_construct(false)
		, m_prototype(nullptr)
#endif
		, m_injector(make_object<Injector>(m_prototype ? *m_prototype : type))
	{}

	void Creator::setPrototype(Type& prototype)
	{
		m_prototype = &prototype;
		m_injector = make_object<Injector>(*m_prototype);
	}

	Ref Creator::create()
	{
		Pool& pool = GlobalPool::me().pool(m_injector->m_type);
		return m_injector->inject(pool);
	}

	void Creator::destroy(Ref object)
	{
		Pool& pool = GlobalPool::me().pool(m_injector->m_type);
		pool.destroy(object);
	}
}
