#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <gfx-ui/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <tree/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#include <gfx/Types.h>
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
