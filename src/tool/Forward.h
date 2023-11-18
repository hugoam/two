#pragma once

#include <infra/Config.h>

#ifndef TWO_TOOL_EXPORT
#define TWO_TOOL_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum class ToolState : unsigned int;


    export_ class EditorAction;
    export_ struct ToolContext;
    export_ class ToolOption;
    export_ class Tool;
    export_ class ViewportTool;
    export_ class SpatialTool;
    export_ class Gizmo;
    export_ class TransformAction;
    export_ class TransformTool;
	export_ class TransformGizmo;
    export_ class ActionStack;
    export_ class UndoTool;
    export_ class RedoTool;
    export_ class Brush;
    export_ class PlaneSnapOption;
    export_ class WorldSnapOption;
    export_ class PlaceBrush;
    export_ class CircleBrush;
    export_ class ScriptedBrush;
    export_ class TranslateAction;
    export_ class TranslateTool;
    export_ class RotateAction;
    export_ class RotateTool;
    export_ class ScaleAction;
    export_ class ScaleTool;
	export_ struct Selection;
    export_ class CopyAction;
    export_ class CopyTool;
    export_ class ViewAction;
    export_ class FrameViewTool;
    export_ class ViewTool;
    export_ struct ViewTools;
    export_ class EditContext;
    export_ class WorkPlaneAction;
    export_ class WorkPlaneTool;
}
