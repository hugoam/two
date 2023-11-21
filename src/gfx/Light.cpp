//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <gfx/Cpp20.h>
module two.gfx;

namespace two
{
	//static uint32_t s_light_index = 0;

	Light::Light(Node3& node, LightType type, bool shadows, Colour colour, float energy, float range)
		: m_node(&node)
		, m_type(type)
		, m_colour(colour)
		, m_range(range)
		, m_energy(energy)
		, m_shadows(shadows)
		//, m_index(s_light_index++)
	{
		m_shadow_bias = 0.01f;
		//m_shadow_normal_bias = 0.f; // @todo investigate why making this higher fucks up the first shadow slice

		m_attenuation = 1.f;

		if(type != LightType::Spot)
			m_spot_angle = 0.f;

		if(type == LightType::Direct)
		{
			m_shadow_flags = CSM_Stabilize;
			m_shadow_bias = 0.1f;
#ifdef TWO_PLATFORM_EMSCRIPTEN
			m_shadow_num_splits = 2;
#else
			m_shadow_num_splits = 4;
#endif
		}
	}
}
