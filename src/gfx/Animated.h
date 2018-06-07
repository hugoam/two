//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#endif
#include <gfx/Generated/Forward.h>
#include <gfx/Animation.h>
#include <gfx/Skeleton.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

namespace mud
{

	export_ struct refl_ MUD_GFX_EXPORT AnimatedTrack
	{
		const AnimationTrack* m_track;
		Ref m_target; // node or bone
		AnimationCursor m_cursor;
		Var m_value;
	};

	export_ struct refl_ MUD_GFX_EXPORT AnimationPlay
	{
		AnimationPlay() {}
		AnimationPlay(const Animation& animation, bool loop, float speed, bool reverse, Skeleton* skeleton = nullptr);
		
		void step(float delta, float speed);
		void update(float time, float delta, float interp);

		const Animation* m_animation = nullptr;
		bool m_loop = true;
		float m_speed = 1.f;
		bool m_reverse = false;

		float m_fadeout = 0.f;
		float m_fadeout_left = 0.f;
		float m_cursor = 0.f;
		bool m_ended = false;

		std::vector<AnimatedTrack> m_tracks;
	};

	export_ class refl_ MUD_GFX_EXPORT Animated
	{
	public:
		Animated(Node3& node);
		~Animated();

		Node3& m_node;
		Rig m_rig;
		float m_speed_scale = 1.f;
		float m_default_blend_time = 1.f;

		std::vector<AnimationPlay> m_playing;
		std::vector<Animation*> m_queue;

		bool m_active = true;

		void play(const Animation& animation, bool loop, float blend = 0.f, float speed = 1.f, bool reverse = false);
		void play(cstring animation, bool loop, float blend = 0.f, float speed = 1.f, bool reverse = false);
		void seek(float time);
		void pause();
		void stop();
		void advance(float time);
		void next_animation();
		
		void add_item(Item& item);
	};
}
