#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tool;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/tree.meta.h>
#include <meta/type.meta.h>
#include <meta/refl.meta.h>
#include <meta/srlz.meta.h>
#include <meta/lang.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
#include <meta/ctx.meta.h>
#include <meta/ui.meta.h>
#include <meta/uio.meta.h>
#include <meta/gfx.meta.h>
#include <meta/gfx.pbr.meta.h>
#include <meta/gfx.ui.meta.h>
#include <meta/gfx.edit.meta.h>
#include <meta/tool.meta.h>
#include <meta/tool.conv.h>
#endif

#include <tool/Api.h>

using namespace mud;

void mud_ToolState__to_string(void* val, string& str) { str = g_enu[type<mud::ToolState>().m_id]->name(uint32_t((*static_cast<mud::ToolState*>(val)))); }
void mud_ToolState__to_value(const string& str, void* val) { (*static_cast<mud::ToolState*>(val)) = mud::ToolState(g_enu[type<mud::ToolState>().m_id]->value(str.c_str())); }
void* mud_Tool__get_type(void* object) { return &(*static_cast<mud::Tool*>(object)).m_type; }
void* mud_Tool__get_context(void* object) { return &(*static_cast<mud::Tool*>(object)).m_context; }
void mud_ToolContext__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ToolContext(  ); }
void mud_ToolContext__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ToolContext((*static_cast<mud::ToolContext*>(other))); }
void mud_CircleBrush__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::CircleBrush( *static_cast<mud::ToolContext*>(args[0]) ); }
void mud_PlaceBrush__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::PlaceBrush( *static_cast<mud::ToolContext*>(args[0]) ); }
void mud_ScriptedBrush__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ScriptedBrush( *static_cast<mud::ToolContext*>(args[0]), *static_cast<mud::Script*>(args[1]) ); }

