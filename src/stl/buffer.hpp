#pragma once

#include <stl/buffer.h>
#include <stl/new.h>
#include <stl/swap.h>
#include <stl/move_tiny.h>
#include <stl/traits.h>

namespace stl {

	template <class T>
	static inline enable_if<is_pod<T>, void> destroy_urange(T*, T*) {
	}

	template <class T>
	static inline enable_if<!is_pod<T>, void> destroy_urange(T* first, T* last) {
		for (; first < last; ++first)
			first->~T();
	}

	template <class T>
	static inline enable_if<is_pod<T>, void> fill_urange(T* first, T* last) {
		for (; first < last; ++first)
			*first = T();
	}

	template <class T>
	static inline enable_if<!is_pod<T>, void> fill_urange(T* first, T* last) {
		for (; first < last; ++first)
			new(placeholder(), first) T();
	}

	template <class T>
	static inline enable_if<is_pod<T>, void> fill_urange(T* first, T* last, const T& value) {
		for (; first < last; ++first)
			*first = value;
	}

	template <class T>
	static inline enable_if<!is_pod<T> && is_copy_constructible<T>, void> fill_urange(T* first, T* last, const T& value) {
		for (; first < last; ++first)
			new(placeholder(), first) T(value);
	}

	template <class T>
	static inline enable_if<!is_pod<T> && !is_copy_constructible<T>, void> fill_urange(T* first, T* last, const T& value) {
		(void) value;
		for (; first < last; ++first)
			new(placeholder(), first) T();
	}

	template <class T>
	static inline enable_if<is_copy_constructible<T>, void> copy_construct(T* where, const T& value) {
		new(placeholder(), where) T(value);
	}

	template <class T>
	static inline enable_if<!is_copy_constructible<T>, void> copy_construct(T* where, const T& value) {
		(void)value; new(placeholder(), where) T();
	}

	template <class T>
	static inline enable_if<is_pod<T>, void> copy_urange(T* dest, const T* first, const T* last) {
		for (; first != last; ++first, ++dest)
			*dest = *first;
	}

	template <class T>
	static inline enable_if<!is_pod<T> && is_copy_constructible<T>, void> copy_urange(T* dest, const T* first, const T* last) {
		for (; first != last; ++first, ++dest)
			new(placeholder(), dest) T(*first);
	}

	template <class T>
	static inline enable_if<!is_pod<T> && !is_copy_constructible<T>, void> copy_urange(T* dest, const T* first, const T* last) {
		for (; first != last; ++first, ++dest)
			new(placeholder(), dest) T();
	}
	
	template <class T>
	static inline enable_if<is_pod<T>, void> move_urange(T* dest, T* first, T* last) {
		for (; first != last; ++first, ++dest)
			*dest = *first;
	}

	template <class T>
	static inline enable_if<!is_pod<T>, void> move_urange(T* dest, T* first, T* last) {
		for (T* it = first; it != last; ++it, ++dest)
			move_construct(dest, *it);
		destroy_urange(first, last);
	}

	template <class T>
	static inline enable_if<is_pod<T>, void> bmove_urange(T* dest, T* first, T* last) {
		dest += (last - first);
		for (T* it = last; it != first; --it, --dest)
			*(dest - 1) = *(it - 1);
	}

	template <class T>
	static inline enable_if<!is_pod<T>, void> bmove_urange(T* dest, T* first, T* last) {
		dest += (last - first);
		for (T* it = last; it != first; --it, --dest) {
			move_construct(dest - 1, *(it - 1));
			(it - 1)->~T();
		}
	}

	template <class T, class Alloc, size_t Pad>
	inline buf<T, Alloc, Pad>::buf() {
	}

	template <class T, class Alloc, size_t Pad>
	inline buf<T, Alloc, Pad>::buf(const buf& other) {
		this->alloc(other.size());
		copy_urange(m_first, other.m_first, other.m_last);
	}

	template <class T, class Alloc, size_t Pad>
	inline buf<T, Alloc, Pad>::buf(buf&& other) {
		this->m_first = other.m_first, this->m_last = other.m_last, this->m_capacity = other.m_capacity;
		other.m_first = other.m_last = other.m_capacity = nullptr;
	}

	template <class T, class Alloc, size_t Pad>
	inline buf<T, Alloc, Pad>::buf(size_t size) {
		this->alloc(size);
		fill_urange(m_first, m_first + size);
	}

	template <class T, class Alloc, size_t Pad>
	inline buf<T, Alloc, Pad>::buf(size_t size, const T& value) {
		this->alloc(size);
		fill_urange(m_first, m_first + size, value);
	}

	template <class T, class Alloc, size_t Pad>
	inline buf<T, Alloc, Pad>::~buf() {
		if(m_first != nullptr)
		{
			destroy_urange(m_first, m_last);
			Alloc::static_deallocate(m_first, this->capacity());
		}
	}

	template <class T, class Alloc, size_t Pad>
	inline buf<T, Alloc, Pad>& buf<T, Alloc, Pad>::operator=(const buf& other) {
		buf(other).swap(*this);
		return *this;
	}

