//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>
#include <math/Vec.h>

#include <cmath>

namespace mud
{
	static inline double fposmod(double x, double y) { return (x >= 0) ? std::fmod(x, y) : y - std::fmod(-x, y); }
	static inline float fposmod(float x, float y) { return (x >= 0) ? std::fmod(x, y) : y - std::fmod(-x, y); }
}
