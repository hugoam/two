#include <infra/Api.h>
#include <tree/Api.h>
#include <type/Api.h>
#include <refl/Api.h>
#include <srlz/Api.h>
#include <lang/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>
#include <uio/Api.h>
#include <gfx/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-ui/Api.h>
#include <gfx-edit/Api.h>
#include <tool/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// EditContext
	mud::UndoTool* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_undo_tool(mud::EditContext* self) {
		return &self->m_undo_tool;
	}
	mud::RedoTool* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_redo_tool(mud::EditContext* self) {
		return &self->m_redo_tool;
	}
	mud::Plane* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_work_plane(mud::EditContext* self) {
		static mud::Plane temp;
		return (temp = self->m_work_plane, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_EditContext_set_work_plane(mud::EditContext* self, mud::Plane* value) {
		self->m_work_plane = *value;
	}
	mud::TranslateTool* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_translate_tool(mud::EditContext* self) {
		return &self->m_translate_tool;
	}
	mud::RotateTool* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_rotate_tool(mud::EditContext* self) {
		return &self->m_rotate_tool;
	}
	mud::ScaleTool* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_scale_tool(mud::EditContext* self) {
		return &self->m_scale_tool;
	}
	mud::Viewer* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_viewer(mud::EditContext* self) {
		return self->m_viewer;
	}
	void EMSCRIPTEN_KEEPALIVE mud_EditContext_set_viewer(mud::EditContext* self, mud::Viewer* value) {
		self->m_viewer = value;
	}
	mud::ViewportTool* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_tool(mud::EditContext* self) {
		return self->m_tool;
	}
	void EMSCRIPTEN_KEEPALIVE mud_EditContext_set_tool(mud::EditContext* self, mud::ViewportTool* value) {
		self->m_tool = value;
	}
	mud::SpatialTool* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_spatial_tool(mud::EditContext* self) {
		return self->m_spatial_tool;
	}
	void EMSCRIPTEN_KEEPALIVE mud_EditContext_set_spatial_tool(mud::EditContext* self, mud::SpatialTool* value) {
		self->m_spatial_tool = value;
	}
	mud::Brush* EMSCRIPTEN_KEEPALIVE mud_EditContext_get_brush(mud::EditContext* self) {
		return self->m_brush;
	}
	void EMSCRIPTEN_KEEPALIVE mud_EditContext_set_brush(mud::EditContext* self, mud::Brush* value) {
		self->m_brush = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_EditContext___destroy__(mud::EditContext* self) {
		delete self;
	}
	// EditorAction
	void EMSCRIPTEN_KEEPALIVE mud_EditorAction___destroy__(mud::EditorAction* self) {
		delete self;
	}
	// Gizmo
	mud::Gizmo* EMSCRIPTEN_KEEPALIVE mud_Gizmo_Gizmo_0() {
		return new mud::Gizmo();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Gizmo___destroy__(mud::Gizmo* self) {
		delete self;
	}
	// Tool
	mud::Type* EMSCRIPTEN_KEEPALIVE mud_Tool_get_type(mud::Tool* self) {
		return &self->m_type;
	}
	mud::ToolContext* EMSCRIPTEN_KEEPALIVE mud_Tool_get_context(mud::Tool* self) {
		return &self->m_context;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Tool_get_name(mud::Tool* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Tool_set_name(mud::Tool* self, const char* value) {
		self->m_name = value;
	}
	mud::ToolState EMSCRIPTEN_KEEPALIVE mud_Tool_get_state(mud::Tool* self) {
		return self->m_state;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Tool_set_state(mud::Tool* self, mud::ToolState value) {
		self->m_state = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Tool___destroy__(mud::Tool* self) {
		delete self;
	}
	// ToolContext
	mud::ToolContext* EMSCRIPTEN_KEEPALIVE mud_ToolContext_ToolContext_0() {
		return new mud::ToolContext();
	}
	void EMSCRIPTEN_KEEPALIVE mud_ToolContext___destroy__(mud::ToolContext* self) {
		delete self;
	}
	// ToolOption
	void EMSCRIPTEN_KEEPALIVE mud_ToolOption___destroy__(mud::ToolOption* self) {
		delete self;
	}
	// RedoTool
	void EMSCRIPTEN_KEEPALIVE mud_RedoTool___destroy__(mud::RedoTool* self) {
		delete self;
	}
	// ViewportTool
	void EMSCRIPTEN_KEEPALIVE mud_ViewportTool___destroy__(mud::ViewportTool* self) {
		delete self;
	}
	// SpatialTool
	void EMSCRIPTEN_KEEPALIVE mud_SpatialTool___destroy__(mud::SpatialTool* self) {
		delete self;
	}
	// Brush
	void EMSCRIPTEN_KEEPALIVE mud_Brush___destroy__(mud::Brush* self) {
		delete self;
	}
	// CircleBrush
	mud::CircleBrush* EMSCRIPTEN_KEEPALIVE mud_CircleBrush_CircleBrush_1(mud::ToolContext* context) {
		return new mud::CircleBrush(*context);
	}
	mud::Creator* EMSCRIPTEN_KEEPALIVE mud_CircleBrush_get_creator(mud::CircleBrush* self) {
		return &self->m_creator;
	}
	float EMSCRIPTEN_KEEPALIVE mud_CircleBrush_get_radius(mud::CircleBrush* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_CircleBrush_set_radius(mud::CircleBrush* self, float value) {
		self->m_radius = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_CircleBrush_get_maxSpotRadius(mud::CircleBrush* self) {
		return self->m_maxSpotRadius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_CircleBrush_set_maxSpotRadius(mud::CircleBrush* self, float value) {
		self->m_maxSpotRadius = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_CircleBrush___destroy__(mud::CircleBrush* self) {
		delete self;
	}
	// PlaceBrush
	mud::PlaceBrush* EMSCRIPTEN_KEEPALIVE mud_PlaceBrush_PlaceBrush_1(mud::ToolContext* context) {
		return new mud::PlaceBrush(*context);
	}
	mud::Creator* EMSCRIPTEN_KEEPALIVE mud_PlaceBrush_get_creator(mud::PlaceBrush* self) {
		return &self->m_creator;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PlaceBrush___destroy__(mud::PlaceBrush* self) {
		delete self;
	}
	// PlaneSnapOption
	void EMSCRIPTEN_KEEPALIVE mud_PlaneSnapOption___destroy__(mud::PlaneSnapOption* self) {
		delete self;
	}
	// ScriptedBrush
	mud::ScriptedBrush* EMSCRIPTEN_KEEPALIVE mud_ScriptedBrush_ScriptedBrush_2(mud::ToolContext* context, mud::Script* script) {
		return new mud::ScriptedBrush(*context, *script);
	}
	mud::Call* EMSCRIPTEN_KEEPALIVE mud_ScriptedBrush_get_call(mud::ScriptedBrush* self) {
		static mud::Call temp;
		return (temp = self->m_call, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ScriptedBrush_set_call(mud::ScriptedBrush* self, mud::Call* value) {
		self->m_call = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ScriptedBrush___destroy__(mud::ScriptedBrush* self) {
		delete self;
	}
	// TransformAction
	void EMSCRIPTEN_KEEPALIVE mud_TransformAction___destroy__(mud::TransformAction* self) {
		delete self;
	}
	// RotateAction
	void EMSCRIPTEN_KEEPALIVE mud_RotateAction___destroy__(mud::RotateAction* self) {
		delete self;
	}
	// TransformTool
	void EMSCRIPTEN_KEEPALIVE mud_TransformTool___destroy__(mud::TransformTool* self) {
		delete self;
	}
	// RotateTool
	void EMSCRIPTEN_KEEPALIVE mud_RotateTool___destroy__(mud::RotateTool* self) {
		delete self;
	}
	// ScaleAction
	void EMSCRIPTEN_KEEPALIVE mud_ScaleAction___destroy__(mud::ScaleAction* self) {
		delete self;
	}
	// ScaleTool
	void EMSCRIPTEN_KEEPALIVE mud_ScaleTool___destroy__(mud::ScaleTool* self) {
		delete self;
	}
	// TranslateAction
	void EMSCRIPTEN_KEEPALIVE mud_TranslateAction___destroy__(mud::TranslateAction* self) {
		delete self;
	}
	// CopyAction
	void EMSCRIPTEN_KEEPALIVE mud_CopyAction___destroy__(mud::CopyAction* self) {
		delete self;
	}
	// CopyTool
	void EMSCRIPTEN_KEEPALIVE mud_CopyTool___destroy__(mud::CopyTool* self) {
		delete self;
	}
	// FrameViewTool
	void EMSCRIPTEN_KEEPALIVE mud_FrameViewTool___destroy__(mud::FrameViewTool* self) {
		delete self;
	}
	// TranslateTool
	void EMSCRIPTEN_KEEPALIVE mud_TranslateTool___destroy__(mud::TranslateTool* self) {
		delete self;
	}
	// UndoTool
	void EMSCRIPTEN_KEEPALIVE mud_UndoTool___destroy__(mud::UndoTool* self) {
		delete self;
	}
	// ViewAction
	void EMSCRIPTEN_KEEPALIVE mud_ViewAction___destroy__(mud::ViewAction* self) {
		delete self;
	}
	// ViewTool
	void EMSCRIPTEN_KEEPALIVE mud_ViewTool___destroy__(mud::ViewTool* self) {
		delete self;
	}
	// WorkPlaneAction
	void EMSCRIPTEN_KEEPALIVE mud_WorkPlaneAction___destroy__(mud::WorkPlaneAction* self) {
		delete self;
	}
	// WorkPlaneTool
	void EMSCRIPTEN_KEEPALIVE mud_WorkPlaneTool___destroy__(mud::WorkPlaneTool* self) {
		delete self;
	}
	// WorldSnapOption
	void EMSCRIPTEN_KEEPALIVE mud_WorldSnapOption___destroy__(mud::WorldSnapOption* self) {
		delete self;
	}
	// ToolState
	mud::ToolState EMSCRIPTEN_KEEPALIVE mud_ToolState_Inactive() {
		return mud::ToolState::Inactive;
	}
	mud::ToolState EMSCRIPTEN_KEEPALIVE mud_ToolState_Done() {
		return mud::ToolState::Done;
	}
	mud::ToolState EMSCRIPTEN_KEEPALIVE mud_ToolState_Active() {
		return mud::ToolState::Active;
	}
	
}


