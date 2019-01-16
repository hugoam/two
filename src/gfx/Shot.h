//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#endif
#include <gfx/Forward.h>

namespace mud
{
	export_ class refl_ MUD_GFX_EXPORT Shot
	{
	public:
		vector<Item*> m_items;
		vector<Item*> m_occluders;
		vector<Light*> m_lights;
		vector<ReflectionProbe*> m_reflection_probes;
		vector<GIProbe*> m_gi_probes;
		vector<LightmapAtlas*> m_lightmaps;
		vector<ImmediateDraw*> m_immediate;
	};
}
