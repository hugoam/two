#pragma once




#if defined(WIN32)
#include <malloc.h>
#else
#include <cstdlib>
#endif

#include <cassert>

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

#ifndef USE_STL
	template <class T>
	class TinystlAlignedAllocator
	{
	public:
		static inline T* static_allocate(size_t bytes) { return (T*)aligned_alloc(bytes, alignof(T)); };
		static inline void static_deallocate(T* ptr, size_t /*bytes*/) { aligned_free(ptr); }
	};
#else
	template <class T>
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
		using propagate_on_container_move_assignment = std::true_type;
		using is_always_equal = std::true_type;

		template <class U>
		struct rebind { using other = STLAlignedAllocator<U>; };

	public:
		inline STLAlignedAllocator() noexcept = default;
		inline ~STLAlignedAllocator() noexcept = default;

		template <class U>
		inline explicit STLAlignedAllocator(const STLAlignedAllocator<U>&) noexcept {}

		inline pointer allocate(size_type n) noexcept { return (pointer)aligned_alloc(n * sizeof(value_type), alignof(T)); }
		inline void deallocate(pointer p, size_type) { aligned_free(p); }

		inline bool operator==(const STLAlignedAllocator<T>&) const { return true; }
		inline bool operator!=(const STLAlignedAllocator<T>&) const { return false; }
	};
#endif
}
#include <stl/span.h>




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
#define base_   // Base type
#define refl_   // Reflect
#define struct_ // Struct
#define nocopy_ // Nocopy type
#define array_	// Array type
#define seque_	// Sequence type
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

#ifdef MUD_META_GENERATOR
base_ static void* dvoidptr;
base_ static bool dbool;
base_ static char dchar;
base_ static signed char dschar;
base_ static short dshort;
base_ static int dint;
base_ static long dlong;
base_ static unsigned char duchar;
base_ static unsigned short dushort;
base_ static unsigned int duint;
base_ static unsigned long dulong;
base_ static unsigned long long dullong;
base_ static long long dllong;
base_ static long double dldouble;
base_ static float dfloat;
base_ static double ddouble;
#include <stdint.h>
#include <stddef.h>
#endif
#ifdef MUD_CPP_20

#include <cassert>
#include <stdint.h>
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


#include <stl/initializer_list.h>
#include <stdint.h>

namespace mud
{
	export_ template <class Enum, class T, size_t Size = size_t(Enum::Count)>
	using enum_array = T[Size];
	
	export_ template <class Enum, class T, size_t Size = size_t(Enum::Count)>
	struct enum_array2
	{
		const T& operator[](Enum e) const { return m_values[size_t(e)]; }
		T& operator[](Enum e) { return m_values[size_t(e)]; }

		T m_values[Size] = {};
	};
}


#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/function.h>
#include <stl/span.h>

#include <stl/base.h>

#ifndef MUD_INFRA_EXPORT
#define MUD_INFRA_EXPORT MUD_IMPORT
#endif

#ifdef USE_STL
#include <cstddef>
namespace stl
{
	template <class T> struct span;
	template <class T, size_t Size> struct array;
}
#else
#include <stl/decls.h>
#endif

namespace mud
{
	using stl::array;
	using stl::span;

    struct Filepath;
    struct swallow;
    class NonCopy;
    class Movabl;
}

#ifdef MUD_META_GENERATOR // #ifdef MUD_META_GENERATOR
#include <stl/decls.h>
namespace stl
{
}
#endif

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
	export_ MUD_INFRA_EXPORT void write_binary_file(const string& path, span<uint8_t> data);

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


namespace mud
{
	struct swallow {
		template <class... T> swallow(T...) {}
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


#include <stdint.h>
#include <stl/limits.h>



namespace mud
{
	export_ class MUD_INFRA_EXPORT NonCopy
	{
	public:
		NonCopy() {}
		NonCopy(const NonCopy&) = delete;
		NonCopy& operator=(const NonCopy&) = delete;
	};
}
//#include <infra/Arena.h>


#include <stl/vector.h>

namespace mud
{
#ifndef USE_STL
	template <class T>
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

	template <class T1, class T2>
	bool operator==(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return left.m_ptr == right.m_ptr; }

	template <class T1, class T2>
	bool operator!=(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return !(left == right); }

	template <class T1, class T2>
	bool operator<(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return right.m_ptr < left.m_ptr; }

	template <class T1, class T2>
	bool operator>(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return right < left; }

