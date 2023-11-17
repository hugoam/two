//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.infra;

namespace two
{
#ifdef TWO_MODULES
	using stl::string;
#endif

	template <> void to_string(const bool&    value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const char&    value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const schar&   value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const uchar&   value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> void to_string(const short&   value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const int&     value, string& str) { str.resize(snprintf(nullptr, 0, "%d",   value)); sprintf(&str[0], "%d",   value); }
	template <> void to_string(const long&    value, string& str) { str.resize(snprintf(nullptr, 0, "%ld",  value)); sprintf(&str[0], "%ld",  value); }
	template <> void to_string(const llong&   value, string& str) { str.resize(snprintf(nullptr, 0, "%lld", value)); sprintf(&str[0], "%lld", value); }
	template <> void to_string(const ushort&  value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> void to_string(const uint&    value, string& str) { str.resize(snprintf(nullptr, 0, "%u",   value)); sprintf(&str[0], "%u",   value); }
	template <> void to_string(const ulong&   value, string& str) { str.resize(snprintf(nullptr, 0, "%lu",  value)); sprintf(&str[0], "%lu",  value); }
	template <> void to_string(const ullong&  value, string& str) { str.resize(snprintf(nullptr, 0, "%llu", value)); sprintf(&str[0], "%llu", value); }
	template <> void to_string(const float&   value, string& str) { str.resize(snprintf(nullptr, 0, "%f",   value)); sprintf(&str[0], "%f",   value); }
	template <> void to_string(const double&  value, string& str) { str.resize(snprintf(nullptr, 0, "%f",   value)); sprintf(&str[0], "%f",   value); }
	template <> void to_string(const ldouble& value, string& str) { str.resize(snprintf(nullptr, 0, "%Lf",  value)); sprintf(&str[0], "%Lf",  value); }
}
