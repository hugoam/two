

#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <tree/Forward.h>
#include <obj/Forward.h>
#include <refl/Forward.h>
#include <srlz/Forward.h>
#include <lang/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>
#include <ctx/Forward.h>
#include <ui/Forward.h>
#include <uio/Forward.h>
#include <gfx/Forward.h>
#include <gfx-pbr/Forward.h>

#ifndef MUD_TOOL_EXPORT
#define MUD_TOOL_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace mud {
namespace ui {

    
    
}
}

namespace glm {

    
    
}

namespace bx {

    
    
}

namespace json11 {

    
    
}

namespace mud {

    enum class ToolState : unsigned int;
    
    
    class EditorAction;
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
    class FrameViewTool;
    class ViewTool;
    struct ViewTools;
    class EditContext;
    class WorkPlaneAction;
    class WorkPlaneTool;
}

namespace mud {
namespace detail {

    
    
}
}

namespace mud {
namespace gfx {

    
    
}
}

namespace bimg {

    
    
}

namespace bgfx {

    
    
}

