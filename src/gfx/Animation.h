//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Var.h>
#include <obj/Strung.h>
#include <math/Vec.h>
#endif
#include <gfx/Generated/Forward.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ enum class _refl_ Interpolation : unsigned int
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

	export_ class _refl_ MUD_GFX_EXPORT AnimationTrack
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
		
		Animation* m_animation;
		size_t m_node;
		strung m_node_name;
		Member* m_member;

		float m_length = 0.f;
		Interpolation m_interpolation = Interpolation::Linear;

		std::vector<Key> m_keys;

		void insert_key(float time, const Var &key, float transition = 1.f);
		size_t key_after(float time) const;
		size_t key_before(float time) const;
		void sample(AnimationCursor& cursor, Var& value) const;
		void value(AnimationCursor& cursor, Var& value, bool forward) const;
	};

	export_ class _refl_ MUD_GFX_EXPORT Animation
	{
	public:
		Animation(cstring name);

		std::vector<AnimationTrack> tracks;

		strung m_name;
		float m_length = 1.f;
		float m_step = 0.1f;
	};
}
