//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <snd/OggFileBuffer.h>

#include <iostream>
#include <vector>

/* vorbis */
#include <vorbis/vorbisfile.h>

/* OpenAL */
#include <al.h>
#include <alc.h>


namespace mud
{
	static size_t ogg_read(void* ptr, size_t size, size_t count, void* file)
	{
		return fread(ptr, size, count, (FILE*)file);
	}

	static int ogg_seek(void* file, ogg_int64_t offset, int whence)
	{
		return fseek((FILE*)file, long(offset), whence);
	}

	static int ogg_close(void* file)
	{
		return fclose((FILE*)file);
	}

	static long ogg_tell(void* file)
	{
		return ftell((FILE*)file);
	}

	struct OggFileBuffer::Impl
	{
		OggVorbis_File m_ogg_file;
		vorbis_info* m_vorbis_info = nullptr;
		vorbis_comment* m_vorbis_comment = nullptr;

		ov_callbacks m_ogg_callbacks;
	};

	OggFileBuffer::OggFileBuffer()
		: m_impl(make_unique<Impl>())
	{}

	OggFileBuffer::~OggFileBuffer()
	{}

	void OggFileBuffer::open(cstring filename)
	{
		m_impl->m_ogg_callbacks.read_func = ogg_read;
		m_impl->m_ogg_callbacks.close_func = ogg_close;
		m_impl->m_ogg_callbacks.seek_func = ogg_seek;
		m_impl->m_ogg_callbacks.tell_func = ogg_tell;

		m_filename = filename;

		//FILE* file = fopen(filename, "rb");
		//int result = ov_open_callbacks(file, &m_oggFile, NULL, 0, m_oggCallbacks);

		int result = ov_fopen(filename, &m_impl->m_ogg_file);

		if(result < 0)
			return;

		m_impl->m_vorbis_info = ov_info(&m_impl->m_ogg_file, -1);
		m_impl->m_vorbis_comment = ov_comment(&m_impl->m_ogg_file, -1);

		m_duration = static_cast<float>(ov_time_total(&m_impl->m_ogg_file, -1));
		m_seekable = (ov_seekable(&m_impl->m_ogg_file) != 0);

		if (!this->read_buffer_info())
			return;

		m_mono = ((m_format==AL_FORMAT_MONO16) || (m_format==AL_FORMAT_MONO8));
	}

	void OggFileBuffer::close()
	{
		ov_clear(&m_impl->m_ogg_file);
	}

	void OggFileBuffer::reopen()
	{
		close();
		open(m_filename.c_str());
	}

	void OggFileBuffer::seek_time(float time)
	{
		ov_time_seek(&m_impl->m_ogg_file, time);
	}

	void OggFileBuffer::seek_bytes(long pos)
	{
		ov_raw_seek(&m_impl->m_ogg_file, pos);
	}

	void OggFileBuffer::fill(ALuint buffer)
	{
		std::vector<char> data;
		std::vector<char> chunk = std::vector<char>(m_chunk_size);

		int size_read = 1;
		int last_pos = 0;
		int section;

		while(size_read > 0)
		{
			//std::cerr << "reading : " << size_read << " at pos : " << last_pos << std::endl;
			size_read = ov_read(&m_impl->m_ogg_file, chunk.data(), int(m_chunk_size), 0, 2, 1, &section);
			data.insert(data.end(), chunk.begin(), chunk.begin() + size_read);
			last_pos += size_read;
		}

		alGetError();
		alBufferData(buffer, m_format, &data[0], last_pos, m_impl->m_vorbis_info->rate);
	}

	bool OggFileBuffer::fill_chunk(ALuint buffer)
	{
		std::vector<char> chunk = std::vector<char>(m_chunk_size);
		
		bool last_chunk = this->read_chunk(chunk.data(), m_chunk_size);

		alBufferData(buffer, m_format, chunk.data(), ALsizei(m_chunk_size), m_impl->m_vorbis_info->rate);
		alGetError();

		return last_chunk;
	}

	bool OggFileBuffer::read_chunk(char* data_chunk, size_t chunk_size)
	{
		UNUSED(chunk_size);
		size_t size = 0;
		int section;
		int result;
		bool last_chunk = true;

		while(size < m_chunk_size)
		{
			result = ov_read(&m_impl->m_ogg_file, data_chunk + size, int(m_chunk_size - size), 0, 2, 1, &section);

			if(result > 0)
				size += result;
			else if(result == 0)
				last_chunk = false;
			else if(result < 0)
				break;
		}

		return last_chunk;
	}


	bool OggFileBuffer::read_buffer_info()
	{
		/** Calculates buffer size and format.
		@remarks
			Calculates a block aligned buffer size of 250ms using
			sound properties.
		 */
		// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...

		switch(m_impl->m_vorbis_info->channels)
		{
		case 1:
				m_format = AL_FORMAT_MONO16;
				// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate >> 1;
				m_chunk_size -= (m_chunk_size % 2);
			break;
		case 2:
				m_format = AL_FORMAT_STEREO16;
				// Set BufferSize to 250ms (Frequency * 4 (16bit stereo) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate;
				m_chunk_size -= (m_chunk_size % 4);
			break;
		case 4:
				m_format = alGetEnumValue("AL_FORMAT_QUAD16");
				if (!m_format) return false;
				// Set BufferSize to 250ms (Frequency * 8 (16bit 4-channel) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate * 2;
				m_chunk_size -= (m_chunk_size % 8);
			break;
		case 6:
				m_format = alGetEnumValue("AL_FORMAT_51CHN16");
				if (!m_format) return false;
				// Set BufferSize to 250ms (Frequency * 12 (16bit 6-channel) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate * 3;
				m_chunk_size -= (m_chunk_size % 12);
			break;
		case 7:
				m_format = alGetEnumValue("AL_FORMAT_61CHN16");
				if (!m_format) return false;
				// Set BufferSize to 250ms (Frequency * 16 (16bit 7-channel) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate * 4;
				m_chunk_size -= (m_chunk_size % 16);
			break;
		case 8:
				m_format = alGetEnumValue("AL_FORMAT_71CHN16");
				if (!m_format) return false;
				// Set BufferSize to 250ms (Frequency * 20 (16bit 8-channel) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate * 5;
				m_chunk_size -= (m_chunk_size % 20);
			break;
		default:
				m_format = AL_FORMAT_MONO16;
				// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
				m_chunk_size = m_impl->m_vorbis_info->rate >> 1;
				m_chunk_size -= (m_chunk_size % 2);
			break;
		}
		return true;
	}
}
