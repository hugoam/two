//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/function.h>
#include <stl/span.h>
#include <infra/Forward.h>

namespace two
{
	using cstring = const char*;

	export_ struct Filepath
	{
		string path;
		string name;
		string extension;
	};

	export_ TWO_INFRA_EXPORT vector<uint8_t> read_binary_file(const string& path);
	export_ TWO_INFRA_EXPORT string read_text_file(const string& path);

	export_ using LineVisitor = function<bool(const string&)>;
	export_ TWO_INFRA_EXPORT void read_text_file(const string& path, LineVisitor visit_line);

	export_ TWO_INFRA_EXPORT void write_file(const string& path, const string& content);
	export_ TWO_INFRA_EXPORT void update_file(const string& path, const string& content);
	export_ TWO_INFRA_EXPORT void write_binary_file(const string& path, span<uint8_t> data);

	export_ TWO_INFRA_EXPORT void copy_file(const string& source, const string& dest);

	export_ TWO_INFRA_EXPORT string exec_path(int argc, char* argv[]);

	export_ TWO_INFRA_EXPORT bool file_exists(const string& path);
	export_ TWO_INFRA_EXPORT bool directory_exists(const string& path);
	export_ TWO_INFRA_EXPORT bool is_subpath(const string& path, const string& dir);
	export_ TWO_INFRA_EXPORT string relative_to(const string& path, const string& dir);
	export_ TWO_INFRA_EXPORT string file_directory(const string& path);
	export_ TWO_INFRA_EXPORT string parent_directory(const string& path);

	export_ TWO_INFRA_EXPORT bool create_directory(const string& path);
	export_ TWO_INFRA_EXPORT bool create_directory_tree(const string& path);
	export_ TWO_INFRA_EXPORT bool create_file_tree(const string& path);
	
	export_ using FileVisitor = function<void(const string&)>;

	export_ TWO_INFRA_EXPORT void visit_files(const string& path, FileVisitor visit_file);
	export_ TWO_INFRA_EXPORT void visit_folders(const string& path, FileVisitor visit_folder, bool ignore_symbolic = true);

	export_ TWO_INFRA_EXPORT void visit_files_recursive(const string& path, FileVisitor visit_file, const string& prefix = "");

	inline string file_name(const string& path)
	{
		string directory = file_directory(path);
		return path.substr(directory.size() + 1);
	}

	inline string file_label(const string& path)
	{
		string directory = file_directory(path);
		return path.substr(directory.size() + 1, path.rfind(".") + 1);
	}

	inline string file_noext(const string& path)
	{
		return path.substr(0, path.rfind("."));
	}

	inline string file_extension(const string& path)
	{
		return path.substr(path.rfind(".") + 1);
	}
}
