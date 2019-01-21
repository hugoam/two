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

		this->release_all();

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
			this->release_active(*sound);

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
		this->stop_all();
		this->clear_sounds();
		this->clear_buffers();
		this->clear_sources();
	}

	bool SoundManager::init(cstring device_name, unsigned int max_sources)
	{
		printf("INFO: Init Sound Manager\n");

		if (m_device)
			return true;

		alGetError();

		this->enum_devices();

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

		this->log_features();

		m_max_sources = create_source_pool(max_sources);

		//m_update_thread = std::make_unique<std::thread>([=] { this->update(); });

		return true;
	}

	int SoundManager::create_source_pool(int max_sources)
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

	void SoundManager::enum_devices()
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

	void SoundManager::set_master_volume(ALfloat vol)
	{
		m_volume = vol;
		alListenerf(AL_GAIN, vol);
	}

	Sound* SoundManager::create_sound(cstring filename, bool loop, bool stream, SoundCallback callback)
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
		this->add_action([&, sound = move(sound)]() mutable { this->create(move(sound), path.c_str(), stream); });
#else
		this->create(move(sound), path.c_str(), stream);
#endif
		return &result;
	}

	void SoundManager::create(unique<Sound> sound, cstring filename, bool stream)
	{
		//std::cerr << "creating sound Impl : " << filename << std::endl;
		m_inactive_sounds.push_back(&*sound);

		if(!stream)
			sound->open_shared(get_buffer(filename));
		else
			sound->open(filename);

		m_sounds.push_back(move(sound));

		//std::cerr << "done" << std::endl;
	}

	void SoundManager::stop_all_sounds()
	{
		this->add_action([&]() { this->stop_all(); });
	}

	void SoundManager::set_global_pitch(float pitch)
	{
		m_global_pitch = pitch;

		this->add_action([&]() { this->set_pitch(); });
	}

	void SoundManager::pause_all_sounds()
	{
		this->add_action([&]() { this->pause_all(); });
	}

	void SoundManager::resume_all_sounds()
	{
		this->add_action([&]() { this->resume_all(); });
	}

	void SoundManager::mute_all_sounds()
	{
		alGetListenerf(AL_GAIN, &m_volume);
		alListenerf(AL_GAIN, 0.f);
	}

	void SoundManager::unmute_all_sounds()
	{
		alListenerf(AL_GAIN, m_volume);
	}

	void SoundManager::destroy_sound(Sound& sound)
	{
		add_action([&]() { this->destroy(sound); });
	}

	void SoundManager::set_distance_model(ALenum value)
	{
		alDistanceModel(value);
	}

	void SoundManager::set_speed_of_sound(float speed)
	{
		alSpeedOfSound(speed);
	}

	void SoundManager::set_doppler_factor(float factor)
	{
		alDopplerFactor(factor);
	}

	void SoundManager::update_active(Sound& sound)
	{
		this->release_active(sound);
		this->queue_active(sound);
	}

	void SoundManager::queue_active(Sound& sound)
	{
		size_t index = 0;
		while(index != m_active_sounds.size() && m_active_sounds[index]->m_priority < sound.m_priority) { ++index; }

		if(m_active_sounds.size() < m_max_sources)
		{
			sound.assign_source(vector_pop(m_source_pool));
		}
		else if(index <= m_max_sources)
		{
			Sound& release = *m_active_sounds[m_max_sources-1];
			sound.assign_source(release.release_source());
		}

		m_active_sounds.insert(m_active_sounds.begin() + index, &sound);
	}

	void SoundManager::activate(Sound& sound)
	{
		this->queue_active(sound);
		vector_remove(m_inactive_sounds, &sound);
	}

	void SoundManager::release_active(Sound& sound)
	{
		if(m_sounds.size() <= m_max_sources)
		{
			m_source_pool.push_back(sound.release_source());
		}
		else
		{
			Sound& assign = *m_active_sounds[m_max_sources-1];
			assign.assign_source(sound.release_source());
		}
	}

	void SoundManager::disactivate(Sound& sound)
	{
		this->release_active(sound);
		m_inactive_sounds.push_back(&sound);
	}

	void SoundManager::update_position(Sound& sound, const vec3& position)
	{
		sound.m_priority.m_distance = distance(position, m_listener.m_position);
		m_update_queue.push_back(&sound);
	}

	void SoundManager::destroy(Sound& sound)
	{
		//std::cerr << "destroying sound " << std::endl;
		if(sound.m_active)
			this->release_active(sound);
		else
			vector_remove(m_inactive_sounds, &sound);

		if(sound.is_paused())
			vector_remove(m_paused_sounds, &sound);
	}

	void SoundManager::play_sound(Sound& sound)
	{
		this->add_action([&] { this->play(sound); });
	}

	void SoundManager::pause_sound(Sound& sound)
	{
		this->add_action([&] { this->pause(sound); });
	}

	void SoundManager::stop_sound(Sound& sound)
	{
		this->add_action([&] { this->stop(sound); });
	}

	void SoundManager::play(Sound& sound)
	{
		this->activate(sound);
		sound.play_impl();
	}

	void SoundManager::pause(Sound& sound)
	{
		sound.pause_impl();
		m_paused_sounds.push_back(&sound);
		this->disactivate(sound);
	}

	void SoundManager::stop(Sound& sound)
	{
		sound.stop_impl();
		this->disactivate(sound);

		if(sound.m_temporary)
			this->destroy_sound(sound);
	}

	void SoundManager::stop_all()
	{
		for(Sound* sound : m_active_sounds)
			this->stop(*sound);
	}

	void SoundManager::pause_all()
	{
		for(Sound* sound : m_active_sounds)
			this->pause(*sound);
	}

	void SoundManager::resume_all()
	{
		for(Sound* sound : m_paused_sounds)
			this->play(*sound);
	}

	void SoundManager::set_pitch()
	{
		for(auto& sound : m_sounds)
			sound->set_pitch(m_global_pitch);
	}

	SharedBuffer& SoundManager::create_buffer(cstring filename)
	{
		m_shared_buffers[filename] = make_unique<SharedBuffer>(filename, *this);
		return *m_shared_buffers[filename];
	}

	SharedBuffer& SoundManager::get_buffer(cstring filename)
	{
		auto find = m_shared_buffers.find(filename);
		if(find != m_shared_buffers.end())
			return *(*find).second;
		else
			return this->create_buffer(filename);
	}

	void SoundManager::release_buffer(SharedBuffer& buffer)
	{
		m_shared_buffers.erase(m_shared_buffers.find(buffer.m_file_buffer->m_filename));
	}

	void SoundManager::add_action(const SoundAction& action)
	{
#ifndef SOUND_THREADED
		action();
#else
		if(!m_actions.push(action))
			m_delayed_actions.push(action);
#endif
	}

#ifdef SOUND_THREADED
	void SoundManager::process_actions()
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

	void SoundManager::update_sounds()
	{
		double time_step = m_clock.read();
		
		//while(openal_check_error());

		m_listener.update();
		
		for(auto& sound : m_sounds)
			sound->update(float(time_step));

		m_clock.update();
	}

	void SoundManager::update()
	{
		if(!m_device)
			return;

		//while(!m_shutting_down)
		//{
			this->update_sounds();
#ifdef SOUND_THREADED
			this->process_actions();
#endif
			//std::this_thread::sleep(std::posix_time::milliseconds(10));
		//}
	}

	void SoundManager::log_features()
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
