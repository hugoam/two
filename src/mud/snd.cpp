#include <mud/snd.h>
#include <mud/infra.h>
#include <mud/type.h>


#include <iostream>
#include <stl/vector.h>

#include <vorbis/vorbisfile.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace mud
{
	static size_t ogg_read(void* ptr, size_t size, size_t count, void* file)
	{
		return fread(ptr, size, count, (FILE*)file);
	}

	static int ogg_seek(void* file, ogg_int64_t offset, int whence)
	{
		return fseek((FILE*)file, long(offset), whence);
	}

	static int ogg_close(void* file)
	{
		return fclose((FILE*)file);
	}

	static long ogg_tell(void* file)
	{
		return ftell((FILE*)file);
	}

	struct OggFileBuffer::Impl
	{
		OggVorbis_File m_ogg_file;
		vorbis_info* m_vorbis_info = nullptr;
		vorbis_comment* m_vorbis_comment = nullptr;

		ov_callbacks m_ogg_callbacks;
	};

	OggFileBuffer::OggFileBuffer()
		: m_impl(make_unique<Impl>())
	{}

	OggFileBuffer::~OggFileBuffer()
	{}

	void OggFileBuffer::open(const string& filename)
	{
		m_impl->m_ogg_callbacks.read_func = ogg_read;
		m_impl->m_ogg_callbacks.close_func = ogg_close;
		m_impl->m_ogg_callbacks.seek_func = ogg_seek;
		m_impl->m_ogg_callbacks.tell_func = ogg_tell;

		m_filename = filename;

		//FILE* file = fopen(filename, "rb");
		//int result = ov_open_callbacks(file, &m_oggFile, NULL, 0, m_oggCallbacks);

		int result = ov_fopen(filename.c_str(), &m_impl->m_ogg_file);

		if(result < 0)
			return;

		m_impl->m_vorbis_info = ov_info(&m_impl->m_ogg_file, -1);
		m_impl->m_vorbis_comment = ov_comment(&m_impl->m_ogg_file, -1);

		m_duration = static_cast<float>(ov_time_total(&m_impl->m_ogg_file, -1));
		m_seekable = (ov_seekable(&m_impl->m_ogg_file) != 0);

		if (!this->read_buffer_info())
			return;

		m_mono = ((m_format==AL_FORMAT_MONO16) || (m_format==AL_FORMAT_MONO8));
	}

	void OggFileBuffer::close()
	{
		ov_clear(&m_impl->m_ogg_file);
	}

	void OggFileBuffer::reopen()
	{
		close();
		open(m_filename.c_str());
	}

	void OggFileBuffer::seek_time(float time)
	{
		ov_time_seek(&m_impl->m_ogg_file, time);
	}

	void OggFileBuffer::seek_bytes(long pos)
	{
		ov_raw_seek(&m_impl->m_ogg_file, pos);
	}

	void OggFileBuffer::fill(ALuint buffer)
	{
		vector<char> data;
		vector<char> chunk = vector<char>(m_chunk_size);

		int size_read = 1;
		int last_pos = 0;
		int section;

		while(size_read > 0)
		{
			//printf("reading : " << size_read << " at pos : " << last_pos );
			size_read = ov_read(&m_impl->m_ogg_file, chunk.data(), int(m_chunk_size), 0, 2, 1, &section);
			data.insert(data.end(), chunk.begin(), chunk.begin() + size_read);
			last_pos += size_read;
		}

		alGetError();
		alBufferData(buffer, m_format, &data[0], last_pos, m_impl->m_vorbis_info->rate);
	}

	bool OggFileBuffer::fill_chunk(ALuint buffer)
	{
		vector<char> chunk = vector<char>(m_chunk_size);
		
		bool last_chunk = this->read_chunk(chunk.data(), m_chunk_size);

		alBufferData(buffer, m_format, chunk.data(), ALsizei(m_chunk_size), m_impl->m_vorbis_info->rate);
		alGetError();

		return last_chunk;
	}

	bool OggFileBuffer::read_chunk(char* data_chunk, size_t chunk_size)
	{
		UNUSED(chunk_size);
		size_t size = 0;
		int section;
		int result;
		bool last_chunk = true;

		while(size < m_chunk_size)
		{
			result = ov_read(&m_impl->m_ogg_file, data_chunk + size, int(m_chunk_size - size), 0, 2, 1, &section);

			if(result > 0)
				size += result;
			else if(result == 0)
				last_chunk = false;
			else if(result < 0)
				break;
		}

		return last_chunk;
	}


	bool OggFileBuffer::read_buffer_info()
	{
		/** Calculates buffer size and format.
		@remarks
			Calculates a block aligned buffer size of 250ms using
			sound properties.
		 */
		// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...

		switch(m_impl->m_vorbis_info->channels)
		{
		case 1:
				m_format = AL_FORMAT_MONO16;
				// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate >> 1;
				m_chunk_size -= (m_chunk_size % 2);
			break;
		case 2:
				m_format = AL_FORMAT_STEREO16;
				// Set BufferSize to 250ms (Frequency * 4 (16bit stereo) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate;
				m_chunk_size -= (m_chunk_size % 4);
			break;
		case 4:
				m_format = alGetEnumValue("AL_FORMAT_QUAD16");
				if (!m_format) return false;
				// Set BufferSize to 250ms (Frequency * 8 (16bit 4-channel) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate * 2;
				m_chunk_size -= (m_chunk_size % 8);
			break;
		case 6:
				m_format = alGetEnumValue("AL_FORMAT_51CHN16");
				if (!m_format) return false;
				// Set BufferSize to 250ms (Frequency * 12 (16bit 6-channel) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate * 3;
				m_chunk_size -= (m_chunk_size % 12);
			break;
		case 7:
				m_format = alGetEnumValue("AL_FORMAT_61CHN16");
				if (!m_format) return false;
				// Set BufferSize to 250ms (Frequency * 16 (16bit 7-channel) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate * 4;
				m_chunk_size -= (m_chunk_size % 16);
			break;
		case 8:
				m_format = alGetEnumValue("AL_FORMAT_71CHN16");
				if (!m_format) return false;
				// Set BufferSize to 250ms (Frequency * 20 (16bit 8-channel) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate * 5;
				m_chunk_size -= (m_chunk_size % 20);
			break;
		default:
				m_format = AL_FORMAT_MONO16;
				// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate >> 1;
				m_chunk_size -= (m_chunk_size % 2);
			break;
		}
		return true;
	}
}




