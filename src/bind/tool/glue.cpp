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


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// EditContext
	mud::UndoTool* EMSCRIPTEN_KEEPALIVE EditContext_get_undo_tool(mud::EditContext* self) {
		static mud::UndoTool temp;
		return (temp = self->m_undo_tool, &temp);
	}
	mud::RedoTool* EMSCRIPTEN_KEEPALIVE EditContext_get_redo_tool(mud::EditContext* self) {
		static mud::RedoTool temp;
		return (temp = self->m_redo_tool, &temp);
	}
	mud::Plane* EMSCRIPTEN_KEEPALIVE EditContext_get_work_plane(mud::EditContext* self) {
		static mud::Plane temp;
		return (temp = self->m_work_plane, &temp);
	}
	mud::TranslateTool* EMSCRIPTEN_KEEPALIVE EditContext_get_translate_tool(mud::EditContext* self) {
		static mud::TranslateTool temp;
		return (temp = self->m_translate_tool, &temp);
	}
	mud::RotateTool* EMSCRIPTEN_KEEPALIVE EditContext_get_rotate_tool(mud::EditContext* self) {
		static mud::RotateTool temp;
		return (temp = self->m_rotate_tool, &temp);
	}
	mud::ScaleTool* EMSCRIPTEN_KEEPALIVE EditContext_get_scale_tool(mud::EditContext* self) {
		static mud::ScaleTool temp;
		return (temp = self->m_scale_tool, &temp);
	}
	mud::Viewer* EMSCRIPTEN_KEEPALIVE EditContext_get_viewer(mud::EditContext* self) {
		return self->m_viewer;
	}
	mud::ViewportTool* EMSCRIPTEN_KEEPALIVE EditContext_get_tool(mud::EditContext* self) {
		return self->m_tool;
	}
	mud::SpatialTool* EMSCRIPTEN_KEEPALIVE EditContext_get_spatial_tool(mud::EditContext* self) {
		return self->m_spatial_tool;
	}
	mud::Brush* EMSCRIPTEN_KEEPALIVE EditContext_get_brush(mud::EditContext* self) {
		return self->m_brush;
	}
	void EMSCRIPTEN_KEEPALIVE EditContext___destroy__(mud::EditContext* self) {
		delete self;
	}
	// EditorAction
	void EMSCRIPTEN_KEEPALIVE EditorAction___destroy__(mud::EditorAction* self) {
		delete self;
	}
	// Gizmo
	mud::Gizmo* EMSCRIPTEN_KEEPALIVE Gizmo_Gizmo_0() {
		return new mud::Gizmo();
	}
	void EMSCRIPTEN_KEEPALIVE Gizmo___destroy__(mud::Gizmo* self) {
		delete self;
	}
	// Tool
	mud::Type* EMSCRIPTEN_KEEPALIVE Tool_get_type(mud::Tool* self) {
		return &self->m_type;
	}
	mud::ToolContext* EMSCRIPTEN_KEEPALIVE Tool_get_context(mud::Tool* self) {
		return &self->m_context;
	}
	const char* EMSCRIPTEN_KEEPALIVE Tool_get_name(mud::Tool* self) {
		return self->m_name.c_str();
	}
	mud::ToolState EMSCRIPTEN_KEEPALIVE Tool_get_state(mud::Tool* self) {
		return self->m_state;
	}
	void EMSCRIPTEN_KEEPALIVE Tool___destroy__(mud::Tool* self) {
		delete self;
	}
	// ToolContext
	mud::ToolContext* EMSCRIPTEN_KEEPALIVE ToolContext_ToolContext_0() {
		return new mud::ToolContext();
	}
	void EMSCRIPTEN_KEEPALIVE ToolContext___destroy__(mud::ToolContext* self) {
		delete self;
	}
	// ToolOption
	void EMSCRIPTEN_KEEPALIVE ToolOption___destroy__(mud::ToolOption* self) {
		delete self;
	}
	// RedoTool
	void EMSCRIPTEN_KEEPALIVE RedoTool___destroy__(mud::RedoTool* self) {
		delete self;
	}
	// ViewportTool
	void EMSCRIPTEN_KEEPALIVE ViewportTool___destroy__(mud::ViewportTool* self) {
		delete self;
	}
	// SpatialTool
	void EMSCRIPTEN_KEEPALIVE SpatialTool___destroy__(mud::SpatialTool* self) {
		delete self;
	}
	// Brush
	void EMSCRIPTEN_KEEPALIVE Brush___destroy__(mud::Brush* self) {
		delete self;
	}
	// CircleBrush
	mud::CircleBrush* EMSCRIPTEN_KEEPALIVE CircleBrush_CircleBrush_1(mud::ToolContext* context) {
		return new mud::CircleBrush(*context);
	}
	mud::Creator* EMSCRIPTEN_KEEPALIVE CircleBrush_get_creator(mud::CircleBrush* self) {
		static mud::Creator temp;
		return (temp = self->m_creator, &temp);
	}
	float EMSCRIPTEN_KEEPALIVE CircleBrush_get_radius(mud::CircleBrush* self) {
		return self->m_radius;
	}
	float EMSCRIPTEN_KEEPALIVE CircleBrush_get_maxSpotRadius(mud::CircleBrush* self) {
		return self->m_maxSpotRadius;
	}
	void EMSCRIPTEN_KEEPALIVE CircleBrush___destroy__(mud::CircleBrush* self) {
		delete self;
	}
	// PlaceBrush
	mud::PlaceBrush* EMSCRIPTEN_KEEPALIVE PlaceBrush_PlaceBrush_1(mud::ToolContext* context) {
		return new mud::PlaceBrush(*context);
	}
	mud::Creator* EMSCRIPTEN_KEEPALIVE PlaceBrush_get_creator(mud::PlaceBrush* self) {
		static mud::Creator temp;
		return (temp = self->m_creator, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE PlaceBrush___destroy__(mud::PlaceBrush* self) {
		delete self;
	}
	// PlaneSnapOption
	void EMSCRIPTEN_KEEPALIVE PlaneSnapOption___destroy__(mud::PlaneSnapOption* self) {
		delete self;
	}
	// ScriptedBrush
	mud::ScriptedBrush* EMSCRIPTEN_KEEPALIVE ScriptedBrush_ScriptedBrush_2(mud::ToolContext* context, mud::Script* script) {
		return new mud::ScriptedBrush(*context, *script);
	}
	mud::Call* EMSCRIPTEN_KEEPALIVE ScriptedBrush_get_call(mud::ScriptedBrush* self) {
		static mud::Call temp;
		return (temp = self->m_call, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ScriptedBrush___destroy__(mud::ScriptedBrush* self) {
		delete self;
	}
	// TransformAction
	void EMSCRIPTEN_KEEPALIVE TransformAction___destroy__(mud::TransformAction* self) {
		delete self;
	}
	// RotateAction
	void EMSCRIPTEN_KEEPALIVE RotateAction___destroy__(mud::RotateAction* self) {
		delete self;
	}
	// TransformTool
	void EMSCRIPTEN_KEEPALIVE TransformTool___destroy__(mud::TransformTool* self) {
		delete self;
	}
	// RotateTool
	void EMSCRIPTEN_KEEPALIVE RotateTool___destroy__(mud::RotateTool* self) {
		delete self;
	}
	// ScaleAction
	void EMSCRIPTEN_KEEPALIVE ScaleAction___destroy__(mud::ScaleAction* self) {
		delete self;
	}
	// ScaleTool
	void EMSCRIPTEN_KEEPALIVE ScaleTool___destroy__(mud::ScaleTool* self) {
		delete self;
	}
	// TranslateAction
	void EMSCRIPTEN_KEEPALIVE TranslateAction___destroy__(mud::TranslateAction* self) {
		delete self;
	}
	// CopyAction
	void EMSCRIPTEN_KEEPALIVE CopyAction___destroy__(mud::CopyAction* self) {
		delete self;
	}
	// CopyTool
	void EMSCRIPTEN_KEEPALIVE CopyTool___destroy__(mud::CopyTool* self) {
		delete self;
	}
	// FrameViewTool
	void EMSCRIPTEN_KEEPALIVE FrameViewTool___destroy__(mud::FrameViewTool* self) {
		delete self;
	}
	// TranslateTool
	void EMSCRIPTEN_KEEPALIVE TranslateTool___destroy__(mud::TranslateTool* self) {
		delete self;
	}
	// UndoTool
	void EMSCRIPTEN_KEEPALIVE UndoTool___destroy__(mud::UndoTool* self) {
		delete self;
	}
	// ViewAction
	void EMSCRIPTEN_KEEPALIVE ViewAction___destroy__(mud::ViewAction* self) {
		delete self;
	}
	// ViewTool
	void EMSCRIPTEN_KEEPALIVE ViewTool___destroy__(mud::ViewTool* self) {
		delete self;
	}
	// WorkPlaneAction
	void EMSCRIPTEN_KEEPALIVE WorkPlaneAction___destroy__(mud::WorkPlaneAction* self) {
		delete self;
	}
	// WorkPlaneTool
	void EMSCRIPTEN_KEEPALIVE WorkPlaneTool___destroy__(mud::WorkPlaneTool* self) {
		delete self;
	}
	// WorldSnapOption
	void EMSCRIPTEN_KEEPALIVE WorldSnapOption___destroy__(mud::WorldSnapOption* self) {
		delete self;
	}
	// ToolState
	mud::ToolState EMSCRIPTEN_KEEPALIVE ToolState_Inactive() {
		return mud::ToolState::Inactive;
	}
	mud::ToolState EMSCRIPTEN_KEEPALIVE ToolState_Done() {
		return mud::ToolState::Done;
	}
	mud::ToolState EMSCRIPTEN_KEEPALIVE ToolState_Active() {
		return mud::ToolState::Active;
	}
	
}


