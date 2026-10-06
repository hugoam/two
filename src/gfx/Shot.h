//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Handles.h>

namespace two
{
	export_ class refl_ TWO_GFX_EXPORT Shot
	{
	public:
		virtual ~Shot() {}
		vector<ItemIndex> m_items;
		vector<ItemIndex> m_occluders;
		vector<LightIndex> m_lights;
		vector<ImmediateDraw*> m_immediate;
	};
}
