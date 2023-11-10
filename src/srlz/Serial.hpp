//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <type/Any.h>
#endif
#include <srlz/Serial.h>

namespace two
{
	export_ template <class T>
	T unpackt(const Json& data)
	{
		Var value = unpack(type<T>(), data);
		return val<T>(value);
	}
}
