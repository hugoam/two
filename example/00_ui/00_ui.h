
#pragma once

#include <mud/Forward.h>

using namespace mud;

#if defined _00_UI_LIB
#define _00_UI_EXPORT MUD_EXPORT
#else
#define _00_UI_EXPORT MUD_IMPORT
#endif


_00_UI_EXPORT void switchUiTheme(UiWindow& ui_window, const string& name);
//_00_UI_EXPORT void selectUiTheme(Widget& sheet, Widget& selected);
//_00_UI_EXPORT void pickUiSample(Widget& sheet, Widget& selected);

_00_UI_EXPORT void ex_style_edit(Widget& parent);
_00_UI_EXPORT void ex_scroll_list(Widget& parent);
_00_UI_EXPORT void ex_custom_list(Widget& parent);
_00_UI_EXPORT void ex_filtered_list(Widget& parent);
_00_UI_EXPORT void ex_text_editor(Widget& parent);
_00_UI_EXPORT void ex_application(Widget& parent);
_00_UI_EXPORT void ex_console(Widget& parent);
_00_UI_EXPORT void ex_script_editor(Widget& parent);
_00_UI_EXPORT void ex_dockspace(Widget& parent);
_00_UI_EXPORT void ex_nodes(Widget& parent);
_00_UI_EXPORT void ex_tabs(Widget& parent);
_00_UI_EXPORT void ex_table(Widget& parent);
_00_UI_EXPORT void ex_tree(Widget& parent);
_00_UI_EXPORT void ex_inline_controls(Widget& parent);
_00_UI_EXPORT void ex_controls(Widget& parent);
_00_UI_EXPORT void ex_progress_dialog(Widget& parent);
_00_UI_EXPORT void ex_window(Widget& parent);
_00_UI_EXPORT void ex_window_page(Widget& parent);
_00_UI_EXPORT void ex_file_browser(Widget& parent);
_00_UI_EXPORT void ex_file_tree(Widget& parent);

_00_UI_EXPORT void example_ui(Widget& root_sheet);

