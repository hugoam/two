//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/table.h>
#include <math/Forward.h>
#include <math/Axis.h>
#include <math/Vec.h>

#include <stl/stddef.h>

namespace mud
{
	// @todo replace with inline constexpr when moving to C++17
	export_ extern MUD_MATH_EXPORT const Side c_sides[6]; // = { Side::Right, Side::Left, Side::Up, Side::Down, Side::Back, Side::Front };

	export_ extern MUD_MATH_EXPORT const table<Axis, vec3> c_axes;			// = {  X3,  Y3,  Z3 };
	export_ extern MUD_MATH_EXPORT const table<Axis, vec3> c_tangents;		// = {  Y3, -Z3,  Y3 };
	export_ extern MUD_MATH_EXPORT const table<Axis, vec3> c_binormals;	// = { -Z3,  X3,  X3 };
	export_ extern MUD_MATH_EXPORT const table<SignedAxis, vec3> c_dirs;			// = {  X3, -X3,  Y3, -Y3,  Z3, -Z3 };
	export_ extern MUD_MATH_EXPORT const table<SignedAxis, vec3> c_dirs_tangents;	// = {  Y3, -Z3, -Z3,  X3,  Y3,  X3 };
	export_ extern MUD_MATH_EXPORT const table<SignedAxis, vec3> c_dirs_normals;	// = { -Z3,  Y3,  X3, -Z3,  X3,  Y3 };

	export_ inline vec3 to_vec3(Axis axis) { return c_axes[axis]; }
	export_ inline vec3 to_vec3(Side side) { return c_dirs[SignedAxis(side)]; }
	export_ inline vec3 to_vec3(SignedAxis axis) { return c_dirs[axis]; }
}
