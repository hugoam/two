#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <tree/Forward.h>
#include <type/Forward.h>
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

#ifndef TWO_TOOL_EXPORT
#define TWO_TOOL_EXPORT TWO_IMPORT
#endif

namespace two
{
    enum class ToolState : unsigned int;
    
    
    class EditorAction;
    struct ToolContext;
    class ToolOption;
    class Tool;
    class ViewportTool;
    class SpatialTool;
    class Gizmo;
    class TransformAction;
    class TransformTool;
	class TransformGizmo;
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
	struct Selection;
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
