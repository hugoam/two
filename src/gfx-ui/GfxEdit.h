//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx-ui/Forward.h>

namespace mud
{
#if 0
	MUD_GFX_UI_EXPORT void painter_edit(Widget& parent, VisuPainter& painter);
	MUD_GFX_UI_EXPORT void painter_panel(Widget& parent, VisuScene& scene);

#endif

	MUD_GFX_UI_EXPORT void space_axes(Gnode& parent);

	MUD_GFX_UI_EXPORT mat4 fix_bone_pose(Bone& bone);

	MUD_GFX_UI_EXPORT void debug_draw_skeleton(Gnode& parent, const quat& position, const quat& rotation, Rig& rig);
	MUD_GFX_UI_EXPORT void debug_draw_light_clusters(Gnode& parent, Camera& camera);
	MUD_GFX_UI_EXPORT void debug_draw_light_slices(Gnode& parent, Light& light);

	MUD_GFX_UI_EXPORT void animation_edit(Widget& parent, Animated& animated);

	MUD_GFX_UI_EXPORT void asset_browser(Widget& parent, GfxSystem& gfx_system);

	MUD_GFX_UI_EXPORT void edit_viewer_filters(Widget& parent, Viewer& viewer);

	MUD_GFX_UI_EXPORT void panel_gfx_stats(Widget& parent);
	MUD_GFX_UI_EXPORT void edit_gfx_system(Widget& parent, GfxSystem& system);
	
	MUD_GFX_UI_EXPORT void gfx_editor(Widget& parent, GfxSystem& system);

	MUD_GFX_UI_EXPORT void declare_gfx_edit();
}
