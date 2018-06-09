//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Config.h>

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Proto.h>
#include <obj/Cls.h>
#endif

namespace mud
{
	Prototype::Prototype(const char* name, Type& stem, const std::vector<Type*>& parts)
		: Type(name, TypeKind::Prototype)
		, m_stem(stem)
		, m_hash_parts(c_max_types)
	{
		for(Type* type : parts)
			this->add_part(*type);
		this->add_part(*this);
	}
}
