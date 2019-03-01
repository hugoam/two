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
	T randi(T min, T max)
	{
		static std::random_device device;
		static std::mt19937 generator(device());
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(generator);
	}

	template <class T>
	T randf(T min, T max)
	{
		static std::random_device device;
		static std::mt19937 generator(device());
		std::uniform_real_distribution<T> distribution(min, max);
		return distribution(generator);
	}

	template <class T>
	T randf()
	{
		static std::random_device device;
		static std::mt19937 generator(device());
		static std::uniform_real_distribution<T> distribution { T(0), T(1) };
		return distribution(generator);
	}

	template MUD_MATH_EXPORT float randf();
	template MUD_MATH_EXPORT double randf<double>();

	template MUD_MATH_EXPORT float randf(float min, float max);
	template MUD_MATH_EXPORT double randf<double>(double min, double max);

	template MUD_MATH_EXPORT int randi<int>(int min, int max);
	template MUD_MATH_EXPORT uint randi<uint>(uint min, uint max);
	template MUD_MATH_EXPORT ulong randi<ulong>(ulong min, ulong max);
	template MUD_MATH_EXPORT ullong randi<ullong>(ullong min, ullong max);
}
