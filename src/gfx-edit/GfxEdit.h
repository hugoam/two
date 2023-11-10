//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <math/Vec.h>
#endif
#include <gfx-edit/Forward.h>

namespace two
{
#if 0
	TWO_GFX_EDIT_EXPORT void painter_edit(Widget& parent, VisuPainter& painter);
	TWO_GFX_EDIT_EXPORT void painter_panel(Widget& parent, VisuScene& scene);

#endif

	TWO_GFX_EDIT_EXPORT void space_axes(Gnode& parent);

	TWO_GFX_EDIT_EXPORT void animation_edit(Widget& parent, Mime& animated);

	TWO_GFX_EDIT_EXPORT void asset_browser(Widget& parent, GfxSystem& gfx);

	TWO_GFX_EDIT_EXPORT void edit_viewer_filters(Widget& parent, Viewer& viewer);

	TWO_GFX_EDIT_EXPORT void panel_gfx_stats(Widget& parent);
	TWO_GFX_EDIT_EXPORT void edit_gfx(Widget& parent, GfxSystem& system);
	
	TWO_GFX_EDIT_EXPORT void gfx_editor(Widget& parent, GfxSystem& system);

	TWO_GFX_EDIT_EXPORT void declare_gfx_edit();
}
