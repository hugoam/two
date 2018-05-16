//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <snd/SharedBuffer.h>

#include <snd/SoundManager.h>

#include <iostream>

/* OpenAL */
#include <al.h>

namespace mud
{
	SharedBuffer::SharedBuffer(const string& filename, const ReleaseCallback& onRelease)
		: m_aLBuffer(AL_NONE)
		, m_numUsers(0)
		, m_onRelease(onRelease)
	{
		if(filename.find(".ogg") != filename.npos || filename.find(".OGG") != filename.npos)
			m_sound_file_buffer = make_unique<OggFileBuffer>();

		alGenBuffers(1, &m_aLBuffer);

		m_sound_file_buffer->open(filename.c_str());
		m_sound_file_buffer->fill(m_aLBuffer);
	}

	SharedBuffer::~SharedBuffer()
	{
		alDeleteBuffers(1, &m_aLBuffer);

		m_sound_file_buffer->close();
	}

	void SharedBuffer::use()
	{
		++m_numUsers;
	}

	void SharedBuffer::release()
	{
		--m_numUsers;
		if(m_numUsers == 0)
			m_onRelease(*this);
	}
}
