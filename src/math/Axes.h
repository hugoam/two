//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>
#include <math/Axis.h>
#include <math/Vec.h>


namespace two
{
	export_ CONSTEXPR inline Side c_sides[6] = { Side::Right, Side::Left, Side::Up, Side::Down, Side::Back, Side::Front };
	export_ CONSTEXPR inline SignedAxis c_signed_axes[6] = { SignedAxis::PlusX, SignedAxis::MinusX, SignedAxis::PlusY, SignedAxis::MinusY, SignedAxis::PlusZ, SignedAxis::MinusZ };

	export_ CONSTEXPR inline table<Axis, vec3> c_axes		= { { x3, y3, z3 } };
	export_ CONSTEXPR inline table<Axis, vec3> c_tangents	= { { y3, z3, y3 } };
	export_ CONSTEXPR inline table<Axis, vec3> c_binormals	= { { z3, x3, x3 } };
	export_ CONSTEXPR inline table<SignedAxis, vec3> c_dirs			 = { {  x3, -x3,  y3, -y3,  z3, -z3 } };
	export_ CONSTEXPR inline table<SignedAxis, vec3> c_dirs_tangents = { {  y3, -z3, -z3,  x3,  y3,  x3 } };
	export_ CONSTEXPR inline table<SignedAxis, vec3> c_dirs_normals	 = { { -z3,  y3,  x3, -z3,  x3,  y3 } };

	export_ inline vec3 to_vec3(Axis axis) { return c_axes[axis]; }
	export_ inline vec3 to_vec3(Side side) { return c_dirs[SignedAxis(side)]; }
	export_ inline vec3 to_vec3(SignedAxis axis) { return c_dirs[axis]; }
}
