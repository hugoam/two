//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


//#include <gfx/Generated/Types.h>
#include <gfx/Animation.h>

#include <obj/Vector.h>
#include <obj/Reflect/Meta.h>
#include <math/Interp.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Skeleton.h>

#include <math/Math.h>
#include <bx/math.h>

namespace mud
{
	Animation::Animation(cstring name)
		: m_name(name)
	{}

	void AnimationTrack::insert_key(float time, const Var& value, float transition)
	{
		size_t position = key_before(time);
		m_keys.insert(m_keys.begin() + position + 1, Key{ time, value, transition });
	}

	size_t AnimationTrack::key_after(float time) const
	{
		assert(m_keys.size() > 0);
		auto predicate = [](float lhs, const Key& rhs) { return lhs < rhs.m_time; };
		auto result = std::upper_bound(m_keys.begin(), m_keys.end(), time, predicate);
		return result - m_keys.begin();
	}

	size_t AnimationTrack::key_before(float time) const
	{
		return key_after(time) - 1;
	}

	void AnimationTrack::sample(AnimationCursor& cursor, Var& value, bool forward) const
	{
		assert(m_keys.size() > 0);

		if(cursor.m_time == m_keys.back().m_time)
		{
			value = m_keys.back().m_value;
			return;
		}
		if(m_keys.size() == 1)
		{
			value = m_keys[0].m_value;
			return;
		}

		float c = std::abs(cursor.m_time - m_keys[cursor.m_prev].m_time) / std::abs(m_keys[cursor.m_next].m_time - m_keys[cursor.m_prev].m_time);
		//printf("sample %i < %i, %f\n", int(cursor.m_prev), int(cursor.m_next), c);

		if(m_interpolation == Interpolation::Nearest)
		{
			value = m_keys[cursor.m_prev].m_value;
			return;
		}
		else if(m_interpolation == Interpolation::Linear)
		{
			interpolate(value, m_keys[cursor.m_prev].m_value, m_keys[cursor.m_next].m_value, c);
			return;
		}
		else if(m_interpolation == Interpolation::Cubic)
		{
			size_t pre = max<size_t>(0, cursor.m_prev - 1);
			size_t post = max<size_t>(cursor.m_next + 1, m_keys.size());
			value = interpolate_cubic(m_keys[pre].m_value, m_keys[cursor.m_prev].m_value, m_keys[cursor.m_next].m_value, m_keys[post].m_value, c);
			return;
		}
	}

	void AnimationTrack::value(AnimationCursor& cursor, Var& value, bool forward) const
	{
		size_t key = forward ? cursor.m_next : cursor.m_prev;
		value = m_keys[key].m_value;
	}
}

