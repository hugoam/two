#pragma once

#include <stl/vector.h>
#include <stl/buffer.h>
#include <stl/new.h>
#include <stl/swap.h>
#include <stl/move_tiny.h>
#include <stl/traits.h>
#include <stl/algorithm.h>
#include <stl/buffer.hpp>

#ifdef USE_UVECTOR
#include <stl/ubuffer.hpp>
#endif

namespace stl {

#ifdef USE_UVECTOR
#elif defined USE_BUFFER
#else
	template <class T, class Alloc>
	inline vector<T, Alloc>::vector() {
	}

	template <class T, class Alloc>
	inline vector<T, Alloc>::vector(const vector& other) {
		this->alloc(other.size());
		copy_urange(this->m_first, other.m_first, other.m_last);
	}

	template <class T, class Alloc>
	inline vector<T, Alloc>::vector(vector&& other) {
		this->m_first = other.m_first, this->m_last = other.m_last, this->m_capacity = other.m_capacity;
		other.m_first = other.m_last = other.m_capacity = nullptr;
	}

	template <class T, class Alloc>
	inline vector<T, Alloc>::vector(size_t size) {
		this->alloc(size);
		fill_urange(this->m_first, this->m_first + size);
	}

	template <class T, class Alloc>
	inline vector<T, Alloc>::vector(size_t size, const T& value) {
		this->alloc(size);
		fill_urange(this->m_first, this->m_first + size, value);
	}

	template <class T, class Alloc>
	inline vector<T, Alloc>::vector(const T* first, const T* last) {
		this->alloc(size_t(last - first));
		copy_urange(this->m_first, first, last);
	}

	template <class T, class Alloc>
	inline vector<T, Alloc>::vector(std::initializer_list<T> list) {
		this->alloc(list.size());
		copy_urange(this->m_first, list.begin(), list.end());
	}

	template <class T, class Alloc>
	inline vector<T, Alloc>::~vector() {
		destroy_urange(this->m_first, this->m_last);
		Alloc::static_deallocate(this->m_first, this->capacity());
	}

