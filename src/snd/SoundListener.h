//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <snd/Forward.h>

namespace mud
{
	class MUD_SND_EXPORT SoundListener
	{
	public:
		SoundListener();

		vec3 m_position = vec3(0.f);
		vec3 m_front = { 0.f, 0.f, -1.f }; //-Z3;
		vec3 m_up = Y3;

		void set_transform(const vec3& position, const quat& rotation);
		void set_transform(const vec3& position, const vec3& front, const vec3& up);

		void update();

	private:
		bool m_transformUpdated = true;
	};
}
