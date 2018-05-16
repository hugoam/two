#pragma once

#include <edit/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <geom/Generated/Types.h>
#include <lang/Generated/Types.h>
#include <ui/Generated/Types.h>
#include <uio/Generated/Types.h>
#include <gfx/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_EDIT_EXPORT Type& type<mud::ToolState>();
    
    template <> MUD_EDIT_EXPORT Type& type<mud::EditContext>();
    template <> MUD_EDIT_EXPORT Type& type<mud::EditorAction>();
    template <> MUD_EDIT_EXPORT Type& type<mud::Gizmo>();
    template <> MUD_EDIT_EXPORT Type& type<mud::Tool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::ToolContext>();
    template <> MUD_EDIT_EXPORT Type& type<mud::ToolOption>();
    template <> MUD_EDIT_EXPORT Type& type<mud::SpatialTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::TransformTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::ViewTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::ViewportTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::UndoTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::RedoTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::WorkPlaneTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::PlaneSnapOption>();
    template <> MUD_EDIT_EXPORT Type& type<mud::WorldSnapOption>();
    template <> MUD_EDIT_EXPORT Type& type<mud::TranslateAction>();
    template <> MUD_EDIT_EXPORT Type& type<mud::RotateAction>();
    template <> MUD_EDIT_EXPORT Type& type<mud::ScaleAction>();
    template <> MUD_EDIT_EXPORT Type& type<mud::PlaceBrush>();
    template <> MUD_EDIT_EXPORT Type& type<mud::CircleBrush>();
    template <> MUD_EDIT_EXPORT Type& type<mud::ScriptedBrush>();
    template <> MUD_EDIT_EXPORT Type& type<mud::TranslateTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::RotateTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::ScaleTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::CopyTool>();
    template <> MUD_EDIT_EXPORT Type& type<mud::TransformAction>();
    template <> MUD_EDIT_EXPORT Type& type<mud::ViewAction>();
    template <> MUD_EDIT_EXPORT Type& type<mud::WorkPlaneAction>();
    template <> MUD_EDIT_EXPORT Type& type<mud::Brush>();
    template <> MUD_EDIT_EXPORT Type& type<mud::CopyAction>();
}
