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

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// EditorAction
	two::Type* DECL two_EditorAction__type() {
		return &two::type<two::EditorAction>();
	}
	void DECL two_EditorAction__destroy(two::EditorAction* self) {
		delete self;
	}
	// ToolContext
	two::Type* DECL two_ToolContext__type() {
		return &two::type<two::ToolContext>();
	}
	two::ToolContext* DECL two_ToolContext__construct_0() {
		return new two::ToolContext();
	}
	void DECL two_ToolContext__destroy(two::ToolContext* self) {
		delete self;
	}
	// ToolOption
	two::Type* DECL two_ToolOption__type() {
		return &two::type<two::ToolOption>();
	}
	void DECL two_ToolOption__destroy(two::ToolOption* self) {
		delete self;
	}
	// Tool
	two::Type* DECL two_Tool__type() {
		return &two::type<two::Tool>();
	}
	two::Type* DECL two_Tool__get_type(two::Tool* self) {
		return &self->m_type;
	}
	two::ToolContext* DECL two_Tool__get_context(two::Tool* self) {
		return &self->m_context;
	}
	const char* DECL two_Tool__get_name(two::Tool* self) {
		return self->m_name.c_str();
	}
	void DECL two_Tool__set_name(two::Tool* self, const char* value) {
		self->m_name = value;
	}
	two::ToolState DECL two_Tool__get_state(two::Tool* self) {
		return self->m_state;
	}
	void DECL two_Tool__set_state(two::Tool* self, two::ToolState value) {
		self->m_state = value;
	}
	void DECL two_Tool__destroy(two::Tool* self) {
		delete self;
	}
	// ViewportTool
	two::Type* DECL two_ViewportTool__type() {
		return &two::type<two::ViewportTool>();
	}
	void DECL two_ViewportTool__destroy(two::ViewportTool* self) {
		delete self;
	}
	// SpatialTool
	two::Type* DECL two_SpatialTool__type() {
		return &two::type<two::SpatialTool>();
	}
	void DECL two_SpatialTool__destroy(two::SpatialTool* self) {
		delete self;
	}
	// Gizmo
	two::Type* DECL two_Gizmo__type() {
		return &two::type<two::Gizmo>();
	}
	void DECL two_Gizmo__destroy(two::Gizmo* self) {
		delete self;
	}
	// TransformAction
	two::Type* DECL two_TransformAction__type() {
		return &two::type<two::TransformAction>();
	}
	void DECL two_TransformAction__destroy(two::TransformAction* self) {
		delete self;
	}
	// TransformTool
	two::Type* DECL two_TransformTool__type() {
		return &two::type<two::TransformTool>();
	}
	void DECL two_TransformTool__destroy(two::TransformTool* self) {
		delete self;
	}
	// TransformGizmo
	two::Type* DECL two_TransformGizmo__type() {
		return &two::type<two::TransformGizmo>();
	}
	void DECL two_TransformGizmo__destroy(two::TransformGizmo* self) {
		delete self;
	}
	// UndoTool
	two::Type* DECL two_UndoTool__type() {
		return &two::type<two::UndoTool>();
	}
	void DECL two_UndoTool__destroy(two::UndoTool* self) {
		delete self;
	}
	// RedoTool
	two::Type* DECL two_RedoTool__type() {
		return &two::type<two::RedoTool>();
	}
	void DECL two_RedoTool__destroy(two::RedoTool* self) {
		delete self;
	}
	// Brush
	two::Type* DECL two_Brush__type() {
		return &two::type<two::Brush>();
	}
	void DECL two_Brush__destroy(two::Brush* self) {
		delete self;
	}
	// PlaneSnapOption
	two::Type* DECL two_PlaneSnapOption__type() {
		return &two::type<two::PlaneSnapOption>();
	}
	void DECL two_PlaneSnapOption__destroy(two::PlaneSnapOption* self) {
		delete self;
	}
	// WorldSnapOption
	two::Type* DECL two_WorldSnapOption__type() {
		return &two::type<two::WorldSnapOption>();
	}
	void DECL two_WorldSnapOption__destroy(two::WorldSnapOption* self) {
		delete self;
	}
	// PlaceBrush
	two::Type* DECL two_PlaceBrush__type() {
		return &two::type<two::PlaceBrush>();
	}
	two::PlaceBrush* DECL two_PlaceBrush__construct_1(two::ToolContext* context) {
		return new two::PlaceBrush(*context);
	}
	two::Creator* DECL two_PlaceBrush__get_creator(two::PlaceBrush* self) {
		return &self->m_creator;
	}
	void DECL two_PlaceBrush__destroy(two::PlaceBrush* self) {
		delete self;
	}
	// CircleBrush
	two::Type* DECL two_CircleBrush__type() {
		return &two::type<two::CircleBrush>();
	}
	two::CircleBrush* DECL two_CircleBrush__construct_1(two::ToolContext* context) {
		return new two::CircleBrush(*context);
	}
	two::Creator* DECL two_CircleBrush__get_creator(two::CircleBrush* self) {
		return &self->m_creator;
	}
	float DECL two_CircleBrush__get_radius(two::CircleBrush* self) {
		return self->m_radius;
	}
	void DECL two_CircleBrush__set_radius(two::CircleBrush* self, float value) {
		self->m_radius = value;
	}
	float DECL two_CircleBrush__get_maxSpotRadius(two::CircleBrush* self) {
		return self->m_maxSpotRadius;
	}
	void DECL two_CircleBrush__set_maxSpotRadius(two::CircleBrush* self, float value) {
		self->m_maxSpotRadius = value;
	}
	void DECL two_CircleBrush__destroy(two::CircleBrush* self) {
		delete self;
	}
	// ScriptedBrush
	two::Type* DECL two_ScriptedBrush__type() {
		return &two::type<two::ScriptedBrush>();
	}
	two::ScriptedBrush* DECL two_ScriptedBrush__construct_2(two::ToolContext* context, two::Script* script) {
		return new two::ScriptedBrush(*context, *script);
	}
	two::Call* DECL two_ScriptedBrush__get_call(two::ScriptedBrush* self) {
		return &self->m_call;
	}
	void DECL two_ScriptedBrush__set_call(two::ScriptedBrush* self, two::Call* value) {
		self->m_call = *value;
	}
	void DECL two_ScriptedBrush__destroy(two::ScriptedBrush* self) {
		delete self;
	}
	// TranslateAction
	two::Type* DECL two_TranslateAction__type() {
		return &two::type<two::TranslateAction>();
	}
	void DECL two_TranslateAction__destroy(two::TranslateAction* self) {
		delete self;
	}
	// TranslateTool
	two::Type* DECL two_TranslateTool__type() {
		return &two::type<two::TranslateTool>();
	}
	void DECL two_TranslateTool__destroy(two::TranslateTool* self) {
		delete self;
	}
	// RotateAction
	two::Type* DECL two_RotateAction__type() {
		return &two::type<two::RotateAction>();
	}
	void DECL two_RotateAction__destroy(two::RotateAction* self) {
		delete self;
	}
	// RotateTool
	two::Type* DECL two_RotateTool__type() {
		return &two::type<two::RotateTool>();
	}
	void DECL two_RotateTool__destroy(two::RotateTool* self) {
		delete self;
	}
	// ScaleAction
	two::Type* DECL two_ScaleAction__type() {
		return &two::type<two::ScaleAction>();
	}
	void DECL two_ScaleAction__destroy(two::ScaleAction* self) {
		delete self;
	}
	// ScaleTool
	two::Type* DECL two_ScaleTool__type() {
		return &two::type<two::ScaleTool>();
	}
	void DECL two_ScaleTool__destroy(two::ScaleTool* self) {
		delete self;
	}
	// CopyAction
	two::Type* DECL two_CopyAction__type() {
		return &two::type<two::CopyAction>();
	}
	void DECL two_CopyAction__destroy(two::CopyAction* self) {
		delete self;
	}
	// CopyTool
	two::Type* DECL two_CopyTool__type() {
		return &two::type<two::CopyTool>();
	}
	void DECL two_CopyTool__destroy(two::CopyTool* self) {
		delete self;
	}
	// ViewAction
	two::Type* DECL two_ViewAction__type() {
		return &two::type<two::ViewAction>();
	}
	void DECL two_ViewAction__destroy(two::ViewAction* self) {
		delete self;
	}
	// FrameViewTool
	two::Type* DECL two_FrameViewTool__type() {
		return &two::type<two::FrameViewTool>();
	}
	void DECL two_FrameViewTool__destroy(two::FrameViewTool* self) {
		delete self;
	}
	// ViewTool
	two::Type* DECL two_ViewTool__type() {
		return &two::type<two::ViewTool>();
	}
	void DECL two_ViewTool__destroy(two::ViewTool* self) {
		delete self;
	}
	// Selection
	two::Type* DECL two_Selection__type() {
		return &two::type<two::Selection>();
	}
	two::Selection* DECL two_Selection__construct_0() {
		return new two::Selection();
	}
	void DECL two_Selection__destroy(two::Selection* self) {
		delete self;
	}
	// EditContext
	two::Type* DECL two_EditContext__type() {
		return &two::type<two::EditContext>();
	}
	two::UndoTool* DECL two_EditContext__get_undo_tool(two::EditContext* self) {
		return &self->m_undo_tool;
	}
	two::RedoTool* DECL two_EditContext__get_redo_tool(two::EditContext* self) {
		return &self->m_redo_tool;
	}
	two::Plane* DECL two_EditContext__get_work_plane(two::EditContext* self) {
		return &self->m_work_plane;
	}
	void DECL two_EditContext__set_work_plane(two::EditContext* self, two::Plane* value) {
		self->m_work_plane = *value;
	}
	two::TranslateTool* DECL two_EditContext__get_translate_tool(two::EditContext* self) {
		return &self->m_translate_tool;
	}
	two::RotateTool* DECL two_EditContext__get_rotate_tool(two::EditContext* self) {
		return &self->m_rotate_tool;
	}
	two::ScaleTool* DECL two_EditContext__get_scale_tool(two::EditContext* self) {
		return &self->m_scale_tool;
	}
	two::Viewer* DECL two_EditContext__get_viewer(two::EditContext* self) {
		return self->m_viewer;
	}
	void DECL two_EditContext__set_viewer(two::EditContext* self, two::Viewer* value) {
		self->m_viewer = value;
	}
	two::ViewportTool* DECL two_EditContext__get_tool(two::EditContext* self) {
		return self->m_tool;
	}
	void DECL two_EditContext__set_tool(two::EditContext* self, two::ViewportTool* value) {
		self->m_tool = value;
	}
	two::SpatialTool* DECL two_EditContext__get_spatial_tool(two::EditContext* self) {
		return self->m_spatial_tool;
	}
	void DECL two_EditContext__set_spatial_tool(two::EditContext* self, two::SpatialTool* value) {
		self->m_spatial_tool = value;
	}
	two::Brush* DECL two_EditContext__get_brush(two::EditContext* self) {
		return self->m_brush;
	}
	void DECL two_EditContext__set_brush(two::EditContext* self, two::Brush* value) {
		self->m_brush = value;
	}
	void DECL two_EditContext__destroy(two::EditContext* self) {
		delete self;
	}
	// WorkPlaneAction
	two::Type* DECL two_WorkPlaneAction__type() {
		return &two::type<two::WorkPlaneAction>();
	}
	void DECL two_WorkPlaneAction__destroy(two::WorkPlaneAction* self) {
		delete self;
	}
	// WorkPlaneTool
	two::Type* DECL two_WorkPlaneTool__type() {
		return &two::type<two::WorkPlaneTool>();
	}
	void DECL two_WorkPlaneTool__destroy(two::WorkPlaneTool* self) {
		delete self;
	}
	// ToolState
	two::ToolState DECL two_ToolState_Inactive() {
		return two::ToolState::Inactive;
	}
	two::ToolState DECL two_ToolState_Done() {
		return two::ToolState::Done;
	}
	two::ToolState DECL two_ToolState_Active() {
		return two::ToolState::Active;
	}
	
}


