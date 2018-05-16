//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>

namespace mud
{
	enum class _refl_ Axis : unsigned int
	{
		X = 0,
		Y = 1,
		Z = 2,
	};

	enum class _refl_ SignedAxis : unsigned int
	{
		PlusX  = 0,
		MinusX = 1,
		PlusY  = 2,
		MinusY = 3,
		PlusZ  = 4,
		MinusZ = 5,
	};

	inline SignedAxis to_signed_axis(Axis axis, bool positive)
	{
		return SignedAxis(uint(axis) * 2 + (positive ? 0 : 1));
	}

	enum class _refl_ Side : unsigned int
	{
		Right = uint(SignedAxis::PlusX),
		Left  = uint(SignedAxis::MinusX),
		Up    = uint(SignedAxis::PlusY),
		Down  = uint(SignedAxis::MinusY),
		Back  = uint(SignedAxis::PlusZ),
		Front = uint(SignedAxis::MinusZ),
	};
}
