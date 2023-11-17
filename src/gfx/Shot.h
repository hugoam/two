//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>

namespace two
{
	export_ class refl_ TWO_GFX_EXPORT Shot
	{
	public:
		virtual ~Shot() {}
		vector<Item*> m_items;
		vector<Item*> m_occluders;
		vector<Light*> m_lights;
		vector<ImmediateDraw*> m_immediate;
	};
}
