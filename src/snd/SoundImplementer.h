//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <snd/Forward.h>

namespace mud
{
	class SoundImplementer
	{
	public:
		virtual void playSound(Sound* sound) = 0;
		virtual void pauseSound(Sound* sound) = 0;
		virtual void stopSound(Sound* sound) = 0;
		virtual void destroySound(Sound* sound) = 0;

		virtual void updatePosition(Sound* sound, const vec3& position) = 0;
	};
}
