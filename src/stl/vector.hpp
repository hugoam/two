#pragma once

#include <stl/vector.h>
#include <stl/buffer.hpp>

#ifdef USE_UVECTOR
#include <stl/ubuffer.hpp>
#endif

namespace stl {

#ifdef USE_UVECTOR
#elif defined USE_BUFFER
#else
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
		for (pointer it = last, end = m_last, dest = first; it != end; ++it, ++dest)
			move(*dest, *it);

		destroy_urange(m_last - count, m_last);

		m_last -= count;
		return first;
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase_unordered(iterator where) {
		return this->erase_unordered(where, where + 1);
	}

	template <class T, class Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase_unordered(iterator first, iterator last) {
		const size_t count = (last - first);
		const size_t tail = (m_last - last);
		pointer it = m_last - ((count < tail) ? count : tail);
		for (pointer end = m_last, dest = first; it != end; ++it, ++dest)
			move(*dest, *it);

		destroy_urange(m_last - count, m_last);

		m_last -= count;
		return first;
	}

	template <class T, class Alloc>
	template <class... Params>
	inline void vector<T, Alloc>::emplace(typename vector::iterator where, Params&&... params) {
		//buffer_emplace(m_buffer, where, 1, static_cast<Params&&>(params)...);
	}
#endif
}
