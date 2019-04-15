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
	Mime::Mime()
	{}

	Mime::~Mime()
	{}

	void Mime::add_item(Item& item)
	{
		m_rig = *item.m_model->m_rig;
		item.m_rig = &m_rig;

		m_targets = m_rig.m_skeleton.m_bones;
		m_nodes.resize(m_rig.m_skeleton.m_bones.size());

		m_anims = item.m_model->m_anims;
	}

	void Mime::add_nodes(span<Node3> nodes)
	{
		m_targets = nodes;
		m_nodes.resize(nodes.size());
	}

	void Mime::start(const string& name, bool loop, float blend, float speed, bool transient)
	{
		for(Animation* animation : m_anims)
			if(animation->m_name == name)
			{
				this->play(*animation, loop, blend, speed, transient);
				return;
			}
	}

	void Mime::play(const Animation& animation, bool loop, float blend, float speed, bool transient)
	{
		for(AnimPlay& playing : m_playing)
		{
			playing.m_transient = true;
			if(blend == 0.f)
				blend = m_default_blend_time;
			if(blend > 0.f)
				playing.m_fadeout = blend;
		}

		m_playing.push_back({ animation, loop, speed, transient, m_nodes, &m_rig });
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
			printf("[warning] Mime playing more than 2 animations at the same time\n");

		for(AnimPlay& play : m_playing)
			play.step(delta, m_speed_scale);

		remove_if(m_playing, [](AnimPlay& play) { return play.m_transient && play.m_ended; });

		for(AnimNode& node : m_nodes)
		{
			node.m_transform = bxTRS(node.m_scale, node.m_rotation, node.m_position);
		}

		for(size_t i = 0; i < m_nodes.size(); ++i)
		{
			Node3& node = m_targets[i];
			node.m_transform = node.m_parent != UINT32_MAX
				? m_targets[node.m_parent].m_transform * m_nodes[i].m_transform
				: m_nodes[i].m_transform;
		}

		m_rig.update_rig();
	}

	void Mime::seek(float time)
	{
		for(AnimPlay& play : m_playing)
		{
			play.m_cursor = time;
			play.update(time, 0.f, 1.f);
		}
	}

	AnimPlay::AnimPlay(const Animation& animation, bool loop, float speed, bool transient, span<AnimNode> nodes, Rig* rig)
		: m_animation(&animation)
		, m_loop(loop)
		, m_speed(speed)
		, m_transient(transient)
		, m_nodes(nodes)
		, m_rig(rig)
	{
		m_tracks.reserve(animation.tracks.size());

		for(const AnimTrack& track : animation.tracks)
		{
			AnimNode* target = nullptr;
			if(nodes.size() > track.m_node)
				target = &nodes[track.m_node];
			if(!target && track.m_target != AnimTarget::Weights)
			{
				printf("[warning] No bone found for animation %s track %s with target %i %s\n", animation.m_name.c_str(), "", track.m_node, track.m_node_name.c_str());
				continue;
			}

			Track playtrack = { &track, target, {}, track.m_keys[0].m_value };

			m_tracks.push_back(playtrack);
		}
	}

	void AnimPlay::step(float timestep, float speed)
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

		for(AnimPlay::Track& track : m_tracks)
		{
			AnimCursor& c = track.m_cursor;
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

	void AnimPlay::update(float time, float delta, float interp)
	{
		UNUSED(time); UNUSED(interp);
		for(AnimPlay::Track& track : m_tracks)
		{
			auto apply = [](Rig& rig, AnimNode& bone, AnimTarget target, const Value& value)
			{
				if(target == AnimTarget::Position)
					bone.m_position = *(vec3*)value.mem;
				else if(target == AnimTarget::Rotation)
					bone.m_rotation = *(quat*)value.mem;
				else if(target == AnimTarget::Scale)
					bone.m_scale = *(vec3*)value.mem;
				else if(target == AnimTarget::Weights)
				{
					vector<float>& weights = *(vector<float>*)value.mem;
					rig.m_morphs.resize(weights.size());
					for(size_t i = 0; i < weights.size(); ++i)
					{
						rig.m_morphs[i] = weights[i];
					}
				}
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
				apply(*m_rig, *track.m_node, track.m_track->m_target, track.m_value);
			}
			else
			{
				track.m_value = track.m_track->value(track.m_cursor, delta > 0.f);
				apply(*m_rig, *track.m_node, track.m_track->m_target, track.m_value);
			}
		}
	}
}

