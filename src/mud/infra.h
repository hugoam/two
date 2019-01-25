#pragma once

//#include <mud/type.h>






#if defined _MSC_VER
#	pragma warning (disable : 4201) // anonymous structs are supported by all target compilers
#	pragma warning (disable : 4251) // members are private, so there's no risk them being accessed by the user
#	pragma warning (disable : 4577) // mud doesn't use exceptions

#ifdef MUD_CPP_20
#	pragma warning (disable : 4996) // with c++20 modules we can't pass _CRT_SECURE_NO_WARNINGS
// these are warnings in the experimental Visual Studio std module
#	pragma warning (disable : 4530) 
#	pragma warning (disable : 4127)
#	pragma warning (disable : 4100)
#	pragma warning (disable : 4244)
#	pragma warning (disable : 4522)
#endif

#endif


#ifndef MUD_META_GENERATOR
#define refl_   // Reflect
#define struct_ // Struct
#define nocopy_ // Nocopy type
#define array_	// Array type
#define extern_ // Extern type
#define comp_   // Component
#define constr_ // Constructor
#define meth_   // Method
#define func_   // Function
#define attr_   // Attribute
#define nomut_  // Non Mutable Attribute
#define graph_  // Graph / Structure Attribute
#define link_   // Link / Reference Attribute
#define pool_   // Pool Attribute
#endif

#if defined _WIN32 || defined __CYGWIN__
	#if defined __GNUC__
		#define MUD_EXPORT __attribute__ ((dllexport))
		#define MUD_IMPORT __attribute__ ((dllimport))
	#else
		#define MUD_EXPORT __declspec(dllexport)
		#define MUD_IMPORT __declspec(dllimport)
	#endif
	#define DLL_LOCAL
#elif __GNUC__ >= 4
	#define MUD_EXPORT __attribute__ ((visibility ("default")))
	#define MUD_IMPORT
	#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
	#define MUD_EXPORT
	#define MUD_IMPORT
	#define DLL_LOCAL
#endif

#ifdef MUD_STATIC
#undef MUD_IMPORT
#define MUD_IMPORT
#endif

#define MUD_FUNC_EXPORT __cdecl

#define UNUSED(x) (void)(x)

#if defined _MSC_VER && _MSC_VER >= 1914
//#define MUD_MODULES
#endif

#ifdef MUD_MODULES
#define export_ export
#undef MUD_EXPORT
#define MUD_EXPORT
#else
#define export_ 
#endif

#ifndef MUD_INFRA_EXPORT
#define MUD_INFRA_EXPORT MUD_IMPORT
#endif

#ifndef MUD_CPP_20
#include <cstddef>
#include <cstdint>
#include <cassert>
#endif

namespace mud
{
	using cstring = const char*;

	template <typename T>
	struct array;

	export_ template <class T, size_t Size>
	struct carray
	{
		template <class... T_Args>
		carray(T_Args... args) : m_array{ T(args)... } {}
		T m_array[Size];
		size_t size() { return Size; }
		T* data() { return m_array; }
		T& operator[](size_t at) { return m_array[at]; }
		const T& operator[](size_t at) const { return m_array[at]; }
		operator array<T>() { return{ m_array, Size }; }
	};

	template <class... T_Args, size_t size = sizeof...(T_Args)>
	carray<cstring, size> cstrarray(T_Args... args) { return carray<cstring, size>{ args... }; }

	template <class... T_Args, size_t size = sizeof...(T_Args)>
	carray<cstring, size> strarray(T_Args... args) { return carray<cstring, size>{ args.c_str()... }; }

	export_ template <typename T>
	struct refl_ struct_ array
	{
	public:
		array() : m_pointer(nullptr), m_count(0) {}
		array(T* pointer, size_t count) : m_pointer(pointer), m_count(count) {}
		array(array<T> other, size_t offset) : m_pointer(other.m_pointer + offset), m_count(other.m_count - offset) {}
		array(array<T> other, size_t offset, size_t count) : m_pointer(other.m_pointer + offset), m_count(count) {}
		template <size_t size>
		array(T(&a)[size]) : m_pointer(a), m_count(size) {}
		template <class U>
		array(U& container) : m_pointer(container.data()), m_count(container.size()) {}

		size_t size() { return m_count; }
		T* data() const { return m_pointer; }

		T& operator[](size_t at) { assert(at < m_count); return m_pointer[at]; }
		const T& operator[](size_t at) const { assert(at < m_count); return m_pointer[at]; }

		T* begin() { return m_pointer; }
		T* end() { return m_pointer + m_count; }
		const T* begin() const { return m_pointer; }
		const T* end() const { return m_pointer + m_count; }

		T* m_pointer;
		size_t m_count;
	};

	export_ template<typename T> class array2d : public array<T>
	{
	public:
		array2d(T* pointer, size_t size_x, size_t size_y) : array<T>(pointer, size_x * size_y), m_x(size_x), m_y(size_y) {}
		
		size_t m_x;
		size_t m_y;

		inline T& at(size_t x, size_t y) { return (*this)[x+y*m_x]; }
		inline const T& at(size_t x, size_t y) const { return (*this)[x+y*m_x]; }
	};
}
#ifdef MUD_CPP_20

#include <cassert>
#include <cstdint>
#include <cfloat>
#include <climits>
//#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <cstdlib>

import std.core;
import std.threading;
import std.regex;
#ifdef _MSC_VER
import std.memory; // std.memory exists only in Visual Studio experimental modules
#else
import std.io;
#endif
#endif


#ifndef MUD_CPP_20
#include <cstdint>
#endif

