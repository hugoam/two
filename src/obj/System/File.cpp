//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>
#ifndef MUD_CPP_20
#include <fstream>
#endif

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/System/File.h>
#endif

namespace mud
{
	std::vector<uint8_t> read_binary_file(const string& path)
	{
		std::vector<uint8_t> buffer;
		std::ifstream file = std::ifstream(path, std::ios::binary);
		//buffer.resize(file.gcount());
		buffer.insert(buffer.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
		return buffer;
	}

	string read_text_file(const string& path)
	{
		std::ifstream file = std::ifstream(path);
		std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		return result;
	}
}
