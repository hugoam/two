#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <refl/Forward.h>
#include <srlz/Forward.h>
#include <lang/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>
#include <ui/Forward.h>
#include <uio/Forward.h>
#include <gfx/Forward.h>
#include <gfx-pbr/Forward.h>

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
