//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <random>
#endif

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/Random.h>
#endif

namespace mud
{
	template <class T>
	T random_integer(T min, T max)
	{
		static std::random_device randomDevice;
		static std::mt19937 range(randomDevice());

		std::uniform_int_distribution<T> uniform(min, max);
		return uniform(range);
	}

	template <class T>
	T random_scalar(T min, T max)
	{
		static std::random_device randomDevice;
		static std::mt19937 range(randomDevice());

		std::uniform_real_distribution<T> uniform(min, max);
		return uniform(range);
	}

	template MUD_MATH_EXPORT float random_scalar<float>(float min, float max);
	template MUD_MATH_EXPORT double random_scalar<double>(double min, double max);

	template MUD_MATH_EXPORT int random_integer<int>(int min, int max);
	template MUD_MATH_EXPORT uint random_integer<uint>(uint min, uint max);
	template MUD_MATH_EXPORT ulong random_integer<ulong>(ulong min, ulong max);
	template MUD_MATH_EXPORT ullong random_integer<ullong>(ullong min, ullong max);
}
