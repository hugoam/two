//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

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
		constr_ ValueCurve() {}
		constr_ ValueCurve(span<T> keys) : m_keys(keys.begin(), keys.end()) {}
		~ValueCurve() {}

		T sample_curve(float t)
		{
			uint32_t key = uint32_t(t * (m_keys.size() - 1));
			float interval = 1.f / float(m_keys.size() - 1);
			float ttmod = fmod(t, interval) / interval;

			return lerp(m_keys[key], m_keys[key + 1], ttmod);
		}

		attr_ vector<T> m_keys;
	};

	extern template struct refl_ ValueCurve<float>;
	extern template struct refl_ ValueCurve<uint32_t>;
	extern template struct refl_ ValueCurve<vec3>;
	extern template struct refl_ ValueCurve<quat>;
	extern template struct refl_ ValueCurve<Colour>;

	export_ template <class T>
	struct One { static T value() { return T(1); } };

	export_ template <> struct One<vec3> { static vec3 value() { return vec3(1.f); } };
	export_ template <> struct One<quat> { static quat value() { return ZeroQuat; } };
	export_ template <> struct One<Colour> { static Colour value() { return Colour(1.f); } };

	export_ template <class T>
	struct refl_ struct_ ValueTrack
	{
		constr_ ValueTrack() {}
		constr_ ValueTrack(TrackMode mode, ValueCurve<T> curve, ValueCurve<T> min_curve, ValueCurve<T> max_curve)
			: m_mode(mode), m_curve(curve), m_min_curve(min_curve), m_max_curve(max_curve) {}
		ValueTrack(T value) : m_mode(TrackMode::Constant), m_value(value) {}
		ValueTrack(T min, T max) : m_mode(TrackMode::ConstantRandom), m_min(min), m_max(max) {}
		ValueTrack(span<T> values) : m_mode(TrackMode::Curve), m_curve(values) {}
		ValueTrack(span<T> min_values, span<T> max_values) : m_mode(TrackMode::CurveRandom), m_min_curve(min_values), m_max_curve(max_values) {}
		~ValueTrack() {}

		void set_mode(TrackMode mode)
		{
			if (mode == TrackMode::Constant)
				*this = ValueTrack<T>(T());
			else if (mode == TrackMode::ConstantRandom)
				*this = ValueTrack<T>(T(), T());
			else if (mode == TrackMode::Curve)
				*this = ValueTrack<T>(vector<T>(2, T()));
			else if (mode == TrackMode::CurveRandom)
				*this = ValueTrack<T>(vector<T>(2, T()), vector<T>(2, T()));
		}


		T sample(float t, float seed = 0.f)
		{
			if (m_mode == TrackMode::Constant)
				return m_value;
			else if (m_mode == TrackMode::ConstantRandom)
				return lerp(m_min, m_max, seed);
			else if (m_mode == TrackMode::Curve)
				return m_curve.sample_curve(t);
			else if (m_mode == TrackMode::CurveRandom || true)
				return lerp(m_min_curve.sample_curve(t), m_max_curve.sample_curve(t), seed);
		}


		attr_ TrackMode m_mode;
		attr_ T m_value = One<T>::value();
		attr_ T m_min = One<T>::value();
		attr_ T m_max = One<T>::value();
		attr_ ValueCurve<T> m_curve;
		attr_ ValueCurve<T> m_min_curve;
		attr_ ValueCurve<T> m_max_curve;
	};

	extern template struct refl_ ValueTrack<vec3>;
	extern template struct refl_ ValueTrack<quat>;
	extern template struct refl_ ValueTrack<float>;
	extern template struct refl_ ValueTrack<uint32_t>;
	extern template struct refl_ ValueTrack<Colour>;
}