namespace mud
{
	export_ template <class T_Enum, class T_Element, size_t Size = size_t(T_Enum::Count)>
	using enum_array = T_Element[Size];
}


#include <stl/string.h>
#include <stl/vector.h>
#include <stl/function.h>

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
	export_ MUD_INFRA_EXPORT bool is_subpath(const string& path, const string& dir);
	export_ MUD_INFRA_EXPORT string relative_to(const string& path, const string& dir);
	export_ MUD_INFRA_EXPORT string file_directory(const string& path);
	export_ MUD_INFRA_EXPORT string parent_directory(const string& path);

	export_ MUD_INFRA_EXPORT bool create_directory(const string& path);
	export_ MUD_INFRA_EXPORT bool create_directory_tree(const string& path);
	export_ MUD_INFRA_EXPORT bool create_file_tree(const string& path);
	
	export_ using FileVisitor = function<void(const string&)>;

	export_ MUD_INFRA_EXPORT void visit_files(const string& path, FileVisitor visit_file);
	export_ MUD_INFRA_EXPORT void visit_folders(const string& path, FileVisitor visit_folder, bool ignore_symbolic = true);

	export_ MUD_INFRA_EXPORT void visit_files_recursive(const string& path, FileVisitor visit_file, const string& prefix = "");

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


#ifndef MUD_INFRA_EXPORT
#define MUD_INFRA_EXPORT MUD_IMPORT
#endif

namespace mud
{
	using uchar = unsigned char;
	using ushort = unsigned short;
	using uint = unsigned int;
	using ulong = unsigned long;
	using ullong = unsigned long long;
	using llong = long long;
	using ddouble = long double;

    template <class T> struct array;
    
    struct Filepath;
    struct swallow;
    class NonCopy;
    class Movabl;
}



namespace mud
{
	struct swallow {
		template<typename... T> swallow(T...) {}
	};
}



namespace mud
{
	export_ template <class T>
	class Global
	{
	public:
		static T me;
	};

	template <class T>
	T Global<T>::me;

	export_ template <class T>
	class LazyGlobal
	{
	public:
		static T& me() { static T instance; return instance; }
	};
}


#include <stl/limits.h>

#ifndef MUD_CPP_20
#include <cstdint>
#endif



namespace mud
{
	export_ class MUD_INFRA_EXPORT NonCopy
	{
	public:
		NonCopy() {}
		NonCopy(const NonCopy&) = delete;
		NonCopy& operator=(const NonCopy&) = delete;
	};

	export_ class MUD_INFRA_EXPORT Movabl
	{
	public:
		Movabl() {}
		Movabl(const Movabl&) = delete;
		Movabl& operator=(const NonCopy&) = delete;
		Movabl(Movabl&& other) = default;
		Movabl& operator=(Movabl&& other) = default;
	};
}
//#include <infra/Pool.h>


#include <stl/vector.h>

namespace mud
{
#ifdef MUD_NO_STL
	template<class T>
	class reverse_pointer
	{
	public:
		using pointer = T*;
		using reference = T&;

		reverse_pointer() : m_ptr() {}
		explicit reverse_pointer(T* other) : m_ptr(other) {}

		reference operator*() const
		{
			T* temp = m_ptr;
			return *--temp;
		}

		pointer operator->() const
		{
			T* temp = m_ptr;
			--temp;
			return temp;
		}

		reverse_pointer& operator++() { --m_ptr; return *this; }
		reverse_pointer operator++(int) { reverse_pointer temp = *this; --m_ptr; return temp; }

		reverse_pointer& operator--() { ++m_ptr; return *this; }
		reverse_pointer operator--(int) { reverse_pointer temp = *this; ++m_ptr; return temp; }

		reverse_pointer& operator+=(size_t offset) { m_ptr -= offset; return *this; }
		reverse_pointer& operator-=(size_t offset) { m_ptr += offset; return *this; }
		reverse_pointer operator+(size_t offset) const { return reverse_pointer(m_ptr - offset); }
		reverse_pointer operator-(size_t offset) const { return reverse_pointer(m_ptr + offset); }

		reference operator[](size_t offset) const { return *(*this + offset); }

		T* m_ptr;
	};

	template<class T1, class T2>
	bool operator==(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return left.m_ptr == right.m_ptr; }

	template<class T1, class T2>
	bool operator!=(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return !(left == right); }

	template<class T1, class T2>
	bool operator<(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return right.m_ptr < left.m_ptr; }

	template<class T1, class T2>
	bool operator>(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return right < left; }

	template<class T1, class T2>
	bool operator<=(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return !(right < left); }

	template<class T1, class T2>
	bool operator>=(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return !(left < right); }
#endif

	export_ template<typename T>
	class reverse_adapter
	{
	public:
		reverse_adapter(T& container) : m_container(container) { }
		reverse_adapter& operator=(const reverse_adapter&) = delete;

#ifdef MUD_NO_STL
		using iterator = reverse_pointer<typename T::value_type>;
		iterator begin() { return iterator(m_container.end()); }
		iterator end() { return iterator(m_container.begin()); }
#else
		typename T::reverse_iterator begin() { return m_container.rbegin(); }
		typename T::reverse_iterator end() { return m_container.rend(); }
#endif
	private:
		T& m_container;
	};

	export_ template<typename T>
	reverse_adapter<T> reverse_adapt(T& container) { return reverse_adapter<T>(container); }
}


#include <stl/string.h>
#include <stl/vector.h>

namespace mud
{
	export_ using cstring = const char*;

	export_ template <class T>
	struct StringConverter;

	export_ template <class T>
	inline void to_value(const string& str, T& val);

	export_ template <class T>
	inline void to_string(const T& val, string& str);

