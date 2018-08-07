

#pragma once

#ifndef MUD_MODULES
#include <meta/ui/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_ui_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::Align>(), &namspc({ "mud" }), "Align", sizeof(mud::Align), TypeClass::Enum };
        static Enum enu = { type<mud::Align>(),
            false,
            { "Left", "CENTER", "Right", "OUT_LEFT", "OUT_RIGHT" },
            { 0, 1, 2, 3, 4 },
            { var(mud::Left), var(mud::CENTER), var(mud::Right), var(mud::OUT_LEFT), var(mud::OUT_RIGHT) }
        };
        meta_enum<mud::Align>();
    }
    
    {
        static Meta meta = { type<mud::AutoLayout>(), &namspc({ "mud" }), "AutoLayout", sizeof(mud::AutoLayout), TypeClass::Enum };
        static Enum enu = { type<mud::AutoLayout>(),
            false,
            { "NO_LAYOUT", "AUTO_SIZE", "AUTO_LAYOUT" },
            { 0, 1, 2 },
            { var(mud::NO_LAYOUT), var(mud::AUTO_SIZE), var(mud::AUTO_LAYOUT) }
        };
        meta_enum<mud::AutoLayout>();
    }
    
    {
        static Meta meta = { type<mud::Clipping>(), &namspc({ "mud" }), "Clipping", sizeof(mud::Clipping), TypeClass::Enum };
        static Enum enu = { type<mud::Clipping>(),
            false,
            { "NOCLIP", "CLIP", "UNCLIP" },
            { 0, 1, 2 },
            { var(mud::NOCLIP), var(mud::CLIP), var(mud::UNCLIP) }
        };
        meta_enum<mud::Clipping>();
    }
    
    {
        static Meta meta = { type<mud::Dim>(), &namspc({ "mud" }), "Dim", sizeof(mud::Dim), TypeClass::Enum };
        static Enum enu = { type<mud::Dim>(),
            false,
            { "DIM_X", "DIM_Y", "DIM_NONE" },
            { 0, 1, 2 },
            { var(mud::DIM_X), var(mud::DIM_Y), var(mud::DIM_NONE) }
        };
        meta_enum<mud::Dim>();
    }
    
    {
        static Meta meta = { type<mud::Flow>(), &namspc({ "mud" }), "Flow", sizeof(mud::Flow), TypeClass::Enum };
        static Enum enu = { type<mud::Flow>(),
            false,
            { "FLOW", "OVERLAY", "ALIGN", "FREE" },
            { 0, 1, 2, 3 },
            { var(mud::FLOW), var(mud::OVERLAY), var(mud::ALIGN), var(mud::FREE) }
        };
        meta_enum<mud::Flow>();
    }
    
    {
        static Meta meta = { type<mud::FlowAxis>(), &namspc({ "mud" }), "FlowAxis", sizeof(mud::FlowAxis), TypeClass::Enum };
        static Enum enu = { type<mud::FlowAxis>(),
            false,
            { "READING", "PARAGRAPH", "PARALLEL", "ORTHOGONAL", "AXIS_NONE" },
            { 0, 1, 2, 3, 4 },
            { var(mud::READING), var(mud::PARAGRAPH), var(mud::PARALLEL), var(mud::ORTHOGONAL), var(mud::AXIS_NONE) }
        };
        meta_enum<mud::FlowAxis>();
    }
    
    {
        static Meta meta = { type<mud::LayoutSolver>(), &namspc({ "mud" }), "LayoutSolver", sizeof(mud::LayoutSolver), TypeClass::Enum };
        static Enum enu = { type<mud::LayoutSolver>(),
            false,
            { "FRAME_SOLVER", "ROW_SOLVER", "GRID_SOLVER", "TABLE_SOLVER" },
            { 0, 1, 2, 3 },
            { var(mud::FRAME_SOLVER), var(mud::ROW_SOLVER), var(mud::GRID_SOLVER), var(mud::TABLE_SOLVER) }
        };
        meta_enum<mud::LayoutSolver>();
    }
    
    {
        static Meta meta = { type<mud::Opacity>(), &namspc({ "mud" }), "Opacity", sizeof(mud::Opacity), TypeClass::Enum };
        static Enum enu = { type<mud::Opacity>(),
            false,
            { "OPAQUE", "CLEAR", "HOLLOW" },
            { 0, 1, 2 },
            { var(mud::OPAQUE), var(mud::CLEAR), var(mud::HOLLOW) }
        };
        meta_enum<mud::Opacity>();
    }
    
    {
        static Meta meta = { type<mud::Pivot>(), &namspc({ "mud" }), "Pivot", sizeof(mud::Pivot), TypeClass::Enum };
        static Enum enu = { type<mud::Pivot>(),
            false,
            { "FORWARD", "REVERSE" },
            { 0, 1 },
            { var(mud::FORWARD), var(mud::REVERSE) }
        };
        meta_enum<mud::Pivot>();
    }
    
    {
        static Meta meta = { type<mud::Sizing>(), &namspc({ "mud" }), "Sizing", sizeof(mud::Sizing), TypeClass::Enum };
        static Enum enu = { type<mud::Sizing>(),
            false,
            { "FIXED", "SHRINK", "WRAP", "EXPAND" },
            { 0, 1, 2, 3 },
            { var(mud::FIXED), var(mud::SHRINK), var(mud::WRAP), var(mud::EXPAND) }
        };
        meta_enum<mud::Sizing>();
    }
    
    {
        static Meta meta = { type<mud::SpacePreset>(), &namspc({ "mud" }), "SpacePreset", sizeof(mud::SpacePreset), TypeClass::Enum };
        static Enum enu = { type<mud::SpacePreset>(),
            false,
            { "SHEET", "FLEX", "ITEM", "UNIT", "BLOCK", "LINE", "STACK", "DIV", "SPACER", "BOARD", "LAYOUT" },
            { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
            { var(mud::SHEET), var(mud::FLEX), var(mud::ITEM), var(mud::UNIT), var(mud::BLOCK), var(mud::LINE), var(mud::STACK), var(mud::DIV), var(mud::SPACER), var(mud::BOARD), var(mud::LAYOUT) }
        };
        meta_enum<mud::SpacePreset>();
    }
    
    {
        static Meta meta = { type<mud::WidgetState>(), &namspc({ "mud" }), "WidgetState", sizeof(mud::WidgetState), TypeClass::Enum };
        static Enum enu = { type<mud::WidgetState>(),
            false,
            { "NOSTATE", "CREATED", "HOVERED", "PRESSED", "ACTIVATED", "ACTIVE", "SELECTED", "DISABLED", "DRAGGED", "FOCUSED", "CLOSED" },
            { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 },
            { var(mud::NOSTATE), var(mud::CREATED), var(mud::HOVERED), var(mud::PRESSED), var(mud::ACTIVATED), var(mud::ACTIVE), var(mud::SELECTED), var(mud::DISABLED), var(mud::DRAGGED), var(mud::FOCUSED), var(mud::CLOSED) }
        };
        meta_enum<mud::WidgetState>();
    }
    
    {
        static Meta meta = { type<mud::WindowState>(), &namspc({ "mud" }), "WindowState", sizeof(mud::WindowState), TypeClass::Enum };
        static Enum enu = { type<mud::WindowState>(),
            false,
            { "WINDOW_NOSTATE", "WINDOW_HEADER", "WINDOW_DOCKABLE", "WINDOW_CLOSABLE", "WINDOW_MOVABLE", "WINDOW_SIZABLE", "WINDOW_DEFAULT" },
            { 0, 2, 4, 8, 16, 32, 58 },
            { var(mud::WINDOW_NOSTATE), var(mud::WINDOW_HEADER), var(mud::WINDOW_DOCKABLE), var(mud::WINDOW_CLOSABLE), var(mud::WINDOW_MOVABLE), var(mud::WINDOW_SIZABLE), var(mud::WINDOW_DEFAULT) }
        };
        meta_enum<mud::WindowState>();
    }
    
    
    // Sequences
    {
        static Meta meta = { type<array<cstring>>(), &namspc({}), "array<cstring>", sizeof(array<cstring>), TypeClass::Sequence };
        static Class cls = { type<array<cstring>>() };
        cls.m_content = &type<cstring>();
        meta_sequence<array<cstring>, cstring>();
    }
    
    {
        static Meta meta = { type<array<float>>(), &namspc({}), "array<float>", sizeof(array<float>), TypeClass::Sequence };
        static Class cls = { type<array<float>>() };
        cls.m_content = &type<float>();
        meta_sequence<array<float>, float>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::Space>>(), &namspc({}), "std::vector<mud::Space>", sizeof(std::vector<mud::Space>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Space>>() };
        cls.m_content = &type<mud::Space>();
        meta_sequence<std::vector<mud::Space>, mud::Space>();
    }
    
    {
        static Meta meta = { type<std::vector<std::string>>(), &namspc({}), "std::vector<std::string>", sizeof(std::vector<std::string>), TypeClass::Sequence };
        static Class cls = { type<std::vector<std::string>>() };
        cls.m_content = &type<std::string>();
        meta_sequence<std::vector<std::string>, std::string>();
    }
    
    
    
    
    
        
    // mud::CanvasConnect
    {
        static Meta meta = { type<mud::CanvasConnect>(), &namspc({ "mud" }), "CanvasConnect", sizeof(mud::CanvasConnect), TypeClass::Struct };
        static Class cls = { type<mud::CanvasConnect>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::CanvasConnect>(), [](Ref ref, Ref other) { new(&val<mud::CanvasConnect>(ref)) mud::CanvasConnect(val<mud::CanvasConnect>(other)); } }
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
    
    
    
    
    
        
    // mud::Dim2<bool>
    {
        static Meta meta = { type<mud::Dim2<bool>>(), &namspc({ "mud" }), "Dim2<bool>", sizeof(mud::Dim2<bool>), TypeClass::Struct };
        static Class cls = { type<mud::Dim2<bool>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Dim2<bool>>(), [](Ref ref, array<Var> args) { new(&val<mud::Dim2<bool>>(ref)) mud::Dim2<bool>( val<bool>(args[0]), val<bool>(args[1]) ); }, { { "a", var(bool()) }, { "b", var(bool()) } } },
                { type<mud::Dim2<bool>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Dim2<bool>>(ref)) mud::Dim2<bool>(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Dim2<bool>>(), [](Ref ref, Ref other) { new(&val<mud::Dim2<bool>>(ref)) mud::Dim2<bool>(val<mud::Dim2<bool>>(other)); } }
            },
            // members
            {
                { type<mud::Dim2<bool>>(), member_address(&mud::Dim2<bool>::x), type<bool>(), "x", var(bool()), Member::Value, nullptr },
                { type<mud::Dim2<bool>>(), member_address(&mud::Dim2<bool>::y), type<bool>(), "y", var(bool()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Dim2<mud::Align>>(), &namspc({ "mud" }), "Dim2<mud::Align>", sizeof(mud::Dim2<mud::Align>), TypeClass::Struct };
        static Class cls = { type<mud::Dim2<mud::Align>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Dim2<mud::Align>>(), [](Ref ref, array<Var> args) { new(&val<mud::Dim2<mud::Align>>(ref)) mud::Dim2<mud::Align>( val<mud::Align>(args[0]), val<mud::Align>(args[1]) ); }, { { "a", var(mud::Align()) }, { "b", var(mud::Align()) } } },
                { type<mud::Dim2<mud::Align>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Dim2<mud::Align>>(ref)) mud::Dim2<mud::Align>(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Dim2<mud::Align>>(), [](Ref ref, Ref other) { new(&val<mud::Dim2<mud::Align>>(ref)) mud::Dim2<mud::Align>(val<mud::Dim2<mud::Align>>(other)); } }
            },
            // members
            {
                { type<mud::Dim2<mud::Align>>(), member_address(&mud::Dim2<mud::Align>::x), type<mud::Align>(), "x", var(mud::Align()), Member::Value, nullptr },
                { type<mud::Dim2<mud::Align>>(), member_address(&mud::Dim2<mud::Align>::y), type<mud::Align>(), "y", var(mud::Align()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Dim2<mud::AutoLayout>>(), &namspc({ "mud" }), "Dim2<mud::AutoLayout>", sizeof(mud::Dim2<mud::AutoLayout>), TypeClass::Struct };
        static Class cls = { type<mud::Dim2<mud::AutoLayout>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Dim2<mud::AutoLayout>>(), [](Ref ref, array<Var> args) { new(&val<mud::Dim2<mud::AutoLayout>>(ref)) mud::Dim2<mud::AutoLayout>( val<mud::AutoLayout>(args[0]), val<mud::AutoLayout>(args[1]) ); }, { { "a", var(mud::AutoLayout()) }, { "b", var(mud::AutoLayout()) } } },
                { type<mud::Dim2<mud::AutoLayout>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Dim2<mud::AutoLayout>>(ref)) mud::Dim2<mud::AutoLayout>(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Dim2<mud::AutoLayout>>(), [](Ref ref, Ref other) { new(&val<mud::Dim2<mud::AutoLayout>>(ref)) mud::Dim2<mud::AutoLayout>(val<mud::Dim2<mud::AutoLayout>>(other)); } }
            },
            // members
            {
                { type<mud::Dim2<mud::AutoLayout>>(), member_address(&mud::Dim2<mud::AutoLayout>::x), type<mud::AutoLayout>(), "x", var(mud::AutoLayout()), Member::Value, nullptr },
                { type<mud::Dim2<mud::AutoLayout>>(), member_address(&mud::Dim2<mud::AutoLayout>::y), type<mud::AutoLayout>(), "y", var(mud::AutoLayout()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Dim2<mud::Pivot>>(), &namspc({ "mud" }), "Dim2<mud::Pivot>", sizeof(mud::Dim2<mud::Pivot>), TypeClass::Struct };
        static Class cls = { type<mud::Dim2<mud::Pivot>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Dim2<mud::Pivot>>(), [](Ref ref, array<Var> args) { new(&val<mud::Dim2<mud::Pivot>>(ref)) mud::Dim2<mud::Pivot>( val<mud::Pivot>(args[0]), val<mud::Pivot>(args[1]) ); }, { { "a", var(mud::Pivot()) }, { "b", var(mud::Pivot()) } } },
                { type<mud::Dim2<mud::Pivot>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Dim2<mud::Pivot>>(ref)) mud::Dim2<mud::Pivot>(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Dim2<mud::Pivot>>(), [](Ref ref, Ref other) { new(&val<mud::Dim2<mud::Pivot>>(ref)) mud::Dim2<mud::Pivot>(val<mud::Dim2<mud::Pivot>>(other)); } }
            },
            // members
            {
                { type<mud::Dim2<mud::Pivot>>(), member_address(&mud::Dim2<mud::Pivot>::x), type<mud::Pivot>(), "x", var(mud::Pivot()), Member::Value, nullptr },
                { type<mud::Dim2<mud::Pivot>>(), member_address(&mud::Dim2<mud::Pivot>::y), type<mud::Pivot>(), "y", var(mud::Pivot()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Dim2<mud::Sizing>>(), &namspc({ "mud" }), "Dim2<mud::Sizing>", sizeof(mud::Dim2<mud::Sizing>), TypeClass::Struct };
        static Class cls = { type<mud::Dim2<mud::Sizing>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Dim2<mud::Sizing>>(), [](Ref ref, array<Var> args) { new(&val<mud::Dim2<mud::Sizing>>(ref)) mud::Dim2<mud::Sizing>( val<mud::Sizing>(args[0]), val<mud::Sizing>(args[1]) ); }, { { "a", var(mud::Sizing()) }, { "b", var(mud::Sizing()) } } },
                { type<mud::Dim2<mud::Sizing>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Dim2<mud::Sizing>>(ref)) mud::Dim2<mud::Sizing>(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Dim2<mud::Sizing>>(), [](Ref ref, Ref other) { new(&val<mud::Dim2<mud::Sizing>>(ref)) mud::Dim2<mud::Sizing>(val<mud::Dim2<mud::Sizing>>(other)); } }
            },
            // members
            {
                { type<mud::Dim2<mud::Sizing>>(), member_address(&mud::Dim2<mud::Sizing>::x), type<mud::Sizing>(), "x", var(mud::Sizing()), Member::Value, nullptr },
                { type<mud::Dim2<mud::Sizing>>(), member_address(&mud::Dim2<mud::Sizing>::y), type<mud::Sizing>(), "y", var(mud::Sizing()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Dim2<size_t>>(), &namspc({ "mud" }), "Dim2<size_t>", sizeof(mud::Dim2<size_t>), TypeClass::Struct };
        static Class cls = { type<mud::Dim2<size_t>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Dim2<size_t>>(), [](Ref ref, array<Var> args) { new(&val<mud::Dim2<size_t>>(ref)) mud::Dim2<size_t>( val<size_t>(args[0]), val<size_t>(args[1]) ); }, { { "a", var(size_t()) }, { "b", var(size_t()) } } },
                { type<mud::Dim2<size_t>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Dim2<size_t>>(ref)) mud::Dim2<size_t>(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Dim2<size_t>>(), [](Ref ref, Ref other) { new(&val<mud::Dim2<size_t>>(ref)) mud::Dim2<size_t>(val<mud::Dim2<size_t>>(other)); } }
            },
            // members
            {
                { type<mud::Dim2<size_t>>(), member_address(&mud::Dim2<size_t>::x), type<size_t>(), "x", var(size_t()), Member::Value, nullptr },
                { type<mud::Dim2<size_t>>(), member_address(&mud::Dim2<size_t>::y), type<size_t>(), "y", var(size_t()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Dock>(), &namspc({ "mud" }), "Dock", sizeof(mud::Dock), TypeClass::Struct };
        static Class cls = { type<mud::Dock>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Dock>(), [](Ref ref, Ref other) { new(&val<mud::Dock>(ref)) mud::Dock(val<mud::Dock>(other)); } }
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
        static Meta meta = { type<mud::Docksystem>(), &namspc({ "mud" }), "Docksystem", sizeof(mud::Docksystem), TypeClass::Object };
        static Class cls = { type<mud::Docksystem>(),
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
        static Meta meta = { type<mud::Gradient>(), &namspc({ "mud" }), "Gradient", sizeof(mud::Gradient), TypeClass::Struct };
        static Class cls = { type<mud::Gradient>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Gradient>(), [](Ref ref, Ref other) { new(&val<mud::Gradient>(ref)) mud::Gradient(val<mud::Gradient>(other)); } }
            },
            // members
            {
                { type<mud::Gradient>(), member_address(&mud::Gradient::m_start), type<mud::Colour>(), "start", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Gradient>(), member_address(&mud::Gradient::m_end), type<mud::Colour>(), "end", var(mud::Colour()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::GridSolver>(), &namspc({ "mud" }), "GridSolver", sizeof(mud::GridSolver), TypeClass::Object };
        static Class cls = { type<mud::GridSolver>(),
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
        static Meta meta = { type<mud::ImageSkin>(), &namspc({ "mud" }), "ImageSkin", sizeof(mud::ImageSkin), TypeClass::Struct };
        static Class cls = { type<mud::ImageSkin>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ImageSkin>(), [](Ref ref, array<Var> args) { new(&val<mud::ImageSkin>(ref)) mud::ImageSkin( val<mud::Image>(args[0]), val<int>(args[1]), val<int>(args[2]), val<int>(args[3]), val<int>(args[4]), val<int>(args[5]), val<mud::Dim>(args[6]) ); }, { { "image", var(mud::Image()) }, { "left", var(int()) }, { "top", var(int()) }, { "right", var(int()) }, { "bottom", var(int()) }, { "margin", var(int(0)), Param::Default }, { "stretch", var(mud::Dim()), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::ImageSkin>(), [](Ref ref, Ref other) { new(&val<mud::ImageSkin>(ref)) mud::ImageSkin(val<mud::ImageSkin>(other)); } }
            },
            // members
            {
                { type<mud::ImageSkin>(), member_address(&mud::ImageSkin::d_image), type<mud::Image>(), "d_image", Ref(type<mud::Image>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::ImageSkin>(), member_address(&mud::ImageSkin::d_left), type<int>(), "d_left", var(int(0)), Member::Value, nullptr },
                { type<mud::ImageSkin>(), member_address(&mud::ImageSkin::d_top), type<int>(), "d_top", var(int(0)), Member::Value, nullptr },
                { type<mud::ImageSkin>(), member_address(&mud::ImageSkin::d_right), type<int>(), "d_right", var(int(0)), Member::Value, nullptr },
                { type<mud::ImageSkin>(), member_address(&mud::ImageSkin::d_bottom), type<int>(), "d_bottom", var(int(0)), Member::Value, nullptr },
                { type<mud::ImageSkin>(), member_address(&mud::ImageSkin::m_margin), type<int>(), "margin", var(int(0)), Member::Value, nullptr },
                { type<mud::ImageSkin>(), member_address(&mud::ImageSkin::d_stretch), type<mud::Dim>(), "d_stretch", var(mud::Dim()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::InkStyle>(), &namspc({ "mud" }), "InkStyle", sizeof(mud::InkStyle), TypeClass::Struct };
        static Class cls = { type<mud::InkStyle>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::InkStyle>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::InkStyle>(ref)) mud::InkStyle(  ); }, {} },
                { type<mud::InkStyle>(), [](Ref ref, array<Var> args) { new(&val<mud::InkStyle>(ref)) mud::InkStyle( val<cstring>(args[0]) ); }, { { "name", var(cstring()) } } }
            },
            // copy constructor
            {
                { type<mud::InkStyle>(), [](Ref ref, Ref other) { new(&val<mud::InkStyle>(ref)) mud::InkStyle(val<mud::InkStyle>(other)); } }
            },
            // members
            {
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_name), type<std::string>(), "name", var(std::string()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_empty), type<bool>(), "empty", var(bool(true)), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_background_colour), type<mud::Colour>(), "background_colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_border_colour), type<mud::Colour>(), "border_colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_image_colour), type<mud::Colour>(), "image_colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_text_colour), type<mud::Colour>(), "text_colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_text_font), type<std::string>(), "text_font", var(std::string()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_text_size), type<float>(), "text_size", var(float(14.f)), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_text_break), type<bool>(), "text_break", var(bool(false)), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_text_wrap), type<bool>(), "text_wrap", var(bool(false)), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_border_width), type<mud::vec4>(), "border_width", var(mud::vec4()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_corner_radius), type<mud::vec4>(), "corner_radius", var(mud::vec4()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_weak_corners), type<bool>(), "weak_corners", var(bool(false)), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_padding), type<mud::vec4>(), "padding", var(mud::vec4()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_margin), type<mud::vec4>(), "margin", var(mud::vec4()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_align), type<mud::Dim2<mud::Align>>(), "align", var(mud::Dim2<mud::Align>()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_linear_gradient), type<mud::vec2>(), "linear_gradient", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_linear_gradient_dim), type<mud::Dim>(), "linear_gradient_dim", var(mud::Dim()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_stretch), type<mud::Dim2<bool>>(), "stretch", var(mud::Dim2<bool>()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_image), type<mud::Image>(), "image", Ref(type<mud::Image>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_overlay), type<mud::Image>(), "overlay", Ref(type<mud::Image>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_tile), type<mud::Image>(), "tile", Ref(type<mud::Image>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_image_skin), type<mud::ImageSkin>(), "image_skin", var(mud::ImageSkin()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_shadow), type<mud::Shadow>(), "shadow", var(mud::Shadow()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_shadow_colour), type<mud::Colour>(), "shadow_colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::InkStyle>(), member_address(&mud::InkStyle::m_hover_cursor), type<mud::Style>(), "hover_cursor", Ref(type<mud::Style>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
        static Meta meta = { type<mud::Layer>(), &namspc({ "mud" }), "Layer", sizeof(mud::Layer), TypeClass::Object };
        static Class cls = { type<mud::Layer>(),
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
        static Meta meta = { type<mud::Layout>(), &namspc({ "mud" }), "Layout", sizeof(mud::Layout), TypeClass::Struct };
        static Class cls = { type<mud::Layout>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Layout>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Layout>(ref)) mud::Layout(  ); }, {} },
                { type<mud::Layout>(), [](Ref ref, array<Var> args) { new(&val<mud::Layout>(ref)) mud::Layout( val<cstring>(args[0]) ); }, { { "name", var(cstring()) } } }
            },
            // copy constructor
            {
                { type<mud::Layout>(), [](Ref ref, Ref other) { new(&val<mud::Layout>(ref)) mud::Layout(val<mud::Layout>(other)); } }
            },
            // members
            {
                { type<mud::Layout>(), member_address(&mud::Layout::m_name), type<std::string>(), "name", var(std::string()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_solver), type<mud::LayoutSolver>(), "solver", var(mud::LayoutSolver()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_layout), type<mud::Dim2<mud::AutoLayout>>(), "layout", var(mud::Dim2<mud::AutoLayout>()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_flow), type<mud::Flow>(), "flow", var(mud::Flow()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_space), type<mud::Space>(), "space", var(mud::Space()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_clipping), type<mud::Clipping>(), "clipping", var(mud::Clipping()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_opacity), type<mud::Opacity>(), "opacity", var(mud::Opacity()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_align), type<mud::Dim2<mud::Align>>(), "align", var(mud::Dim2<mud::Align>()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_span), type<mud::vec2>(), "span", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_size), type<mud::vec2>(), "size", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_padding), type<mud::vec4>(), "padding", var(mud::vec4()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_margin), type<mud::vec2>(), "margin", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_spacing), type<mud::vec2>(), "spacing", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_pivot), type<mud::Dim2<mud::Pivot>>(), "pivot", var(mud::Dim2<mud::Pivot>()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_zorder), type<int>(), "zorder", var(int(0)), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_no_grid), type<bool>(), "no_grid", var(bool(false)), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_grid_division), type<std::vector<mud::Space>>(), "grid_division", var(std::vector<mud::Space>()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_table_division), type<std::vector<float>>(), "table_division", var(std::vector<float>()), Member::Value, nullptr },
                { type<mud::Layout>(), member_address(&mud::Layout::m_updated), type<size_t>(), "updated", var(size_t()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::NodeConnection>(), &namspc({ "mud" }), "NodeConnection", sizeof(mud::NodeConnection), TypeClass::Struct };
        static Class cls = { type<mud::NodeConnection>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::NodeConnection>(), [](Ref ref, Ref other) { new(&val<mud::NodeConnection>(ref)) mud::NodeConnection(val<mud::NodeConnection>(other)); } }
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
        static Meta meta = { type<mud::Paint>(), &namspc({ "mud" }), "Paint", sizeof(mud::Paint), TypeClass::Struct };
        static Class cls = { type<mud::Paint>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Paint>(), [](Ref ref, Ref other) { new(&val<mud::Paint>(ref)) mud::Paint(val<mud::Paint>(other)); } }
            },
            // members
            {
                { type<mud::Paint>(), member_address(&mud::Paint::m_fill_colour), type<mud::Colour>(), "fill_colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Paint>(), member_address(&mud::Paint::m_stroke_colour), type<mud::Colour>(), "stroke_colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Paint>(), member_address(&mud::Paint::m_stroke_width), type<float>(), "stroke_width", var(float()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Shadow>(), &namspc({ "mud" }), "Shadow", sizeof(mud::Shadow), TypeClass::Struct };
        static Class cls = { type<mud::Shadow>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Shadow>(), [](Ref ref, array<Var> args) { new(&val<mud::Shadow>(ref)) mud::Shadow( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]), val<mud::Colour>(args[4]) ); }, { { "xpos", var(float()) }, { "ypos", var(float()) }, { "blur", var(float()) }, { "spread", var(float()) }, { "colour", var(mud::Colour()), Param::Default } } },
                { type<mud::Shadow>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Shadow>(ref)) mud::Shadow(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Shadow>(), [](Ref ref, Ref other) { new(&val<mud::Shadow>(ref)) mud::Shadow(val<mud::Shadow>(other)); } }
            },
            // members
            {
                { type<mud::Shadow>(), member_address(&mud::Shadow::d_xpos), type<float>(), "d_xpos", var(float()), Member::Value, nullptr },
                { type<mud::Shadow>(), member_address(&mud::Shadow::d_ypos), type<float>(), "d_ypos", var(float()), Member::Value, nullptr },
                { type<mud::Shadow>(), member_address(&mud::Shadow::d_blur), type<float>(), "d_blur", var(float()), Member::Value, nullptr },
                { type<mud::Shadow>(), member_address(&mud::Shadow::d_spread), type<float>(), "d_spread", var(float()), Member::Value, nullptr },
                { type<mud::Shadow>(), member_address(&mud::Shadow::d_colour), type<mud::Colour>(), "d_colour", var(mud::Colour()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Space>(), &namspc({ "mud" }), "Space", sizeof(mud::Space), TypeClass::Struct };
        static Class cls = { type<mud::Space>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Space>(), [](Ref ref, Ref other) { new(&val<mud::Space>(ref)) mud::Space(val<mud::Space>(other)); } }
            },
            // members
            {
                { type<mud::Space>(), member_address(&mud::Space::direction), type<mud::FlowAxis>(), "direction", var(mud::FlowAxis()), Member::Value, nullptr },
                { type<mud::Space>(), member_address(&mud::Space::sizingLength), type<mud::Sizing>(), "sizingLength", var(mud::Sizing()), Member::Value, nullptr },
                { type<mud::Space>(), member_address(&mud::Space::sizingDepth), type<mud::Sizing>(), "sizingDepth", var(mud::Sizing()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::Style>(), &namspc({ "mud" }), "Style", sizeof(mud::Style), TypeClass::Object };
        static Class cls = { type<mud::Style>(),
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
                { type<mud::Style>(), member_address(&mud::Style::m_base), type<mud::Style>(), "base", Ref(type<mud::Style>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Style>(), member_address(&mud::Style::name), type<cstring>(), "name", var(cstring()), Member::Value, [](Ref object) { return Ref(val<mud::Style>(object).name()); } },
                { type<mud::Style>(), member_address(&mud::Style::layout), type<mud::Layout>(), "layout", var(mud::Layout()), Member::Flags(Member::Value|Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Style>(object).layout()); } },
                { type<mud::Style>(), member_address(&mud::Style::skin), type<mud::InkStyle>(), "skin", var(mud::InkStyle()), Member::Flags(Member::Value|Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Style>(object).skin()); } }
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
    
    
        
    // mud::Styler
    {
        static Meta meta = { type<mud::Styler>(), &namspc({ "mud" }), "Styler", sizeof(mud::Styler), TypeClass::Object };
        static Class cls = { type<mud::Styler>(),
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
        
        
        
        
        meta_class<mud::Styler>();
    }
    
    
    
    
        
    // mud::TableSolver
    {
        static Meta meta = { type<mud::TableSolver>(), &namspc({ "mud" }), "TableSolver", sizeof(mud::TableSolver), TypeClass::Object };
        static Class cls = { type<mud::TableSolver>(),
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
        static Meta meta = { type<mud::Text>(), &namspc({ "mud" }), "Text", sizeof(mud::Text), TypeClass::Object };
        static Class cls = { type<mud::Text>(),
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
        static Meta meta = { type<mud::TextCursor>(), &namspc({ "mud" }), "TextCursor", sizeof(mud::TextCursor), TypeClass::Struct };
        static Class cls = { type<mud::TextCursor>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::TextCursor>(), [](Ref ref, Ref other) { new(&val<mud::TextCursor>(ref)) mud::TextCursor(val<mud::TextCursor>(other)); } }
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
    
    
    
        
    // mud::TextPaint
    {
        static Meta meta = { type<mud::TextPaint>(), &namspc({ "mud" }), "TextPaint", sizeof(mud::TextPaint), TypeClass::Struct };
        static Class cls = { type<mud::TextPaint>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::TextPaint>(), [](Ref ref, Ref other) { new(&val<mud::TextPaint>(ref)) mud::TextPaint(val<mud::TextPaint>(other)); } }
            },
            // members
            {
                { type<mud::TextPaint>(), member_address(&mud::TextPaint::m_font), type<cstring>(), "font", var(cstring()), Member::Value, nullptr },
                { type<mud::TextPaint>(), member_address(&mud::TextPaint::m_colour), type<mud::Colour>(), "colour", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::TextPaint>(), member_address(&mud::TextPaint::m_size), type<float>(), "size", var(float()), Member::Value, nullptr },
                { type<mud::TextPaint>(), member_address(&mud::TextPaint::m_align), type<mud::Dim2<mud::Align>>(), "align", var(mud::Dim2<mud::Align>()), Member::Value, nullptr },
                { type<mud::TextPaint>(), member_address(&mud::TextPaint::m_text_break), type<bool>(), "text_break", var(bool()), Member::Value, nullptr },
                { type<mud::TextPaint>(), member_address(&mud::TextPaint::m_text_wrap), type<bool>(), "text_wrap", var(bool()), Member::Value, nullptr }
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
        static Meta meta = { type<mud::TextSelection>(), &namspc({ "mud" }), "TextSelection", sizeof(mud::TextSelection), TypeClass::Struct };
        static Class cls = { type<mud::TextSelection>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::TextSelection>(), [](Ref ref, Ref other) { new(&val<mud::TextSelection>(ref)) mud::TextSelection(val<mud::TextSelection>(other)); } }
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
        static Meta meta = { type<mud::UiRect>(), &namspc({ "mud" }), "UiRect", sizeof(mud::UiRect), TypeClass::Struct };
        static Class cls = { type<mud::UiRect>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::UiRect>(), [](Ref ref, Ref other) { new(&val<mud::UiRect>(ref)) mud::UiRect(val<mud::UiRect>(other)); } }
            },
            // members
            {
                { type<mud::UiRect>(), member_address(&mud::UiRect::m_position), type<mud::vec2>(), "position", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::UiRect>(), member_address(&mud::UiRect::m_size), type<mud::vec2>(), "size", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::UiRect>(), member_address(&mud::UiRect::m_content), type<mud::vec2>(), "content", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::UiRect>(), member_address(&mud::UiRect::m_span), type<mud::vec2>(), "span", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::UiRect>(), member_address(&mud::UiRect::m_scale), type<float>(), "scale", var(float(1.f)), Member::Value, nullptr }
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
        static Meta meta = { type<mud::UiWindow>(), &namspc({ "mud" }), "UiWindow", sizeof(mud::UiWindow), TypeClass::Object };
        static Class cls = { type<mud::UiWindow>(),
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
        static Meta meta = { type<mud::User>(), &namspc({ "mud" }), "User", sizeof(mud::User), TypeClass::Object };
        static Class cls = { type<mud::User>(),
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
    
    
    
    
        
    // mud::Frame
    {
        static Meta meta = { type<mud::Frame>(), &namspc({ "mud" }), "Frame", sizeof(mud::Frame), TypeClass::Object };
        static Class cls = { type<mud::Frame>(),
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
        static Meta meta = { type<mud::FrameSolver>(), &namspc({ "mud" }), "FrameSolver", sizeof(mud::FrameSolver), TypeClass::Object };
        static Class cls = { type<mud::FrameSolver>(),
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
    
    
        
    // mud::Canvas
    {
        static Meta meta = { type<mud::Canvas>(), &namspc({ "mud" }), "Canvas", sizeof(mud::Canvas), TypeClass::Object };
        static Class cls = { type<mud::Canvas>(),
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
        static Meta meta = { type<mud::Dockable>(), &namspc({ "mud" }), "Dockable", sizeof(mud::Dockable), TypeClass::Object };
        static Class cls = { type<mud::Dockable>(),
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
        static Meta meta = { type<mud::Docker>(), &namspc({ "mud" }), "Docker", sizeof(mud::Docker), TypeClass::Object };
        static Class cls = { type<mud::Docker>(),
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
    
    
        
    // mud::Expandbox
    {
        static Meta meta = { type<mud::Expandbox>(), &namspc({ "mud" }), "Expandbox", sizeof(mud::Expandbox), TypeClass::Object };
        static Class cls = { type<mud::Expandbox>(),
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
        static Meta meta = { type<mud::Node>(), &namspc({ "mud" }), "Node", sizeof(mud::Node), TypeClass::Object };
        static Class cls = { type<mud::Node>(),
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
        static Meta meta = { type<mud::NodePlug>(), &namspc({ "mud" }), "NodePlug", sizeof(mud::NodePlug), TypeClass::Object };
        static Class cls = { type<mud::NodePlug>(),
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
    
    
        
    // mud::ScrollSheet
    {
        static Meta meta = { type<mud::ScrollSheet>(), &namspc({ "mud" }), "ScrollSheet", sizeof(mud::ScrollSheet), TypeClass::Object };
        static Class cls = { type<mud::ScrollSheet>(),
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
        static Meta meta = { type<mud::ui::Sequence>(), &namspc({ "mud", "ui" }), "Sequence", sizeof(mud::ui::Sequence), TypeClass::Object };
        static Class cls = { type<mud::ui::Sequence>(),
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
        static Meta meta = { type<mud::Tabber>(), &namspc({ "mud" }), "Tabber", sizeof(mud::Tabber), TypeClass::Object };
        static Class cls = { type<mud::Tabber>(),
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
        static Meta meta = { type<mud::Table>(), &namspc({ "mud" }), "Table", sizeof(mud::Table), TypeClass::Object };
        static Class cls = { type<mud::Table>(),
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
        static Meta meta = { type<mud::TextEdit>(), &namspc({ "mud" }), "TextEdit", sizeof(mud::TextEdit), TypeClass::Object };
        static Class cls = { type<mud::TextEdit>(),
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
        static Meta meta = { type<mud::TreeNode>(), &namspc({ "mud" }), "TreeNode", sizeof(mud::TreeNode), TypeClass::Object };
        static Class cls = { type<mud::TreeNode>(),
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
        static Meta meta = { type<mud::Ui>(), &namspc({ "mud" }), "Ui", sizeof(mud::Ui), TypeClass::Object };
        static Class cls = { type<mud::Ui>(),
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
                { type<mud::Ui>(), "begin", member_address(&mud::Ui::begin), [](Ref object, array<Var> args, Var& result) { UNUSED(args);result = Ref(&val<mud::Ui>(object).begin()); }, {}, Ref(type<mud::Widget>()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Ui>();
    }
    
    
        
    // mud::RowSolver
    {
        static Meta meta = { type<mud::RowSolver>(), &namspc({ "mud" }), "RowSolver", sizeof(mud::RowSolver), TypeClass::Object };
        static Class cls = { type<mud::RowSolver>(),
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
    
    
    
        
    // mud::LineSolver
    {
        static Meta meta = { type<mud::LineSolver>(), &namspc({ "mud" }), "LineSolver", sizeof(mud::LineSolver), TypeClass::Object };
        static Class cls = { type<mud::LineSolver>(),
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
    
    
        
    // mud::Window
    {
        static Meta meta = { type<mud::Window>(), &namspc({ "mud" }), "Window", sizeof(mud::Window), TypeClass::Object };
        static Class cls = { type<mud::Window>(),
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
    
    
        
    // mud::Dockbar
    {
        static Meta meta = { type<mud::Dockbar>(), &namspc({ "mud" }), "Dockbar", sizeof(mud::Dockbar), TypeClass::Object };
        static Class cls = { type<mud::Dockbar>(),
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
        static Meta meta = { type<mud::Dockspace>(), &namspc({ "mud" }), "Dockspace", sizeof(mud::Dockspace), TypeClass::Object };
        static Class cls = { type<mud::Dockspace>(),
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
    
    
        
    // mud::Widget
    {
        static Meta meta = { type<mud::Widget>(), &namspc({ "mud" }), "Widget", sizeof(mud::Widget), TypeClass::Object };
        static Class cls = { type<mud::Widget>(),
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
                { type<mud::Widget>(), member_address(&mud::Widget::m_frame), type<mud::Frame>(), "frame", Ref(type<mud::Frame>()), Member::None, nullptr },
                { type<mud::Widget>(), member_address(&mud::Widget::m_state), type<mud::WidgetState>(), "state", var(mud::WidgetState()), Member::Value, nullptr },
                { type<mud::Widget>(), member_address(&mud::Widget::m_switch), type<uint32_t>(), "switch", var(uint32_t()), Member::Value, nullptr },
                { type<mud::Widget>(), member_address(&mud::Widget::m_index), type<size_t>(), "index", var(size_t()), Member::Value, nullptr },
                { type<mud::Widget>(), member_address(&mud::Widget::m_open), type<bool>(), "open", var(bool(false)), Member::Value, nullptr },
                { type<mud::Widget>(), member_address(&mud::Widget::m_body), type<mud::Widget>(), "body", Ref(type<mud::Widget>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
            },
            // methods
            {
                { type<mud::Widget>(), "ui_window", member_address(&mud::Widget::ui_window), [](Ref object, array<Var> args, Var& result) { UNUSED(args);result = Ref(&val<mud::Widget>(object).ui_window()); }, {}, Ref(type<mud::UiWindow>()) },
                { type<mud::Widget>(), "ui", member_address(&mud::Widget::ui), [](Ref object, array<Var> args, Var& result) { UNUSED(args);result = Ref(&val<mud::Widget>(object).ui()); }, {}, Ref(type<mud::Ui>()) },
                { type<mud::Widget>(), "parent_modal", member_address(&mud::Widget::parent_modal), [](Ref object, array<Var> args, Var& result) { UNUSED(args);result = Ref(&val<mud::Widget>(object).parent_modal()); }, {}, Ref(type<mud::Widget>()) },
                { type<mud::Widget>(), "toggle_state", member_address(&mud::Widget::toggle_state), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).toggle_state(val<mud::WidgetState>(args[0])); }, { { "state", var(mud::WidgetState()) } }, Var() },
                { type<mud::Widget>(), "disable_state", member_address(&mud::Widget::disable_state), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).disable_state(val<mud::WidgetState>(args[0])); }, { { "state", var(mud::WidgetState()) } }, Var() },
                { type<mud::Widget>(), "set_state", member_address(&mud::Widget::set_state), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).set_state(val<mud::WidgetState>(args[0]), val<bool>(args[1])); }, { { "state", var(mud::WidgetState()) }, { "enabled", var(bool()) } }, Var() },
                { type<mud::Widget>(), "enable_state", member_address(&mud::Widget::enable_state), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).enable_state(val<mud::WidgetState>(args[0])); }, { { "state", var(mud::WidgetState()) } }, Var() },
                { type<mud::Widget>(), "clear_focus", member_address(&mud::Widget::clear_focus), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Widget>(object).clear_focus(); }, {}, Var() },
                { type<mud::Widget>(), "take_focus", member_address(&mud::Widget::take_focus), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Widget>(object).take_focus(); }, {}, Var() },
                { type<mud::Widget>(), "yield_focus", member_address(&mud::Widget::yield_focus), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Widget>(object).yield_focus(); }, {}, Var() },
                { type<mud::Widget>(), "take_modal", member_address(&mud::Widget::take_modal), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Widget>(object).take_modal(val<uint32_t>(args[0])); }, { { "device_filter", var(uint32_t()) } }, Var() },
                { type<mud::Widget>(), "yield_modal", member_address(&mud::Widget::yield_modal), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Widget>(object).yield_modal(); }, {}, Var() },
                { type<mud::Widget>(), "key_event", member_address(&mud::Widget::key_event), [](Ref object, array<Var> args, Var& result) { val<mud::KeyEvent>(result) = val<mud::Widget>(object).key_event(val<mud::Key>(args[0]), val<mud::EventType>(args[1]), val<mud::InputMod>(args[2])); }, { { "code", var(mud::Key()) }, { "event_type", var(mud::EventType()) }, { "modifier", var(mud::InputMod()), Param::Default } }, var(mud::KeyEvent()) },
                { type<mud::Widget>(), "key_stroke", member_address(&mud::Widget::key_stroke), [](Ref object, array<Var> args, Var& result) { val<mud::KeyEvent>(result) = val<mud::Widget>(object).key_stroke(val<mud::Key>(args[0]), val<mud::InputMod>(args[1])); }, { { "code", var(mud::Key()) }, { "modifier", var(mud::InputMod()), Param::Default } }, var(mud::KeyEvent()) },
                { type<mud::Widget>(), "mouse_event", member_address(&mud::Widget::mouse_event), [](Ref object, array<Var> args, Var& result) { val<mud::MouseEvent>(result) = val<mud::Widget>(object).mouse_event(val<mud::DeviceType>(args[0]), val<mud::EventType>(args[1]), val<mud::InputMod>(args[2]), val<bool>(args[3])); }, { { "device", var(mud::DeviceType()) }, { "event_type", var(mud::EventType()) }, { "modifier", var(mud::InputMod()), Param::Default }, { "consume", var(bool(true)), Param::Default } }, var(mud::MouseEvent()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Widget>();
    }
    

    
        m.m_types.push_back(&type<mud::Align>());
        m.m_types.push_back(&type<mud::AutoLayout>());
        m.m_types.push_back(&type<mud::CanvasConnect>());
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
        m.m_types.push_back(&type<mud::Shadow>());
        m.m_types.push_back(&type<mud::Sizing>());
        m.m_types.push_back(&type<mud::Space>());
        m.m_types.push_back(&type<mud::SpacePreset>());
        m.m_types.push_back(&type<mud::Style>());
        m.m_types.push_back(&type<mud::Styler>());
        m.m_types.push_back(&type<mud::TableSolver>());
        m.m_types.push_back(&type<mud::Text>());
        m.m_types.push_back(&type<mud::TextCursor>());
        m.m_types.push_back(&type<mud::TextPaint>());
        m.m_types.push_back(&type<mud::TextSelection>());
        m.m_types.push_back(&type<mud::UiRect>());
        m.m_types.push_back(&type<mud::UiWindow>());
        m.m_types.push_back(&type<mud::User>());
        m.m_types.push_back(&type<mud::WidgetState>());
        m.m_types.push_back(&type<mud::WindowState>());
        m.m_types.push_back(&type<array<cstring>>());
        m.m_types.push_back(&type<array<float>>());
        m.m_types.push_back(&type<std::vector<mud::Space>>());
        m.m_types.push_back(&type<std::vector<std::string>>());
        m.m_types.push_back(&type<mud::Frame>());
        m.m_types.push_back(&type<mud::FrameSolver>());
        m.m_types.push_back(&type<mud::Canvas>());
        m.m_types.push_back(&type<mud::Dockable>());
        m.m_types.push_back(&type<mud::Docker>());
        m.m_types.push_back(&type<mud::Expandbox>());
        m.m_types.push_back(&type<mud::Node>());
        m.m_types.push_back(&type<mud::NodePlug>());
        m.m_types.push_back(&type<mud::ScrollSheet>());
        m.m_types.push_back(&type<mud::ui::Sequence>());
        m.m_types.push_back(&type<mud::Tabber>());
        m.m_types.push_back(&type<mud::Table>());
        m.m_types.push_back(&type<mud::TextEdit>());
        m.m_types.push_back(&type<mud::TreeNode>());
        m.m_types.push_back(&type<mud::Ui>());
        m.m_types.push_back(&type<mud::RowSolver>());
        m.m_types.push_back(&type<mud::LineSolver>());
        m.m_types.push_back(&type<mud::Window>());
        m.m_types.push_back(&type<mud::Dockbar>());
        m.m_types.push_back(&type<mud::Dockspace>());
        m.m_types.push_back(&type<mud::Widget>());
    
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::widget(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<bool>(args[2]), val<mud::Dim>(args[3]), val<mud::Dim2<size_t>>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "open", var(bool(false)), Param::Default }, { "length", var(mud::Dim()), Param::Default }, { "index", var(mud::Dim2<size_t>()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "widget", function_id<mud::Widget&(*)(mud::Widget&, mud::Style&, bool, mud::Dim, mud::Dim2<size_t>)>(&mud::ui::widget), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::item(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<cstring>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "content", var(cstring()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "item", function_id<mud::Widget&(*)(mud::Widget&, mud::Style&, cstring)>(&mud::ui::item), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::multi_item(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<array<cstring>>(args[2]), &val<mud::Style>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "elements", var(array<cstring>()) }, { "element_style", Ref(type<mud::Style>()), Param::Flags(Param::Nullable|Param::Default) } };
            static Function f = { &namspc({ "mud", "ui" }), "multi_item", function_id<mud::Widget&(*)(mud::Widget&, mud::Style&, array<cstring>, mud::Style*)>(&mud::ui::multi_item), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::multi_item(val<mud::Widget>(args[0]), val<array<cstring>>(args[1]), &val<mud::Style>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "elements", var(array<cstring>()) }, { "element_style", Ref(type<mud::Style>()), Param::Flags(Param::Nullable|Param::Default) } };
            static Function f = { &namspc({ "mud", "ui" }), "multi_item", function_id<mud::Widget&(*)(mud::Widget&, array<cstring>, mud::Style*)>(&mud::ui::multi_item), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::spanner(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<mud::Dim>(args[2]), val<float>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "dim", var(mud::Dim()) }, { "span", var(float()) } };
            static Function f = { &namspc({ "mud", "ui" }), "spanner", function_id<mud::Widget&(*)(mud::Widget&, mud::Style&, mud::Dim, float)>(&mud::ui::spanner), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::spacer(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "spacer", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::spacer), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::icon(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "icon", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "icon", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::icon), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::label(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "label", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::label), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::title(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "title", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::title), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::message(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "message", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::message), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::text(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "text", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::text), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::button(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "content", var(cstring()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "button", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::button), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::multi_button(val<mud::Widget>(args[0]), val<array<cstring>>(args[1]), &val<mud::Style>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "elements", var(array<cstring>()) }, { "element_style", Ref(type<mud::Style>()), Param::Flags(Param::Nullable|Param::Default) } };
            static Function f = { &namspc({ "mud", "ui" }), "multi_button", function_id<mud::Widget&(*)(mud::Widget&, array<cstring>, mud::Style*)>(&mud::ui::multi_button), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::toggle(val<mud::Widget>(args[0]), val<bool>(args[1]), val<cstring>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "on", var(bool()) }, { "content", var(cstring()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "toggle", function_id<mud::Widget&(*)(mud::Widget&, bool&, cstring)>(&mud::ui::toggle), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::multi_toggle(val<mud::Widget>(args[0]), val<bool>(args[1]), val<array<cstring>>(args[2]), &val<mud::Style>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "on", var(bool()) }, { "elements", var(array<cstring>()) }, { "element_style", Ref(type<mud::Style>()), Param::Flags(Param::Nullable|Param::Default) } };
            static Function f = { &namspc({ "mud", "ui" }), "multi_toggle", function_id<mud::Widget&(*)(mud::Widget&, bool&, array<cstring>, mud::Style*)>(&mud::ui::multi_toggle), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::modal_button(val<mud::Widget>(args[0]), val<mud::Widget>(args[1]), val<cstring>(args[2]), val<uint32_t>(args[3])); };
            std::vector<Param> params = { { "screen", Ref(type<mud::Widget>()) }, { "parent", Ref(type<mud::Widget>()) }, { "content", var(cstring()) }, { "mode", var(uint32_t()) } };
            static Function f = { &namspc({ "mud", "ui" }), "modal_button", function_id<bool(*)(mud::Widget&, mud::Widget&, cstring, uint32_t)>(&mud::ui::modal_button), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::modal_multi_button(val<mud::Widget>(args[0]), val<mud::Widget>(args[1]), val<array<cstring>>(args[2]), val<uint32_t>(args[3])); };
            std::vector<Param> params = { { "screen", Ref(type<mud::Widget>()) }, { "parent", Ref(type<mud::Widget>()) }, { "elements", var(array<cstring>()) }, { "mode", var(uint32_t()) } };
            static Function f = { &namspc({ "mud", "ui" }), "modal_multi_button", function_id<bool(*)(mud::Widget&, mud::Widget&, array<cstring>, uint32_t)>(&mud::ui::modal_multi_button), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::checkbox(val<mud::Widget>(args[0]), val<bool>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "on", var(bool()) } };
            static Function f = { &namspc({ "mud", "ui" }), "checkbox", function_id<mud::Widget&(*)(mud::Widget&, bool&)>(&mud::ui::checkbox), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::fill_bar(val<mud::Widget>(args[0]), val<float>(args[1]), val<mud::Dim>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "percentage", var(float()) }, { "dim", var(mud::Dim()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "fill_bar", function_id<mud::Widget&(*)(mud::Widget&, float, mud::Dim)>(&mud::ui::fill_bar), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::image256(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<mud::Image256>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "source", var(mud::Image256()) } };
            static Function f = { &namspc({ "mud", "ui" }), "image256", function_id<mud::Widget&(*)(mud::Widget&, cstring, const mud::Image256&)>(&mud::ui::image256), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::image256(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<mud::Image256>(args[2]), val<mud::vec2>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "source", var(mud::Image256()) }, { "size", var(mud::vec2()) } };
            static Function f = { &namspc({ "mud", "ui" }), "image256", function_id<mud::Widget&(*)(mud::Widget&, cstring, const mud::Image256&, const mud::vec2&)>(&mud::ui::image256), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::radio_choice(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<bool>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(cstring()) }, { "active", var(bool()) } };
            static Function f = { &namspc({ "mud", "ui" }), "radio_choice", function_id<mud::Widget&(*)(mud::Widget&, cstring, bool)>(&mud::ui::radio_choice), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::radio_switch(val<mud::Widget>(args[0]), val<array<cstring>>(args[1]), val<size_t>(args[2]), val<mud::Dim>(args[3])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "labels", var(array<cstring>()) }, { "value", var(size_t()) }, { "dim", var(mud::Dim()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "radio_switch", function_id<bool(*)(mud::Widget&, array<cstring>, size_t&, mud::Dim)>(&mud::ui::radio_switch), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::popdown(val<mud::Widget>(args[0]), val<array<cstring>>(args[1]), val<size_t>(args[2]), val<mud::vec2>(args[3]), val<mud::ui::PopupFlags>(args[4])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "choices", var(array<cstring>()) }, { "value", var(size_t()) }, { "position", var(mud::vec2()) }, { "flags", var(mud::ui::PopupFlags()) } };
            static Function f = { &namspc({ "mud", "ui" }), "popdown", function_id<bool(*)(mud::Widget&, array<cstring>, size_t&, mud::vec2, mud::ui::PopupFlags)>(&mud::ui::popdown), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dropdown(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<cstring>(args[2]), val<mud::ui::PopupFlags>(args[3]), &val<mud::Style>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "value", var(cstring()) }, { "flags", var(mud::ui::PopupFlags()) }, { "list_style", Ref(type<mud::Style>()), Param::Flags(Param::Nullable|Param::Default) } };
            static Function f = { &namspc({ "mud", "ui" }), "dropdown", function_id<mud::Widget&(*)(mud::Widget&, mud::Style&, cstring, mud::ui::PopupFlags, mud::Style*)>(&mud::ui::dropdown), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::dropdown_input(val<mud::Widget>(args[0]), val<array<cstring>>(args[1]), val<size_t>(args[2]), val<bool>(args[3])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "choices", var(array<cstring>()) }, { "value", var(size_t()) }, { "compact", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "dropdown_input", function_id<bool(*)(mud::Widget&, array<cstring>, size_t&, bool)>(&mud::ui::dropdown_input), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::typedown_input(val<mud::Widget>(args[0]), val<array<cstring>>(args[1]), val<size_t>(args[2])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "choices", var(array<cstring>()) }, { "value", var(size_t()) } };
            static Function f = { &namspc({ "mud", "ui" }), "typedown_input", function_id<bool(*)(mud::Widget&, array<cstring>, size_t&)>(&mud::ui::typedown_input), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::menu_choice(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "content", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "menu_choice", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::menu_choice), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::menu(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<bool>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "label", var(cstring()) }, { "submenu", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "menu", function_id<mud::Widget&(*)(mud::Widget&, cstring, bool)>(&mud::ui::menu), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::menubar(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "menubar", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::menubar), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::toolbutton(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "icon", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "toolbutton", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::toolbutton), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::tooldock(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "tooldock", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::tooldock), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::toolbar(val<mud::Widget>(args[0]), val<bool>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "wrap", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "toolbar", function_id<mud::Widget&(*)(mud::Widget&, bool)>(&mud::ui::toolbar), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::select_list(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "select_list", function_id<mud::ScrollSheet&(*)(mud::Widget&)>(&mud::ui::select_list), func, params, Ref(type<mud::ScrollSheet>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::columns(val<mud::Widget>(args[0]), val<array<float>>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "weights", var(array<float>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "columns", function_id<mud::Table&(*)(mud::Widget&, array<float>)>(&mud::ui::columns), func, params, Ref(type<mud::Table>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::table(val<mud::Widget>(args[0]), val<array<cstring>>(args[1]), val<array<float>>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "columns", var(array<cstring>()) }, { "weights", var(array<float>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "table", function_id<mud::Table&(*)(mud::Widget&, array<cstring>, array<float>)>(&mud::ui::table), func, params, Ref(type<mud::Table>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::table_row(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "table_row", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::table_row), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::table_separator(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "table_separator", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::table_separator), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::expandbox(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<bool>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "open", var(bool(true)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "expandbox", function_id<mud::Expandbox&(*)(mud::Widget&, cstring, bool)>(&mud::ui::expandbox), func, params, Ref(type<mud::Expandbox>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::tree_node(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<bool>(args[2]), val<bool>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "leaf", var(bool(false)), Param::Default }, { "open", var(bool(true)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "tree_node", function_id<mud::TreeNode&(*)(mud::Widget&, cstring, bool, bool)>(&mud::ui::tree_node), func, params, Ref(type<mud::TreeNode>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::tree(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "tree", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::tree), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::tab(val<mud::Tabber>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "tabber", Ref(type<mud::Tabber>()) }, { "name", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "tab", function_id<mud::Widget*(*)(mud::Tabber&, cstring)>(&mud::ui::tab), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::tabber(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "tabber", function_id<mud::Tabber&(*)(mud::Widget&)>(&mud::ui::tabber), func, params, Ref(type<mud::Tabber>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::row(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "row", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::row), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::header(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "header", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::header), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::div(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "div", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::div), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::stack(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "stack", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::stack), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::sheet(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "sheet", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::sheet), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::board(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "board", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::board), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::layout(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "layout", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::layout), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::screen(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "screen", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::screen), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::decal(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "decal", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::decal), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::overlay(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "overlay", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::overlay), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::title_header(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "title", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "title_header", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::title_header), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dummy(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()) } };
            static Function f = { &namspc({ "mud", "ui" }), "dummy", function_id<mud::Widget&(*)(mud::Widget&, const mud::vec2&)>(&mud::ui::dummy), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::popup(val<mud::Widget>(args[0]), val<mud::ui::PopupFlags>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "flags", var(mud::ui::PopupFlags()) } };
            static Function f = { &namspc({ "mud", "ui" }), "popup", function_id<mud::Widget&(*)(mud::Widget&, mud::ui::PopupFlags)>(&mud::ui::popup), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::popup(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]), val<mud::ui::PopupFlags>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()) }, { "flags", var(mud::ui::PopupFlags()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "popup", function_id<mud::Widget&(*)(mud::Widget&, const mud::vec2&, mud::ui::PopupFlags)>(&mud::ui::popup), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::popup_at(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]), val<mud::ui::PopupFlags>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "position", var(mud::vec2()) }, { "flags", var(mud::ui::PopupFlags()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "popup_at", function_id<mud::Widget&(*)(mud::Widget&, const mud::vec2&, mud::ui::PopupFlags)>(&mud::ui::popup_at), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::modal(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "modal", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::modal), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::modal(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()) } };
            static Function f = { &namspc({ "mud", "ui" }), "modal", function_id<mud::Widget&(*)(mud::Widget&, const mud::vec2&)>(&mud::ui::modal), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::auto_modal(val<mud::Widget>(args[0]), val<uint32_t>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "mode", var(uint32_t()) } };
            static Function f = { &namspc({ "mud", "ui" }), "auto_modal", function_id<mud::Widget&(*)(mud::Widget&, uint32_t)>(&mud::ui::auto_modal), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::auto_modal(val<mud::Widget>(args[0]), val<uint32_t>(args[1]), val<mud::vec2>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "mode", var(uint32_t()) }, { "size", var(mud::vec2()) } };
            static Function f = { &namspc({ "mud", "ui" }), "auto_modal", function_id<mud::Widget&(*)(mud::Widget&, uint32_t, const mud::vec2&)>(&mud::ui::auto_modal), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::context(val<mud::Widget>(args[0]), val<uint32_t>(args[1]), val<mud::ui::PopupFlags>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "mode", var(uint32_t()) }, { "flags", var(mud::ui::PopupFlags()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "context", function_id<mud::Widget*(*)(mud::Widget&, uint32_t, mud::ui::PopupFlags)>(&mud::ui::context), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::hoverbox(val<mud::Widget>(args[0]), val<float>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "delay", var(float(0.5f)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "hoverbox", function_id<mud::Widget*(*)(mud::Widget&, float)>(&mud::ui::hoverbox), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::tooltip(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]), val<cstring>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "position", var(mud::vec2()) }, { "content", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "tooltip", function_id<mud::Widget*(*)(mud::Widget&, const mud::vec2&, cstring)>(&mud::ui::tooltip), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::cursor(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]), val<mud::Widget>(args[2]), val<bool>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "position", var(mud::vec2()) }, { "hovered", Ref(type<mud::Widget>()) }, { "locked", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "cursor", function_id<mud::Widget&(*)(mud::Widget&, const mud::vec2&, mud::Widget&, bool)>(&mud::ui::cursor), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::rectangle(val<mud::Widget>(args[0]), val<mud::vec4>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "rect", var(mud::vec4()) } };
            static Function f = { &namspc({ "mud", "ui" }), "rectangle", function_id<mud::Widget&(*)(mud::Widget&, const mud::vec4&)>(&mud::ui::rectangle), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dockspace(val<mud::Widget>(args[0]), val<mud::Docksystem>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "docksystem", Ref(type<mud::Docksystem>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "dockspace", function_id<mud::Dockspace&(*)(mud::Widget&, mud::Docksystem&)>(&mud::ui::dockspace), func, params, Ref(type<mud::Dockspace>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dockbar(val<mud::Widget>(args[0]), val<mud::Docksystem>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "docksystem", Ref(type<mud::Docksystem>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "dockbar", function_id<mud::Dockbar&(*)(mud::Widget&, mud::Docksystem&)>(&mud::ui::dockbar), func, params, Ref(type<mud::Dockbar>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(mud::ui::dockitem(val<mud::Widget>(args[0]), val<mud::Docksystem>(args[1]), val<mud::Dock>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "docksystem", Ref(type<mud::Docksystem>()) }, { "dock", var(mud::Dock()) } };
            static Function f = { &namspc({ "mud", "ui" }), "dockitem", function_id<mud::Widget*(*)(mud::Widget&, mud::Docksystem&, mud::Dock&)>(&mud::ui::dockitem), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::text_box(val<mud::Widget>(args[0]), val<mud::Style>(args[1]), val<std::string>(args[2]), val<bool>(args[3]), val<size_t>(args[4]), val<std::string>(args[5]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "style", Ref(type<mud::Style>()) }, { "text", var(std::string()) }, { "editor", var(bool(false)), Param::Default }, { "lines", var(size_t()), Param::Default }, { "allowed_chars", var(std::string()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "text_box", function_id<mud::TextEdit&(*)(mud::Widget&, mud::Style&, std::string&, bool, size_t, const std::string&)>(&mud::ui::text_box), func, params, Ref(type<mud::TextEdit>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::type_in(val<mud::Widget>(args[0]), val<std::string>(args[1]), val<size_t>(args[2]), val<std::string>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "text", var(std::string()) }, { "lines", var(size_t()), Param::Default }, { "allowed_chars", var(std::string()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "type_in", function_id<mud::TextEdit&(*)(mud::Widget&, std::string&, size_t, const std::string&)>(&mud::ui::type_in), func, params, Ref(type<mud::TextEdit>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::text_edit(val<mud::Widget>(args[0]), val<std::string>(args[1]), val<size_t>(args[2]), &val<std::vector<std::string>>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "text", var(std::string()) }, { "lines", var(size_t()), Param::Default }, { "vocabulary", Ref(type<std::vector<std::string>>()), Param::Flags(Param::Nullable|Param::Default) } };
            static Function f = { &namspc({ "mud", "ui" }), "text_edit", function_id<mud::TextEdit&(*)(mud::Widget&, std::string&, size_t, std::vector<std::string>*)>(&mud::ui::text_edit), func, params, Ref(type<mud::TextEdit>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::code_edit(val<mud::Widget>(args[0]), val<std::string>(args[1]), val<size_t>(args[2]), &val<std::vector<std::string>>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "text", var(std::string()) }, { "lines", var(size_t()), Param::Default }, { "vocabulary", Ref(type<std::vector<std::string>>()), Param::Flags(Param::Nullable|Param::Default) } };
            static Function f = { &namspc({ "mud", "ui" }), "code_edit", function_id<mud::TextEdit&(*)(mud::Widget&, std::string&, size_t, std::vector<std::string>*)>(&mud::ui::code_edit), func, params, Ref(type<mud::TextEdit>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::drag_float(val<mud::Widget>(args[0]), val<float>(args[1]), val<float>(args[2])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(float()) }, { "step", var(float(0.1f)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "drag_float", function_id<bool(*)(mud::Widget&, float&, float)>(&mud::ui::drag_float), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::vec2_edit(val<mud::Widget>(args[0]), val<mud::vec2>(args[1])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "vec", var(mud::vec2()) } };
            static Function f = { &namspc({ "mud", "ui" }), "vec2_edit", function_id<bool(*)(mud::Widget&, mud::vec2&)>(&mud::ui::vec2_edit), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::vec3_edit(val<mud::Widget>(args[0]), val<mud::vec3>(args[1])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "vec", var(mud::vec3()) } };
            static Function f = { &namspc({ "mud", "ui" }), "vec3_edit", function_id<bool(*)(mud::Widget&, mud::vec3&)>(&mud::ui::vec3_edit), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::quat_edit(val<mud::Widget>(args[0]), val<mud::quat>(args[1])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "quat", var(mud::quat()) } };
            static Function f = { &namspc({ "mud", "ui" }), "quat_edit", function_id<bool(*)(mud::Widget&, mud::quat&)>(&mud::ui::quat_edit), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_edit_hsl(val<mud::Widget>(args[0]), val<mud::Colour>(args[1]), val<mud::Colour>(args[2])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "colour", var(mud::Colour()) }, { "value", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud", "ui" }), "color_edit_hsl", function_id<bool(*)(mud::Widget&, const mud::Colour&, mud::Colour&)>(&mud::ui::color_edit_hsl), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::color_display(val<mud::Widget>(args[0]), val<mud::Colour>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud", "ui" }), "color_display", function_id<mud::Widget&(*)(mud::Widget&, const mud::Colour&)>(&mud::ui::color_display), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_edit(val<mud::Widget>(args[0]), val<mud::Colour>(args[1])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud", "ui" }), "color_edit", function_id<bool(*)(mud::Widget&, mud::Colour&)>(&mud::ui::color_edit), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_edit_simple(val<mud::Widget>(args[0]), val<mud::Colour>(args[1])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud", "ui" }), "color_edit_simple", function_id<bool(*)(mud::Widget&, mud::Colour&)>(&mud::ui::color_edit_simple), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_toggle_edit(val<mud::Widget>(args[0]), val<mud::Colour>(args[1])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "value", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud", "ui" }), "color_toggle_edit", function_id<bool(*)(mud::Widget&, mud::Colour&)>(&mud::ui::color_toggle_edit), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::curve_graph(val<mud::Widget>(args[0]), val<array<float>>(args[1]), val<array<float>>(args[2])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "values", var(array<float>()) }, { "points", var(array<float>()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "curve_graph", function_id<bool(*)(mud::Widget&, array<float>, array<float>)>(&mud::ui::curve_graph), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::curve_edit(val<mud::Widget>(args[0]), val<array<float>>(args[1]), val<array<float>>(args[2])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "values", var(array<float>()) }, { "points", var(array<float>()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "curve_edit", function_id<bool(*)(mud::Widget&, array<float>, array<float>)>(&mud::ui::curve_edit), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::flag_field(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<uint32_t>(args[2]), val<uint8_t>(args[3]), val<bool>(args[4])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "value", var(uint32_t()) }, { "shift", var(uint8_t()) }, { "reverse", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "flag_field", function_id<bool(*)(mud::Widget&, cstring, uint32_t&, uint8_t, bool)>(&mud::ui::flag_field), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::radio_field(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<array<cstring>>(args[2]), val<size_t>(args[3]), val<bool>(args[4])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "choices", var(array<cstring>()) }, { "value", var(size_t()) }, { "reverse", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "radio_field", function_id<bool(*)(mud::Widget&, cstring, array<cstring>, size_t&, bool)>(&mud::ui::radio_field), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::dropdown_field(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<array<cstring>>(args[2]), val<size_t>(args[3]), val<bool>(args[4])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "choices", var(array<cstring>()) }, { "value", var(size_t()) }, { "reverse", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "dropdown_field", function_id<bool(*)(mud::Widget&, cstring, array<cstring>, size_t&, bool)>(&mud::ui::dropdown_field), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::typedown_field(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<array<cstring>>(args[2]), val<size_t>(args[3]), val<bool>(args[4])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "choices", var(array<cstring>()) }, { "value", var(size_t()) }, { "reverse", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "typedown_field", function_id<bool(*)(mud::Widget&, cstring, array<cstring>, size_t&, bool)>(&mud::ui::typedown_field), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::color_field(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<mud::Colour>(args[2]), val<bool>(args[3])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "value", var(mud::Colour()) }, { "reverse", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "color_field", function_id<bool(*)(mud::Widget&, cstring, mud::Colour&, bool)>(&mud::ui::color_field), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::ui::color_display_field(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<mud::Colour>(args[2]), val<bool>(args[3])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) }, { "value", var(mud::Colour()) }, { "reverse", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "color_display_field", function_id<void(*)(mud::Widget&, cstring, const mud::Colour&, bool)>(&mud::ui::color_display_field), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::node_input(val<mud::Node>(args[0]), val<cstring>(args[1]), val<cstring>(args[2]), val<mud::Colour>(args[3]), val<bool>(args[4]), val<bool>(args[5]))); };
            std::vector<Param> params = { { "node", Ref(type<mud::Node>()) }, { "name", var(cstring()) }, { "icon", var(cstring()), Param::Default }, { "colour", var(mud::Colour()), Param::Default }, { "active", var(bool(true)), Param::Default }, { "connected", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "node_input", function_id<mud::NodePlug&(*)(mud::Node&, cstring, cstring, const mud::Colour&, bool, bool)>(&mud::ui::node_input), func, params, Ref(type<mud::NodePlug>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::node_output(val<mud::Node>(args[0]), val<cstring>(args[1]), val<cstring>(args[2]), val<mud::Colour>(args[3]), val<bool>(args[4]), val<bool>(args[5]))); };
            std::vector<Param> params = { { "node", Ref(type<mud::Node>()) }, { "name", var(cstring()) }, { "icon", var(cstring()), Param::Default }, { "colour", var(mud::Colour()), Param::Default }, { "active", var(bool(true)), Param::Default }, { "connected", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "node_output", function_id<mud::NodePlug&(*)(mud::Node&, cstring, cstring, const mud::Colour&, bool, bool)>(&mud::ui::node_output), func, params, Ref(type<mud::NodePlug>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::node(val<mud::Canvas>(args[0]), val<cstring>(args[1]), val<mud::vec2>(args[2]), val<int>(args[3]), args[4])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Canvas>()) }, { "title", var(cstring()) }, { "position", var(mud::vec2()) }, { "order", var(int(0)), Param::Default }, { "identity", Ref(), Param::Flags(Param::Nullable|Param::Default) } };
            static Function f = { &namspc({ "mud", "ui" }), "node", function_id<mud::Node&(*)(mud::Canvas&, cstring, mud::vec2&, int, mud::Ref)>(&mud::ui::node), func, params, Ref(type<mud::Node>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::node_cable(val<mud::Canvas>(args[0]), val<mud::NodePlug>(args[1]), val<mud::NodePlug>(args[2]))); };
            std::vector<Param> params = { { "canvas", Ref(type<mud::Canvas>()) }, { "plug_out", Ref(type<mud::NodePlug>()) }, { "plug_in", Ref(type<mud::NodePlug>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "node_cable", function_id<mud::Widget&(*)(mud::Canvas&, mud::NodePlug&, mud::NodePlug&)>(&mud::ui::node_cable), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::canvas(val<mud::Widget>(args[0]), val<size_t>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "num_nodes", var(size_t()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "canvas", function_id<mud::Canvas&(*)(mud::Widget&, size_t)>(&mud::ui::canvas), func, params, Ref(type<mud::Canvas>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::scrollable(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "scrollable", function_id<mud::Widget&(*)(mud::Widget&)>(&mud::ui::scrollable), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::sequence(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "sequence", function_id<mud::ui::Sequence&(*)(mud::Widget&)>(&mud::ui::sequence), func, params, Ref(type<mud::ui::Sequence>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::scroll_sequence(val<mud::Widget>(args[0]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "scroll_sequence", function_id<mud::ui::Sequence&(*)(mud::Widget&)>(&mud::ui::scroll_sequence), func, params, Ref(type<mud::ui::Sequence>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::multiselect_logic(val<mud::Widget>(args[0]), args[1], val<std::vector<mud::Ref>>(args[2])); };
            std::vector<Param> params = { { "element", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable }, { "selection", var(std::vector<mud::Ref>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "multiselect_logic", function_id<bool(*)(mud::Widget&, mud::Ref, std::vector<mud::Ref>&)>(&mud::ui::multiselect_logic), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<bool>(result) = mud::ui::select_logic(val<mud::Widget>(args[0]), args[1], args[2]); };
            std::vector<Param> params = { { "element", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable }, { "selection", Ref() } };
            static Function f = { &namspc({ "mud", "ui" }), "select_logic", function_id<bool(*)(mud::Widget&, mud::Ref, mud::Ref&)>(&mud::ui::select_logic), func, params, var(bool()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::element(val<mud::Widget>(args[0]), args[1])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "object", Ref(), Param::Nullable } };
            static Function f = { &namspc({ "mud", "ui" }), "element", function_id<mud::Widget&(*)(mud::Widget&, mud::Ref)>(&mud::ui::element), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::sequence_element(val<mud::ui::Sequence>(args[0]), args[1])); };
            std::vector<Param> params = { { "parent", Ref(type<mud::ui::Sequence>()) }, { "object", Ref(), Param::Nullable } };
            static Function f = { &namspc({ "mud", "ui" }), "sequence_element", function_id<mud::Widget&(*)(mud::ui::Sequence&, mud::Ref)>(&mud::ui::sequence_element), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::window(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<mud::WindowState>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "title", var(cstring()) }, { "state", var(mud::WindowState()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "window", function_id<mud::Window&(*)(mud::Widget&, cstring, mud::WindowState)>(&mud::ui::window), func, params, Ref(type<mud::Window>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dir_item(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "dir_item", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::dir_item), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_item(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "file_item", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::file_item), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_list(val<mud::Widget>(args[0]), val<std::string>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "path", var(std::string()) } };
            static Function f = { &namspc({ "mud", "ui" }), "file_list", function_id<mud::Widget&(*)(mud::Widget&, std::string&)>(&mud::ui::file_list), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_browser(val<mud::Widget>(args[0]), val<std::string>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "path", var(std::string()) } };
            static Function f = { &namspc({ "mud", "ui" }), "file_browser", function_id<mud::Widget&(*)(mud::Widget&, std::string&)>(&mud::ui::file_browser), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::dir_node(val<mud::Widget>(args[0]), val<cstring>(args[1]), val<cstring>(args[2]), val<bool>(args[3]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "path", var(cstring()) }, { "name", var(cstring()) }, { "collapsed", var(bool()) } };
            static Function f = { &namspc({ "mud", "ui" }), "dir_node", function_id<mud::Widget&(*)(mud::Widget&, cstring, cstring, bool)>(&mud::ui::dir_node), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_node(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "name", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "file_node", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::file_node), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::file_tree(val<mud::Widget>(args[0]), val<cstring>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "path", var(cstring()) } };
            static Function f = { &namspc({ "mud", "ui" }), "file_tree", function_id<mud::Widget&(*)(mud::Widget&, cstring)>(&mud::ui::file_tree), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::command_line(val<mud::Widget>(args[0]), val<std::string>(args[1]), val<std::string>(args[2]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "text", var(std::string()) }, { "command", var(std::string()) } };
            static Function f = { &namspc({ "mud", "ui" }), "command_line", function_id<mud::Widget&(*)(mud::Widget&, std::string&, std::string&)>(&mud::ui::command_line), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::console(val<mud::Widget>(args[0]), val<std::string>(args[1]), val<std::string>(args[2]), val<std::string>(args[3]), val<size_t>(args[4]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "feed", var(std::string()) }, { "line", var(std::string()) }, { "command", var(std::string()) }, { "num_lines", var(size_t()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "console", function_id<mud::Widget&(*)(mud::Widget&, std::string&, std::string&, std::string&, size_t)>(&mud::ui::console), func, params, Ref(type<mud::Widget>()) };
            m.m_functions.push_back(&f);
        }
    }
}
