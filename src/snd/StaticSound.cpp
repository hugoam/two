//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <snd/StaticSound.h>

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
