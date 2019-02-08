//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <stl/base.h>
#include <infra/StringOps.h>

namespace mud
{
	export_ template <> MUD_INFRA_EXPORT void to_string(const bool&    value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const char&    value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const schar&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const uchar&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const short&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const int&     value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const long&    value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const llong&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const ushort&  value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const uint&    value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const ulong&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const ullong&  value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const float&   value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const double&  value, string& str);
	export_ template <> MUD_INFRA_EXPORT void to_string(const ldouble& value, string& str);
}
