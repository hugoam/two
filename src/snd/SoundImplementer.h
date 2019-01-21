//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <snd/Forward.h>

namespace mud
{
	class SoundImplementer
	{
	public:
		virtual void play_sound(Sound& sound) = 0;
		virtual void pause_sound(Sound& sound) = 0;
		virtual void stop_sound(Sound& sound) = 0;
		virtual void destroy_sound(Sound& sound) = 0;

		virtual void update_position(Sound& sound, const vec3& position) = 0;
	};
}
