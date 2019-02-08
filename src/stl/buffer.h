#pragma once

#include <stl/allocator.h>
#include <stl/initializer_list.h>

namespace stl {

	template <class T, class Alloc = TINYSTL_ALLOCATOR, size_t Pad = 0>
	class buf {
	public:
		buf();
		buf(const buf& other);
		buf(buf&& other);
		explicit buf(size_t size);
		buf(size_t size, const T& value);
		~buf();

		buf& operator=(const buf& other);
		buf& operator=(buf&& other);

		void swap(buf& other);

		const T* data() const { return m_first; }
		T* data() { return m_first; }
		size_t size() const { return size_t(m_last - m_first); }
		size_t capacity() const { return size_t(m_capacity - m_first); }
		bool empty() const { return m_last == m_first; }

		T& operator[](size_t idx) { return m_first[idx]; }
		const T& operator[](size_t idx) const { return m_first[idx]; }

		void alloc(size_t size);
		void realloc(size_t size, bool dealloc = true);
		void reserve(size_t capacity, bool dealloc = true);
		void resize(size_t size);
		void resize(size_t size, const T& value);
		void clear();
		
		using value_type = T;
		using pointer = T*;

	//protected:
		T* m_first = 0;
		T* m_last = 0;
		T* m_capacity = 0;
	};

	template <class T, class Alloc = TINYSTL_ALLOCATOR, size_t Pad = 0>
	class buffer : public buf<T, Alloc, Pad> {
	public:
		using buf<T, Alloc, Pad>::buf;
		buffer(const T* first, const T* last);
		buffer(std::initializer_list<T> list);

		const T& front() const { return this->m_first[0]; }
		T& front() { return this->m_first[0]; }
		const T& back() const { return this->m_last[-1]; }
		T& back() { return this->m_last[-1]; }

		void grow(size_t size, bool dealloc = true);

		void push_back(const T& t);
		void push_back(T&& t);
		void emplace_back();
		template <class... Params>
		void emplace_back(Params&&... params);
		void pop_back();

		void append(const T* first, const T* last);

		void shrink_to_fit();

		T* spread(T* where, size_t count, bool dealloc = true);

		using iterator = T*;
		using const_iterator = const T*;

		iterator begin() { return this->m_first; }
		iterator end() { return this->m_last; }

		const_iterator begin() const { return this->m_first; }
		const_iterator end() const { return this->m_last; }
	};
}
