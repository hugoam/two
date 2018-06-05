

#pragma once

#ifndef MUD_MODULES
#include <edit/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>
#endif

namespace mud
{
    template <> MUD_EDIT_EXPORT Type& type<mud::ViewAction::State>();
    
#ifdef MUD_EDIT_REFLECTION_IMPL
    void edit_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::ToolState>(), &namspc({ "mud" }), "ToolState", sizeof(mud::ToolState), TypeClass::Enum };
        static Enum enu = { type<mud::ToolState>(),
            true,
            { "Inactive", "Done", "Active" },
            { 0, 1, 2 },
            { var(ToolState::Inactive), var(ToolState::Done), var(ToolState::Active) }
        };
        meta_enum<mud::ToolState>();
    }
    
    
    // Sequences
    
    
    
    
        
    // mud::EditContext
    {
        static Meta meta = { type<mud::EditContext>(), &namspc({ "mud" }), "EditContext", sizeof(mud::EditContext), TypeClass::Object };
        static Class cls = { type<mud::EditContext>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::EditContext>();
    }
    
    
        
    // mud::EditorAction
    {
        static Meta meta = { type<mud::EditorAction>(), &namspc({ "mud" }), "EditorAction", sizeof(mud::EditorAction), TypeClass::Object };
        static Class cls = { type<mud::EditorAction>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::EditorAction>();
    }
    
    
    
        
    // mud::Gizmo
    {
        static Meta meta = { type<mud::Gizmo>(), &namspc({ "mud" }), "Gizmo", sizeof(mud::Gizmo), TypeClass::Struct };
        static Class cls = { type<mud::Gizmo>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Gizmo>(), [](Ref ref, Ref other) { new(&val<mud::Gizmo>(ref)) mud::Gizmo(val<mud::Gizmo>(other)); } }
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Gizmo>();
    }
    
    
        
    // mud::Tool
    {
        static Meta meta = { type<mud::Tool>(), &namspc({ "mud" }), "Tool", sizeof(mud::Tool), TypeClass::Object };
        static Class cls = { type<mud::Tool>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Tool>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::None },
                { type<mud::Tool>(), Address(), type<mud::ToolContext>(), "context", var(mud::ToolContext()), Member::Value },
                { type<mud::Tool>(), member_address(&mud::Tool::m_name), type<mud::strung>(), "name", var(mud::strung()), Member::Value },
                { type<mud::Tool>(), member_address(&mud::Tool::m_state), type<mud::ToolState>(), "state", var(mud::ToolState()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Tool>();
    }
    
    
        
    // mud::ToolContext
    {
        static Meta meta = { type<mud::ToolContext>(), &namspc({ "mud" }), "ToolContext", sizeof(mud::ToolContext), TypeClass::Struct };
        static Class cls = { type<mud::ToolContext>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::ToolContext>(), [](Ref ref, Ref other) { new(&val<mud::ToolContext>(ref)) mud::ToolContext(val<mud::ToolContext>(other)); } }
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ToolContext>();
    }
    
    
        
    // mud::ToolOption
    {
        static Meta meta = { type<mud::ToolOption>(), &namspc({ "mud" }), "ToolOption", sizeof(mud::ToolOption), TypeClass::Object };
        static Class cls = { type<mud::ToolOption>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ToolOption>();
    }
    
    
        
    // mud::ViewerController
    {
        static Meta meta = { type<mud::ViewerController>(), &namspc({ "mud" }), "ViewerController", sizeof(mud::ViewerController), TypeClass::Object };
        static Class cls = { type<mud::ViewerController>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ViewerController>();
    }
    
    
    
        
    // mud::TransformAction
    {
        static Meta meta = { type<mud::TransformAction>(), &namspc({ "mud" }), "TransformAction", sizeof(mud::TransformAction), TypeClass::Object };
        static Class cls = { type<mud::TransformAction>(),
            // bases
            { &type<mud::EditorAction>() },
            { base_offset<mud::TransformAction, mud::EditorAction>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::TransformAction>();
    }
    
    
        
    // mud::ViewAction
    {
        static Meta meta = { type<mud::ViewAction>(), &namspc({ "mud" }), "ViewAction", sizeof(mud::ViewAction), TypeClass::Object };
        static Class cls = { type<mud::ViewAction>(),
            // bases
            { &type<mud::EditorAction>() },
            { base_offset<mud::ViewAction, mud::EditorAction>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ViewAction>();
    }
    
    
        
    // mud::WorkPlaneAction
    {
        static Meta meta = { type<mud::WorkPlaneAction>(), &namspc({ "mud" }), "WorkPlaneAction", sizeof(mud::WorkPlaneAction), TypeClass::Object };
        static Class cls = { type<mud::WorkPlaneAction>(),
            // bases
            { &type<mud::EditorAction>() },
            { base_offset<mud::WorkPlaneAction, mud::EditorAction>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::WorkPlaneAction>();
    }
    
    
    
    
        
    // mud::RedoTool
    {
        static Meta meta = { type<mud::RedoTool>(), &namspc({ "mud" }), "RedoTool", sizeof(mud::RedoTool), TypeClass::Object };
        static Class cls = { type<mud::RedoTool>(),
            // bases
            { &type<mud::Tool>() },
            { base_offset<mud::RedoTool, mud::Tool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::RedoTool>();
    }
    
    
        
    // mud::UndoTool
    {
        static Meta meta = { type<mud::UndoTool>(), &namspc({ "mud" }), "UndoTool", sizeof(mud::UndoTool), TypeClass::Object };
        static Class cls = { type<mud::UndoTool>(),
            // bases
            { &type<mud::Tool>() },
            { base_offset<mud::UndoTool, mud::Tool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::UndoTool>();
    }
    
    
        
    // mud::ViewportTool
    {
        static Meta meta = { type<mud::ViewportTool>(), &namspc({ "mud" }), "ViewportTool", sizeof(mud::ViewportTool), TypeClass::Object };
        static Class cls = { type<mud::ViewportTool>(),
            // bases
            { &type<mud::Tool>() },
            { base_offset<mud::ViewportTool, mud::Tool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ViewportTool>();
    }
    
    
        
    // mud::WorkPlaneTool
    {
        static Meta meta = { type<mud::WorkPlaneTool>(), &namspc({ "mud" }), "WorkPlaneTool", sizeof(mud::WorkPlaneTool), TypeClass::Object };
        static Class cls = { type<mud::WorkPlaneTool>(),
            // bases
            { &type<mud::Tool>() },
            { base_offset<mud::WorkPlaneTool, mud::Tool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::WorkPlaneTool>();
    }
    
    
        
    // mud::PlaneSnapOption
    {
        static Meta meta = { type<mud::PlaneSnapOption>(), &namspc({ "mud" }), "PlaneSnapOption", sizeof(mud::PlaneSnapOption), TypeClass::Object };
        static Class cls = { type<mud::PlaneSnapOption>(),
            // bases
            { &type<mud::ToolOption>() },
            { base_offset<mud::PlaneSnapOption, mud::ToolOption>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::PlaneSnapOption>();
    }
    
    
        
    // mud::WorldSnapOption
    {
        static Meta meta = { type<mud::WorldSnapOption>(), &namspc({ "mud" }), "WorldSnapOption", sizeof(mud::WorldSnapOption), TypeClass::Object };
        static Class cls = { type<mud::WorldSnapOption>(),
            // bases
            { &type<mud::ToolOption>() },
            { base_offset<mud::WorldSnapOption, mud::ToolOption>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::WorldSnapOption>();
    }
    
    
        
    // mud::SpatialTool
    {
        static Meta meta = { type<mud::SpatialTool>(), &namspc({ "mud" }), "SpatialTool", sizeof(mud::SpatialTool), TypeClass::Object };
        static Class cls = { type<mud::SpatialTool>(),
            // bases
            { &type<mud::ViewportTool>() },
            { base_offset<mud::SpatialTool, mud::ViewportTool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::SpatialTool>();
    }
    
    
        
    // mud::ViewTool
    {
        static Meta meta = { type<mud::ViewTool>(), &namspc({ "mud" }), "ViewTool", sizeof(mud::ViewTool), TypeClass::Object };
        static Class cls = { type<mud::ViewTool>(),
            // bases
            { &type<mud::ViewportTool>() },
            { base_offset<mud::ViewTool, mud::ViewportTool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ViewTool>();
    }
    
    
        
    // mud::Brush
    {
        static Meta meta = { type<mud::Brush>(), &namspc({ "mud" }), "Brush", sizeof(mud::Brush), TypeClass::Object };
        static Class cls = { type<mud::Brush>(),
            // bases
            { &type<mud::SpatialTool>() },
            { base_offset<mud::Brush, mud::SpatialTool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Brush>();
    }
    
    
        
    // mud::TransformTool
    {
        static Meta meta = { type<mud::TransformTool>(), &namspc({ "mud" }), "TransformTool", sizeof(mud::TransformTool), TypeClass::Object };
        static Class cls = { type<mud::TransformTool>(),
            // bases
            { &type<mud::SpatialTool>() },
            { base_offset<mud::TransformTool, mud::SpatialTool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::TransformTool>();
    }
    
    
        
    // mud::RotateAction
    {
        static Meta meta = { type<mud::RotateAction>(), &namspc({ "mud" }), "RotateAction", sizeof(mud::RotateAction), TypeClass::Object };
        static Class cls = { type<mud::RotateAction>(),
            // bases
            { &type<mud::TransformAction>() },
            { base_offset<mud::RotateAction, mud::TransformAction>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::RotateAction>();
    }
    
    
        
    // mud::ScaleAction
    {
        static Meta meta = { type<mud::ScaleAction>(), &namspc({ "mud" }), "ScaleAction", sizeof(mud::ScaleAction), TypeClass::Object };
        static Class cls = { type<mud::ScaleAction>(),
            // bases
            { &type<mud::TransformAction>() },
            { base_offset<mud::ScaleAction, mud::TransformAction>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ScaleAction>();
    }
    
    
        
    // mud::TranslateAction
    {
        static Meta meta = { type<mud::TranslateAction>(), &namspc({ "mud" }), "TranslateAction", sizeof(mud::TranslateAction), TypeClass::Object };
        static Class cls = { type<mud::TranslateAction>(),
            // bases
            { &type<mud::TransformAction>() },
            { base_offset<mud::TranslateAction, mud::TransformAction>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::TranslateAction>();
    }
    
    
        
    // mud::CopyTool
    {
        static Meta meta = { type<mud::CopyTool>(), &namspc({ "mud" }), "CopyTool", sizeof(mud::CopyTool), TypeClass::Object };
        static Class cls = { type<mud::CopyTool>(),
            // bases
            { &type<mud::TransformTool>() },
            { base_offset<mud::CopyTool, mud::TransformTool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::CopyTool>();
    }
    
    
        
    // mud::RotateTool
    {
        static Meta meta = { type<mud::RotateTool>(), &namspc({ "mud" }), "RotateTool", sizeof(mud::RotateTool), TypeClass::Object };
        static Class cls = { type<mud::RotateTool>(),
            // bases
            { &type<mud::TransformTool>() },
            { base_offset<mud::RotateTool, mud::TransformTool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::RotateTool>();
    }
    
    
        
    // mud::ScaleTool
    {
        static Meta meta = { type<mud::ScaleTool>(), &namspc({ "mud" }), "ScaleTool", sizeof(mud::ScaleTool), TypeClass::Object };
        static Class cls = { type<mud::ScaleTool>(),
            // bases
            { &type<mud::TransformTool>() },
            { base_offset<mud::ScaleTool, mud::TransformTool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ScaleTool>();
    }
    
    
        
    // mud::TranslateTool
    {
        static Meta meta = { type<mud::TranslateTool>(), &namspc({ "mud" }), "TranslateTool", sizeof(mud::TranslateTool), TypeClass::Object };
        static Class cls = { type<mud::TranslateTool>(),
            // bases
            { &type<mud::TransformTool>() },
            { base_offset<mud::TranslateTool, mud::TransformTool>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::TranslateTool>();
    }
    
    
        
    // mud::CircleBrush
    {
        static Meta meta = { type<mud::CircleBrush>(), &namspc({ "mud" }), "CircleBrush", sizeof(mud::CircleBrush), TypeClass::Object };
        static Class cls = { type<mud::CircleBrush>(),
            // bases
            { &type<mud::Brush>() },
            { base_offset<mud::CircleBrush, mud::Brush>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::CircleBrush>(), member_address(&mud::CircleBrush::m_creator), type<mud::Creator>(), "creator", Ref(type<mud::Creator>()), Member::None },
                { type<mud::CircleBrush>(), member_address(&mud::CircleBrush::m_radius), type<float>(), "radius", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::CircleBrush>(), member_address(&mud::CircleBrush::m_maxSpotRadius), type<float>(), "maxSpotRadius", var(float()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::CircleBrush>();
    }
    
    
        
    // mud::PlaceBrush
    {
        static Meta meta = { type<mud::PlaceBrush>(), &namspc({ "mud" }), "PlaceBrush", sizeof(mud::PlaceBrush), TypeClass::Object };
        static Class cls = { type<mud::PlaceBrush>(),
            // bases
            { &type<mud::Brush>() },
            { base_offset<mud::PlaceBrush, mud::Brush>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::PlaceBrush>(), member_address(&mud::PlaceBrush::m_creator), type<mud::Creator>(), "creator", Ref(type<mud::Creator>()), Member::None }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::PlaceBrush>();
    }
    
    
        
    // mud::ScriptedBrush
    {
        static Meta meta = { type<mud::ScriptedBrush>(), &namspc({ "mud" }), "ScriptedBrush", sizeof(mud::ScriptedBrush), TypeClass::Object };
        static Class cls = { type<mud::ScriptedBrush>(),
            // bases
            { &type<mud::Brush>() },
            { base_offset<mud::ScriptedBrush, mud::Brush>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::ScriptedBrush>(), member_address(&mud::ScriptedBrush::m_call), type<mud::Call>(), "call", var(mud::Call()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ScriptedBrush>();
    }
    
    
        
    // mud::CopyAction
    {
        static Meta meta = { type<mud::CopyAction>(), &namspc({ "mud" }), "CopyAction", sizeof(mud::CopyAction), TypeClass::Object };
        static Class cls = { type<mud::CopyAction>(),
            // bases
            { &type<mud::TranslateAction>() },
            { base_offset<mud::CopyAction, mud::TranslateAction>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::CopyAction>();
    }
    
    
        
    // mud::Viewer
    {
        static Meta meta = { type<mud::Viewer>(), &namspc({ "mud" }), "Viewer", sizeof(mud::Viewer), TypeClass::Object };
        static Class cls = { type<mud::Viewer>(),
            // bases
            { &type<mud::Widget>() },
            { base_offset<mud::Viewer, mud::Widget>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link) },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_viewport), type<mud::Viewport>(), "viewport", Ref(type<mud::Viewport>()), Member::None },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_position), type<mud::vec2>(), "position", var(mud::vec2()), Member::Value },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_size), type<mud::vec2>(), "size", var(mud::vec2()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Viewer>();
    }
    
    
        
    // mud::SpaceSheet
    {
        static Meta meta = { type<mud::SpaceSheet>(), &namspc({ "mud" }), "SpaceSheet", sizeof(mud::SpaceSheet), TypeClass::Object };
        static Class cls = { type<mud::SpaceSheet>(),
            // bases
            { &type<mud::RootSheet>() },
            { base_offset<mud::SpaceSheet, mud::RootSheet>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::SpaceSheet>();
    }
    
    
        
    // mud::SceneViewer
    {
        static Meta meta = { type<mud::SceneViewer>(), &namspc({ "mud" }), "SceneViewer", sizeof(mud::SceneViewer), TypeClass::Object };
        static Class cls = { type<mud::SceneViewer>(),
            // bases
            { &type<mud::Scene>(), &type<mud::Viewer>() },
            { base_offset<mud::SceneViewer, mud::Scene>(), base_offset<mud::SceneViewer, mud::Viewer>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::SceneViewer>();
    }
    

    
        m.m_types.push_back(&type<mud::EditContext>());
        m.m_types.push_back(&type<mud::EditorAction>());
        m.m_types.push_back(&type<mud::Gizmo>());
        m.m_types.push_back(&type<mud::Tool>());
        m.m_types.push_back(&type<mud::ToolContext>());
        m.m_types.push_back(&type<mud::ToolOption>());
        m.m_types.push_back(&type<mud::ToolState>());
        m.m_types.push_back(&type<mud::ViewerController>());
        m.m_types.push_back(&type<mud::TransformAction>());
        m.m_types.push_back(&type<mud::ViewAction>());
        m.m_types.push_back(&type<mud::WorkPlaneAction>());
        m.m_types.push_back(&type<mud::RedoTool>());
        m.m_types.push_back(&type<mud::UndoTool>());
        m.m_types.push_back(&type<mud::ViewportTool>());
        m.m_types.push_back(&type<mud::WorkPlaneTool>());
        m.m_types.push_back(&type<mud::PlaneSnapOption>());
        m.m_types.push_back(&type<mud::WorldSnapOption>());
        m.m_types.push_back(&type<mud::SpatialTool>());
        m.m_types.push_back(&type<mud::ViewTool>());
        m.m_types.push_back(&type<mud::Brush>());
        m.m_types.push_back(&type<mud::TransformTool>());
        m.m_types.push_back(&type<mud::RotateAction>());
        m.m_types.push_back(&type<mud::ScaleAction>());
        m.m_types.push_back(&type<mud::TranslateAction>());
        m.m_types.push_back(&type<mud::CopyTool>());
        m.m_types.push_back(&type<mud::RotateTool>());
        m.m_types.push_back(&type<mud::ScaleTool>());
        m.m_types.push_back(&type<mud::TranslateTool>());
        m.m_types.push_back(&type<mud::CircleBrush>());
        m.m_types.push_back(&type<mud::PlaceBrush>());
        m.m_types.push_back(&type<mud::ScriptedBrush>());
        m.m_types.push_back(&type<mud::CopyAction>());
        m.m_types.push_back(&type<mud::Viewer>());
        m.m_types.push_back(&type<mud::SpaceSheet>());
        m.m_types.push_back(&type<mud::SceneViewer>());
    
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::viewer(val<mud::Widget>(args[0]), val<mud::Scene>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "scene", Ref(type<mud::Scene>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "viewer", function_id<mud::Viewer&(*)(mud::Widget&, mud::Scene&)>(&mud::ui::viewer), func, params, Ref(type<mud::Viewer>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::scene_viewer(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "scene_viewer", function_id<mud::SceneViewer&(*)(mud::Widget&, const mud::vec2&)>(&mud::ui::scene_viewer), func, params, Ref(type<mud::SceneViewer>()) };
            m.m_functions.push_back(&f);
        }
    }
#endif

}
