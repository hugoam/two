//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <infra/String.h>

#ifndef MUD_CPP_20
#include <memory>
#include <algorithm>
#include <sstream>
#endif

namespace mud
{
	using uchar = unsigned char;
	using ushort = unsigned short;
	using uint = unsigned int;

	template <typename T, typename = int>
	struct is_string_convertible : std::false_type { };

	template <typename T>
	struct is_string_convertible <T, decltype(std::to_string(std::declval<T>()), 0)> : std::true_type { };

	export_ template <class T>
	inline void string_to_type(const string& str, T& val)
	{
		std::stringstream ss(str);
		ss >> val;
	}

	export_ template <> inline void string_to_type(const string& str, bool& val) { val = std::stoi(str) != 0; } //str == "true" ? true : false; }

	export_ template <> inline void string_to_type(const string& str, float& val) { val = std::stof(str); }
	export_ template <> inline void string_to_type(const string& str, double& val) { val = std::stod(str); }
	export_ template <> inline void string_to_type(const string& str, char& val) { val = char(std::stoi(str)); }
	export_ template <> inline void string_to_type(const string& str, short& val) { val = short(std::stoi(str)); }
	export_ template <> inline void string_to_type(const string& str, int& val) { val = std::stoi(str); }
	export_ template <> inline void string_to_type(const string& str, long& val) { val = std::stoi(str); }
	export_ template <> inline void string_to_type(const string& str, long long& val) { val = std::stoi(str); }
	export_ template <> inline void string_to_type(const string& str, unsigned char& val) { val = uchar(std::stoi(str)); }
	export_ template <> inline void string_to_type(const string& str, unsigned short& val) { val = ushort(std::stoi(str)); }
	export_ template <> inline void string_to_type(const string& str, unsigned int& val) { val = std::stoi(str); }
	export_ template <> inline void string_to_type(const string& str, unsigned long& val) { val = std::stoi(str); }
	export_ template <> inline void string_to_type(const string& str, unsigned long long& val) { val = std::stoi(str); }

	export_ template <class T>
	inline typename std::enable_if<is_string_convertible<T>::value, void>::type
		type_to_string(const T& val, string& str)
	{
		str = std::to_string(val);
	}

	export_ template <class T>
	inline typename std::enable_if<!is_string_convertible<T>::value, void>::type
		type_to_string(const T& val, string& str)
	{
		std::stringstream ss;
		ss << val;
		str = ss.str();
	}

	// Vector - string conversion
	export_ template <class T>
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

	export_ template <class T>
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

	export_ template <class T, uint32_t size>
	inline void fixed_vector_to_string(const T& val, string& str)
	{
		for(uint32_t i = 0; i < size; ++i)
		{
			str += to_string(val[i]);
			str += ",";
		}
		str.pop_back();
	}

	export_ template <class Vec, class T>
	inline void string_to_fixed_vector(const string& str, Vec& vec)
	{
		auto first = str.begin();
		auto end = str.end();
		auto second = std::find(first, end, ',');

		uint32_t i = 0;
		while(second != end)
		{
			second = std::find(first, end, ',');
			vec[i] = from_string<T>(str.substr(first - str.begin(), second - first));

			++i;
			if(second != end)
				first = second + 1;
		}
	}

	export_ template <class T>
	struct StringConverter
	{
		static inline void to(const T& val, string& str) { type_to_string(val, str); }
		static inline void from(const string& str, T& val) { string_to_type<T>(str, val); }
	};

	export_ template <class T>
	struct StringConverter<std::vector<T>>
	{
		static inline void to(const std::vector<T>& val, string& str) { vector_to_string(val, str); }
		static inline void from(const string& str, std::vector<T>& vec) { string_to_vector(str, vec); }
	};

	export_ template <class T, size_t s>
	struct StringConverter<std::array<T, s>>
	{
		static inline void to(const std::array<T, s>& val, string& str) { fixed_vector_to_string<std::array<T, s>, s>(val, str); }
		static inline void from(const string& str, std::array<T, s>& vec) { string_to_fixed_vector<std::array<T, s>, T>(str, vec); }
	};

	export_ template <class T_Enum>
	inline void flags_from_string(const string& str, T_Enum& value)
	{
		std::vector<string> names = split_string(to_upper(str), "|");
		for(const string& name : names)
			value = static_cast<T_Enum>(value | from_string<T_Enum>(name));
	}

	export_ template <class T_Enum>
	inline T_Enum flags_from_string(const string& str) { T_Enum value = T_Enum(0); flags_from_string(str, value); return value; }

	export_ template <class T_Enum, size_t Count>
	inline void flags_to_string(const T_Enum& value, string& str)
	{
		for(size_t shift = 0; shift < Count; ++shift)
			if(value & (1 << shift))
				str += (str.empty() ? "" : "|") + to_string<T_Enum>(static_cast<T_Enum>((1 << shift)));
	}

	export_ template <class T_Enum, size_t Count>
	inline string flags_to_string(const T_Enum& value) { string str; flags_to_string<T_Enum, Count>(value, str); return str; }

	export_ template <class T>
	inline void from_string(const string& str, T& val) { StringConverter<T>::from(str, val); }

	export_ template <class T>
	inline void to_string(const T& val, string& str) { StringConverter<T>::to(val, str); }
}
