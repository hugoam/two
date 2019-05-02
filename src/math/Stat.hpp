//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Math.h>
#include <math/Stat.h>

namespace two
{
	export_ template <class T>
	inline T StatDef<T>::rincrement(T& value, T amount) const { T diff = min(m_max - value, amount); value += diff; update(value); return diff; }
	export_ template <class T>
	inline T StatDef<T>::rdecrement(T& value, T amount) const { T diff = max(-m_min + value, amount); value -= diff; update(value); return diff; }

	export_ template <class T>
	inline void StatDef<T>::increment(T& value, T amount) const { value += amount; update(value); }
	export_ template <class T>
	inline void StatDef<T>::decrement(T& value, T amount) const { value -= amount; update(value); }

	export_ template <class T>
	inline void StatDef<T>::increment(T& value) const { value += m_step; update(value); }
	export_ template <class T>
	inline void StatDef<T>::decrement(T& value) const { value -= m_step; update(value); }

	export_ template <class T>
	inline void StatDef<T>::multiply(T& value, T& base, T multiplier) const { T diff = value - base; base *= multiplier; value = base + diff; update(value); }
		
	export_ template <class T>
	inline void StatDef<T>::modify(T& value, T& base, T val) const { value += val - base; base = value; update(value); }
	export_ template <class T>
	inline void StatDef<T>::modify(T& value, T val) const { value = val; update(value); }

	export_ template <class T>
	inline void StatDef<T>::update(T& value) const
	{
		if(value < m_min)
			value = m_min;
		if(value > m_max)
			value = m_max;
	}

	export_ template <class T>
	Stat<T>::Stat(T& value, const StatDef<T>& def)
		//: m_base(base)
		: m_ref(&value)
		, m_def(&def)
	{}

	export_ template <class T>
	Stat<T>::operator T() const { return *m_ref; }

	export_ template <class T>
	inline T& Stat<T>::ref() const { return *m_ref; }
	export_ template <class T>
	inline T Stat<T>::value() const { return *m_ref; }

	export_ template <class T>
	inline T Stat<T>::min() const { return m_def->m_min; }
	export_ template <class T>
	inline T Stat<T>::max() const { return m_def->m_max; }
	export_ template <class T>
	inline T Stat<T>::step() const { return m_def->m_step; }

	export_ template <class T>
	inline void Stat<T>::modify(T value) { m_def->modify(*m_ref, value); }
	export_ template <class T>
	inline void Stat<T>::increment() { m_def->increment(*m_ref); }
	export_ template <class T>
	inline void Stat<T>::decrement() { m_def->decrement(*m_ref); }
}
