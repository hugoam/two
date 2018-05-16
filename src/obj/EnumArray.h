//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <array>
#include <stdint.h>

namespace mud
{
	template <class T_Enum, class T_Element, size_t Size = size_t(T_Enum::Count)>
	using enum_array = std::array<T_Element, Size>;
	//using enum_array = T_Element[Size];
}
