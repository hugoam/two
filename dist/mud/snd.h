#pragma once

#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>




#ifndef MUD_SND_EXPORT
#define MUD_SND_EXPORT MUD_IMPORT
#endif

namespace mud
{
    class Sound;
    class SoundFileBuffer;
    class OggFileBuffer;
    class SharedBuffer;
    class SoundImplementer;
    class SoundListener;
    class SoundManager;
    class StaticSound;
    class StreamSound;
}






#include <stl/string.h>
#include <stl/vector.h>


typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;

typedef char ALboolean;
typedef char ALchar;
typedef char ALbyte;
typedef unsigned char ALubyte;
typedef short ALshort;
typedef unsigned short ALushort;
typedef int ALint;
typedef unsigned int ALuint;
typedef int ALsizei;
typedef int ALenum;
typedef float ALfloat;
typedef double ALdouble;
typedef void ALvoid;

#include <stdint.h>

namespace mud
{
	class Sound;

	using cstring = const char*;
	using SoundCallback = void(*)(Sound&);

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

		vec3 m_position = Zero3;	// 3D position
		vec3 m_direction = Zero3;	// 3D direction
		vec3 m_velocity = Zero3;	// 3D velocity

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
#include <stl/string.h>

namespace mud
{
	class MUD_SND_EXPORT SoundFileBuffer
	{
	public:
		virtual ~SoundFileBuffer() {}

		string m_filename = "";
		ALenum m_format = 0;
		bool m_seekable = true;
		bool m_mono = false;
		ALfloat m_duration = 0.f;

		virtual void open(const string& filename) = 0;
		virtual void close() = 0;
		virtual void reopen() = 0;

		virtual void seek_time(float time) = 0;
		virtual void seek_bytes(long pos) = 0;

		virtual void fill(ALuint buffer) = 0;
		virtual bool fill_chunk(ALuint buffer) = 0;
	};
}

namespace mud
{
	using cstring = const char*;

	class MUD_SND_EXPORT OggFileBuffer : public SoundFileBuffer
	{
	public:	
		OggFileBuffer();
		~OggFileBuffer();

		size_t m_chunk_size = 0;			// Size of audio buffer (250ms)

		virtual void open(const string& filename) override;
		virtual void close() override;
		virtual void reopen() override;

		virtual void seek_time(float time) override;
		virtual void seek_bytes(long pos) override;

		virtual void fill(ALuint buffer) override;
		virtual bool fill_chunk(ALuint buffer) override;

	protected:
		bool read_buffer_info();		
		bool read_chunk(char* chunk, size_t chunk_size);

	private:
		struct Impl;
		unique<Impl> m_impl;
	};
}



namespace mud
{
	class SharedBuffer
	{
	public:
		SharedBuffer(const string& fileName, SoundManager& manager);
		~SharedBuffer();

		unique<SoundFileBuffer> m_file_buffer;

		ALuint m_al_buffer;

		void use();
		void release();

	private:
		int m_num_users = 0;
		SoundManager* m_manager = nullptr;
	};
}



namespace mud
{
	class SoundImplementer
	{
	public:
		virtual void play_sound(Sound& sound) = 0;
		virtual void pause_sound(Sound& sound) = 0;
		virtual void stop_sound(Sound& sound) = 0;
		virtual void destroy_sound(Sound& sound) = 0;

		virtual void update_position(Sound& sound, const vec3& position) = 0;
	};
}



namespace mud
{
	class MUD_SND_EXPORT SoundListener
	{
	public:
		SoundListener();

		vec3 m_position = Zero3;
		vec3 m_front = { 0.f, 0.f, -1.f }; //-Z3;
		vec3 m_up = Y3;

		void set_transform(const vec3& position, const quat& rotation);
		void set_transform(const vec3& position, const vec3& front, const vec3& up);

		void update();

	private:
		bool m_transformUpdated = true;
	};
}


#include <stl/function.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/memory.h>
#include <stl/map.h>

#ifdef SOUND_THREADED
//#include <thread>
//#include <memory>
#endif

namespace mud
{
	using SoundCallback = void(*)(Sound&);

	bool openal_check_error();

	class MUD_SND_EXPORT SoundManager : public SoundImplementer
	{
	public:
		using SoundAction = function<void()>;
		using SourceVector = vector<ALuint>;

		// Thread-safe interface
	public:
		SoundManager(const string& resource_path = "");
		~SoundManager();

		SoundManager(const SoundManager& other) = delete;
		SoundManager& operator=(const SoundManager& other) = delete;

		bool init(const string& device_name = "", unsigned int max_sources = 100);

		Sound* create_sound(const string& file, bool loop = false, bool stream = false, SoundCallback callback = {});

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

		void create(unique<Sound> sound, const string& filename, bool stream);
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
		SharedBuffer& create_buffer(const string& filename);
		SharedBuffer& get_buffer(const string& filename);
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



namespace mud
{
	class StaticSound : public Sound
	{
	public:
		StaticSound(SoundImplementer& manager, SoundCallback callback = {});
		~StaticSound();

		virtual void open(SharedBuffer& buffer) override;
		virtual void release() override;
			    
		virtual void update_buffers() override;
		virtual void fill_buffers() override;
		virtual void clear_buffers() override;
			    
		virtual void rewind() override;
		virtual void update_play_cursor() override;
		virtual ALfloat get_play_cursor() override;

		void set_loop(bool loop);

	private:
		SharedBuffer* m_buffer;
	};
}



#include <stl/vector.h>

namespace mud
{
	class StreamSound : public Sound
	{
	public:
		StreamSound(SoundImplementer& manager, SoundCallback callback = {});
		~StreamSound();

		void setup();

		virtual void open(const string& filename) override;
		virtual void release() override;

		virtual void update_buffers() override;
		virtual void fill_buffers() override;
		virtual void clear_buffers() override;

		virtual void rewind() override;
		virtual void update_play_cursor() override;
		virtual ALfloat get_play_cursor() override;

	private:
		int m_numBuffers;
		vector<ALuint> m_aLBuffers;
		unique<SoundFileBuffer> m_buffer;

		ALfloat m_lastOffset;
	};
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif


namespace mud
{
    // Exported types
    
    
}

