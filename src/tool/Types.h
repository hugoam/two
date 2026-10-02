#pragma once

#include <tool/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_TOOL_EXPORT Type& type<two::ToolState>();
    
    
    template <> TWO_TOOL_EXPORT Type& type<two::EditorAction>();
    template <> TWO_TOOL_EXPORT Type& type<two::ToolContext>();
    template <> TWO_TOOL_EXPORT Type& type<two::ToolOption>();
    template <> TWO_TOOL_EXPORT Type& type<two::Tool>();
    template <> TWO_TOOL_EXPORT Type& type<two::ViewportTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::SpatialTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::Gizmo>();
    template <> TWO_TOOL_EXPORT Type& type<two::TransformAction>();
    template <> TWO_TOOL_EXPORT Type& type<two::TransformTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::TransformGizmo>();
    template <> TWO_TOOL_EXPORT Type& type<two::UndoTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::RedoTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::Brush>();
    template <> TWO_TOOL_EXPORT Type& type<two::PlaneSnapOption>();
    template <> TWO_TOOL_EXPORT Type& type<two::WorldSnapOption>();
    template <> TWO_TOOL_EXPORT Type& type<two::PlaceBrush>();
    template <> TWO_TOOL_EXPORT Type& type<two::CircleBrush>();
    template <> TWO_TOOL_EXPORT Type& type<two::ScriptedBrush>();
    template <> TWO_TOOL_EXPORT Type& type<two::TranslateAction>();
    template <> TWO_TOOL_EXPORT Type& type<two::TranslateTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::RotateAction>();
    template <> TWO_TOOL_EXPORT Type& type<two::RotateTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::ScaleAction>();
    template <> TWO_TOOL_EXPORT Type& type<two::ScaleTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::CopyAction>();
    template <> TWO_TOOL_EXPORT Type& type<two::CopyTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::ViewAction>();
    template <> TWO_TOOL_EXPORT Type& type<two::FrameViewTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::ViewTool>();
    template <> TWO_TOOL_EXPORT Type& type<two::Selection>();
    template <> TWO_TOOL_EXPORT Type& type<two::EditContext>();
    template <> TWO_TOOL_EXPORT Type& type<two::WorkPlaneAction>();
    template <> TWO_TOOL_EXPORT Type& type<two::WorkPlaneTool>();
}
