//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <math/Vec.hpp>
#include <snd/SoundListener.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace two
{
	SoundListener::SoundListener()
	{}

	void SoundListener::set_transform(const vec3& position, const quat& rotation)
	{
		m_position = position;
		m_front = rotate(rotation, -Z3);
		m_up = rotate(rotation, Y3);
		m_transformUpdated = true;
	}

	void SoundListener::set_transform(const vec3& position, const vec3& front, const vec3& up)
	{
		m_position = position;
		m_front = front;
		m_up = up;
		m_transformUpdated = true;
	}

	void SoundListener::update()
	{
		if(m_transformUpdated)
		{
			alListener3f(AL_POSITION, m_position.x, m_position.y, m_position.z);
			alListenerfv(AL_ORIENTATION, value_ptr(m_front));

			//alListener3f(AL_VELOCITY, );

			m_transformUpdated = false;
		}     
	}
}
