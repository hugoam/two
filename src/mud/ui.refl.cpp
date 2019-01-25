#include <mud/ui.h>
#include <mud/ui.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/ctx.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#endif


namespace mud
{
	void mud_ui_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::Align>();
		static Meta meta = { t, &namspc({ "mud" }), "Align", sizeof(mud::Align), TypeClass::Enum };
		static cstring ids[] = { "Left", "CENTER", "Right", "OUT_LEFT", "OUT_RIGHT" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::Align vars[] = { mud::Left, mud::CENTER, mud::Right, mud::OUT_LEFT, mud::OUT_RIGHT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Align>();
	}
	{
		Type& t = type<mud::AutoLayout>();
		static Meta meta = { t, &namspc({ "mud" }), "AutoLayout", sizeof(mud::AutoLayout), TypeClass::Enum };
		static cstring ids[] = { "NO_LAYOUT", "AUTO_SIZE", "AUTO_LAYOUT" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::AutoLayout vars[] = { mud::NO_LAYOUT, mud::AUTO_SIZE, mud::AUTO_LAYOUT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::AutoLayout>();
	}
	{
		Type& t = type<mud::Clipping>();
		static Meta meta = { t, &namspc({ "mud" }), "Clipping", sizeof(mud::Clipping), TypeClass::Enum };
		static cstring ids[] = { "NOCLIP", "CLIP", "UNCLIP" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Clipping vars[] = { mud::NOCLIP, mud::CLIP, mud::UNCLIP};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Clipping>();
	}
	{
		Type& t = type<mud::Dim>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim", sizeof(mud::Dim), TypeClass::Enum };
		static cstring ids[] = { "DIM_X", "DIM_Y", "DIM_NONE" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Dim vars[] = { mud::DIM_X, mud::DIM_Y, mud::DIM_NONE};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Dim>();
	}
	{
		Type& t = type<mud::Flow>();
		static Meta meta = { t, &namspc({ "mud" }), "Flow", sizeof(mud::Flow), TypeClass::Enum };
		static cstring ids[] = { "FLOW", "OVERLAY", "ALIGN", "FREE" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::Flow vars[] = { mud::FLOW, mud::OVERLAY, mud::ALIGN, mud::FREE};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Flow>();
	}
	{
		Type& t = type<mud::FlowAxis>();
		static Meta meta = { t, &namspc({ "mud" }), "FlowAxis", sizeof(mud::FlowAxis), TypeClass::Enum };
		static cstring ids[] = { "READING", "PARAGRAPH", "PARALLEL", "ORTHOGONAL", "AXIS_NONE" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::FlowAxis vars[] = { mud::READING, mud::PARAGRAPH, mud::PARALLEL, mud::ORTHOGONAL, mud::AXIS_NONE};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::FlowAxis>();
	}
	{
		Type& t = type<mud::LayoutSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "LayoutSolver", sizeof(mud::LayoutSolver), TypeClass::Enum };
		static cstring ids[] = { "FRAME_SOLVER", "ROW_SOLVER", "GRID_SOLVER", "TABLE_SOLVER" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::LayoutSolver vars[] = { mud::FRAME_SOLVER, mud::ROW_SOLVER, mud::GRID_SOLVER, mud::TABLE_SOLVER};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::LayoutSolver>();
	}
	{
		Type& t = type<mud::Opacity>();
		static Meta meta = { t, &namspc({ "mud" }), "Opacity", sizeof(mud::Opacity), TypeClass::Enum };
		static cstring ids[] = { "OPAQUE", "CLEAR", "HOLLOW" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Opacity vars[] = { mud::OPAQUE, mud::CLEAR, mud::HOLLOW};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Opacity>();
	}
	{
		Type& t = type<mud::Pivot>();
		static Meta meta = { t, &namspc({ "mud" }), "Pivot", sizeof(mud::Pivot), TypeClass::Enum };
		static cstring ids[] = { "FORWARD", "REVERSE" };
		static uint32_t values[] = { 0, 1 };
		static mud::Pivot vars[] = { mud::FORWARD, mud::REVERSE};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Pivot>();
	}
	{
		Type& t = type<mud::ui::PopupFlags>();
		static Meta meta = { t, &namspc({ "mud", "ui" }), "PopupFlags", sizeof(mud::ui::PopupFlags), TypeClass::Enum };
		static cstring ids[] = { "None", "Modal", "Clamp", "AutoClose", "AutoModal" };
		static uint32_t values[] = { 0, 1, 2, 4, 5 };
		static mud::ui::PopupFlags vars[] = { mud::ui::PopupFlags::None, mud::ui::PopupFlags::Modal, mud::ui::PopupFlags::Clamp, mud::ui::PopupFlags::AutoClose, mud::ui::PopupFlags::AutoModal};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::ui::PopupFlags>();
	}
	{
		Type& t = type<mud::Sizing>();
		static Meta meta = { t, &namspc({ "mud" }), "Sizing", sizeof(mud::Sizing), TypeClass::Enum };
		static cstring ids[] = { "FIXED", "SHRINK", "WRAP", "EXPAND" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::Sizing vars[] = { mud::FIXED, mud::SHRINK, mud::WRAP, mud::EXPAND};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Sizing>();
	}
	{
		Type& t = type<mud::SpacePreset>();
		static Meta meta = { t, &namspc({ "mud" }), "SpacePreset", sizeof(mud::SpacePreset), TypeClass::Enum };
		static cstring ids[] = { "SHEET", "FLEX", "ITEM", "UNIT", "BLOCK", "LINE", "STACK", "DIV", "SPACER", "BOARD", "LAYOUT" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		static mud::SpacePreset vars[] = { mud::SHEET, mud::FLEX, mud::ITEM, mud::UNIT, mud::BLOCK, mud::LINE, mud::STACK, mud::DIV, mud::SPACER, mud::BOARD, mud::LAYOUT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::SpacePreset>();
	}
	{
		Type& t = type<mud::WidgetState>();
		static Meta meta = { t, &namspc({ "mud" }), "WidgetState", sizeof(mud::WidgetState), TypeClass::Enum };
		static cstring ids[] = { "NOSTATE", "CREATED", "HOVERED", "PRESSED", "ACTIVATED", "ACTIVE", "SELECTED", "DISABLED", "DRAGGED", "FOCUSED", "CLOSED" };
		static uint32_t values[] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
		static mud::WidgetState vars[] = { mud::NOSTATE, mud::CREATED, mud::HOVERED, mud::PRESSED, mud::ACTIVATED, mud::ACTIVE, mud::SELECTED, mud::DISABLED, mud::DRAGGED, mud::FOCUSED, mud::CLOSED};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::WidgetState>();
	}
	{
		Type& t = type<mud::WindowState>();
		static Meta meta = { t, &namspc({ "mud" }), "WindowState", sizeof(mud::WindowState), TypeClass::Enum };
		static cstring ids[] = { "WINDOW_NOSTATE", "WINDOW_HEADER", "WINDOW_DOCKABLE", "WINDOW_CLOSABLE", "WINDOW_MOVABLE", "WINDOW_SIZABLE", "WINDOW_DEFAULT" };
		static uint32_t values[] = { 0, 2, 4, 8, 16, 32, 58 };
		static mud::WindowState vars[] = { mud::WINDOW_NOSTATE, mud::WINDOW_HEADER, mud::WINDOW_DOCKABLE, mud::WINDOW_CLOSABLE, mud::WINDOW_MOVABLE, mud::WINDOW_SIZABLE, mud::WINDOW_DEFAULT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::WindowState>();
	}
	
	// Sequences
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<const char*>();
		meta_sequence<array<const char*>, const char*>();
	}
	{
		Type& t = type<array<float>>();
		static Meta meta = { t, &namspc({}), "array<float>", sizeof(array<float>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<float>();
		meta_sequence<array<float>, float>();
	}
	{
		Type& t = type<vector<mud::Space>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Space>", sizeof(vector<mud::Space>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Space>();
		meta_vector<vector<mud::Space>, mud::Space>();
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<string>();
		meta_vector<vector<string>, string>();
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<string>();
		meta_vector<vector<string>, string>();
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<string>();
		meta_vector<vector<string>, string>();
	}
	
	// mud::CanvasConnect
	{
		Type& t = type<mud::CanvasConnect>();
		static Meta meta = { t, &namspc({ "mud" }), "CanvasConnect", sizeof(mud::CanvasConnect), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::CanvasConnect>(ref)) mud::CanvasConnect(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::CanvasConnect>(ref)) mud::CanvasConnect(val<mud::CanvasConnect>(other)); } }
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
		meta_class<mud::CanvasConnect>();
	}
	// mud::Clipboard
	{
		Type& t = type<mud::Clipboard>();
		static Meta meta = { t, &namspc({ "mud" }), "Clipboard", sizeof(mud::Clipboard), TypeClass::Struct };
		// defaults
		static string text_default = "";
		static bool line_mode_default = false;
		static vector<string> pasted_default = {};
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Clipboard>(ref)) mud::Clipboard(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Clipboard>(ref)) mud::Clipboard(val<mud::Clipboard>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Clipboard::m_text), type<string>(), "text", Ref(&text_default), Member::Value, nullptr },
				{ t, member_address(&mud::Clipboard::m_line_mode), type<bool>(), "line_mode", Ref(&line_mode_default), Member::Value, nullptr },
				{ t, member_address(&mud::Clipboard::m_pasted), type<vector<string>>(), "pasted", Ref(&pasted_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Clipboard>();
	}
	// mud::Dim2<bool>
	{
		Type& t = type<mud::Dim2<bool>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<bool>", sizeof(mud::Dim2<bool>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Dim2<bool>>(ref)) mud::Dim2<bool>( val<bool>(args[0]), val<bool>(args[1]) ); }, { { "a", var(bool()) }, { "b", var(bool()) } } },
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Dim2<bool>>(ref)) mud::Dim2<bool>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Dim2<bool>>(ref)) mud::Dim2<bool>(val<mud::Dim2<bool>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Dim2<bool>::x), type<bool>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Dim2<bool>::y), type<bool>(), "y", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::Dim2<bool>>();
		meta_class<mud::Dim2<bool>>();
	}
	// mud::Dim2<mud::Align>
	{
		Type& t = type<mud::Dim2<mud::Align>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<mud::Align>", sizeof(mud::Dim2<mud::Align>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Dim2<mud::Align>>(ref)) mud::Dim2<mud::Align>( val<mud::Align>(args[0]), val<mud::Align>(args[1]) ); }, { { "a", var(mud::Align()) }, { "b", var(mud::Align()) } } },
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Dim2<mud::Align>>(ref)) mud::Dim2<mud::Align>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Dim2<mud::Align>>(ref)) mud::Dim2<mud::Align>(val<mud::Dim2<mud::Align>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Dim2<mud::Align>::x), type<mud::Align>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Dim2<mud::Align>::y), type<mud::Align>(), "y", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::Dim2<mud::Align>>();
		meta_class<mud::Dim2<mud::Align>>();
	}
	// mud::Dim2<mud::AutoLayout>
	{
		Type& t = type<mud::Dim2<mud::AutoLayout>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<mud::AutoLayout>", sizeof(mud::Dim2<mud::AutoLayout>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Dim2<mud::AutoLayout>>(ref)) mud::Dim2<mud::AutoLayout>( val<mud::AutoLayout>(args[0]), val<mud::AutoLayout>(args[1]) ); }, { { "a", var(mud::AutoLayout()) }, { "b", var(mud::AutoLayout()) } } },
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Dim2<mud::AutoLayout>>(ref)) mud::Dim2<mud::AutoLayout>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Dim2<mud::AutoLayout>>(ref)) mud::Dim2<mud::AutoLayout>(val<mud::Dim2<mud::AutoLayout>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Dim2<mud::AutoLayout>::x), type<mud::AutoLayout>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Dim2<mud::AutoLayout>::y), type<mud::AutoLayout>(), "y", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::Dim2<mud::AutoLayout>>();
		meta_class<mud::Dim2<mud::AutoLayout>>();
	}
	// mud::Dim2<mud::Pivot>
	{
		Type& t = type<mud::Dim2<mud::Pivot>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<mud::Pivot>", sizeof(mud::Dim2<mud::Pivot>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Dim2<mud::Pivot>>(ref)) mud::Dim2<mud::Pivot>( val<mud::Pivot>(args[0]), val<mud::Pivot>(args[1]) ); }, { { "a", var(mud::Pivot()) }, { "b", var(mud::Pivot()) } } },
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Dim2<mud::Pivot>>(ref)) mud::Dim2<mud::Pivot>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Dim2<mud::Pivot>>(ref)) mud::Dim2<mud::Pivot>(val<mud::Dim2<mud::Pivot>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Dim2<mud::Pivot>::x), type<mud::Pivot>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Dim2<mud::Pivot>::y), type<mud::Pivot>(), "y", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::Dim2<mud::Pivot>>();
		meta_class<mud::Dim2<mud::Pivot>>();
	}
	// mud::Dim2<mud::Sizing>
	{
		Type& t = type<mud::Dim2<mud::Sizing>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<mud::Sizing>", sizeof(mud::Dim2<mud::Sizing>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Dim2<mud::Sizing>>(ref)) mud::Dim2<mud::Sizing>( val<mud::Sizing>(args[0]), val<mud::Sizing>(args[1]) ); }, { { "a", var(mud::Sizing()) }, { "b", var(mud::Sizing()) } } },
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Dim2<mud::Sizing>>(ref)) mud::Dim2<mud::Sizing>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Dim2<mud::Sizing>>(ref)) mud::Dim2<mud::Sizing>(val<mud::Dim2<mud::Sizing>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Dim2<mud::Sizing>::x), type<mud::Sizing>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Dim2<mud::Sizing>::y), type<mud::Sizing>(), "y", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::Dim2<mud::Sizing>>();
		meta_class<mud::Dim2<mud::Sizing>>();
	}
	// mud::Dim2<size_t>
	{
		Type& t = type<mud::Dim2<size_t>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<size_t>", sizeof(mud::Dim2<size_t>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Dim2<size_t>>(ref)) mud::Dim2<size_t>( val<size_t>(args[0]), val<size_t>(args[1]) ); }, { { "a", var(size_t()) }, { "b", var(size_t()) } } },
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Dim2<size_t>>(ref)) mud::Dim2<size_t>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Dim2<size_t>>(ref)) mud::Dim2<size_t>(val<mud::Dim2<size_t>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Dim2<size_t>::x), type<size_t>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Dim2<size_t>::y), type<size_t>(), "y", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::Dim2<size_t>>();
		meta_class<mud::Dim2<size_t>>();
	}
	// mud::Dock
	{
		Type& t = type<mud::Dock>();
		static Meta meta = { t, &namspc({ "mud" }), "Dock", sizeof(mud::Dock), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Dock>(ref)) mud::Dock(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Dock>(ref)) mud::Dock(val<mud::Dock>(other)); } }
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
		meta_class<mud::Dock>();
	}
	// mud::Docksystem
	{
		Type& t = type<mud::Docksystem>();
		static Meta meta = { t, &namspc({ "mud" }), "Docksystem", sizeof(mud::Docksystem), TypeClass::Object };
		// defaults
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
		meta_class<mud::Docksystem>();
	}
	// mud::Gradient
	{
		Type& t = type<mud::Gradient>();
		static Meta meta = { t, &namspc({ "mud" }), "Gradient", sizeof(mud::Gradient), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Gradient>(ref)) mud::Gradient(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Gradient>(ref)) mud::Gradient(val<mud::Gradient>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Gradient::m_start), type<mud::Colour>(), "start", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Gradient::m_end), type<mud::Colour>(), "end", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Gradient>();
	}
	// mud::GridSolver
	{
		Type& t = type<mud::GridSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "GridSolver", sizeof(mud::GridSolver), TypeClass::Object };
		// defaults
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
		meta_class<mud::GridSolver>();
	}
	// mud::ImageSkin
	{
		Type& t = type<mud::ImageSkin>();
		static Meta meta = { t, &namspc({ "mud" }), "ImageSkin", sizeof(mud::ImageSkin), TypeClass::Struct };
		// defaults
		static mud::Image* d_image_default = nullptr;
		static int d_left_default = 0;
		static int d_top_default = 0;
		static int d_right_default = 0;
		static int d_bottom_default = 0;
		static int margin_default = 0;
		static mud::Dim d_stretch_default = DIM_NONE;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ImageSkin>(ref)) mud::ImageSkin( val<mud::Image>(args[0]), val<int>(args[1]), val<int>(args[2]), val<int>(args[3]), val<int>(args[4]), val<int>(args[5]), val<mud::Dim>(args[6]) ); }, { { "image", var(mud::Image()) }, { "left", var(int()) }, { "top", var(int()) }, { "right", var(int()) }, { "bottom", var(int()) }, { "margin", var(int(0)), Param::Default }, { "stretch", var(mud::Dim(DIM_NONE)), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ImageSkin>(ref)) mud::ImageSkin(val<mud::ImageSkin>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ImageSkin::d_image), type<mud::Image>(), "d_image", Ref(d_image_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::ImageSkin::d_left), type<int>(), "d_left", Ref(&d_left_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImageSkin::d_top), type<int>(), "d_top", Ref(&d_top_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImageSkin::d_right), type<int>(), "d_right", Ref(&d_right_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImageSkin::d_bottom), type<int>(), "d_bottom", Ref(&d_bottom_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImageSkin::m_margin), type<int>(), "margin", Ref(&margin_default), Member::Value, nullptr },
				{ t, member_address(&mud::ImageSkin::d_stretch), type<mud::Dim>(), "d_stretch", Ref(&d_stretch_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ImageSkin>();
	}
	// mud::InkStyle
	{
		Type& t = type<mud::InkStyle>();
		static Meta meta = { t, &namspc({ "mud" }), "InkStyle", sizeof(mud::InkStyle), TypeClass::Struct };
		// defaults
		static string name_default = "";
		static bool empty_default = true;
		static mud::Colour background_colour_default = mud::Colour::None;
		static mud::Colour border_colour_default = mud::Colour::None;
		static mud::Colour image_colour_default = mud::Colour::None;
		static mud::Colour text_colour_default = mud::Colour::None;
		static string text_font_default = "dejavu";
		static float text_size_default = 14.f;
		static bool text_break_default = false;
		static bool text_wrap_default = false;
		static bool weak_corners_default = false;
		static mud::Dim2<mud::Align> align_default = {Left,Left};
		static mud::Dim linear_gradient_dim_default = DIM_Y;
		static mud::Dim2<bool> stretch_default = {false,false};
		static mud::Image* image_default = nullptr;
		static mud::Image* overlay_default = nullptr;
		static mud::Image* tile_default = nullptr;
		static mud::Style* hover_cursor_default = nullptr;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::InkStyle>(ref)) mud::InkStyle(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::InkStyle>(ref)) mud::InkStyle( val<const char*>(args[0]) ); }, { { "name", Ref(type<const char*>()), Param::Nullable } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::InkStyle>(ref)) mud::InkStyle(val<mud::InkStyle>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::InkStyle::m_name), type<string>(), "name", Ref(&name_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_empty), type<bool>(), "empty", Ref(&empty_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_background_colour), type<mud::Colour>(), "background_colour", Ref(&background_colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_border_colour), type<mud::Colour>(), "border_colour", Ref(&border_colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_image_colour), type<mud::Colour>(), "image_colour", Ref(&image_colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_text_colour), type<mud::Colour>(), "text_colour", Ref(&text_colour_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_text_font), type<string>(), "text_font", Ref(&text_font_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_text_size), type<float>(), "text_size", Ref(&text_size_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_text_break), type<bool>(), "text_break", Ref(&text_break_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_text_wrap), type<bool>(), "text_wrap", Ref(&text_wrap_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_border_width), type<mud::vec4>(), "border_width", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_corner_radius), type<mud::vec4>(), "corner_radius", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_weak_corners), type<bool>(), "weak_corners", Ref(&weak_corners_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_padding), type<mud::vec4>(), "padding", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_margin), type<mud::vec4>(), "margin", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_align), type<mud::Dim2<mud::Align>>(), "align", Ref(&align_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_linear_gradient), type<mud::vec2>(), "linear_gradient", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_linear_gradient_dim), type<mud::Dim>(), "linear_gradient_dim", Ref(&linear_gradient_dim_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_stretch), type<mud::Dim2<bool>>(), "stretch", Ref(&stretch_default), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_image), type<mud::Image>(), "image", Ref(image_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::InkStyle::m_overlay), type<mud::Image>(), "overlay", Ref(overlay_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::InkStyle::m_tile), type<mud::Image>(), "tile", Ref(tile_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::InkStyle::m_image_skin), type<mud::ImageSkin>(), "image_skin", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_shadow), type<mud::Shadow>(), "shadow", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_shadow_colour), type<mud::Colour>(), "shadow_colour", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::InkStyle::m_hover_cursor), type<mud::Style>(), "hover_cursor", Ref(hover_cursor_default), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::InkStyle>();
	}
	// mud::Layer
	{
		Type& t = type<mud::Layer>();
		static Meta meta = { t, &namspc({ "mud" }), "Layer", sizeof(mud::Layer), TypeClass::Object };
		// defaults
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
		meta_class<mud::Layer>();
	}
	// mud::Layout
	{
		Type& t = type<mud::Layout>();
		static Meta meta = { t, &namspc({ "mud" }), "Layout", sizeof(mud::Layout), TypeClass::Struct };
		// defaults
		static string name_default = "";
		static mud::LayoutSolver solver_default = FRAME_SOLVER;
		static mud::Dim2<mud::AutoLayout> layout_default = {AUTO_LAYOUT,AUTO_LAYOUT};
		static mud::Flow flow_default = FLOW;
		static mud::Space space_default = SHEET;
		static mud::Clipping clipping_default = NOCLIP;
		static mud::Opacity opacity_default = CLEAR;
		static mud::Dim2<mud::Align> align_default = {Left,Left};
		static mud::Dim2<mud::Pivot> pivot_default = {FORWARD,FORWARD};
		static int zorder_default = 0;
		static bool no_grid_default = false;
		static size_t updated_default = 0;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Layout>(ref)) mud::Layout(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Layout>(ref)) mud::Layout( val<const char*>(args[0]) ); }, { { "name", Ref(type<const char*>()), Param::Nullable } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Layout>(ref)) mud::Layout(val<mud::Layout>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Layout::m_name), type<string>(), "name", Ref(&name_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_solver), type<mud::LayoutSolver>(), "solver", Ref(&solver_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_layout), type<mud::Dim2<mud::AutoLayout>>(), "layout", Ref(&layout_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_flow), type<mud::Flow>(), "flow", Ref(&flow_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_space), type<mud::Space>(), "space", Ref(&space_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_clipping), type<mud::Clipping>(), "clipping", Ref(&clipping_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_opacity), type<mud::Opacity>(), "opacity", Ref(&opacity_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_align), type<mud::Dim2<mud::Align>>(), "align", Ref(&align_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_span), type<mud::vec2>(), "span", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_size), type<mud::vec2>(), "size", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_padding), type<mud::vec4>(), "padding", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_margin), type<mud::vec2>(), "margin", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_spacing), type<mud::vec2>(), "spacing", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_pivot), type<mud::Dim2<mud::Pivot>>(), "pivot", Ref(&pivot_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_zorder), type<int>(), "zorder", Ref(&zorder_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_no_grid), type<bool>(), "no_grid", Ref(&no_grid_default), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_grid_division), type<vector<mud::Space>>(), "grid_division", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_table_division), type<vector<float>>(), "table_division", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Layout::m_updated), type<size_t>(), "updated", Ref(&updated_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Layout>();
	}
	// mud::NodeConnection
	{
		Type& t = type<mud::NodeConnection>();
		static Meta meta = { t, &namspc({ "mud" }), "NodeConnection", sizeof(mud::NodeConnection), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::NodeConnection>(ref)) mud::NodeConnection(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::NodeConnection>(ref)) mud::NodeConnection(val<mud::NodeConnection>(other)); } }
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
		meta_class<mud::NodeConnection>();
	}
	// mud::Paint
	{
		Type& t = type<mud::Paint>();
		static Meta meta = { t, &namspc({ "mud" }), "Paint", sizeof(mud::Paint), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Paint>(ref)) mud::Paint(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Paint>(ref)) mud::Paint(val<mud::Paint>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Paint::m_fill_colour), type<mud::Colour>(), "fill_colour", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Paint::m_stroke_colour), type<mud::Colour>(), "stroke_colour", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Paint::m_stroke_width), type<float>(), "stroke_width", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Paint>();
	}
	// mud::Shadow
	{
		Type& t = type<mud::Shadow>();
		static Meta meta = { t, &namspc({ "mud" }), "Shadow", sizeof(mud::Shadow), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Shadow>(ref)) mud::Shadow( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]), val<mud::Colour>(args[4]) ); }, { { "xpos", var(float()) }, { "ypos", var(float()) }, { "blur", var(float()) }, { "spread", var(float()) }, { "colour", var(mud::Colour::AlphaBlack), Param::Default } } },
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Shadow>(ref)) mud::Shadow(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Shadow>(ref)) mud::Shadow(val<mud::Shadow>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Shadow::d_xpos), type<float>(), "d_xpos", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Shadow::d_ypos), type<float>(), "d_ypos", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Shadow::d_blur), type<float>(), "d_blur", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Shadow::d_spread), type<float>(), "d_spread", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Shadow::d_colour), type<mud::Colour>(), "d_colour", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Shadow>();
	}
	// mud::Space
	{
		Type& t = type<mud::Space>();
		static Meta meta = { t, &namspc({ "mud" }), "Space", sizeof(mud::Space), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Space>(ref)) mud::Space(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Space>(ref)) mud::Space(val<mud::Space>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Space::direction), type<mud::FlowAxis>(), "direction", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Space::sizingLength), type<mud::Sizing>(), "sizingLength", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Space::sizingDepth), type<mud::Sizing>(), "sizingDepth", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Space>();
	}
	// mud::Style
	{
		Type& t = type<mud::Style>();
		static Meta meta = { t, &namspc({ "mud" }), "Style", sizeof(mud::Style), TypeClass::Object };
		// defaults
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
				{ t, member_address(&mud::Style::m_base), type<mud::Style>(), "base", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address<const char*(mud::Style::*)()>(&mud::Style::name), type<const char*>(), "name", Ref(), Member::Flags(Member::Pointer|Member::NonMutable|Member::Link), [](Ref object) { return Ref(val<mud::Style>(object).name()); } },
				{ t, member_address<mud::Layout&(mud::Style::*)()>(&mud::Style::layout), type<mud::Layout>(), "layout", Ref(), Member::Flags(Member::Value|Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Style>(object).layout()); } },
				{ t, member_address<mud::InkStyle&(mud::Style::*)()>(&mud::Style::skin), type<mud::InkStyle>(), "skin", Ref(), Member::Flags(Member::Value|Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Style>(object).skin()); } }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Style>();
	}
	// mud::TableSolver
	{
		Type& t = type<mud::TableSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "TableSolver", sizeof(mud::TableSolver), TypeClass::Object };
		// defaults
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
		meta_class<mud::TableSolver>();
	}
	// mud::Text
	{
		Type& t = type<mud::Text>();
		static Meta meta = { t, &namspc({ "mud" }), "Text", sizeof(mud::Text), TypeClass::Object };
		// defaults
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
		meta_class<mud::Text>();
	}
	// mud::TextCursor
	{
		Type& t = type<mud::TextCursor>();
		static Meta meta = { t, &namspc({ "mud" }), "TextCursor", sizeof(mud::TextCursor), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::TextCursor>(ref)) mud::TextCursor(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::TextCursor>(ref)) mud::TextCursor(val<mud::TextCursor>(other)); } }
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
		meta_class<mud::TextCursor>();
	}
	// mud::TextMarker
	{
		Type& t = type<mud::TextMarker>();
		static Meta meta = { t, &namspc({ "mud" }), "TextMarker", sizeof(mud::TextMarker), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::TextMarker>(ref)) mud::TextMarker(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::TextMarker>(ref)) mud::TextMarker(val<mud::TextMarker>(other)); } }
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
		meta_class<mud::TextMarker>();
	}
	// mud::TextPaint
	{
		Type& t = type<mud::TextPaint>();
		static Meta meta = { t, &namspc({ "mud" }), "TextPaint", sizeof(mud::TextPaint), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::TextPaint>(ref)) mud::TextPaint(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::TextPaint>(ref)) mud::TextPaint(val<mud::TextPaint>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::TextPaint::m_font), type<const char*>(), "font", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::TextPaint::m_colour), type<mud::Colour>(), "colour", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::TextPaint::m_size), type<float>(), "size", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::TextPaint::m_align), type<mud::Dim2<mud::Align>>(), "align", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::TextPaint::m_text_break), type<bool>(), "text_break", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::TextPaint::m_text_wrap), type<bool>(), "text_wrap", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::TextPaint>();
	}
	// mud::TextSelection
	{
		Type& t = type<mud::TextSelection>();
		static Meta meta = { t, &namspc({ "mud" }), "TextSelection", sizeof(mud::TextSelection), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::TextSelection>(ref)) mud::TextSelection(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::TextSelection>(ref)) mud::TextSelection(val<mud::TextSelection>(other)); } }
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
		meta_class<mud::TextSelection>();
	}
	// mud::UiRect
	{
		Type& t = type<mud::UiRect>();
		static Meta meta = { t, &namspc({ "mud" }), "UiRect", sizeof(mud::UiRect), TypeClass::Struct };
		// defaults
		static mud::vec2 position_default = Zero2;
		static mud::vec2 size_default = Zero2;
		static mud::vec2 content_default = Zero2;
		static mud::vec2 span_default = Unit2;
		static float scale_default = 1.f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::UiRect>(ref)) mud::UiRect(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::UiRect>(ref)) mud::UiRect(val<mud::UiRect>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::UiRect::m_position), type<mud::vec2>(), "position", Ref(&position_default), Member::Value, nullptr },
				{ t, member_address(&mud::UiRect::m_size), type<mud::vec2>(), "size", Ref(&size_default), Member::Value, nullptr },
				{ t, member_address(&mud::UiRect::m_content), type<mud::vec2>(), "content", Ref(&content_default), Member::Value, nullptr },
				{ t, member_address(&mud::UiRect::m_span), type<mud::vec2>(), "span", Ref(&span_default), Member::Value, nullptr },
				{ t, member_address(&mud::UiRect::m_scale), type<float>(), "scale", Ref(&scale_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::UiRect>();
	}
	// mud::UiWindow
	{
		Type& t = type<mud::UiWindow>();
		static Meta meta = { t, &namspc({ "mud" }), "UiWindow", sizeof(mud::UiWindow), TypeClass::Object };
		// defaults
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
		meta_class<mud::UiWindow>();
	}
	// mud::User
	{
		Type& t = type<mud::User>();
		static Meta meta = { t, &namspc({ "mud" }), "User", sizeof(mud::User), TypeClass::Object };
		// defaults
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
		meta_class<mud::User>();
	}
	// mud::Vg
	{
		Type& t = type<mud::Vg>();
		static Meta meta = { t, &namspc({ "mud" }), "Vg", sizeof(mud::Vg), TypeClass::Object };
		// defaults
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
		meta_class<mud::Vg>();
	}
	// mud::Frame
	{
		Type& t = type<mud::Frame>();
		static Meta meta = { t, &namspc({ "mud" }), "Frame", sizeof(mud::Frame), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::UiRect>() },
			{ base_offset<mud::Frame, mud::UiRect>() },
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
		meta_class<mud::Frame>();
	}
	// mud::FrameSolver
	{
		Type& t = type<mud::FrameSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "FrameSolver", sizeof(mud::FrameSolver), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::UiRect>() },
			{ base_offset<mud::FrameSolver, mud::UiRect>() },
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
		meta_class<mud::FrameSolver>();
	}
	// mud::LineSolver
	{
		Type& t = type<mud::LineSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "LineSolver", sizeof(mud::LineSolver), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::RowSolver>() },
			{ base_offset<mud::LineSolver, mud::RowSolver>() },
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
		meta_class<mud::LineSolver>();
	}
	// mud::Widget
	{
		Type& t = type<mud::Widget>();
		static Meta meta = { t, &namspc({ "mud" }), "Widget", sizeof(mud::Widget), TypeClass::Object };
		// defaults
		static mud::WidgetState state_default = CREATED;
		static uint32_t switch_default = 0;
		static size_t index_default = 0;
		static bool open_default = false;
		static mud::Widget* body_default = nullptr;
		static Class cls = { t,
			// bases
			{ &type<mud::ControlNode>() },
			{ base_offset<mud::Widget, mud::ControlNode>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Widget::m_frame), type<mud::Frame>(), "frame", Ref(), Member::NonMutable, nullptr },
				{ t, member_address(&mud::Widget::m_state), type<mud::WidgetState>(), "state", Ref(&state_default), Member::Value, nullptr },
				{ t, member_address(&mud::Widget::m_switch), type<uint32_t>(), "switch", Ref(&switch_default), Member::Value, nullptr },
				{ t, member_address(&mud::Widget::m_index), type<size_t>(), "index", Ref(&index_default), Member::Value, nullptr },
				{ t, member_address(&mud::Widget::m_open), type<bool>(), "open", Ref(&open_default), Member::Value, nullptr },
				{ t, member_address(&mud::Widget::m_body), type<mud::Widget>(), "body", Ref(body_default), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
				{ t, "focused", member_address<bool(mud::Widget::*)()>(&mud::Widget::focused), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Widget>(object).focused(); }, {}, var(bool()) },
				{ t, "hovered", member_address<bool(mud::Widget::*)()>(&mud::Widget::hovered), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Widget>(object).hovered(); }, {}, var(bool()) },
				{ t, "pressed", member_address<bool(mud::Widget::*)()>(&mud::Widget::pressed), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Widget>(object).pressed(); }, {}, var(bool()) },
				{ t, "activated", member_address<bool(mud::Widget::*)()>(&mud::Widget::activated), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Widget>(object).activated(); }, {}, var(bool()) },
				{ t, "selected", member_address<bool(mud::Widget::*)()>(&mud::Widget::selected), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Widget>(object).selected(); }, {}, var(bool()) },
				{ t, "modal", member_address<bool(mud::Widget::*)()>(&mud::Widget::modal), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Widget>(object).modal(); }, {}, var(bool()) },
				{ t, "closed", member_address<bool(mud::Widget::*)()>(&mud::Widget::closed), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Widget>(object).closed(); }, {}, var(bool()) },
				{ t, "ui_window", member_address<mud::UiWindow&(mud::Widget::*)()>(&mud::Widget::ui_window), [](Ref object, array<Var> args, Var& result) { UNUSED(args); result = Ref(&val<mud::Widget>(object).ui_window()); }, {}, Ref(type<mud::UiWindow>()) },
				{ t, "ui", member_address<mud::Ui&(mud::Widget::*)()>(&mud::Widget::ui), [](Ref object, array<Var> args, Var& result) { UNUSED(args); result = Ref(&val<mud::Widget>(object).ui()); }, {}, Ref(type<mud::Ui>()) },
				{ t, "parent_modal", member_address<mud::Widget&(mud::Widget::*)()>(&mud::Widget::parent_modal), [](Ref object, array<Var> args, Var& result) { UNUSED(args); result = Ref(&val<mud::Widget>(object).parent_modal()); }, {}, Ref(type<mud::Widget>()) },
				{ t, "toggle_state", member_address<void(mud::Widget::*)(mud::WidgetState)>(&mud::Widget::toggle_state), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).toggle_state(val<mud::WidgetState>(args[0])); }, { { "state", var(mud::WidgetState()) } }, Var() },
				{ t, "disable_state", member_address<void(mud::Widget::*)(mud::WidgetState)>(&mud::Widget::disable_state), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).disable_state(val<mud::WidgetState>(args[0])); }, { { "state", var(mud::WidgetState()) } }, Var() },
				{ t, "set_state", member_address<void(mud::Widget::*)(mud::WidgetState, bool)>(&mud::Widget::set_state), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).set_state(val<mud::WidgetState>(args[0]), val<bool>(args[1])); }, { { "state", var(mud::WidgetState()) }, { "enabled", var(bool()) } }, Var() },
				{ t, "enable_state", member_address<void(mud::Widget::*)(mud::WidgetState)>(&mud::Widget::enable_state), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).enable_state(val<mud::WidgetState>(args[0])); }, { { "state", var(mud::WidgetState()) } }, Var() },
				{ t, "clear_focus", member_address<void(mud::Widget::*)()>(&mud::Widget::clear_focus), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Widget>(object).clear_focus(); }, {}, Var() },
				{ t, "take_focus", member_address<void(mud::Widget::*)()>(&mud::Widget::take_focus), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Widget>(object).take_focus(); }, {}, Var() },
				{ t, "yield_focus", member_address<void(mud::Widget::*)()>(&mud::Widget::yield_focus), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Widget>(object).yield_focus(); }, {}, Var() },
				{ t, "take_modal", member_address<void(mud::Widget::*)(uint32_t)>(&mud::Widget::take_modal), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).take_modal(val<uint32_t>(args[0])); }, { { "device_filter", var(uint32_t()) } }, Var() },
				{ t, "yield_modal", member_address<void(mud::Widget::*)()>(&mud::Widget::yield_modal), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Widget>(object).yield_modal(); }, {}, Var() },
				{ t, "key_event", member_address<mud::KeyEvent(mud::Widget::*)(mud::Key, mud::EventType, mud::InputMod)>(&mud::Widget::key_event), [](Ref object, array<Var> args, Var& result) { val<mud::KeyEvent>(result) = val<mud::Widget>(object).key_event(val<mud::Key>(args[0]), val<mud::EventType>(args[1]), val<mud::InputMod>(args[2])); }, { { "code", var(mud::Key()) }, { "event_type", var(mud::EventType()) }, { "modifier", var(mud::InputMod::Any), Param::Default } }, var(mud::KeyEvent()) },
				{ t, "key_stroke", member_address<mud::KeyEvent(mud::Widget::*)(mud::Key, mud::InputMod)>(&mud::Widget::key_stroke), [](Ref object, array<Var> args, Var& result) { val<mud::KeyEvent>(result) = val<mud::Widget>(object).key_stroke(val<mud::Key>(args[0]), val<mud::InputMod>(args[1])); }, { { "code", var(mud::Key()) }, { "modifier", var(mud::InputMod::Any), Param::Default } }, var(mud::KeyEvent()) },
				{ t, "char_stroke", member_address<mud::KeyEvent(mud::Widget::*)(mud::Key, mud::InputMod)>(&mud::Widget::char_stroke), [](Ref object, array<Var> args, Var& result) { val<mud::KeyEvent>(result) = val<mud::Widget>(object).char_stroke(val<mud::Key>(args[0]), val<mud::InputMod>(args[1])); }, { { "code", var(mud::Key()) }, { "modifier", var(mud::InputMod::Any), Param::Default } }, var(mud::KeyEvent()) },
				{ t, "mouse_event", member_address<mud::MouseEvent(mud::Widget::*)(mud::DeviceType, mud::EventType, mud::InputMod, bool)>(&mud::Widget::mouse_event), [](Ref object, array<Var> args, Var& result) { val<mud::MouseEvent>(result) = val<mud::Widget>(object).mouse_event(val<mud::DeviceType>(args[0]), val<mud::EventType>(args[1]), val<mud::InputMod>(args[2]), val<bool>(args[3])); }, { { "device", var(mud::DeviceType()) }, { "event_type", var(mud::EventType()) }, { "modifier", var(mud::InputMod::None), Param::Default }, { "consume", var(bool(true)), Param::Default } }, var(mud::MouseEvent()) }
			},
			// static members
			{
			}
		};
		meta_class<mud::Widget>();
	}
	// mud::Canvas
	{
		Type& t = type<mud::Canvas>();
		static Meta meta = { t, &namspc({ "mud" }), "Canvas", sizeof(mud::Canvas), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::Canvas, mud::Widget>() },
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
		meta_class<mud::Canvas>();
	}
	// mud::Dockable
	{
		Type& t = type<mud::Dockable>();
		static Meta meta = { t, &namspc({ "mud" }), "Dockable", sizeof(mud::Dockable), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::Dockable, mud::Widget>() },
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
		meta_class<mud::Dockable>();
	}
	// mud::Docker
	{
		Type& t = type<mud::Docker>();
		static Meta meta = { t, &namspc({ "mud" }), "Docker", sizeof(mud::Docker), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::Docker, mud::Widget>() },
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
		meta_class<mud::Docker>();
	}
	// mud::Dockbar
	{
		Type& t = type<mud::Dockbar>();
		static Meta meta = { t, &namspc({ "mud" }), "Dockbar", sizeof(mud::Dockbar), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Docker>() },
			{ base_offset<mud::Dockbar, mud::Docker>() },
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
		meta_class<mud::Dockbar>();
	}
	// mud::Dockspace
	{
		Type& t = type<mud::Dockspace>();
		static Meta meta = { t, &namspc({ "mud" }), "Dockspace", sizeof(mud::Dockspace), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Docker>() },
			{ base_offset<mud::Dockspace, mud::Docker>() },
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
		meta_class<mud::Dockspace>();
	}
	// mud::Expandbox
	{
		Type& t = type<mud::Expandbox>();
		static Meta meta = { t, &namspc({ "mud" }), "Expandbox", sizeof(mud::Expandbox), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::Expandbox, mud::Widget>() },
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
		meta_class<mud::Expandbox>();
	}
	// mud::Node
	{
		Type& t = type<mud::Node>();
		static Meta meta = { t, &namspc({ "mud" }), "Node", sizeof(mud::Node), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::Node, mud::Widget>() },
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
		meta_class<mud::Node>();
	}
	// mud::NodePlug
	{
		Type& t = type<mud::NodePlug>();
		static Meta meta = { t, &namspc({ "mud" }), "NodePlug", sizeof(mud::NodePlug), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::NodePlug, mud::Widget>() },
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
		meta_class<mud::NodePlug>();
	}
	// mud::RowSolver
	{
		Type& t = type<mud::RowSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "RowSolver", sizeof(mud::RowSolver), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::FrameSolver>() },
			{ base_offset<mud::RowSolver, mud::FrameSolver>() },
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
		meta_class<mud::RowSolver>();
	}
	// mud::ScrollSheet
	{
		Type& t = type<mud::ScrollSheet>();
		static Meta meta = { t, &namspc({ "mud" }), "ScrollSheet", sizeof(mud::ScrollSheet), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::ScrollSheet, mud::Widget>() },
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
		meta_class<mud::ScrollSheet>();
	}
	// mud::ui::Sequence
	{
		Type& t = type<mud::ui::Sequence>();
		static Meta meta = { t, &namspc({ "mud", "ui" }), "Sequence", sizeof(mud::ui::Sequence), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::ui::Sequence, mud::Widget>() },
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
		meta_class<mud::ui::Sequence>();
	}
	// mud::Tabber
	{
		Type& t = type<mud::Tabber>();
		static Meta meta = { t, &namspc({ "mud" }), "Tabber", sizeof(mud::Tabber), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::Tabber, mud::Widget>() },
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
		meta_class<mud::Tabber>();
	}
	// mud::Table
	{
		Type& t = type<mud::Table>();
		static Meta meta = { t, &namspc({ "mud" }), "Table", sizeof(mud::Table), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::Table, mud::Widget>() },
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
		meta_class<mud::Table>();
	}
	// mud::TextEdit
	{
		Type& t = type<mud::TextEdit>();
		static Meta meta = { t, &namspc({ "mud" }), "TextEdit", sizeof(mud::TextEdit), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::TextEdit, mud::Widget>() },
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
		meta_class<mud::TextEdit>();
	}
	// mud::TreeNode
	{
		Type& t = type<mud::TreeNode>();
		static Meta meta = { t, &namspc({ "mud" }), "TreeNode", sizeof(mud::TreeNode), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::TreeNode, mud::Widget>() },
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
		meta_class<mud::TreeNode>();
	}
	// mud::Ui
	{
		Type& t = type<mud::Ui>();
		static Meta meta = { t, &namspc({ "mud" }), "Ui", sizeof(mud::Ui), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Widget>() },
			{ base_offset<mud::Ui, mud::Widget>() },
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
				{ t, "begin", member_address<mud::Widget&(mud::Ui::*)()>(&mud::Ui::begin), [](Ref object, array<Var> args, Var& result) { UNUSED(args); result = Ref(&val<mud::Ui>(object).begin()); }, {}, Ref(type<mud::Widget>()) }
			},
			// static members
			{
			}
		};
		meta_class<mud::Ui>();
	}
	// mud::Window
	{
		Type& t = type<mud::Window>();
		static Meta meta = { t, &namspc({ "mud" }), "Window", sizeof(mud::Window), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Dockable>() },
			{ base_offset<mud::Window, mud::Dockable>() },
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
		meta_class<mud::Window>();
	}
		m.m_types.push_back(&type<mud::Align>());
		m.m_types.push_back(&type<mud::AutoLayout>());
		m.m_types.push_back(&type<mud::CanvasConnect>());
		m.m_types.push_back(&type<mud::Clipboard>());
		m.m_types.push_back(&type<mud::Clipping>());
		m.m_types.push_back(&type<mud::Dim>());
		m.m_types.push_back(&type<mud::Dim2<bool>>());
		m.m_types.push_back(&type<mud::Dim2<mud::Align>>());
		m.m_types.push_back(&type<mud::Dim2<mud::AutoLayout>>());
		m.m_types.push_back(&type<mud::Dim2<mud::Pivot>>());
		m.m_types.push_back(&type<mud::Dim2<mud::Sizing>>());
		m.m_types.push_back(&type<mud::Dim2<size_t>>());
		m.m_types.push_back(&type<mud::Dock>());
		m.m_types.push_back(&type<mud::Docksystem>());
		m.m_types.push_back(&type<mud::Flow>());
		m.m_types.push_back(&type<mud::FlowAxis>());
		m.m_types.push_back(&type<mud::Gradient>());
		m.m_types.push_back(&type<mud::GridSolver>());
		m.m_types.push_back(&type<mud::ImageSkin>());
		m.m_types.push_back(&type<mud::InkStyle>());
		m.m_types.push_back(&type<mud::Layer>());
		m.m_types.push_back(&type<mud::Layout>());
		m.m_types.push_back(&type<mud::LayoutSolver>());
		m.m_types.push_back(&type<mud::NodeConnection>());
		m.m_types.push_back(&type<mud::Opacity>());
		m.m_types.push_back(&type<mud::Paint>());
		m.m_types.push_back(&type<mud::Pivot>());
		m.m_types.push_back(&type<mud::ui::PopupFlags>());
		m.m_types.push_back(&type<mud::Shadow>());
		m.m_types.push_back(&type<mud::Sizing>());
		m.m_types.push_back(&type<mud::Space>());
		m.m_types.push_back(&type<mud::SpacePreset>());
		m.m_types.push_back(&type<mud::Style>());
		m.m_types.push_back(&type<mud::TableSolver>());
		m.m_types.push_back(&type<mud::Text>());
		m.m_types.push_back(&type<mud::TextCursor>());
		m.m_types.push_back(&type<mud::TextMarker>());
		m.m_types.push_back(&type<mud::TextPaint>());
		m.m_types.push_back(&type<mud::TextSelection>());
		m.m_types.push_back(&type<mud::UiRect>());
		m.m_types.push_back(&type<mud::UiWindow>());
		m.m_types.push_back(&type<mud::User>());
		m.m_types.push_back(&type<mud::Vg>());
		m.m_types.push_back(&type<mud::WidgetState>());
		m.m_types.push_back(&type<mud::WindowState>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<float>>());
		m.m_types.push_back(&type<vector<mud::Space>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<mud::Dockable>());
		m.m_types.push_back(&type<mud::Frame>());
		m.m_types.push_back(&type<mud::Widget>());
		m.m_types.push_back(&type<mud::Canvas>());
		m.m_types.push_back(&type<mud::Docker>());
		m.m_types.push_back(&type<mud::Dockbar>());
		m.m_types.push_back(&type<mud::Dockspace>());
		m.m_types.push_back(&type<mud::Expandbox>());
		m.m_types.push_back(&type<mud::FrameSolver>());
		m.m_types.push_back(&type<mud::RowSolver>());
		m.m_types.push_back(&type<mud::LineSolver>());
		m.m_types.push_back(&type<mud::Node>());
		m.m_types.push_back(&type<mud::NodePlug>());
		m.m_types.push_back(&type<mud::ScrollSheet>());
		m.m_types.push_back(&type<mud::ui::Sequence>());
		m.m_types.push_back(&type<mud::Tabber>());
		m.m_types.push_back(&type<mud::Table>());
		m.m_types.push_back(&type<mud::TextEdit>());
		m.m_types.push_back(&type<mud::TreeNode>());
		m.m_types.push_back(&type<mud::Ui>());
		m.m_types.push_back(&type<mud::Window>());
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::widget(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<bool>(args[2]), val<mud::Dim>(args[3]), val<mud::Dim2<size_t>>(args[4]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "open", var(bool(false)), Param::Default }, { "length", var(mud::Dim(DIM_NONE)), Param::Default }, { "index", var(mud::Dim2<size_t>{0,0}), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "widget", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, bool, mud::Dim, mud::Dim2<size_t>)>(&mud::ui::widget), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::item(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<const char*>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "content", Ref(type<const char*>()), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "item", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, const char*)>(&mud::ui::item), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::multi_item(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<array<const char*>>(args[2]), &val<mud::Style>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "elements", var(array<const char*>()) }, { "element_style", Ref(type<mud::Style>()), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "multi_item", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, array<const char*>, mud::Style*)>(&mud::ui::multi_item), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::spanner(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<mud::Dim>(args[2]), val<float>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "dim", var(mud::Dim()) }, { "span", var(float()) } };
			static Function f = { &namspc({ "mud", "ui" }), "spanner", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, mud::Dim, float)>(&mud::ui::spanner), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::spacer(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "spacer", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::spacer), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::icon(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "image", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "icon", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::icon), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::label(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "label", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::label), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::title(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "title", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::title), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::message(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "message", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::message), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::text(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "text", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::text), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::button(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "content", Ref(type<const char*>()), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "button", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::button), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::toggle(val<mud::Widget>(args[0]), val<bool>(args[1]), val<const char*>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "on", var(bool()) }, { "content", Ref(type<const char*>()), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "toggle", funcptr<mud::Widget&(*)(mud::Widget&, bool&, const char*)>(&mud::ui::toggle), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::button(val<mud::Widget>(args[0]), val<string>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "content", var(string()) } };
			static Function f = { &namspc({ "mud", "ui" }), "button", funcptr<mud::Widget&(*)(mud::Widget&, const string&)>(&mud::ui::button), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::toggle(val<mud::Widget>(args[0]), val<bool>(args[1]), val<string>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "on", var(bool()) }, { "content", var(string()) } };
			static Function f = { &namspc({ "mud", "ui" }), "toggle", funcptr<mud::Widget&(*)(mud::Widget&, bool&, const string&)>(&mud::ui::toggle), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::multi_button(val<mud::Widget>(args[0]), val<array<const char*>>(args[1]), &val<mud::Style>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "elements", var(array<const char*>()) }, { "element_style", Ref(type<mud::Style>()), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "multi_button", funcptr<mud::Widget&(*)(mud::Widget&, array<const char*>, mud::Style*)>(&mud::ui::multi_button), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::multi_toggle(val<mud::Widget>(args[0]), val<bool>(args[1]), val<array<const char*>>(args[2]), &val<mud::Style>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "on", var(bool()) }, { "elements", var(array<const char*>()) }, { "element_style", Ref(type<mud::Style>()), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "multi_toggle", funcptr<mud::Widget&(*)(mud::Widget&, bool&, array<const char*>, mud::Style*)>(&mud::ui::multi_toggle), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::modal_button(val<mud::Widget>(args[0]), val<mud::Widget>(args[1]), val<const char*>(args[2]), val<uint32_t>(args[3])); };
			vector<Param> params = { { "screen", Ref(type<mud::Widget>()) }, { "parent", Ref(type<mud::Widget>()) }, { "content", Ref(type<const char*>()), Param::Nullable }, { "mode", var(uint32_t()) } };
			static Function f = { &namspc({ "mud", "ui" }), "modal_button", funcptr<bool(*)(mud::Widget&, mud::Widget&, const char*, uint32_t)>(&mud::ui::modal_button), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::modal_multi_button(val<mud::Widget>(args[0]), val<mud::Widget>(args[1]), val<array<const char*>>(args[2]), val<uint32_t>(args[3])); };
			vector<Param> params = { { "screen", Ref(type<mud::Widget>()) }, { "parent", Ref(type<mud::Widget>()) }, { "elements", var(array<const char*>()) }, { "mode", var(uint32_t()) } };
			static Function f = { &namspc({ "mud", "ui" }), "modal_multi_button", funcptr<bool(*)(mud::Widget&, mud::Widget&, array<const char*>, uint32_t)>(&mud::ui::modal_multi_button), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::checkbox(val<mud::Widget>(args[0]), val<bool>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "on", var(bool()) } };
			static Function f = { &namspc({ "mud", "ui" }), "checkbox", funcptr<mud::Widget&(*)(mud::Widget&, bool&)>(&mud::ui::checkbox), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::fill_bar(val<mud::Widget>(args[0]), val<float>(args[1]), val<mud::Dim>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "percentage", var(float()) }, { "dim", var(mud::Dim(DIM_X)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "fill_bar", funcptr<mud::Widget&(*)(mud::Widget&, float, mud::Dim)>(&mud::ui::fill_bar), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::image256(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<mud::Image256>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "source", var(mud::Image256()) } };
			static Function f = { &namspc({ "mud", "ui" }), "image256", funcptr<mud::Widget&(*)(mud::Widget&, const char*, const mud::Image256&)>(&mud::ui::image256), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::image256(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<mud::Image256>(args[2]), val<mud::vec2>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "source", var(mud::Image256()) }, { "size", var(mud::vec2()) } };
			static Function f = { &namspc({ "mud", "ui" }), "image256", funcptr<mud::Widget&(*)(mud::Widget&, const char*, const mud::Image256&, const mud::vec2&)>(&mud::ui::image256), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::image256(val<mud::Widget>(args[0]), val<string>(args[1]), val<mud::Image256>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(string()) }, { "source", var(mud::Image256()) } };
			static Function f = { &namspc({ "mud", "ui" }), "image256", funcptr<mud::Widget&(*)(mud::Widget&, const string&, const mud::Image256&)>(&mud::ui::image256), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::image256(val<mud::Widget>(args[0]), val<string>(args[1]), val<mud::Image256>(args[2]), val<mud::vec2>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(string()) }, { "source", var(mud::Image256()) }, { "size", var(mud::vec2()) } };
			static Function f = { &namspc({ "mud", "ui" }), "image256", funcptr<mud::Widget&(*)(mud::Widget&, const string&, const mud::Image256&, const mud::vec2&)>(&mud::ui::image256), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::radio_choice(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<bool>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", Ref(type<const char*>()), Param::Nullable }, { "active", var(bool()) } };
			static Function f = { &namspc({ "mud", "ui" }), "radio_choice", funcptr<mud::Widget&(*)(mud::Widget&, const char*, bool)>(&mud::ui::radio_choice), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::radio_switch(val<mud::Widget>(args[0]), val<array<const char*>>(args[1]), val<uint32_t>(args[2]), val<mud::Dim>(args[3])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "labels", var(array<const char*>()) }, { "value", var(uint32_t()) }, { "dim", var(mud::Dim(DIM_X)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "radio_switch", funcptr<bool(*)(mud::Widget&, array<const char*>, uint32_t&, mud::Dim)>(&mud::ui::radio_switch), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::popdown(val<mud::Widget>(args[0]), val<array<const char*>>(args[1]), val<uint32_t>(args[2]), val<mud::vec2>(args[3]), val<mud::ui::PopupFlags>(args[4])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "choices", var(array<const char*>()) }, { "value", var(uint32_t()) }, { "position", var(mud::vec2()) }, { "flags", var(mud::ui::PopupFlags()) } };
			static Function f = { &namspc({ "mud", "ui" }), "popdown", funcptr<bool(*)(mud::Widget&, array<const char*>, uint32_t&, mud::vec2, mud::ui::PopupFlags)>(&mud::ui::popdown), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dropdown(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<const char*>(args[2]), val<mud::ui::PopupFlags>(args[3]), &val<mud::Style>(args[4]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "value", Ref(type<const char*>()), Param::Nullable }, { "flags", var(mud::ui::PopupFlags()) }, { "list_style", Ref(type<mud::Style>()), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "dropdown", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, const char*, mud::ui::PopupFlags, mud::Style*)>(&mud::ui::dropdown), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::dropdown_input(val<mud::Widget>(args[0]), val<array<const char*>>(args[1]), val<uint32_t>(args[2]), val<bool>(args[3])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "choices", var(array<const char*>()) }, { "value", var(uint32_t()) }, { "compact", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "dropdown_input", funcptr<bool(*)(mud::Widget&, array<const char*>, uint32_t&, bool)>(&mud::ui::dropdown_input), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::typedown_input(val<mud::Widget>(args[0]), val<array<const char*>>(args[1]), val<uint32_t>(args[2])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "choices", var(array<const char*>()) }, { "value", var(uint32_t()) } };
			static Function f = { &namspc({ "mud", "ui" }), "typedown_input", funcptr<bool(*)(mud::Widget&, array<const char*>, uint32_t&)>(&mud::ui::typedown_input), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::menu_choice(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "content", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "menu_choice", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::menu_choice), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::menu(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<bool>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", Ref(type<const char*>()), Param::Nullable }, { "submenu", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "menu", funcptr<mud::Widget&(*)(mud::Widget&, const char*, bool)>(&mud::ui::menu), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::menubar(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "menubar", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::menubar), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::toolbutton(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "icon", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "toolbutton", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::toolbutton), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::tooldock(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "tooldock", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::tooldock), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::toolbar(val<mud::Widget>(args[0]), val<bool>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "wrap", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "toolbar", funcptr<mud::Widget&(*)(mud::Widget&, bool)>(&mud::ui::toolbar), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::select_list(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "select_list", funcptr<mud::ScrollSheet&(*)(mud::Widget&)>(&mud::ui::select_list), func, params, Ref(type<mud::ScrollSheet>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::columns(val<mud::Widget>(args[0]), val<array<float>>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "weights", var(array<float>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "columns", funcptr<mud::Table&(*)(mud::Widget&, array<float>)>(&mud::ui::columns), func, params, Ref(type<mud::Table>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::table(val<mud::Widget>(args[0]), val<array<const char*>>(args[1]), val<array<float>>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "columns", var(array<const char*>()) }, { "weights", var(array<float>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "table", funcptr<mud::Table&(*)(mud::Widget&, array<const char*>, array<float>)>(&mud::ui::table), func, params, Ref(type<mud::Table>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::table_row(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "table_row", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::table_row), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::table_separator(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "table_separator", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::table_separator), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::expandbox(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<bool>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "open", var(bool(true)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "expandbox", funcptr<mud::Expandbox&(*)(mud::Widget&, const char*, bool)>(&mud::ui::expandbox), func, params, Ref(type<mud::Expandbox>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::tree_node(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<bool>(args[2]), val<bool>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "leaf", var(bool(false)), Param::Default }, { "open", var(bool(true)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "tree_node", funcptr<mud::TreeNode&(*)(mud::Widget&, const char*, bool, bool)>(&mud::ui::tree_node), func, params, Ref(type<mud::TreeNode>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::tree(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "tree", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::tree), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::tab(val<mud::Tabber>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "tabber", Ref(type<mud::Tabber>()) }, { "name", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "tab", funcptr<mud::Widget*(*)(mud::Tabber&, const char*)>(&mud::ui::tab), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::tabber(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "tabber", funcptr<mud::Tabber&(*)(mud::Widget&)>(&mud::ui::tabber), func, params, Ref(type<mud::Tabber>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::row(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "row", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::row), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::header(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "header", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::header), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::div(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "div", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::div), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::stack(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "stack", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::stack), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::sheet(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "sheet", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::sheet), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::board(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "board", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::board), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::layout(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "layout", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::layout), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::screen(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "screen", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::screen), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::decal(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "decal", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::decal), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::overlay(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "overlay", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::overlay), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::title_header(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "title", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "title_header", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::title_header), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dummy(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()) } };
			static Function f = { &namspc({ "mud", "ui" }), "dummy", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&)>(&mud::ui::dummy), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::popup(val<mud::Widget>(args[0]), val<mud::ui::PopupFlags>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "flags", var(mud::ui::PopupFlags()) } };
			static Function f = { &namspc({ "mud", "ui" }), "popup", funcptr<mud::Widget&(*)(mud::Widget&, mud::ui::PopupFlags)>(&mud::ui::popup), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::popup(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]), val<mud::ui::PopupFlags>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()) }, { "flags", var(mud::ui::PopupFlags::None), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "popup", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&, mud::ui::PopupFlags)>(&mud::ui::popup), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::popup_at(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]), val<mud::ui::PopupFlags>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "position", var(mud::vec2()) }, { "flags", var(mud::ui::PopupFlags::None), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "popup_at", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&, mud::ui::PopupFlags)>(&mud::ui::popup_at), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::modal(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "modal", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::modal), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::modal(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()) } };
			static Function f = { &namspc({ "mud", "ui" }), "modal", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&)>(&mud::ui::modal), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::auto_modal(val<mud::Widget>(args[0]), val<uint32_t>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "mode", var(uint32_t()) } };
			static Function f = { &namspc({ "mud", "ui" }), "auto_modal", funcptr<mud::Widget&(*)(mud::Widget&, uint32_t)>(&mud::ui::auto_modal), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::auto_modal(val<mud::Widget>(args[0]), val<uint32_t>(args[1]), val<mud::vec2>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "mode", var(uint32_t()) }, { "size", var(mud::vec2()) } };
			static Function f = { &namspc({ "mud", "ui" }), "auto_modal", funcptr<mud::Widget&(*)(mud::Widget&, uint32_t, const mud::vec2&)>(&mud::ui::auto_modal), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::context(val<mud::Widget>(args[0]), val<uint32_t>(args[1]), val<mud::ui::PopupFlags>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "mode", var(uint32_t()) }, { "flags", var(mud::ui::PopupFlags::None), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "context", funcptr<mud::Widget*(*)(mud::Widget&, uint32_t, mud::ui::PopupFlags)>(&mud::ui::context), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::hoverbox(val<mud::Widget>(args[0]), val<float>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "delay", var(float(0.5f)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "hoverbox", funcptr<mud::Widget*(*)(mud::Widget&, float)>(&mud::ui::hoverbox), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::tooltip(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]), val<const char*>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "position", var(mud::vec2()) }, { "content", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "tooltip", funcptr<mud::Widget*(*)(mud::Widget&, const mud::vec2&, const char*)>(&mud::ui::tooltip), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::cursor(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]), val<mud::Widget>(args[2]), val<bool>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "position", var(mud::vec2()) }, { "hovered", Ref(type<mud::Widget>()) }, { "locked", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "cursor", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&, mud::Widget&, bool)>(&mud::ui::cursor), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::rectangle(val<mud::Widget>(args[0]), val<mud::vec4>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "rect", var(mud::vec4()) } };
			static Function f = { &namspc({ "mud", "ui" }), "rectangle", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec4&)>(&mud::ui::rectangle), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dockspace(val<mud::Widget>(args[0]), val<mud::Docksystem>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "docksystem", Ref(type<mud::Docksystem>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "dockspace", funcptr<mud::Dockspace&(*)(mud::Widget&, mud::Docksystem&)>(&mud::ui::dockspace), func, params, Ref(type<mud::Dockspace>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dockbar(val<mud::Widget>(args[0]), val<mud::Docksystem>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "docksystem", Ref(type<mud::Docksystem>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "dockbar", funcptr<mud::Dockbar&(*)(mud::Widget&, mud::Docksystem&)>(&mud::ui::dockbar), func, params, Ref(type<mud::Dockbar>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::dockitem(val<mud::Widget>(args[0]), val<mud::Docksystem>(args[1]), val<mud::Dock>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "docksystem", Ref(type<mud::Docksystem>()) }, { "dock", var(mud::Dock()) } };
			static Function f = { &namspc({ "mud", "ui" }), "dockitem", funcptr<mud::Widget*(*)(mud::Widget&, mud::Docksystem&, mud::Dock&)>(&mud::ui::dockitem), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::text_box(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<string>(args[2]), val<bool>(args[3]), val<size_t>(args[4]), val<string>(args[5]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "text", var(string()) }, { "editor", var(bool(false)), Param::Default }, { "lines", var(size_t(1)), Param::Default }, { "allowed_chars", var(string("")), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "text_box", funcptr<mud::TextEdit&(*)(mud::Widget&, mud::Style&, string&, bool, size_t, const string&)>(&mud::ui::text_box), func, params, Ref(type<mud::TextEdit>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::type_in(val<mud::Widget>(args[0]), val<string>(args[1]), val<size_t>(args[2]), val<string>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "text", var(string()) }, { "lines", var(size_t(1)), Param::Default }, { "allowed_chars", var(string("")), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "type_in", funcptr<mud::TextEdit&(*)(mud::Widget&, string&, size_t, const string&)>(&mud::ui::type_in), func, params, Ref(type<mud::TextEdit>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::text_edit(val<mud::Widget>(args[0]), val<string>(args[1]), val<size_t>(args[2]), &val<vector<string>>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "text", var(string()) }, { "lines", var(size_t(1)), Param::Default }, { "vocabulary", Ref(type<vector<string>>()), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "text_edit", funcptr<mud::TextEdit&(*)(mud::Widget&, string&, size_t, vector<string>*)>(&mud::ui::text_edit), func, params, Ref(type<mud::TextEdit>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::code_edit(val<mud::Widget>(args[0]), val<string>(args[1]), val<size_t>(args[2]), &val<vector<string>>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "text", var(string()) }, { "lines", var(size_t(1)), Param::Default }, { "vocabulary", Ref(type<vector<string>>()), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "code_edit", funcptr<mud::TextEdit&(*)(mud::Widget&, string&, size_t, vector<string>*)>(&mud::ui::code_edit), func, params, Ref(type<mud::TextEdit>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::drag_float(val<mud::Widget>(args[0]), val<float>(args[1]), val<float>(args[2])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(float()) }, { "step", var(float(0.1f)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "drag_float", funcptr<bool(*)(mud::Widget&, float&, float)>(&mud::ui::drag_float), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::vec2_edit(val<mud::Widget>(args[0]), val<mud::vec2>(args[1])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "vec", var(mud::vec2()) } };
			static Function f = { &namspc({ "mud", "ui" }), "vec2_edit", funcptr<bool(*)(mud::Widget&, mud::vec2&)>(&mud::ui::vec2_edit), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::vec3_edit(val<mud::Widget>(args[0]), val<mud::vec3>(args[1])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "vec", var(mud::vec3()) } };
			static Function f = { &namspc({ "mud", "ui" }), "vec3_edit", funcptr<bool(*)(mud::Widget&, mud::vec3&)>(&mud::ui::vec3_edit), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::quat_edit(val<mud::Widget>(args[0]), val<mud::quat>(args[1])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "quat", var(mud::quat()) } };
			static Function f = { &namspc({ "mud", "ui" }), "quat_edit", funcptr<bool(*)(mud::Widget&, mud::quat&)>(&mud::ui::quat_edit), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_edit_hsl(val<mud::Widget>(args[0]), val<mud::Colour>(args[1]), val<mud::Colour>(args[2])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "colour", var(mud::Colour()) }, { "value", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud", "ui" }), "color_edit_hsl", funcptr<bool(*)(mud::Widget&, const mud::Colour&, mud::Colour&)>(&mud::ui::color_edit_hsl), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::color_display(val<mud::Widget>(args[0]), val<mud::Colour>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud", "ui" }), "color_display", funcptr<mud::Widget&(*)(mud::Widget&, const mud::Colour&)>(&mud::ui::color_display), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_edit(val<mud::Widget>(args[0]), val<mud::Colour>(args[1])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud", "ui" }), "color_edit", funcptr<bool(*)(mud::Widget&, mud::Colour&)>(&mud::ui::color_edit), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_edit_simple(val<mud::Widget>(args[0]), val<mud::Colour>(args[1])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud", "ui" }), "color_edit_simple", funcptr<bool(*)(mud::Widget&, mud::Colour&)>(&mud::ui::color_edit_simple), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_toggle_edit(val<mud::Widget>(args[0]), val<mud::Colour>(args[1])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud", "ui" }), "color_toggle_edit", funcptr<bool(*)(mud::Widget&, mud::Colour&)>(&mud::ui::color_toggle_edit), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::curve_graph(val<mud::Widget>(args[0]), val<array<float>>(args[1]), val<array<float>>(args[2])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "values", var(array<float>()) }, { "points", var(array<float>{}), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "curve_graph", funcptr<bool(*)(mud::Widget&, array<float>, array<float>)>(&mud::ui::curve_graph), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::curve_edit(val<mud::Widget>(args[0]), val<array<float>>(args[1]), val<array<float>>(args[2])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "values", var(array<float>()) }, { "points", var(array<float>{}), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "curve_edit", funcptr<bool(*)(mud::Widget&, array<float>, array<float>)>(&mud::ui::curve_edit), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::flag_field(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<uint32_t>(args[2]), val<uint8_t>(args[3]), val<bool>(args[4])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "value", var(uint32_t()) }, { "shift", var(uint8_t()) }, { "reverse", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "flag_field", funcptr<bool(*)(mud::Widget&, const char*, uint32_t&, uint8_t, bool)>(&mud::ui::flag_field), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::radio_field(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<array<const char*>>(args[2]), val<uint32_t>(args[3]), val<mud::Dim>(args[4]), val<bool>(args[5])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "choices", var(array<const char*>()) }, { "value", var(uint32_t()) }, { "dim", var(mud::Dim(DIM_X)), Param::Default }, { "reverse", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "radio_field", funcptr<bool(*)(mud::Widget&, const char*, array<const char*>, uint32_t&, mud::Dim, bool)>(&mud::ui::radio_field), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::dropdown_field(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<array<const char*>>(args[2]), val<uint32_t>(args[3]), val<bool>(args[4])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "choices", var(array<const char*>()) }, { "value", var(uint32_t()) }, { "reverse", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "dropdown_field", funcptr<bool(*)(mud::Widget&, const char*, array<const char*>, uint32_t&, bool)>(&mud::ui::dropdown_field), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::typedown_field(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<array<const char*>>(args[2]), val<uint32_t>(args[3]), val<bool>(args[4])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "choices", var(array<const char*>()) }, { "value", var(uint32_t()) }, { "reverse", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "typedown_field", funcptr<bool(*)(mud::Widget&, const char*, array<const char*>, uint32_t&, bool)>(&mud::ui::typedown_field), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_field(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<mud::Colour>(args[2]), val<bool>(args[3])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "value", var(mud::Colour()) }, { "reverse", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "color_field", funcptr<bool(*)(mud::Widget&, const char*, mud::Colour&, bool)>(&mud::ui::color_field), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::ui::color_display_field(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<mud::Colour>(args[2]), val<bool>(args[3])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "value", var(mud::Colour()) }, { "reverse", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "color_display_field", funcptr<void(*)(mud::Widget&, const char*, const mud::Colour&, bool)>(&mud::ui::color_display_field), func, params, Var() };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::node_input(val<mud::Node>(args[0]), val<const char*>(args[1]), val<const char*>(args[2]), val<mud::Colour>(args[3]), val<bool>(args[4]), val<bool>(args[5]))); };
			vector<Param> params = { { "node", Ref(type<mud::Node>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "icon", Ref(type<const char*>()), Param::Flags(Param::Nullable|Param::Default) }, { "colour", var(mud::Colour::NeonGreen), Param::Default }, { "active", var(bool(true)), Param::Default }, { "connected", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "node_input", funcptr<mud::NodePlug&(*)(mud::Node&, const char*, const char*, const mud::Colour&, bool, bool)>(&mud::ui::node_input), func, params, Ref(type<mud::NodePlug>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::node_output(val<mud::Node>(args[0]), val<const char*>(args[1]), val<const char*>(args[2]), val<mud::Colour>(args[3]), val<bool>(args[4]), val<bool>(args[5]))); };
			vector<Param> params = { { "node", Ref(type<mud::Node>()) }, { "name", Ref(type<const char*>()), Param::Nullable }, { "icon", Ref(type<const char*>()), Param::Flags(Param::Nullable|Param::Default) }, { "colour", var(mud::Colour::NeonGreen), Param::Default }, { "active", var(bool(true)), Param::Default }, { "connected", var(bool(false)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "node_output", funcptr<mud::NodePlug&(*)(mud::Node&, const char*, const char*, const mud::Colour&, bool, bool)>(&mud::ui::node_output), func, params, Ref(type<mud::NodePlug>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::node(val<mud::Canvas>(args[0]), val<const char*>(args[1]), val<mud::vec2>(args[2]), val<int>(args[3]), args[4])); };
			vector<Param> params = { { "parent", Ref(type<mud::Canvas>()) }, { "title", Ref(type<const char*>()), Param::Nullable }, { "position", var(mud::vec2()) }, { "order", var(int(0)), Param::Default }, { "identity", Ref(), Param::Flags(Param::Nullable|Param::Default) } };
			static Function f = { &namspc({ "mud", "ui" }), "node", funcptr<mud::Node&(*)(mud::Canvas&, const char*, mud::vec2&, int, mud::Ref)>(&mud::ui::node), func, params, Ref(type<mud::Node>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::node_cable(val<mud::Canvas>(args[0]), val<mud::NodePlug>(args[1]), val<mud::NodePlug>(args[2]))); };
			vector<Param> params = { { "canvas", Ref(type<mud::Canvas>()) }, { "plug_out", Ref(type<mud::NodePlug>()) }, { "plug_in", Ref(type<mud::NodePlug>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "node_cable", funcptr<mud::Widget&(*)(mud::Canvas&, mud::NodePlug&, mud::NodePlug&)>(&mud::ui::node_cable), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::canvas(val<mud::Widget>(args[0]), val<size_t>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "num_nodes", var(size_t(0)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "canvas", funcptr<mud::Canvas&(*)(mud::Widget&, size_t)>(&mud::ui::canvas), func, params, Ref(type<mud::Canvas>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::scrollable(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "scrollable", funcptr<mud::Widget&(*)(mud::Widget&)>(&mud::ui::scrollable), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::sequence(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "sequence", funcptr<mud::ui::Sequence&(*)(mud::Widget&)>(&mud::ui::sequence), func, params, Ref(type<mud::ui::Sequence>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::scroll_sequence(val<mud::Widget>(args[0]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "scroll_sequence", funcptr<mud::ui::Sequence&(*)(mud::Widget&)>(&mud::ui::scroll_sequence), func, params, Ref(type<mud::ui::Sequence>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::multiselect_logic(val<mud::Widget>(args[0]), args[1], val<vector<mud::Ref>>(args[2])); };
			vector<Param> params = { { "element", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable }, { "selection", var(vector<mud::Ref>()) } };
			static Function f = { &namspc({ "mud", "ui" }), "multiselect_logic", funcptr<bool(*)(mud::Widget&, mud::Ref, vector<mud::Ref>&)>(&mud::ui::multiselect_logic), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::select_logic(val<mud::Widget>(args[0]), args[1], args[2]); };
			vector<Param> params = { { "element", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable }, { "selection", Ref(), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "select_logic", funcptr<bool(*)(mud::Widget&, mud::Ref, mud::Ref&)>(&mud::ui::select_logic), func, params, var(bool()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::element(val<mud::Widget>(args[0]), args[1])); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "element", funcptr<mud::Widget&(*)(mud::Widget&, mud::Ref)>(&mud::ui::element), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::sequence_element(val<mud::ui::Sequence>(args[0]), args[1])); };
			vector<Param> params = { { "parent", Ref(type<mud::ui::Sequence>()) }, { "object", Ref(), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "sequence_element", funcptr<mud::Widget&(*)(mud::ui::Sequence&, mud::Ref)>(&mud::ui::sequence_element), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::window(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<mud::WindowState>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "title", Ref(type<const char*>()), Param::Nullable }, { "state", var(mud::WindowState(WINDOW_DEFAULT)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "window", funcptr<mud::Window&(*)(mud::Widget&, const char*, mud::WindowState)>(&mud::ui::window), func, params, Ref(type<mud::Window>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dir_item(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "dir_item", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::dir_item), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_item(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "file_item", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::file_item), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_list(val<mud::Widget>(args[0]), val<string>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "path", var(string()) } };
			static Function f = { &namspc({ "mud", "ui" }), "file_list", funcptr<mud::Widget&(*)(mud::Widget&, string&)>(&mud::ui::file_list), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_browser(val<mud::Widget>(args[0]), val<string>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "path", var(string()) } };
			static Function f = { &namspc({ "mud", "ui" }), "file_browser", funcptr<mud::Widget&(*)(mud::Widget&, string&)>(&mud::ui::file_browser), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dir_node(val<mud::Widget>(args[0]), val<const char*>(args[1]), val<const char*>(args[2]), val<bool>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "path", Ref(type<const char*>()), Param::Nullable }, { "name", Ref(type<const char*>()), Param::Nullable }, { "collapsed", var(bool()) } };
			static Function f = { &namspc({ "mud", "ui" }), "dir_node", funcptr<mud::Widget&(*)(mud::Widget&, const char*, const char*, bool)>(&mud::ui::dir_node), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_node(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "file_node", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::file_node), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_tree(val<mud::Widget>(args[0]), val<const char*>(args[1]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "path", Ref(type<const char*>()), Param::Nullable } };
			static Function f = { &namspc({ "mud", "ui" }), "file_tree", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(&mud::ui::file_tree), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::command_line(val<mud::Widget>(args[0]), val<string>(args[1]), val<string>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "text", var(string()) }, { "command", var(string()) } };
			static Function f = { &namspc({ "mud", "ui" }), "command_line", funcptr<mud::Widget&(*)(mud::Widget&, string&, string&)>(&mud::ui::command_line), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::console(val<mud::Widget>(args[0]), val<string>(args[1]), val<string>(args[2]), val<string>(args[3]), val<size_t>(args[4]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "feed", var(string()) }, { "line", var(string()) }, { "command", var(string()) }, { "num_lines", var(size_t(0)), Param::Default } };
			static Function f = { &namspc({ "mud", "ui" }), "console", funcptr<mud::Widget&(*)(mud::Widget&, string&, string&, string&, size_t)>(&mud::ui::console), func, params, Ref(type<mud::Widget>()) };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_ui::mud_ui()
		: Module("mud::ui", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_ctx::m() })
	{
		// setup reflection meta data
		mud_ui_meta(*this);
	}
}

#ifdef MUD_UI_MODULE
extern "C"
Module& getModule()
{
		return mud_ui::m();
}
#endif
