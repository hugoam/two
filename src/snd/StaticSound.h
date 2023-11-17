//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <snd/Sound.h>
#include <snd/SharedBuffer.h>

namespace two
{
	class StaticSound : public Sound
	{
	public:
		StaticSound(SoundImplementer& manager, SoundCallback callback = {});
		~StaticSound();

		virtual void open(SharedBuffer& buffer) override;
		virtual void release() override;
			    
		virtual void update_buffers() override;
		virtual void fill_buffers() override;
		virtual void clear_buffers() override;
			    
		virtual void rewind() override;
		virtual void update_play_cursor() override;
		virtual ALfloat get_play_cursor() override;

		void set_loop(bool loop);

	private:
		SharedBuffer* m_buffer;
	};
}
