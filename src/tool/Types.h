#pragma once

#include <tool/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <tree/Types.h>
#include <type/Types.h>
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
#include <gfx-ui/Types.h>
#include <gfx-edit/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ToolState>();
    
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::EditContext>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::EditorAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::Gizmo>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::Tool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ToolContext>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ToolOption>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::RedoTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ViewportTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::SpatialTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::Brush>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::CircleBrush>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::PlaceBrush>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::PlaneSnapOption>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ScriptedBrush>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TransformAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::RotateAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TransformGizmo>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TransformTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::RotateTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ScaleAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ScaleTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TranslateAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::CopyAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::CopyTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::FrameViewTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TranslateTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::UndoTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ViewAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ViewTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::WorkPlaneAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::WorkPlaneTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::WorldSnapOption>();
    
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::EditContext*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::EditorAction*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::Gizmo*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::Tool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::ToolContext*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::ToolOption*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::RedoTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::ViewportTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::SpatialTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::Brush*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::CircleBrush*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::PlaceBrush*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::PlaneSnapOption*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::ScriptedBrush*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::TransformAction*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::RotateAction*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::TransformGizmo*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::TransformTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::RotateTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::ScaleAction*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::ScaleTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::TranslateAction*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::CopyAction*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::CopyTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::FrameViewTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::TranslateTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::UndoTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::ViewAction*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::ViewTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::WorkPlaneAction*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::WorkPlaneTool*>>();
    export_ template <> MUD_TOOL_EXPORT Type& type<vector<mud::WorldSnapOption*>>();
}
