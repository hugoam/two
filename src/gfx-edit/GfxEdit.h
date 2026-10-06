//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx-edit/Forward.h>

namespace two
{
#if 0
	export_ TWO_GFX_EDIT_EXPORT void painter_edit(Widget parent, VisuPainter& painter);
	export_ TWO_GFX_EDIT_EXPORT void painter_panel(Widget parent, VisuScene& scene);

#endif

	export_ TWO_GFX_EDIT_EXPORT void space_axes(Gnode parent);

	export_ TWO_GFX_EDIT_EXPORT void animation_edit(Widget parent, MimeHandle animated);

	export_ TWO_GFX_EDIT_EXPORT void asset_browser(Widget parent, GfxSystem& gfx);

	export_ TWO_GFX_EDIT_EXPORT void edit_viewer_filters(Widget parent, Viewer& viewer);

	export_ TWO_GFX_EDIT_EXPORT void panel_gfx_stats(Widget parent);
	export_ TWO_GFX_EDIT_EXPORT void edit_gfx(Widget parent, GfxSystem& system);
	
	export_ TWO_GFX_EDIT_EXPORT void gfx_editor(Widget parent, GfxSystem& system);

	export_ TWO_GFX_EDIT_EXPORT void declare_gfx_edit();
}
