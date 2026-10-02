//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <stl/base.h>
#include <infra/StringOps.h>

namespace two
{
	template <> TWO_INFRA_EXPORT void to_value(const string& str, bool& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, char& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, schar& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, short& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, int& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, long& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, llong& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, uchar& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, ushort& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, uint& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, ulong& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, ullong& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, float& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, double& val);
	template <> TWO_INFRA_EXPORT void to_value(const string& str, ldouble& val);
}
