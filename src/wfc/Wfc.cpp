//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <cmath>
#include <cfloat>
#endif

#ifdef MUD_MODULES
module mud.wfc;
#else
#include <stl/limits.h>
#include <infra/ToString.h>
#include <math/Random.h>
#include <wfc/Wfc.h>
#endif

namespace mud
{
	double calc_sum(const vector<double>& a)
	{
		double sum = 0.0;
		for(double d : a)
			sum += d;
		return sum;
	}

	// Pick a random index weighted by a
	size_t spin_the_bottle(const vector<double>& a, double between_zero_and_one)
	{
		double sum = calc_sum(a);

		if(sum == 0.0)
			return size_t(floor(between_zero_and_one * a.size()));

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
		, m_wave(width, height, depth, vector<ubool>(states, true))
	{
		m_random_double = []() -> double { return random_scalar<double>(); };
	}

	void Wave::clear()
	{
		m_wave.reset(m_width, m_height, m_depth, vector<ubool>(m_states.size(), true));
		m_changes.clear();
	}

	Result Wave::find_lowest_entropy(uvec3& coord)
	{
		// We actually calculate exp(entropy), i.e. the sum of the weights of the possible patterns
		double min = FLT_MAX;// std::numeric_limits<double>::infinity();

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
					{
						int directions = m_depth == 1 ? 4 : 6;

						for(int d = 0; d < directions; d++)
						{
							uvec3 adjacent;
							neighbour(*this, { x, y, z }, SignedAxis(d), adjacent);
							m_failure_point[d] = tile_at(*this, uint16_t(adjacent.x), uint16_t(adjacent.y), uint16_t(adjacent.z));
						}
						return Result::kFail;
					}

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

		if(min == FLT_MAX) //std::numeric_limits<double>::infinity())
			return Result::kSuccess;
		else
			return Result::kUnfinished;
	}

	Result Wave::observe()
	{
		uvec3 coord;
		m_state = find_lowest_entropy(coord);
		if(m_state == Result::kSuccess)
			m_solved = true;
		if(m_state != Result::kUnfinished)
			return m_state;

		vector<double> distribution(m_states.size());
		for(uint16_t t = 0; t < m_states.size(); ++t)
			distribution[t] = m_wave.at(coord.x, coord.y, coord.z)[t] ? m_states[t] : 0;

		size_t r = spin_the_bottle(distribution, m_random_double());
		for(uint16_t t = 0; t < m_states.size(); ++t)
			m_wave.at(coord.x, coord.y, coord.z)[t] = (t == r);

		m_changes.push_back(coord);
		m_stabilized = false;

		return Result::kUnfinished;
	}

	void Wave::propagate(size_t limit)
	{
		for(size_t i = 0; (limit && i < limit) || (!limit && m_changes.size() > 0); ++i)
			m_propagate(*this);

		if(m_changes.size() == 0)
			m_stabilized = true;
	}

	void Wave::set_tile(const uvec3& coord, uint16_t tile)
	{
		for(uint16_t t = 0; t < m_states.size(); ++t)
			if(t != tile)
				m_wave.at(coord.x, coord.y, coord.z)[t] = false;

		m_changes.push_back({ coord.x, coord.y, coord.z });
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
