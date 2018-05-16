//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#ifdef MUD_VG_RENDERER
#include <ui-nanovg/VgRenderer.h>
#else
#include <ui-nanovg/NanoRenderer.h>
#endif

#include <bx/allocator.h>

namespace mud
{
#ifdef MUD_VG_RENDERER
	class BgfxUiRenderer : public vgRenderer
#else
	class BgfxUiRenderer : public NanoRenderer
#endif
	{
	public:
		BgfxUiRenderer(cstring resource_path, bx::AllocatorI* allocator);
	};
}
