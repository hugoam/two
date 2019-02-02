#pragma once

#include <stl/buffer.h>
#include <stl/new.h>
#include <stl/move_tiny.h>
#include <stl/traits.h>

namespace stl {

	template <class T>
	static inline void buffer_destroy_range_traits(T* first, T* last, pod_traits<T, false>) {
		for (; first < last; ++first)
			first->~T();
	}

	template <class T>
	static inline void buffer_destroy_range_traits(T*, T*, pod_traits<T, true>) {
	}

	template <class T>
	static inline void buffer_destroy_range(T* first, T* last) {
		buffer_destroy_range_traits(first, last, pod_traits<T>());
	}

	template <class T>
	static inline void buffer_fill_urange_traits(T* first, T* last, pod_traits<T, false>) {
		for (; first < last; ++first)
			new(placeholder(), first) T();
	}

	template <class T>
	static inline void buffer_fill_urange_traits(T* first, T* last, pod_traits<T, true>) {
		for (; first < last; ++first)
			*first = T();
	}

	template <class T>
	static inline void buffer_fill_urange_traits(T* first, T* last, const T& value, pod_traits<T, false>) {
		for (; first < last; ++first)
			new(placeholder(), first) T(value);
	}

	template <class T>
	static inline void buffer_fill_urange_traits(T* first, T* last, const T& value, pod_traits<T, true>) {
		for (; first < last; ++first)
			*first = value;
	}

	template <class T>
	static inline void buffer_copy_urange_traits(T* dest, const T* first, const T* last, pod_traits<T, false>) {
		for (T* it = first; it != last; ++it, ++dest)
			new(placeholder(), first) T(*it);
	}

	template <class T>
	static inline void buffer_copy_urange_traits(T* dest, const T* first, const T* last, pod_traits<T, true>) {
		for (; first != last; ++first, ++dest)
			*dest = *first;
	}

	template <class T>
	static inline void buffer_move_urange_traits(T* dest, T* first, T* last, pod_traits<T, false>) {
		for (T* it = first; it != last; ++it, ++dest)
			move_construct(dest, *it);
		buffer_destroy_range(first, last);
	}

	template <class T>
	static inline void buffer_move_urange_traits(T* dest, T* first, T* last, pod_traits<T, true>) {
		for (; first != last; ++first, ++dest)
			*dest = *first;
	}

	template <class T>
	static inline void buffer_bmove_urange_traits(T* dest, T* first, T* last, pod_traits<T, false>) {
		dest += (last - first);
		for (T* it = last; it != first; --it, --dest) {
			move_construct(dest - 1, *(it - 1));
			buffer_destroy_range(it - 1, it);
		}
	}

	template <class T>
	static inline void buffer_bmove_urange_traits(T* dest, T* first, T* last, pod_traits<T, true>) {
		dest += (last - first);
		for (T* it = last; it != first; --it, --dest)
			*(dest - 1) = *(it - 1);
	}

	template <class T>
	static inline void buffer_fill_urange(T* first, T* last) {
		buffer_fill_urange_traits(first, last, pod_traits<T>());
	}

	template <class T>
	static inline void buffer_fill_urange(T* first, T* last, const T& value) {
		buffer_fill_urange_traits(first, last, value, pod_traits<T>());
	}

	template <class T>
	static inline void buffer_copy_urange(T* dest, const T* first, const T* last) {
		buffer_copy_urange_traits(dest, first, last, pod_traits<T>());
	}

	template <class T>
	static inline void buffer_move_urange(T* dest, T* first, T* last) {
		buffer_move_urange_traits(dest, first, last, pod_traits<T>());
	}

	template <class T>
	static inline void buffer_bmove_urange(T* dest, T* first, T* last) {
		buffer_bmove_urange_traits(dest, first, last, pod_traits<T>());
	}

	template <class T, class Alloc>
	static inline void string_reset(buffer<T, Alloc>& b, T* storage, size_t capacity) {
		b.first = b.last = storage;
		b.capacity = storage + capacity;
		storage[0] = 0;
	}

