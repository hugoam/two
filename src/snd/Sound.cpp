//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <snd/Sound.h>

#include <snd/SharedBuffer.h>
#include <snd/SoundImplementer.h>

#include <iostream>

/* OpenAL */
#include <al.h>

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

		ALenum state;
		alGetSourcei(m_source, AL_SOURCE_STATE, &state);

		if (state == AL_STOPPED)
		{
			stop();
			return;
		}

		if(m_updateTransform)
		{
			alSource3f(m_source, AL_POSITION, m_position.x, m_position.y, m_position.z);
			alSource3f(m_source, AL_DIRECTION, m_direction.x, m_direction.y, m_direction.z);
			m_updateTransform = false;
		}

		if(m_updateCursor)
		{
			updatePlayCursor();
		}

		updateBuffers();
		updateFade(fTime);
	}

	void Sound::checkError()
	{
		alGetError();
	}

	void Sound::play()
	{
		m_manager.playSound(this);
	}

	void Sound::stop()
	{
		m_manager.stopSound(this);
	}
	void Sound::pause()
	{
		m_manager.pauseSound(this);
	}

	void Sound::playImpl()
	{
		if(m_state == PLAYING)
			return;

		m_state = PLAYING;

		if(m_active)
		{
			updatePlayCursor();

			clearBuffers();
			fillBuffers();

			alSourcePlay(m_source);
		}
	}

	void Sound::stopImpl()
	{
		if(m_state == STOPPED)
			return;

		m_state = STOPPED;

		if(m_active)
		{
			alSourceStop(m_source);

			clearBuffers();
			rewind();
		}
	}

	void Sound::pauseImpl()
	{
		m_state = PAUSED;

		if(m_active)
		{
			m_cursor = getPlayCursor();
			alSourcePause(m_source);
		}
	}

	void Sound::setPlayCursor(float seconds)
	{
		m_cursor = seconds;
		m_updateCursor = true;
	}

	void Sound::update3D()
	{
		alSourcei(m_source, AL_SOURCE_RELATIVE, m_sourceRelative);
		alSourcef(m_source, AL_REFERENCE_DISTANCE, m_referenceDistance);
		alSource3f(m_source, AL_POSITION, m_position.x, m_position.y, m_position.z);
		alSource3f(m_source, AL_DIRECTION, m_direction.x, m_direction.y, m_direction.z);
	}

	void Sound::disable3D()
	{
		m_sourceRelative = false;
		m_position = Zero3;
		m_direction = Zero3;
		m_referenceDistance = 1.f;

		if(m_active)
			this->update3D();
	}

	void Sound::enable3D()
	{
		m_sourceRelative = true;

		if(m_active)
			this->update3D();
	}

	void Sound::set_position(const vec3& pos)
	{
		m_position = pos;
		m_updateTransform = true;
	}

	void Sound::setDirection(const vec3& dir)
	{
		m_direction = dir;
		m_updateTransform = true;
	}

	void Sound::setVelocity(const vec3& vel)
	{
		m_velocity = vel;

		if(m_active)
			alSource3f(m_source, AL_VELOCITY, vel.x, vel.y, vel.z);
	}

	void Sound::setLoop(bool loop)
	{
		m_loop = loop;
	}

	void Sound::setVolume(float gain)
	{
		m_gain = gain;

		if(m_active)
			alSourcef(m_source, AL_GAIN, m_gain);
	}

	void Sound::setMaxVolume(float maxGain)
	{
		m_maxGain = maxGain;

		if(m_active)
			alSourcef(m_source, AL_MAX_GAIN, m_maxGain);
	}

	void Sound::setMinVolume(float minGain)
	{
		m_minGain = minGain;

		if(m_active)
			alSourcef(m_source, AL_MIN_GAIN, m_minGain);
	}

	void Sound::setConeAngles(float insideAngle, float outsideAngle)
	{
		m_innerConeAngle = insideAngle;
		m_outerConeAngle = outsideAngle;

		if(m_active)
		{
			alSourcef (m_source, AL_CONE_INNER_ANGLE, m_innerConeAngle);
			alSourcef (m_source, AL_CONE_OUTER_ANGLE, m_outerConeAngle);
		}
	}

	void Sound::setOuterConeVolume(float gain)
	{
		m_outerConeGain = gain;

		if(m_active)
			alSourcef (m_source, AL_CONE_OUTER_GAIN, m_outerConeGain);
	}

	void Sound::setMaxDistance(float maxDistance)
	{
		m_maxDistance = maxDistance;

		if(m_active)
			alSourcef(m_source, AL_MAX_DISTANCE, m_maxDistance);
	}

	void Sound::setRolloffFactor(float rolloffFactor)
	{
		m_rolloffFactor = rolloffFactor;

		if(m_active)
			alSourcef(m_source, AL_ROLLOFF_FACTOR, m_rolloffFactor);		
	}

	void Sound::setReferenceDistance(float referenceDistance)
	{
		m_referenceDistance = referenceDistance;

		if(m_active)
			alSourcef(m_source, AL_REFERENCE_DISTANCE, m_referenceDistance);		
	}

	void Sound::setPitch(float pitch)
	{
		m_pitch = pitch;

		if(m_active)
			alSourcef(m_source, AL_PITCH, m_pitch);		
	}

	void Sound::initSource()
	{		
		alSourcef (m_source, AL_GAIN,				m_gain);
		alSourcef (m_source, AL_MAX_GAIN,			m_maxGain);
		alSourcef (m_source, AL_MIN_GAIN,			m_minGain);
		alSourcef (m_source, AL_MAX_DISTANCE,		m_maxDistance);	
		alSourcef (m_source, AL_ROLLOFF_FACTOR,		m_rolloffFactor);
		alSourcef (m_source, AL_REFERENCE_DISTANCE,	m_referenceDistance);
		alSourcef (m_source, AL_CONE_OUTER_GAIN,	m_outerConeGain);
		alSourcef (m_source, AL_CONE_INNER_ANGLE,	m_innerConeAngle);
		alSourcef (m_source, AL_CONE_OUTER_ANGLE,	m_outerConeAngle);
		alSource3f(m_source, AL_POSITION,			m_position.x, m_position.y, m_position.z);
		alSource3f(m_source, AL_DIRECTION,			m_direction.x, m_direction.y, m_direction.z);
		alSource3f(m_source, AL_VELOCITY,			m_velocity.x, m_velocity.y, m_velocity.z);
		alSourcef (m_source, AL_PITCH,				m_pitch);
		alSourcei (m_source, AL_SOURCE_RELATIVE,	m_sourceRelative);
		alSourcei (m_source, AL_LOOPING,			m_loop);
		alSourcei (m_source, AL_SOURCE_STATE,		AL_INITIAL);
	}

	void Sound::assignSource(ALuint src)
	{
		m_active = true;
		m_source = src;
		initSource();
		fillBuffers();	

		if(m_pauseOnDisactivate)
			playImpl();
	}

	void Sound::releaseSource()
	{
		if(m_pauseOnDisactivate)
			pauseImpl();

		alSourceStop(m_source);
		clearBuffers();	

		m_source = AL_NONE;
		m_active = false;
	}

	void Sound::startFade(bool fDir, float fadeTime, FadeControl actionOnComplete)
	{
		m_fade = true;
	    m_fadeInitVol = fDir ? 0.f : m_gain;
		m_fadeEndVol = fDir ? 1.f : 0.f;
		m_fadeTimer = 0.f;
		m_fadeEndAction = actionOnComplete;
		m_fadeTime = fadeTime;

		if(fDir == true && !isPlaying())
			play();
	}

	void Sound::updateFade(float fTime)
	{
		if(m_fade) return;

		m_fadeTimer += fTime;
		if(m_fadeTimer >= m_fadeTime)
		{
			setVolume(m_fadeEndVol);
			m_fade = false;

			if(m_fadeEndAction == FC_PAUSE)
				pause(); 
			else if(m_fadeEndAction == FC_STOP)
				stop(); 
		}
		else
		{
			float vol = (m_fadeEndVol - m_fadeInitVol) * (m_fadeTimer / m_fadeTime);
			setVolume(m_fadeInitVol + vol);
		}
	}
}
