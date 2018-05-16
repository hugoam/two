//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <snd/StreamSound.h>

#include <al.h>

#include <snd/OggFileBuffer.h>

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

	void StreamSound::open(cstring filename)
	{
		//std::cerr << "opening stream sound" << std::endl;

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

	void StreamSound::updateBuffers()
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

	void StreamSound::fillBuffers()
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

	void StreamSound::clearBuffers()
	{
		int queued;
		ALuint buffer;

		alGetSourcei(m_source, AL_BUFFERS_QUEUED, &queued);

		while (queued--)
		{
			alSourceUnqueueBuffers(m_source, 1, &buffer);
			checkError();
		}
	}

	void StreamSound::updatePlayCursor()
	{
		if(m_buffer->m_seekable)
			m_buffer->seek_time(m_cursor);

		m_updateCursor = false;
		m_lastOffset = m_cursor;
	}

	ALfloat StreamSound::getPlayCursor()
	{
		ALfloat pos;
		alGetSourcef(m_source, AL_SEC_OFFSET, &pos);

		if ((m_lastOffset + pos) >= m_duration) 
			return (m_lastOffset + pos) - m_duration;
		else
			return m_lastOffset + pos;
	}
}
