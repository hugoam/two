//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

/* std */
#include <obj/Generated/Forward.h>
#include <obj/Strung.h>
#include <obj/Array.h>

#include <string>
#include <vector>

namespace mud
{
	using string = std::string;
	//using std::vector;

	struct Filepath
	{
		string path;
		string name;
		string extension;
	};

	//template <>
	//cstring::operator string() { return m_str; }

	template <class T>
	struct StringConverter;

	template <class T>
	inline void from_string(const string& str, T& val);

	template <class T>
	inline void to_string(const T& val, string& str);

	template <class T>
	inline T from_string(const string& str) { T val; from_string<T>(str, val); return val; }

	template <class T>
	inline string to_string(const T& val) { string str; to_string<T>(val, str); return str; }

	// string - string conversion
	template <> inline void from_string<cstring>(const string& str, cstring& val) { val = str.c_str(); }
	template <> inline void to_string<cstring>(const cstring& val, string& str) { str = val; }
	template <> inline void from_string<string>(const string& str, string& val) { val = str; }
	template <> inline void to_string<string>(const string& val, string& str){ str = val; }

	MUD_OBJ_EXPORT void split_string(const string& str, const string& separator, array<string> output);
	MUD_OBJ_EXPORT std::vector<string> split_string(const string& str, const string& separator);

	MUD_OBJ_EXPORT string replace_all(const string& original, const string& before, const string& after);

	MUD_OBJ_EXPORT string to_lower(const string& original);
	MUD_OBJ_EXPORT string to_upper(const string& original);
	MUD_OBJ_EXPORT string to_camelcase(const string& name);

	extern MUD_OBJ_EXPORT const size_t g_num_precision; // = 3;

	inline string truncate_number(const string& str)
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
