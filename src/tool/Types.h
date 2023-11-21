#pragma once

#include <tool/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_TOOL_EXPORT Type& type<two::ToolState>();
    
    
    export_ template <> TWO_TOOL_EXPORT Type& type<two::EditorAction>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::ToolContext>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::ToolOption>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::Tool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::ViewportTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::SpatialTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::Gizmo>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::TransformAction>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::TransformTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::TransformGizmo>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::UndoTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::RedoTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::Brush>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::PlaneSnapOption>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::WorldSnapOption>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::PlaceBrush>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::CircleBrush>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::ScriptedBrush>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::TranslateAction>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::TranslateTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::RotateAction>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::RotateTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::ScaleAction>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::ScaleTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::CopyAction>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::CopyTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::ViewAction>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::FrameViewTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::ViewTool>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::Selection>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::EditContext>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::WorkPlaneAction>();
    export_ template <> TWO_TOOL_EXPORT Type& type<two::WorkPlaneTool>();
}
