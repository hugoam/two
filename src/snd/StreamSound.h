//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Unique.h>
#include <snd/Sound.h>
#include <snd/SoundFileBuffer.h>

#include <stl/vector.h>

namespace two
{
	class StreamSound : public Sound
	{
	public:
		StreamSound(SoundImplementer& manager, SoundCallback callback = {});
		~StreamSound();

		void setup();

		virtual void open(const string& filename) override;
		virtual void release() override;

		virtual void update_buffers() override;
		virtual void fill_buffers() override;
		virtual void clear_buffers() override;

		virtual void rewind() override;
		virtual void update_play_cursor() override;
		virtual ALfloat get_play_cursor() override;

	private:
		int m_numBuffers;
		vector<ALuint> m_aLBuffers;
		unique<SoundFileBuffer> m_buffer;

		ALfloat m_lastOffset;
	};
}
