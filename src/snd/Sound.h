//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <snd/Forward.h>
#include <snd/Structs.h>
#include <math/Vec.h>

#include <list>
#include <functional>
#include <stdint.h>

namespace mud
{
	class Sound;

	using cstring = const char*;
	using SoundCallback = std::function<void(Sound&)>;

	class MUD_SND_EXPORT Sound
	{
	public:
		enum State
		{
			PLAYING,
			PAUSED,
			STOPPED
		};

		struct Priority
		{
			uint8_t m_level;
			float m_distance;

			int m_queueIndex;
			std::list<Sound*>::iterator m_queueIterator;

			friend bool operator < (Priority& rhs, Priority& lhs);
		};

		enum FadeControl
		{
			FC_NONE		= 0x00,
			FC_PAUSE	= 0x01,
			FC_STOP		= 0x02
		};

	// Thread-Safe externals
	public:
		Sound(SoundImplementer& manager, SoundCallback callback = {});
		virtual ~Sound();

		void play();
		void stop();
		void pause();

		// @check : are these thread-safe ???
		void setDirection(const vec3& dir);
		void set_position(const vec3& pos);
		void setVelocity(const vec3& vel);

	// Thread-Exclusive externals
	public:
		void update(float fTime);

		void playImpl();
		void stopImpl();
		void pauseImpl();

		void enable3D();
		void disable3D();
		void update3D();

		virtual void setLoop(bool loop);

		void setVolume(float gain);
		void setMaxVolume(float maxGain);
		void setMinVolume(float minGain);

		void setConeAngles(float insideAngle, float outsideAngle);
		void setOuterConeVolume(float gain);
		void setMaxDistance(float maxDistance);
		void setRolloffFactor(float rolloffFactor);
		void setReferenceDistance(float referenceDistance);

		void setPitch(float pitch);

		void assignSource(ALuint src);
		void releaseSource();

		void setPlayCursor(float seconds);

		void startFade(bool fDir, float fadeTime, FadeControl actionOnComplete = FC_NONE);

	public:
		inline bool isPlaying() const { return m_state == PLAYING; }
		inline bool isPaused() const { return m_state == PAUSED; }
		inline bool isStopped() const { return m_state == STOPPED; }

	public:
		virtual void open(cstring filename) { UNUSED(filename); }
		virtual void openShared(SharedBuffer& buffer) { UNUSED(buffer); }

	protected:
		virtual void release() {}

		virtual void fillBuffers() = 0;
		virtual void clearBuffers() = 0;
		virtual void updateBuffers() = 0;

		virtual void rewind() = 0;
		virtual void updatePlayCursor() = 0;
		virtual ALfloat getPlayCursor() = 0;

	protected:
		void initSource();

		void checkError();

		void updateFade(float fTime);

	public:
		SoundImplementer& m_manager;
		SoundCallback m_callback;

		ALuint m_source = 0;			// OpenAL Source
		Priority m_priority;			// Priority assigned to source
		bool m_active = false;
		bool m_pauseOnDisactivate;

		float m_gain = 1.f;				// Current volume
		float m_pitch = 1.f;			// Current pitch 

		bool m_loop = false;
		bool m_temporary = false;
		bool m_stream = false;			// Stream flag
		bool m_mono;

		State m_state = STOPPED;
		ALfloat m_cursor = 0.f;			// Playback position in seconds

		float m_duration = 0.f;			// Time in seconds of sound file
		bool m_seekable = true;			// Flag indicating seeking available

		bool m_sourceRelative;

		vec3 m_position = Zero3;	// 3D position
		vec3 m_direction = Zero3;	// 3D direction
		vec3 m_velocity = Zero3;	// 3D velocity

		float m_maxGain = 1.f;			// Minimum volume
		float m_minGain = 0.f;			// Maximum volume
		float m_maxDistance = 1E10;		// Maximum attenuation distance
		float m_rolloffFactor = 1.f;	// Rolloff factor for attenuation
		float m_referenceDistance = 1.f;// Half-volume distance for attenuation

		float m_outerConeGain = 0.f;	// Outer cone volume
		float m_innerConeAngle = 360.f;	// Inner cone angle
		float m_outerConeAngle = 360.f;	// outer cone angle

		bool m_updateTransform = false;	// Transformation update flag
		bool m_updateCursor = false;	// Flag indicating playback position has changed

		std::list<float> m_cuePoints;	// List of play position points

		/* Fade sound */
		float m_fadeTimer = 0.f;
		float m_fadeTime = 1.f;
		float m_fadeInitVol = 0.f;
		float m_fadeEndVol = 1.f;
		bool m_fade = false;
		FadeControl m_fadeEndAction = FC_NONE;
	};
}