	template <class T, class Alloc>
	static inline void string_reset(buffer<T, Alloc>& b, T* storage, size_t capacity, size_t size) {
		b.first = storage;
		b.last = storage + size;
		b.capacity = storage + capacity;
		storage[size] = 0;
	}

	template <class T, class Alloc>
	static inline void buffer_alloc(buffer<T, Alloc>& b, size_t count) {
		typedef T* pointer;
		b.first = (pointer)Alloc::static_allocate(sizeof(T) * count);
		b.last = b.capacity = b.first + count;
		buffer_fill_urange(b.first, b.first + count);
	}

	template <class T, class Alloc>
	static inline void buffer_destroy(buffer<T, Alloc>& b) {
		buffer_destroy_range(b.first, b.last);
		Alloc::static_deallocate(b.first, (size_t)((char*)b.capacity - (char*)b.first));
	}

	template <class T, class Alloc>
	static inline void buffer_realloc(buffer<T, Alloc>& b, size_t capacity, size_t padding = 0, bool nodealloc = false) {
		typedef T* pointer;
		const size_t size = (size_t)(b.last - b.first);
		pointer first = (pointer)Alloc::static_allocate(sizeof(T) * (capacity + padding));
		buffer_move_urange(first, b.first, b.last);
		if(!nodealloc)
			Alloc::static_deallocate(b.first, sizeof(T) * capacity);

		b.first = first;
		b.last = first + size;
		b.capacity = first + capacity;
	}

	template <class T, class Alloc>
	static inline void buffer_reserve(buffer<T, Alloc>& b, size_t capacity, size_t padding = 0, bool nodealloc = false) {
		if(b.first + capacity + padding <= b.capacity)
			return;
		buffer_realloc(b, capacity, padding, nodealloc);
	}

	template <class T, class Alloc>
	static inline void buffer_grow(buffer<T, Alloc>& b, size_t size, size_t padding = 0, bool nodealloc = false) {
		if(b.first + size > b.capacity)
			buffer_realloc(b, (size * 3) / 2, padding, nodealloc);
	}

	template <class T, class Alloc>
	static inline void buffer_grow_count(buffer<T, Alloc>& b, size_t count, size_t padding = 0, bool nodealloc = false) {
		if(b.last + count > b.capacity)
			buffer_realloc(b, ((b.last - b.first + count) * 3) / 2, padding, nodealloc);
	}

	template <class T, class Alloc>
	static inline void string_reserve(buffer<T, Alloc>& b, T* storage, size_t capacity) {
		buffer_reserve(b, capacity, 1, b.first == storage);
	}

	template <class T, class Alloc>
	static inline void buffer_resize(buffer<T, Alloc>& b, size_t size) {
		buffer_reserve(b, size);

		buffer_fill_urange(b.last, b.first + size);
		buffer_destroy_range(b.first + size, b.last);
		b.last = b.first + size;
	}

	template <class T, class Alloc>
	static inline enable_if<is_copy_constructible<T>, void> buffer_resize(buffer<T, Alloc>& b, size_t size, const T& value) {
		buffer_reserve(b, size);

		buffer_fill_urange(b.last, b.first + size, value);
		buffer_destroy_range(b.first + size, b.last);
		b.last = b.first + size;
	}

	template <class T, class Alloc>
	static inline enable_if<!is_copy_constructible<T>, void> buffer_resize(buffer<T, Alloc>& b, size_t size, const T& value) {
		(void)value; buffer_resize(b, size);
	}

	template <class T, class Alloc>
	static inline void string_resize(buffer<T, Alloc>& b, T* storage, size_t size) {
		string_reserve(b, storage, size);

		buffer_fill_urange(b.last, b.first + size + 1);
		b.last = b.first + size;
		*b.last = 0;
	}

	template <class T, class Alloc>
	static inline void string_resize(buffer<T, Alloc>& b, T* storage, size_t size, const T& value) {
		string_reserve(b, storage, size);

		buffer_fill_urange(b.last, b.first + size + 1, value);
		b.last = b.first + size;
		*b.last = 0;
	}

