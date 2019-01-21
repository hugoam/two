//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/function.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/memory.h>
#include <stl/map.h>
#include <infra/NonCopy.h>
#include <type/Unique.h>
#include <math/Timer.h>
#include <math/Vec.h>
#include <snd/Forward.h>
#include <snd/SoundImplementer.h>
#include <snd/SoundListener.h>
#include <snd/Sound.h>

#ifdef SOUND_THREADED
#include <type/Util/LocklessQueue.h>
//#include <thread>
//#include <memory>
#endif

namespace mud
{
	using SoundCallback = void(*)(Sound&);

	bool openal_check_error();

	class MUD_SND_EXPORT SoundManager : public NonCopy, public SoundImplementer
	{
	public:
		using SoundAction = function<void()>;
		using SourceVector = vector<ALuint>;

		// Thread-safe interface
	public:
		SoundManager(cstring resourcePath = "");
		~SoundManager();

		bool init(cstring deviceName = "", unsigned int maxSources = 100);

		Sound* create_sound(cstring file, bool loop = false, bool stream = false, SoundCallback callback = {});

	public:
		void set_master_volume(ALfloat vol);
		void set_global_pitch(float pitch);

		void set_distance_model(ALenum value);
		void set_doppler_factor(float factor = 1.f);
		void set_speed_of_sound(float speed = 363.f);

	public:
		void play_sound(Sound& sound);
		void stop_sound(Sound& sound);
		void pause_sound(Sound& sound);
		void destroy_sound(Sound& sound);

		void update_position(Sound& sound, const vec3& position);

		void stop_all_sounds();
		void pause_all_sounds();
		void mute_all_sounds();
		void unmute_all_sounds();
		void resume_all_sounds();

	private:
		void enum_devices();
		int create_source_pool(int numSources);

		void clear_sounds();
		void clear_sources();
		void clear_buffers();
		void release_all();

	// Thread-safe implementation to be executed by one same unique thread
	public:
		void update();

		void create(unique<Sound> sound, cstring filename, bool stream);
		void destroy(Sound& sound);

		void play(Sound& sound);
		void stop(Sound& sound);
		void pause(Sound& sound);

		void set_pitch();

		void stop_all();
		void pause_all();
		void resume_all();

	private:
		void update_active(Sound& sound);
		void release_active(Sound& sound);
		void queue_active(Sound& sound);
		
		void activate(Sound& sound);
		void disactivate(Sound& sound);

		void log_features();

	public:
		SharedBuffer& create_buffer(cstring filename);
		SharedBuffer& get_buffer(cstring filename);
		void release_buffer(SharedBuffer& buffer);

	private:
		void add_action(const SoundAction& action);

		void update_sounds();

#ifdef SOUND_THREADED
		void process_actions();
#endif
	private:
		string m_resource_path;

#ifdef SOUND_THREADED
		//std::unique_ptr<std::thread> m_update_thread = nullptr;

		LocklessQueue<SoundAction> m_actions;
		LocklessQueue<SoundAction> m_delayed_actions;
#endif

		bool m_shutting_down = false;

	public:
		vector<string> m_devices;			// List of available devices strings
		ALCdevice* m_device = nullptr;			// OpenAL device
		ALCcontext* m_context = nullptr;		// OpenAL context

		ALfloat	m_volume = 1.f;					// Main Volume
		float m_global_pitch = 1.f;				// Global pitch modifier
		SoundListener m_listener;				// Listener object

	private:
		vector<unique<Sound>> m_sounds;			// list of all sounds : m_sounds.begin() to m_sounds[m_max_sources] are active
		vector<Sound*> m_active_sounds;
		vector<Sound*> m_inactive_sounds;
		vector<Sound*> m_paused_sounds;				// list of sounds currently paused

		vector<Sound*> m_update_queue;

		unsigned int m_max_sources = 100;		// Maximum Number of sources to allocate
		SourceVector m_source_pool;				// List of available sources

		map<string, unique<SharedBuffer>> m_shared_buffers;

		Clock m_clock;
	};
}
