#pragma once

#include <mud/gfx.h>
#include <mud/geom.h>
#include <mud/ui.h>
#include <mud/srlz.h>
#include <mud/uio.h>
#include <mud/gfx.pbr.h>
#include <mud/lang.h>
#include <mud/math.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>



#ifndef MUD_GFX_EDIT_EXPORT
#define MUD_GFX_EDIT_EXPORT MUD_IMPORT
#endif

namespace mud
{
namespace ui
{
    enum class OrbitMode : int;
    
}
}

namespace mud
{
    class SpaceSheet;
    struct ViewerStyles;
    class ViewerController;
    class Viewer;
    class SceneViewer;
    class OrbitController;
    class FreeOrbitController;
    class SpaceViewport;
}


#ifndef MUD_MODULES
#endif

namespace mud
{
#if 0
	MUD_GFX_EDIT_EXPORT void painter_edit(Widget& parent, VisuPainter& painter);
	MUD_GFX_EDIT_EXPORT void painter_panel(Widget& parent, VisuScene& scene);

#endif

	MUD_GFX_EDIT_EXPORT void space_axes(Gnode& parent);

	MUD_GFX_EDIT_EXPORT void animation_edit(Widget& parent, Animated& animated);

	MUD_GFX_EDIT_EXPORT void asset_browser(Widget& parent, GfxSystem& gfx_system);

	MUD_GFX_EDIT_EXPORT void edit_viewer_filters(Widget& parent, Viewer& viewer);

	MUD_GFX_EDIT_EXPORT void panel_gfx_stats(Widget& parent);
	MUD_GFX_EDIT_EXPORT void edit_gfx_system(Widget& parent, GfxSystem& system);
	
	MUD_GFX_EDIT_EXPORT void gfx_editor(Widget& parent, GfxSystem& system);

	MUD_GFX_EDIT_EXPORT void declare_gfx_edit();
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	MUD_GFX_EDIT_EXPORT void particle_edit(Widget& parent, GfxSystem& system, ParticleFlow& generator);
	MUD_GFX_EDIT_EXPORT void particle_edit(Widget& parent, GfxSystem& system, Call& particles);
	MUD_GFX_EDIT_EXPORT void particle_editor(Widget& parent, GfxSystem& system);
}



namespace mud
{
	MUD_GFX_EDIT_EXPORT void prefab_edit(Widget& parent, GfxSystem& gfx_system, PrefabNode& node, PrefabNode*& selected);
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <cstdint>
#include <stl/vector.h>
#endif


namespace mud
{
    // Exported types
    
    
}

