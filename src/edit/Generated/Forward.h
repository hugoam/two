

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <srlz/Generated/Forward.h>
#include <math/Generated/Forward.h>
#include <geom/Generated/Forward.h>
#include <lang/Generated/Forward.h>
#include <ui/Generated/Forward.h>
#include <uio/Generated/Forward.h>
#include <gfx/Generated/Forward.h>
#include <gfx-pbr/Generated/Forward.h>

#ifndef MUD_EDIT_EXPORT
#define MUD_EDIT_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace mud {
namespace ui {

    
    
}
}

namespace glm {

    
    
}

namespace bgfx {

    
    
}

namespace mud {
namespace gfx {

    
    
}
}

namespace json11 {

    
    
}

namespace mud {

    enum class ToolState : unsigned int;
    
    
    class EditorAction;
    struct ViewerStyles;
    class ViewerController;
    class Viewer;
    class SceneViewer;
    class OrbitController;
    class FreeOrbitController;
    struct ToolContext;
    class ToolOption;
    class Tool;
    class ViewportTool;
    class SpatialTool;
    struct Gizmo;
    class TransformAction;
    class TransformTool;
    class ActionStack;
    class UndoTool;
    class RedoTool;
    class Brush;
    class PlaneSnapOption;
    class WorldSnapOption;
    class PlaceBrush;
    class CircleBrush;
    class ScriptedBrush;
    class TranslateAction;
    class TranslateTool;
    class RotateAction;
    class RotateTool;
    class ScaleAction;
    class ScaleTool;
    class CopyAction;
    class CopyTool;
    class ViewAction;
    class ViewTool;
    class EditContext;
    class WorkPlaneAction;
    class WorkPlaneTool;
    class SpaceSheet;
    class SpaceViewport;
}

namespace mud {
namespace detail {

    
    
}
}

namespace bimg {

    
    
}

namespace bx {

    
    
}

