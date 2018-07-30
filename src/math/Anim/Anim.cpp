//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <infra/Vector.h>
#include <refl/Class.h>
#include <math/Anim/Anim.h>
#endif

namespace mud
{
	Animator Animator::me;

	Animator::Animator()
	{}

	void Animator::next_frame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);

		float elapsed = float(m_clock.step());
		for(Anim& anim : m_animations)
		{
			anim.m_cursor = min(anim.m_cursor + elapsed, anim.m_duration);
			float ratio = anim.m_cursor / anim.m_duration;
			Var value = anim.m_member->get(anim.m_object);
			Lerp::me().dispatch(value, anim.m_source_value, anim.m_target_value, ratio);
			anim.m_member->set(anim.m_object, value);
		}

		vector_prune(m_animations, [](Anim& anim) { return anim.m_cursor >= anim.m_duration; });
	}

	void Animator::animate(Ref object, Member& member, Var value, float duration)
	{
		m_animations.push_back({ object, &member, member.get_value(object), value, duration, 0.f });
	}
}
