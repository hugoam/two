#include <ui/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_ui)
{
    
    // Enums
    enum_<mud::Align>("mud::Align")
        .value("Left", mud::Left)
        .value("CENTER", mud::CENTER)
        .value("Right", mud::Right)
        .value("OUT_LEFT", mud::OUT_LEFT)
        .value("OUT_RIGHT", mud::OUT_RIGHT)
        ;
    enum_<mud::AutoLayout>("mud::AutoLayout")
        .value("NO_LAYOUT", mud::NO_LAYOUT)
        .value("AUTO_SIZE", mud::AUTO_SIZE)
        .value("AUTO_LAYOUT", mud::AUTO_LAYOUT)
        ;
    enum_<mud::Clipping>("mud::Clipping")
        .value("NOCLIP", mud::NOCLIP)
        .value("CLIP", mud::CLIP)
        .value("UNCLIP", mud::UNCLIP)
        ;
    enum_<mud::Dim>("mud::Dim")
        .value("DIM_X", mud::DIM_X)
        .value("DIM_Y", mud::DIM_Y)
        .value("DIM_NONE", mud::DIM_NONE)
        ;
    enum_<mud::Flow>("mud::Flow")
        .value("FLOW", mud::FLOW)
        .value("OVERLAY", mud::OVERLAY)
        .value("ALIGN", mud::ALIGN)
        .value("FREE", mud::FREE)
        ;
    enum_<mud::FlowAxis>("mud::FlowAxis")
        .value("READING", mud::READING)
        .value("PARAGRAPH", mud::PARAGRAPH)
        .value("PARALLEL", mud::PARALLEL)
        .value("ORTHOGONAL", mud::ORTHOGONAL)
        .value("AXIS_NONE", mud::AXIS_NONE)
        ;
    enum_<mud::LayoutSolver>("mud::LayoutSolver")
        .value("FRAME_SOLVER", mud::FRAME_SOLVER)
        .value("ROW_SOLVER", mud::ROW_SOLVER)
        .value("GRID_SOLVER", mud::GRID_SOLVER)
        .value("TABLE_SOLVER", mud::TABLE_SOLVER)
        ;
    enum_<mud::Opacity>("mud::Opacity")
        .value("OPAQUE", mud::OPAQUE)
        .value("CLEAR", mud::CLEAR)
        .value("HOLLOW", mud::HOLLOW)
        ;
    enum_<mud::Pivot>("mud::Pivot")
        .value("FORWARD", mud::FORWARD)
        .value("REVERSE", mud::REVERSE)
        ;
    enum_<mud::ui::PopupFlags>("mud::ui::PopupFlags")
        .value("None", mud::ui::PopupFlags::None)
        .value("Modal", mud::ui::PopupFlags::Modal)
        .value("Clamp", mud::ui::PopupFlags::Clamp)
        .value("AutoClose", mud::ui::PopupFlags::AutoClose)
        .value("AutoModal", mud::ui::PopupFlags::AutoModal)
        ;
    enum_<mud::Sizing>("mud::Sizing")
        .value("FIXED", mud::FIXED)
        .value("SHRINK", mud::SHRINK)
        .value("WRAP", mud::WRAP)
        .value("EXPAND", mud::EXPAND)
        ;
    enum_<mud::SpacePreset>("mud::SpacePreset")
        .value("SHEET", mud::SHEET)
        .value("FLEX", mud::FLEX)
        .value("ITEM", mud::ITEM)
        .value("UNIT", mud::UNIT)
        .value("BLOCK", mud::BLOCK)
        .value("LINE", mud::LINE)
        .value("STACK", mud::STACK)
        .value("DIV", mud::DIV)
        .value("SPACER", mud::SPACER)
        .value("BOARD", mud::BOARD)
        .value("LAYOUT", mud::LAYOUT)
        ;
    enum_<mud::WidgetState>("mud::WidgetState")
        .value("NOSTATE", mud::NOSTATE)
        .value("CREATED", mud::CREATED)
        .value("HOVERED", mud::HOVERED)
        .value("PRESSED", mud::PRESSED)
        .value("ACTIVATED", mud::ACTIVATED)
        .value("ACTIVE", mud::ACTIVE)
        .value("SELECTED", mud::SELECTED)
        .value("DISABLED", mud::DISABLED)
        .value("DRAGGED", mud::DRAGGED)
        .value("FOCUSED", mud::FOCUSED)
        .value("CLOSED", mud::CLOSED)
        ;
    enum_<mud::WindowState>("mud::WindowState")
        .value("WINDOW_NOSTATE", mud::WINDOW_NOSTATE)
        .value("WINDOW_HEADER", mud::WINDOW_HEADER)
        .value("WINDOW_DOCKABLE", mud::WINDOW_DOCKABLE)
        .value("WINDOW_CLOSABLE", mud::WINDOW_CLOSABLE)
        .value("WINDOW_MOVABLE", mud::WINDOW_MOVABLE)
        .value("WINDOW_SIZABLE", mud::WINDOW_SIZABLE)
        .value("WINDOW_DEFAULT", mud::WINDOW_DEFAULT)
        ;
    
    // Sequences
    
    // Arrays
    value_array<mud::Dim2<bool>>("Dim2<bool>")
        .element(&mud::Dim2<bool>::x)
        .element(&mud::Dim2<bool>::y)
        ;
    value_array<mud::Dim2<mud::Align>>("Dim2<mud::Align>")
        .element(&mud::Dim2<mud::Align>::x)
        .element(&mud::Dim2<mud::Align>::y)
        ;
    value_array<mud::Dim2<mud::AutoLayout>>("Dim2<mud::AutoLayout>")
        .element(&mud::Dim2<mud::AutoLayout>::x)
        .element(&mud::Dim2<mud::AutoLayout>::y)
        ;
    value_array<mud::Dim2<mud::Pivot>>("Dim2<mud::Pivot>")
        .element(&mud::Dim2<mud::Pivot>::x)
        .element(&mud::Dim2<mud::Pivot>::y)
        ;
    value_array<mud::Dim2<mud::Sizing>>("Dim2<mud::Sizing>")
        .element(&mud::Dim2<mud::Sizing>::x)
        .element(&mud::Dim2<mud::Sizing>::y)
        ;
    value_array<mud::Dim2<size_t>>("Dim2<size_t>")
        .element(&mud::Dim2<size_t>::x)
        .element(&mud::Dim2<size_t>::y)
        ;
    
    // Structs
    value_object<mud::CanvasConnect>("CanvasConnect")
        ;
    value_object<mud::Clipboard>("Clipboard")
        .field("text", &mud::Clipboard::m_text)
        .field("line_mode", &mud::Clipboard::m_line_mode)
        .field("pasted", &mud::Clipboard::m_pasted)
        ;
    value_object<mud::Dock>("Dock")
        ;
    value_object<mud::Gradient>("Gradient")
        .field("start", &mud::Gradient::m_start)
        .field("end", &mud::Gradient::m_end)
        ;
    value_object<mud::ImageSkin>("ImageSkin")
        .field("d_image", &mud::ImageSkin::d_image)
        .field("d_left", &mud::ImageSkin::d_left)
        .field("d_top", &mud::ImageSkin::d_top)
        .field("d_right", &mud::ImageSkin::d_right)
        .field("d_bottom", &mud::ImageSkin::d_bottom)
        .field("margin", &mud::ImageSkin::m_margin)
        .field("d_stretch", &mud::ImageSkin::d_stretch)
        ;
    value_object<mud::InkStyle>("InkStyle")
        .field("name", &mud::InkStyle::m_name)
        .field("empty", &mud::InkStyle::m_empty)
        .field("background_colour", &mud::InkStyle::m_background_colour)
        .field("border_colour", &mud::InkStyle::m_border_colour)
        .field("image_colour", &mud::InkStyle::m_image_colour)
        .field("text_colour", &mud::InkStyle::m_text_colour)
        .field("text_font", &mud::InkStyle::m_text_font)
        .field("text_size", &mud::InkStyle::m_text_size)
        .field("text_break", &mud::InkStyle::m_text_break)
        .field("text_wrap", &mud::InkStyle::m_text_wrap)
        .field("border_width", &mud::InkStyle::m_border_width)
        .field("corner_radius", &mud::InkStyle::m_corner_radius)
        .field("weak_corners", &mud::InkStyle::m_weak_corners)
        .field("padding", &mud::InkStyle::m_padding)
        .field("margin", &mud::InkStyle::m_margin)
        .field("align", &mud::InkStyle::m_align)
        .field("linear_gradient", &mud::InkStyle::m_linear_gradient)
        .field("linear_gradient_dim", &mud::InkStyle::m_linear_gradient_dim)
        .field("stretch", &mud::InkStyle::m_stretch)
        .field("image", &mud::InkStyle::m_image)
        .field("overlay", &mud::InkStyle::m_overlay)
        .field("tile", &mud::InkStyle::m_tile)
        .field("image_skin", &mud::InkStyle::m_image_skin)
        .field("shadow", &mud::InkStyle::m_shadow)
        .field("shadow_colour", &mud::InkStyle::m_shadow_colour)
        .field("hover_cursor", &mud::InkStyle::m_hover_cursor)
        ;
    value_object<mud::Layout>("Layout")
        .field("name", &mud::Layout::m_name)
        .field("solver", &mud::Layout::m_solver)
        .field("layout", &mud::Layout::m_layout)
        .field("flow", &mud::Layout::m_flow)
        .field("space", &mud::Layout::m_space)
        .field("clipping", &mud::Layout::m_clipping)
        .field("opacity", &mud::Layout::m_opacity)
        .field("align", &mud::Layout::m_align)
        .field("span", &mud::Layout::m_span)
        .field("size", &mud::Layout::m_size)
        .field("padding", &mud::Layout::m_padding)
        .field("margin", &mud::Layout::m_margin)
        .field("spacing", &mud::Layout::m_spacing)
        .field("pivot", &mud::Layout::m_pivot)
        .field("zorder", &mud::Layout::m_zorder)
        .field("no_grid", &mud::Layout::m_no_grid)
        .field("grid_division", &mud::Layout::m_grid_division)
        .field("table_division", &mud::Layout::m_table_division)
        .field("updated", &mud::Layout::m_updated)
        ;
    value_object<mud::NodeConnection>("NodeConnection")
        ;
    value_object<mud::Paint>("Paint")
        .field("fill_colour", &mud::Paint::m_fill_colour)
        .field("stroke_colour", &mud::Paint::m_stroke_colour)
        .field("stroke_width", &mud::Paint::m_stroke_width)
        ;
    value_object<mud::Shadow>("Shadow")
        .field("d_xpos", &mud::Shadow::d_xpos)
        .field("d_ypos", &mud::Shadow::d_ypos)
        .field("d_blur", &mud::Shadow::d_blur)
        .field("d_spread", &mud::Shadow::d_spread)
        .field("d_colour", &mud::Shadow::d_colour)
        ;
    value_object<mud::Space>("Space")
        .field("direction", &mud::Space::direction)
        .field("sizingLength", &mud::Space::sizingLength)
        .field("sizingDepth", &mud::Space::sizingDepth)
        ;
    value_object<mud::TextCursor>("TextCursor")
        ;
    value_object<mud::TextMarker>("TextMarker")
        ;
    value_object<mud::TextPaint>("TextPaint")
        .field("font", &mud::TextPaint::m_font)
        .field("colour", &mud::TextPaint::m_colour)
        .field("size", &mud::TextPaint::m_size)
        .field("align", &mud::TextPaint::m_align)
        .field("text_break", &mud::TextPaint::m_text_break)
        .field("text_wrap", &mud::TextPaint::m_text_wrap)
        ;
    value_object<mud::TextSelection>("TextSelection")
        ;
    value_object<mud::UiRect>("UiRect")
        .field("position", &mud::UiRect::m_position)
        .field("size", &mud::UiRect::m_size)
        .field("content", &mud::UiRect::m_content)
        .field("span", &mud::UiRect::m_span)
        .field("scale", &mud::UiRect::m_scale)
        ;
    
    // Classes
    class_<mud::Docksystem>("Docksystem")
        ;
    class_<mud::GridSolver>("GridSolver")
        ;
    class_<mud::Layer>("Layer")
        ;
    class_<mud::Style>("Style")
        .property("base", &mud::Style::m_base)
        .property("name", &mud::Style::name, &mud::Style::setName)
        .property("layout", &mud::Style::layout, &mud::Style::setLayout)
        .property("skin", &mud::Style::skin, &mud::Style::setSkin)
        ;
    class_<mud::TableSolver>("TableSolver")
        ;
    class_<mud::Text>("Text")
        ;
    class_<mud::UiWindow>("UiWindow")
        ;
    class_<mud::User>("User")
        ;
    class_<mud::Vg>("Vg")
        ;
    class_<mud::Frame>("Frame")
        ;
    class_<mud::FrameSolver>("FrameSolver")
        ;
    class_<mud::LineSolver>("LineSolver")
        ;
    class_<mud::Widget>("Widget")
        .property("frame", &mud::Widget::m_frame)
        .property("state", &mud::Widget::m_state)
        .property("switch", &mud::Widget::m_switch)
        .property("index", &mud::Widget::m_index)
        .property("open", &mud::Widget::m_open)
        .property("body", &mud::Widget::m_body)
        .function("focused", &mud::Widget::focused)
        .function("hovered", &mud::Widget::hovered)
        .function("pressed", &mud::Widget::pressed)
        .function("activated", &mud::Widget::activated)
        .function("selected", &mud::Widget::selected)
        .function("modal", &mud::Widget::modal)
        .function("closed", &mud::Widget::closed)
        .function("ui_window", &mud::Widget::ui_window)
        .function("ui", &mud::Widget::ui)
        .function("parent_modal", &mud::Widget::parent_modal)
        .function("toggle_state", &mud::Widget::toggle_state)
        .function("disable_state", &mud::Widget::disable_state)
        .function("set_state", &mud::Widget::set_state)
        .function("enable_state", &mud::Widget::enable_state)
        .function("clear_focus", &mud::Widget::clear_focus)
        .function("take_focus", &mud::Widget::take_focus)
        .function("yield_focus", &mud::Widget::yield_focus)
        .function("take_modal", &mud::Widget::take_modal)
        .function("yield_modal", &mud::Widget::yield_modal)
        .function("key_event", &mud::Widget::key_event)
        .function("key_stroke", &mud::Widget::key_stroke)
        .function("char_stroke", &mud::Widget::char_stroke)
        .function("mouse_event", &mud::Widget::mouse_event)
        ;
    class_<mud::Canvas>("Canvas")
        ;
    class_<mud::Dockable>("Dockable")
        ;
    class_<mud::Docker>("Docker")
        ;
    class_<mud::Dockbar>("Dockbar")
        ;
    class_<mud::Dockspace>("Dockspace")
        ;
    class_<mud::Expandbox>("Expandbox")
        ;
    class_<mud::Node>("Node")
        ;
    class_<mud::NodePlug>("NodePlug")
        ;
    class_<mud::RowSolver>("RowSolver")
        ;
    class_<mud::ScrollSheet>("ScrollSheet")
        ;
    class_<mud::ui::Sequence>("Sequence")
        ;
    class_<mud::Tabber>("Tabber")
        ;
    class_<mud::Table>("Table")
        ;
    class_<mud::TextEdit>("TextEdit")
        ;
    class_<mud::TreeNode>("TreeNode")
        ;
    class_<mud::Ui>("Ui")
        .function("begin", &mud::Ui::begin)
        ;
    class_<mud::Window>("Window")
        ;
    
    // Functions
    function("widget", &mud::ui::widget);
    function("item", &mud::ui::item);
    function("multi_item", &mud::ui::multi_item);
    function("spanner", &mud::ui::spanner);
    function("spacer", &mud::ui::spacer);
    function("icon", &mud::ui::icon);
    function("label", &mud::ui::label);
    function("title", &mud::ui::title);
    function("message", &mud::ui::message);
    function("text", &mud::ui::text);
    function("button", &mud::ui::button);
    function("multi_button", &mud::ui::multi_button);
    function("toggle", &mud::ui::toggle);
    function("multi_toggle", &mud::ui::multi_toggle);
    function("modal_button", &mud::ui::modal_button);
    function("modal_multi_button", &mud::ui::modal_multi_button);
    function("checkbox", &mud::ui::checkbox);
    function("fill_bar", &mud::ui::fill_bar);
    function("image256", &mud::ui::image256);
    function("image256", &mud::ui::image256);
    function("radio_choice", &mud::ui::radio_choice);
    function("radio_switch", &mud::ui::radio_switch);
    function("popdown", &mud::ui::popdown);
    function("dropdown", &mud::ui::dropdown);
    function("dropdown_input", &mud::ui::dropdown_input);
    function("typedown_input", &mud::ui::typedown_input);
    function("menu_choice", &mud::ui::menu_choice);
    function("menu", &mud::ui::menu);
    function("menubar", &mud::ui::menubar);
    function("toolbutton", &mud::ui::toolbutton);
    function("tooldock", &mud::ui::tooldock);
    function("toolbar", &mud::ui::toolbar);
    function("select_list", &mud::ui::select_list);
    function("columns", &mud::ui::columns);
    function("table", &mud::ui::table);
    function("table_row", &mud::ui::table_row);
    function("table_separator", &mud::ui::table_separator);
    function("expandbox", &mud::ui::expandbox);
    function("tree_node", &mud::ui::tree_node);
    function("tree", &mud::ui::tree);
    function("tab", &mud::ui::tab);
    function("tabber", &mud::ui::tabber);
    function("row", &mud::ui::row);
    function("header", &mud::ui::header);
    function("div", &mud::ui::div);
    function("stack", &mud::ui::stack);
    function("sheet", &mud::ui::sheet);
    function("board", &mud::ui::board);
    function("layout", &mud::ui::layout);
    function("screen", &mud::ui::screen);
    function("decal", &mud::ui::decal);
    function("overlay", &mud::ui::overlay);
    function("title_header", &mud::ui::title_header);
    function("dummy", &mud::ui::dummy);
    function("popup", &mud::ui::popup);
    function("popup", &mud::ui::popup);
    function("popup_at", &mud::ui::popup_at);
    function("modal", &mud::ui::modal);
    function("modal", &mud::ui::modal);
    function("auto_modal", &mud::ui::auto_modal);
    function("auto_modal", &mud::ui::auto_modal);
    function("context", &mud::ui::context);
    function("hoverbox", &mud::ui::hoverbox);
    function("tooltip", &mud::ui::tooltip);
    function("cursor", &mud::ui::cursor);
    function("rectangle", &mud::ui::rectangle);
    function("dockspace", &mud::ui::dockspace);
    function("dockbar", &mud::ui::dockbar);
    function("dockitem", &mud::ui::dockitem);
    function("text_box", &mud::ui::text_box);
    function("type_in", &mud::ui::type_in);
    function("text_edit", &mud::ui::text_edit);
    function("code_edit", &mud::ui::code_edit);
    function("drag_float", &mud::ui::drag_float);
    function("vec2_edit", &mud::ui::vec2_edit);
    function("vec3_edit", &mud::ui::vec3_edit);
    function("quat_edit", &mud::ui::quat_edit);
    function("color_edit_hsl", &mud::ui::color_edit_hsl);
    function("color_display", &mud::ui::color_display);
    function("color_edit", &mud::ui::color_edit);
    function("color_edit_simple", &mud::ui::color_edit_simple);
    function("color_toggle_edit", &mud::ui::color_toggle_edit);
    function("curve_graph", &mud::ui::curve_graph);
    function("curve_edit", &mud::ui::curve_edit);
    function("flag_field", &mud::ui::flag_field);
    function("radio_field", &mud::ui::radio_field);
    function("dropdown_field", &mud::ui::dropdown_field);
    function("typedown_field", &mud::ui::typedown_field);
    function("color_field", &mud::ui::color_field);
    function("color_display_field", &mud::ui::color_display_field);
    function("node_input", &mud::ui::node_input);
    function("node_output", &mud::ui::node_output);
    function("node", &mud::ui::node);
    function("node_cable", &mud::ui::node_cable);
    function("canvas", &mud::ui::canvas);
    function("scrollable", &mud::ui::scrollable);
    function("sequence", &mud::ui::sequence);
    function("scroll_sequence", &mud::ui::scroll_sequence);
    function("multiselect_logic", &mud::ui::multiselect_logic);
    function("select_logic", &mud::ui::select_logic);
    function("element", &mud::ui::element);
    function("sequence_element", &mud::ui::sequence_element);
    function("window", &mud::ui::window);
    function("dir_item", &mud::ui::dir_item);
    function("file_item", &mud::ui::file_item);
    function("file_list", &mud::ui::file_list);
    function("file_browser", &mud::ui::file_browser);
    function("dir_node", &mud::ui::dir_node);
    function("file_node", &mud::ui::file_node);
    function("file_tree", &mud::ui::file_tree);
    function("command_line", &mud::ui::command_line);
    function("console", &mud::ui::console);
    
}
