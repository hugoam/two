//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/vector.h>
#include <type/Var.h>
#include <math/Vec.h>
#endif
#include <gfx/Forward.h>

namespace mud
{
	export_ enum class refl_ AnimationTarget : unsigned int
	{
		Position,
		Rotation,
		Scale,
		Count
	};

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

	struct Value
	{
		char m_value[16];
	};

	export_ class refl_ MUD_GFX_EXPORT AnimationTrack
	{
	public:
		struct Key
		{
			Key() {}
			template <class T>
			Key(float time, const T& value, float transition = 1.f) : m_time(time), m_value(), m_transition(transition) {  *(T*)m_value.m_value = value; }
			float m_time;
			Value m_value;
			float m_transition = 1.f;
		};

		AnimationTrack();
		AnimationTrack(Animation& animation, size_t node, cstring node_name, AnimationTarget target);

		attr_ Animation* m_animation;
		attr_ size_t m_node;
		attr_ string m_node_name;
		attr_ AnimationTarget m_target;
		attr_ Type* m_value_type = nullptr;

		attr_ float m_length = 0.f;
		attr_ Interpolation m_interpolation = Interpolation::Linear;

		vector<Key> m_keys;

		void insert_key(float time, const Value& value, float transition = 1.f);
		size_t key_after(float time) const;
		size_t key_before(float time) const;
		Value sample(AnimationCursor& cursor) const;
		Value value(AnimationCursor& cursor, bool forward) const;
	};

	export_ class refl_ MUD_GFX_EXPORT Animation
	{
	public:
		explicit Animation(cstring name);

		vector<AnimationTrack> tracks;

		attr_ string m_name;
		attr_ float m_length = 1.f;
		attr_ float m_step = 0.1f;
	};
}
