//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

#ifndef MUD_CPP_20
#include <cstring>
#include <string>
#endif

namespace mud
{
	export_ using cstring = const char*;
	export_ using string = std::string;
}
