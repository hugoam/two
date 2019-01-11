#include <tool/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_tool)
{
    
    // Enums
    enum_<mud::ToolState>("mud::ToolState")
        .value("Inactive", mud::ToolState::Inactive)
        .value("Done", mud::ToolState::Done)
        .value("Active", mud::ToolState::Active)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::Gizmo>("Gizmo")
        ;
    value_object<mud::ToolContext>("ToolContext")
        ;
    
    // Classes
    class_<mud::EditContext>("EditContext")
        .property("undo_tool", &mud::EditContext::m_undo_tool)
        .property("redo_tool", &mud::EditContext::m_redo_tool)
        .property("work_plane", &mud::EditContext::m_work_plane)
        .property("translate_tool", &mud::EditContext::m_translate_tool)
        .property("rotate_tool", &mud::EditContext::m_rotate_tool)
        .property("scale_tool", &mud::EditContext::m_scale_tool)
        .property("viewer", &mud::EditContext::m_viewer)
        .property("tool", &mud::EditContext::m_tool)
        .property("spatial_tool", &mud::EditContext::m_spatial_tool)
        .property("brush", &mud::EditContext::m_brush)
        ;
    class_<mud::EditorAction>("EditorAction")
        ;
    class_<mud::Tool>("Tool")
        .property("type", &mud::Tool::m_type)
        .property("context", &mud::Tool::m_context)
        .property("name", &mud::Tool::m_name)
        .property("state", &mud::Tool::m_state)
        ;
    class_<mud::ToolOption>("ToolOption")
        ;
    class_<mud::RedoTool>("RedoTool")
        ;
    class_<mud::ViewportTool>("ViewportTool")
        ;
    class_<mud::SpatialTool>("SpatialTool")
        ;
    class_<mud::Brush>("Brush")
        ;
    class_<mud::CircleBrush>("CircleBrush")
        .constructor<mud::ToolContext&>()
        .property("creator", &mud::CircleBrush::m_creator)
        .property("radius", &mud::CircleBrush::m_radius)
        .property("maxSpotRadius", &mud::CircleBrush::m_maxSpotRadius)
        ;
    class_<mud::PlaceBrush>("PlaceBrush")
        .constructor<mud::ToolContext&>()
        .property("creator", &mud::PlaceBrush::m_creator)
        ;
    class_<mud::PlaneSnapOption>("PlaneSnapOption")
        ;
    class_<mud::ScriptedBrush>("ScriptedBrush")
        .constructor<mud::ToolContext&, mud::Script&>()
        .property("call", &mud::ScriptedBrush::m_call)
        ;
    class_<mud::TransformAction>("TransformAction")
        ;
    class_<mud::RotateAction>("RotateAction")
        ;
    class_<mud::TransformTool>("TransformTool")
        ;
    class_<mud::RotateTool>("RotateTool")
        ;
    class_<mud::ScaleAction>("ScaleAction")
        ;
    class_<mud::ScaleTool>("ScaleTool")
        ;
    class_<mud::TranslateAction>("TranslateAction")
        ;
    class_<mud::CopyAction>("CopyAction")
        ;
    class_<mud::CopyTool>("CopyTool")
        ;
    class_<mud::FrameViewTool>("FrameViewTool")
        ;
    class_<mud::TranslateTool>("TranslateTool")
        ;
    class_<mud::UndoTool>("UndoTool")
        ;
    class_<mud::ViewAction>("ViewAction")
        ;
    class_<mud::ViewTool>("ViewTool")
        ;
    class_<mud::WorkPlaneAction>("WorkPlaneAction")
        ;
    class_<mud::WorkPlaneTool>("WorkPlaneTool")
        ;
    class_<mud::WorldSnapOption>("WorldSnapOption")
        ;
    
    // Functions
    
}
