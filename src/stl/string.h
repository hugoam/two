#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#ifndef TWO_STD_MODULES
#include <string>
#endif
namespace stl
{
	export_ using std::string;
}
#else
#include <stl/initializer_list.h>

#include <stl/allocator.h>
#include <stl/buffer.h>
#include <stl/stddef.h>
#include <stl/hash.h>
#include <stl/span.h>

namespace stl {

	template <class Alloc>
	class refl_ basic_string : public buffer<char, Alloc, 1> {
	public:
		basic_string();
		basic_string(const basic_string& other);
		//basic_string(const basic_string& other, size_t pos, size_t len = npos);
		basic_string(basic_string&& other);
		basic_string(const char* s);
		basic_string(const char* s, size_t len);
		basic_string(size_t len, char c);
		basic_string(const char* first, const char* last);
		basic_string(std::initializer_list<char> list);
		~basic_string();

		basic_string& operator=(const basic_string& other);
		basic_string& operator=(basic_string&& other);

		const char* c_str() const;

		void resize(size_t size);
		void resize(size_t size, char value);
		void clear();
		void alloc(size_t capacity);
		void reserve(size_t capacity);

		void push_back(char t);
		void pop_back();

		void shrink_to_fit();

		void swap(basic_string& other);

		typedef char value_type;
		typedef char* pointer;
		typedef char* iterator;
		typedef const char* const_iterator;

		void append(const char* first, const char* last);
		void append(const basic_string& other);
		void assign(const char* first, const char* last);
		void assign(const char* s, size_t n);
		void insert(size_t where, char c);
		void insert(size_t where, const char* first, const char* last);
		void insert(size_t where, const basic_string& other);
		void insert(iterator where, char c);
		void insert(iterator where, const char* first, const char* last);
		void insert(iterator where, const basic_string& other);

		basic_string& operator+=(const basic_string& other);

		void erase(size_t pos = 0, size_t len = npos);
		iterator erase(iterator where);
		iterator erase(iterator first, iterator last);

		basic_string substr(size_t begin, size_t count = npos) const;

		size_t find(char c, const size_t offset = 0) const;
		size_t rfind(char c, const size_t offset = npos) const;
		size_t find(const basic_string& other, const size_t offset = 0) const;
		size_t rfind(const basic_string& other, const size_t offset = npos) const;

		size_t find_any(span<char> chars, const size_t offset = 0) const;

		bool operator==(const basic_string& rhs) const;
		bool operator!=(const basic_string& rhs) const;
		bool operator<(const basic_string& rhs) const;

		int compare(const basic_string& other) const;

		static constexpr auto npos{ static_cast<size_t>(-1) };

	private:
		void reset(size_t size);

	protected:
		static const size_t c_nbuffer = 12;
		char m_small[12];
	};

	template <class Alloc>
	inline bool operator==(const basic_string<Alloc>& lhs, const char* rhs) { return lhs == basic_string<Alloc>(rhs); }

	template <class Alloc>
	inline bool operator==(const char* lhs, const basic_string<Alloc>& rhs) { return basic_string<Alloc>(lhs) == rhs; }

	template <class Alloc>
	inline bool operator!=(const basic_string<Alloc>& lhs, const char* rhs) { return lhs != basic_string<Alloc>(rhs); }

	template <class Alloc>
	inline bool operator!=(const char* lhs, const basic_string<Alloc>& rhs) { return basic_string<Alloc>(lhs) != rhs; }

	template <class Alloc>
	basic_string<Alloc> operator+(const basic_string<Alloc>& lhs, const basic_string<Alloc>& rhs);

	template <class Alloc>
	basic_string<Alloc> operator+(const basic_string<Alloc>& lhs, const char* rhs);

	template <class Alloc>
	basic_string<Alloc> operator+(const char* lhs, const basic_string<Alloc>& rhs);

	template <class Alloc>
	static inline size_t hash(const basic_string<Alloc>& value) {
		return hash_string(value.c_str(), value.size());
	}

	export_ using string = basic_string<TINYSTL_ALLOCATOR>;

	extern template TWO_INFRA_EXPORT string operator+(const string& lhs, const string& rhs);
	extern template TWO_INFRA_EXPORT string operator+(const char* lhs, const string& rhs);
	extern template TWO_INFRA_EXPORT string operator+(const string& lhs, const char* rhs);
}
#endif

#ifdef TWO_META_GENERATOR
namespace stl
{
	extern template class refl_ basic_string<TINYSTL_ALLOCATOR>;
	using string = basic_string<TINYSTL_ALLOCATOR>;
	base_ static string dstring;
}
#endif

namespace two
{
  //export_ using string = stl::basic_string<TINYSTL_ALLOCATOR>;
	export_ using stl::string;
}

