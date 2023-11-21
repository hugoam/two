#pragma once

#include <infra/Config.h>

#ifndef TWO_MATH_EXPORT
#define TWO_MATH_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum Clockwise : unsigned int;
    export_ enum class Axis : unsigned int;
    export_ enum class Axes : unsigned int;
    export_ enum class SignedAxis : unsigned int;
    export_ enum class Side : unsigned int;
    export_ enum class TrackMode : unsigned int;
    export_ enum class Spectrum : short;

	export_ template <class T> class vector2d;
	export_ template <class T> struct vector3d;

    export_ template <class T> struct Range;
    export_ template <class T> struct ValueCurve;
    export_ template <class T> struct ValueTrack;
	export_ template <class T> struct StatDef;
	export_ template <class T> struct Stat;

	export_ template <class T> struct v2;
	export_ template <class T> struct v3;
	export_ template <class T> struct v4;

	export_ using half2 = v2<ushort>;
	export_ using half3 = v3<ushort>;
	export_ using half4 = v4<ushort>;

	export_ using ushort2 = v2<ushort>;
	export_ using ushort3 = v3<ushort>;
	export_ using ushort4 = v4<ushort>;

	export_ using float2 = v2<float>;
	export_ using float3 = v3<float>;
	export_ using float4 = v4<float>;

	export_ using double2 = v2<double>;
	export_ using double3 = v3<double>;
	export_ using double4 = v4<double>;

	export_ using int2 = v2<int>;
	export_ using int3 = v3<int>;
	export_ using int4 = v4<int>;

	export_ using uint2 = v2<uint>;
	export_ using uint3 = v3<uint>;
	export_ using uint4 = v4<uint>;

	export_ using bool2 = v2<bool>;
	export_ using bool3 = v3<bool>;
	export_ using bool4 = v4<bool>;

	export_ using vec2 = float2;
	export_ using vec3 = float3;
	export_ using vec4 = float4;
	export_ using uvec2 = uint2;
	export_ using uvec3 = uint3;
	export_ using uvec4 = uint4;
	export_ using ivec2 = int2;
	export_ using ivec3 = int3;
	export_ using ivec4 = int4;
	export_ using bvec3 = bool3;
	export_ using bvec4 = bool4;

	export_ struct mat3;
	export_ struct mat4;
	export_ struct quat;

    export_ struct Transform;
    export_ struct Colour;
    export_ class Lerp;
    export_ class Grided3;
    export_ struct Image;
    export_ struct Palette;
    export_ struct Image256;
    export_ class ImageAtlas;
    export_ class Sprite;
    export_ class SpriteAtlas;
	export_ class TextureAtlas;
    export_ struct Ratio;
    export_ struct Gauge;
    export_ struct Time;
    export_ struct TimeSpan;
    export_ class Clock;
    export_ struct Anim;
    export_ class Animator;
}

#ifdef TWO_META_GENERATOR
#include <stl/span.h>
#include <stl/vector.h>
//#include <math/Vec.h>
namespace stl
{
	extern template struct refl_ span_ span<uint8_t>;
	extern template struct refl_ span_ span<int>;
	extern template struct refl_ span_ span<float>;
	extern template struct refl_ span_ span<uint32_t>;
	extern template struct refl_ span_ span<two::vec3>;
	extern template struct refl_ span_ span<two::quat>;
	extern template struct refl_ span_ span<two::Colour>;
	extern template struct refl_ span_ span<two::uvec3>;

	extern template class refl_ seque_ vector<int>;
	extern template class refl_ seque_ vector<float>;
	extern template class refl_ seque_ vector<uint32_t>;
	extern template class refl_ seque_ vector<two::vec3>;
	extern template class refl_ seque_ vector<two::quat>;
	extern template class refl_ seque_ vector<two::Colour>;
	extern template class refl_ seque_ vector<two::uvec3>;
}
#endif
