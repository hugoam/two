//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <snd/Sound.h>
#include <snd/SoundManager.h>

#include <snd/SharedBuffer.h>
#include <snd/SoundImplementer.h>

#include <iostream>

#include <AL/al.h>

namespace mud
{
	bool operator < (Sound::Priority& rhs, Sound::Priority& lhs)
	{
		if(rhs.m_level > lhs.m_level)
			return true;
		else if(rhs.m_level < lhs.m_level)
			return false;

		else if(rhs.m_distance < lhs.m_distance)
				return true;
		else if(rhs.m_distance > lhs.m_distance)
				return false;

		else return false;
	}

	Sound::Sound(SoundImplementer& manager, SoundCallback callback)
		: m_manager(manager)
		, m_callback(callback)
	{}

	Sound::~Sound() 
	{
		if(m_callback)
			m_callback(*this);
		release();
	}

	void Sound::update(float fTime)
	{
		if(!m_active || m_state != PLAYING)
			return;

		//printf("Playing sound %s\n", m_name.c_str());

		ALenum state;
		alGetSourcei(m_source, AL_SOURCE_STATE, &state);

		if (state == AL_STOPPED)
		{
			stop();
			return;
		}

		if(m_update_transform)
		{
			alSource3f(m_source, AL_POSITION, m_position.x, m_position.y, m_position.z);
			alSource3f(m_source, AL_DIRECTION, m_direction.x, m_direction.y, m_direction.z);
			m_update_transform = false;
		}

		if(m_update_cursor)
		{
			update_play_cursor();
		}

		update_buffers();
		update_fade(fTime);
	}

	void Sound::check_error()
	{
		alGetError();
	}

	void Sound::play()
	{
		m_manager.playSound(*this);
	}

	void Sound::stop()
	{
		m_manager.stopSound(*this);
	}
	void Sound::pause()
	{
		m_manager.pauseSound(*this);
	}

	void Sound::play_impl()
	{
		if(m_state == PLAYING)
			return;

		m_state = PLAYING;

		if(m_active)
		{
			clear_buffers();
			fill_buffers();

			update_play_cursor();

			alSourcePlay(m_source);
		}
	}

	void Sound::stop_impl()
	{
		if(m_state == STOPPED)
			return;

		m_state = STOPPED;

		if(m_active)
		{
			alSourceStop(m_source);

			clear_buffers();

			rewind();
		}
	}

	void Sound::pause_impl()
	{
		m_state = PAUSED;

		if(m_active)
		{
			m_cursor = get_play_cursor();
			alSourcePause(m_source);
		}
	}

	void Sound::set_play_cursor(float seconds)
	{
		m_cursor = seconds;
		m_update_cursor = true;
	}

	void Sound::update_3D()
	{
		alSourcei(m_source, AL_SOURCE_RELATIVE, m_source_relative);
		alSourcef(m_source, AL_REFERENCE_DISTANCE, m_reference_distance);
		alSource3f(m_source, AL_POSITION, m_position.x, m_position.y, m_position.z);
		alSource3f(m_source, AL_DIRECTION, m_direction.x, m_direction.y, m_direction.z);
	}

	void Sound::disable_3D()
	{
		m_source_relative = false;
		m_position = Zero3;
		m_direction = Zero3;
		m_reference_distance = 1.f;

		if(m_active)
			this->update_3D();
	}

	void Sound::enable_3D()
	{
		m_source_relative = true;

		if(m_active)
			this->update_3D();
	}

	void Sound::set_position(const vec3& pos)
	{
		m_position = pos;
		m_update_transform = true;
	}

	void Sound::set_direction(const vec3& dir)
	{
		m_direction = dir;
		m_update_transform = true;
	}

	void Sound::set_velocity(const vec3& vel)
	{
		m_velocity = vel;

		if(m_active)
			alSource3f(m_source, AL_VELOCITY, vel.x, vel.y, vel.z);
	}

	void Sound::set_loop(bool loop)
	{
		m_loop = loop;
	}

	void Sound::set_volume(float gain)
	{
		m_gain = gain;

		if(m_active)
			alSourcef(m_source, AL_GAIN, m_gain);
	}

	void Sound::set_max_volume(float maxGain)
	{
		m_max_gain = maxGain;

		if(m_active)
			alSourcef(m_source, AL_MAX_GAIN, m_max_gain);
	}

	void Sound::set_min_volume(float minGain)
	{
		m_min_gain = minGain;

		if(m_active)
			alSourcef(m_source, AL_MIN_GAIN, m_min_gain);
	}

