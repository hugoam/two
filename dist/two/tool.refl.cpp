#include <two/tree.refl.h>
#include <two/lang.refl.h>
#include <two/srlz.refl.h>
#include <two/uio.refl.h>
#include <two/gfx.pbr.refl.h>
#include <two/geom.refl.h>
#include <two/ui.refl.h>
#include <two/gfx.refl.h>
#include <two/infra.refl.h>
#include <two/type.refl.h>
#include <two/refl.refl.h>
#include <two/ctx.refl.h>
#include <two/gfx.ui.refl.h>
#include <two/tool.h>
#include <two/refl.h>
#include <two/math.refl.h>
#include <two/tool.refl.h>
#include <two/infra.h>
#include <two/type.h>
#include <two/gfx.edit.refl.h>


#ifdef TWO_MODULES
module two.tool;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace two;

void two_ToolState__to_string(void* val, string& str) { str = g_enu[type<two::ToolState>().m_id]->name(uint32_t((*static_cast<two::ToolState*>(val)))); }
void two_ToolState__to_value(const string& str, void* val) { (*static_cast<two::ToolState*>(val)) = two::ToolState(g_enu[type<two::ToolState>().m_id]->value(str.c_str())); }
void two_ToolContext__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ToolContext(  ); }
void two_ToolContext__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ToolContext((*static_cast<two::ToolContext*>(other))); }
void* two_Tool__get_type(void* object) { return &(*static_cast<two::Tool*>(object)).m_type; }
void* two_Tool__get_context(void* object) { return &(*static_cast<two::Tool*>(object)).m_context; }
void two_PlaceBrush__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::PlaceBrush( *static_cast<two::ToolContext*>(args[0]) ); }
void two_CircleBrush__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::CircleBrush( *static_cast<two::ToolContext*>(args[0]) ); }
void two_ScriptedBrush__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ScriptedBrush( *static_cast<two::ToolContext*>(args[0]), *static_cast<two::Script*>(args[1]) ); }
void two_Selection__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Selection(  ); }
void two_Selection__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Selection((*static_cast<two::Selection*>(other))); }

