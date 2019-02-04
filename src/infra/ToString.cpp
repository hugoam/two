//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_MODULES
module mud.infra;
#else
#include <infra/ToString.h>
#endif

#include <cstdio>

namespace mud
{
	template <> inline void to_string(const bool&    value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> inline void to_string(const char&    value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> inline void to_string(const schar&   value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> inline void to_string(const uchar&   value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> inline void to_string(const int&     value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> inline void to_string(const long&    value, string& str) { str.resize(snprintf(nullptr, 0, "%ld",  value)); sprintf(&str[0], "%ld",  value); }
	template <> inline void to_string(const llong&   value, string& str) { str.resize(snprintf(nullptr, 0, "%lld", value)); sprintf(&str[0], "%lld", value); }
	template <> inline void to_string(const ushort&  value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> inline void to_string(const uint&    value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> inline void to_string(const ulong&   value, string& str) { str.resize(snprintf(nullptr, 0, "%lu",  value)); sprintf(&str[0], "%lu",  value); }
	template <> inline void to_string(const ullong&  value, string& str) { str.resize(snprintf(nullptr, 0, "%llu", value)); sprintf(&str[0], "%llu", value); }
	template <> inline void to_string(const float&   value, string& str) { str.resize(snprintf(nullptr, 0, "%f",   value)); sprintf(&str[0], "%f",   value); }
	template <> inline void to_string(const double&  value, string& str) { str.resize(snprintf(nullptr, 0, "%f",   value)); sprintf(&str[0], "%f",   value); }
	template <> inline void to_string(const ldouble& value, string& str) { str.resize(snprintf(nullptr, 0, "%Lf",  value)); sprintf(&str[0], "%Lf",  value); }
}
