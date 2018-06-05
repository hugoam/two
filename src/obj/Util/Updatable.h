//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <cstddef>
#endif

namespace mud
{
	export_ class MUD_OBJ_EXPORT Updatable
	{
	public:
		virtual void next_frame(size_t tick, size_t delta) = 0;
	};
}
