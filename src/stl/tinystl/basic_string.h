#pragma once

#include <initializer_list>

#include <stl/tinystl/buffer.h>
#include <stl/tinystl/stddef.h>
#include <stl/tinystl/hash.h>

namespace tinystl {

	template<typename Alloc>
	class basic_string {
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

		const char* data() const;
		char* data();

		const char* c_str() const;
		size_t size() const;
		size_t capacity() const;
		bool empty() const;

		char& operator[](size_t idx);
		const char& operator[](size_t idx) const;

		const char& front() const;
		char& front();
		const char& back() const;
		char& back();

		void resize(size_t size);
		void resize(size_t size, char value);
		void clear();
		void reserve(size_t capacity);

		void push_back(char t);
		void pop_back();

		void shrink_to_fit();

		void swap(basic_string& other);

		typedef char value_type;

		typedef char* pointer;
		typedef char* iterator;
		iterator begin();
		iterator end();

		typedef const char* const_iterator;
		const_iterator begin() const;
		const_iterator end() const;

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

		bool operator==(const basic_string& rhs) const;
		bool operator!=(const basic_string& rhs) const;
		bool operator<(const basic_string& rhs) const;

		int compare(const basic_string& other) const;

		static constexpr auto npos{ static_cast<size_t>(-1) };

	protected:
		static const size_t c_nbuffer = 12;
		char m_small[12];

		buffer<char, Alloc> m_buffer;
	};

	template<typename Alloc>
	inline bool operator==(const basic_string<Alloc>& lhs, const char* rhs) { return lhs == basic_string<Alloc>(rhs); }

	template<typename Alloc>
	inline bool operator==(const char* lhs, const basic_string<Alloc>& rhs) { return basic_string<Alloc>(lhs) == rhs; }

	template<typename Alloc>
	inline bool operator!=(const basic_string<Alloc>& lhs, const char* rhs) { return lhs != basic_string<Alloc>(rhs); }

	template<typename Alloc>
	inline bool operator!=(const char* lhs, const basic_string<Alloc>& rhs) { return basic_string<Alloc>(lhs) != rhs; }

	template<typename Alloc>
	static inline size_t hash(const basic_string<Alloc>& value) {
		return hash_string(value.c_str(), value.size());
	}
}
