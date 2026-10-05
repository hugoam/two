#pragma once

#include <gfx-ui/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_GFX_UI_EXPORT Type& type<two::ui::OrbitMode>();
    
    
    template <> TWO_GFX_UI_EXPORT Type& type<two::SpaceSheet>();
    template <> TWO_GFX_UI_EXPORT Type& type<two::ViewerController>();
    template <> TWO_GFX_UI_EXPORT Type& type<two::Viewer>();
    template <> TWO_GFX_UI_EXPORT Type& type<two::SceneViewer>();
    template <> TWO_GFX_UI_EXPORT Type& type<two::OrbitController>();
    template <> TWO_GFX_UI_EXPORT Type& type<two::TrackballController>();
    template <> TWO_GFX_UI_EXPORT Type& type<two::OrbitControls>();
    template <> TWO_GFX_UI_EXPORT Type& type<two::FreeOrbitController>();
    template <> TWO_GFX_UI_EXPORT Type& type<two::ViewerBox>();
    template <> TWO_GFX_UI_EXPORT Type& type<two::SceneViewerBox>();
}
