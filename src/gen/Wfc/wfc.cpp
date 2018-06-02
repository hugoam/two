//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#else
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <random>
#endif

#ifdef MUD_MODULES
module mud.gen;
#else
#include <obj/String/StringConvert.h>
#include <gen/Wfc/wfc.h>
#endif

namespace mud
{
	double calc_sum(const std::vector<double>& a)
	{
		return std::accumulate(a.begin(), a.end(), 0.0);
	}

	// Pick a random index weighted by a
	size_t spin_the_bottle(const std::vector<double>& a, double between_zero_and_one)
	{
		double sum = calc_sum(a);

		if(sum == 0.0)
			return std::floor(between_zero_and_one * a.size());

		double between_zero_and_sum = between_zero_and_one * sum;

		double accumulated = 0;
		for(size_t i = 0; i < a.size(); ++i)
		{
			accumulated += a[i];
			if(between_zero_and_sum <= accumulated)
				return i;
		}

		return 0;
	}

	Wave::Wave()
		: m_solved(true)
	{}

	Wave::Wave(uint16_t states, uint16_t width, uint16_t height, uint16_t depth, bool periodic)
		: m_width(width)
		, m_height(height)
		, m_depth(depth)
		, m_periodic(periodic)
		, m_states(states, 1.0)
		, m_wave(width, height, depth, std::vector<ubool>(states, true))
	{
		static DoubleGenerator generator;
		m_random_double = [&] { return generator.next(); };
	}

	void Wave::clear()
	{
		m_wave.reset(m_width, m_height, m_depth, std::vector<ubool>(m_states.size(), true));
		m_changes.clear();
	}

	Result Wave::find_lowest_entropy(uvec3& coord)
	{
		// We actually calculate exp(entropy), i.e. the sum of the weights of the possible patterns
		double min = std::numeric_limits<double>::infinity();

		for(uint16_t x = 0; x < m_width; ++x)
			for(uint16_t y = 0; y < m_height; ++y)
				for(uint16_t z = 0; z < m_depth; ++z)
				{
					if(!m_valid_coord(x, y, z)) continue;

					size_t states = 0;
					double entropy = 0;

					for(uint16_t t = 0; t < m_states.size(); ++t)
					{
						if(m_wave.at(x, y, z)[t])
						{
							states += 1;
							entropy += m_states[t];
						}
					}

					if(entropy == 0 || states == 0)
						return Result::kFail;

					if(states == 1)
						continue; // Already frozen

					// Add a tie-breaking bias:
					const double noise = 0.5 * m_random_double();
					entropy += noise;

					if(entropy < min)
					{
						min = entropy;
						coord = { x, y, z };
					}
				}

		if(min == std::numeric_limits<double>::infinity())
			return Result::kSuccess;
		else
			return Result::kUnfinished;
	}

	Result Wave::observe()
	{
		uvec3 coord;
		const auto result = find_lowest_entropy(coord);
		if(result == Result::kSuccess)
			m_solved = true;
		if(result != Result::kUnfinished)
			return result;

		std::vector<double> distribution(m_states.size());
		for(uint16_t t = 0; t < m_states.size(); ++t)
			distribution[t] = m_wave.at(coord.x, coord.y, coord.z)[t] ? m_states[t] : 0;

		size_t r = spin_the_bottle(distribution, m_random_double());
		for(uint16_t t = 0; t < m_states.size(); ++t)
			m_wave.at(coord.x, coord.y, coord.z)[t] = (t == r);

		m_changes.push_back(coord);
		m_stabilized = false;

		return Result::kUnfinished;
	}

	void Wave::propagate()
	{
		m_propagate(*this);
	}

	void Wave::add_foundation(uint16_t tile)
	{
		for(uint16_t x = 0; x < m_wave.m_x; ++x)
		{
			for(uint16_t t = 0; t < m_states.size(); ++t)
				if(t != tile)
					m_wave.at(x, m_wave.m_y - 1)[t] = false;

			m_changes.push_back({ x, m_wave.m_y - 1, 0 });

			for(uint16_t y = 0; y < m_wave.m_y - 1; ++y)
			{
				m_wave.at(x, y)[tile] = false;
				m_changes.push_back({ x, y, 0 });
			}

			this->propagate();
		}
	}

	Result Wave::solve(size_t limit)
	{
		for(size_t l = 0; l < limit || limit == 0; ++l)
		{
			Result result = this->observe();

			if(result != Result::kUnfinished)
				return result;

			this->propagate();
		}

		return Result::kUnfinished;
	}
}
