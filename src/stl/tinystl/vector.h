#pragma once

#include <initializer_list>

#include <stl/tinystl/allocator.h>
#include <stl/tinystl/buffer.h>
#include <stl/tinystl/stddef.h>

namespace tinystl {

	template<typename T, typename Alloc = TINYSTL_ALLOCATOR>
	class vector {
	public:
		vector();
		vector(const vector& other);
		vector(vector&& other);
		vector(size_t size);
		vector(size_t size, const T& value);
		vector(const T* first, const T* last);
		vector(std::initializer_list<T> list);
		~vector();

		vector& operator=(const vector& other);
		vector& operator=(vector&& other);

		void assign(const T* first, const T* last);

		const T* data() const;
		T* data();
		size_t size() const;
		size_t capacity() const;
		bool empty() const;

		T& operator[](size_t idx);
		const T& operator[](size_t idx) const;

		const T& front() const;
		T& front();
		const T& back() const;
		T& back();

		void resize(size_t size);
		void resize(size_t size, const T& value);
		void clear();
		void reserve(size_t capacity);

		void push_back(const T& t);
		void push_back(T&& t);
		void pop_back();

		void emplace_back();
		void emplace_back(T&& t);
		template<typename... Params>
		void emplace_back(Params&&... params);

		void shrink_to_fit();

		void swap(vector& other);

		typedef T value_type;

		typedef T* iterator;
		iterator begin();
		iterator end();

		typedef const T* const_iterator;
		const_iterator begin() const;
		const_iterator end() const;

		iterator insert(iterator where);
		iterator insert(iterator where, const T& value);
		iterator insert(iterator where, T&& value);
		iterator insert(iterator where, const T* first, const T* last);

		template<typename... Params>
		void emplace(iterator where, Params&&... params);

		iterator erase(iterator where);
		iterator erase(iterator first, iterator last);

		iterator erase_unordered(iterator where);
		iterator erase_unordered(iterator first, iterator last);

	protected:
		buffer<T, Alloc> m_buffer;
	};
}
