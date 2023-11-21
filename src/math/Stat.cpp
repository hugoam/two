//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.math;

namespace two
{
#if 0
	Ratio::Ratio(float value)
		: Stat<float>(m_value, def())
		, m_value(value)
	{}

	Gauge::Gauge(float value)
		: Stat<float>(m_value, def())
		, m_value(value)
	{}
#endif

	template struct TWO_MATH_EXPORT StatDef<int>;
	template struct TWO_MATH_EXPORT StatDef<float>;

	template struct TWO_MATH_EXPORT Stat<int>;
	template struct TWO_MATH_EXPORT Stat<float>;
}
