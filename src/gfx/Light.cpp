//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <gfx/Light.h>
#endif

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
