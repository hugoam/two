//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
//#include <stl/type_traits.h>
#include <infra/Config.h>
#include <infra/String.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>

namespace mud
{
	// vector - string conversion
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
	
	export_ template <typename T>
	struct is_vector : false_type {};
	
	export_ template <typename T>
	struct is_vector<vector<T>> : true_type {};

#if 0
	export_ template <class T>
	inline typename enable_if<is_vector<T>::value, void>::type
		to_string(const T& val, string& str) { vector_to_string(val, str); }
#endif

	export_ template <class T>
	inline void string_to_vector(const string& str, T& vec)
	{
		size_t first = 0;
		size_t second = str.find(",");
		const size_t end = str.size();

		while(second != end)
		{
			second = str.find(",", first);
			vec.push_back(to_value<typename T::value_type>(str.substr(first, second - first)));
			
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
		size_t first = 0;
		size_t second = str.find(",");
		const size_t end = str.size();

		uint32_t i = 0;
		while(second != end)
		{
			second = str.find(",", first);
			vec[i] = to_value<T>(str.substr(first, second - first));

			++i;
			if(second != end)
				first = second + 1;
		}
	}

	export_ template <class T>
	struct StringConverter
	{
		static inline void to(const T& val, string& str) { UNUSED(val); UNUSED(str); }
		static inline void from(const string& str, T& val) { UNUSED(str); UNUSED(val); }
	};

	export_ template <class T>
	struct StringConverter<vector<T>>
	{
		static inline void to(const vector<T>& val, string& str) { vector_to_string(val, str); }
		static inline void from(const string& str, vector<T>& vec) { string_to_vector(str, vec); }
	};

#if 0
	export_ template <class T, size_t s>
	struct StringConverter<carray<T, s>>
	{
		static inline void to(const std::array<T, s>& val, string& str) { fixed_vector_to_string<carray<T, s>, s>(val, str); }
		static inline void from(const string& str, std::array<T, s>& vec) { string_to_fixed_vector<carray<T, s>, T>(str, vec); }
	};
#endif

	export_ template <class T_Enum>
	inline void flags_from_string(const string& str, T_Enum& value)
	{
		vector<string> names = split(to_upper(str), "|");
		for(const string& name : names)
			value = static_cast<T_Enum>(value | to_value<T_Enum>(name));
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
	inline void to_value(const string& str, T& val) { StringConverter<T>::from(str, val); }

	export_ template <class T>
	inline void to_string(const T& val, string& str) { StringConverter<T>::to(val, str); }
}
