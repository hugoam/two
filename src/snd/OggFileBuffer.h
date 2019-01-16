//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <snd/SoundFileBuffer.h>
#include <type/Unique.h>

namespace mud
{
	using cstring = const char*;

	class MUD_SND_EXPORT OggFileBuffer : public SoundFileBuffer
	{
	public:	
		OggFileBuffer();
		~OggFileBuffer();

		size_t m_chunk_size = 0;			// Size of audio buffer (250ms)

		void open(cstring filename);
		void close();
		void reopen();

		void seek_time(float time);
		void seek_bytes(long pos);

		void fill(ALuint buffer);
		bool fill_chunk(ALuint buffer);

	protected:
		bool read_buffer_info();		
		bool read_chunk(char* chunk, size_t chunk_size);

	private:
		struct Impl;
		unique<Impl> m_impl;
	};
}
