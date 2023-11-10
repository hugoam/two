#include <two/infra.h>


#ifndef TWO_CPP_20
#include <cmath>
#endif

#ifdef TWO_MODULES
module two.infra;
#else
#endif

namespace two
{
	FreeListBase::Node* FreeListBase::init(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra)
	{
		void* const p = pointermath::align(begin, alignment, extra);
		void* const n = pointermath::align(pointermath::add(p, elementSize), alignment, extra);
		assert(p >= begin && p < end);
		assert(n >= begin && n < end && n > p);

		const size_t d = uintptr_t(n) - uintptr_t(p);
		const size_t num = (uintptr_t(end) - uintptr_t(p)) / d;

		// set first entry
		Node* head = static_cast<Node*>(p);

		// next entry
		Node* cur = head;
		for(size_t i = 1; i<num; ++i)
		{
			Node* next = pointermath::add(cur, d);
			cur->next = next;
			cur = next;
		}
		assert(cur < end);
		assert(pointermath::add(cur, d) <= end);
		cur->next = nullptr;
		return head;
	}

	FreeList::FreeList(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra)
		: m_head(init(begin, end, elementSize, alignment, extra))
#ifndef NDEBUG
		, m_begin(begin), m_end(end)
#endif
	{}

	AtomicFreeList::AtomicFreeList(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra)
		: m_head(init(begin, end, elementSize, alignment, extra))
	{}
}

#ifdef TWO_CPP_20
#include <dirent.h>
#else
#include <vector>
#include <string>
#include <fstream>
#include <dirent.h>
#undef min
#undef max
#undef near
#undef far
#undef NEAR
#undef FAR
#endif

#ifdef TWO_MODULES
module two.infra;
#else
#endif

#if defined _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

namespace two
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

	void write_binary_file(const string& path, span<uint8_t> data)
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
#ifndef USE_STL
		return vector<uint8_t>(buffer.data(), buffer.data() + buffer.size());
#else
		return buffer;
#endif
	}

	string read_text_file(const string& path)
	{
		std::ifstream file = std::ifstream(path.c_str());
		std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
#ifndef USE_STL
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
			if(!visit_line(line))
				return;
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
		//return std::fstream(path.c_str()).good();
#if defined WIN32
		struct _stat info;
		return _stat(path.c_str(), &info) == 0 && (info.st_mode & _S_IFMT) != 0;
#else 
		struct stat info;
		return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFMT) != 0;
#endif
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
#ifndef USE_STL
#ifdef TWO_MODULES
module two.infra;
#else
#include <stl/vector.hpp>
#endif

namespace stl
{
	using namespace two;
	template class TWO_INFRA_EXPORT vector<string>;
	template class TWO_INFRA_EXPORT vector<uchar>;
}
#endif


#ifdef TWO_MODULES
module two.infra;
#else
#include <stl/algorithm.h>
#endif

#include <cctype>
#include <cassert>

namespace two
{
	const size_t g_num_precision = 3;

	void split(const string& str, const string& separator, span<string> output)
	{
		size_t start = 0;
		size_t next = str.find(separator, start);

		size_t index = 0;
		while(next != string::npos && index < output.size())
		{
			assert(index < output.size());
			output[index++].assign(str.data() + start, next - start);
			start = next + 1;
			next = str.find(separator, start);
		}
		if(index < output.size())
			output[index++].assign(str.data() + start, str.size() - start);
	}

	vector<string> split(const string& str, const string& separator)
	{
		vector<string> result;
		
		if(str.size() == 0)
			return result;

		size_t cur_pos = 0;
		size_t last_pos = 0;

		while (cur_pos != string::npos)
		{
			cur_pos = str.find(separator, last_pos);
			result.push_back(str.substr(last_pos, cur_pos - last_pos));
			last_pos = cur_pos + separator.size();
		}

		return result;
	}

	string join(span<string> strings, string separator)
	{
		if(strings.size() == 0) return "";
		string result;
		for(const string& s : strings)
		{
			result += s;
			result += separator;
		}
		result.erase(result.size() - separator.size(), separator.size());
		return result;
	}

	string replace(const string& original, const string& before, const string& after)
	{
		if(before.empty()) return original;
		string retval;
		retval.reserve(original.size());

		size_t current = 0;
		size_t next = original.find(before, current);
		while(next != string::npos)
		{
			retval.append(original.begin() + current, original.begin() + next);
			retval.append(after);
			current = next + before.size();
			next = original.find(before, current);
		}
		retval.append(original.substr(current));
		return retval;
	}

	string to_lower(const string& original)
	{
		string result = original;
		transform(result.begin(), result.end(), result.begin(), [](char c) { return char(tolower(c)); });
		return result;
	}

	string to_upper(const string& original)
	{
		string result = original;
		transform(result.begin(), result.end(), result.begin(), [](char c) { return char(toupper(c)); });
		return result;
	}

	string to_pascalcase(const string& name)
	{
		string result = name;
		result[0] = char(::toupper(name[0]));
		for(size_t pos = result.find("_"); pos != string::npos; pos = result.find("_", pos))
		{
			result.erase(pos, 1);
			result[pos] = char(::toupper(result[pos]));
		}
		return result;
	}

	string to_camelcase(const string& name)
	{
		string result = name;
		for(size_t pos = result.find("_"); pos != string::npos; pos = result.find("_", pos))
		{
			result.erase(pos, 1);
			result[pos] = char(::toupper(result[pos]));
		}
		return result;
	}
}


#if !defined(WIN32)
#    include <pthread.h>
#endif

