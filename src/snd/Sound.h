//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/string.h>
#include <stl/vector.h>
#include <snd/Forward.h>
#include <snd/Structs.h>
#include <math/Vec.h>

#include <stdint.h>

namespace two
{
	class Sound;

	using cstring = const char*;
	using SoundCallback = void(*)(Sound&);

	class TWO_SND_EXPORT Sound
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

			friend bool operator<(Priority& rhs, Priority& lhs);
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
		void set_direction(const vec3& dir);
		void set_position(const vec3& pos);
		void set_velocity(const vec3& vel);

	// Thread-Exclusive externals
	public:
		void update(float fTime);

		void play_impl();
		void stop_impl();
		void pause_impl();

		void enable_3D();
		void disable_3D();
		void update_3D();

		virtual void set_loop(bool loop);

		void set_volume(float gain);
		void set_max_volume(float maxGain);
		void set_min_volume(float minGain);

		void set_cone_angles(float insideAngle, float outsideAngle);
		void set_outer_cone_volume(float gain);
		void set_max_distance(float maxDistance);
		void set_rolloff_factor(float rolloffFactor);
		void set_reference_distance(float referenceDistance);

		void set_pitch(float pitch);

		void assign_source(ALuint src);
		ALuint release_source();

		void set_play_cursor(float seconds);

		void start_fade(bool fDir, float fadeTime, FadeControl actionOnComplete = FC_NONE);

	public:
		inline bool is_playing() const { return m_state == PLAYING; }
		inline bool is_paused() const { return m_state == PAUSED; }
		inline bool is_stopped() const { return m_state == STOPPED; }

	public:
		virtual void open(const string& filename) { UNUSED(filename); }
		virtual void open(SharedBuffer& buffer) { UNUSED(buffer); }

	protected:
		virtual void release() {}

		virtual void fill_buffers() = 0;
		virtual void clear_buffers() = 0;
		virtual void update_buffers() = 0;

		virtual void rewind() = 0;
		virtual void update_play_cursor() = 0;
		virtual ALfloat get_play_cursor() = 0;

	protected:
		void init_source();

		void check_error();

		void update_fade(float fTime);

	public:
		SoundImplementer& m_manager;
		SoundCallback m_callback;

		ALuint m_source = 0;			// OpenAL Source
		Priority m_priority;			// Priority assigned to source
		bool m_active = false;
		bool m_pause_on_disactivate = false;

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

		bool m_source_relative = true;

		vec3 m_position = vec3(0.f);	// 3D position
		vec3 m_direction = vec3(0.f);	// 3D direction
		vec3 m_velocity = vec3(0.f);	// 3D velocity

		float m_max_gain = 1.f;			// Minimum volume
		float m_min_gain = 0.f;			// Maximum volume
		float m_max_distance = 1E10;		// Maximum attenuation distance
		float m_rolloff_factor = 1.f;	// Rolloff factor for attenuation
		float m_reference_distance = 1.f;// Half-volume distance for attenuation

		float m_outer_cone_gain = 0.f;		// Outer cone volume
		float m_inner_cone_angle = 360.f;	// Inner cone angle
		float m_outer_cone_angle = 360.f;	// outer cone angle

		bool m_update_transform = false;	// Transformation update flag
		bool m_update_cursor = false;		// Flag indicating playback position has changed

		vector<float> m_cue_points;	// List of play position points

		struct Fade
		{
			float m_timer = 0.f;
			float m_time = 1.f;
			float m_init_vol = 0.f;
			float m_end_vol = 1.f;
			bool m_fade = false;
			FadeControl m_end_action = FC_NONE;

		} m_fade;

		string m_name;
	};
}
