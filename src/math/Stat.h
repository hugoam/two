//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>
#include <math/Math.h>

namespace two
{
	export_ template <class T>
	struct refl_ StatDef
	{
		attr_ T m_min = limits<T>::min();
		attr_ T m_max = limits<T>::max();
		attr_ T m_step = T(1);

		T rincrement(T& value, T amount) const { T diff = min(m_max - value, amount); value += diff; update(value); return diff; }
		T rdecrement(T& value, T amount) const { T diff = max(-m_min + value, amount); value -= diff; update(value); return diff; }
		void increment(T& value, T amount) const { value += amount; update(value); }
		void decrement(T& value, T amount) const { value -= amount; update(value); }

		void increment(T& value) const { value += m_step; update(value); }
		void decrement(T& value) const { value -= m_step; update(value); }

		void multiply(T& value, T& base, T multiplier) const { T diff = value - base; base *= multiplier; value = base + diff; update(value); }
		
		void modify(T& value, T& base, T val) const { value += val - base; base = value; update(value); }
		void modify(T& value, T val) const { value = val; update(value); }

		void update(T& value) const
		{
			if (value < m_min)
				value = m_min;
			if (value > m_max)
				value = m_max;
		}

	};

	extern template struct refl_ StatDef<int>;
	extern template struct refl_ StatDef<float>;

	export_ template <class T>
	struct Stat
	{
	public:
		Stat(T& value, const StatDef<T>& def)
			//: m_base(base)
			: m_ref(&value)
			, m_def(&def)
		{}


		operator T() const { return *m_ref; }

		inline T& ref() const { return *m_ref; }
		inline T value() const { return *m_ref; }

		inline T min() const { return m_def->m_min; }
		inline T max() const { return m_def->m_max; }
		inline T step() const { return m_def->m_step; }

		inline void modify(T value) { m_def->modify(*m_ref, value); }

		inline void increment() { m_def->increment(*m_ref); }
		inline void decrement() { m_def->decrement(*m_ref); }

		//T m_base;
		T* m_ref;
		const StatDef<T>* m_def;
	};

	extern template struct Stat<int>;
	extern template struct Stat<float>;

#if 0
	export_ struct refl_ TWO_MATH_EXPORT Ratio : public Stat<float>
	{
	public:
		constr_ Ratio(float value = 0.f);

		attr_ float m_value;

		void set(float value) { def().modify(m_value, value); }

		const StatDef<float>& def() const { static StatDef<float> df = { 0.f, 1.f, 0.01f }; return df; }
	};

	export_ struct refl_ TWO_MATH_EXPORT Gauge : public Stat<float>
	{
	public:
		constr_ Gauge(float value = 0.f);

		attr_ float m_value;

		void set(float value) { def().modify(m_value, value); }

		const StatDef<float>& def() const { static StatDef<float> df = { 0.f, FLT_MAX, 1.f }; return df; }
	};
#endif
}