#ifdef ANDROID
#    include <sys/time.h>
#    include <sys/resource.h>
#    ifndef ANDROID_PRIORITY_URGENT_DISPLAY
#        define ANDROID_PRIORITY_URGENT_DISPLAY -8  // see include/system/thread_defs.h
#    endif
#    ifndef ANDROID_PRIORITY_DISPLAY
#        define ANDROID_PRIORITY_DISPLAY -4  // see include/system/thread_defs.h
#    endif
#    ifndef ANDROID_PRIORITY_NORMAL
#        define ANDROID_PRIORITY_NORMAL 0 // see include/system/thread_defs.h
#    endif
#elif defined(__linux__)
// There is no glibc wrapper for gettid on linux so we need to syscall it.
#    include <unistd.h>
#    include <sys/syscall.h>
#    define gettid() syscall(SYS_gettid)
#endif

#ifdef WIN32
//#include <Windows.h>
//#include <tchar.h>*
//#undef small
#endif


#ifdef TWO_MODULES
module two.infra;
#else
#endif

namespace two
{
	void set_thread_name(const char* name)
	{
#if defined(__linux__)
		pthread_setname_np(pthread_self(), name);
#elif defined(__APPLE__)
		pthread_setname_np(name);
#else
		UNUSED(name);
		// TODO: implement setting thread name on WIN32 
#endif
	}

	void set_thread_priority(ThreadPriority priority)
	{
#ifdef ANDROID
		int androidPriority = 0;
		switch(priority) {
		case Priority::NORMAL:
			androidPriority = ANDROID_PRIORITY_NORMAL;
			break;
		case Priority::DISPLAY:
			androidPriority = ANDROID_PRIORITY_DISPLAY;
			break;
		case Priority::URGENT_DISPLAY:
			androidPriority = ANDROID_PRIORITY_URGENT_DISPLAY;
			break;
		}
		setpriority(PRIO_PROCESS, 0, androidPriority);
#endif
		UNUSED(priority);
		//SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	}

	void set_thread_affinity(uint32_t mask)
	{
#if defined(__linux__)
		int bit = 0;
		cpu_set_t set;
		CPU_ZERO(&set);
		while(mask) {
			if(mask & 1) {
				CPU_SET(bit, &set);
			}
			bit++;
			mask >>= 1;
		}
		sched_setaffinity(gettid(), sizeof(set), &set);
#else
		UNUSED(mask);
		//SetThreadAffinityMask(GetCurrentThread(), mask);
#endif
	}
}

#ifdef TWO_MODULES
module two.infra;
#else
#endif

#include <cstdio>

namespace two
{
	template <> void to_string(const bool&    value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const char&    value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const schar&   value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const uchar&   value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> void to_string(const short&   value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const int&     value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const long&    value, string& str) { str.resize(snprintf(nullptr, 0, "%ld",  value)); sprintf(&str[0], "%ld",  value); }
	template <> void to_string(const llong&   value, string& str) { str.resize(snprintf(nullptr, 0, "%lld", value)); sprintf(&str[0], "%lld", value); }
	template <> void to_string(const ushort&  value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> void to_string(const uint&    value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> void to_string(const ulong&   value, string& str) { str.resize(snprintf(nullptr, 0, "%lu",  value)); sprintf(&str[0], "%lu",  value); }
	template <> void to_string(const ullong&  value, string& str) { str.resize(snprintf(nullptr, 0, "%llu", value)); sprintf(&str[0], "%llu", value); }
	template <> void to_string(const float&   value, string& str) { str.resize(snprintf(nullptr, 0, "%f",   value)); sprintf(&str[0], "%f",   value); }
	template <> void to_string(const double&  value, string& str) { str.resize(snprintf(nullptr, 0, "%f",   value)); sprintf(&str[0], "%f",   value); }
	template <> void to_string(const ldouble& value, string& str) { str.resize(snprintf(nullptr, 0, "%Lf",  value)); sprintf(&str[0], "%Lf",  value); }
}

#ifdef TWO_MODULES
module two.infra;
#else
#endif

#include <cstdlib>

namespace two
{
#ifndef USE_STL
	template <> void to_value(const string& str, bool& val) { val = atoi(str.c_str()) != 0; } //str == "true" ? true : false; }
	template <> void to_value(const string& str, char& val) { val = char(atoi(str.c_str())); }
	template <> void to_value(const string& str, schar& val) { val = schar(atoi(str.c_str())); }
	template <> void to_value(const string& str, short& val) { val = short(atoi(str.c_str())); }
	template <> void to_value(const string& str, int& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, long& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, llong& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, uchar& val) { val = uchar(atoi(str.c_str())); }
	template <> void to_value(const string& str, ushort& val) { val = ushort(atoi(str.c_str())); }
	template <> void to_value(const string& str, uint& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, ulong& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, ullong& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, float& val) { val = float(atof(str.c_str())); }
	template <> void to_value(const string& str, double& val) { val = atof(str.c_str()); } //sscanf(str.c_str(), "%lf", &val); }
	template <> void to_value(const string& str, ldouble& val) { val = atof(str.c_str()); }
#else
	template <> void to_value(const string& str, bool& val) { val = std::stoi(str) != 0; } //str == "true" ? true : false; }
	template <> void to_value(const string& str, char& val) { val = char(std::stoi(str)); }
	template <> void to_value(const string& str, schar& val) { val = schar(std::stoi(str)); }
	template <> void to_value(const string& str, short& val) { val = short(std::stoi(str)); }
	template <> void to_value(const string& str, int& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, long& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, llong& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, uchar& val) { val = uchar(std::stoi(str)); }
	template <> void to_value(const string& str, ushort& val) { val = ushort(std::stoi(str)); }
	template <> void to_value(const string& str, uint& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, ulong& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, ullong& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, float& val) { val = std::stof(str); }
	template <> void to_value(const string& str, double& val) { val = std::stod(str); }
	template <> void to_value(const string& str, ldouble& val) { val = std::stod(str); }
#endif
}
