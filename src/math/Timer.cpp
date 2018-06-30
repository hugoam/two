//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.infra;
#else
#include <math/Timer.h>
#endif

namespace mud
{
	const double c_tick_interval = 0.02;

    Clock::Clock()
        : m_last(clock())
		, m_last_tick(0)
    {}

    void Clock::update()
    {
		m_last = clock();
    }

	size_t Clock::readTick()
	{
		return size_t(this->read() / c_tick_interval);
	}

	size_t Clock::stepTick()
	{
		size_t tick = this->readTick();
		size_t delta = tick - m_last_tick;

		m_last_tick = tick;
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
