//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/Curve.h>
#endif

namespace mud
{
	template <class T>
	ValueCurve<T>::ValueCurve() {}
	template <class T>
	ValueCurve<T>::ValueCurve(vector<T> keys) : m_keys(keys) {}
	template <class T>
	ValueCurve<T>::~ValueCurve() {}

	template <class T>
	T ValueCurve<T>::sample_curve(float t)
	{
		uint32_t key = uint32_t(t * (m_keys.size() - 1));
		float interval = 1.f / float(m_keys.size() - 1);
		float ttmod = fmod(t, interval) / interval;

		return mud::lerp(m_keys[key], m_keys[key + 1], ttmod);
	}

	template struct MUD_MATH_EXPORT ValueCurve<vec3>;
	template struct MUD_MATH_EXPORT ValueCurve<quat>;
	template struct MUD_MATH_EXPORT ValueCurve<float>;
	template struct MUD_MATH_EXPORT ValueCurve<uint32_t>;
	template struct MUD_MATH_EXPORT ValueCurve<Colour>;

	template <class T>
	ValueTrack<T>::ValueTrack() {}
	template <class T>
	ValueTrack<T>::ValueTrack(TrackMode mode, ValueCurve<T> curve, ValueCurve<T> min_curve, ValueCurve<T> max_curve) : m_mode(mode), m_curve(curve), m_min_curve(min_curve), m_max_curve(max_curve) {}
	template <class T>
	ValueTrack<T>::ValueTrack(T value) : m_mode(TrackMode::Constant), m_value(value) {}
	template <class T>
	ValueTrack<T>::ValueTrack(T min, T max) : m_mode(TrackMode::ConstantRandom), m_min(min), m_max(max) {}
	template <class T>
	ValueTrack<T>::ValueTrack(vector<T> values) : m_mode(TrackMode::Curve), m_curve(values) {}
	template <class T>
	ValueTrack<T>::ValueTrack(vector<T> min_values, vector<T> max_values) : m_mode(TrackMode::CurveRandom), m_min_curve(min_values), m_max_curve(max_values) {}
	template <class T>
	ValueTrack<T>::~ValueTrack() {}

	template <class T>
	void ValueTrack<T>::set_mode(TrackMode mode)
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

	template <class T>
	T ValueTrack<T>::sample(float t, float seed)
	{
		if (m_mode == TrackMode::Constant)
			return m_value;
		else if (m_mode == TrackMode::ConstantRandom)
			return mud::lerp(m_min, m_max, seed);
		else if (m_mode == TrackMode::Curve)
			return m_value * m_curve.sample_curve(t);
		else //if(m_mode == TrackMode::CurveRandom)
			return mud::lerp(m_min * m_min_curve.sample_curve(t), m_max * m_max_curve.sample_curve(t), seed);
	}

	template struct MUD_MATH_EXPORT ValueTrack<vec3>;
	template struct MUD_MATH_EXPORT ValueTrack<quat>;
	template struct MUD_MATH_EXPORT ValueTrack<float>;
	template struct MUD_MATH_EXPORT ValueTrack<uint32_t>;
	template struct MUD_MATH_EXPORT ValueTrack<Colour>;
}
