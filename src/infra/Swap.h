//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

#ifdef TWO_MODULES
// @TODO fix this shit
namespace two
{
	namespace
	{
		template <class T>
		inline void swap(T& t1, T& t2)
		{
			T temp = move(t1);
			t1 = move(t2);
			t2 = move(temp);
		}
	}
}
#else
#include <stl/swap.h>
#endif
