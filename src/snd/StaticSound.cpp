//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <snd/StaticSound.h>

#include <iostream>

/* OpenAL */
#include <al.h>

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

	void StaticSound::openShared(SharedBuffer& buffer)
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

	void StaticSound::updateBuffers()
	{}

	void StaticSound::fillBuffers()
	{
		alSourcei(m_source, AL_BUFFER, m_buffer->m_al_buffer);
	}

	void StaticSound::clearBuffers()
	{
		alSourcei(m_source, AL_BUFFER, 0);
	}

	void StaticSound::rewind()
	{
		alSourceRewind(m_source);
	}

	void StaticSound::updatePlayCursor()
	{
		alSourcef(m_source, AL_SEC_OFFSET, m_cursor);

		m_updateCursor = false;
	}

	ALfloat StaticSound::getPlayCursor()
	{
		ALfloat cursor;
		alGetSourcef(m_source, AL_SEC_OFFSET, &cursor);
		return cursor;
	}

	void StaticSound::setLoop(bool loop)
	{
		Sound::setLoop(loop);

		if(m_active)
			alSourcei(m_source, AL_LOOPING, loop);
	}
}
