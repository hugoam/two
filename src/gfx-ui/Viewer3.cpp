//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.gfx.ui;

namespace two
{
	SpaceViewport::SpaceViewport(Widget& self, Scene& scene)
		: Viewer(self, scene)
	{}
}
