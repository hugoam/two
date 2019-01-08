//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <infra/Strung.h>
#include <infra/Array.h>

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#endif

namespace mud
{
	export_ using string = std::string;
	
	export_ template <class T>
	struct StringConverter;

	export_ template <class T>
	inline void from_string(const string& str, T& val);

	export_ template <class T>
	inline void to_string(const T& val, string& str);

	export_ template <class T>
	inline T from_string(const string& str) { T val; from_string<T>(str, val); return val; }

	export_ template <class T>
	inline string to_string(const T& val) { string str; to_string<T>(val, str); return str; }

	// string - string conversion
	export_ template <> inline void from_string<cstring>(const string& str, cstring& val) { val = str.c_str(); }
	export_ template <> inline void to_string<cstring>(const cstring& val, string& str) { str = val; }
	export_ template <> inline void from_string<string>(const string& str, string& val) { val = str; }
	export_ template <> inline void to_string<string>(const string& val, string& str){ str = val; }

	export_ MUD_INFRA_EXPORT void split(const string& str, const string& separator, array<string> output);
	export_ MUD_INFRA_EXPORT std::vector<string> split(const string& str, const string& separator);

	//export_ MUD_INFRA_EXPORT string join(array<string> strings, string separator);
	export_ MUD_INFRA_EXPORT string join(const std::vector<string>& strings, string separator);

	export_ MUD_INFRA_EXPORT string replace(const string& original, const string& before, const string& after);

	export_ MUD_INFRA_EXPORT string to_lower(const string& original);
	export_ MUD_INFRA_EXPORT string to_upper(const string& original);
	export_ MUD_INFRA_EXPORT string to_pascalcase(const string& name);
	export_ MUD_INFRA_EXPORT string to_camelcase(const string& name);

	extern MUD_INFRA_EXPORT const size_t g_num_precision; // = 3;

	export_ inline string truncate_number(const string& str)
	{
		// @todo use snprintf ?
		size_t dot = str.find(".");
		if(dot == string::npos) return str;
		string result = str;
		while(result.size() > 1 + dot + g_num_precision || (result.size() > 1 + dot + 1 && result.back() == '0'))
			result.pop_back();
		return result;
	}
}
