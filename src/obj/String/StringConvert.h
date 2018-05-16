//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

/* std */
#include <obj/Generated/Forward.h>
#include <obj/String/String.h>

#include <memory>
#include <algorithm>
#include <sstream>

namespace mud
{
	template <typename T, typename = int>
	struct is_string_convertible : std::false_type { };

	template <typename T>
	struct is_string_convertible <T, decltype(std::to_string(std::declval<T>()), 0)> : std::true_type { };

	template <class T>
	inline void string_to_type(const string& str, T& val)
	{
		std::stringstream ss(str);
		ss >> val;
	}

	template <> inline void string_to_type(const string& str, float& val) { val = std::stof(str); }
	template <> inline void string_to_type(const string& str, double& val) { val = std::stod(str); }
	template <> inline void string_to_type(const string& str, int& val) { val = std::stoi(str); }
	template <> inline void string_to_type(const string& str, unsigned int& val) { val = std::stoi(str); }

	template <class T>
	inline typename std::enable_if<is_string_convertible<T>::value, void>::type
		type_to_string(const T& val, string& str)
	{
		str = std::to_string(val);
	}

	template <class T>
	inline typename std::enable_if<!is_string_convertible<T>::value, void>::type
		type_to_string(const T& val, string& str)
	{
		std::stringstream ss;
		ss << val;
		str = ss.str();
	}

	// Vector - string conversion
	template <class T>
	inline void vector_to_string(const T& val, string& str)
	{
		for(const typename T::value_type& v : val)
		{
			str += to_string(v, str);
			str += ",";
		}
		if(val.size() > 0)
			str.pop_back();
	}

	template <class T>
	inline void string_to_vector(const string& str, T& vec)
	{
		auto first = str.begin();
		auto end = str.end();
		auto second = std::find(first, end, ',');

		while(second != end)
		{
			second = std::find(first, end, ',');
			vec.push_back(from_string<typename T::value_type>(str.substr(first - str.begin(), second - first)));
			
			if(second != end)
				first = second + 1;
		}
	}

	template <class T, size_t size>
	inline void fixed_vector_to_string(const T& val, string& str)
	{
		for(size_t i = 0; i < size; ++i)
		{
			str += to_string(val[i]);
			str += ",";
		}
		str.pop_back();
	}

	template <class Vec, class T>
	inline void string_to_fixed_vector(const string& str, Vec& vec)
	{
		auto first = str.begin();
		auto end = str.end();
		auto second = std::find(first, end, ',');

		size_t i = 0;
		while(second != end)
		{
			second = std::find(first, end, ',');
			vec[i] = from_string<T>(str.substr(first - str.begin(), second - first));

			++i;
			if(second != end)
				first = second + 1;
		}
	}

	template <class T>
	struct StringConverter
	{
		static inline void to(const T& val, string& str) { type_to_string(val, str); }
		static inline void from(const string& str, T& val) { string_to_type<T>(str, val); }
	};

	template <class T>
	struct StringConverter<std::vector<T>>
	{
		static inline void to(const std::vector<T>& val, string& str) { vector_to_string(val, str); }
		static inline void from(const string& str, std::vector<T>& vec) { string_to_vector(str, vec); }
	};

	template <class T, size_t s>
	struct StringConverter<std::array<T, s>>
	{
		static inline void to(const std::array<T, s>& val, string& str) { fixed_vector_to_string<std::array<T, s>, s>(val, str); }
		static inline void from(const string& str, std::array<T, s>& vec) { string_to_fixed_vector<std::array<T, s>, T>(str, vec); }
	};

	template <class T_Enum>
	inline void flags_from_string(const string& str, T_Enum& value)
	{
		std::vector<string> names = split_string(to_upper(str), "|");
		for(const string& name : names)
			value = static_cast<T_Enum>(value | from_string<T_Enum>(name));
	}

	template <class T_Enum>
	inline T_Enum flags_from_string(const string& str) { T_Enum value = T_Enum(0); flags_from_string(str, value); return value; }

	template <class T_Enum, size_t Count>
	inline void flags_to_string(const T_Enum& value, string& str)
	{
		for(size_t shift = 0; shift < Count; ++shift)
			if(value & (1 << shift))
				str += (str.empty() ? "" : "|") + to_string<T_Enum>(static_cast<T_Enum>((1 << shift)));
	}

	template <class T_Enum, size_t Count>
	inline string flags_to_string(const T_Enum& value) { string str; flags_to_string<T_Enum, Count>(value, str); return str; }

	template <class T>
	inline void from_string(const string& str, T& val) { StringConverter<T>::from(str, val); }

	template <class T>
	inline void to_string(const T& val, string& str) { StringConverter<T>::to(val, str); }
}
