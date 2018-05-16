//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>

#include <random>

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

}
