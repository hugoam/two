//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <string>
#include <vector>

#include <obj/Generated/Types.h>

namespace mud
{
	using string = std::string;

	//template <> MUD_OBJ_EXPORT Type& type<std::vector<float>>();
	template <> MUD_OBJ_EXPORT Type& type<std::vector<string>>();
	template <> MUD_OBJ_EXPORT Type& type<std::vector<size_t>>();
}
