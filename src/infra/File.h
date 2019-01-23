//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/string.h>
#include <stl/vector.h>
#include <stl/function.h>
#include <infra/Array.h>
#include <type/Forward.h>

namespace mud
{
	using cstring = const char*;

	export_ struct Filepath
	{
		string path;
		string name;
		string extension;
	};

	export_ MUD_INFRA_EXPORT vector<uint8_t> read_binary_file(const string& path);
	export_ MUD_INFRA_EXPORT string read_text_file(const string& path);

	export_ using LineVisitor = function<void(const string&)>;
	export_ MUD_INFRA_EXPORT void read_text_file(const string& path, LineVisitor visit_line);

	export_ MUD_INFRA_EXPORT void write_file(const string& path, const string& content);
	export_ MUD_INFRA_EXPORT void update_file(const string& path, const string& content);
	export_ MUD_INFRA_EXPORT void write_binary_file(const string& path, array<uint8_t> data);

	export_ MUD_INFRA_EXPORT void copy_file(const string& source, const string& dest);

	export_ MUD_INFRA_EXPORT string exec_path(int argc, char* argv[]);

	export_ MUD_INFRA_EXPORT bool file_exists(const string& path);
	export_ MUD_INFRA_EXPORT bool directory_exists(const string& path);
	export_ MUD_INFRA_EXPORT bool directory_contains(const string& path, const string& query);
	export_ MUD_INFRA_EXPORT string file_directory(const string& path);
	export_ MUD_INFRA_EXPORT string parent_directory(const string& path);

	export_ MUD_INFRA_EXPORT bool create_directory(const string& path);
	export_ MUD_INFRA_EXPORT bool create_directory_tree(const string& path);
	export_ MUD_INFRA_EXPORT bool create_file_tree(const string& path);
	
	export_ using FileVisitor = function<void(const string&, const string&)>;

	export_ MUD_INFRA_EXPORT void visit_files(const string& path, FileVisitor visit_file);
	export_ MUD_INFRA_EXPORT void visit_folders(const string& path, FileVisitor visit_folder, bool ignore_symbolic = true);

	inline string file_name(const string& path)
	{
		string directory = file_directory(path);
		return path.substr(directory.size() + 1);
	}

	inline string file_extension(const string& path)
	{
		return path.substr(path.rfind(".") + 1);
	}
}
