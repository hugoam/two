//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.obj;
#else
#include <infra/Config.h>
#include <type/Var.h>
#include <type/Any.h>
#endif

namespace mud
{
	Val::Val()
		: m_type(&type<None>())
		, m_any(make_unique<TAny<None>>())
	{}
}
