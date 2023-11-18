//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>

namespace two
{
	using stl::string;

	export_ enum class refl_ AnimTarget : unsigned int
	{
		Position,
		Rotation,
		Scale,
		Weights,
		Count
	};

	export_ enum class refl_ Interpolation : unsigned int
	{
		Nearest,
		Linear,
		Cubic
	};

	export_ struct TWO_GFX_EXPORT AnimCursor
	{
		AnimCursor() {}
		float m_time = 0.f;
		size_t m_prev = 0;
		size_t m_next = 1;
	};

	struct Value
	{
		//char mem[16];
		char mem[32]; // need to be able to store vector<float>
	};

	export_ class refl_ TWO_GFX_EXPORT AnimTrack
	{
	public:
		struct Key
		{
			Key() {}
			float m_time;
			Value m_value;
			float m_transition = 1.f;

			template <class T>
			Key(float time, const T& value, float transition = 1.f)
				: m_time(time), m_value(), m_transition(transition)
			{
				static_assert(sizeof(T) <= sizeof(Value));
				new (stl::placeholder(), m_value.mem) T(value);
			}
		};

		AnimTrack();
		AnimTrack(Animation& animation, size_t node, cstring node_name, AnimTarget target);

		attr_ Animation* m_animation;
		attr_ size_t m_node;
		attr_ string m_node_name;
		attr_ AnimTarget m_target;
		attr_ Type* m_value_type = nullptr;

		attr_ float m_length = 0.f;
		attr_ Interpolation m_interpolation = Interpolation::Linear;

		vector<Key> m_keys;

		void insert_key(float time, const Value& value, float transition = 1.f);
		size_t key_after(float time) const;
		size_t key_before(float time) const;
		Value sample(AnimCursor& cursor) const;
		Value value(AnimCursor& cursor, bool forward) const;
	};

	export_ class refl_ TWO_GFX_EXPORT Animation
	{
	public:
		explicit Animation(cstring name);

		vector<AnimTrack> tracks;

		attr_ string m_name;
		attr_ float m_length = 1.f;
		attr_ float m_step = 0.1f;
	};
}
