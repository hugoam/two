#pragma once

#ifdef USE_STL
#include <string_view>
namespace stl
{
	using std::string_view;
}
#else
#include <stl/stddef.h>
namespace stl {

	class string_view
	{
	public:
		typedef char value_type;
		typedef char* pointer;
		typedef const char* const_pointer;
		typedef char& reference;
		typedef const char& const_reference;
		typedef const_pointer iterator;
		typedef const_pointer const_iterator;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		static constexpr size_type npos = size_type(-1);

		constexpr string_view();
		constexpr string_view(const char* s, size_type count);
		constexpr string_view(const char* s);
		constexpr string_view(const string_view&) = default;
		string_view& operator=(const string_view&) = default;

		constexpr const char* data() const;
		constexpr char operator[](size_type pos) const;
		constexpr size_type size() const;
		constexpr bool empty() const;
		constexpr iterator begin() const;
		constexpr const_iterator cbegin() const;
		constexpr iterator end() const;
		constexpr const_iterator cend() const;
		constexpr string_view substr(size_type pos = 0, size_type count = npos) const;
		constexpr void swap(string_view& v);

	private:
		string_view(decltype(nullptr)) = delete;

		static constexpr size_type strlen(const char*);

		const char* m_str;
		size_type m_size;
	};

	constexpr string_view::string_view()
		: m_str(nullptr)
		, m_size(0)
	{
	}

	constexpr string_view::string_view(const char* s, size_type count)
		: m_str(s)
		, m_size(count)
	{
	}

	constexpr string_view::string_view(const char* s)
		: m_str(s)
		, m_size(strlen(s))
	{
	}

	constexpr const char* string_view::data() const {
		return m_str;
	}

	constexpr char string_view::operator[](size_type pos) const {
		return m_str[pos];
	}

	constexpr string_view::size_type string_view::size() const {
		return m_size;
	}

	constexpr bool string_view::empty() const {
    	return 0 == m_size;
	}

	constexpr string_view::iterator string_view::begin() const {
		return m_str;
	}

	constexpr string_view::const_iterator string_view::cbegin() const {
		return m_str;
	}

	constexpr string_view::iterator string_view::end() const {
		return m_str + m_size;
	}

	constexpr string_view::const_iterator string_view::cend() const {
		return m_str + m_size;
	}

	constexpr string_view string_view::substr(size_type pos, size_type count) const {
		return string_view(m_str + pos, npos == count ? m_size - pos : count);
	}

	constexpr void string_view::swap(string_view& v) {
		const char* strtmp = m_str;
		size_type sizetmp = m_size;
		m_str = v.m_str;
		m_size = v.m_size;
		v.m_str = strtmp;
		v.m_size = sizetmp;
	}

	constexpr string_view::size_type string_view::strlen(const char* s) {
		for(size_t len = 0; ; ++len) {
			if(0 == s[len]) {
				return len;
			}
		}
	}
}
#endif
