#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <infra/Forward.h>
#include <tree/Forward.h>
#include <type/Forward.h>
#include <ecs/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>
#include <ctx/Forward.h>
#include <ui/Forward.h>
#include <gfx/Forward.h>
#endif

#ifndef TWO_GFX_UI_EXPORT
#define TWO_GFX_UI_EXPORT TWO_IMPORT
#endif

namespace two
{
namespace ui
{
    enum class OrbitMode : int;
    
}
}

namespace two
{
	class Object;
    class SpaceSheet;
    struct ViewerStyles;
    class ViewerController;
    class Viewer;
    class SceneViewer;
    class OrbitController;
    class TrackballController;
    class FreeOrbitController;
	class OrbitControls;
    class SpaceViewport;
}
