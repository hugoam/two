//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>

namespace mud
{
	export_ template <class T>
	T random_scalar();

	export_ template <class T>
	T random_integer(T min, T max);

	export_ template <class T>
	T random_scalar(T min, T max);

	extern template float random_scalar();

	extern template float random_scalar<float>(float min, float max);
	extern template double random_scalar<double>(double min, double max);

	extern template int random_integer<int>(int min, int max);
	extern template uint random_integer<uint>(uint min, uint max);
	extern template ulong random_integer<ulong>(ulong min, ulong max);
	extern template ullong random_integer<ullong>(ullong min, ullong max);
}
