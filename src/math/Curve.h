//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <math/Interp.h>
#include <math/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
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
		constr_ ValueCurve() {}
		constr_ ValueCurve(std::vector<T> keys) : m_keys(keys) {}
		ValueCurve(T value) : m_keys(1, value) {}

		T sample_constant()
		{
			return m_keys[0];
		}

		T sample_curve(float t)
		{
			uint32_t key = uint32_t(t * (m_keys.size() - 1));
			float interval = 1.f / float(m_keys.size() - 1);
			float ttmod = fmod(t, interval) / interval;

			return mud::lerp(m_keys[key], m_keys[key + 1], ttmod);
		}

		attr_ mut_ std::vector<T> m_keys;
	};

	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueCurve<vec3>;
	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueCurve<quat>;
	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueCurve<float>;
	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueCurve<uint32_t>;
	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueCurve<Colour>;

	export_ template <class T>
	struct refl_ struct_ ValueTrack
	{
		constr_ ValueTrack() {}
		constr_ ValueTrack(TrackMode mode, ValueCurve<T> curve, ValueCurve<T> min_curve, ValueCurve<T> max_curve) : m_mode(mode), m_curve(curve), m_min_curve(min_curve), m_max_curve(max_curve) {}
		ValueTrack(T value) : m_mode(TrackMode::Constant), m_curve(value) {}
		ValueTrack(T min, T max) : m_mode(TrackMode::ConstantRandom), m_min_curve(min), m_max_curve(max) {}
		ValueTrack(std::vector<T> values) : m_mode(TrackMode::Curve), m_curve(values) {}
		ValueTrack(std::vector<T> min_values, std::vector<T> max_values) : m_mode(TrackMode::CurveRandom), m_min_curve(min_values), m_max_curve(max_values) {}

		void set_mode(TrackMode mode)
		{
			if(mode == TrackMode::Constant)
				*this = ValueTrack<T>(T());
			else if(mode == TrackMode::ConstantRandom)
				*this = ValueTrack<T>(T(), T());
			else if(mode == TrackMode::Curve)
				*this = ValueTrack<T>(std::vector<T>(2, T()));
			else if(mode == TrackMode::CurveRandom)
				*this = ValueTrack<T>(std::vector<T>(2, T()), std::vector<T>(2, T()));
		}

		T sample(float t, float seed = 0.f)
		{
			if(m_mode == TrackMode::Constant)
				return m_curve.sample_constant();
			else if(m_mode == TrackMode::ConstantRandom)
				return mud::lerp(m_min_curve.sample_constant(), m_max_curve.sample_constant(), seed);
			else if(m_mode == TrackMode::Curve)
				return m_curve.sample_curve(t);
			else //if(m_mode == TrackMode::CurveRandom)
				return mud::lerp(m_min_curve.sample_curve(t), m_max_curve.sample_curve(t), seed);
		}

		attr_ mut_ TrackMode m_mode;
		attr_ mut_ ValueCurve<T> m_curve;
		attr_ mut_ ValueCurve<T> m_min_curve;
		attr_ mut_ ValueCurve<T> m_max_curve;
	};

	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueTrack<vec3>;
	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueTrack<quat>;
	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueTrack<float>;
	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueTrack<uint32_t>;
	export_ template struct refl_ struct_ MUD_MATH_EXPORT ValueTrack<Colour>;
}
