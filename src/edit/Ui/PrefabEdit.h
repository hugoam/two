//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <edit/Generated/Forward.h>

namespace mud
{
	MUD_GFX_EXPORT PrefabNode* prefab_edit(Widget& parent, GfxSystem& system, PrefabNode& node, PrefabNode*& selected);
}
