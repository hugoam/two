#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.tool;
#else
#include <tool/Types.h>
#include <tool/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    template <> TWO_TOOL_EXPORT Type& type<two::ToolState>() { static Type ty("ToolState", sizeof(two::ToolState)); return ty; }
    
    
    template <> TWO_TOOL_EXPORT Type& type<two::EditorAction>() { static Type ty("EditorAction", sizeof(two::EditorAction)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::ToolContext>() { static Type ty("ToolContext", sizeof(two::ToolContext)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::ToolOption>() { static Type ty("ToolOption", sizeof(two::ToolOption)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::Tool>() { static Type ty("Tool", sizeof(two::Tool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::ViewportTool>() { static Type ty("ViewportTool", type<two::Tool>(), sizeof(two::ViewportTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::SpatialTool>() { static Type ty("SpatialTool", type<two::ViewportTool>(), sizeof(two::SpatialTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::Gizmo>() { static Type ty("Gizmo", sizeof(two::Gizmo)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::TransformAction>() { static Type ty("TransformAction", type<two::EditorAction>(), sizeof(two::TransformAction)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::TransformTool>() { static Type ty("TransformTool", type<two::SpatialTool>(), sizeof(two::TransformTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::TransformGizmo>() { static Type ty("TransformGizmo", type<two::Gizmo>(), sizeof(two::TransformGizmo)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::UndoTool>() { static Type ty("UndoTool", type<two::Tool>(), sizeof(two::UndoTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::RedoTool>() { static Type ty("RedoTool", type<two::Tool>(), sizeof(two::RedoTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::Brush>() { static Type ty("Brush", type<two::SpatialTool>(), sizeof(two::Brush)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::PlaneSnapOption>() { static Type ty("PlaneSnapOption", type<two::ToolOption>(), sizeof(two::PlaneSnapOption)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::WorldSnapOption>() { static Type ty("WorldSnapOption", type<two::ToolOption>(), sizeof(two::WorldSnapOption)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::PlaceBrush>() { static Type ty("PlaceBrush", type<two::Brush>(), sizeof(two::PlaceBrush)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::CircleBrush>() { static Type ty("CircleBrush", type<two::Brush>(), sizeof(two::CircleBrush)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::ScriptedBrush>() { static Type ty("ScriptedBrush", type<two::Brush>(), sizeof(two::ScriptedBrush)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::TranslateAction>() { static Type ty("TranslateAction", type<two::TransformAction>(), sizeof(two::TranslateAction)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::TranslateTool>() { static Type ty("TranslateTool", type<two::TransformTool>(), sizeof(two::TranslateTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::RotateAction>() { static Type ty("RotateAction", type<two::TransformAction>(), sizeof(two::RotateAction)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::RotateTool>() { static Type ty("RotateTool", type<two::TransformTool>(), sizeof(two::RotateTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::ScaleAction>() { static Type ty("ScaleAction", type<two::TransformAction>(), sizeof(two::ScaleAction)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::ScaleTool>() { static Type ty("ScaleTool", type<two::TransformTool>(), sizeof(two::ScaleTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::CopyAction>() { static Type ty("CopyAction", type<two::TranslateAction>(), sizeof(two::CopyAction)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::CopyTool>() { static Type ty("CopyTool", type<two::TransformTool>(), sizeof(two::CopyTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::ViewAction>() { static Type ty("ViewAction", type<two::EditorAction>(), sizeof(two::ViewAction)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::FrameViewTool>() { static Type ty("FrameViewTool", type<two::ViewportTool>(), sizeof(two::FrameViewTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::ViewTool>() { static Type ty("ViewTool", type<two::ViewportTool>(), sizeof(two::ViewTool)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::Selection>() { static Type ty("Selection", sizeof(two::Selection)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::EditContext>() { static Type ty("EditContext", sizeof(two::EditContext)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::WorkPlaneAction>() { static Type ty("WorkPlaneAction", type<two::EditorAction>(), sizeof(two::WorkPlaneAction)); return ty; }
    template <> TWO_TOOL_EXPORT Type& type<two::WorkPlaneTool>() { static Type ty("WorkPlaneTool", type<two::Tool>(), sizeof(two::WorkPlaneTool)); return ty; }
}
