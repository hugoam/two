//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>

#include <ctime>

namespace mud
{
	export_ extern MUD_MATH_EXPORT const double c_tick_interval;

	inline size_t globalTick()
	{
		return size_t(clock() / c_tick_interval);
	}

	export_ struct refl_ MUD_MATH_EXPORT Time
	{
	public:
		constr_ Time(double value) : m_value(value) {}
		Time(int days, int hours, int minutes, int seconds) : m_value(days * 86400 + hours * 3600 + minutes * 60 + seconds) {}
		Time(int hours, int minutes, int seconds) : m_value(hours * 3600 + minutes * 60 + seconds) {}
		Time(const Time& other) : m_value(other.m_value) {}
		Time() : m_value(0.f) {}

		operator double() const { return m_value; }

		attr_ double m_value;

		inline int days() { return int(m_value) / 86400; }
		inline int hours() { return int(m_value) % 86400 / 3600; }
		inline int minutes() { return int(m_value) % 3600 / 60; }
		inline int seconds() { return int(m_value) % 60; }
	};

	export_ struct refl_ MUD_MATH_EXPORT TimeSpan
	{
	public:
		constr_ TimeSpan(Time s, Time e) : start(s), end(e) {}
		TimeSpan(int sh, int eh) : start(0, sh, 0, 0), end(0, eh, 0, 0) {}
		TimeSpan() : start(), end() {}

		Time operator [](size_t i) const { return i == 0 ? start : end; }
		Time& operator [](size_t i) { return i == 0 ? start : end; }

		attr_ Time start;
		attr_ Time end;
	};

	export_ class MUD_MATH_EXPORT Clock
    {
    public:
		Clock();

		void update();
        double read();
		double step();

		size_t readTick();
		size_t stepTick();

    private:
        clock_t m_last;
		size_t m_last_tick;
    };
}
