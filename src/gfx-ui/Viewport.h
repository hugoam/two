//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#endif
#include <gfx-ui/Forward.h>

namespace mud
{
	MUD_GFX_UI_EXPORT void viewport_picker(Viewer& viewer, Widget& widget, std::vector<Ref>& selection);

	MUD_GFX_UI_EXPORT Viewer& scene_viewport(Widget& parent, Scene& scene, Camera& camera, std::vector<Ref>& selection);
}