	export_ template <class T>
	inline T to_value(const string& str) { T val; to_value<T>(str, val); return val; }

	export_ template <class T>
	inline string to_string(const T& val) { string str; to_string<T>(val, str); return str; }

	// string - string conversion
	export_ template <> inline void to_value<cstring>(const string& str, cstring& val) { val = str.c_str(); }
	export_ template <> inline void to_string<cstring>(const cstring& val, string& str) { str = val; }
	export_ template <> inline void to_value<string>(const string& str, string& val) { val = str; }
	export_ template <> inline void to_string<string>(const string& val, string& str){ str = val; }

	export_ MUD_INFRA_EXPORT void split(const string& str, const string& separator, array<string> output);
	export_ MUD_INFRA_EXPORT vector<string> split(const string& str, const string& separator);

	//export_ MUD_INFRA_EXPORT string join(array<string> strings, string separator);
	export_ MUD_INFRA_EXPORT string join(const vector<string>& strings, string separator);

	export_ MUD_INFRA_EXPORT string replace(const string& original, const string& before, const string& after);

	export_ MUD_INFRA_EXPORT string to_lower(const string& original);
	export_ MUD_INFRA_EXPORT string to_upper(const string& original);
	export_ MUD_INFRA_EXPORT string to_pascalcase(const string& name);
	export_ MUD_INFRA_EXPORT string to_camelcase(const string& name);

	export_ inline bool starts_with(const string& s, const string& start) { return s.size() >= start.size() && (s.find(start) == 0); };
	export_ inline bool ends_with(const string& s, const string& end) { return s.size() >= end.size() && (s.rfind(end) == (s.size() - end.size())); };

	extern MUD_INFRA_EXPORT const size_t g_num_precision; // = 3;

	export_ inline string truncate_number(const string& str)
	{
		// @todo use snprintf ?
		size_t dot = str.find(".");
		if(dot == string::npos) return str;
		string result = str;
		while(result.size() > 1 + dot + g_num_precision || (result.size() > 1 + dot + 1 && result.back() == '0'))
			result.pop_back();
		return result;
	}
}





namespace mud
{
	using schar = signed char;
	using uchar = unsigned char;
	using ushort = unsigned short;
	using uint = unsigned int;
	using ulong = unsigned long;
	using ullong = unsigned long long;
	using llong = long long;
	using ldouble = long double;
}

#include <cstdio>

