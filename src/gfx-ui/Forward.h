

#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <tree/Forward.h>
#include <type/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>
#include <ctx/Forward.h>
#include <ui/Forward.h>
#include <gfx/Forward.h>

#ifndef MUD_GFX_UI_EXPORT
#define MUD_GFX_UI_EXPORT MUD_IMPORT
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
	class Object;
    class SpaceSheet;
    struct ViewerStyles;
    class ViewerController;
    class Viewer;
    class SceneViewer;
    class OrbitController;
    class FreeOrbitController;
    class SpaceViewport;
}
