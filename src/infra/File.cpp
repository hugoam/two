//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <infra/Cpp20.h>
#include <dirent.h>
#else
#include <fstream>
#include <dirent.h>
#endif

#ifdef MUD_MODULES
module mud.obj;
#else
#include <infra/File.h>
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

	void visit_files(cstring path, FileVisitor visit_file)
	{
		DIR* dir = opendir(path);
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
			{
				visit_file(path, ent->d_name);
			}


		closedir(dir);
	}

	void visit_folders(cstring path, FileVisitor visit_file, bool ignore_symbolic)
	{
		DIR* dir = opendir(path);
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR)
			{
				bool is_symbolic = string(ent->d_name) == "." || string(ent->d_name) == "..";
				if(!is_symbolic || !ignore_symbolic)
					visit_file(path, ent->d_name);
			}

		closedir(dir);
	}

	void write_file(cstring path, cstring content)
	{
		std::ofstream out(path);
		out << content;
	}

}
