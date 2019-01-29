#pragma once

#include <stl/tinystl/vector.h>
#include <stl/tinystl/buffer_base.h>

namespace tinystl {
	
	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector() {
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(const vector& other) {
		buffer_reserve(m_buffer, other.size());
		buffer_insert(m_buffer, m_buffer.last, other.m_buffer.first, other.m_buffer.last);
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(vector&& other) {
		buffer_move(m_buffer, other.m_buffer);
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(size_t size) {
		buffer_alloc(m_buffer, size);
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(size_t size, const T& value) {
		buffer_resize(m_buffer, size, value);
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(const T* first, const T* last) {
		buffer_insert(m_buffer, m_buffer.last, first, last);
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(std::initializer_list<T> list) {
		buffer_insert(m_buffer, m_buffer.last, list.begin(), list.end());
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::~vector() {
		buffer_destroy(m_buffer);
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& other) {
		vector(other).swap(*this);
		return *this;
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& other) {
		buffer_destroy(m_buffer);
		buffer_move(m_buffer, other.m_buffer);
		return *this;
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::assign(const T* first, const T* last) {
		buffer_clear(m_buffer);
		buffer_insert(m_buffer, m_buffer.last, first, last);
	}

	template<typename T, typename Alloc>
	inline const T* vector<T, Alloc>::data() const {
		return m_buffer.first;
	}

	template<typename T, typename Alloc>
	inline T* vector<T, Alloc>::data() {
		return m_buffer.first;
	}

	template<typename T, typename Alloc>
	inline size_t vector<T, Alloc>::size() const {
		return (size_t)(m_buffer.last - m_buffer.first);
	}

	template<typename T, typename Alloc>
	inline size_t vector<T, Alloc>::capacity() const {
		return (size_t)(m_buffer.capacity - m_buffer.first);
	}

	template<typename T, typename Alloc>
	inline bool vector<T, Alloc>::empty() const {
		return m_buffer.last == m_buffer.first;
	}

	template<typename T, typename Alloc>
	inline T& vector<T, Alloc>::operator[](size_t idx) {
		return m_buffer.first[idx];
	}

	template<typename T, typename Alloc>
	inline const T& vector<T, Alloc>::operator[](size_t idx) const {
		return m_buffer.first[idx];
	}

	template<typename T, typename Alloc>
	inline const T& vector<T, Alloc>::front() const {
		return m_buffer.first[0];
	}

	template<typename T, typename Alloc>
	inline T& vector<T, Alloc>::front() {
		return m_buffer.first[0];
	}

	template<typename T, typename Alloc>
	inline const T& vector<T, Alloc>::back() const {
		return m_buffer.last[-1];
	}

	template<typename T, typename Alloc>
	inline T& vector<T, Alloc>::back() {
		return m_buffer.last[-1];
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::resize(size_t size) {
		buffer_resize(m_buffer, size);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::resize(size_t size, const T& value) {
		buffer_resize(m_buffer, size, value);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::clear() {
		buffer_clear(m_buffer);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::reserve(size_t capacity) {
		buffer_reserve(m_buffer, capacity);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::push_back(const T& t) {
		buffer_append(m_buffer, &t);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::push_back(T&& t) {
		buffer_emplace_back(m_buffer, static_cast<T&&>(t));
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::emplace_back() {
		buffer_append(m_buffer);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::emplace_back(T&& t) {
		buffer_emplace_back(m_buffer, static_cast<T&&>(t));
	}

	template<typename T, typename Alloc>
	template<typename... Params>
	inline void vector<T, Alloc>::emplace_back(Params&&... params) {
		buffer_emplace_back(m_buffer, static_cast<Params&&>(params)...);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::pop_back() {
		buffer_pop(m_buffer);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::shrink_to_fit() {
		buffer_shrink_to_fit(m_buffer);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::swap(vector& other) {
		buffer_swap(m_buffer, other.m_buffer);
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T,Alloc>::begin() {
		return m_buffer.first;
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T,Alloc>::end() {
		return m_buffer.last;
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::const_iterator vector<T,Alloc>::begin() const {
		return m_buffer.first;
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::const_iterator vector<T,Alloc>::end() const {
		return m_buffer.last;
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator where) {
		return buffer_insert(m_buffer, where);
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator where, const T& value) {
		return buffer_insert(m_buffer, where, value);
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator where, T&& value) {
		return buffer_insert(m_buffer, where, static_cast<T&&>(value));
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator where, const T* first, const T* last) {
		return buffer_insert(m_buffer, where, first, last);
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator where) {
		return buffer_erase(m_buffer, where, where + 1);
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last) {
		return buffer_erase(m_buffer, first, last);
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase_unordered(iterator where) {
		return buffer_erase_unordered(m_buffer, where, where + 1);
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase_unordered(iterator first, iterator last) {
		return buffer_erase_unordered(m_buffer, first, last);
	}

	template<typename T, typename Alloc>
	template<typename... Params>
	void vector<T, Alloc>::emplace(typename vector::iterator where, Params&&... params) {
		buffer_emplace(m_buffer, where, 1, static_cast<Params&&>(params)...);
	}
}
