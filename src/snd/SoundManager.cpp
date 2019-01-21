//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <snd/SoundManager.h>

#include <infra/Vector.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <snd/StaticSound.h>
#include <snd/StreamSound.h>
#include <snd/SharedBuffer.h>
#include <snd/SoundListener.h>

#include <snd/SoundManager.h>

#include <iostream>
#include <fstream>

namespace mud
{
#define QUEUE_LIST_SIZE 64

	bool openal_check_error()
	{
		ALenum error = alGetError();
		if(error == AL_NO_ERROR)				return false;
		else if(error == AL_INVALID_NAME)		printf("ERROR: OpenAL - AL_INVALID_NAME\n");
		else if(error == AL_ILLEGAL_ENUM)		printf("ERROR: OpenAL - AL_ILLEGAL_ENUM\n");
		else if(error == AL_INVALID_ENUM)		printf("ERROR: OpenAL - AL_INVALID_ENUM\n");
		else if(error == AL_INVALID_VALUE)		printf("ERROR: OpenAL - AL_INVALID_VALUE\n");
		else if(error == AL_ILLEGAL_COMMAND)	printf("ERROR: OpenAL - AL_ILLEGAL_COMMAND\n");
		else if(error == AL_INVALID_OPERATION)	printf("ERROR: OpenAL - AL_INVALID_OPERATION\n");
		else if(error == AL_OUT_OF_MEMORY)		printf("ERROR: OpenAL - AL_OUT_OF_MEMORY\n");
		else									printf("ERROR: OpenAL - %i\n", int(error));
		return true;
	}

	bool openalc_check_error(ALCdevice* device)
	{
		bool errors = false;
		while(ALCenum error = alcGetError(device) != ALC_NO_ERROR)
		{
			if(error == ALC_INVALID_DEVICE)			printf("ERROR: OpenALC - ALC_INVALID_DEVICE\n");
			else if(error == ALC_INVALID_CONTEXT)	printf("ERROR: OpenALC - ALC_INVALID_CONTEXT\n");
			else if(error == ALC_INVALID_ENUM)		printf("ERROR: OpenALC - ALC_INVALID_ENUM\n");
			else if(error == ALC_INVALID_VALUE)		printf("ERROR: OpenALC - ALC_INVALID_VALUE\n");
			else if(error == ALC_OUT_OF_MEMORY)		printf("ERROR: OpenALC - ALC_OUT_OF_MEMORY\n");
			errors = true;
		}
		return errors;
	}

	SoundManager::SoundManager(cstring resource_path)
		: m_resource_path(resource_path)
#ifdef SOUND_THREADED
		, m_actions(QUEUE_LIST_SIZE)
		, m_delayed_actions(500)
#endif
	{}

	SoundManager::~SoundManager()
	{
		if(m_context == 0)
			return;

		m_shutting_down = true;
#ifdef SOUND_THREADED
		//mUpdateThread->join();
		//delete m_updateThread;
#endif

		release_all();

		alcMakeContextCurrent(0);
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
	}

	void SoundManager::clear_sources()
	{
		alDeleteSources(m_max_sources, &m_source_pool[0]);
		m_source_pool.clear();
	}

	void SoundManager::clear_sounds()
	{
		for(auto& sound : m_sounds)
			this->releaseActiveSound(*sound);

		m_sounds.clear();
		m_paused_sounds.clear();
		m_inactive_sounds.clear();
	}

	void SoundManager::clear_buffers()
	{
		m_shared_buffers.clear();
	}

	void SoundManager::release_all()
	{
		stopAllSoundsImpl();
		clear_sounds();
		clear_buffers();
		clear_sources();
	}

	bool SoundManager::init(cstring device_name, unsigned int max_sources)
	{
		printf("INFO: Init Sound Manager\n");

		if (m_device)
			return true;

		alGetError();

		enumDevices();

		string name = device_name;
		if(!name.empty() && std::find(m_devices.begin(), m_devices.end(), name) != m_devices.end())
			m_device = alcOpenDevice(name.c_str());
		else if(m_devices.size() > 0)
			m_device = alcOpenDevice(m_devices.front().c_str());
		else
			m_device = alcOpenDevice(NULL);

		if(!m_device)
			return false;
		
		ALCint attributes[] = { 0 };

		m_context = alcCreateContext(m_device, attributes);
		if(!m_context)
			return false;

		if (!alcMakeContextCurrent(m_context))
			return false;

		this->logFeatureSupport();

		m_max_sources = createSourcePool(max_sources);

		//m_update_thread = std::make_unique<std::thread>([=] { this->threadUpdate(); });

		return true;
	}

	int SoundManager::createSourcePool(int max_sources)
	{
		ALuint source;
		int num_sources = 0;

		while(!openal_check_error() && num_sources < max_sources)
		{
			source = 0;
			alGenSources(1,&source);
			if(source != 0)
			{
				m_source_pool.push_back(source);
				num_sources++;
			}
			else
			{
				openal_check_error();
				break;
			}
		}

		printf("INFO: Sound - added %i source\n", num_sources);
		return num_sources;
	}

