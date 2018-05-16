//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>
#include <math/Axis.h>
#include <math/Vec.h>

namespace mud
{
	// @todo replace with inline constexpr when moving to C++17
	extern MUD_MATH_EXPORT const Side Sides[6]; // = { Side::Right, Side::Left, Side::Up, Side::Down, Side::Back, Side::Front };

	extern MUD_MATH_EXPORT const vec3 Axes[3]; // = { X3, Y3, Z3 };
	extern MUD_MATH_EXPORT const vec3 Directions[6]; //= {  X3, -X3,  Y3, -Y3,  Z3, -Z3 };
	extern MUD_MATH_EXPORT const vec3 NormalX[6]; //   = {  Y3, -Z3, -Z3,  X3,  Y3,  X3 };
	extern MUD_MATH_EXPORT const vec3 NormalY[6]; //   = { -Z3,  Y3,  X3, -Z3,  X3,  Y3 };

	inline vec3 to_vec3(Axis axis) { return Axes[size_t(axis)]; }
	inline vec3 to_vec3(Side side) { return Directions[size_t(side)]; }
	inline vec3 to_vec3(SignedAxis axis) { return Directions[size_t(axis)]; }
}