	void Sound::set_cone_angles(float insideAngle, float outsideAngle)
	{
		m_inner_cone_angle = insideAngle;
		m_outer_cone_angle = outsideAngle;

		if(m_active)
		{
			alSourcef (m_source, AL_CONE_INNER_ANGLE, m_inner_cone_angle);
			alSourcef (m_source, AL_CONE_OUTER_ANGLE, m_outer_cone_angle);
		}
	}

	void Sound::set_outer_cone_volume(float gain)
	{
		m_outer_cone_gain = gain;

		if(m_active)
			alSourcef (m_source, AL_CONE_OUTER_GAIN, m_outer_cone_gain);
	}

	void Sound::set_max_distance(float maxDistance)
	{
		m_max_distance = maxDistance;

		if(m_active)
			alSourcef(m_source, AL_MAX_DISTANCE, m_max_distance);
	}

	void Sound::set_rolloff_factor(float rolloffFactor)
	{
		m_rolloff_factor = rolloffFactor;

		if(m_active)
			alSourcef(m_source, AL_ROLLOFF_FACTOR, m_rolloff_factor);		
	}

	void Sound::set_reference_distance(float referenceDistance)
	{
		m_reference_distance = referenceDistance;

		if(m_active)
			alSourcef(m_source, AL_REFERENCE_DISTANCE, m_reference_distance);		
	}

	void Sound::set_pitch(float pitch)
	{
		m_pitch = pitch;

		if(m_active)
			alSourcef(m_source, AL_PITCH, m_pitch);		
	}

	void Sound::init_source()
	{
		ALenum state;
		alGetSourcei(m_source, AL_SOURCE_STATE, &state);

		alSourcef (m_source, AL_GAIN,				m_gain);
		alSourcef (m_source, AL_MAX_GAIN,			m_max_gain);
		alSourcef (m_source, AL_MIN_GAIN,			m_min_gain);
		alSourcef (m_source, AL_MAX_DISTANCE,		m_max_distance);
		alSourcef (m_source, AL_ROLLOFF_FACTOR,		m_rolloff_factor);
		alSourcef (m_source, AL_REFERENCE_DISTANCE,	m_reference_distance);
		alSourcef (m_source, AL_CONE_OUTER_GAIN,	m_outer_cone_gain);
		alSourcef (m_source, AL_CONE_INNER_ANGLE,	m_inner_cone_angle);
		alSourcef (m_source, AL_CONE_OUTER_ANGLE,	m_outer_cone_angle);
		alSource3f(m_source, AL_POSITION,			m_position.x, m_position.y, m_position.z);
		alSource3f(m_source, AL_DIRECTION,			m_direction.x, m_direction.y, m_direction.z);
		alSource3f(m_source, AL_VELOCITY,			m_velocity.x, m_velocity.y, m_velocity.z);
		alSourcef (m_source, AL_PITCH,				m_pitch);
		alSourcei (m_source, AL_SOURCE_RELATIVE,	m_source_relative);
		alSourcei (m_source, AL_LOOPING,			m_loop);
		//alSourcei (m_source, AL_SOURCE_STATE,		AL_INITIAL);
		alSourceRewind(m_source);
	}

	void Sound::assign_source(ALuint src)
	{
		m_active = true;
		m_source = src;
		init_source();
		fill_buffers();

		if(m_pause_on_disactivate)
		{
			play_impl();
		}
	}

	ALuint Sound::release_source()
	{
		ALuint source = m_source;

		if(m_state != STOPPED && m_pause_on_disactivate)
			pause_impl();

		alSourceStop(m_source);
		clear_buffers();

		m_source = AL_NONE;
		m_active = false;
		return source;
	}

	void Sound::start_fade(bool fDir, float fadeTime, FadeControl actionOnComplete)
	{
		m_fade =
		{
			0.f,
			fadeTime,
			fDir ? 0.f : m_gain,
			fDir ? 1.f : 0.f,
			true,
			actionOnComplete
		};

		if(fDir == true && !is_playing())
			play();
	}

	void Sound::update_fade(float fTime)
	{
		if(!m_fade.m_fade) return;

		m_fade.m_timer += fTime;
		if(m_fade.m_timer >= m_fade.m_time)
		{
			set_volume(m_fade.m_end_vol);
			m_fade.m_fade = false;

			if(m_fade.m_end_action == FC_PAUSE)
				pause(); 
			else if(m_fade.m_end_action == FC_STOP)
				stop(); 
		}
		else
		{
			float vol = (m_fade.m_end_vol - m_fade.m_init_vol) * (m_fade.m_timer / m_fade.m_time);
			set_volume(m_fade.m_init_vol + vol);
		}
	}
}
