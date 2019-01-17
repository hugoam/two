//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/string.h>
#include <stl/vector.h>
#include <stl/map.h>
#include <infra/NonCopy.h>
#include <type/Unique.h>
#include <type/Util/LocklessQueue.h>
#include <math/Timer.h>
#include <math/Vec.h>
#include <snd/Forward.h>
#include <snd/SoundImplementer.h>
#include <snd/SoundListener.h>
#include <snd/Sound.h>

#include <functional>
#include <list>
//#include <thread>
//#include <memory>

namespace mud
{
	using SoundCallback = void(*)(Sound&);

	bool openal_check_error();

	class MUD_SND_EXPORT SoundManager : public NonCopy, public SoundImplementer
	{
	public:
		using SoundAction = std::function<void()>;
		using SoundList = std::list<Sound*>;
		using SoundVector = vector<Sound*>;
		using SourceVector = vector<ALuint>;

		// Thread-safe interface
	public:
		SoundManager(cstring resourcePath = "");
		~SoundManager();

		bool init(cstring deviceName = "", unsigned int maxSources = 100);

		Sound* createSound(cstring file, bool loop = false, bool stream = false, SoundCallback callback = {});

	public:
		void setMasterVolume(ALfloat vol);
		void setGlobalPitch(float pitch);

		void setDistanceModel(ALenum value);
		void setDopplerFactor(float factor = 1.f);
		void setSpeedOfSound(float speed = 363.f);

	public:
		void playSound(Sound* sound);
		void stopSound(Sound* sound);
		void pauseSound(Sound* sound);
		void destroySound(Sound* sound);

		void updatePosition(Sound* sound, const vec3& position);

		void stopAllSounds();
		void pauseAllSounds();
		void muteAllSounds();
		void unmuteAllSounds();
		void resumeAllSounds();

	private:
		void enumDevices();
		int createSourcePool(int numSources);

		void clearSounds();
		void clearSources();
		void clearBuffers();
		void releaseAll();

	// Thread-safe implementation to be executed by one same unique thread
	public:
		void threadUpdate();

		void createSoundImpl(Sound* sound, cstring filename, bool stream);
		void destroySoundImpl(Sound* sound);

		void playSoundImpl(Sound* sound);
		void stopSoundImpl(Sound* sound);
		void pauseSoundImpl(Sound* sound);

		void setGlobalPitchImpl();

		void stopAllSoundsImpl();
		void pauseAllSoundsImpl();
		void resumeAllSoundsImpl();

	private:
		void updateActiveSound(Sound* sound);
		void releaseActiveSound(Sound* sound);
		void queueActiveSound(Sound* sound);
		
		void activateSound(Sound* sound);
		void disactivateSound(Sound* sound);

		SharedBuffer& createSharedBuffer(cstring filename);
		SharedBuffer& getSharedBuffer(cstring filename);
	public:
		void releaseBuffer(SharedBuffer& buffer);
	private:
		void logFeatureSupport();

	private:
		void addAction(const SoundAction& action);

		void processActions();
		void updateSounds();

	private:
		string m_resource_path;

		LocklessQueue<SoundAction> m_actions;
		LocklessQueue<SoundAction> m_delayedActions;

		//std::unique_ptr<std::thread> m_update_thread = nullptr;
		bool m_shuttingDown = false;

	public:
		vector<string> m_devices;			// List of available devices strings
		ALCdevice* m_device = nullptr;			// OpenAL device
		ALCcontext* m_context = nullptr;		// OpenAL context

		ALfloat	m_volume = 1.f;					// Main Volume
		float m_globalPitch = 1.f;				// Global pitch modifier
		SoundListener m_listener;				// Listener object

	private:
		/** Sounds **/
		SoundList m_active_sounds;				// list of all sounds : m_active_sounds.begin() to m_active_sounds[m_maxSources] are active
		SoundList m_inactiveSounds;
		SoundList m_pausedSounds;				// list of sounds currently paused

		SoundList::iterator m_lastActive;
		SoundVector m_updateQueue;

		unsigned int m_maxSources = 100;		// Maximum Number of sources to allocate
		SourceVector m_sourcePool;				// List of available sources

		map<string, unique<SharedBuffer>> m_sharedBuffers;

		Clock m_clock;
	};
}