namespace two
{
	void two_tool_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::ToolState>();
		static Meta meta = { t, &namspc({ "two" }), "ToolState", sizeof(two::ToolState), TypeClass::Enum };
		static cstring ids[] = { "Inactive", "Done", "Active" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::ToolState vars[] = { two::ToolState::Inactive, two::ToolState::Done, two::ToolState::Active};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_ToolState__to_string,
		                           two_ToolState__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// two::EditorAction
	{
		Type& t = type<two::EditorAction>();
		static Meta meta = { t, &namspc({ "two" }), "EditorAction", sizeof(two::EditorAction), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::ToolContext
	{
		Type& t = type<two::ToolContext>();
		static Meta meta = { t, &namspc({ "two" }), "ToolContext", sizeof(two::ToolContext), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ToolContext__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ToolContext__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::ToolOption
	{
		Type& t = type<two::ToolOption>();
		static Meta meta = { t, &namspc({ "two" }), "ToolOption", sizeof(two::ToolOption), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Tool
	{
		Type& t = type<two::Tool>();
		static Meta meta = { t, &namspc({ "two" }), "Tool", sizeof(two::Tool), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Tool__get_type },
			{ t, SIZE_MAX, type<two::ToolContext>(), "context", nullptr, Member::Flags(Member::Value|Member::NonMutable|Member::Link), two_Tool__get_context },
			{ t, offsetof(two::Tool, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Tool, m_state), type<two::ToolState>(), "state", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::ViewportTool
	{
		Type& t = type<two::ViewportTool>();
		static Meta meta = { t, &namspc({ "two" }), "ViewportTool", sizeof(two::ViewportTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Tool>() };
		static size_t bases_offsets[] = { base_offset<two::ViewportTool, two::Tool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::SpatialTool
	{
		Type& t = type<two::SpatialTool>();
		static Meta meta = { t, &namspc({ "two" }), "SpatialTool", sizeof(two::SpatialTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ViewportTool>() };
		static size_t bases_offsets[] = { base_offset<two::SpatialTool, two::ViewportTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Gizmo
	{
		Type& t = type<two::Gizmo>();
		static Meta meta = { t, &namspc({ "two" }), "Gizmo", sizeof(two::Gizmo), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::TransformAction
	{
		Type& t = type<two::TransformAction>();
		static Meta meta = { t, &namspc({ "two" }), "TransformAction", sizeof(two::TransformAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::EditorAction>() };
		static size_t bases_offsets[] = { base_offset<two::TransformAction, two::EditorAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::TransformTool
	{
		Type& t = type<two::TransformTool>();
		static Meta meta = { t, &namspc({ "two" }), "TransformTool", sizeof(two::TransformTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::SpatialTool>() };
		static size_t bases_offsets[] = { base_offset<two::TransformTool, two::SpatialTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::TransformGizmo
	{
		Type& t = type<two::TransformGizmo>();
		static Meta meta = { t, &namspc({ "two" }), "TransformGizmo", sizeof(two::TransformGizmo), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Gizmo>() };
		static size_t bases_offsets[] = { base_offset<two::TransformGizmo, two::Gizmo>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::UndoTool
	{
		Type& t = type<two::UndoTool>();
		static Meta meta = { t, &namspc({ "two" }), "UndoTool", sizeof(two::UndoTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Tool>() };
		static size_t bases_offsets[] = { base_offset<two::UndoTool, two::Tool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::RedoTool
	{
		Type& t = type<two::RedoTool>();
		static Meta meta = { t, &namspc({ "two" }), "RedoTool", sizeof(two::RedoTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Tool>() };
		static size_t bases_offsets[] = { base_offset<two::RedoTool, two::Tool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Brush
	{
		Type& t = type<two::Brush>();
		static Meta meta = { t, &namspc({ "two" }), "Brush", sizeof(two::Brush), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::SpatialTool>() };
		static size_t bases_offsets[] = { base_offset<two::Brush, two::SpatialTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::PlaneSnapOption
	{
		Type& t = type<two::PlaneSnapOption>();
		static Meta meta = { t, &namspc({ "two" }), "PlaneSnapOption", sizeof(two::PlaneSnapOption), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ToolOption>() };
		static size_t bases_offsets[] = { base_offset<two::PlaneSnapOption, two::ToolOption>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::WorldSnapOption
	{
		Type& t = type<two::WorldSnapOption>();
		static Meta meta = { t, &namspc({ "two" }), "WorldSnapOption", sizeof(two::WorldSnapOption), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ToolOption>() };
		static size_t bases_offsets[] = { base_offset<two::WorldSnapOption, two::ToolOption>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::PlaceBrush
	{
		Type& t = type<two::PlaceBrush>();
		static Meta meta = { t, &namspc({ "two" }), "PlaceBrush", sizeof(two::PlaceBrush), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Brush>() };
		static size_t bases_offsets[] = { base_offset<two::PlaceBrush, two::Brush>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_PlaceBrush__construct_0, { { "context", type<two::ToolContext>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::PlaceBrush, m_creator), type<two::Creator>(), "creator", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, {}, {}, };
	}
	// two::CircleBrush
	{
		Type& t = type<two::CircleBrush>();
		static Meta meta = { t, &namspc({ "two" }), "CircleBrush", sizeof(two::CircleBrush), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Brush>() };
		static size_t bases_offsets[] = { base_offset<two::CircleBrush, two::Brush>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CircleBrush__construct_0, { { "context", type<two::ToolContext>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::CircleBrush, m_creator), type<two::Creator>(), "creator", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::CircleBrush, m_radius), type<float>(), "radius", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CircleBrush, m_maxSpotRadius), type<float>(), "maxSpotRadius", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, {}, {}, };
	}
	// two::ScriptedBrush
	{
		Type& t = type<two::ScriptedBrush>();
		static Meta meta = { t, &namspc({ "two" }), "ScriptedBrush", sizeof(two::ScriptedBrush), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Brush>() };
		static size_t bases_offsets[] = { base_offset<two::ScriptedBrush, two::Brush>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ScriptedBrush__construct_0, { { "context", type<two::ToolContext>(),  }, { "script", type<two::Script>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::ScriptedBrush, m_call), type<two::Call>(), "call", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, {}, {}, };
	}
	// two::TranslateAction
	{
		Type& t = type<two::TranslateAction>();
		static Meta meta = { t, &namspc({ "two" }), "TranslateAction", sizeof(two::TranslateAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::TransformAction>() };
		static size_t bases_offsets[] = { base_offset<two::TranslateAction, two::TransformAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::TranslateTool
	{
		Type& t = type<two::TranslateTool>();
		static Meta meta = { t, &namspc({ "two" }), "TranslateTool", sizeof(two::TranslateTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::TransformTool>() };
		static size_t bases_offsets[] = { base_offset<two::TranslateTool, two::TransformTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::RotateAction
	{
		Type& t = type<two::RotateAction>();
		static Meta meta = { t, &namspc({ "two" }), "RotateAction", sizeof(two::RotateAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::TransformAction>() };
		static size_t bases_offsets[] = { base_offset<two::RotateAction, two::TransformAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::RotateTool
	{
		Type& t = type<two::RotateTool>();
		static Meta meta = { t, &namspc({ "two" }), "RotateTool", sizeof(two::RotateTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::TransformTool>() };
		static size_t bases_offsets[] = { base_offset<two::RotateTool, two::TransformTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::ScaleAction
	{
		Type& t = type<two::ScaleAction>();
		static Meta meta = { t, &namspc({ "two" }), "ScaleAction", sizeof(two::ScaleAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::TransformAction>() };
		static size_t bases_offsets[] = { base_offset<two::ScaleAction, two::TransformAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::ScaleTool
	{
		Type& t = type<two::ScaleTool>();
		static Meta meta = { t, &namspc({ "two" }), "ScaleTool", sizeof(two::ScaleTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::TransformTool>() };
		static size_t bases_offsets[] = { base_offset<two::ScaleTool, two::TransformTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::CopyAction
	{
		Type& t = type<two::CopyAction>();
		static Meta meta = { t, &namspc({ "two" }), "CopyAction", sizeof(two::CopyAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::TranslateAction>() };
		static size_t bases_offsets[] = { base_offset<two::CopyAction, two::TranslateAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::CopyTool
	{
		Type& t = type<two::CopyTool>();
		static Meta meta = { t, &namspc({ "two" }), "CopyTool", sizeof(two::CopyTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::TransformTool>() };
		static size_t bases_offsets[] = { base_offset<two::CopyTool, two::TransformTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::ViewAction
	{
		Type& t = type<two::ViewAction>();
		static Meta meta = { t, &namspc({ "two" }), "ViewAction", sizeof(two::ViewAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::EditorAction>() };
		static size_t bases_offsets[] = { base_offset<two::ViewAction, two::EditorAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::FrameViewTool
	{
		Type& t = type<two::FrameViewTool>();
		static Meta meta = { t, &namspc({ "two" }), "FrameViewTool", sizeof(two::FrameViewTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ViewportTool>() };
		static size_t bases_offsets[] = { base_offset<two::FrameViewTool, two::ViewportTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::ViewTool
	{
		Type& t = type<two::ViewTool>();
		static Meta meta = { t, &namspc({ "two" }), "ViewTool", sizeof(two::ViewTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ViewportTool>() };
		static size_t bases_offsets[] = { base_offset<two::ViewTool, two::ViewportTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Selection
	{
		Type& t = type<two::Selection>();
		static Meta meta = { t, &namspc({ "two" }), "Selection", sizeof(two::Selection), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Selection__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Selection__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::EditContext
	{
		Type& t = type<two::EditContext>();
		static Meta meta = { t, &namspc({ "two" }), "EditContext", sizeof(two::EditContext), TypeClass::Object };
		// bases
		// defaults
		static two::Viewer* viewer_default = nullptr;
		static two::ViewportTool* tool_default = nullptr;
		static two::SpatialTool* spatial_tool_default = nullptr;
		static two::Brush* brush_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::EditContext, m_undo_tool), type<two::UndoTool>(), "undo_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::EditContext, m_redo_tool), type<two::RedoTool>(), "redo_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::EditContext, m_work_plane), type<two::Plane>(), "work_plane", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::EditContext, m_translate_tool), type<two::TranslateTool>(), "translate_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::EditContext, m_rotate_tool), type<two::RotateTool>(), "rotate_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::EditContext, m_scale_tool), type<two::ScaleTool>(), "scale_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::EditContext, m_viewer), type<two::Viewer>(), "viewer", viewer_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::EditContext, m_tool), type<two::ViewportTool>(), "tool", tool_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::EditContext, m_spatial_tool), type<two::SpatialTool>(), "spatial_tool", spatial_tool_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::EditContext, m_brush), type<two::Brush>(), "brush", brush_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::WorkPlaneAction
	{
		Type& t = type<two::WorkPlaneAction>();
		static Meta meta = { t, &namspc({ "two" }), "WorkPlaneAction", sizeof(two::WorkPlaneAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::EditorAction>() };
		static size_t bases_offsets[] = { base_offset<two::WorkPlaneAction, two::EditorAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::WorkPlaneTool
	{
		Type& t = type<two::WorkPlaneTool>();
		static Meta meta = { t, &namspc({ "two" }), "WorkPlaneTool", sizeof(two::WorkPlaneTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Tool>() };
		static size_t bases_offsets[] = { base_offset<two::WorkPlaneTool, two::Tool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::EditorAction>());
		m.m_types.push_back(&type<two::ToolContext>());
		m.m_types.push_back(&type<two::ToolOption>());
		m.m_types.push_back(&type<two::ToolState>());
		m.m_types.push_back(&type<two::Tool>());
		m.m_types.push_back(&type<two::ViewportTool>());
		m.m_types.push_back(&type<two::SpatialTool>());
		m.m_types.push_back(&type<two::Gizmo>());
		m.m_types.push_back(&type<two::TransformAction>());
		m.m_types.push_back(&type<two::TransformTool>());
		m.m_types.push_back(&type<two::TransformGizmo>());
		m.m_types.push_back(&type<two::UndoTool>());
		m.m_types.push_back(&type<two::RedoTool>());
		m.m_types.push_back(&type<two::Brush>());
		m.m_types.push_back(&type<two::PlaneSnapOption>());
		m.m_types.push_back(&type<two::WorldSnapOption>());
		m.m_types.push_back(&type<two::PlaceBrush>());
		m.m_types.push_back(&type<two::CircleBrush>());
		m.m_types.push_back(&type<two::ScriptedBrush>());
		m.m_types.push_back(&type<two::TranslateAction>());
		m.m_types.push_back(&type<two::TranslateTool>());
		m.m_types.push_back(&type<two::RotateAction>());
		m.m_types.push_back(&type<two::RotateTool>());
		m.m_types.push_back(&type<two::ScaleAction>());
		m.m_types.push_back(&type<two::ScaleTool>());
		m.m_types.push_back(&type<two::CopyAction>());
		m.m_types.push_back(&type<two::CopyTool>());
		m.m_types.push_back(&type<two::ViewAction>());
		m.m_types.push_back(&type<two::FrameViewTool>());
		m.m_types.push_back(&type<two::ViewTool>());
		m.m_types.push_back(&type<two::Selection>());
		m.m_types.push_back(&type<two::EditContext>());
		m.m_types.push_back(&type<two::WorkPlaneAction>());
		m.m_types.push_back(&type<two::WorkPlaneTool>());
	}
}

namespace two
{
	two_tool::two_tool()
		: Module("two::tool", { &two_infra::m(), &two_tree::m(), &two_type::m(), &two_refl::m(), &two_srlz::m(), &two_lang::m(), &two_math::m(), &two_geom::m(), &two_ctx::m(), &two_ui::m(), &two_uio::m(), &two_gfx::m(), &two_gfx_pbr::m(), &two_gfx_ui::m(), &two_gfx_edit::m() })
	{
		// setup reflection meta data
		two_tool_meta(*this);
	}
}

#ifdef TWO_TOOL_MODULE
extern "C"
Module& getModule()
{
	return two_tool::m();
}
#endif
