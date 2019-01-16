//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <snd/SharedBuffer.h>

#include <snd/SoundManager.h>

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
			m_manager->releaseBuffer(*this);
	}
}
