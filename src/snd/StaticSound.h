//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <snd/Sound.h>
#include <snd/SharedBuffer.h>

namespace mud
{
	class StaticSound : public Sound
	{
	public:
		StaticSound(SoundImplementer& manager, SoundCallback callback = {});
		~StaticSound();

		virtual void open_shared(SharedBuffer& buffer) final;
		virtual void release() final;
			    
		virtual void update_buffers() final;
		virtual void fill_buffers() final;
		virtual void clear_buffers() final;
			    
		virtual void rewind() final;
		virtual void update_play_cursor() final;
		virtual ALfloat get_play_cursor() final;

		void set_loop(bool loop);

	private:
		SharedBuffer* m_buffer;
	};
}
