//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/limits.h>
#include <math/Forward.h>
#include <math/Math.h>

#ifndef MUD_CPP_20
#include <cstdint>
#include <cfloat>
#endif

namespace mud
{
	export_ template <class T>
	struct StatDef
	{
		T m_min = limits<T>::min();
		T m_max = limits<T>::max();
		T m_step = T(1);

		T rincrement(T& value, T amount) const;
		T rdecrement(T& value, T amount) const;
		void increment(T& value, T amount) const;
		void decrement(T& value, T amount) const;

		void increment(T& value) const;
		void decrement(T& value) const;

		void multiply(T& value, T& base, T multiplier) const;
		
		void modify(T& value, T& base, T val) const;
		void modify(T& value, T val) const;

		void update(T& value) const;
	};

	export_ extern template struct StatDef<int>;
	export_ extern template struct StatDef<float>;

	export_ template <class T>
	struct Stat
	{
	public:
		Stat(T& value, const StatDef<T>& def);

		operator T() const;

		inline T& ref() const;
		inline T value() const;

		inline T min() const;
		inline T max() const;
		inline T step() const;

		inline void modify(T value);

		inline void increment();
		inline void decrement();

		//T m_base;
		T* m_ref;
		const StatDef<T>* m_def;
	};

	export_ extern template struct Stat<int>;
	export_ extern template struct Stat<float>;

	export_ template <class T>
	struct refl_ AutoStat : public Stat<T>
	{
	public:
		AutoStat(T value = T(), T min = limits<T>::min(), T max = limits<T>::max(), T step = T(1));
		AutoStat(T& value, StatDef<T> def);
		AutoStat(const AutoStat& other);

		AutoStat& operator=(const AutoStat& other) = default;

		attr_ T m_value;
		StatDef<T> m_def;
	};

	export_ extern template struct refl_ AutoStat<int>;
	export_ extern template struct refl_ AutoStat<float>;

#if 0
	export_ struct refl_ MUD_MATH_EXPORT Ratio : public Stat<float>
	{
	public:
		constr_ Ratio(float value = 0.f);

		attr_ float m_value;

		void set(float value) { def().modify(m_value, value); }

		const StatDef<float>& def() const { static StatDef<float> df = { 0.f, 1.f, 0.01f }; return df; }
	};

	export_ struct refl_ MUD_MATH_EXPORT Gauge : public Stat<float>
	{
	public:
		constr_ Gauge(float value = 0.f);

		attr_ float m_value;

		void set(float value) { def().modify(m_value, value); }

		const StatDef<float>& def() const { static StatDef<float> df = { 0.f, FLT_MAX, 1.f }; return df; }
	};
#endif
}
