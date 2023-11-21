//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.math;

namespace two
{
	template struct TWO_MATH_EXPORT ValueCurve<vec3>;
	template struct TWO_MATH_EXPORT ValueCurve<quat>;
	template struct TWO_MATH_EXPORT ValueCurve<float>;
	template struct TWO_MATH_EXPORT ValueCurve<uint32_t>;
	template struct TWO_MATH_EXPORT ValueCurve<Colour>;

	template struct TWO_MATH_EXPORT ValueTrack<vec3>;
	template struct TWO_MATH_EXPORT ValueTrack<quat>;
	template struct TWO_MATH_EXPORT ValueTrack<float>;
	template struct TWO_MATH_EXPORT ValueTrack<uint32_t>;
	template struct TWO_MATH_EXPORT ValueTrack<Colour>;
}