	template <class T, class Alloc>
	inline vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& other) {
		vector(other).swap(*this);
		return *this;
	}

	template <class T, class Alloc>
	inline vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& other) {
		other.swap(*this);
		return *this;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::swap(vector& other) {
		using stl::swap;
		swap(this->m_first, other.m_first);
		swap(this->m_last, other.m_last);
		swap(this->m_capacity, other.m_capacity);
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::alloc(size_t size) {
		this->m_first = (T*)Alloc::static_allocate(sizeof(T) * size);
		this->m_last = this->m_capacity = this->m_first + size;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::realloc(size_t capacity, bool dealloc) {
		const size_t size = this->size();
		T* first = (T*)Alloc::static_allocate(sizeof(T) * capacity);
		move_urange(first, this->m_first, this->m_last);
		if(dealloc)
		{
			const size_t oldcapacity = this->capacity();
			Alloc::static_deallocate(this->m_first, sizeof(T) * oldcapacity);
		}
		this->m_first = first;
		this->m_last = first + size;
		this->m_capacity = first + capacity;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::reserve(size_t capacity, bool dealloc) {
		if(this->capacity() > capacity)
			return;
		this->realloc(capacity, dealloc);
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::resize(size_t size) {
		this->reserve(size);
		fill_urange(this->m_last, this->m_first + size);
		destroy_urange(this->m_first + size, this->m_last);
		this->m_last = this->m_first + size;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::resize(size_t size, const T& value) {
		this->reserve(size);
		fill_urange(this->m_last, this->m_first + size, value);
		destroy_urange(this->m_first + size, this->m_last);
		this->m_last = this->m_first + size;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::clear() {
		destroy_urange(this->m_first, this->m_last);
		this->m_last = this->m_first;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::grow(size_t size, bool dealloc) {
		if(size > this->capacity())
			this->realloc((size * 3) / 2, dealloc);
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::push_back(const T& t) {
		this->grow(this->size() + 1);
		copy_construct(this->m_last, t);
		this->m_last++;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::push_back(T&& t) {
		this->grow(this->size() + 1);
		new(placeholder(), this->m_last) T(static_cast<T&&>(t));
		this->m_last++;
	}

	template <class T, class Alloc>
	template <class... Params>
	inline void vector<T, Alloc>::emplace_back(Params&&... params) {
		this->grow(this->size() + 1);
		new(placeholder(), this->m_last) T(static_cast<Params&&>(params)...);
		this->m_last++;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::emplace_back() {
		this->grow(this->size() + 1);
		new(placeholder(), this->m_last) T();
		this->m_last++;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::pop_back() {
		destroy_urange(this->m_last - 1, this->m_last);
		this->m_last--;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::append(const T* first, const T* last) {
		const size_t count = last - first;
		this->grow(this->size() + count);
		copy_urange(this->m_last, first, last);
		this->m_last += count;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::shrink_to_fit() {
		if(this->m_capacity == this->m_last) return;
		if(this->empty()) {
			const size_t capacity = this->capacity();
			Alloc::static_deallocate(this->m_first, sizeof(T) * capacity);
			this->m_capacity = this->m_first = this->m_last = nullptr;
		} else {
			const size_t size = this->size();
			this->realloc(size);
		}
	}

	template <class T, class Alloc>
	inline T* vector<T, Alloc>::spread(T* where, size_t count, bool dealloc) {
		const size_t offset = size_t(where - this->m_first);
		const size_t newsize = this->size() + count;
		this->grow(newsize, dealloc);
		where = this->m_first + offset;

		if(where != this->m_last)
			bmove_urange(where + count, where, this->m_last);
		this->m_last = this->m_first + newsize;
		return where;
	}

	template <class T, class Alloc>
	inline void vector<T, Alloc>::assign(const T* first, const T* last) {
		this->clear();
		this->append(first, last);
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator where) {
		where = this->spread(where, 1);
		new(placeholder(), where) T();
		return where;
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator where, const T& value) {
		where = this->spread(where, 1);
		copy_construct(where, value);
		return where;
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator where, T&& value) {
		where = this->spread(where, 1);
		new(placeholder(), where) T(static_cast<T&&>(value));
		return where;
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator where, const T* first, const T* last) {
		const size_t count = last - first;
		where = this->spread(where, count);
		copy_urange(where, first, last);
		return where;
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator where) {
		return this->erase(where, where + 1);
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last) {
		const size_t count = (last - first);
		for(pointer it = last, end = this->m_last, dest = first; it != end; ++it, ++dest)
			move(*dest, *it);

		destroy_urange(this->m_last - count, this->m_last);

		this->m_last -= count;
		return first;
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase_unstable(iterator where) {
		return this->erase_unstable(where, where + 1);
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase_unstable(iterator first, iterator last) {
		const size_t count = (last - first);
		const size_t tail = (this->m_last - last);
		pointer it = this->m_last - ((count < tail) ? count : tail);
		for(pointer end = this->m_last, dest = first; it != end; ++it, ++dest)
			move(*dest, *it);

		destroy_urange(this->m_last - count, this->m_last);

		this->m_last -= count;
		return first;
	}

	template <class T, class Alloc>
	template <class... Params>
	inline void vector<T, Alloc>::emplace(iterator where, Params&&... params) {
		where = this->spread(where, 1);
		new(placeholder(), where) T(static_cast<Params&&>(params)...);
	}
#endif

	template <class T, class Alloc>
	inline bool operator==(const vector<T, Alloc>& left, const vector<T, Alloc>& right)
	{
		auto equal_to = [](auto&& left, auto&& right)
		{
			return static_cast<decltype(left) && >(left) == static_cast<decltype(right) && >(right);
		};
		return left.size() == right.size() && equal(left.begin(), left.end(), right.begin(), equal_to);
	}
}
