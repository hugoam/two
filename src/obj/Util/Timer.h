//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

/* std */
#include <obj/Generated/Forward.h>

#include <ctime>

#define TICK_INTERVAL 0.02

namespace mud
{
	inline size_t globalTick()
	{
		return size_t(clock() / TICK_INTERVAL);
	}

	struct _refl_ MUD_OBJ_EXPORT Time
	{
	public:
		_constr_ Time(double value) : m_value(value) {}
		Time(int days, int hours, int minutes, int seconds) : m_value(days * 86400 + hours * 3600 + minutes * 60 + seconds) {}
		Time(int hours, int minutes, int seconds) : m_value(hours * 3600 + minutes * 60 + seconds) {}
		Time(const Time& other) : m_value(other.m_value) {}
		Time() : m_value(0.f) {}

		operator double() const { return m_value; }

		_attr_ double m_value;

		inline int days() { return int(m_value) / 86400; }
		inline int hours() { return int(m_value) % 86400 / 3600; }
		inline int minutes() { return int(m_value) % 3600 / 60; }
		inline int seconds() { return int(m_value) % 60; }
	};

	struct _refl_ MUD_OBJ_EXPORT TimeSpan
	{
	public:
		_constr_ TimeSpan(Time s, Time e) : start(s), end(e) {}
		TimeSpan(int sh, int eh) : start(0, sh, 0, 0), end(0, eh, 0, 0) {}
		TimeSpan() : start(), end() {}

		Time operator [](size_t i) const { return i == 0 ? start : end; }
		Time& operator [](size_t i) { return i == 0 ? start : end; }

		_attr_ Time start;
		_attr_ Time end;
	};

	class MUD_OBJ_EXPORT Clock
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
		size_t m_lastTick;
    };
}
