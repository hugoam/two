#pragma once

#include <stl/tinystl/basic_string.h>
#include <stl/tinystl/buffer_base.h>
#include <stl/tinystl/stddef.h>
#include <stl/tinystl/hash.h>

namespace tinystl {

	template<typename T>
	inline constexpr T min(const T& a, const T& b) { return a < b ? a : b; }

	template<typename T>
	inline constexpr T max(const T& a, const T& b) { return a > b ? a : b; }

	template<typename Alloc>
	inline basic_string<Alloc>::basic_string()
		: m_buffer{ m_small, m_small, m_small + c_nbuffer }
	{}

	template<typename Alloc>
	inline basic_string<Alloc>::basic_string(const basic_string& other)
		: basic_string()
	{
		string_reserve(m_buffer, m_small, other.size());
		string_copy(m_buffer, other.m_buffer.first, other.m_buffer.last);
	}

	template<typename Alloc>
	inline basic_string<Alloc>::basic_string(basic_string&& other)
		: basic_string()
	{
		if(other.m_buffer.first == other.m_small)
			string_copy(m_buffer, other.m_buffer.first, other.m_buffer.last);
		else
			m_buffer = other.m_buffer;
		string_reset(other.m_buffer, other.m_small, c_nbuffer);
	}

	template<typename Alloc>
	inline basic_string<Alloc>::basic_string(const char* s)
		: basic_string()
	{
		size_t len = 0;
		for(const char* it = s; *it; ++it)
			++len;

		string_reserve(m_buffer, m_small, len);
		string_copy(m_buffer, s, s + len);
	}

	template<typename Alloc>
	inline basic_string<Alloc>::basic_string(const char* s, size_t len)
		: basic_string()
	{
		string_reserve(m_buffer, m_small, len);
		string_copy(m_buffer, s, s + len);
	}

	template<typename Alloc>
	inline basic_string<Alloc>::basic_string(size_t len, char c)
		: basic_string()
	{
		string_reserve(m_buffer, m_small, len);
		buffer_fill_urange(m_buffer.first, m_buffer.last, c);
	}

	template<typename Alloc>
	inline basic_string<Alloc>::basic_string(const char* first, const char* last) 
		: basic_string()
	{
		string_reserve(m_buffer, m_small, last - first);
		string_copy(m_buffer, first, last);
	}

	template<typename Alloc>
	inline basic_string<Alloc>::basic_string(std::initializer_list<char> list) 
		: basic_string(list.begin(), list.end())
	{
	}

	template<typename Alloc>
	inline basic_string<Alloc>::~basic_string() {
		if(m_buffer.first != m_small)
			Alloc::static_deallocate(m_buffer.first, m_buffer.capacity - m_buffer.first);
	}

	template<typename Alloc>
	inline basic_string<Alloc>& basic_string<Alloc>::operator=(const basic_string& other) {
		basic_string(other).swap(*this);
		return *this;
	}

	template<typename Alloc>
	basic_string<Alloc>& basic_string<Alloc>::operator=(basic_string&& other) {
		basic_string(static_cast<basic_string&&>(other)).swap(*this);
		return *this;
	}

	template<typename Alloc>
	inline const char* basic_string<Alloc>::data() const {
		return m_buffer.first;
	}

	template<typename Alloc>
	inline char* basic_string<Alloc>::data() {
		return m_buffer.first;
	}

	template<typename Alloc>
	inline const char* basic_string<Alloc>::c_str() const {
		return m_buffer.first;
	}

	template<typename Alloc>
	inline size_t basic_string<Alloc>::size() const {
		return (size_t)(m_buffer.last - m_buffer.first);
	}

	template<typename Alloc>
	inline size_t basic_string<Alloc>::capacity() const {
		return (size_t)(m_buffer.capacity - m_buffer.first);
	}

	template<typename Alloc>
	inline bool basic_string<Alloc>::empty() const {
		return m_buffer.last == m_buffer.first;
	}

	template<typename Alloc>
	inline char& basic_string<Alloc>::operator[](size_t idx) {
		return m_buffer.first[idx];
	}

	template<typename Alloc>
	inline const char& basic_string<Alloc>::operator[](size_t idx) const {
		return m_buffer.first[idx];
	}

	template<typename Alloc>
	inline const char& basic_string<Alloc>::front() const {
		return m_buffer.first[0];
	}

	template<typename Alloc>
	inline char& basic_string<Alloc>::front() {
		return m_buffer.first[0];
	}

	template<typename Alloc>
	inline const char& basic_string<Alloc>::back() const {
		return m_buffer.last[-1];
	}