	template <class T1, class T2>
	bool operator<=(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return !(right < left); }

	template <class T1, class T2>
	bool operator>=(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return !(left < right); }
#endif

	export_ template <class T>
	class reverse_adapter
	{
	public:
		reverse_adapter(T& container) : m_container(container) { }
		reverse_adapter& operator=(const reverse_adapter&) = delete;

#ifndef USE_STL
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

	export_ template <class T>
	reverse_adapter<T> reverse_adapt(T& container) { return reverse_adapter<T>(container); }
}


#include <stl/string.h>
#include <stl/vector.h>
#include <stl/span.h>

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

	export_ MUD_INFRA_EXPORT void split(const string& str, const string& separator, span<string> output);
	export_ MUD_INFRA_EXPORT vector<string> split(const string& str, const string& separator);

	//export_ MUD_INFRA_EXPORT string join(span<string> strings, string separator);
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


#include <stl/base.h>

namespace mud
{
	export_ template <> MUD_INFRA_EXPORT void to_string(const bool&    value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const char&    value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const schar&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const uchar&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const short&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const int&     value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const long&    value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const llong&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const ushort&  value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const uint&    value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const ulong&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const ullong&  value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const float&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const double&  value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const ldouble& value, string& str);
}


#include <stl/base.h>

namespace mud
{
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, bool& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, char& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, schar& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, short& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, int& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, long& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, llong& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, uchar& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, ushort& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, uint& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, ulong& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, ullong& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, float& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, double& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, ldouble& val);
}


#include <stdint.h>
#include <stl/vector.h>
//#include <stl/type_traits.h>

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

#if 0
	export_ template <class T>
	constexpr bool is_vector = false;
	
	export_ template <class T>
	constexpr bool is_vector<vector<T>> = true;

	export_ template <class T>
	inline enable_if<is_vector<T>, void>
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
			vec.push_back(to_value<class T::value_type>(str.substr(first, second - first)));
			
			if(second != end)
				first = second + 1;
		}
	}

	export_ template <class T, uint32_t size>
	inline void array_to_string(const T& val, string& str)
	{
		for(uint32_t i = 0; i < size; ++i)
		{
			str += to_string(val[i]);
			str += ",";
		}
		str.pop_back();
	}

	export_ template <class Vec, class T>
	inline void string_to_array(const string& str, Vec& vec)
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


#include <stl/stddef.h>
#include <stdint.h>

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
//#include <infra/TypeTraits.h>


#include <stl/type_traits.h>
#include <stl/stddef.h>
#include <stl/span.h>

