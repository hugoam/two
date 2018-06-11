#pragma once

#include <edit/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
//#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <obj/Types.h>
#include <refl/Types.h>
#include <srlz/Types.h>
#include <lang/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#include <uio/Types.h>
#include <gfx/Types.h>
#include <gfx-pbr/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ToolState>();
    
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::EditContext>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::EditorAction>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::Gizmo>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::Tool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ToolContext>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ToolOption>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ViewerController>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::SceneViewer>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::TransformAction>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ViewAction>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::WorkPlaneAction>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::Viewer>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::SpaceSheet>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::Brush>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::TransformTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::SpatialTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ViewTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::CopyTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::RotateTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ScaleTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::TranslateTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::RotateAction>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ScaleAction>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::TranslateAction>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::RedoTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::UndoTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ViewportTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::WorkPlaneTool>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::PlaneSnapOption>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::WorldSnapOption>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::CopyAction>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::CircleBrush>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::PlaceBrush>();
    export_ template <> MUD_EDIT_EXPORT Type& type<mud::ScriptedBrush>();
}
