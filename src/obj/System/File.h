//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#endif

namespace mud
{
	using string = std::string;

	export_ struct Filepath
	{
		string path;
		string name;
		string extension;
	};

	export_ MUD_OBJ_EXPORT std::vector<uint8_t> read_binary_file(const string& path);
	export_ MUD_OBJ_EXPORT string read_text_file(const string& path);
}
