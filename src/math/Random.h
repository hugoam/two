//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>

namespace mud
{
	export_ template <class T = float>
	T randf();
	
	export_ template <class T = int>
	T randi();

	export_ template <class T = int>
	T randi(T min, T max);

	export_ template <class T = float>
	T randf(T min, T max);

	extern template float randf();

	extern template float randf(float min, float max);
	extern template double randf<double>(double min, double max);

	extern template int randi<int>(int min, int max);
	extern template uint randi<uint>(uint min, uint max);
	extern template ulong randi<ulong>(ulong min, ulong max);
	extern template ullong randi<ullong>(ullong min, ullong max);
}
