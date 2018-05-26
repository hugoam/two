//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <edit/Generated/Forward.h>
#include <edit/Viewer/Viewer.h>

namespace mud
{
	class MUD_GFX_EXPORT SpaceViewport : public Viewer
	{
	public:
		SpaceViewport(Widget* parent, void* identity, Scene& scene);

		virtual ControlNode* controlEvent(InputEvent& inputEvent);
	};
}
