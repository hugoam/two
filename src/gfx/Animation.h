//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <type/Var.h>
#include <infra/Strung.h>
#include <math/Vec.h>
#endif
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ enum class refl_ Interpolation : unsigned int
	{
		Nearest,
		Linear,
		Cubic
	};

	export_ struct MUD_GFX_EXPORT AnimationCursor
	{
		AnimationCursor() {}
		float m_time = 0.f;
		size_t m_prev = 0;
		size_t m_next = 1;
	};

	export_ class refl_ MUD_GFX_EXPORT AnimationTrack
	{
	public:
		struct Key
		{
			Key(float time, Var value, float transition = 1.f) : m_time(time), m_value(value), m_transition(transition) {}
			float m_time;
			Var m_value;
			float m_transition = 1.f;
		};

		AnimationTrack(Animation& animation, size_t node, cstring node_name, Member& member)
			: m_animation(&animation), m_node(node), m_node_name(node_name), m_member(&member)
		{}
		
		attr_ Animation* m_animation;
		attr_ size_t m_node;
		attr_ string m_node_name;
		attr_ Member* m_member;

		attr_ float m_length = 0.f;
		attr_ Interpolation m_interpolation = Interpolation::Linear;

		std::vector<Key> m_keys;

		void insert_key(float time, const Var &key, float transition = 1.f);
		size_t key_after(float time) const;
		size_t key_before(float time) const;
		void sample(AnimationCursor& cursor, Var& value) const;
		void value(AnimationCursor& cursor, Var& value, bool forward) const;
	};

	export_ class refl_ MUD_GFX_EXPORT Animation
	{
	public:
		Animation(cstring name);

		std::vector<AnimationTrack> tracks;

		attr_ string m_name;
		attr_ float m_length = 1.f;
		attr_ float m_step = 0.1f;
	};
}
