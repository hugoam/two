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

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// EditContext
	mud::Type* DECL mud_EditContext__type() {
		return &mud::type<mud::EditContext>();
	}
	mud::UndoTool* DECL mud_EditContext__get_undo_tool(mud::EditContext* self) {
		return &self->m_undo_tool;
	}
	mud::RedoTool* DECL mud_EditContext__get_redo_tool(mud::EditContext* self) {
		return &self->m_redo_tool;
	}
	mud::Plane* DECL mud_EditContext__get_work_plane(mud::EditContext* self) {
		return &self->m_work_plane;
	}
	void DECL mud_EditContext__set_work_plane(mud::EditContext* self, mud::Plane* value) {
		self->m_work_plane = *value;
	}
	mud::TranslateTool* DECL mud_EditContext__get_translate_tool(mud::EditContext* self) {
		return &self->m_translate_tool;
	}
	mud::RotateTool* DECL mud_EditContext__get_rotate_tool(mud::EditContext* self) {
		return &self->m_rotate_tool;
	}
	mud::ScaleTool* DECL mud_EditContext__get_scale_tool(mud::EditContext* self) {
		return &self->m_scale_tool;
	}
	mud::Viewer* DECL mud_EditContext__get_viewer(mud::EditContext* self) {
		return self->m_viewer;
	}
	void DECL mud_EditContext__set_viewer(mud::EditContext* self, mud::Viewer* value) {
		self->m_viewer = value;
	}
	mud::ViewportTool* DECL mud_EditContext__get_tool(mud::EditContext* self) {
		return self->m_tool;
	}
	void DECL mud_EditContext__set_tool(mud::EditContext* self, mud::ViewportTool* value) {
		self->m_tool = value;
	}
	mud::SpatialTool* DECL mud_EditContext__get_spatial_tool(mud::EditContext* self) {
		return self->m_spatial_tool;
	}
	void DECL mud_EditContext__set_spatial_tool(mud::EditContext* self, mud::SpatialTool* value) {
		self->m_spatial_tool = value;
	}
	mud::Brush* DECL mud_EditContext__get_brush(mud::EditContext* self) {
		return self->m_brush;
	}
	void DECL mud_EditContext__set_brush(mud::EditContext* self, mud::Brush* value) {
		self->m_brush = value;
	}
	void DECL mud_EditContext__destroy(mud::EditContext* self) {
		delete self;
	}
	// EditorAction
	mud::Type* DECL mud_EditorAction__type() {
		return &mud::type<mud::EditorAction>();
	}
	void DECL mud_EditorAction__destroy(mud::EditorAction* self) {
		delete self;
	}
	// Gizmo
	mud::Type* DECL mud_Gizmo__type() {
		return &mud::type<mud::Gizmo>();
	}
	void DECL mud_Gizmo__destroy(mud::Gizmo* self) {
		delete self;
	}
	// Tool
	mud::Type* DECL mud_Tool__type() {
		return &mud::type<mud::Tool>();
	}
	mud::Type* DECL mud_Tool__get_type(mud::Tool* self) {
		return &self->m_type;
	}
	mud::ToolContext* DECL mud_Tool__get_context(mud::Tool* self) {
		return &self->m_context;
	}
	const char* DECL mud_Tool__get_name(mud::Tool* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Tool__set_name(mud::Tool* self, const char* value) {
		self->m_name = value;
	}
	mud::ToolState DECL mud_Tool__get_state(mud::Tool* self) {
		return self->m_state;
	}
	void DECL mud_Tool__set_state(mud::Tool* self, mud::ToolState value) {
		self->m_state = value;
	}
	void DECL mud_Tool__destroy(mud::Tool* self) {
		delete self;
	}
	// ToolContext
	mud::Type* DECL mud_ToolContext__type() {
		return &mud::type<mud::ToolContext>();
	}
	mud::ToolContext* DECL mud_ToolContext__construct_0() {
		return new mud::ToolContext();
	}
	void DECL mud_ToolContext__destroy(mud::ToolContext* self) {
		delete self;
	}
	// ToolOption
	mud::Type* DECL mud_ToolOption__type() {
		return &mud::type<mud::ToolOption>();
	}
	void DECL mud_ToolOption__destroy(mud::ToolOption* self) {
		delete self;
	}
	// Brush
	mud::Type* DECL mud_Brush__type() {
		return &mud::type<mud::Brush>();
	}
	void DECL mud_Brush__destroy(mud::Brush* self) {
		delete self;
	}
	// CircleBrush
	mud::Type* DECL mud_CircleBrush__type() {
		return &mud::type<mud::CircleBrush>();
	}
	mud::CircleBrush* DECL mud_CircleBrush__construct_1(mud::ToolContext* context) {
		return new mud::CircleBrush(*context);
	}
	mud::Creator* DECL mud_CircleBrush__get_creator(mud::CircleBrush* self) {
		return &self->m_creator;
	}
	float DECL mud_CircleBrush__get_radius(mud::CircleBrush* self) {
		return self->m_radius;
	}
	void DECL mud_CircleBrush__set_radius(mud::CircleBrush* self, float value) {
		self->m_radius = value;
	}
	float DECL mud_CircleBrush__get_maxSpotRadius(mud::CircleBrush* self) {
		return self->m_maxSpotRadius;
	}
	void DECL mud_CircleBrush__set_maxSpotRadius(mud::CircleBrush* self, float value) {
		self->m_maxSpotRadius = value;
	}
	void DECL mud_CircleBrush__destroy(mud::CircleBrush* self) {
		delete self;
	}
	// CopyAction
	mud::Type* DECL mud_CopyAction__type() {
		return &mud::type<mud::CopyAction>();
	}
	void DECL mud_CopyAction__destroy(mud::CopyAction* self) {
		delete self;
	}
	// CopyTool
	mud::Type* DECL mud_CopyTool__type() {
		return &mud::type<mud::CopyTool>();
	}
	void DECL mud_CopyTool__destroy(mud::CopyTool* self) {
		delete self;
	}
	// FrameViewTool
	mud::Type* DECL mud_FrameViewTool__type() {
		return &mud::type<mud::FrameViewTool>();
	}
	void DECL mud_FrameViewTool__destroy(mud::FrameViewTool* self) {
		delete self;
	}
	// PlaceBrush
	mud::Type* DECL mud_PlaceBrush__type() {
		return &mud::type<mud::PlaceBrush>();
	}
	mud::PlaceBrush* DECL mud_PlaceBrush__construct_1(mud::ToolContext* context) {
		return new mud::PlaceBrush(*context);
	}
	mud::Creator* DECL mud_PlaceBrush__get_creator(mud::PlaceBrush* self) {
		return &self->m_creator;
	}
	void DECL mud_PlaceBrush__destroy(mud::PlaceBrush* self) {
		delete self;
	}
	// PlaneSnapOption
	mud::Type* DECL mud_PlaneSnapOption__type() {
		return &mud::type<mud::PlaneSnapOption>();
	}
	void DECL mud_PlaneSnapOption__destroy(mud::PlaneSnapOption* self) {
		delete self;
	}
	// RedoTool
	mud::Type* DECL mud_RedoTool__type() {
		return &mud::type<mud::RedoTool>();
	}
	void DECL mud_RedoTool__destroy(mud::RedoTool* self) {
		delete self;
	}
	// RotateAction
	mud::Type* DECL mud_RotateAction__type() {
		return &mud::type<mud::RotateAction>();
	}
	void DECL mud_RotateAction__destroy(mud::RotateAction* self) {
		delete self;
	}
	// RotateTool
	mud::Type* DECL mud_RotateTool__type() {
		return &mud::type<mud::RotateTool>();
	}
	void DECL mud_RotateTool__destroy(mud::RotateTool* self) {
		delete self;
	}
	// ScaleAction
	mud::Type* DECL mud_ScaleAction__type() {
		return &mud::type<mud::ScaleAction>();
	}
	void DECL mud_ScaleAction__destroy(mud::ScaleAction* self) {
		delete self;
	}
	// ViewportTool
	mud::Type* DECL mud_ViewportTool__type() {
		return &mud::type<mud::ViewportTool>();
	}
	void DECL mud_ViewportTool__destroy(mud::ViewportTool* self) {
		delete self;
	}
	// SpatialTool
	mud::Type* DECL mud_SpatialTool__type() {
		return &mud::type<mud::SpatialTool>();
	}
	void DECL mud_SpatialTool__destroy(mud::SpatialTool* self) {
		delete self;
	}
	// ScaleTool
	mud::Type* DECL mud_ScaleTool__type() {
		return &mud::type<mud::ScaleTool>();
	}
	void DECL mud_ScaleTool__destroy(mud::ScaleTool* self) {
		delete self;
	}
	// ScriptedBrush
	mud::Type* DECL mud_ScriptedBrush__type() {
		return &mud::type<mud::ScriptedBrush>();
	}
	mud::ScriptedBrush* DECL mud_ScriptedBrush__construct_2(mud::ToolContext* context, mud::Script* script) {
		return new mud::ScriptedBrush(*context, *script);
	}
	mud::Call* DECL mud_ScriptedBrush__get_call(mud::ScriptedBrush* self) {
		return &self->m_call;
	}
	void DECL mud_ScriptedBrush__set_call(mud::ScriptedBrush* self, mud::Call* value) {
		self->m_call = *value;
	}
	void DECL mud_ScriptedBrush__destroy(mud::ScriptedBrush* self) {
		delete self;
	}
	// TransformAction
	mud::Type* DECL mud_TransformAction__type() {
		return &mud::type<mud::TransformAction>();
	}
	void DECL mud_TransformAction__destroy(mud::TransformAction* self) {
		delete self;
	}
	// TransformGizmo
	mud::Type* DECL mud_TransformGizmo__type() {
		return &mud::type<mud::TransformGizmo>();
	}
	void DECL mud_TransformGizmo__destroy(mud::TransformGizmo* self) {
		delete self;
	}
	// TransformTool
	mud::Type* DECL mud_TransformTool__type() {
		return &mud::type<mud::TransformTool>();
	}
	void DECL mud_TransformTool__destroy(mud::TransformTool* self) {
		delete self;
	}
	// TranslateAction
	mud::Type* DECL mud_TranslateAction__type() {
		return &mud::type<mud::TranslateAction>();
	}
	void DECL mud_TranslateAction__destroy(mud::TranslateAction* self) {
		delete self;
	}
	// TranslateTool
	mud::Type* DECL mud_TranslateTool__type() {
		return &mud::type<mud::TranslateTool>();
	}
	void DECL mud_TranslateTool__destroy(mud::TranslateTool* self) {
		delete self;
	}
	// UndoTool
	mud::Type* DECL mud_UndoTool__type() {
		return &mud::type<mud::UndoTool>();
	}
	void DECL mud_UndoTool__destroy(mud::UndoTool* self) {
		delete self;
	}
	// ViewAction
	mud::Type* DECL mud_ViewAction__type() {
		return &mud::type<mud::ViewAction>();
	}
	void DECL mud_ViewAction__destroy(mud::ViewAction* self) {
		delete self;
	}
	// ViewTool
	mud::Type* DECL mud_ViewTool__type() {
		return &mud::type<mud::ViewTool>();
	}
	void DECL mud_ViewTool__destroy(mud::ViewTool* self) {
		delete self;
	}
	// WorkPlaneAction
	mud::Type* DECL mud_WorkPlaneAction__type() {
		return &mud::type<mud::WorkPlaneAction>();
	}
	void DECL mud_WorkPlaneAction__destroy(mud::WorkPlaneAction* self) {
		delete self;
	}
	// WorkPlaneTool
	mud::Type* DECL mud_WorkPlaneTool__type() {
		return &mud::type<mud::WorkPlaneTool>();
	}
	void DECL mud_WorkPlaneTool__destroy(mud::WorkPlaneTool* self) {
		delete self;
	}
	// WorldSnapOption
	mud::Type* DECL mud_WorldSnapOption__type() {
		return &mud::type<mud::WorldSnapOption>();
	}
	void DECL mud_WorldSnapOption__destroy(mud::WorldSnapOption* self) {
		delete self;
	}
	// ToolState
	mud::ToolState DECL mud_ToolState_Inactive() {
		return mud::ToolState::Inactive;
	}
	mud::ToolState DECL mud_ToolState_Done() {
		return mud::ToolState::Done;
	}
	mud::ToolState DECL mud_ToolState_Active() {
		return mud::ToolState::Active;
	}
	
}


