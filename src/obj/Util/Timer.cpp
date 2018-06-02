//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h>
#include <time.h>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Config.h>
#include <obj/Util/Timer.h>
#endif

namespace mud
{
    Clock::Clock()
        : m_last(clock())
		, m_lastTick(0)
    {}

    void Clock::update()
    {
		m_last = clock();
    }

	size_t Clock::readTick()
	{
		return size_t(this->read() / TICK_INTERVAL);
	}

	size_t Clock::stepTick()
	{
		size_t tick = this->readTick();
		size_t delta = tick - m_lastTick;

		m_lastTick = tick;
		return delta;
	}

    double Clock::read()
    {
        double timeStep = static_cast<double>(clock() - m_last) / CLOCKS_PER_SEC;
        return timeStep;
    }

	double Clock::step()
	{
		double step = this->read();
		this->update();
		return step;
	}
}
