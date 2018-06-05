

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.edit;
#else
#include <edit/Generated/Types.h>
#include <edit/Generated/Module.h>
#include <obj/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_EDIT_EXPORT Type& type<mud::ViewAction::State>() { static Type ty("mud::ViewAction::State"); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ToolState>() { static Type ty("mud::ToolState"); return ty; }
    
    template <> MUD_EDIT_EXPORT Type& type<mud::EditContext>() { static Type ty("EditContext"); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::EditorAction>() { static Type ty("EditorAction"); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::Gizmo>() { static Type ty("Gizmo"); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::Tool>() { static Type ty("Tool"); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ToolContext>() { static Type ty("ToolContext"); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ToolOption>() { static Type ty("ToolOption"); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ViewerController>() { static Type ty("ViewerController"); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::TransformAction>() { static Type ty("TransformAction", type<mud::EditorAction>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ViewAction>() { static Type ty("ViewAction", type<mud::EditorAction>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::WorkPlaneAction>() { static Type ty("WorkPlaneAction", type<mud::EditorAction>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::PlaneSnapOption>() { static Type ty("PlaneSnapOption", type<mud::ToolOption>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::WorldSnapOption>() { static Type ty("WorldSnapOption", type<mud::ToolOption>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::SpatialTool>() { static Type ty("SpatialTool", type<mud::ViewportTool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ViewTool>() { static Type ty("ViewTool", type<mud::ViewportTool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::RedoTool>() { static Type ty("RedoTool", type<mud::Tool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::UndoTool>() { static Type ty("UndoTool", type<mud::Tool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ViewportTool>() { static Type ty("ViewportTool", type<mud::Tool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::WorkPlaneTool>() { static Type ty("WorkPlaneTool", type<mud::Tool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::Brush>() { static Type ty("Brush", type<mud::SpatialTool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::TransformTool>() { static Type ty("TransformTool", type<mud::SpatialTool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::RotateAction>() { static Type ty("RotateAction", type<mud::TransformAction>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ScaleAction>() { static Type ty("ScaleAction", type<mud::TransformAction>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::TranslateAction>() { static Type ty("TranslateAction", type<mud::TransformAction>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::CopyTool>() { static Type ty("CopyTool", type<mud::TransformTool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::RotateTool>() { static Type ty("RotateTool", type<mud::TransformTool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ScaleTool>() { static Type ty("ScaleTool", type<mud::TransformTool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::TranslateTool>() { static Type ty("TranslateTool", type<mud::TransformTool>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::CircleBrush>() { static Type ty("CircleBrush", type<mud::Brush>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::PlaceBrush>() { static Type ty("PlaceBrush", type<mud::Brush>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::ScriptedBrush>() { static Type ty("ScriptedBrush", type<mud::Brush>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::CopyAction>() { static Type ty("CopyAction", type<mud::TranslateAction>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::Viewer>() { static Type ty("Viewer", type<mud::Widget>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::SpaceSheet>() { static Type ty("SpaceSheet", type<mud::RootSheet>()); return ty; }
    template <> MUD_EDIT_EXPORT Type& type<mud::SceneViewer>() { static Type ty("SceneViewer", type<mud::Scene>()); return ty; }
}