namespace mud
{
	void mud_tool_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::ToolState>();
		static Meta meta = { t, &namspc({ "mud" }), "ToolState", sizeof(mud::ToolState), TypeClass::Enum };
		static cstring ids[] = { "Inactive", "Done", "Active" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::ToolState vars[] = { mud::ToolState::Inactive, mud::ToolState::Done, mud::ToolState::Active};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_ToolState__to_string,
		                           mud_ToolState__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// mud::EditContext
	{
		Type& t = type<mud::EditContext>();
		static Meta meta = { t, &namspc({ "mud" }), "EditContext", sizeof(mud::EditContext), TypeClass::Object };
		// bases
		// defaults
		static mud::Viewer* viewer_default = nullptr;
		static mud::ViewportTool* tool_default = nullptr;
		static mud::SpatialTool* spatial_tool_default = nullptr;
		static mud::Brush* brush_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::EditContext, m_undo_tool), type<mud::UndoTool>(), "undo_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::EditContext, m_redo_tool), type<mud::RedoTool>(), "redo_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::EditContext, m_work_plane), type<mud::Plane>(), "work_plane", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::EditContext, m_translate_tool), type<mud::TranslateTool>(), "translate_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::EditContext, m_rotate_tool), type<mud::RotateTool>(), "rotate_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::EditContext, m_scale_tool), type<mud::ScaleTool>(), "scale_tool", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::EditContext, m_viewer), type<mud::Viewer>(), "viewer", viewer_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::EditContext, m_tool), type<mud::ViewportTool>(), "tool", tool_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::EditContext, m_spatial_tool), type<mud::SpatialTool>(), "spatial_tool", spatial_tool_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::EditContext, m_brush), type<mud::Brush>(), "brush", brush_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::EditorAction
	{
		Type& t = type<mud::EditorAction>();
		static Meta meta = { t, &namspc({ "mud" }), "EditorAction", sizeof(mud::EditorAction), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Gizmo
	{
		Type& t = type<mud::Gizmo>();
		static Meta meta = { t, &namspc({ "mud" }), "Gizmo", sizeof(mud::Gizmo), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Tool
	{
		Type& t = type<mud::Tool>();
		static Meta meta = { t, &namspc({ "mud" }), "Tool", sizeof(mud::Tool), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Tool__get_type },
			{ t, SIZE_MAX, type<mud::ToolContext>(), "context", nullptr, Member::Flags(Member::Value|Member::NonMutable|Member::Link), mud_Tool__get_context },
			{ t, offsetof(mud::Tool, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Tool, m_state), type<mud::ToolState>(), "state", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::ToolContext
	{
		Type& t = type<mud::ToolContext>();
		static Meta meta = { t, &namspc({ "mud" }), "ToolContext", sizeof(mud::ToolContext), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ToolContext__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ToolContext__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::ToolOption
	{
		Type& t = type<mud::ToolOption>();
		static Meta meta = { t, &namspc({ "mud" }), "ToolOption", sizeof(mud::ToolOption), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Brush
	{
		Type& t = type<mud::Brush>();
		static Meta meta = { t, &namspc({ "mud" }), "Brush", sizeof(mud::Brush), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::SpatialTool>() };
		static size_t bases_offsets[] = { base_offset<mud::Brush, mud::SpatialTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::CircleBrush
	{
		Type& t = type<mud::CircleBrush>();
		static Meta meta = { t, &namspc({ "mud" }), "CircleBrush", sizeof(mud::CircleBrush), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Brush>() };
		static size_t bases_offsets[] = { base_offset<mud::CircleBrush, mud::Brush>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CircleBrush__construct_0, { { "context", type<mud::ToolContext>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::CircleBrush, m_creator), type<mud::Creator>(), "creator", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::CircleBrush, m_radius), type<float>(), "radius", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CircleBrush, m_maxSpotRadius), type<float>(), "maxSpotRadius", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, {}, {}, };
	}
	// mud::PlaceBrush
	{
		Type& t = type<mud::PlaceBrush>();
		static Meta meta = { t, &namspc({ "mud" }), "PlaceBrush", sizeof(mud::PlaceBrush), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Brush>() };
		static size_t bases_offsets[] = { base_offset<mud::PlaceBrush, mud::Brush>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_PlaceBrush__construct_0, { { "context", type<mud::ToolContext>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::PlaceBrush, m_creator), type<mud::Creator>(), "creator", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, {}, {}, };
	}
	// mud::PlaneSnapOption
	{
		Type& t = type<mud::PlaneSnapOption>();
		static Meta meta = { t, &namspc({ "mud" }), "PlaneSnapOption", sizeof(mud::PlaneSnapOption), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ToolOption>() };
		static size_t bases_offsets[] = { base_offset<mud::PlaneSnapOption, mud::ToolOption>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::RedoTool
	{
		Type& t = type<mud::RedoTool>();
		static Meta meta = { t, &namspc({ "mud" }), "RedoTool", sizeof(mud::RedoTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Tool>() };
		static size_t bases_offsets[] = { base_offset<mud::RedoTool, mud::Tool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ScriptedBrush
	{
		Type& t = type<mud::ScriptedBrush>();
		static Meta meta = { t, &namspc({ "mud" }), "ScriptedBrush", sizeof(mud::ScriptedBrush), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Brush>() };
		static size_t bases_offsets[] = { base_offset<mud::ScriptedBrush, mud::Brush>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ScriptedBrush__construct_0, { { "context", type<mud::ToolContext>(),  }, { "script", type<mud::Script>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::ScriptedBrush, m_call), type<mud::Call>(), "call", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, {}, {}, };
	}
	// mud::TransformAction
	{
		Type& t = type<mud::TransformAction>();
		static Meta meta = { t, &namspc({ "mud" }), "TransformAction", sizeof(mud::TransformAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::EditorAction>() };
		static size_t bases_offsets[] = { base_offset<mud::TransformAction, mud::EditorAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::TransformGizmo
	{
		Type& t = type<mud::TransformGizmo>();
		static Meta meta = { t, &namspc({ "mud" }), "TransformGizmo", sizeof(mud::TransformGizmo), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Gizmo>() };
		static size_t bases_offsets[] = { base_offset<mud::TransformGizmo, mud::Gizmo>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ViewportTool
	{
		Type& t = type<mud::ViewportTool>();
		static Meta meta = { t, &namspc({ "mud" }), "ViewportTool", sizeof(mud::ViewportTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Tool>() };
		static size_t bases_offsets[] = { base_offset<mud::ViewportTool, mud::Tool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::SpatialTool
	{
		Type& t = type<mud::SpatialTool>();
		static Meta meta = { t, &namspc({ "mud" }), "SpatialTool", sizeof(mud::SpatialTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ViewportTool>() };
		static size_t bases_offsets[] = { base_offset<mud::SpatialTool, mud::ViewportTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::TransformTool
	{
		Type& t = type<mud::TransformTool>();
		static Meta meta = { t, &namspc({ "mud" }), "TransformTool", sizeof(mud::TransformTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::SpatialTool>() };
		static size_t bases_offsets[] = { base_offset<mud::TransformTool, mud::SpatialTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::CopyTool
	{
		Type& t = type<mud::CopyTool>();
		static Meta meta = { t, &namspc({ "mud" }), "CopyTool", sizeof(mud::CopyTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::TransformTool>() };
		static size_t bases_offsets[] = { base_offset<mud::CopyTool, mud::TransformTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::RotateAction
	{
		Type& t = type<mud::RotateAction>();
		static Meta meta = { t, &namspc({ "mud" }), "RotateAction", sizeof(mud::RotateAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::TransformAction>() };
		static size_t bases_offsets[] = { base_offset<mud::RotateAction, mud::TransformAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::RotateTool
	{
		Type& t = type<mud::RotateTool>();
		static Meta meta = { t, &namspc({ "mud" }), "RotateTool", sizeof(mud::RotateTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::TransformTool>() };
		static size_t bases_offsets[] = { base_offset<mud::RotateTool, mud::TransformTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ScaleAction
	{
		Type& t = type<mud::ScaleAction>();
		static Meta meta = { t, &namspc({ "mud" }), "ScaleAction", sizeof(mud::ScaleAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::TransformAction>() };
		static size_t bases_offsets[] = { base_offset<mud::ScaleAction, mud::TransformAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ScaleTool
	{
		Type& t = type<mud::ScaleTool>();
		static Meta meta = { t, &namspc({ "mud" }), "ScaleTool", sizeof(mud::ScaleTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::TransformTool>() };
		static size_t bases_offsets[] = { base_offset<mud::ScaleTool, mud::TransformTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::TranslateAction
	{
		Type& t = type<mud::TranslateAction>();
		static Meta meta = { t, &namspc({ "mud" }), "TranslateAction", sizeof(mud::TranslateAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::TransformAction>() };
		static size_t bases_offsets[] = { base_offset<mud::TranslateAction, mud::TransformAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::CopyAction
	{
		Type& t = type<mud::CopyAction>();
		static Meta meta = { t, &namspc({ "mud" }), "CopyAction", sizeof(mud::CopyAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::TranslateAction>() };
		static size_t bases_offsets[] = { base_offset<mud::CopyAction, mud::TranslateAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::FrameViewTool
	{
		Type& t = type<mud::FrameViewTool>();
		static Meta meta = { t, &namspc({ "mud" }), "FrameViewTool", sizeof(mud::FrameViewTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ViewportTool>() };
		static size_t bases_offsets[] = { base_offset<mud::FrameViewTool, mud::ViewportTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::TranslateTool
	{
		Type& t = type<mud::TranslateTool>();
		static Meta meta = { t, &namspc({ "mud" }), "TranslateTool", sizeof(mud::TranslateTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::TransformTool>() };
		static size_t bases_offsets[] = { base_offset<mud::TranslateTool, mud::TransformTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::UndoTool
	{
		Type& t = type<mud::UndoTool>();
		static Meta meta = { t, &namspc({ "mud" }), "UndoTool", sizeof(mud::UndoTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Tool>() };
		static size_t bases_offsets[] = { base_offset<mud::UndoTool, mud::Tool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ViewAction
	{
		Type& t = type<mud::ViewAction>();
		static Meta meta = { t, &namspc({ "mud" }), "ViewAction", sizeof(mud::ViewAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::EditorAction>() };
		static size_t bases_offsets[] = { base_offset<mud::ViewAction, mud::EditorAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ViewTool
	{
		Type& t = type<mud::ViewTool>();
		static Meta meta = { t, &namspc({ "mud" }), "ViewTool", sizeof(mud::ViewTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ViewportTool>() };
		static size_t bases_offsets[] = { base_offset<mud::ViewTool, mud::ViewportTool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::WorkPlaneAction
	{
		Type& t = type<mud::WorkPlaneAction>();
		static Meta meta = { t, &namspc({ "mud" }), "WorkPlaneAction", sizeof(mud::WorkPlaneAction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::EditorAction>() };
		static size_t bases_offsets[] = { base_offset<mud::WorkPlaneAction, mud::EditorAction>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::WorkPlaneTool
	{
		Type& t = type<mud::WorkPlaneTool>();
		static Meta meta = { t, &namspc({ "mud" }), "WorkPlaneTool", sizeof(mud::WorkPlaneTool), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Tool>() };
		static size_t bases_offsets[] = { base_offset<mud::WorkPlaneTool, mud::Tool>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::WorldSnapOption
	{
		Type& t = type<mud::WorldSnapOption>();
		static Meta meta = { t, &namspc({ "mud" }), "WorldSnapOption", sizeof(mud::WorldSnapOption), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ToolOption>() };
		static size_t bases_offsets[] = { base_offset<mud::WorldSnapOption, mud::ToolOption>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::EditContext>());
		m.m_types.push_back(&type<mud::EditorAction>());
		m.m_types.push_back(&type<mud::Gizmo>());
		m.m_types.push_back(&type<mud::Tool>());
		m.m_types.push_back(&type<mud::ToolContext>());
		m.m_types.push_back(&type<mud::ToolOption>());
		m.m_types.push_back(&type<mud::ToolState>());
		m.m_types.push_back(&type<mud::CircleBrush>());
		m.m_types.push_back(&type<mud::RedoTool>());
		m.m_types.push_back(&type<mud::SpatialTool>());
		m.m_types.push_back(&type<mud::Brush>());
		m.m_types.push_back(&type<mud::PlaceBrush>());
		m.m_types.push_back(&type<mud::PlaneSnapOption>());
		m.m_types.push_back(&type<mud::ScriptedBrush>());
		m.m_types.push_back(&type<mud::TransformAction>());
		m.m_types.push_back(&type<mud::RotateAction>());
		m.m_types.push_back(&type<mud::TransformGizmo>());
		m.m_types.push_back(&type<mud::TransformTool>());
		m.m_types.push_back(&type<mud::RotateTool>());
		m.m_types.push_back(&type<mud::ScaleTool>());
		m.m_types.push_back(&type<mud::TranslateAction>());
		m.m_types.push_back(&type<mud::CopyAction>());
		m.m_types.push_back(&type<mud::CopyTool>());
		m.m_types.push_back(&type<mud::FrameViewTool>());
		m.m_types.push_back(&type<mud::ScaleAction>());
		m.m_types.push_back(&type<mud::TranslateTool>());
		m.m_types.push_back(&type<mud::UndoTool>());
		m.m_types.push_back(&type<mud::ViewAction>());
		m.m_types.push_back(&type<mud::ViewportTool>());
		m.m_types.push_back(&type<mud::ViewTool>());
		m.m_types.push_back(&type<mud::WorkPlaneAction>());
		m.m_types.push_back(&type<mud::WorkPlaneTool>());
		m.m_types.push_back(&type<mud::WorldSnapOption>());
	}
}

namespace mud
{
	mud_tool::mud_tool()
		: Module("mud::tool", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_lang::m(), &mud_math::m(), &mud_geom::m(), &mud_ctx::m(), &mud_ui::m(), &mud_uio::m(), &mud_gfx::m(), &mud_gfx_pbr::m(), &mud_gfx_ui::m(), &mud_gfx_edit::m() })
	{
		// setup reflection meta data
		mud_tool_meta(*this);
	}
}

#ifdef MUD_TOOL_MODULE
extern "C"
Module& getModule()
{
		return mud_tool::m();
}
#endif
