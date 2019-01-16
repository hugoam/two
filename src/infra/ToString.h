//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <infra/Base.h>
#include <infra/String.h>

#include <cstdio>

namespace mud
{
	template <> inline void to_string(const int&     value, string& str) { str.resize(sprintf(nullptr, "%d",   value)); sprintf(str.data(), "%d",   value); }
	template <> inline void to_string(const long&    value, string& str) { str.resize(sprintf(nullptr, "%ld",  value)); sprintf(str.data(), "%ld",  value); }
	template <> inline void to_string(const llong&   value, string& str) { str.resize(sprintf(nullptr, "%lld", value)); sprintf(str.data(), "%lld", value); }
	template <> inline void to_string(const uint&    value, string& str) { str.resize(sprintf(nullptr, "%u",   value)); sprintf(str.data(), "%u",   value); }
	template <> inline void to_string(const ulong&   value, string& str) { str.resize(sprintf(nullptr, "%lu",  value)); sprintf(str.data(), "%lu",  value); }
	template <> inline void to_string(const ullong&  value, string& str) { str.resize(sprintf(nullptr, "%llu", value)); sprintf(str.data(), "%llu", value); }
	template <> inline void to_string(const float&   value, string& str) { str.resize(sprintf(nullptr, "%f",   value)); sprintf(str.data(), "%f",   value); }
	template <> inline void to_string(const double&  value, string& str) { str.resize(sprintf(nullptr, "%f",   value)); sprintf(str.data(), "%f",   value); }
	template <> inline void to_string(const ldouble& value, string& str) { str.resize(sprintf(nullptr, "%Lf",  value)); sprintf(str.data(), "%Lf",  value); }
}
