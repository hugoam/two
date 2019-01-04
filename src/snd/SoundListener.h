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

		vec3 m_position = Zero3;
		vec3 m_front = { 0.f, 0.f, -1.f }; //-Z3;
		vec3 m_up = Y3;

		void setTransform(const vec3& position, const quat& rotation)
		{
			m_position = position;
			m_front = rotate(rotation, -Z3);
			m_up = rotate(rotation, Y3);
			m_transformUpdated = true;
		}

		void setTransform(const vec3& position, const vec3& front, const vec3& up)
		{
			m_position = position;
			m_front = front;
			m_up = up;
			m_transformUpdated = true;
		}

		void update();

	private:
		bool m_transformUpdated = true;
	};
}