namespace mud
{
	template <> inline void to_string(const bool&    value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> inline void to_string(const char&    value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> inline void to_string(const schar&   value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> inline void to_string(const uchar&   value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> inline void to_string(const int&     value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> inline void to_string(const long&    value, string& str) { str.resize(snprintf(nullptr, 0, "%ld",  value)); sprintf(&str[0], "%ld",  value); }
	template <> inline void to_string(const llong&   value, string& str) { str.resize(snprintf(nullptr, 0, "%lld", value)); sprintf(&str[0], "%lld", value); }
	template <> inline void to_string(const ushort&  value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> inline void to_string(const uint&    value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> inline void to_string(const ulong&   value, string& str) { str.resize(snprintf(nullptr, 0, "%lu",  value)); sprintf(&str[0], "%lu",  value); }
	template <> inline void to_string(const ullong&  value, string& str) { str.resize(snprintf(nullptr, 0, "%llu", value)); sprintf(&str[0], "%llu", value); }
	template <> inline void to_string(const float&   value, string& str) { str.resize(snprintf(nullptr, 0, "%f",   value)); sprintf(&str[0], "%f",   value); }
	template <> inline void to_string(const double&  value, string& str) { str.resize(snprintf(nullptr, 0, "%f",   value)); sprintf(&str[0], "%f",   value); }
	template <> inline void to_string(const ldouble& value, string& str) { str.resize(snprintf(nullptr, 0, "%Lf",  value)); sprintf(&str[0], "%Lf",  value); }
}



#include <cstdlib>

namespace mud
{
#ifdef MUD_NO_STL
	export_ template <> inline void to_value(const string& str, bool& val) { val = atoi(str.c_str()) != 0; } //str == "true" ? true : false; }
	export_ template <> inline void to_value(const string& str, float& val) { val = float(atof(str.c_str())); }
	export_ template <> inline void to_value(const string& str, double& val) { sscanf(str.c_str(), "%lf", &val); }
	export_ template <> inline void to_value(const string& str, char& val) { val = char(atoi(str.c_str())); }
	export_ template <> inline void to_value(const string& str, short& val) { val = short(atoi(str.c_str())); }
	export_ template <> inline void to_value(const string& str, int& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, long& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, llong& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, uchar& val) { val = uchar(atoi(str.c_str())); }
	export_ template <> inline void to_value(const string& str, ushort& val) { val = ushort(atoi(str.c_str())); }
	export_ template <> inline void to_value(const string& str, uint& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, ulong& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, ullong& val) { val = atoi(str.c_str()); }
#else
	export_ template <> inline void to_value(const string& str, bool& val) { val = std::stoi(str) != 0; } //str == "true" ? true : false; }
	export_ template <> inline void to_value(const string& str, float& val) { val = std::stof(str); }
	export_ template <> inline void to_value(const string& str, double& val) { val = std::stod(str); }
	export_ template <> inline void to_value(const string& str, char& val) { val = char(std::stoi(str)); }
	export_ template <> inline void to_value(const string& str, short& val) { val = short(std::stoi(str)); }
	export_ template <> inline void to_value(const string& str, int& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, long& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, llong& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, uchar& val) { val = uchar(std::stoi(str)); }
	export_ template <> inline void to_value(const string& str, ushort& val) { val = ushort(std::stoi(str)); }
	export_ template <> inline void to_value(const string& str, uint& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, ulong& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, ullong& val) { val = std::stoi(str); }
#endif
}


#include <stl/vector.h>
#include <stl/type_traits.h>

namespace mud
{
	// vector - string conversion
	export_ template <class T>
	inline void vector_to_string(const T& val, string& str)
	{
		for(const typename T::value_type& v : val)
		{
			str += to_string(v, str);
			str += ",";
		}
		if(val.size() > 0)
			str.pop_back();
	}
	
	export_ template <typename T>
	struct is_vector : false_type {};
	
	export_ template <typename T>
	struct is_vector<vector<T>> : true_type {};

#if 0
	export_ template <class T>
	inline typename enable_if<is_vector<T>::value, void>::type
		to_string(const T& val, string& str) { vector_to_string(val, str); }
#endif

	export_ template <class T>
	inline void string_to_vector(const string& str, T& vec)
	{
		size_t first = 0;
		size_t second = str.find(",");
		const size_t end = str.size();

		while(second != end)
		{
			second = str.find(",", first);
			vec.push_back(to_value<typename T::value_type>(str.substr(first, second - first)));
			
			if(second != end)
				first = second + 1;
		}
	}

	export_ template <class T, uint32_t size>
	inline void fixed_vector_to_string(const T& val, string& str)
	{
		for(uint32_t i = 0; i < size; ++i)
		{
			str += to_string(val[i]);
			str += ",";
		}
		str.pop_back();
	}

	export_ template <class Vec, class T>
	inline void string_to_fixed_vector(const string& str, Vec& vec)
	{
		size_t first = 0;
		size_t second = str.find(",");
		const size_t end = str.size();

		uint32_t i = 0;
		while(second != end)
		{
			second = str.find(",", first);
			vec[i] = to_value<T>(str.substr(first, second - first));

			++i;
			if(second != end)
				first = second + 1;
		}
	}

	export_ template <class T>
	struct StringConverter
	{
		static inline void to(const T& val, string& str) { UNUSED(val); UNUSED(str); }
		static inline void from(const string& str, T& val) { UNUSED(str); UNUSED(val); }
	};

	export_ template <class T>
	struct StringConverter<vector<T>>
	{
		static inline void to(const vector<T>& val, string& str) { vector_to_string(val, str); }
		static inline void from(const string& str, vector<T>& vec) { string_to_vector(str, vec); }
	};

#if 0
	export_ template <class T, size_t s>
	struct StringConverter<carray<T, s>>
	{
		static inline void to(const std::array<T, s>& val, string& str) { fixed_vector_to_string<carray<T, s>, s>(val, str); }
		static inline void from(const string& str, std::array<T, s>& vec) { string_to_fixed_vector<carray<T, s>, T>(str, vec); }
	};
#endif

	export_ template <class T_Enum>
	inline void flags_from_string(const string& str, T_Enum& value)
	{
		vector<string> names = split(to_upper(str), "|");
		for(const string& name : names)
			value = static_cast<T_Enum>(value | to_value<T_Enum>(name));
	}

	export_ template <class T_Enum>
	inline T_Enum flags_from_string(const string& str) { T_Enum value = T_Enum(0); flags_from_string(str, value); return value; }

	export_ template <class T_Enum, size_t Count>
	inline void flags_to_string(const T_Enum& value, string& str)
	{
		for(size_t shift = 0; shift < Count; ++shift)
			if(value & (1 << shift))
				str += (str.empty() ? "" : "|") + to_string<T_Enum>(static_cast<T_Enum>((1 << shift)));
	}

	export_ template <class T_Enum, size_t Count>
	inline string flags_to_string(const T_Enum& value) { string str; flags_to_string<T_Enum, Count>(value, str); return str; }

	export_ template <class T>
	inline void to_value(const string& str, T& val) { StringConverter<T>::from(str, val); }

	export_ template <class T>
	inline void to_string(const T& val, string& str) { StringConverter<T>::to(val, str); }
}


#include <cstddef>
#include <cstdint>

namespace mud
{
	export_ MUD_INFRA_EXPORT void set_thread_name(const char* name);

	export_ enum class ThreadPriority
	{
		Normal,
		Display,
		UrgentDisplay
	};

	export_ MUD_INFRA_EXPORT void set_thread_priority(ThreadPriority priority);
	export_ MUD_INFRA_EXPORT void set_thread_affinity(uint32_t mask);
}


#ifndef MUD_CPP_20
#include <stl/type_traits.h>
#include <cstring>
#endif

#if defined __GNUC__
#   pragma GCC system_header
#endif

namespace mud
{
	export_ template <typename T>
	struct is_function_pointer : integral_constant<bool, is_pointer<T>::value
													  && is_function<typename remove_pointer<T>::type>::value> {};

	export_ template <typename T>
	struct is_object_pointer : integral_constant<bool, is_pointer<T>::value
													&& !is_function_pointer<T>::value> {};

	export_ template <typename T, typename = void>
	struct is_comparable_base : false_type {};

	export_ template <typename T>
	struct is_comparable_base<T, decltype(std::declval<T&>() == std::declval<T&>(), (void) 0)> : true_type {};

	export_ template <typename T>
	struct is_comparable : is_comparable_base<T> {};

	export_ template <typename T>
	struct is_copyable : integral_constant<bool, is_copy_constructible<T>::value
											  && is_copy_assignable<T>::value> {};
}


#include <stl/vector.h>
#include <stl/algorithm.h>

namespace mud
{
	template <typename T>
	struct is_comparable<vector<T>> : is_comparable_base<T> {};

	export_ template <class T>
	array<T> to_array(vector<T>& vec) { return { &vec[0], vec.size() }; }
	export_ template <class T>
	array<T> to_array(vector<T>& vec, size_t offset) { return { &vec[offset], vec.size() - offset }; }
	export_ template <class T>
	array<T> to_array(vector<T>& vec, size_t offset, size_t count) { return { &vec[offset], count }; }

	template <class T, class U>
	array<T> to_array_cast(vector<U>& vec) { return{ (T*)&vec[0], vec.size() }; }

	export_ template <class T>
	vector<T> to_vector(const array<T>& array) { return { array.m_pointer, array.m_pointer + array.m_count }; }

	export_ template <class T>
	inline void vector_extend(vector<T>& vec, const vector<T>& other)
	{
		vec.insert(vec.end(), other.begin(), other.end());
	}
	
	export_ template <class T>
	inline void vector_prepend(vector<T>& vec, const T& value)
	{
		vec.insert(vec.begin(), value);
	}

	export_ template <class T>
	inline void vector_prepend(vector<T>& vec, const vector<T>& other)
	{
		vec.insert(vec.begin(), other.begin(), other.end());
	}

	export_ template <class T>
	inline vector<T> vector_union(const vector<T>& first, const vector<T>& second)
	{
		vector<T> result; vector_extend(result, first); vector_extend(result, second); return result;
	}

	export_ template <class T, class... T_Args>
	inline T& vector_push(vector<T>& vec, T_Args&&... args)
	{
		vec.emplace_back(static_cast<T_Args&&>(args)...);
		return vec.back();
	}

	export_ template <class T>
	inline T pop(vector<T>& vec)
	{
		T val = move(vec.back());
		vec.pop_back();
		return val;
	}

	export_ template <class T>
	inline void swap_pop(vector<T>& vec, size_t index)
	{
		swap(vec[index], vec.back());
		vec.pop_back();
	}

	export_ template <class T, class U>
	inline void vector_cast(const vector<T>& source, vector<U>& target)
	{
		target.reserve(source.size());
		for(const T& val : source)
			target.push_back(static_cast<U>(val));
	}

	export_ template <class U, class T>
	inline vector<U> vector_convert(const vector<T>& source)
	{
		vector<U> target;
		vector_cast(source, target);
		return target;
	}

	export_ template <class U, class T, class Op>
	inline vector<U> vector_convert(const vector<T>& source, Op op)
	{
		vector<U> result;
		result.resize(source.size());
		transform(source.begin(), source.end(), result.begin(), op);
		return result;
	}

	export_ template <class T>
	inline void vector_remove(vector<T>& vec, T value)
	{
		vec.erase(remove(vec.begin(), vec.end(), value), vec.end());
	}

	export_ template <class T>
	inline void vector_remove_ref(vector<T>& vec, T& value)
	{
		size_t index = &value - vec.data();
		vec.erase(vec.begin() + index);
	}

	export_ template <class T, class Pred>
	inline auto vector_remove_if(vector<T>& vec, Pred predicate)
	{
		return vec.erase(remove_if(vec.begin(), vec.end(), predicate), vec.end());
	}

	export_ template <class T, class Pred>
	inline void vector_prune(vector<T>& vec, Pred predicate)
	{
		for(int i = int(vec.size()) - 1; i >= 0; i--)
			if(predicate(vec[i]))
				vec.erase(vec.begin() + i);
	}

	export_ template <class T>
	inline size_t vector_index(const vector<T>& vec, T value)
	{
		return find(vec.begin(), vec.end(), value) - vec.begin();
	}
	
	export_ template <class T>
	inline size_t array_index(array<T> vec, T value)
	{
		return find(vec.begin(), vec.end(), value) - vec.begin();
	}

	export_ template <class T>
	inline bool vector_has(const vector<T>& vec, T value)
	{
		return find(vec.begin(), vec.end(), value) != vec.end();
	}

	export_ template <class T, class Pred>
	inline bool vector_has_pred(const vector<T>& vec, Pred predicate)
	{
		return find_if(vec.begin(), vec.end(), predicate) != vec.end();
	}

	export_ template <class T, class Pred>
	inline const T* vector_find(const vector<T>& vec, Pred predicate)
	{
		auto it = find_if(vec.begin(), vec.end(), predicate);
		return it != vec.end() ? &(*it) : nullptr;
	}

	export_ template <class T, class Pred>
	inline auto vector_find_if(vector<T>& vec, Pred predicate)
	{
		return find_if(vec.begin(), vec.end(), predicate);
	}
	
	export_ template <class T, class Pred>
	inline auto vector_find_if(const vector<T>& vec, Pred predicate)
	{
		return find_if(vec.begin(), vec.end(), predicate);
	}
	
	export_ template <class T>
	inline void vector_remove_object(vector<T>& vec, T& object)
	{
		auto pos = find_if(vec.begin(), vec.end(), [&](const T& look) { return &look == &object; });
		vec.erase(pos);
	}

	export_ template <class T>
	inline bool vector_contains(const vector<T>& vec, const vector<T>& other)
	{
		return includes(vec.begin(), vec.end(), other.begin(), other.end());
	}

	export_ template <class T>
	inline vector<T> vector_reverse(const vector<T>& vec)
	{
		vector<T> result = vec;
		reverse(result.begin(), result.end());
		return result;
	}

	export_ template <class T, class V>
	inline auto vector_remove_pt(vector<T>& vec, V& value)
	{
		auto pos = find_if(vec.begin(), vec.end(), [&](auto& pt) { return pt.get() == &value; });
		vec.erase(pos);
	}

	export_ template <class T, class V>
	inline auto vector_transfer_pt(vector<T>& source, vector<T>& target, V& value)
	{
		auto pos = find_if(source.begin(), source.end(), [&](auto& pt) { return pt.get() == &value; });
		target.emplace_back(move(*pos));
		source.erase(pos);
	}

	export_ template <class T>
	inline void vector_add(vector<T>& vec, T value)
	{
		if(!vector_has(vec, value))
			vec.push_back(value);
	}

	export_ template <class T>
	inline void vector_select(vector<T>& vec, T value) { vec.clear(); vec.push_back(value); }

	export_ template <class T>
	inline bool vector_swap(vector<T>& vec, T value) { if(vector_has(vec, value)) { vector_remove(vec, value); return false; } else { vector_add(vec, value); return true; } }
	
	export_ template <class T>
	inline size_t index_of(const vector<T>& vec, const T& value)
	{
		return find(vec.begin(), vec.end(), value) - vec.begin();
	}

	template <class U, class T, class F>
	export_ vector<U> transform(const vector<T>& vec, F func)
	{
		vector<U> result;
		for(const T& value : vec)
			result.push_back(func(value));
		return result;
	}

	template <class V, class T, class U, class F>
	export_ vector<V> transform(const vector<T>& a, const vector<U>& b, F func)
	{
		vector<V> result;
		for(size_t i = 0; i < a.size(); ++i)
			result.push_back(func(a[i], b[i]));
		return result;
	}

	template <class T, class F>
	export_ vector<T> transform(size_t begin, size_t end, F func)
	{
		vector<T> result;
		for(size_t i = begin; i < end; ++i)
			result.push_back(func(i));
		return result;
	}
}

#if defined(WIN32)
#include <malloc.h>
#else
#include <cstdlib>
#endif

namespace mud
{
	inline void* aligned_alloc(size_t size, size_t align) noexcept
	{
		assert(align && !(align & (align - 1)));
		void* p = nullptr;

		// must be a power of two and >= sizeof(void*)
		while(align < sizeof(void*))
			align <<= 1;

#if defined(WIN32)
		p = ::_aligned_malloc(size, align);
#else
		::posix_memalign(&p, align, size);
#endif
		return p;
	}

	inline void aligned_free(void* p) noexcept
	{
#if defined(WIN32)
		::_aligned_free(p);
#else
		::free(p);
#endif
	}

#ifdef MUD_NO_STL
	template <typename T>
	class TinystlAlignedAllocator
	{
	public:
		static inline T* static_allocate(size_t bytes) { return (T*)aligned_alloc(bytes, alignof(T)); };
		static inline void static_deallocate(T* ptr, size_t /*bytes*/) { aligned_free(ptr); }
	};
#else
	template <typename T>
	class STLAlignedAllocator
	{
		static_assert(!(alignof(T) & (alignof(T)-1)), "alignof(T) must be a power of two");

	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = true_type;
		using is_always_equal = true_type;

		template <typename U>
		struct rebind { using other = STLAlignedAllocator<U>; };

	public:
		inline STLAlignedAllocator() noexcept = default;
		inline ~STLAlignedAllocator() noexcept = default;

		template <typename U>
		inline explicit STLAlignedAllocator(const STLAlignedAllocator<U>&) noexcept {}

		inline pointer allocate(size_type n) noexcept { return (pointer)aligned_alloc(n * sizeof(value_type), alignof(T)); }
		inline void deallocate(pointer p, size_type) { aligned_free(p); }

		inline bool operator==(const STLAlignedAllocator<T>&) const { return true; }
		inline bool operator!=(const STLAlignedAllocator<T>&) const { return false; }
	};
#endif
}


#include <cassert>
#include <cstddef>
#include <cstdint>
#include <climits>

#include <stl/type_traits.h>

namespace mud
{
	template<typename T>
	inline T popcount(T v)
	{
		static_assert(sizeof(T) * 8 <= 128, "popcount() only support up to 128 bits");
		const T ONES = ~T(0);
		v = v - ((v >> 1) & ONES / 3);
		v = (v & ONES / 15 * 3) + ((v >> 2) & ONES / 15 * 3);
		v = (v + (v >> 4)) & ONES / 255 * 15;
		return (T)(v * (ONES / 255)) >> (sizeof(T) - 1) * CHAR_BIT;
	}

	template<typename T>
	inline T clz(T x)
	{
		static_assert(sizeof(T) <= sizeof(uint64_t), "clz() only support up to 64 bits");
		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);
		if(sizeof(T) * 8 > 32) { // if() only needed to quash compiler warnings
			x |= (x >> 32);
		}
		return (sizeof(T) * CHAR_BIT) - popcount(x);
	}

	template<typename T>
	inline T ctz(T x)
	{
		static_assert(sizeof(T) <= sizeof(uint64_t), "ctz() only support up to 64 bits");
		T c = sizeof(T) * 8;
		x &= -signed(x);
		if(x) c--;
		if(sizeof(T) * 8 > 32) { // if() only needed to quash compiler warnings
			if(x & 0x00000000FFFFFFFF) c -= 32;
		}
		if(x & 0x0000FFFF) c -= 16;
		if(x & 0x00FF00FF) c -= 8;
		if(x & 0x0F0F0F0F) c -= 4;
		if(x & 0x33333333) c -= 2;
		if(x & 0x55555555) c -= 1;
		return c;
	}
/*
 * This bitset<> class is different from std::bitset<> in that it allows us to control
 * the exact storage size. This is useful for small bitset (e.g. < 64, on 64-bits machines).
 * It also allows for lexicographical compares (i.e. sorting).
 */

template<typename T, size_t N = 1,
         typename = typename enable_if<is_integral<T>::value &&
                                       is_unsigned<T>::value>::type>
class bitset {
	T storage[N] = {};

public:
    static constexpr T BITS_PER_WORD = sizeof(T) * 8;
    static constexpr T BIT_COUNT = BITS_PER_WORD * N;
    static constexpr T WORLD_COUNT = N;
    using container_type = T;

    bitset()
	{}

    T at(size_t n) const
	{
        return storage[n];
    }

    T& at(size_t n)
	{
        return storage[n];
    }

    T get_bits() const
	{
        static_assert(N == 1, "bitfield must only have one storage word");
        return storage[0];
    }

    void set_bits(T value)
	{
        static_assert(N == 1, "bitfield must only have one storage word");
        storage[0] = value;
    }

    template<typename F>
    void for_each(F exec) const
	{
        for(size_t i = 0; i < N; i++)
		{
            T v = storage[i];
            while(v)
			{
                T k = ctz(v);
                v &= ~(T(1) << k);
                exec(size_t(k + BITS_PER_WORD * i));
            }
        }
    }

    size_t size() const { return N * BITS_PER_WORD; }

    bool test(size_t bit) const { return operator[](bit); }

    void set(size_t b)
	{
        storage[b / BITS_PER_WORD] |= T(1) << (b % BITS_PER_WORD);
    }

    void set(size_t b, bool value)
	{
        storage[b / BITS_PER_WORD] &= ~(T(1) << (b % BITS_PER_WORD));
        storage[b / BITS_PER_WORD] |= T(value) << (b % BITS_PER_WORD);
    }

    void unset(size_t b)
	{
        storage[b / BITS_PER_WORD] &= ~(T(1) << (b % BITS_PER_WORD));
    }

    void flip(size_t b)
	{
        storage[b / BITS_PER_WORD] ^= T(1) << (b % BITS_PER_WORD);
    }

    void reset()
	{
        *this = {};
    }

    bool operator[](size_t b) const
	{
        return (storage[b / BITS_PER_WORD] & (T(1) << (b % BITS_PER_WORD))) != 0;
    }

    T count() const
	{
        T r = popcount(storage[0]);
        for (size_t i = 1; i < N; ++i)
            r += popcount(storage[i]);
        return r;
    }

    bool any() const
	{
        T r = storage[0];
        for (size_t i = 1; i < N; ++i)
            r |= storage[i];
        return r != 0;
    }

    bool none() const { return !any(); }

    bool all() const
	{
        T r = storage[0];
        for (size_t i = 1; i < N; ++i)
            r &= storage[i];
        return T(~r) == T(0);
    }

    bool operator!=(const bitset& b) const
	{
        T r = storage[0] ^ b.storage[0];
        for(size_t i = 1; i < N; ++i)
            r |= storage[i] ^ b.storage[i];
        return r != 0;
    }

    bool operator==(const bitset& b) const { return !operator!=(b); }

    bitset& operator&=(const bitset& b) { for(size_t i = 0; i < N; ++i) storage[i] &= b.storage[i]; return *this; }
    bitset& operator|=(const bitset& b) { for(size_t i = 0; i < N; ++i) storage[i] |= b.storage[i]; return *this; }
    bitset& operator^=(const bitset& b) { for(size_t i = 0; i < N; ++i) storage[i] ^= b.storage[i]; return *this; }
    bitset operator~() const { bitset r; for(size_t i = 0; i < N; ++i) r.storage[i] = ~storage[i]; return r; }

private:

    friend bitset operator&(const bitset& lhs, const bitset& rhs) { return bitset(lhs) &= rhs; }
    friend bitset operator|(const bitset& lhs, const bitset& rhs) { return bitset(lhs) |= rhs; }
    friend bitset operator^(const bitset& lhs, const bitset& rhs) { return bitset(lhs) ^= rhs; }
};

using bitset8 = bitset<uint8_t>;
using bitset32 = bitset<uint32_t>;
using bitset256 = bitset<uint64_t, 4>;

static_assert(sizeof(bitset8) == sizeof(uint8_t), "bitset8 isn't 8 bits!");
static_assert(sizeof(bitset32) == sizeof(uint32_t), "bitset32 isn't 32 bits!");

}




#include <cstring>

namespace mud
{
	template <class T>
	void copy(array<T> dest, array<T> src) { memcpy(dest.m_pointer, src.m_pointer, sizeof(T) * src.m_count); }

	template <class T>
	void copy(T* dest, array<T> src) { memcpy(dest, src.m_pointer, sizeof(T) * src.m_count); }

	template <class T>
	void copy(void* dest, array<T> src) { memcpy(dest, src.m_pointer, sizeof(T) * src.m_count); }
}

#include <stl/type_traits.h>

#include <cassert>
#include <cstddef>
#include <cstdlib>

#include <atomic>
#include <utility>

#if defined(WIN32)
#include <malloc.h>
#endif

namespace mud
{
	namespace pointermath
	{
		export_ template <typename P, typename T>
		inline P* add(P* a, T b)
		{
			return (P*)(uintptr_t(a) + uintptr_t(b));
		}

		export_ template <typename P>
		inline P* align(P* p, size_t alignment)
		{
			// alignment must be a power-of-two
			assert(alignment && !(alignment & (alignment - 1)));
			return (P*)((uintptr_t(p) + alignment - 1) & ~(alignment - 1));
		}

		export_ template <typename P>
		inline P* align(P* p, size_t alignment, size_t offset)
		{
			P* const r = align(add(p, offset), alignment);
			//assert(pointermath::add(r, -offset) >= p);
			return r;
		}
	}

	export_ class FreeListBase
	{
	public:
		struct Node
		{
			Node* next;
		};
		static Node* init(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra);
	};

	export_ class FreeList : private FreeListBase
	{
	public:
		FreeList() = default;
		FreeList(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra);
		FreeList(const FreeList& rhs) = delete;
		FreeList& operator=(const FreeList& rhs) = delete;
		FreeList(FreeList&& rhs) = default;
		FreeList& operator=(FreeList&& rhs) = default;

		void* pop()
		{
			Node* const head = m_head;
			m_head = head ? head->next : nullptr;
			// this could indicate a use after free
			assert(!m_head || (m_head >= m_begin && m_head < m_end));
			return head;
}

		void push(void* p)
		{
			assert(p);
			assert(p >= m_begin && p < m_end);
			// TODO: assert this is one of our pointer (i.e.: it's address match one of ours)
			Node* const head = static_cast<Node*>(p);
			head->next = m_head;
			m_head = head;
		}

		void* current() { return m_head; }

	private:
		Node* m_head = nullptr;

#ifndef NDEBUG
		void* m_begin = nullptr;
		void* m_end = nullptr;
#endif
	};

	export_ class AtomicFreeList : private FreeListBase
	{
	public:
		AtomicFreeList() = default;
		AtomicFreeList(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra);
		AtomicFreeList(const FreeList& rhs) = delete;
		AtomicFreeList& operator=(const FreeList& rhs) = delete;

		void* pop()
		{
			Node* head = m_head.load(std::memory_order_relaxed);
			while(head && !m_head.compare_exchange_weak(head, head->next, std::memory_order_release, std::memory_order_relaxed))
			{
			}
			return head;
		}

		void push(void* p)
		{
			assert(p);
			Node* head = static_cast<Node*>(p);
			head->next = m_head.load(std::memory_order_relaxed);
			while(!m_head.compare_exchange_weak(head->next, head, std::memory_order_release, std::memory_order_relaxed))
			{
			}
		}

		void* current() { return m_head.load(std::memory_order_relaxed); }

	private:
		std::atomic<Node*> m_head;
	};

#define GENERIC_MAX(a,b) ((a) > (b) ? (a) : (b))

	export_ template <class T, class T_FreeList = FreeList>
	class Arena
	{
	public:
		Arena() = default;

		Arena(const char* name, size_t size)
			: m_name(name)
			, m_begin(malloc(size))
			, m_end(pointermath::add(m_begin, size))
			, m_freelist(m_begin, m_end, sizeof(T), GENERIC_MAX(alignof(T_FreeList), alignof(T)), 0)
		{}

		~Arena()
		{
			free(m_begin);
		}

		void* alloc()
		{
			void* p = m_freelist.pop();
			return p;
		}

		template <typename U = T, typename = typename enable_if<std::is_trivially_destructible<U>::value>::type>
		T* alloc(size_t count, size_t alignment = alignof(T))
		{
			return (T*)alloc(count * sizeof(T), alignment);
		}

		void free(void* p)
		{
			if(p) m_freelist.push(p);
		}

		void free(void* p, size_t size)
		{
			UNUSED(size);
			if(p) m_freelist.push(p);
		}

		//void reset() { m_allocator.reset(); }

		void* current() { return m_freelist.current(); }

		//void rewind(void* addr) { m_allocator.rewind(addr); }

		template <typename... T_Args>
		T* make(T_Args&&... args)
		{
			void* const p = this->alloc();
			return p ? new(p) T(static_cast<T_Args&&>(args)...) : nullptr;
		}

		void destroy(T* p)
		{
			p->~T();
			this->free((void*)p);
		}

		Arena(Arena const& rhs) = delete;
		Arena& operator=(Arena const& rhs) = delete;

		const char* m_name = nullptr;
		void* m_begin = nullptr;
		void* m_end = nullptr;
		T_FreeList m_freelist;
	};
}


#include <stl/swap.h>

namespace mud
{
	template <class T_Key, class T_Value, class T_Indices, class T_Greater>
	void quicksort(array<T_Key> keys, array<T_Value> values, T_Indices& indices, T_Greater greater, const size_t left, const size_t right)
	{
		auto swap = [&](size_t first, size_t second)
		{
			using mud::swap;
			swap(keys[first], keys[second]);
			swap(values[first], values[second]);
			swap(indices[keys[first]], indices[keys[second]]);
		};

		auto partition = [&](const size_t left, const size_t right)
		{
			const size_t mid = left + (right - left) / 2;
			const T_Key pivot = keys[mid];
			// move the mid point value to the front.
			swap(mid, left);
			size_t i = left + 1;
			size_t j = right;
			while(i <= j)
			{
				while(i <= j && !greater(keys[i], pivot))
					i++;

				while(i <= j && greater(keys[j], pivot))
					j--;

				if(i < j)
					swap(i, j);
			}
			swap(i - 1, left);
			return i - 1;
		};

		size_t part = partition(left, right);

		if(int(left) < int(part) - 1)
			quicksort(keys, values, indices, greater, left, part - 1);
		if(part + 1 < right)
			quicksort(keys, values, indices, greater, part + 1, right);
	}

	template <class T_Key, class T_Value, class T_Indices, class T_Greater>
	void quicksort(array<T_Key> keys, array<T_Value> values, T_Indices& indices, T_Greater greater)
	{
		if(keys.size() > 0)
			quicksort(keys, values, indices, greater, 0, keys.size() - 1);
	}

	template <class T_Key, class T_Value, class T_Indices>
	void quicksort(array<T_Key> keys, array<T_Value> values, T_Indices& indices)
	{
		auto greater = [](T_Key a, T_Key b) { return a > b; };
		if(keys.size() > 0)
			quicksort(keys, values, indices, greater, 0, keys.size() - 1);
	}
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    
    
}
