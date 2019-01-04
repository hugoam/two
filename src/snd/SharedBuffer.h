//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Unique.h>
#include <snd/SoundFileBuffer.h>
#include <snd/OggFileBuffer.h>

#include <functional>

namespace mud
{
	class SharedBuffer
	{
	public:
		typedef std::function<void (SharedBuffer&)> ReleaseCallback;

	public:
		SharedBuffer(const string& fileName, const ReleaseCallback& onRelease);
		~SharedBuffer();

		unique_ptr<SoundFileBuffer> m_file_buffer;

		ALuint m_al_buffer;

		void use();
		void release();

	private:
		int m_num_users = 0;
		ReleaseCallback m_on_release;
	};
}
