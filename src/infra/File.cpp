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
module mud.infra;
#else
#include <infra/File.h>
#endif

#if defined _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
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
		string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		return result;
	}

	bool directory_exists(cstring path)
	{
#if defined WIN32
		struct _stat info;
		return _stat(path, &info) == 0 && (info.st_mode & _S_IFDIR) != 0;
#else 
		struct stat info;
		return stat(path, &info) == 0 && (info.st_mode & S_IFDIR) != 0;
#endif
	}

	string file_directory(cstring path)
	{
		string directory = path;
		size_t separator = directory.rfind("/");
#ifdef WIN32
		size_t backslash = directory.rfind("\\");
		separator = (backslash != string::npos && backslash > separator) ? backslash : separator;
#endif
		return directory.substr(0, separator);
	}

	bool create_directory(cstring path)
	{
#ifdef WIN32
		return 0 == _mkdir(path);
		//CreateDirectory(path, NULL);
		//return ERROR_SUCCESS == GetLastError();
#else
		mode_t mode = 0755;
		return 0 == mkdir(path, mode);
#endif
	}

	bool create_directory_tree(cstring path)
	{
		string parent = file_directory(path);
		if(!directory_exists(parent.c_str()))
		{
			bool success = create_directory_tree(parent.c_str());
			if(!success) return false;
		}
		return create_directory(path);
	}

	bool create_file_tree(cstring path)
	{
		string directory = file_directory(path);
		if(!directory_exists(directory.c_str()))
			return create_directory_tree(directory.c_str());
		else
			return true;
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
