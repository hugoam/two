//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
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
		, m_actions(QUEUE_LIST_SIZE)
		, m_delayedActions(500)
	{}

	SoundManager::~SoundManager()
	{
		if(m_context == 0)
			return;

		m_shuttingDown = true;
		//mUpdateThread->join();
		//delete m_updateThread;

		releaseAll();

		alcMakeContextCurrent(0);
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
	}

	void SoundManager::clearSources()
	{
		alDeleteSources(m_maxSources, &m_sourcePool[0]);

		m_sourcePool.clear();
	}

	void SoundManager::clearSounds()
	{
		for (SoundList::iterator it = m_active_sounds.begin(); it != m_active_sounds.end(); ++it)
		{
			destroySoundImpl((*it));
		}

		m_pausedSounds.clear();
		m_active_sounds.clear();
		m_inactiveSounds.clear();
	}

	void SoundManager::clearBuffers()
	{
		m_sharedBuffers.clear();
	}

	void SoundManager::releaseAll()
	{
		stopAllSoundsImpl();
		clearSounds();
		clearBuffers();
		clearSources();
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

		m_maxSources = createSourcePool(max_sources);

		//m_update_thread = make_unique<std::thread>([=] { this->threadUpdate(); });

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
				m_sourcePool.push_back(source);
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

		std::ifstream ifile(path, std::ifstream::out);
		if(!ifile.good())
		{
			printf("ERROR: Could not open sound file %s\n", path.c_str());
			return nullptr;
		}

		Sound* sound = nullptr;
		if(stream)
			sound = new/*sound*/StreamSound(*this, callback);
		else
			sound = new/*sound*/StaticSound(*this, callback);

		sound->setLoop(loop);

		this->addAction([=] { this->createSoundImpl(sound, path.c_str(), stream); });

		return sound;
	}

	void SoundManager::createSoundImpl(Sound* sound, cstring filename, bool stream)
	{
		//std::cerr << "creating sound Impl : " << filename << std::endl;
		m_inactiveSounds.push_back(sound);

		if(!stream)
			sound->openShared(getSharedBuffer(filename));
		else
			sound->open(filename);
		//std::cerr << "done" << std::endl;
	}

	void SoundManager::stopAllSounds()
	{
		addAction(std::bind(&SoundManager::stopAllSoundsImpl, this));
	}

	void SoundManager::setGlobalPitch(float pitch)
	{
		m_globalPitch = pitch;

		addAction(std::bind(&SoundManager::setGlobalPitchImpl, this));
	}

	void SoundManager::pauseAllSounds()
	{
		addAction(std::bind(&SoundManager::pauseAllSoundsImpl, this));
	}

	void SoundManager::resumeAllSounds()
	{
		addAction(std::bind(&SoundManager::resumeAllSoundsImpl, this));
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

	void SoundManager::destroySound(Sound* sound)
	{
		addAction(std::bind(&SoundManager::destroySoundImpl, this, sound));
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

	void SoundManager::updateActiveSound(Sound* sound)
	{
		releaseActiveSound(sound);
		queueActiveSound(sound);
	}

	void SoundManager::queueActiveSound(Sound* sound)
	{
		unsigned int index = 0;
		SoundList::iterator pos = m_active_sounds.begin();

		while(pos != m_active_sounds.end() && (*pos)->m_priority < sound->m_priority) { ++index; ++pos; }

		if(m_active_sounds.size() < m_maxSources)
		{
			sound->assignSource(vector_pop(m_sourcePool));
		}
		else if(index <= m_maxSources)
		{
			sound->assignSource((*m_lastActive)->m_source);
			(*m_lastActive)->releaseSource();
			--m_lastActive;
		}

		m_active_sounds.insert(pos, sound);

		sound->m_priority.m_queueIndex = index;
		sound->m_priority.m_queueIterator = pos;
	}

	void SoundManager::activateSound(Sound* sound)
	{
		queueActiveSound(sound);
		m_inactiveSounds.remove(sound);
	}

	void SoundManager::releaseActiveSound(Sound* sound)
	{
		//int lastIndex = sound->getPriority().m_queueIndex;
		//SoundList::iterator lastPos = sound->getPriority().m_queueIterator;

		if(m_active_sounds.size() <= m_maxSources)
		{
			m_sourcePool.push_back(sound->m_source);
			sound->releaseSource();
		}
		else
		{
			++m_lastActive;
			(*m_lastActive)->assignSource(sound->m_source);
			sound->releaseSource();
		}

		m_active_sounds.remove(sound);
	}

	void SoundManager::disactivateSound(Sound* sound)
	{
		releaseActiveSound(sound);
		m_inactiveSounds.push_back(sound);
	}

	void SoundManager::updatePosition(Sound* sound, const vec3& position)
	{
		sound->m_priority.m_distance = distance(position, m_listener.m_position);
		m_updateQueue.push_back(sound);
	}

	void SoundManager::destroySoundImpl(Sound* sound)
	{
		//std::cerr << "destroying sound " << std::endl;
		if(sound->m_active)
			releaseActiveSound(sound);
		else
			m_inactiveSounds.remove(sound);

		if(sound->isPaused())
			m_pausedSounds.remove(sound);

		delete sound;
	}

	void SoundManager::playSound(Sound* sound)
	{
		addAction([=] { this->playSoundImpl(sound); });
	}

	void SoundManager::pauseSound(Sound* sound)
	{
		addAction([=] { this->pauseSoundImpl(sound); });
	}

	void SoundManager::stopSound(Sound* sound)
	{
		addAction([=] { this->stopSoundImpl(sound); });
	}

	void SoundManager::playSoundImpl(Sound* sound)
	{
		activateSound(sound);
		sound->playImpl();
	}

	void SoundManager::pauseSoundImpl(Sound* sound)
	{
		sound->pauseImpl();
		m_pausedSounds.push_back(sound);
		disactivateSound(sound);
	}

	void SoundManager::stopSoundImpl(Sound* sound)
	{
		sound->stopImpl();
		disactivateSound(sound);

		if(sound->m_temporary)
			destroySound(sound);
	}

	void SoundManager::stopAllSoundsImpl()
	{
		SoundList activeSounds(m_active_sounds.begin(), m_active_sounds.end());

		for(Sound* sound : activeSounds)
			stopSoundImpl(sound);
	}

	void SoundManager::pauseAllSoundsImpl()
	{
		SoundList activeSounds(m_active_sounds.begin(), m_active_sounds.end());

		for(Sound* sound : activeSounds)
			pauseSoundImpl(sound);
	}

	void SoundManager::resumeAllSoundsImpl()
	{
		SoundList pausedSounds(m_pausedSounds.begin(), m_pausedSounds.end());

		for(Sound* sound : pausedSounds)
			playSoundImpl(sound);
	}

	void SoundManager::setGlobalPitchImpl()
	{
		for(Sound* sound : m_active_sounds)
			sound->setPitch(m_globalPitch);
	}

	SharedBuffer& SoundManager::createSharedBuffer(cstring filename)
	{
		m_sharedBuffers[filename] = make_unique<SharedBuffer>(filename, [=](SharedBuffer& buffer) { this->releaseBuffer(buffer); });
		return *m_sharedBuffers[filename];
	}

	SharedBuffer& SoundManager::getSharedBuffer(cstring filename)
	{
		auto find = m_sharedBuffers.find(filename);
		if(find != m_sharedBuffers.end())
			return *(*find).second;
		else
			return createSharedBuffer(filename);
	}

	void SoundManager::releaseBuffer(SharedBuffer& buffer)
	{
		m_sharedBuffers.erase(m_sharedBuffers.find(buffer.m_file_buffer->m_filename));
	}

	void SoundManager::addAction(const SoundAction& action)
	{
		if(!m_actions.push(action))
			m_delayedActions.push(action);
	}

	void SoundManager::processActions()
	{
		int i = 0;
		std::function<void ()> action;

		if(!m_actions.empty())
			while(((++i) < 5) && m_actions.pop(action))
				action();

		if(!m_delayedActions.empty())
			while(((++i) < 5) && m_delayedActions.pop(action))
				action();
	}

	void SoundManager::updateSounds()
	{
		double time_step = m_clock.read();
		
		//while(openal_check_error());

		m_listener.update();
		
		for(Sound* sound : m_active_sounds)
			sound->update(float(time_step));

		m_clock.update();
	}

	void SoundManager::threadUpdate()
	{
		if(!m_device)
			return;

		//std::cerr << "SoundManager::next_frame" << std::endl;
		//while(!m_shuttingDown)
		//{
			updateSounds();
			processActions();
			//std::this_thread::sleep(std::posix_time::milliseconds(10));
		//}
		//std::cerr << "SoundManager::next_frame" << std::endl;
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
