//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Config.h>
#include <obj/Types.h>
#include <obj/Var.h>
#include <obj/Any.h>
#endif

namespace mud
{
	Val::Val()
		: m_type(&type<None>())
		, m_any(make_unique<TAny<None>>())
	{}
}