	template <class T, class Alloc>
	static inline void buffer_shrink_to_fit(buffer<T, Alloc>& b, size_t padding = 0) {
		if (b.capacity != b.last) {
			if (b.last == b.first) {
				const size_t capacity = (size_t)(b.capacity - b.first);
				Alloc::static_deallocate(b.first, sizeof(T) * (capacity + padding));
				b.capacity = b.first = b.last = nullptr;
			} else {
				const size_t capacity = (size_t)(b.capacity - b.first);
				const size_t size = (size_t)(b.last - b.first);
				T* newfirst = (T*)Alloc::static_allocate(sizeof(T) * (size + padding));
				buffer_move_urange(newfirst, b.first, b.last);
				Alloc::static_deallocate(b.first, sizeof(T) * (capacity + padding));
				b.first = newfirst;
				b.last = newfirst + size;
				b.capacity = b.last;
			}
		}
	}

	template <class T, class Alloc>
	static inline void buffer_clear(buffer<T, Alloc>& b) {
		buffer_destroy_range(b.first, b.last);
		b.last = b.first;
	}

	template <class T, class Alloc>
	static inline void string_clear(buffer<T, Alloc>& b) {
		b.last = b.first;
		*b.last = 0;
	}

	template <class T, class Alloc>
	static inline T* buffer_insert_spread(buffer<T, Alloc>& b, T* where, size_t count, size_t padding = 0, bool nodealloc = false) {
		const size_t offset = (size_t)(where - b.first);
		const size_t newsize = (size_t)((b.last - b.first) + count);
		buffer_grow(b, newsize, padding, nodealloc);

		where = b.first + offset;

		if (where != b.last)
			buffer_bmove_urange(where + count, where, b.last);

		b.last = b.first + newsize;

		return where;
	}

	template <class T, class Alloc>
	static inline enable_if<is_copy_constructible<T>, T*> buffer_insert(buffer<T, Alloc>& b, T* where, const T* first, const T* last) {
		const size_t count = last - first;
		where = buffer_insert_spread(b, where, count);
		for (; first != last; ++first, ++where)
			new(placeholder(), where) T(*first);
		return where;
	}

	template <class T, class Alloc>
	static inline enable_if<!is_copy_constructible<T>, T*> buffer_insert(buffer<T, Alloc>& b, T* where, const T* first, const T* last) {
		(void)first; (void)last;
		const size_t count = last - first;
		where = buffer_insert_spread(b, where, count);
		for (; first != last; ++first, ++where)
			new(placeholder(), where) T();
		return where;
	}

	template <class T, class Alloc>
	static inline void string_insert(buffer<T, Alloc>& b, T* storage, T* where, const T* first, const T* last) {
		const size_t count = last - first;
		where = buffer_insert_spread(b, where, count, 1, b.first == storage);
		buffer_copy_urange(where, first, last);
		*b.last = 0;
	}

	template <class T, class Alloc>
	static inline void string_copy(buffer<T, Alloc>& b, const T* first, const T* last) {
		buffer_copy_urange(b.last, first, last);
		b.last += last - first;
		*b.last = 0;
	}

	template <class T, class Alloc>
	static inline void string_append(buffer<T, Alloc>& b, T* storage, const T* first, const T* last) {
		const size_t newsize = (size_t)((b.last - b.first) + (last - first));
		buffer_grow(b, newsize, 1, b.first == storage);
		buffer_copy_urange(b.last, first, last);
		b.last += last - first;
		*b.last = 0;
	}

	template <class T, class Alloc>
	static inline enable_if<is_copy_constructible<T>, T*> buffer_insert(buffer<T, Alloc>& b, T* where, const T& value) {
		where = buffer_insert_spread(b, where, 1);
		new(placeholder(), where) T(value);
		return where;
	}

	template <class T, class Alloc>
	static inline enable_if<!is_copy_constructible<T>, T*> buffer_insert(buffer<T, Alloc>& b, T* where, const T& value) {
		(void)value;
		where = buffer_insert_spread(b, where, 1);
		new(placeholder(), where) T();
		return where;
	}

	template <class T, class Alloc>
	static inline T* buffer_insert(buffer<T, Alloc>& b, T* where, T&& value) {
		where = buffer_insert_spread(b, where, 1);
		new(placeholder(), where) T(static_cast<T&&>(value));
		return where;
	}

