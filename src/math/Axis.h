//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/base.h>
#include <math/Forward.h>

namespace mud
{
	export_ enum class refl_ Axis : unsigned int
	{
		X = 0,
		Y = 1,
		Z = 2,
	};

	export_ enum class refl_ Axes : unsigned int
	{
		None = 0,
		X = 1 << 0,
		Y = 1 << 1,
		Z = 1 << 2,
	};

	export_ inline Axes to_axes(Axes x = Axes::None, Axes y = Axes::None, Axes z = Axes::None) { return Axes(uint(x) | uint(y) | uint(z)); }
	export_ inline bool check_axis(Axes axes, Axes axis) { return (uint(axes) & uint(axis)) != 0; }

	export_ enum class refl_ SignedAxis : unsigned int
	{
		PlusX  = 0,
		MinusX = 1,
		PlusY  = 2,
		MinusY = 3,
		PlusZ  = 4,
		MinusZ = 5,
	};

	export_ inline SignedAxis to_signed_axis(Axis axis, bool positive)
	{
		return SignedAxis(uint(axis) * 2 + (positive ? 0 : 1));
	}

	export_ enum class refl_ Side : unsigned int
	{
		Right = uint(SignedAxis::PlusX),
		Left  = uint(SignedAxis::MinusX),
		Up    = uint(SignedAxis::PlusY),
		Down  = uint(SignedAxis::MinusY),
		Back  = uint(SignedAxis::PlusZ),
		Front = uint(SignedAxis::MinusZ),
		Count
	};
}
