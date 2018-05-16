//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Config.h>
#include <obj/Complex.h>

#include <obj/Proto.h>
#include <obj/Indexer.h>

namespace mud
{
	Complex::Complex(Id id, Type& type, Prototype& prototype)
		: m_id(index(type, id, Ref(this, type)))
		, m_type(type)
		, m_prototype(prototype)
		, m_parts(prototype.m_parts.size())
	{}

	Complex::~Complex()
	{
		unindex(m_type, m_id);
	}

	Construct::Construct(Complex& stem, Prototype& prototype)
		: m_type(prototype), m_stem(stem), m_prototype(prototype)
	{
		m_stem.m_construct = this;
	}

	Construct::~Construct()
	{}
}
