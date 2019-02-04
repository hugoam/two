//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <infra/Base.h>
#include <infra/StringOps.h>

namespace mud
{
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, bool& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, float& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, double& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, char& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, short& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, int& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, long& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, llong& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, uchar& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, ushort& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, uint& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, ulong& val);
	export_ template <> MUD_INFRA_EXPORT void to_value(const string& str, ullong& val);
}
