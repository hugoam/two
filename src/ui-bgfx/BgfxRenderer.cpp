//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui-bgfx/BgfxRenderer.h>

namespace mud
{
	BgfxUiRenderer::BgfxUiRenderer(cstring resource_path, bx::AllocatorI* allocator)
#ifdef MUD_VG_RENDERER
		: vgRenderer(resource_path, allocator)
#else
		: NanoRenderer(resource_path)
#endif
	{}
}
