//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <snd/Sound.h>
#include <snd/Forward.h>
#include <string>

namespace mud
{
	using string = std::string;

	class MUD_SND_EXPORT SoundFileBuffer
	{
	public:
		virtual ~SoundFileBuffer() {}

		string m_filename = "";
		ALenum m_format = 0;
		bool m_seekable = true;
		bool m_mono = false;
		ALfloat m_duration = 0.f;

		virtual void open(cstring filename) = 0;
		virtual void close() = 0;
		virtual void reopen() = 0;

		virtual void seek_time(float time) = 0;
		virtual void seek_bytes(long pos) = 0;

		virtual void fill(ALuint buffer) = 0;
		virtual bool fill_chunk(ALuint buffer) = 0;
	};
}
