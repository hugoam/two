#pragma once

#include <gfx-ui/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::ui::OrbitMode>();
    
    
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::SpaceSheet>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::ViewerController>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::Viewer>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::SceneViewer>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::OrbitController>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::TrackballController>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::OrbitControls>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::FreeOrbitController>();
}
