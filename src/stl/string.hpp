#pragma once

#include <stl/string.h>
#include <stl/buffer.hpp>
#include <stl/stddef.h>
#include <stl/hash.h>

namespace stl {

	template <class T>
	inline constexpr T min(const T& a, const T& b) { return a < b ? a : b; }

	template <class T>
	inline constexpr T max(const T& a, const T& b) { return a > b ? a : b; }

	template <class Alloc>
	inline basic_string<Alloc>::basic_string()
	{
		m_first = m_last = m_small;
		m_capacity = m_small + c_nbuffer;
	}

	template <class Alloc>
	inline basic_string<Alloc>::basic_string(const basic_string& other)
		: basic_string()
	{
		this->reserve(other.size());
		this->fill(other.m_first, other.m_last);
	}

	template <class Alloc>
	inline basic_string<Alloc>::basic_string(basic_string&& other)
		: basic_string()
	{
		if(other.m_first == other.m_small)
			this->fill(other.m_first, other.m_last);
		else
			buffer<char, Alloc, 1>::swap(other);
		other.reset(0);
	}

	template <class Alloc>
	inline basic_string<Alloc>::basic_string(const char* s)
		: basic_string()
	{
		size_t len = 0;
		for(const char* it = s; *it; ++it)
			++len;

		this->reserve(len);
		this->fill(s, s + len);
	}

	template <class Alloc>
	inline basic_string<Alloc>::basic_string(const char* s, size_t len)
		: basic_string()
	{
		this->reserve(len);
		this->fill(s, s + len);
	}

	template <class Alloc>
	inline basic_string<Alloc>::basic_string(size_t len, char c)
		: basic_string()
	{
		this->reserve(len);
		fill_urange(m_first, m_last, c);
	}

	template <class Alloc>
	inline basic_string<Alloc>::basic_string(const char* first, const char* last) 
		: basic_string()
	{
		this->reserve(last - first);
		this->fill(first, last);
	}

	template <class Alloc>
	inline basic_string<Alloc>::basic_string(std::initializer_list<char> list) 
		: basic_string(list.begin(), list.end())
	{}

	template <class Alloc>
	inline basic_string<Alloc>::~basic_string() {
		if(m_first == m_small)
			m_first = m_last = m_capacity = nullptr;
	}

