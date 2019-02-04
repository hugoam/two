//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <infra/Config.h>
#include <infra/TypeTraits.h>

namespace mud
{
	template <class T>
	constexpr bool is_comparable<vector<T>> = is_comparable<T>;
}
