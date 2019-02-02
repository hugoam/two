//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#define ENFORCE_STL_INITIALIZER_LIST
#ifdef MUD_CPP_20
#include <infra/Cpp20.h>
#include <dirent.h>
#else
#include <vector>
#include <string>
#include <fstream>
#include <dirent.h>
#undef min
#undef max
#endif

#ifdef MUD_MODULES
module mud.infra;
#else
#include <infra/File.h>
#include <infra/String.h>
#endif

#if defined _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

namespace mud
{
	void copy_file(const string& source, const string& dest)
	{
		std::ifstream source_file(source.c_str(), std::ios::binary);
		std::ofstream dest_file(dest.c_str(), std::ios::binary);
		dest_file << source_file.rdbuf();
	}

	void write_file(const string& path, const string& content)
	{
		std::ofstream out(path.c_str());
		out << content.c_str();
	}

	void update_file(const string& path, const string& content)
	{
		string current = read_text_file(path);
		if(content != current)
			write_file(path, content);
	}

	void write_binary_file(const string& path, array<uint8_t> data)
	{
		std::ofstream file(path.c_str(), std::ios::out | std::ios::binary);
		file.write((const char*)data.data(), data.size());
	}

	vector<uint8_t> read_binary_file(const string& path)
	{
		std::vector<uint8_t> buffer;
		std::ifstream file = std::ifstream(path.c_str(), std::ios::binary);
		buffer.resize(file.gcount());
		buffer.insert(buffer.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
#ifdef MUD_NO_STL
		return vector<uint8_t>(buffer.data(), buffer.data() + buffer.size());
#else
		return buffer;
#endif
	}

	string read_text_file(const string& path)
	{
		std::ifstream file = std::ifstream(path.c_str());
		std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
#ifdef MUD_NO_STL
		return string(result.data(), result.data() + result.size());
#else
		return result;
#endif
	}

	void read_text_file(const string& path, LineVisitor visit_line)
	{
		std::ifstream file = std::ifstream(path.c_str());
		if(!file.good()) return;

		std::string stdline;
		while(std::getline(file, stdline))
		{
			string line = { stdline.data(), stdline.data() + stdline.size() };
			if(line.back() == '\r') line.pop_back();
			visit_line(line);
		}
	}

	string exec_path(int argc, char* argv[])
	{
#ifdef _WIN32
		UNUSED(argc);
		string exec_path = argv[0];
		string exec_dir = exec_path.substr(0, exec_path.rfind("\\"));
#else
		UNUSED(argc); UNUSED(argv);
		string exec_dir = "./";
#endif
		return exec_dir;
	}

	bool file_exists(const string& path)
	{
		return std::fstream(path.c_str()).good();
	}

	bool directory_exists(const string& path)
	{
#if defined WIN32
		struct _stat info;
		return _stat(path.c_str(), &info) == 0 && (info.st_mode & _S_IFDIR) != 0;
#else 
		struct stat info;
		return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR) != 0;
#endif
	}

	string fix_path(const string& path)
	{
		return replace(path, "\\", "/");
	}

	string closed_path(const string& path)
	{
		// closed path is useful to do string compare on the tree structure
		// e.g foo/subpath would be seen as a child of foo/sub but clearly not a child of foo/sub/
		string clean = replace(path, "\\", "/");
		return clean + (clean.back() == '/' ? "" : "/");
	}

	bool is_subpath(const string& path, const string& dir)
	{
		return fix_path(path).find(closed_path(dir)) == 0;
	}

	string relative_to(const string& path, const string& dir)
	{
		return fix_path(path).substr(closed_path(dir).size());
	}

	string file_directory(const string& path)
	{
		string directory = path;
		size_t separator = directory.rfind("/");
#ifdef WIN32
		size_t backslash = directory.rfind("\\");
		separator = (backslash != string::npos && backslash > separator) ? backslash : separator;
#endif
		return directory.substr(0, separator);
	}

	string parent_directory(const string& path)
	{
		if(path.back() == '/' || path.back() == '\\')
			return file_directory(path.substr(0, path.size() - 1));
		else
			return file_directory(path);
	}

	bool create_directory(const string& path)
	{
#ifdef WIN32
		return 0 == _mkdir(path.c_str());
		//CreateDirectory(path, NULL);
		//return ERROR_SUCCESS == GetLastError();
#else
		mode_t mode = 0755;
		return 0 == mkdir(path.c_str(), mode);
#endif
	}

	bool create_directory_tree(const string& path)
	{
		string parent = file_directory(path);
		if(!directory_exists(parent))
		{
			bool success = create_directory_tree(parent);
			if(!success) return false;
		}
		return create_directory(path);
	}

	bool create_file_tree(const string& path)
	{
		string directory = file_directory(path);
		if(!directory_exists(directory))
			return create_directory_tree(directory);
		else
			return true;
	}

	void visit_files(const string& path, FileVisitor visit)
	{
		DIR* dir = opendir(path.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_REG)
			{
				visit(ent->d_name);
			}

		closedir(dir);
	}

	void visit_folders(const string& path, FileVisitor visit, bool ignore_symbolic)
	{
		DIR* dir = opendir(path.c_str());
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR)
			{
				bool is_symbolic = string(ent->d_name) == "." || string(ent->d_name) == "..";
				if(!is_symbolic || !ignore_symbolic)
					visit(ent->d_name);
			}

		closedir(dir);
	}

	void visit_files_recursive(const string& path, FileVisitor visit, const string& prefix)
	{
		string suffix = prefix == "" ? "" : "/" + prefix;

		auto visit_file = [&](const string& file)
		{
			visit(prefix + file);
		};

		auto visit_folder = [&](const string& folder)
		{
			visit_files_recursive(path + suffix, visit_file, folder + "/");
		};

		visit_files(path + suffix, visit_file);
		visit_folders(path + suffix, visit_folder);
	}
}
