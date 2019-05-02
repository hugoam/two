//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.ecs;
#else
#include <type/Indexer.h>
#include <type/Proto.h>
#include <ecs/Complex.h>
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