	template <class Alloc>
	inline const char* basic_string<Alloc>::c_str() const {
		return m_first;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::reset(size_t size) {
		m_first = m_small;
		m_last = m_small + size;
		m_capacity = m_small + c_nbuffer;
		m_small[size] = 0;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::fill(const char* first, const char* last)
	{
		copy_urange(m_last, first, last);
		m_last += last - first;
		*m_last = 0;
	}

	template <class Alloc>
	inline basic_string<Alloc>& basic_string<Alloc>::operator=(const basic_string& other) {
		basic_string(other).swap(*this);
		return *this;
	}

	template <class Alloc>
	basic_string<Alloc>& basic_string<Alloc>::operator=(basic_string&& other) {
		other.swap(*this);
		return *this;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::resize(size_t size) {
		this->reserve(size);
		fill_urange(m_last, m_first + size + 1);
		m_last = m_first + size;
		*m_last = 0;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::resize(size_t size, char value) {
		this->reserve(size);
		fill_urange(m_last, m_first + size + 1, value);
		m_last = m_first + size;
		*m_last = 0;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::clear() {
		m_last = m_first;
		*m_last = 0;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::reserve(size_t capacity) {
		buffer<char, Alloc, 1>::reserve(capacity, m_first == m_small);
	}

	template <class Alloc>
	inline void basic_string<Alloc>::push_back(char c) {
		this->grow(this->size() + 1, m_first == m_small);
		*m_last++ = c;
		*m_last = 0;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::pop_back() {
		m_last--;
		*m_last = 0;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::swap(basic_string& other) {
		buffer<char, Alloc, 1>::swap(other);

		char tbuffer[c_nbuffer];

		if(m_first == other.m_small)
			for(pointer it = other.m_small, end = m_last, out = tbuffer; it != end; ++it, ++out)
				*out = *it;

		if(other.m_first == m_small) {
			other.reset(other.size());
			for(pointer it = other.m_first, end = other.m_last, in = m_small; it != end; ++it, ++in)
				*it = *in;
			*other.m_last = 0;
		}

		if(m_first == other.m_small) {
			this->reset(this->size());
			for(pointer it = m_first, end = m_last, in = tbuffer; it != end; ++it, ++in)
				*it = *in;
			*m_last = 0;
		}
	}

	template <class Alloc>
	inline void basic_string<Alloc>::shrink_to_fit() {
		if(m_first != m_small)
			buffer<char, Alloc, 1>::shrink_to_fit();
	}

	template <class Alloc>
	inline void basic_string<Alloc>::append(const char* first, const char* last) {
		const size_t newsize = size_t(this->size() + (last - first));
		this->grow(newsize, m_first == m_small);
		copy_urange(m_last, first, last);
		m_last += last - first;
		*m_last = 0;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::append(const basic_string& other) {
		this->append(other.begin(), other.end());
	}

	template <class Alloc>
	inline void basic_string<Alloc>::assign(const char* first, const char* last) {
		this->clear();
		this->append(first, last);
	}

	template <class Alloc>
	inline void basic_string<Alloc>::assign(const char* s, size_t n) {
		this->clear();
		this->append(s, s + n);
	}

	template <class Alloc>
	inline void basic_string<Alloc>::insert(size_t where, char value) {
		this->insert(m_first + where, value);
	}

	template <class Alloc>
	inline void basic_string<Alloc>::insert(size_t where, const char* first, const char* last) {
		this->insert(m_first + where, first, last);
	}

	template <class Alloc>
	inline void basic_string<Alloc>::insert(size_t where, const basic_string& other) {
		this->insert(m_first + where, other.begin(), other.end());
	}

	template <class Alloc>
	inline void basic_string<Alloc>::insert(iterator where, char value) {
		(void)where; (void)value; //string_insert(m_buffer, m_small, where, value);
	}

	template <class Alloc>
	inline void basic_string<Alloc>::insert(iterator where, const char* first, const char* last) {
		const size_t count = last - first;
		where = this->spread(where, count, m_first == m_small);
		copy_urange(where, first, last);
		*m_last = 0;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::insert(iterator where, const basic_string& other) {
		this->insert(where, other.begin(), other.end());
	}

	template <class Alloc>
	inline basic_string<Alloc>& basic_string<Alloc>::operator+=(const basic_string& other) {
		this->append(other.begin(), other.end());
		return *this;
	}

	template <class Alloc>
	inline void basic_string<Alloc>::erase(size_t pos, size_t len) {
		this->erase(m_first + pos, len == npos ? m_last : m_first + pos + len);
	}

	template <class Alloc>
	inline typename basic_string<Alloc>::iterator basic_string<Alloc>::erase(iterator where) {
		return this->erase(where, where + 1);
	}

	template <class Alloc>
	inline typename basic_string<Alloc>::iterator basic_string<Alloc>::erase(iterator first, iterator last) {
		const size_t count = (last - first);
		for (pointer it = last, end = m_last, dest = first; it != end; ++it, ++dest)
			*dest = *it;
		m_last -= count;
		*m_last = 0;
		return first;
	}

	template <class Alloc>
	inline basic_string<Alloc> basic_string<Alloc>::substr(size_t begin, size_t count) const {
		return basic_string(m_first + begin, min(count, this->size() - begin));
	}

	template <class Alloc>
	inline int basic_string<Alloc>::compare(const basic_string& other) const {
		pointer first1 = m_first;
		pointer first2 = other.m_first;
		const pointer last1 = m_last;
		const pointer last2 = other.m_last;

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

	template <class Alloc>
	inline size_t basic_string<Alloc>::find(char c, const size_t offset) const {
		const size_t hay_size = size();
		const char* hay = m_first;
		if(offset < hay_size)
		{
			const char* match = string_find(hay + offset, hay_size - offset, c);
			if(match)
				return size_t(match - m_first);
		}

		return size_t(-1);
	}

	template <class Alloc>
	inline size_t basic_string<Alloc>::rfind(char c, const size_t offset) const {
		const size_t hay_size = size();
		const char* hay = m_first;
		if(hay_size != 0)
			for(const char* current = hay + min(offset, hay_size - 1); current != hay; --current)
			{
				if(*current == c)
					return size_t(current - hay);
			}

		return size_t(-1);
	}

	template <class Alloc>
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

	template <class Alloc>
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

	template <class Alloc>
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

	template <class Alloc>
	inline bool basic_string<Alloc>::operator!=(const basic_string& other) const {
		return !(*this == other);
	}

	template <class Alloc>
	inline bool basic_string<Alloc>::operator<(const basic_string& other) const {
		return this->compare(other) < 0;
	}
}
