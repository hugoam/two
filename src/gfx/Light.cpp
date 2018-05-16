//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <gfx/Light.h>

namespace mud
{
	Light::Light(Node3& node, LightType type, bool shadows)
		: m_node(node)
		, m_type(type)
		, m_shadows(shadows)
	{
		m_shadow_bias = 0.1f;
		m_shadow_normal_bias = 0.1f;
	}

	Light::~Light()
	{}
}
