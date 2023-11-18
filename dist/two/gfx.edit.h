#pragma once

#include <two/gfx.h>
#include <two/geom.h>
#include <two/ui.h>
#include <two/srlz.h>
#include <two/uio.h>
#include <two/gfx.pbr.h>
#include <two/lang.h>
#include <two/math.h>
#include <two/refl.h>
#include <two/gfx.ui.h>
#include <two/infra.h>
#include <two/type.h>




#ifndef TWO_GFX_EDIT_EXPORT
#define TWO_GFX_EDIT_EXPORT TWO_IMPORT
#endif

namespace two
{
}



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



namespace two
{
	TWO_GFX_EDIT_EXPORT void particle_edit(Widget& parent, GfxSystem& system, Flow& generator);
	TWO_GFX_EDIT_EXPORT void particle_edit(Widget& parent, GfxSystem& system, Call& particles);
	TWO_GFX_EDIT_EXPORT void particle_editor(Widget& parent, GfxSystem& system);
}



namespace two
{
	TWO_GFX_EDIT_EXPORT void prefab_edit(Widget& parent, GfxSystem& gfx, PrefabNode& node, PrefabNode*& selected);
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif



namespace two
{
    // Exported types
    
    
}

