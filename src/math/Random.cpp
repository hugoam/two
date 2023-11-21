//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.math;

namespace two
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
	T randi()
	{
		static std::random_device device;
		static std::mt19937 generator(device());
		static std::uniform_int_distribution<T> distribution { limits<T>::min(), limits<T>::max() };
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

	template TWO_MATH_EXPORT float randf();
	template TWO_MATH_EXPORT double randf<double>();

	template TWO_MATH_EXPORT float randf(float min, float max);
	template TWO_MATH_EXPORT double randf<double>(double min, double max);

	template TWO_MATH_EXPORT int randi<int>();
	template TWO_MATH_EXPORT uint randi<uint>();

	template TWO_MATH_EXPORT int randi<int>(int min, int max);
	template TWO_MATH_EXPORT uint randi<uint>(uint min, uint max);
	template TWO_MATH_EXPORT ulong randi<ulong>(ulong min, ulong max);
	template TWO_MATH_EXPORT ullong randi<ullong>(ullong min, ullong max);
}
