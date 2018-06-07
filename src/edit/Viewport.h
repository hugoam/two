//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#include <uio/Unode.h>
#endif
#include <edit/Generated/Forward.h>

namespace mud
{
	MUD_EDIT_EXPORT void viewport_picker(Viewer& viewer, Widget& widget, std::vector<Ref>& selection);

	MUD_EDIT_EXPORT Viewer& scene_viewport(Widget& parent, Scene& scene, Camera& camera, std::vector<Ref>& selection);
}