#include <iostream>

#include <AL/al.h>

namespace mud
{
	SharedBuffer::SharedBuffer(const string& filename, SoundManager& manager)
		: m_al_buffer(AL_NONE)
		, m_manager(&manager)
	{
		if(filename.find(".ogg") != filename.npos || filename.find(".OGG") != filename.npos)
			m_file_buffer = make_unique<OggFileBuffer>();

		alGenBuffers(1, &m_al_buffer);

		m_file_buffer->open(filename.c_str());
		m_file_buffer->fill(m_al_buffer);
	}

	SharedBuffer::~SharedBuffer()
	{
		alDeleteBuffers(1, &m_al_buffer);

		m_file_buffer->close();
	}

	void SharedBuffer::use()
	{
		++m_num_users;
	}

	void SharedBuffer::release()
	{
		--m_num_users;
		if(m_num_users == 0)
			m_manager->release_buffer(*this);
	}
}




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
		m_manager.play_sound(*this);
	}

	void Sound::stop()
	{
		m_manager.stop_sound(*this);
	}
	void Sound::pause()
	{
		m_manager.pause_sound(*this);
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



#include <AL/al.h>
#include <AL/alc.h>

namespace mud
{
	SoundListener::SoundListener()
	{}

	void SoundListener::update()
	{
		if(m_transformUpdated)
		{
			alListener3f(AL_POSITION, m_position.x, m_position.y, m_position.z);
			alListenerfv(AL_ORIENTATION, value_ptr(m_front));

			//alListener3f(AL_VELOCITY, );

			m_transformUpdated = false;
		}     
	}
}




#include <AL/al.h>
#include <AL/alc.h>



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

	SoundManager::SoundManager(const string& resource_path)
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

	bool SoundManager::init(const string& device_name, unsigned int max_sources)
	{
		printf("INFO: Init Sound Manager\n");

		if (m_device)
			return true;

		alGetError();

		this->enum_devices();

		string name = device_name;
		if(!name.empty() && find(m_devices.begin(), m_devices.end(), name) != m_devices.end())
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

	Sound* SoundManager::create_sound(const string& filename, bool loop, bool stream, SoundCallback callback)
	{
		string path = filename; //m_resource_path + "/sounds/" + filename;

		if(!file_exists(path))
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

	void SoundManager::create(unique<Sound> sound, const string& filename, bool stream)
	{
		//printf("creating sound Impl : " << filename );
		m_inactive_sounds.push_back(&*sound);

		if(!stream)
			sound->open(get_buffer(filename));
		else
			sound->open(filename);

		m_sounds.push_back(move(sound));

		//printf("done" );
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
			sound.assign_source(pop(m_source_pool));
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
		//printf("destroying sound " );
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

	SharedBuffer& SoundManager::create_buffer(const string& filename)
	{
		m_shared_buffers[filename] = make_unique<SharedBuffer>(filename, *this);
		return *m_shared_buffers[filename];
	}

	SharedBuffer& SoundManager::get_buffer(const string& filename)
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



#include <iostream>

#include <AL/al.h>

namespace mud
{
	StaticSound::StaticSound(SoundImplementer& manager, SoundCallback callback)
		: Sound(manager, callback)
		, m_buffer(0)
	{
		m_stream = false;
	}

	StaticSound::~StaticSound()
	{}

	void StaticSound::open(SharedBuffer& buffer)
	{
		m_name = buffer.m_file_buffer->m_filename;
		m_buffer = &buffer;
		m_buffer->use();
		m_duration = buffer.m_file_buffer->m_duration;
		m_seekable = buffer.m_file_buffer->m_seekable;
		m_mono = buffer.m_file_buffer->m_mono;
	}

	void StaticSound::release()
	{
		m_buffer->release();
	}

	void StaticSound::update_buffers()
	{}

	void StaticSound::fill_buffers()
	{
		alSourcei(m_source, AL_BUFFER, m_buffer->m_al_buffer);
	}

	void StaticSound::clear_buffers()
	{
		alSourcei(m_source, AL_BUFFER, 0);
	}

	void StaticSound::rewind()
	{
		alSourceRewind(m_source);
	}

	void StaticSound::update_play_cursor()
	{
		alSourcef(m_source, AL_SEC_OFFSET, m_cursor);

		m_update_cursor = false;
	}

	ALfloat StaticSound::get_play_cursor()
	{
		ALfloat cursor;
		alGetSourcef(m_source, AL_SEC_OFFSET, &cursor);
		return cursor;
	}

	void StaticSound::set_loop(bool loop)
	{
		Sound::set_loop(loop);

		if(m_active)
			alSourcei(m_source, AL_LOOPING, loop);
	}
}




#include <AL/al.h>

namespace mud
{
#define NUM_BUFFERS 3

	StreamSound::StreamSound(SoundImplementer& manager, SoundCallback callback)
		: Sound(manager, callback)
		, m_numBuffers(NUM_BUFFERS)
		, m_aLBuffers(m_numBuffers)
		, m_lastOffset(0)
	{
		m_stream = true;
	}

	void StreamSound::open(const string& filename)
	{
		//printf("opening stream sound" );

		for(int i=0; i < m_numBuffers; i++)
		{
			m_aLBuffers[i] = AL_NONE;
		}

		alGenBuffers(m_numBuffers, &m_aLBuffers[0]);

		string name = filename;
		if(name.find(".ogg") != name.npos || name.find(".OGG") != name.npos)
			m_buffer = make_unique<OggFileBuffer>();

		m_buffer->open(filename);
		m_duration = m_buffer->m_duration;
		m_seekable = m_buffer->m_seekable;
		m_mono = m_buffer->m_mono;
	}

	StreamSound::~StreamSound()
	{}

	void StreamSound::setup()
	{

	}

	void StreamSound::release()
	{
		for(int i = 0; i < m_numBuffers; i++)
		{
			if (m_aLBuffers[i] != AL_NONE)
				alDeleteBuffers(1, &m_aLBuffers[i]);
		}
	}

	void StreamSound::rewind()
	{
		if(m_buffer->m_seekable)
		{
			m_buffer->seek_time(0);
			m_cursor = 0;
		}
		else
		{
			m_buffer->reopen();
		}

		m_lastOffset = 0;
	}

	void StreamSound::update_buffers()
	{
		int processed;

		alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &processed);

		while(processed--)
		{
			ALuint buffer;
			alSourceUnqueueBuffers(m_source, 1, &buffer);

			ALint size, bits, channels, freq;

			alGetBufferi(buffer, AL_SIZE, &size);
			alGetBufferi(buffer, AL_BITS, &bits);
			alGetBufferi(buffer, AL_CHANNELS, &channels);
			alGetBufferi(buffer, AL_FREQUENCY, &freq);    

			m_lastOffset += ((ALuint)size/channels/(bits/8)) / (ALfloat)freq;

			bool ended = m_buffer->fill_chunk(buffer);

			if(ended && m_loop)
				rewind();

			alSourceQueueBuffers(m_source, 1, &buffer);
		}
	}

	void StreamSound::fill_buffers()
	{
		int i = 0;
		while(i < NUM_BUFFERS)
		{
			bool active = m_buffer->fill_chunk(m_aLBuffers[i]);

			if(active)
				alSourceQueueBuffers(m_source, 1, &m_aLBuffers[i++]);
			else
				break;
		}
	}

	void StreamSound::clear_buffers()
	{
		int queued;
		ALuint buffer;

		alGetSourcei(m_source, AL_BUFFERS_QUEUED, &queued);

		while (queued--)
		{
			alSourceUnqueueBuffers(m_source, 1, &buffer);
			check_error();
		}
	}

	void StreamSound::update_play_cursor()
	{
		if(m_buffer->m_seekable)
			m_buffer->seek_time(m_cursor);

		m_update_cursor = false;
		m_lastOffset = m_cursor;
	}

	ALfloat StreamSound::get_play_cursor()
	{
		ALfloat pos;
		alGetSourcef(m_source, AL_SEC_OFFSET, &pos);

		if ((m_lastOffset + pos) >= m_duration) 
			return (m_lastOffset + pos) - m_duration;
		else
			return m_lastOffset + pos;
	}
}

#ifdef MUD_MODULES
module mud.snd;
#else
#endif

namespace mud
{
    // Exported types
    
}
