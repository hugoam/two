//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>
#include <math/Vec.h>

#include <cmath>

namespace mud
{
	static inline double fposmod(double p_x, double p_y) { return (p_x >= 0) ? std::fmod(p_x, p_y) : p_y - std::fmod(-p_x, p_y); }
	static inline float fposmod(float p_x, float p_y) { return (p_x >= 0) ? std::fmod(p_x, p_y) : p_y - std::fmod(-p_x, p_y); }
}
