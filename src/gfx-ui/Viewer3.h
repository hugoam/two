//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx-ui/Forward.h>
#include <gfx-ui/Viewer.h>

namespace mud
{
	export_ class MUD_GFX_UI_EXPORT SpaceViewport : public Viewer
	{
	public:
		SpaceViewport(Widget* parent, void* identity, Scene& scene);

		virtual ControlNode* controlEvent(InputEvent& inputEvent);
	};
}
