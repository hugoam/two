//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/Stat.h>
#include <math/Stat.hpp>
#endif

namespace mud
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

	template struct MUD_MATH_EXPORT StatDef<int>;
	template struct MUD_MATH_EXPORT StatDef<float>;

	template struct MUD_MATH_EXPORT Stat<int>;
	template struct MUD_MATH_EXPORT Stat<float>;

	template struct MUD_MATH_EXPORT AutoStat<int>;
	template struct MUD_MATH_EXPORT AutoStat<float>;
}
