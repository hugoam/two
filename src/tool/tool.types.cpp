#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tool;
#else
#include <tool/Types.h>
#include <tool/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_TOOL_EXPORT Type& type<mud::ToolState>() { static Type ty("ToolState", sizeof(mud::ToolState)); return ty; }
    
    
    template <> MUD_TOOL_EXPORT Type& type<mud::EditorAction>() { static Type ty("EditorAction", sizeof(mud::EditorAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ToolContext>() { static Type ty("ToolContext", sizeof(mud::ToolContext)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ToolOption>() { static Type ty("ToolOption", sizeof(mud::ToolOption)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::Tool>() { static Type ty("Tool", sizeof(mud::Tool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ViewportTool>() { static Type ty("ViewportTool", type<mud::Tool>(), sizeof(mud::ViewportTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::SpatialTool>() { static Type ty("SpatialTool", type<mud::ViewportTool>(), sizeof(mud::SpatialTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::Gizmo>() { static Type ty("Gizmo", sizeof(mud::Gizmo)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TransformAction>() { static Type ty("TransformAction", type<mud::EditorAction>(), sizeof(mud::TransformAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TransformTool>() { static Type ty("TransformTool", type<mud::SpatialTool>(), sizeof(mud::TransformTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TransformGizmo>() { static Type ty("TransformGizmo", type<mud::Gizmo>(), sizeof(mud::TransformGizmo)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::UndoTool>() { static Type ty("UndoTool", type<mud::Tool>(), sizeof(mud::UndoTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::RedoTool>() { static Type ty("RedoTool", type<mud::Tool>(), sizeof(mud::RedoTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::Brush>() { static Type ty("Brush", type<mud::SpatialTool>(), sizeof(mud::Brush)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::PlaneSnapOption>() { static Type ty("PlaneSnapOption", type<mud::ToolOption>(), sizeof(mud::PlaneSnapOption)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::WorldSnapOption>() { static Type ty("WorldSnapOption", type<mud::ToolOption>(), sizeof(mud::WorldSnapOption)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::PlaceBrush>() { static Type ty("PlaceBrush", type<mud::Brush>(), sizeof(mud::PlaceBrush)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::CircleBrush>() { static Type ty("CircleBrush", type<mud::Brush>(), sizeof(mud::CircleBrush)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ScriptedBrush>() { static Type ty("ScriptedBrush", type<mud::Brush>(), sizeof(mud::ScriptedBrush)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TranslateAction>() { static Type ty("TranslateAction", type<mud::TransformAction>(), sizeof(mud::TranslateAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TranslateTool>() { static Type ty("TranslateTool", type<mud::TransformTool>(), sizeof(mud::TranslateTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::RotateAction>() { static Type ty("RotateAction", type<mud::TransformAction>(), sizeof(mud::RotateAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::RotateTool>() { static Type ty("RotateTool", type<mud::TransformTool>(), sizeof(mud::RotateTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ScaleAction>() { static Type ty("ScaleAction", type<mud::TransformAction>(), sizeof(mud::ScaleAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ScaleTool>() { static Type ty("ScaleTool", type<mud::TransformTool>(), sizeof(mud::ScaleTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::CopyAction>() { static Type ty("CopyAction", type<mud::TranslateAction>(), sizeof(mud::CopyAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::CopyTool>() { static Type ty("CopyTool", type<mud::TransformTool>(), sizeof(mud::CopyTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ViewAction>() { static Type ty("ViewAction", type<mud::EditorAction>(), sizeof(mud::ViewAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::FrameViewTool>() { static Type ty("FrameViewTool", type<mud::ViewportTool>(), sizeof(mud::FrameViewTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ViewTool>() { static Type ty("ViewTool", type<mud::ViewportTool>(), sizeof(mud::ViewTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::Selection>() { static Type ty("Selection", sizeof(mud::Selection)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::EditContext>() { static Type ty("EditContext", sizeof(mud::EditContext)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::WorkPlaneAction>() { static Type ty("WorkPlaneAction", type<mud::EditorAction>(), sizeof(mud::WorkPlaneAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::WorkPlaneTool>() { static Type ty("WorkPlaneTool", type<mud::Tool>(), sizeof(mud::WorkPlaneTool)); return ty; }
}