	template<typename Alloc>
	inline char& basic_string<Alloc>::back() {
		return m_buffer.last[-1];
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::resize(size_t size) {
		string_resize(m_buffer, m_small, size);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::resize(size_t size, char value) {
		string_resize(m_buffer, m_small, size, value);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::clear() {
		string_clear(m_buffer);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::reserve(size_t capacity) {
		string_reserve(m_buffer, m_small, capacity);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::push_back(char c) {
		buffer_grow_count(m_buffer, 1, 1, m_buffer.first == m_small);
		*m_buffer.last++ = c;
		*m_buffer.last = 0;
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::pop_back() {
		string_pop(m_buffer);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::swap(basic_string& other) {
		const pointer tfirst = m_buffer.first, tlast = m_buffer.last, tcapacity = m_buffer.capacity;
		m_buffer.first = other.m_buffer.first, m_buffer.last = other.m_buffer.last, m_buffer.capacity = other.m_buffer.capacity;
		other.m_buffer.first = tfirst, other.m_buffer.last = tlast, other.m_buffer.capacity = tcapacity;

		char tbuffer[c_nbuffer];

		if(m_buffer.first == other.m_small)
			for(pointer it = other.m_small, end = m_buffer.last, out = tbuffer; it != end; ++it, ++out)
				*out = *it;

		if(other.m_buffer.first == m_small) {
			string_reset(other.m_buffer, other.m_small, c_nbuffer, other.m_buffer.last - other.m_buffer.first);
			for(pointer it = other.m_buffer.first, end = other.m_buffer.last, in = m_small; it != end; ++it, ++in)
				*it = *in;
			*other.m_buffer.last = 0;
		}

		if(m_buffer.first == other.m_small) {
			string_reset(m_buffer, m_small, c_nbuffer, m_buffer.last - m_buffer.first);
			for(pointer it = m_buffer.first, end = m_buffer.last, in = tbuffer; it != end; ++it, ++in)
				*it = *in;
			*m_buffer.last = 0;
		}
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::shrink_to_fit() {
		if(m_buffer.first != m_small)
			buffer_shrink_to_fit(m_buffer, 1);
	}

	template<typename Alloc>
	inline typename basic_string<Alloc>::iterator basic_string<Alloc>::begin() {
		return m_buffer.first;
	}

	template<typename Alloc>
	inline typename basic_string<Alloc>::iterator basic_string<Alloc>::end() {
		return m_buffer.last;
	}

	template<typename Alloc>
	inline typename basic_string<Alloc>::const_iterator basic_string<Alloc>::begin() const {
		return m_buffer.first;
	}

	template<typename Alloc>
	inline typename basic_string<Alloc>::const_iterator basic_string<Alloc>::end() const {
		return m_buffer.last;
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::append(const char* first, const char* last) {
		string_append(m_buffer, m_small, first, last);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::append(const basic_string& other) {
		string_append(m_buffer, m_small, other.begin(), other.end());
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::assign(const char* first, const char* last) {
		string_clear(m_buffer);
		string_append(m_buffer, m_small, first, last);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::assign(const char* sz, size_t n) {
		string_clear(m_buffer);
		string_append(m_buffer, m_small, sz, sz + n);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::insert(size_t where, char value) {
		(void)where; (void)value; //string_insert(m_buffer, m_small, m_buffer.first + where, value);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::insert(size_t where, const char* first, const char* last) {
		string_insert(m_buffer, m_small, m_buffer.first + where, first, last);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::insert(size_t where, const basic_string& other) {
		string_insert(m_buffer, m_small, m_buffer.first + where, other.begin(), other.end());
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::insert(iterator where, char value) {
		(void)where; (void)value; //string_insert(m_buffer, m_small, where, value);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::insert(iterator where, const char* first, const char* last) {
		string_insert(m_buffer, m_small, where, first, last);
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::insert(iterator where, const basic_string& other) {
		string_insert(m_buffer, m_small, where, other.begin(), other.end());
	}

	template<typename Alloc>
	inline basic_string<Alloc>& basic_string<Alloc>::operator+=(const basic_string& other) {
		string_append(m_buffer, m_small, other.begin(), other.end());
		return *this;
	}

	template<typename Alloc>
	inline void basic_string<Alloc>::erase(size_t pos, size_t len) {
		string_erase(m_buffer, m_buffer.first + pos, len == npos ? m_buffer.last : m_buffer.first + pos + len);
	}

	template<typename Alloc>
	inline typename basic_string<Alloc>::iterator basic_string<Alloc>::erase(iterator where) {
		return string_erase(m_buffer, where, where + 1);
	}

	template<typename Alloc>
	inline typename basic_string<Alloc>::iterator basic_string<Alloc>::erase(iterator first, iterator last) {
		return string_erase(m_buffer, first, last);
	}

	template<typename Alloc>
	inline basic_string<Alloc> basic_string<Alloc>::substr(size_t begin, size_t count) const {
		return basic_string(m_buffer.first + begin, min(count, this->size() - begin));
	}

	template<typename Alloc>
	inline int basic_string<Alloc>::compare(const basic_string& other) const {
		pointer first1 = m_buffer.first;
		pointer first2 = other.m_buffer.first;
		const pointer last1 = m_buffer.last;
		const pointer last2 = other.m_buffer.last;

		const size_t count1 = size_t(last1 - first1);
		const size_t count2 = size_t(last2 - first2);
		size_t count = count1 < count2 ? count1 : count2;

		for(; 0 < count; --count, ++first1, ++first2)
			if(*first1 != *first2)
			{
				return (*first1 < *first2 ? -1 : +1);
			}

		if(count1 < count2) return -1;
		if(count1 > count2) return 1;
		return 0;
	}

	inline int string_compare(const char* first1, const char* first2, size_t count)
	{
		for(; 0 < count; --count, ++first1, ++first2)
			if(*first1 != *first2)
			{
				return *first1 < *first2 ? -1 : 1;
			}
		return 0;
	}

	inline const char* string_find(const char* first, size_t count, const char& c)
	{
		for(; 0 < count; --count, ++first)
			if(*first == c)
			{
				return first;
			}
		return nullptr;
	}

	template<typename Alloc>
	inline size_t basic_string<Alloc>::find(char c, const size_t offset) const {
		const size_t hay_size = size();
		const char* hay = m_buffer.first;
		if(offset < hay_size)
		{
			const char* match = string_find(hay + offset, hay_size - offset, c);
			if(match)
				return size_t(match - m_buffer.first);
		}

		return size_t(-1);
	}

	template<typename Alloc>
	inline size_t basic_string<Alloc>::rfind(char c, const size_t offset) const {
		const size_t hay_size = size();
		const char* hay = m_buffer.first;
		if(hay_size != 0)
			for(const char* current = hay + min(offset, hay_size - 1); current != hay; --current)
			{
				if(*current == c)
					return size_t(current - hay);
			}

		return size_t(-1);
	}

	template<typename Alloc>
	inline size_t basic_string<Alloc>::find(const basic_string& other, const size_t offset) const {
		const char* hay = this->begin();
		const char* needle = other.begin();
		const size_t hay_size = size();
		const size_t needle_size = other.size();

		if(needle_size > hay_size || offset > hay_size - needle_size)
			return size_t(-1);
		if(needle_size == 0)
			return offset;

		const char* last_possible = hay + (hay_size - needle_size) + 1;
		for(const char* current = hay + offset; ; ++current)
		{
			current = string_find(current, size_t(last_possible - current), *needle);
			if(!current)
				return size_t(-1);
			if(string_compare(current, needle, needle_size) == 0)
				return size_t(current - hay);
		}
	}

	template<typename Alloc>
	inline size_t basic_string<Alloc>::rfind(const basic_string& other, const size_t offset) const {
		const char* hay = this->begin();
		const char* needle = other.begin();
		const size_t hay_size = this->size();
		const size_t needle_size = other.size();

		if(needle_size == 0)
			return min(offset, hay_size);

		if(needle_size <= hay_size)
			for(const char* current = hay + min(offset, hay_size - needle_size); current != hay; --current)
			{
				if(*current == *needle && string_compare(current, needle, needle_size) == 0)
				{
					return size_t(current - hay);
				}
			}

		return size_t(-1);
	}

	template<typename Alloc>
	inline bool basic_string<Alloc>::operator==(const basic_string& other) const {
		const size_t lsize = this->size(), rsize = other.size();
		if (lsize != rsize)
			return false;

		const char* lit = this->c_str();
		const char* rit = other.c_str();
		const char* lend = lit + lsize;
		while (lit != lend)
			if (*lit++ != *rit++)
				return false;

		return true;
	}

	template<typename Alloc>
	inline bool basic_string<Alloc>::operator!=(const basic_string& other) const {
		return !(*this == other);
	}

	template<typename Alloc>
	inline bool basic_string<Alloc>::operator<(const basic_string& other) const {
		return this->compare(other) < 0;
	}
}