	template <class T, class Alloc, size_t Pad>
	inline buf<T, Alloc, Pad>& buf<T, Alloc, Pad>::operator=(buf&& other) {
		other.swap(*this);
		return *this;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buf<T, Alloc, Pad>::swap(buf& other) {
		using stl::swap;
		swap(this->m_first, other.m_first);
		swap(this->m_last, other.m_last);
		swap(this->m_capacity, other.m_capacity);
	}

	template <class T, class Alloc, size_t Pad>
	inline void buf<T, Alloc, Pad>::alloc(size_t size) {
		m_first = (T*)Alloc::static_allocate(sizeof(T) * size);
		m_last = m_capacity = m_first + size;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buf<T, Alloc, Pad>::realloc(size_t capacity, bool dealloc) {
		const size_t size = this->size();
		T* first = (T*)Alloc::static_allocate(sizeof(T) * (capacity + Pad));
		move_urange(first, m_first, m_last);
		if (dealloc)
		{
			const size_t oldcapacity = this->capacity();
			Alloc::static_deallocate(m_first, sizeof(T) * (oldcapacity + Pad));
		}
		m_first = first;
		m_last = first + size;
		m_capacity = first + capacity;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buf<T, Alloc, Pad>::reserve(size_t capacity, bool dealloc) {
		if (this->capacity() > capacity + Pad)
			return;
		this->realloc(capacity, dealloc);
	}

	template <class T, class Alloc, size_t Pad>
	inline void buf<T, Alloc, Pad>::resize(size_t size) {
		this->reserve(size);
		fill_urange(m_last, m_first + size);
		destroy_urange(m_first + size, m_last);
		m_last = m_first + size;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buf<T, Alloc, Pad>::resize(size_t size, const T& value) {
		this->reserve(size);
		fill_urange(m_last, m_first + size, value);
		destroy_urange(m_first + size, m_last);
		m_last = m_first + size;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buf<T, Alloc, Pad>::clear() {
		destroy_urange(m_first, m_last);
		m_last = m_first;
	}

	template <class T, class Alloc, size_t Pad>
	inline buffer<T, Alloc, Pad>::buffer(const T* first, const T* last) {
		this->alloc(size_t(last - first));
		this->fill(first, last);
	}

	template <class T, class Alloc, size_t Pad>
	inline buffer<T, Alloc, Pad>::buffer(std::initializer_list<T> list) {
		this->alloc(list.size());
		this->fill(list.begin(), list.end());
	}

	template <class T, class Alloc, size_t Pad>
	inline void buffer<T, Alloc, Pad>::grow(size_t size, bool dealloc) {
		if (size > this->capacity())
			this->realloc((size * 3) / 2, dealloc);
	}

	template <class T, class Alloc, size_t Pad>
	inline void buffer<T, Alloc, Pad>::push_back(const T& t) {
		this->grow(this->size() + 1);
		copy_construct(m_last, t);
		m_last++;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buffer<T, Alloc, Pad>::push_back(T&& t) {
		this->grow(this->size() + 1);
		new(placeholder(), m_last) T(static_cast<T&&>(t));
		m_last++;
	}

	template <class T, class Alloc, size_t Pad>
	template <class... Params>
	inline void buffer<T, Alloc, Pad>::emplace_back(Params&&... params) {
		this->grow(this->size() + 1);
		new(placeholder(), m_last) T(static_cast<Params&&>(params)...);
		m_last++;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buffer<T, Alloc, Pad>::emplace_back() {
		this->grow(this->size() + 1);
		new(placeholder(), m_last) T();
		m_last++;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buffer<T, Alloc, Pad>::pop_back() {
		destroy_urange(m_last - 1, m_last);
		m_last--;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buffer<T, Alloc, Pad>::fill(const T* first, const T* last) {
		copy_urange(m_last, first, last);
		m_last += size_t(last - first);
	}

	template <class T, class Alloc, size_t Pad>
	inline void buffer<T, Alloc, Pad>::append(const T* first, const T* last) {
		const size_t count = last - first;
		this->grow(this->size() + count);
		copy_urange(m_last, first, last);
		m_last += count;
	}

	template <class T, class Alloc, size_t Pad>
	inline void buffer<T, Alloc, Pad>::shrink_to_fit() {
		if (m_capacity == m_last) return;
		if (this->empty()) {
			const size_t capacity = this->capacity();
			Alloc::static_deallocate(m_first, sizeof(T) * (capacity + Pad));
			m_capacity = m_first = m_last = nullptr;
		} else {
			const size_t size = this->size();
			this->realloc(size);
		}
	}

	template <class T, class Alloc, size_t Pad>
	inline T* buffer<T, Alloc, Pad>::spread(T* where, size_t count, bool dealloc) {
		const size_t offset = size_t(where - m_first);
		const size_t newsize = this->size() + count;
		this->grow(newsize, dealloc);
		where = m_first + offset;

		if (where != m_last)
			bmove_urange(where + count, where, m_last);
		m_last = m_first + newsize;
		return where;
	}
}
