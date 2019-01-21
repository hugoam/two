//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Unique.h>
#include <snd/Sound.h>
#include <snd/SoundFileBuffer.h>

#include <stl/vector.h>

namespace mud
{
	class StreamSound : public Sound
	{
	public:
		StreamSound(SoundImplementer& manager, SoundCallback callback = {});
		~StreamSound();

		void open(cstring filename);

		void setup();
		void release();

		void update_buffers();
		void fill_buffers();
		void clear_buffers();

		void rewind();
		void update_play_cursor();
		ALfloat get_play_cursor();

	private:
		// Streaming sounds have local buffers
		int m_numBuffers;
		vector<ALuint> m_aLBuffers;
		unique<SoundFileBuffer> m_buffer;

		ALfloat m_lastOffset;
	};
}
