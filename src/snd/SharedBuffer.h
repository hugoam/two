//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Unique.h>
#include <snd/SoundFileBuffer.h>
#include <snd/OggFileBuffer.h>

namespace two
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
