//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ class refl_ MUD_GFX_EXPORT Shot
	{
	public:
		std::vector<Item*> m_items;
		std::vector<Light*> m_lights;
		//std::vector<ReflectionProbe*> m_reflection_probes;
		std::vector<GIProbe*> m_gi_probes;
		std::vector<ImmediateDraw*> m_immediate;
	};
}
