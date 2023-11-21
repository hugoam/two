#pragma once

#include <infra/Config.h>

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
    export_ class SpaceSheet;
    export_ struct ViewerStyles;
    export_ class ViewerController;
    export_ class Viewer;
    export_ class SceneViewer;
    export_ class OrbitController;
    export_ class TrackballController;
    export_ class FreeOrbitController;
	export_ class OrbitControls;
    export_ class SpaceViewport;
}
