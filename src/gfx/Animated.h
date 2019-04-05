//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Animation.h>
#include <gfx/Skeleton.h>

namespace mud
{
	export_ struct refl_ MUD_GFX_EXPORT AnimatedTrack
	{
		const AnimationTrack* m_track;
		// this used to be generic Ref, but until we actually need a generic animation system, switched to explicit type
		Bone* m_bone; // node or bone
		AnimationCursor m_cursor;
		Value m_value;
	};

	export_ struct refl_ MUD_GFX_EXPORT AnimationPlay
	{
		AnimationPlay() {}
		AnimationPlay(const Animation& animation, bool loop, float speed, bool transient, Rig& rig);

		void step(float delta, float speed);
		void update(float time, float delta, float interp);

		attr_ const Animation* m_animation = nullptr;
		attr_ bool m_loop = true;
		attr_ float m_speed = 1.f;
		attr_ bool m_transient = false;

		attr_ float m_fadeout = 0.f;
		attr_ float m_fadeout_left = 0.f;
		attr_ float m_cursor = 0.f;
		attr_ bool m_ended = false;

		Rig* m_rig = nullptr;
		vector<AnimatedTrack> m_tracks;
	};

	export_ class refl_ MUD_GFX_EXPORT Mime
	{
	public:
		Mime(Node3& node);
		~Mime();

		Node3& m_node;
		Rig m_rig;

		attr_ vector<AnimationPlay> m_playing;
		attr_ vector<Animation*> m_queue;

		attr_ bool m_active = true;

		attr_ float m_speed_scale = 1.f;
		attr_ float m_default_blend_time = 1.f;

		meth_ void start(const string& animation, bool loop, float blend = 0.f, float speed = 1.f, bool transient = false);
		meth_ void play(const Animation& animation, bool loop, float blend = 0.f, float speed = 1.f, bool transient = false);
		meth_ void seek(float time);
		meth_ void pause();
		meth_ void stop();
		meth_ void advance(float time);
		meth_ void next_animation();
		
		void add_item(Item& item);

		meth_ string playing() { return m_playing.empty() ? "" : m_playing.back().m_animation->m_name; }
	};
}