	void SoundManager::enumDevices()
	{
		const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

		// devices is a list separated by null characters and a double null at the end
		while(*devices != 0)
		{
			ALCdevice* device = alcOpenDevice(devices);
			if(openalc_check_error(device))
				continue;

			ALCcontext* context = alcCreateContext(device, NULL);
			if(openalc_check_error(device))
				continue;

			alcMakeContextCurrent(context);
			if(openalc_check_error(device))
				continue;

			m_devices.push_back(alcGetString(device, ALC_DEVICE_SPECIFIER));

			alcMakeContextCurrent(NULL);
			alcDestroyContext(context);

			alcCloseDevice(device);

			devices += strlen(devices) + 1;
		}
	}

	void SoundManager::setMasterVolume(ALfloat vol)
	{
		m_volume = vol;
		alListenerf(AL_GAIN, vol);
	}

	Sound* SoundManager::createSound(cstring filename, bool loop, bool stream, SoundCallback callback)
	{
		string path = filename; //m_resource_path + "sounds/" + filename;

		std::ifstream ifile(path.c_str(), std::ifstream::out);
		if(!ifile.good())
		{
			printf("ERROR: Could not open sound file %s\n", path.c_str());
			return nullptr;
		}

		unique<Sound> sound;
		if(stream)
			sound = construct<StreamSound>(*this, callback);
		else
			sound = construct<StaticSound>(*this, callback);

		sound->set_loop(loop);

		Sound& result = *sound;
#ifdef SOUND_THREADED
		this->addAction([&, sound = move(sound)]() mutable { this->createSoundImpl(move(sound), path.c_str(), stream); });
#else
		this->createSoundImpl(move(sound), path.c_str(), stream);
#endif
		return &result;
	}

	void SoundManager::createSoundImpl(unique<Sound> sound, cstring filename, bool stream)
	{
		//std::cerr << "creating sound Impl : " << filename << std::endl;
		m_inactive_sounds.push_back(&*sound);

		if(!stream)
			sound->open_shared(getSharedBuffer(filename));
		else
			sound->open(filename);

		m_sounds.push_back(move(sound));

		//std::cerr << "done" << std::endl;
	}

	void SoundManager::stopAllSounds()
	{
		addAction([&]() { this->stopAllSoundsImpl(); });
	}

	void SoundManager::setGlobalPitch(float pitch)
	{
		m_global_pitch = pitch;

		addAction([&]() { this->setGlobalPitchImpl(); });
	}

	void SoundManager::pauseAllSounds()
	{
		addAction([&]() { this->pauseAllSoundsImpl(); });
	}

	void SoundManager::resumeAllSounds()
	{
		addAction([&]() { this->resumeAllSoundsImpl(); });
	}

	void SoundManager::muteAllSounds()
	{
		alGetListenerf(AL_GAIN, &m_volume);
		alListenerf(AL_GAIN, 0.f);
	}

	void SoundManager::unmuteAllSounds()
	{
		alListenerf(AL_GAIN, m_volume);
	}

	void SoundManager::destroySound(Sound& sound)
	{
		addAction([&]() { this->destroySoundImpl(sound); });
	}

	void SoundManager::setDistanceModel(ALenum value)
	{
		alDistanceModel(value);
	}

	void SoundManager::setSpeedOfSound(float speed)
	{
		alSpeedOfSound(speed);
	}

	void SoundManager::setDopplerFactor(float factor)
	{
		alDopplerFactor(factor);
	}

	void SoundManager::updateActiveSound(Sound& sound)
	{
		releaseActiveSound(sound);
		queueActiveSound(sound);
	}

	void SoundManager::queueActiveSound(Sound& sound)
	{
		size_t index = 0;
		while(index != m_active_sounds.size() && m_active_sounds[index]->m_priority < sound.m_priority) { ++index; }

		if(m_active_sounds.size() < m_max_sources)
		{
			sound.assign_source(vector_pop(m_source_pool));
		}
		else if(index <= m_max_sources)
		{
			Sound& release = *m_active_sounds[m_max_sources];
			sound.assign_source(release.release_source());
		}

		m_active_sounds.insert(m_active_sounds.begin() + index, &sound);
	}

	void SoundManager::activateSound(Sound& sound)
	{
		queueActiveSound(sound);
		vector_remove(m_inactive_sounds, &sound);
	}

	void SoundManager::releaseActiveSound(Sound& sound)
	{
		if(m_sounds.size() <= m_max_sources)
		{
			m_source_pool.push_back(sound.release_source());
		}
		else
		{
			Sound& assign = *m_active_sounds[m_max_sources];
			assign.assign_source(sound.release_source());
		}
	}

	void SoundManager::disactivateSound(Sound& sound)
	{
		releaseActiveSound(sound);
		m_inactive_sounds.push_back(&sound);
	}