	template <class T, class Alloc>
	static inline T* buffer_insert(buffer<T, Alloc>& b, T* where) {
		where = buffer_insert_spread(b, where, 1);
		new(placeholder(), where) T();
		return where;
	}

	/*template <class T, class Alloc>
	static inline T* buffer_insert(buffer<T, Alloc>& b, T* where, size_t count) {
		where = buffer_insert_spread(b, where, count);
		for (T* end = where+count; where != end; ++where)
			new(placeholder(), where) T();
		return where;
	}*/

	template <class T, class Alloc, typename... Params>
	static inline void buffer_emplace(buffer<T, Alloc>& b, T* where, size_t count, Params&&... params) {
		where = buffer_insert_spread(b, where, count);
		for(T* end = where + count; where != end; ++where)
			new(placeholder(), where) T(static_cast<Params&&>(params)...);
	}

	template <class T, class Alloc>
	static inline void buffer_append(buffer<T, Alloc>& b) {
		buffer_grow_count(b, 1);
		new(placeholder(), b.last) T();
		++b.last;
	}

	template <class T, class Alloc, typename... Params>
	static inline void buffer_emplace_back(buffer<T, Alloc>& b, Params&&... params) {
		buffer_grow_count(b, 1);
		new(placeholder(), b.last) T(static_cast<Params&&>(params)...);
		++b.last;
	}

	template <class T, class Alloc>
	static inline enable_if<is_copy_constructible<T>> buffer_append(buffer<T, Alloc>& b, const T* value) {
		buffer_grow_count(b, 1);
		new(placeholder(), b.last) T(*value);
		++b.last;
	}

	template <class T, class Alloc>
	static inline enable_if<!is_copy_constructible<T>> buffer_append(buffer<T, Alloc>& b, const T* value) {
		(void)value;
		buffer_grow_count(b, 1);
		new(placeholder(), b.last) T();
		++b.last;
	}

	template <class T, class Alloc>
	static inline T* buffer_erase(buffer<T, Alloc>& b, T* first, T* last) {
		typedef T* pointer;
		const size_t count = (last - first);
		for (pointer it = last, end = b.last, dest = first; it != end; ++it, ++dest)
			move(*dest, *it);

		buffer_destroy_range(b.last - count, b.last);

		b.last -= count;
		return first;
	}

	template <class T, class Alloc>
	static inline T* string_erase(buffer<T, Alloc>& b, T* first, T* last) {
		buffer_erase(b, first, last);
		*b.last = 0;
		return first;
	}

	template <class T, class Alloc>
	static inline void buffer_pop(buffer<T, Alloc>& b) {
		buffer_destroy_range(b.last - 1, b.last);
		b.last--;
	}

	template <class T, class Alloc>
	static inline void string_pop(buffer<T, Alloc>& b) {
		b.last--;
		*b.last = 0;
	}

	template <class T, class Alloc>
	static inline T* buffer_erase_unordered(buffer<T, Alloc>& b, T* first, T* last) {
		typedef T* pointer;
		const size_t count = (last - first);
		const size_t tail = (b.last - last);
		pointer it = b.last - ((count < tail) ? count : tail);
		for (pointer end = b.last, dest = first; it != end; ++it, ++dest)
			move(*dest, *it);

		buffer_destroy_range(b.last - count, b.last);

		b.last -= count;
		return first;
	}

	template <class T, class Alloc>
	static inline void buffer_swap(buffer<T, Alloc>& b, buffer<T, Alloc>& other) {
		typedef T* pointer;
		const pointer tfirst = b.first, tlast = b.last, tcapacity = b.capacity;
		b.first = other.first, b.last = other.last, b.capacity = other.capacity;
		other.first = tfirst, other.last = tlast, other.capacity = tcapacity;
	}

	template <class T, class Alloc>
	static inline void buffer_move(buffer<T, Alloc>& dst, buffer<T, Alloc>& src) {
		dst.first = src.first, dst.last = src.last, dst.capacity = src.capacity;
		src.first = src.last = src.capacity = nullptr;
	}
}
