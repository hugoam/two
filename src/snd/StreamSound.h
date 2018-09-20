//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Unique.h>
#include <snd/Sound.h>
#include <snd/SoundFileBuffer.h>

#include <vector>

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

		void updateBuffers();
		void fillBuffers();
		void clearBuffers();

		void rewind();
		void updatePlayCursor();
		ALfloat getPlayCursor();

	private:
		// Streaming sounds have local buffers
		int m_numBuffers;
		std::vector<ALuint> m_aLBuffers;
		unique_ptr<SoundFileBuffer> m_buffer;

		ALfloat m_lastOffset;
	};
}
