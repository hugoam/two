#pragma once

#include <stl/vector.h>
#include <stl/buffer.hpp>
#include <stl/algorithm.h>

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
