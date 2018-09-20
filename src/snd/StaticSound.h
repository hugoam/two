//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
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

		virtual void openShared(SharedBuffer& buffer) final;
		virtual void release() final;
			    
		virtual void updateBuffers() final;
		virtual void fillBuffers() final;
		virtual void clearBuffers() final;
			    
		virtual void rewind() final;
		virtual void updatePlayCursor() final;
		virtual ALfloat getPlayCursor() final;

		void setLoop(bool loop);

	private:
		SharedBuffer* m_buffer;
	};
}
