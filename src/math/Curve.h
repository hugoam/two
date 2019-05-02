//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <stl/span.h>
#include <math/Vec.h>
#include <math/Interp.h>
#include <math/Forward.h>

namespace two
{
	export_ enum class refl_ TrackMode : unsigned int
	{
		Constant,
		ConstantRandom,
		Curve,
		CurveRandom
	};

	export_ template <class T>
	struct refl_ struct_ ValueCurve
	{
		constr_ ValueCurve();
		constr_ ValueCurve(span<T> keys);
		~ValueCurve();

		T sample_curve(float t);

		attr_ vector<T> m_keys;
	};

	export_ extern template struct refl_ ValueCurve<float>;
	export_ extern template struct refl_ ValueCurve<uint32_t>;
	export_ extern template struct refl_ ValueCurve<vec3>;
	export_ extern template struct refl_ ValueCurve<quat>;
	export_ extern template struct refl_ ValueCurve<Colour>;

	template <class T>
	struct One { static T value() { return T(1); } };

	template <> struct One<vec3> { static vec3 value() { return vec3(1.f); } };
	template <> struct One<quat> { static quat value() { return ZeroQuat; } };
	template <> struct One<Colour> { static Colour value() { return Colour(1.f); } };

	export_ template <class T>
	struct refl_ struct_ ValueTrack
	{
		constr_ ValueTrack();
		constr_ ValueTrack(TrackMode mode, ValueCurve<T> curve, ValueCurve<T> min_curve, ValueCurve<T> max_curve);
		ValueTrack(T value);
		ValueTrack(T min, T max);
		ValueTrack(span<T> values);
		ValueTrack(span<T> min_values, span<T> max_values);
		~ValueTrack();

		void set_mode(TrackMode mode);

		T sample(float t, float seed = 0.f);

		attr_ TrackMode m_mode;
		attr_ T m_value = One<T>::value();
		attr_ T m_min = One<T>::value();
		attr_ T m_max = One<T>::value();
		attr_ ValueCurve<T> m_curve;
		attr_ ValueCurve<T> m_min_curve;
		attr_ ValueCurve<T> m_max_curve;
	};

	export_ extern template struct refl_ ValueTrack<vec3>;
	export_ extern template struct refl_ ValueTrack<quat>;
	export_ extern template struct refl_ ValueTrack<float>;
	export_ extern template struct refl_ ValueTrack<uint32_t>;
	export_ extern template struct refl_ ValueTrack<Colour>;
}
