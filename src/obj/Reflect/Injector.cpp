//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Config.h>
#include <obj/Types.h>
#include <obj/Proto.h>
#include <obj/Reflect/Injector.h>
#include <obj/Reflect/Class.h>
#include <obj/Reflect/Injector.h>
#include <obj/Memory/ObjectPool.h>
#endif

namespace mud
{
	Injector::Injector(Type& type, const Constructor& constructor)
		: m_type(type)
		, m_constructor(constructor)
		, m_args(m_constructor.m_arguments)
		, m_proto(is<Prototype>(type) ? &as<Prototype>(type) : nullptr)
	{
		if(type.m_class->m_constructors.empty())
			return;

		if(m_proto && &constructor == &type.m_class->m_constructors[int(ConstructorIndex::ProtoParts)])
		{
			// we are a combined constructor
			size_t offset = m_proto->m_stem.m_class->m_constructors[int(ConstructorIndex::Default)].m_params.size();
			for(Type* part : m_proto->m_parts)
			{
				m_partIndex.push_back(offset);
				offset += part->m_class->m_constructors[int(ConstructorIndex::Default)].m_params.size();
			}
		}
	}

	Injector::Injector(Type& type, ConstructorIndex index)
		: Injector(type, type.m_class->m_constructors[int(index)])
	{}

	Injector::Injector(Type& type, size_t arguments)
		: Injector(type, *type.m_class->constructor(arguments))
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
		Var value = m_type.m_meta->m_empty_var();
		this->inject(value);
		return value;
	}

	Ref Injector::injectpool()
	{
		Pool& pool = GlobalPool::me().pool(m_type);
		return this->inject(pool);
	}

	array<Var> Injector::args(Type& type)
	{
		size_t index = m_partIndex[m_proto->part_index(type)];
		return to_array(m_args, index);
	}

	Creator::Creator(Type& type)
		: m_type(type)
		, m_construct(type.m_class->m_prototypes.size() > 0)
		, m_prototype(m_construct ? type.m_class->m_prototypes[0] : nullptr)
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