	void SoundManager::updatePosition(Sound& sound, const vec3& position)
	{
		sound.m_priority.m_distance = distance(position, m_listener.m_position);
		m_update_queue.push_back(&sound);
	}

	void SoundManager::destroySoundImpl(Sound& sound)
	{
		//std::cerr << "destroying sound " << std::endl;
		if(sound.m_active)
			releaseActiveSound(sound);
		else
			vector_remove(m_inactive_sounds, &sound);

		if(sound.is_paused())
			vector_remove(m_paused_sounds, &sound);
	}

	void SoundManager::playSound(Sound& sound)
	{
		addAction([&] { this->playSoundImpl(sound); });
	}

	void SoundManager::pauseSound(Sound& sound)
	{
		addAction([&] { this->pauseSoundImpl(sound); });
	}

	void SoundManager::stopSound(Sound& sound)
	{
		addAction([&] { this->stopSoundImpl(sound); });
	}

	void SoundManager::playSoundImpl(Sound& sound)
	{
		activateSound(sound);
		sound.play_impl();
	}

	void SoundManager::pauseSoundImpl(Sound& sound)
	{
		sound.pause_impl();
		m_paused_sounds.push_back(&sound);
		disactivateSound(sound);
	}

	void SoundManager::stopSoundImpl(Sound& sound)
	{
		sound.stop_impl();
		disactivateSound(sound);

		if(sound.m_temporary)
			destroySound(sound);
	}

	void SoundManager::stopAllSoundsImpl()
	{
		for(Sound* sound : m_active_sounds)
			stopSoundImpl(*sound);
	}

	void SoundManager::pauseAllSoundsImpl()
	{
		for(Sound* sound : m_active_sounds)
			pauseSoundImpl(*sound);
	}

	void SoundManager::resumeAllSoundsImpl()
	{
		for(Sound* sound : m_paused_sounds)
			playSoundImpl(*sound);
	}

	void SoundManager::setGlobalPitchImpl()
	{
		for(auto& sound : m_sounds)
			sound->set_pitch(m_global_pitch);
	}

	SharedBuffer& SoundManager::createSharedBuffer(cstring filename)
	{
		m_shared_buffers[filename] = make_unique<SharedBuffer>(filename, *this);
		return *m_shared_buffers[filename];
	}

	SharedBuffer& SoundManager::getSharedBuffer(cstring filename)
	{
		auto find = m_shared_buffers.find(filename);
		if(find != m_shared_buffers.end())
			return *(*find).second;
		else
			return createSharedBuffer(filename);
	}

	void SoundManager::releaseBuffer(SharedBuffer& buffer)
	{
		m_shared_buffers.erase(m_shared_buffers.find(buffer.m_file_buffer->m_filename));
	}

	void SoundManager::addAction(const SoundAction& action)
	{
#ifndef SOUND_THREADED
		action();
#else
		if(!m_actions.push(action))
			m_delayed_actions.push(action);
#endif
	}

#ifdef SOUND_THREADED
	void SoundManager::processActions()
	{
		int i = 0;
		function<void ()> action;

		if(!m_actions.empty())
			while(((++i) < 5) && m_actions.pop(action))
				action();

		if(!m_delayed_actions.empty())
			while(((++i) < 5) && m_delayed_actions.pop(action))
				action();
	}
#endif

	void SoundManager::updateSounds()
	{
		double time_step = m_clock.read();
		
		//while(openal_check_error());

		m_listener.update();
		
		for(auto& sound : m_sounds)
			sound->update(float(time_step));

		m_clock.update();
	}

	void SoundManager::threadUpdate()
	{
		if(!m_device)
			return;

		//while(!m_shutting_down)
		//{
			updateSounds();
#ifdef SOUND_THREADED
			processActions();
#endif
			//std::this_thread::sleep(std::posix_time::milliseconds(10));
		//}
	}

	void SoundManager::logFeatureSupport()
	{
		printf("INFO: Supported sound formats\n");

		if(alcGetEnumValue(m_device, "AL_FORMAT_MONO16"))
			printf("    - AL_FORMAT_MONO16 -- Monophonic Sound\n");
		if(alcGetEnumValue(m_device, "AL_FORMAT_STEREO16"))
			printf("    - AL_FORMAT_STEREO16 -- Stereo Sound\n");
		if(alcGetEnumValue(m_device, "AL_FORMAT_QUAD16"))
			printf("    - AL_FORMAT_QUAD16 -- 4 Channel Sound\n");
		if(alcGetEnumValue(m_device, "AL_FORMAT_51CHN16"))
			printf("    - AL_FORMAT_51CHN16 -- 5.1 Surround Sound\n");
		if(alcGetEnumValue(m_device, "AL_FORMAT_61CHN16"))
			printf("    - AL_FORMAT_61CHN16 -- 6.1 Surround Sound\n");
		if(alcGetEnumValue(m_device, "AL_FORMAT_71CHN16"))
			printf("    - AL_FORMAT_71CHN16 -- 7.1 Surround Sound");
	}
}
