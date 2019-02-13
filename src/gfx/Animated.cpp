//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/algorithm.h>
#include <math/Math.h>
#include <math/Interp.h>
#include <gfx/Types.h>
#include <gfx/Animated.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Skeleton.h>
#endif

#include <cstdio>

namespace mud
{
	Mime::Mime(Node3& node)
		: m_node(node)
	{}

	Mime::~Mime()
	{}

	void Mime::add_item(Item& item)
	{
		m_rig = *item.m_model->m_rig;
		item.m_rig = &m_rig;
	}

	void Mime::start(cstring name, bool loop, float blend, float speed, bool transient)
	{
		for(Animation* animation : m_rig.m_skeleton.m_animations)
			if(animation->m_name == name)
			{
				this->play(*animation, loop, blend, speed, transient);
				return;
			}
	}

	void Mime::play(const Animation& animation, bool loop, float blend, float speed, bool transient)
	{
		for(AnimationPlay& playing : m_playing)
		{
			playing.m_transient = true;
			if(blend == 0.f)
				blend = m_default_blend_time;
			if(blend > 0.f)
				playing.m_fadeout = blend;
		}

		m_playing.push_back({ animation, loop, speed, transient, &m_rig.m_skeleton });
		m_active = true;
	}

	void Mime::stop()
	{
		m_playing.clear();
	}

	void Mime::pause()
	{
		m_active = false;
	}

	void Mime::next_animation()
	{
		//this->play(*pop(m_queue));
	}

	void Mime::advance(float delta)
	{
		if(m_playing.size() > 2)
			printf("WARNING: Mime playing more than 2 animations at the same time\n");

		for(AnimationPlay& play : m_playing)
			play.step(delta, m_speed_scale);

		remove_if(m_playing, [](AnimationPlay& play) { return play.m_transient && play.m_ended; });

		for(Bone& bone : m_rig.m_skeleton.m_bones)
			bone.m_pose_local = bxTRS(bone.m_scale, bone.m_rotation, bone.m_position);

		m_rig.update_rig();
	}

	void Mime::seek(float time)
	{
		for(AnimationPlay& play : m_playing)
		{
			play.m_cursor = time;
			play.update(time, 0.f, 1.f);
		}
	}

	AnimationPlay::AnimationPlay(const Animation& animation, bool loop, float speed, bool transient, Skeleton* skeleton)
		: m_animation(&animation)
		, m_loop(loop)
		, m_speed(speed)
		, m_transient(transient)
	{
		m_tracks.reserve(animation.tracks.size());

		for(const AnimationTrack& track : animation.tracks)
		{
			Bone* target = nullptr;
			if(skeleton && skeleton->m_bones.size() > track.m_node)
				target = &skeleton->m_bones[track.m_node];
			if(!target)
			{
				//printf("WARNING: No bone found for animation %s track %s with target %s\n", animation.m_name.c_str(), "", track.m_node_name.c_str());
				continue;
			}

			AnimatedTrack playtrack = { &track, target, {}, track.m_keys[0].m_value };

			m_tracks.push_back(playtrack);
		}
	}

	void AnimationPlay::step(float timestep, float speed)
	{
		float delta = timestep * m_speed * speed;
		float next_pos = m_cursor + delta;
		float blend = 1.f;

		bool looped = false;
		if(m_loop && next_pos >= m_animation->m_length)
		{
			next_pos = fmod(next_pos, m_animation->m_length);
			looped = true;
		}
		else if(m_loop && next_pos < 0.f)
		{
			next_pos = m_animation->m_length - fmod(-next_pos, m_animation->m_length);
			looped = true;
		}
		else if(!m_loop && next_pos >= m_animation->m_length)
		{
			next_pos = m_animation->m_length;
			m_ended = true;
		}

		delta = next_pos - m_cursor;
		m_cursor = next_pos;

		if(m_fadeout)
		{
			blend = m_fadeout_left / m_fadeout;
			m_fadeout_left -= delta;

			if(m_fadeout_left <= 0.f)
				m_ended = true;
		}

		for(AnimatedTrack& track : m_tracks)
		{
			AnimationCursor& c = track.m_cursor;
			c.m_time = m_cursor;

			if(m_ended)
				continue;

			if(looped)
			{
				c.m_prev = m_speed > 0.f ? 0 : track.m_track->m_keys.size() - 2;
				c.m_next = m_speed > 0.f ? 1 : track.m_track->m_keys.size() - 1;
			}

			while(m_speed > 0.f && c.m_time >= track.m_track->m_keys[c.m_next].m_time)
			{
				c.m_next++;
				c.m_prev++;
			}
			while(m_speed < 0.f && c.m_time <= track.m_track->m_keys[c.m_prev].m_time)
			{
				c.m_next--;
				c.m_prev--;
			}
		}

		this->update(m_cursor, delta, blend);
	}

	void AnimationPlay::update(float time, float delta, float interp)
	{
		UNUSED(time); UNUSED(interp);
		for(AnimatedTrack& track : m_tracks)
		{
			auto apply = [](Bone& bone, AnimationTarget target, const Value& value)
			{
				if(target == AnimationTarget::Position)
					bone.m_position = *(vec3*)value.m_value;
				else if(target == AnimationTarget::Rotation)
					bone.m_rotation = *(quat*)value.m_value;
				if(target == AnimationTarget::Scale)
					bone.m_scale = *(vec3*)value.m_value;
			};

			if(track.m_track->m_interpolation > Interpolation::Nearest)
			{
				track.m_value = track.m_track->sample(track.m_cursor);

				// @todo : add blending of multiple animations
				/*
				if(track.m_value.none())
					track.m_value = value;
				else
					track.m_value = interpolate(track.m_value, value, interp);
				*/

				//printf("Animation value for track %s = %s\n", track.m_track->m_node_name.c_str(), to_string(track.m_value).c_str());
				apply(*track.m_target, track.m_track->m_target, track.m_value);
			}
			else
			{
				track.m_value = track.m_track->value(track.m_cursor, delta > 0.f);
				apply(*track.m_target, track.m_track->m_target, track.m_value);
			}
		}
	}
}

