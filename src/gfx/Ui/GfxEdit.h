//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Generated/Forward.h>

namespace mud
{
#if 0
	MUD_GFX_EXPORT void painter_edit(Widget& parent, VisuPainter& painter);
	MUD_GFX_EXPORT void painter_panel(Widget& parent, VisuScene& scene);
#endif

	MUD_GFX_EXPORT void space_axes(Gnode& parent);
	MUD_GFX_EXPORT void debug_draw_light_slices(Gnode& parent, Light& light, LightShadow& shadow);

	MUD_GFX_EXPORT void animation_edit(Widget& parent, Animated& animated);

	MUD_GFX_EXPORT void edit_viewer_filters(Widget& parent, Viewer& viewer);

	MUD_GFX_EXPORT void panel_gfx_stats(Widget& parent);
	MUD_GFX_EXPORT void edit_gfx_system(Widget& parent, GfxSystem& system);

	MUD_GFX_EXPORT void declare_gfx_edit();
}
