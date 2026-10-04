#pragma once

using namespace two;

#ifndef _00_IDE_EXPORT
#define _00_IDE_EXPORT TWO_IMPORT
#endif

// an IDE main window, modelled on Visual Studio: menus, toolbars, docked panels, a tree, code editors, an output log, a status bar
// it exercises every sizing mode and most of the widgets, as a reference to check the layout against
_00_IDE_EXPORT void example_ide(Widget& ui);
