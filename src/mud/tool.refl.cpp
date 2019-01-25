#include <mud/tree.refl.h>
#include <mud/lang.refl.h>
#include <mud/srlz.refl.h>
#include <mud/uio.refl.h>
#include <mud/gfx.pbr.refl.h>
#include <mud/geom.refl.h>
#include <mud/ui.refl.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.refl.h>
#include <mud/ctx.refl.h>
#include <mud/gfx.ui.refl.h>
#include <mud/tool.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/tool.refl.h>
#include <mud/infra.h>
#include <mud/type.h>
#include <mud/gfx.edit.refl.h>

#ifdef MUD_MODULES
module mud.tool;
#else
#endif


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
		meta_enum<mud::ToolState>();
	}
	
	// Sequences
	
	// mud::EditContext
	{
		Type& t = type<mud::EditContext>();
		static Meta meta = { t, &namspc({ "mud" }), "EditContext", sizeof(mud::EditContext), TypeClass::Object };
		static Class cls = { t,
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
				{ t, member_address(&mud::EditContext::m_undo_tool), type<mud::UndoTool>(), "undo_tool", Ref(type<mud::UndoTool>()), Member::NonMutable, nullptr },
				{ t, member_address(&mud::EditContext::m_redo_tool), type<mud::RedoTool>(), "redo_tool", Ref(type<mud::RedoTool>()), Member::NonMutable, nullptr },
				{ t, member_address(&mud::EditContext::m_work_plane), type<mud::Plane>(), "work_plane", var(mud::Plane()), Member::Value, nullptr },
				{ t, member_address(&mud::EditContext::m_translate_tool), type<mud::TranslateTool>(), "translate_tool", Ref(type<mud::TranslateTool>()), Member::NonMutable, nullptr },
				{ t, member_address(&mud::EditContext::m_rotate_tool), type<mud::RotateTool>(), "rotate_tool", Ref(type<mud::RotateTool>()), Member::NonMutable, nullptr },
				{ t, member_address(&mud::EditContext::m_scale_tool), type<mud::ScaleTool>(), "scale_tool", Ref(type<mud::ScaleTool>()), Member::NonMutable, nullptr },
				{ t, member_address(&mud::EditContext::m_viewer), type<mud::Viewer>(), "viewer", Ref(type<mud::Viewer>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::EditContext::m_tool), type<mud::ViewportTool>(), "tool", Ref(type<mud::ViewportTool>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::EditContext::m_spatial_tool), type<mud::SpatialTool>(), "spatial_tool", Ref(type<mud::SpatialTool>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::EditContext::m_brush), type<mud::Brush>(), "brush", Ref(type<mud::Brush>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
		Type& t = type<mud::EditorAction>();
		static Meta meta = { t, &namspc({ "mud" }), "EditorAction", sizeof(mud::EditorAction), TypeClass::Object };
		static Class cls = { t,
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
		Type& t = type<mud::Gizmo>();
		static Meta meta = { t, &namspc({ "mud" }), "Gizmo", sizeof(mud::Gizmo), TypeClass::Object };
		static Class cls = { t,
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
		meta_class<mud::Gizmo>();
	}
	// mud::Tool
	{
		Type& t = type<mud::Tool>();
		static Meta meta = { t, &namspc({ "mud" }), "Tool", sizeof(mud::Tool), TypeClass::Object };
		static Class cls = { t,
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
				{ t, Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Tool>(object).m_type); } },
				{ t, Address(), type<mud::ToolContext>(), "context", var(mud::ToolContext()), Member::Flags(Member::Value|Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Tool>(object).m_context); } },
				{ t, member_address(&mud::Tool::m_name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&mud::Tool::m_state), type<mud::ToolState>(), "state", var(mud::ToolState()), Member::Value, nullptr }
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
		Type& t = type<mud::ToolContext>();
		static Meta meta = { t, &namspc({ "mud" }), "ToolContext", sizeof(mud::ToolContext), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ToolContext>(ref)) mud::ToolContext(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ToolContext>(ref)) mud::ToolContext(val<mud::ToolContext>(other)); } }
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
		Type& t = type<mud::ToolOption>();
		static Meta meta = { t, &namspc({ "mud" }), "ToolOption", sizeof(mud::ToolOption), TypeClass::Object };
		static Class cls = { t,
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
	// mud::RedoTool
	{
		Type& t = type<mud::RedoTool>();
		static Meta meta = { t, &namspc({ "mud" }), "RedoTool", sizeof(mud::RedoTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::ViewportTool
	{
		Type& t = type<mud::ViewportTool>();
		static Meta meta = { t, &namspc({ "mud" }), "ViewportTool", sizeof(mud::ViewportTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::SpatialTool
	{
		Type& t = type<mud::SpatialTool>();
		static Meta meta = { t, &namspc({ "mud" }), "SpatialTool", sizeof(mud::SpatialTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::Brush
	{
		Type& t = type<mud::Brush>();
		static Meta meta = { t, &namspc({ "mud" }), "Brush", sizeof(mud::Brush), TypeClass::Object };
		static Class cls = { t,
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
	// mud::CircleBrush
	{
		Type& t = type<mud::CircleBrush>();
		static Meta meta = { t, &namspc({ "mud" }), "CircleBrush", sizeof(mud::CircleBrush), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Brush>() },
			{ base_offset<mud::CircleBrush, mud::Brush>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::CircleBrush>(ref)) mud::CircleBrush( val<mud::ToolContext>(args[0]) ); }, { { "context", var(mud::ToolContext()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::CircleBrush::m_creator), type<mud::Creator>(), "creator", Ref(type<mud::Creator>()), Member::NonMutable, nullptr },
				{ t, member_address(&mud::CircleBrush::m_radius), type<float>(), "radius", var(float()), Member::Value, nullptr },
				{ t, member_address(&mud::CircleBrush::m_maxSpotRadius), type<float>(), "maxSpotRadius", var(float()), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::CircleBrush>();
		meta_class<mud::CircleBrush>();
	}
	// mud::PlaceBrush
	{
		Type& t = type<mud::PlaceBrush>();
		static Meta meta = { t, &namspc({ "mud" }), "PlaceBrush", sizeof(mud::PlaceBrush), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Brush>() },
			{ base_offset<mud::PlaceBrush, mud::Brush>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::PlaceBrush>(ref)) mud::PlaceBrush( val<mud::ToolContext>(args[0]) ); }, { { "context", var(mud::ToolContext()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::PlaceBrush::m_creator), type<mud::Creator>(), "creator", Ref(type<mud::Creator>()), Member::NonMutable, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::PlaceBrush>();
		meta_class<mud::PlaceBrush>();
	}
	// mud::PlaneSnapOption
	{
		Type& t = type<mud::PlaneSnapOption>();
		static Meta meta = { t, &namspc({ "mud" }), "PlaneSnapOption", sizeof(mud::PlaneSnapOption), TypeClass::Object };
		static Class cls = { t,
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
	// mud::ScriptedBrush
	{
		Type& t = type<mud::ScriptedBrush>();
		static Meta meta = { t, &namspc({ "mud" }), "ScriptedBrush", sizeof(mud::ScriptedBrush), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Brush>() },
			{ base_offset<mud::ScriptedBrush, mud::Brush>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ScriptedBrush>(ref)) mud::ScriptedBrush( val<mud::ToolContext>(args[0]), val<mud::Script>(args[1]) ); }, { { "context", var(mud::ToolContext()) }, { "script", Ref(type<mud::Script>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::ScriptedBrush::m_call), type<mud::Call>(), "call", var(mud::Call()), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ScriptedBrush>();
		meta_class<mud::ScriptedBrush>();
	}
	// mud::TransformAction
	{
		Type& t = type<mud::TransformAction>();
		static Meta meta = { t, &namspc({ "mud" }), "TransformAction", sizeof(mud::TransformAction), TypeClass::Object };
		static Class cls = { t,
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
	// mud::RotateAction
	{
		Type& t = type<mud::RotateAction>();
		static Meta meta = { t, &namspc({ "mud" }), "RotateAction", sizeof(mud::RotateAction), TypeClass::Object };
		static Class cls = { t,
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
	// mud::TransformGizmo
	{
		Type& t = type<mud::TransformGizmo>();
		static Meta meta = { t, &namspc({ "mud" }), "TransformGizmo", sizeof(mud::TransformGizmo), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Gizmo>() },
			{ base_offset<mud::TransformGizmo, mud::Gizmo>() },
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
		meta_class<mud::TransformGizmo>();
	}
	// mud::TransformTool
	{
		Type& t = type<mud::TransformTool>();
		static Meta meta = { t, &namspc({ "mud" }), "TransformTool", sizeof(mud::TransformTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::RotateTool
	{
		Type& t = type<mud::RotateTool>();
		static Meta meta = { t, &namspc({ "mud" }), "RotateTool", sizeof(mud::RotateTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::ScaleAction
	{
		Type& t = type<mud::ScaleAction>();
		static Meta meta = { t, &namspc({ "mud" }), "ScaleAction", sizeof(mud::ScaleAction), TypeClass::Object };
		static Class cls = { t,
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
	// mud::ScaleTool
	{
		Type& t = type<mud::ScaleTool>();
		static Meta meta = { t, &namspc({ "mud" }), "ScaleTool", sizeof(mud::ScaleTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::TranslateAction
	{
		Type& t = type<mud::TranslateAction>();
		static Meta meta = { t, &namspc({ "mud" }), "TranslateAction", sizeof(mud::TranslateAction), TypeClass::Object };
		static Class cls = { t,
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
	// mud::CopyAction
	{
		Type& t = type<mud::CopyAction>();
		static Meta meta = { t, &namspc({ "mud" }), "CopyAction", sizeof(mud::CopyAction), TypeClass::Object };
		static Class cls = { t,
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
	// mud::CopyTool
	{
		Type& t = type<mud::CopyTool>();
		static Meta meta = { t, &namspc({ "mud" }), "CopyTool", sizeof(mud::CopyTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::FrameViewTool
	{
		Type& t = type<mud::FrameViewTool>();
		static Meta meta = { t, &namspc({ "mud" }), "FrameViewTool", sizeof(mud::FrameViewTool), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::ViewportTool>() },
			{ base_offset<mud::FrameViewTool, mud::ViewportTool>() },
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
		meta_class<mud::FrameViewTool>();
	}
	// mud::TranslateTool
	{
		Type& t = type<mud::TranslateTool>();
		static Meta meta = { t, &namspc({ "mud" }), "TranslateTool", sizeof(mud::TranslateTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::UndoTool
	{
		Type& t = type<mud::UndoTool>();
		static Meta meta = { t, &namspc({ "mud" }), "UndoTool", sizeof(mud::UndoTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::ViewAction
	{
		Type& t = type<mud::ViewAction>();
		static Meta meta = { t, &namspc({ "mud" }), "ViewAction", sizeof(mud::ViewAction), TypeClass::Object };
		static Class cls = { t,
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
	// mud::ViewTool
	{
		Type& t = type<mud::ViewTool>();
		static Meta meta = { t, &namspc({ "mud" }), "ViewTool", sizeof(mud::ViewTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::WorkPlaneAction
	{
		Type& t = type<mud::WorkPlaneAction>();
		static Meta meta = { t, &namspc({ "mud" }), "WorkPlaneAction", sizeof(mud::WorkPlaneAction), TypeClass::Object };
		static Class cls = { t,
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
	// mud::WorkPlaneTool
	{
		Type& t = type<mud::WorkPlaneTool>();
		static Meta meta = { t, &namspc({ "mud" }), "WorkPlaneTool", sizeof(mud::WorkPlaneTool), TypeClass::Object };
		static Class cls = { t,
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
	// mud::WorldSnapOption
	{
		Type& t = type<mud::WorldSnapOption>();
		static Meta meta = { t, &namspc({ "mud" }), "WorldSnapOption", sizeof(mud::WorldSnapOption), TypeClass::Object };
		static Class cls = { t,
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
		m.m_types.push_back(&type<mud::EditContext>());
		m.m_types.push_back(&type<mud::EditorAction>());
		m.m_types.push_back(&type<mud::Gizmo>());
		m.m_types.push_back(&type<mud::Tool>());
		m.m_types.push_back(&type<mud::ToolContext>());
		m.m_types.push_back(&type<mud::ToolOption>());
		m.m_types.push_back(&type<mud::ToolState>());
		m.m_types.push_back(&type<mud::SpatialTool>());
		m.m_types.push_back(&type<mud::Brush>());
		m.m_types.push_back(&type<mud::CircleBrush>());
		m.m_types.push_back(&type<mud::CopyAction>());
		m.m_types.push_back(&type<mud::CopyTool>());
		m.m_types.push_back(&type<mud::FrameViewTool>());
		m.m_types.push_back(&type<mud::PlaceBrush>());
		m.m_types.push_back(&type<mud::PlaneSnapOption>());
		m.m_types.push_back(&type<mud::RedoTool>());
		m.m_types.push_back(&type<mud::RotateAction>());
		m.m_types.push_back(&type<mud::ScriptedBrush>());
		m.m_types.push_back(&type<mud::TransformAction>());
		m.m_types.push_back(&type<mud::ViewportTool>());
		m.m_types.push_back(&type<mud::TransformTool>());
		m.m_types.push_back(&type<mud::RotateTool>());
		m.m_types.push_back(&type<mud::ScaleAction>());
		m.m_types.push_back(&type<mud::ScaleTool>());
		m.m_types.push_back(&type<mud::TransformGizmo>());
		m.m_types.push_back(&type<mud::TranslateAction>());
		m.m_types.push_back(&type<mud::TranslateTool>());
		m.m_types.push_back(&type<mud::UndoTool>());
		m.m_types.push_back(&type<mud::ViewAction>());
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
