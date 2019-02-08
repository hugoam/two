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

		const T* data() const;
		T* data();
		size_t size() const;
		size_t capacity() const;
		bool empty() const;

		T& operator[](size_t idx);
		const T& operator[](size_t idx) const;

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

	template <class T, class Alloc, size_t Pad>
	inline const T* buf<T, Alloc, Pad>::data() const {
		return m_first;
	}

	template <class T, class Alloc, size_t Pad>
	inline T* buf<T, Alloc, Pad>::data() {
		return m_first;
	}

	template <class T, class Alloc, size_t Pad>
	inline size_t buf<T, Alloc, Pad>::size() const {
		return size_t(m_last - m_first);
	}

	template <class T, class Alloc, size_t Pad>
	inline size_t buf<T, Alloc, Pad>::capacity() const {
		return size_t(m_capacity - m_first);
	}

	template <class T, class Alloc, size_t Pad>
	inline bool buf<T, Alloc, Pad>::empty() const {
		return m_last == m_first;
	}

	template <class T, class Alloc, size_t Pad>
	inline T& buf<T, Alloc, Pad>::operator[](size_t idx) {
		return m_first[idx];
	}

	template <class T, class Alloc, size_t Pad>
	inline const T& buf<T, Alloc, Pad>::operator[](size_t idx) const {
		return m_first[idx];
	}

	template <class T, class Alloc = TINYSTL_ALLOCATOR, size_t Pad = 0>
	class buffer : public buf<T, Alloc, Pad> {
	public:
		using buf<T, Alloc, Pad>::buf;
		buffer(const T* first, const T* last);
		buffer(std::initializer_list<T> list);

		const T& front() const;
		T& front();
		const T& back() const;
		T& back();

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

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;
	};

	template <class T, class Alloc, size_t Pad>
	inline const T& buffer<T, Alloc, Pad>::front() const {
		return this->m_first[0];
	}

	template <class T, class Alloc, size_t Pad>
	inline T& buffer<T, Alloc, Pad>::front() {
		return this->m_first[0];
	}

	template <class T, class Alloc, size_t Pad>
	inline const T& buffer<T, Alloc, Pad>::back() const {
		return this->m_last[-1];
	}

	template <class T, class Alloc, size_t Pad>
	inline T& buffer<T, Alloc, Pad>::back() {
		return this->m_last[-1];
	}

	template <class T, class Alloc, size_t Pad>
	inline typename buffer<T, Alloc, Pad>::iterator buffer<T, Alloc, Pad>::begin() {
		return this->m_first;
	}

	template <class T, class Alloc, size_t Pad>
	inline typename buffer<T, Alloc, Pad>::iterator buffer<T, Alloc, Pad>::end() {
		return this->m_last;
	}

	template <class T, class Alloc, size_t Pad>
	inline typename buffer<T, Alloc, Pad>::const_iterator buffer<T, Alloc, Pad>::begin() const {
		return this->m_first;
	}

	template <class T, class Alloc, size_t Pad>
	inline typename buffer<T, Alloc, Pad>::const_iterator buffer<T, Alloc, Pad>::end() const {
		return this->m_last;
	}
}