#include <cassert>
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
		export_ template <class P, class T>
		inline P* add(P* a, T b)
		{
			return (P*)(uintptr_t(a) + uintptr_t(b));
		}

		export_ template <class P>
		inline P* align(P* p, size_t alignment)
		{
			// alignment must be a power-of-two
			assert(alignment && !(alignment & (alignment - 1)));
			return (P*)((uintptr_t(p) + alignment - 1) & ~(alignment - 1));
		}

		export_ template <class P>
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

		template <class U = T, typename = enable_if<is_trivially_destructible<U>>>
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

		template <class... Args>
		T* make(Args&&... args)
		{
			void* const p = this->alloc();
			return p ? new(p) T(static_cast<Args&&>(args)...) : nullptr;
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


#include <stl/span.h>

#include <cstring>

namespace mud
{
	template <class T>
	void copy(span<T> dest, span<T> src) { memcpy(dest.m_pointer, src.m_pointer, sizeof(T) * src.m_count); }

	template <class T>
	void copy(T* dest, span<T> src) { memcpy(dest, src.m_pointer, sizeof(T) * src.m_count); }

	template <class T>
	void copy(void* dest, span<T> src) { memcpy(dest, src.m_pointer, sizeof(T) * src.m_count); }
}


#include <stl/swap.h>
#include <stl/span.h>

namespace mud
{
#if 0
	template <class T_Key, class T_Value, class T_Indices, class T_Greater>
	void quicksort(span<T_Key> keys, span<T_Value> values, T_Indices& indices, T_Greater greater, const size_t left, const size_t right)
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
	void quicksort(span<T_Key> keys, span<T_Value> values, T_Indices& indices, T_Greater greater)
	{
		if(keys.size() > 0)
			quicksort(keys, values, indices, greater, 0, keys.size() - 1);
	}

	template <class T_Key, class T_Value, class T_Indices>
	void quicksort(span<T_Key> keys, span<T_Value> values, T_Indices& indices)
	{
		auto greater = [](T_Key a, T_Key b) { return a > b; };
		if(keys.size() > 0)
			quicksort(keys, values, indices, greater, 0, keys.size() - 1);
	}
#endif
	
	template <class T, class Pred>
	void quicksort(span<T> vec, Pred greater, const size_t left, const size_t right)
	{
		auto partition = [&](const size_t left, const size_t right)
		{
			using stl::swap;
			const size_t mid = left + (right - left) / 2;
			const T& pivot = vec[mid];
			// move the mid point value to the front.
			swap(vec[mid], vec[left]);
			size_t i = left + 1;
			size_t j = right;
			while(i <= j)
			{
				while(i <= j && !greater(vec[i], pivot))
					i++;

				while(i <= j && greater(vec[j], pivot))
					j--;

				if(i < j)
					swap(vec[i], vec[j]);
			}
			swap(vec[i - 1], vec[left]);
			return i - 1;
		};

		size_t part = partition(left, right);

		if(int(left) < int(part) - 1)
			quicksort(vec, greater, left, part - 1);
		if(part + 1 < right)
			quicksort(vec, greater, part + 1, right);
	}

	template <class T, class Pred>
	void quicksort(span<T> values, Pred greater)
	{
		if(values.size() > 0)
			quicksort(values, greater, 0, values.size() - 1);
	}

	template <class T>
	void quicksort(span<T> values)
	{
		auto greater = [](T a, T b) { return a > b; };
		if(values.size() > 0)
			quicksort(values, greater, 0, values.size() - 1);
	}
}


#include <stl/type_traits.h>

#if defined __GNUC__
#   pragma GCC system_header
#endif

namespace mud
{
	export_ template <class T>
	constexpr bool is_object_pointer = is_pointer<T>;// && !is_function_pointer<T>;

	export_ template <class T, typename = void>
	struct is_comparable_base { constexpr static bool value = false;};

	export_ template <class T>
	struct is_comparable_base<T, decltype(declval<T&>() == declval<T&>(), (void) 0)> { constexpr static bool value = true; };

	export_ template <class T>
	constexpr bool is_comparable = is_comparable_base<T>::value;

	export_ template <class T>
	constexpr bool is_copyable = is_copy_constructible<T> && is_copy_assignable<T>;
}


#include <stl/vector.h>
#include <stl/algorithm.h>
#include <stl/span.h>

namespace mud
{
	export_ template <class T>
	span<T> to_array(vector<T>& vec) { return { &vec[0], vec.size() }; }
	export_ template <class T>
	span<T> to_array(vector<T>& vec, size_t offset) { return { &vec[offset], vec.size() - offset }; }
	export_ template <class T>
	span<T> to_array(vector<T>& vec, size_t offset, size_t count) { return { &vec[offset], count }; }

	template <class T, class U>
	span<T> to_array_cast(vector<U>& vec) { return{ (T*)&vec[0], vec.size() }; }

	export_ template <class T>
	vector<T> to_vector(const span<T>& span) { return { span.m_pointer, span.m_pointer + span.m_count }; }
	
	//export_ template <class T>
	//inline bool has(const vector<T>& vec, const T& value)
	//{
	//	return find(vec.begin(), vec.end(), value) != vec.end();
	//}
	
	export_ template <class T>
	inline bool has(span<T> vec, const T& value)
	{
		return find(vec.begin(), vec.end(), value) != vec.end();
	}

	export_ template <class T>
	inline bool has(std::initializer_list<T> vec, const T& value)
	{
		return find(vec.begin(), vec.end(), value) != vec.end();
	}

	export_ template <class T, class U>
	inline void cast(const vector<T>& source, vector<U>& target)
	{
		target.reserve(source.size());
		for(const T& val : source)
			target.push_back(static_cast<U>(val));
	}

	export_ template <class U, class T>
	inline vector<U> convert(const vector<T>& source)
	{
		vector<U> target;
		cast(source, target);
		return target;
	}

	export_ template <class U, class T, class Op>
	inline vector<U> convert(const vector<T>& source, Op op)
	{
		vector<U> result;
		result.resize(source.size());
		transform(source.begin(), source.end(), result.begin(), op);
		return result;
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


#include <stl/vector.h>

namespace mud
{
	template <class T>
	constexpr bool is_comparable<vector<T>> = is_comparable<T>;
}
