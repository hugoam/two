// The flags of the dear imgui API used by the demo, copied as is from imgui.h (v1.93.0 WIP) so the port of the demo maps 1:1 to the original.
// Most of them have no equivalent in two.ui yet: they are only exposed as options in the demo, as in the original.

// dear imgui is licensed under the MIT License, see https://github.com/ocornut/imgui/blob/master/LICENSE.txt
// Copyright (c) 2014-2026 Omar Cornut

#pragma once

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS

typedef int ImGuiWindowFlags;       // -> enum ImGuiWindowFlags_
typedef int ImGuiChildFlags;        // -> enum ImGuiChildFlags_
typedef int ImGuiItemFlags;         // -> enum ImGuiItemFlags_
typedef int ImGuiInputTextFlags;    // -> enum ImGuiInputTextFlags_
typedef int ImGuiTreeNodeFlags;     // -> enum ImGuiTreeNodeFlags_
typedef int ImGuiPopupFlags;        // -> enum ImGuiPopupFlags_
typedef int ImGuiSelectableFlags;   // -> enum ImGuiSelectableFlags_
typedef int ImGuiComboFlags;        // -> enum ImGuiComboFlags_
typedef int ImGuiTabBarFlags;       // -> enum ImGuiTabBarFlags_
typedef int ImGuiTabItemFlags;      // -> enum ImGuiTabItemFlags_
typedef int ImGuiFocusedFlags;      // -> enum ImGuiFocusedFlags_
typedef int ImGuiHoveredFlags;      // -> enum ImGuiHoveredFlags_
typedef int ImGuiDragDropFlags;     // -> enum ImGuiDragDropFlags_
typedef int ImGuiConfigFlags;       // -> enum ImGuiConfigFlags_
typedef int ImGuiBackendFlags;      // -> enum ImGuiBackendFlags_
typedef int ImGuiColorEditFlags;    // -> enum ImGuiColorEditFlags_
typedef int ImGuiSliderFlags;       // -> enum ImGuiSliderFlags_
typedef int ImGuiTableFlags;        // -> enum ImGuiTableFlags_
typedef int ImGuiTableColumnFlags;  // -> enum ImGuiTableColumnFlags_

enum ImGuiWindowFlags_
{
    ImGuiWindowFlags_None                   = 0,
    ImGuiWindowFlags_NoTitleBar             = 1 << 0,   // Disable title-bar
    ImGuiWindowFlags_NoResize               = 1 << 1,   // Disable user resizing with the lower-right grip
    ImGuiWindowFlags_NoMove                 = 1 << 2,   // Disable user moving the window
    ImGuiWindowFlags_NoScrollbar            = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    ImGuiWindowFlags_NoScrollWithMouse      = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    ImGuiWindowFlags_NoCollapse             = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
    ImGuiWindowFlags_AlwaysAutoResize       = 1 << 6,   // Resize every window to its content every frame
    ImGuiWindowFlags_NoBackground           = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    ImGuiWindowFlags_NoSavedSettings        = 1 << 8,   // Never load/save settings in .ini file
    ImGuiWindowFlags_NoMouseInputs          = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    ImGuiWindowFlags_MenuBar                = 1 << 10,  // Has a menu-bar
    ImGuiWindowFlags_HorizontalScrollbar    = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    ImGuiWindowFlags_NoFocusOnAppearing     = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    ImGuiWindowFlags_NoBringToFrontOnFocus  = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    ImGuiWindowFlags_AlwaysVerticalScrollbar= 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    ImGuiWindowFlags_AlwaysHorizontalScrollbar=1<< 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    ImGuiWindowFlags_NoNavInputs            = 1 << 16,  // No keyboard/gamepad navigation within the window
    ImGuiWindowFlags_NoNavFocus             = 1 << 17,  // No focusing toward this window with keyboard/gamepad navigation (e.g. skipped by Ctrl+Tab)
    ImGuiWindowFlags_UnsavedDocument        = 1 << 18,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    ImGuiWindowFlags_NoNav                  = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
    ImGuiWindowFlags_NoDecoration           = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
    ImGuiWindowFlags_NoInputs               = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,

    // [Internal]
    ImGuiWindowFlags_ChildWindow            = 1 << 24,  // Don't use! For internal use by BeginChild()
    ImGuiWindowFlags_Tooltip                = 1 << 25,  // Don't use! For internal use by BeginTooltip()
    ImGuiWindowFlags_Popup                  = 1 << 26,  // Don't use! For internal use by BeginPopup()
    ImGuiWindowFlags_Modal                  = 1 << 27,  // Don't use! For internal use by BeginPopupModal()
    ImGuiWindowFlags_ChildMenu              = 1 << 28,  // Don't use! For internal use by BeginMenu()

    // Obsolete names
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    //ImGuiWindowFlags_NavFlattened           = 1 << 29,  // Obsoleted in 1.90.9: moved to ImGuiChildFlags. BeginChild(name, size, 0, ImGuiWindowFlags_NavFlattened)           --> BeginChild(name, size, ImGuiChildFlags_NavFlattened, 0)
    //ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 30,  // Obsoleted in 1.90.0: moved to ImGuiChildFlags. BeginChild(name, size, 0, ImGuiWindowFlags_AlwaysUseWindowPadding) --> BeginChild(name, size, ImGuiChildFlags_AlwaysUseWindowPadding, 0)
#endif
};

enum ImGuiChildFlags_
{
    ImGuiChildFlags_None                    = 0,
    ImGuiChildFlags_Borders                 = 1 << 0,   // Show an outer border and enable WindowPadding. (IMPORTANT: this is always == 1 == true for legacy reason)
    ImGuiChildFlags_AlwaysUseWindowPadding  = 1 << 1,   // Pad with style.WindowPadding even if no border are drawn (no padding by default for non-bordered child windows because it makes more sense)
    ImGuiChildFlags_ResizeX                 = 1 << 2,   // Allow resize from right border (layout direction). Enable .ini saving (unless ImGuiWindowFlags_NoSavedSettings passed to window flags)
    ImGuiChildFlags_ResizeY                 = 1 << 3,   // Allow resize from bottom border (layout direction). "
    ImGuiChildFlags_AutoResizeX             = 1 << 4,   // Enable auto-resizing width. Read "IMPORTANT: Size measurement" details above.
    ImGuiChildFlags_AutoResizeY             = 1 << 5,   // Enable auto-resizing height. Read "IMPORTANT: Size measurement" details above.
    ImGuiChildFlags_AlwaysAutoResize        = 1 << 6,   // Combined with AutoResizeX/AutoResizeY. Always measure size even when child is hidden, always return true, always disable clipping optimization! NOT RECOMMENDED.
    ImGuiChildFlags_FrameStyle              = 1 << 7,   // Style the child window like a framed item: use FrameBg, FrameRounding, FrameBorderSize, FramePadding instead of ChildBg, ChildRounding, ChildBorderSize, WindowPadding.
    ImGuiChildFlags_NavFlattened            = 1 << 8,   // [BETA] Share focus scope, allow keyboard/gamepad navigation to cross over parent border to this child or between sibling child windows.

    // Obsolete names
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    //ImGuiChildFlags_Border                = ImGuiChildFlags_Borders,  // Renamed in 1.91.1 (August 2024) for consistency.
#endif
};

enum ImGuiItemFlags_
{
    ImGuiItemFlags_None                     = 0,        // Default:
    ImGuiItemFlags_NoTabStop                = 1 << 0,   // false    // Disable keyboard tabbing. This is a "lighter" version of ImGuiItemFlags_NoNav.
    ImGuiItemFlags_NoNav                    = 1 << 1,   // false    // Disable any form of focusing: keyboard/gamepad directional navigation and SetKeyboardFocusHere() calls.
    ImGuiItemFlags_NoNavDefaultFocus        = 1 << 2,   // false    // Disable item being a candidate for default focus (e.g. used by title bar items).
    ImGuiItemFlags_ButtonRepeat             = 1 << 3,   // false    // Any button-like behavior will have repeat mode enabled (based on io.KeyRepeatDelay and io.KeyRepeatRate values). Note that you can also call IsItemActive() after any button to tell if it is being held.
    ImGuiItemFlags_AutoClosePopups          = 1 << 4,   // true     // MenuItem()/Selectable() automatically close their parent popup window.
    ImGuiItemFlags_AllowDuplicateId         = 1 << 5,   // false    // Allow submitting an item with the same identifier as an item already submitted this frame without triggering a warning tooltip if io.ConfigDebugHighlightIdConflicts is set.
    ImGuiItemFlags_Disabled                 = 1 << 6,   // false    // [Internal] Disable interactions. DOES NOT affect visuals. This is used by BeginDisabled()/EndDisabled() and only provided here so you can read back via GetItemFlags().

    //---------------------------------------------------------------------------------
    // LiveEdit refers to applying edits to backing variables _while_ typing a value using the keyboard.
    // Widget:                          | Input:   | w/ LiveEdit:    | Output:
    //   InputText()                    |   "123"  |   on(default)   |  "1" then "12" then "123"
    //   InputText()                    |   "123"  |   off           |  "123" after validating or tabbing out or losing focus.
    //   DragFloat(), SliderInt(), etc. |   "123"  |   on*           |  1 then 12 then 123
    //   DragFloat(), SliderInt(), etc. |   "123"  |   off(default)* |  123 after validation or tabbing out or losing focus.
    // (*) Since 1.92.9 (July 2026), ImGuiItemFlags_LiveEditOnInputScalar is OFF by default. In prior version it was ON for everything.
    //---------------------------------------------------------------------------------
    ImGuiItemFlags_LiveEditOnInputText      = 1 << 7,   // true     // InputText: apply keyboard edits to backing value while typing. Otherwise, edits are applied when validating, tabbing out or losing focus.
    ImGuiItemFlags_LiveEditOnInputScalar    = 1 << 8,   // false    // DragXXX, SliderXXX, InputScalar: apply keyboard edits to backing value while typing. Otherwise, edits are applied when validating, tabbing out or losing focus.
    ImGuiItemFlags_LiveEditOnInput          = ImGuiItemFlags_LiveEditOnInputText | ImGuiItemFlags_LiveEditOnInputScalar,

    //---------------------------------------------------------------------------------
    // [BETA] MixedValue mode used to represent a mixed/indeterminate state, typically for multi-selection.
    // - Replace value display with "-" or a custom label.
    // - Enter key validation apply an edit and return true even if value hasn't changed (in order to apply to all).
    // - Supported by selected widgets: Checkbox, RadioButton, Sliders, Drags, Inputs, Combo.
    // - Note: InputText-side Undo cannot be reliably combined with MixedValue + LiveEdit On:
    //   - Both the initial edit and subsequent undo/revert will typically make your app code write to all backing objects.
    //   - If you use MixedMode and the simplest solution is to ensure LiveEdit is off but widgets where this applies.
    //---------------------------------------------------------------------------------
    ImGuiItemFlags_MixedValue               = 1 << 9,   // false    // [BETA] Represent a mixed/indeterminate value. Replace value label with "-" and apply edits on validation.
};

enum ImGuiInputTextFlags_
{
    // Basic filters (also see ImGuiInputTextFlags_CallbackCharFilter)
    ImGuiInputTextFlags_None                = 0,
    ImGuiInputTextFlags_CharsDecimal        = 1 << 0,   // Allow 0123456789.+-*/
    ImGuiInputTextFlags_CharsHexadecimal    = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    ImGuiInputTextFlags_CharsScientific     = 1 << 2,   // Allow 0123456789.+-*/eE (Scientific notation input)
    ImGuiInputTextFlags_CharsUppercase      = 1 << 3,   // Turn a..z into A..Z
    ImGuiInputTextFlags_CharsNoBlank        = 1 << 4,   // Filter out spaces, tabs

    // Inputs
    ImGuiInputTextFlags_AllowTabInput       = 1 << 5,   // Pressing TAB input a '\t' character into the text field
    ImGuiInputTextFlags_EnterReturnsTrue    = 1 << 6,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider disabling LiveEdit! or using IsItemDeactivatedAfterEdit() instead!
    ImGuiInputTextFlags_EscapeClearsAll     = 1 << 7,   // Escape key clears content if not empty, and deactivate otherwise (contrast to default behavior of Escape to revert)
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 8,   // In multi-line mode: validate with Enter, add new line with Ctrl+Enter (default is opposite: validate with Ctrl+Enter, add line with Enter). Note that Shift+Enter always enter a new line either way.

    // Other options
    ImGuiInputTextFlags_ReadOnly            = 1 << 9,   // Read-only mode
    ImGuiInputTextFlags_Password            = 1 << 10,  // Password mode, display all characters as '*', disable copy
    ImGuiInputTextFlags_AlwaysOverwrite     = 1 << 11,  // Overwrite mode
    ImGuiInputTextFlags_AutoSelectAll       = 1 << 12,  // Select entire text when first taking mouse focus
    ImGuiInputTextFlags_ParseEmptyRefVal    = 1 << 13,  // InputFloat(), InputInt(), InputScalar() etc. only: parse empty string as zero value.
    ImGuiInputTextFlags_DisplayEmptyRefVal  = 1 << 14,  // InputFloat(), InputInt(), InputScalar() etc. only: when value is zero, do not display it. Generally used with ImGuiInputTextFlags_ParseEmptyRefVal.
    ImGuiInputTextFlags_NoHorizontalScroll  = 1 << 15,  // Disable following the cursor horizontally
    ImGuiInputTextFlags_NoUndoRedo          = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
    //ImGuiInputTextFlags_NoLiveEdit        = 1 << 25,  // Disable applying output to backing variable while typing. Same as setting ImGuiItemFlags_LiveEditOnInput to false.

    // Elide display / Alignment
    ImGuiInputTextFlags_ElideLeft           = 1 << 17,  // When text doesn't fit, elide left side to ensure right side stays visible. Useful for path/filenames. Single-line only!

    // Callback features
    ImGuiInputTextFlags_CallbackCompletion  = 1 << 18,  // Callback on pressing TAB (for completion handling)
    ImGuiInputTextFlags_CallbackHistory     = 1 << 19,  // Callback on pressing Up/Down arrows (for history handling)
    ImGuiInputTextFlags_CallbackAlways      = 1 << 20,  // Callback on each iteration. User code may query cursor position, modify text buffer.
    ImGuiInputTextFlags_CallbackCharFilter  = 1 << 21,  // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
    ImGuiInputTextFlags_CallbackResize      = 1 << 22,  // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
    ImGuiInputTextFlags_CallbackEdit        = 1 << 23,  // Callback on any edit. Note that InputText() already returns true on edit + you can always use IsItemEdited(). The callback is useful to manipulate the underlying buffer while focus is active.

    // Multi-line Word-Wrapping [BETA]
    // - Not well tested yet. Please report any incorrect cursor movement, selection behavior etc. bug to https://github.com/ocornut/imgui/issues/3237.
    // - Wrapping style is not ideal. Wrapping of long words/sections (e.g. words larger than total available width) may be particularly unpleasing.
    // - Wrapping width needs to always account for the possibility of a vertical scrollbar.
    // - It is much slower than regular text fields.
    //   Ballpark estimate of cost on my 2019 desktop PC: for a 100 KB text buffer: +~0.3 ms (Optimized) / +~1.0 ms (Debug build).
    //   The CPU cost is very roughly proportional to text length, so a 10 KB buffer should cost about ten times less.
    ImGuiInputTextFlags_WordWrap            = 1 << 24,  // InputTextMultiline(): word-wrap lines that are too long.

    // Obsolete names
    //ImGuiInputTextFlags_AlwaysInsertMode  = ImGuiInputTextFlags_AlwaysOverwrite   // [renamed in 1.82] name was not matching behavior
};

enum ImGuiTreeNodeFlags_
{
    ImGuiTreeNodeFlags_None                 = 0,
    ImGuiTreeNodeFlags_Selected             = 1 << 0,   // Draw as selected
    ImGuiTreeNodeFlags_Framed               = 1 << 1,   // Draw frame with background (e.g. for CollapsingHeader)
    ImGuiTreeNodeFlags_AllowOverlap         = 1 << 2,   // Hit testing will allow subsequent widgets to overlap this one. Require previous frame HoveredId to match before being usable. Shortcut to calling SetNextItemAllowOverlap().
    ImGuiTreeNodeFlags_NoTreePushOnOpen     = 1 << 3,   // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
    ImGuiTreeNodeFlags_NoAutoOpenOnLog      = 1 << 4,   // Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
    ImGuiTreeNodeFlags_DefaultOpen          = 1 << 5,   // Default node to be open
    ImGuiTreeNodeFlags_OpenOnDoubleClick    = 1 << 6,   // Open on double-click instead of simple click (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
    ImGuiTreeNodeFlags_OpenOnArrow          = 1 << 7,   // Open when clicking on the arrow part (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
    ImGuiTreeNodeFlags_Leaf                 = 1 << 8,   // No collapsing, no arrow (use as a convenience for leaf nodes). Note: will always open a tree/id scope and return true. If you never use that scope, add ImGuiTreeNodeFlags_NoTreePushOnOpen.
    ImGuiTreeNodeFlags_Bullet               = 1 << 9,   // Display a bullet instead of arrow. IMPORTANT: node can still be marked open/close if you don't set the _Leaf flag!
    ImGuiTreeNodeFlags_FramePadding         = 1 << 10,  // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding() before the node.
    ImGuiTreeNodeFlags_SpanAvailWidth       = 1 << 11,  // Extend hit box to the right-most edge, even if not framed. This is not the default in order to allow adding other items on the same line without using AllowOverlap mode.
    ImGuiTreeNodeFlags_SpanFullWidth        = 1 << 12,  // Extend hit box to the left-most and right-most edges (cover the indent area).
    ImGuiTreeNodeFlags_SpanLabelWidth       = 1 << 13,  // Narrow hit box + narrow hovering highlight, will only cover the label text.
    ImGuiTreeNodeFlags_SpanAllColumns       = 1 << 14,  // Frame will span all columns of its container table (label will still fit in current column)
    ImGuiTreeNodeFlags_LabelSpanAllColumns  = 1 << 15,  // Label will span all columns of its container table
    //ImGuiTreeNodeFlags_NoScrollOnOpen     = 1 << 16,  // FIXME: TODO: Disable automatic scroll on TreePop() if node got just open and contents is not visible
    ImGuiTreeNodeFlags_NavLeftJumpsToParent = 1 << 17,  // Nav: left arrow moves back to parent. This is processed in TreePop() when there's an unfulfilled Left nav request remaining.
    ImGuiTreeNodeFlags_CollapsingHeader     = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog,

    // [EXPERIMENTAL] Draw lines connecting TreeNode hierarchy. Discuss in GitHub issue #2920.
    // Default value is pulled from style.TreeLinesFlags. May be overridden in TreeNode calls.
    ImGuiTreeNodeFlags_DrawLinesNone        = 1 << 18,  // No lines drawn
    ImGuiTreeNodeFlags_DrawLinesFull        = 1 << 19,  // Horizontal lines to child nodes. Vertical line drawn down to TreePop() position: cover full contents. Faster (for large trees).
    ImGuiTreeNodeFlags_DrawLinesToNodes     = 1 << 20,  // Horizontal lines to child nodes. Vertical line drawn down to bottom-most child node. Slower (for large trees).

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiTreeNodeFlags_NavLeftJumpsBackHere = ImGuiTreeNodeFlags_NavLeftJumpsToParent,  // Renamed in 1.92.0
    //ImGuiTreeNodeFlags_SpanTextWidth      = ImGuiTreeNodeFlags_SpanLabelWidth,        // Renamed in 1.90.7
    //ImGuiTreeNodeFlags_AllowItemOverlap   = ImGuiTreeNodeFlags_AllowOverlap,          // Renamed in 1.89.7
#endif
};

enum ImGuiPopupFlags_
{
    ImGuiPopupFlags_None                    = 0,
    ImGuiPopupFlags_MouseButtonLeft         = 1 << 2,   // For BeginPopupContext*(): open on Left Mouse release. Only one button allowed!
    ImGuiPopupFlags_MouseButtonRight        = 2 << 2,   // For BeginPopupContext*(): open on Right Mouse release. Only one button allowed! (default)
    ImGuiPopupFlags_MouseButtonMiddle       = 3 << 2,   // For BeginPopupContext*(): open on Middle Mouse release. Only one button allowed!
    ImGuiPopupFlags_NoReopen                = 1 << 5,   // For OpenPopup*(), BeginPopupContext*(): don't reopen same popup if already open (won't reposition, won't reinitialize navigation)
    //ImGuiPopupFlags_NoReopenAlwaysNavInit = 1 << 6,   // For OpenPopup*(), BeginPopupContext*(): focus and initialize navigation even when not reopening.
    ImGuiPopupFlags_NoOpenOverExistingPopup = 1 << 7,   // For OpenPopup*(), BeginPopupContext*(): don't open if there's already a popup at the same level of the popup stack
    ImGuiPopupFlags_NoOpenOverItems         = 1 << 8,   // For BeginPopupContextWindow(): don't return true when hovering items, only when hovering empty space
    ImGuiPopupFlags_AnyPopupId              = 1 << 10,  // For IsPopupOpen(): ignore the ImGuiID parameter and test for any popup.
    ImGuiPopupFlags_AnyPopupLevel           = 1 << 11,  // For IsPopupOpen(): search/test at any level of the popup stack (default test in the current level)
    ImGuiPopupFlags_AnyPopup                = ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel,
    ImGuiPopupFlags_MouseButtonShift_       = 2,        // [Internal]
    ImGuiPopupFlags_MouseButtonMask_        = 0x0C,     // [Internal]
    ImGuiPopupFlags_InvalidMask_            = 0x03,     // [Internal] Reserve legacy bits 0-1 to detect incorrectly passing 1 or 2 to the function.
};

enum ImGuiSelectableFlags_
{
    ImGuiSelectableFlags_None               = 0,
    ImGuiSelectableFlags_NoAutoClosePopups  = 1 << 0,   // Clicking this doesn't close parent popup window (overrides ImGuiItemFlags_AutoClosePopups)
    ImGuiSelectableFlags_SpanAllColumns     = 1 << 1,   // Frame will span all columns of its container table (text will still fit in current column)
    ImGuiSelectableFlags_AllowDoubleClick   = 1 << 2,   // Generate press events on double clicks too
    ImGuiSelectableFlags_Disabled           = 1 << 3,   // Cannot be selected, display grayed out text
    ImGuiSelectableFlags_AllowOverlap       = 1 << 4,   // Hit testing will allow subsequent widgets to overlap this one. Require previous frame HoveredId to match before being usable. Shortcut to calling SetNextItemAllowOverlap().
    ImGuiSelectableFlags_Highlight          = 1 << 5,   // Make the item be displayed as if it is hovered
    ImGuiSelectableFlags_SelectOnNav        = 1 << 6,   // Auto-select when moved into, unless Ctrl is held. Automatic when in a BeginMultiSelect() block.

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiSelectableFlags_DontClosePopups    = ImGuiSelectableFlags_NoAutoClosePopups,   // Renamed in 1.91.0
    //ImGuiSelectableFlags_AllowItemOverlap = ImGuiSelectableFlags_AllowOverlap,        // Renamed in 1.89.7
#endif
};

enum ImGuiComboFlags_
{
    ImGuiComboFlags_None                    = 0,
    ImGuiComboFlags_PopupAlignLeft          = 1 << 0,   // Align the popup toward the left by default
    ImGuiComboFlags_HeightSmall             = 1 << 1,   // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
    ImGuiComboFlags_HeightRegular           = 1 << 2,   // Max ~8 items visible (default)
    ImGuiComboFlags_HeightLarge             = 1 << 3,   // Max ~20 items visible
    ImGuiComboFlags_HeightLargest           = 1 << 4,   // As many fitting items as possible
    ImGuiComboFlags_NoArrowButton           = 1 << 5,   // Display on the preview box without the square arrow button
    ImGuiComboFlags_NoPreview               = 1 << 6,   // Display only a square arrow button
    ImGuiComboFlags_WidthFitPreview         = 1 << 7,   // Width dynamically calculated from preview contents
    ImGuiComboFlags_HeightMask_             = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest,
};

enum ImGuiTabBarFlags_
{
    ImGuiTabBarFlags_None                           = 0,
    ImGuiTabBarFlags_Reorderable                    = 1 << 0,   // Allow manually dragging tabs to re-order them + New tabs are appended at the end of list
    ImGuiTabBarFlags_AutoSelectNewTabs              = 1 << 1,   // Automatically select new tabs when they appear
    ImGuiTabBarFlags_TabListPopupButton             = 1 << 2,   // Disable buttons to open the tab list popup
    ImGuiTabBarFlags_NoCloseWithMiddleMouseButton   = 1 << 3,   // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You may handle this behavior manually on user's side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.
    ImGuiTabBarFlags_NoTabListScrollingButtons      = 1 << 4,   // Disable scrolling buttons (apply when fitting policy is ImGuiTabBarFlags_FittingPolicyScroll)
    ImGuiTabBarFlags_NoTooltip                      = 1 << 5,   // Disable tooltips when hovering a tab
    ImGuiTabBarFlags_DrawSelectedOverline           = 1 << 6,   // Draw selected overline markers over selected tab

    // Fitting/Resize policy
    ImGuiTabBarFlags_FittingPolicyMixed             = 1 << 7,   // Shrink down tabs when they don't fit, until width is style.TabMinWidthShrink, then enable scrolling. Setting TabMinWidthShrink to FLT_MAX makes this behave like ImGuiTabBarFlags_FittingPolicyScroll.
    ImGuiTabBarFlags_FittingPolicyShrink            = 1 << 8,   // Shrink down tabs when they don't fit
    ImGuiTabBarFlags_FittingPolicyScroll            = 1 << 9,   // Enable scrolling buttons when tabs don't fit
    ImGuiTabBarFlags_FittingPolicyMask_             = ImGuiTabBarFlags_FittingPolicyMixed | ImGuiTabBarFlags_FittingPolicyShrink | ImGuiTabBarFlags_FittingPolicyScroll,
    ImGuiTabBarFlags_FittingPolicyDefault_          = ImGuiTabBarFlags_FittingPolicyMixed,

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiTabBarFlags_FittingPolicyResizeDown        = ImGuiTabBarFlags_FittingPolicyShrink, // Renamed in 1.92.2
#endif
};

enum ImGuiTabItemFlags_
{
    ImGuiTabItemFlags_None                          = 0,
    ImGuiTabItemFlags_UnsavedDocument               = 1 << 0,   // Display a dot next to the title + set ImGuiTabItemFlags_NoAssumedClosure.
    ImGuiTabItemFlags_SetSelected                   = 1 << 1,   // Trigger flag to programmatically make the tab selected when calling BeginTabItem()
    ImGuiTabItemFlags_NoCloseWithMiddleMouseButton  = 1 << 2,   // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You may handle this behavior manually on user's side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.
    ImGuiTabItemFlags_NoPushId                      = 1 << 3,   // Don't call PushID()/PopID() on BeginTabItem()/EndTabItem()
    ImGuiTabItemFlags_NoTooltip                     = 1 << 4,   // Disable tooltip for the given tab
    ImGuiTabItemFlags_NoReorder                     = 1 << 5,   // Disable reordering this tab or having another tab cross over this tab
    ImGuiTabItemFlags_Leading                       = 1 << 6,   // Enforce the tab position to the left of the tab bar (after the tab list popup button)
    ImGuiTabItemFlags_Trailing                      = 1 << 7,   // Enforce the tab position to the right of the tab bar (before the scrolling buttons)
    ImGuiTabItemFlags_NoAssumedClosure              = 1 << 8,   // Tab is selected when trying to close + closure is not immediately assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
};

enum ImGuiFocusedFlags_
{
    ImGuiFocusedFlags_None                          = 0,
    ImGuiFocusedFlags_ChildWindows                  = 1 << 0,   // Return true if any children of the window is focused
    ImGuiFocusedFlags_RootWindow                    = 1 << 1,   // Test from root window (top most parent of the current hierarchy)
    ImGuiFocusedFlags_AnyWindow                     = 1 << 2,   // Return true if any window is focused. Important: If you are trying to tell how to dispatch your low-level inputs, do NOT use this. Use 'io.WantCaptureMouse' instead! Please read the FAQ!
    ImGuiFocusedFlags_NoPopupHierarchy              = 1 << 3,   // Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
    //ImGuiFocusedFlags_DockHierarchy               = 1 << 4,   // Consider docking hierarchy (treat dockspace host as parent of docked window) (when used with _ChildWindows or _RootWindow)
    ImGuiFocusedFlags_RootAndChildWindows           = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows,
};

enum ImGuiHoveredFlags_
{
    ImGuiHoveredFlags_None                          = 0,        // Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
    ImGuiHoveredFlags_ChildWindows                  = 1 << 0,   // IsWindowHovered() only: Return true if any children of the window is hovered
    ImGuiHoveredFlags_RootWindow                    = 1 << 1,   // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
    ImGuiHoveredFlags_AnyWindow                     = 1 << 2,   // IsWindowHovered() only: Return true if any window is hovered
    ImGuiHoveredFlags_NoPopupHierarchy              = 1 << 3,   // IsWindowHovered() only: Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
    //ImGuiHoveredFlags_DockHierarchy               = 1 << 4,   // IsWindowHovered() only: Consider docking hierarchy (treat dockspace host as parent of docked window) (when used with _ChildWindows or _RootWindow)
    ImGuiHoveredFlags_AllowWhenBlockedByPopup       = 1 << 5,   // Return true even if a popup window is normally blocking access to this item/window
    //ImGuiHoveredFlags_AllowWhenBlockedByModal     = 1 << 6,   // Return true even if a modal popup window is normally blocking access to this item/window. FIXME-TODO: Unavailable yet.
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem  = 1 << 7,   // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
    ImGuiHoveredFlags_AllowWhenOverlappedByItem     = 1 << 8,   // IsItemHovered() only: Return true even if the item uses AllowOverlap mode and is overlapped by another hoverable item.
    ImGuiHoveredFlags_AllowWhenOverlappedByWindow   = 1 << 9,   // IsItemHovered() only: Return true even if the position is obstructed or overlapped by another window.
    ImGuiHoveredFlags_AllowWhenDisabled             = 1 << 10,  // IsItemHovered() only: Return true even if the item is disabled
    ImGuiHoveredFlags_NoNavOverride                 = 1 << 11,  // IsItemHovered() only: Disable using keyboard/gamepad navigation state when active, always query mouse
    ImGuiHoveredFlags_AllowWhenOverlapped           = ImGuiHoveredFlags_AllowWhenOverlappedByItem | ImGuiHoveredFlags_AllowWhenOverlappedByWindow,
    ImGuiHoveredFlags_RectOnly                      = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
    ImGuiHoveredFlags_RootAndChildWindows           = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows,

    // Tooltips mode
    // - typically used in IsItemHovered() + SetTooltip() sequence.
    // - this is a shortcut to pull flags from 'style.HoverFlagsForTooltipMouse' or 'style.HoverFlagsForTooltipNav' where you can reconfigure desired behavior.
    //   e.g. 'HoverFlagsForTooltipMouse' defaults to 'ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_AllowWhenDisabled'.
    // - for frequently actioned or hovered items providing a tooltip, you want may to use ImGuiHoveredFlags_ForTooltip (stationary + delay) so the tooltip doesn't show too often.
    // - for items which main purpose is to be hovered, or items with low affordance, or in less consistent apps, prefer no delay or shorter delay.
    ImGuiHoveredFlags_ForTooltip                    = 1 << 12,  // Shortcut for standard flags when using IsItemHovered() + SetTooltip() sequence.

    // (Advanced) Mouse Hovering delays.
    // - generally you can use ImGuiHoveredFlags_ForTooltip to use application-standardized flags.
    // - use those if you need specific overrides.
    ImGuiHoveredFlags_Stationary                    = 1 << 13,  // Require mouse to be stationary for style.HoverStationaryDelay (~0.15 sec) _at least one time_. After this, can move on same item/window. Using the stationary test tends to reduces the need for a long delay.
    ImGuiHoveredFlags_DelayNone                     = 1 << 14,  // IsItemHovered() only: Return true immediately (default). As this is the default you generally ignore this.
    ImGuiHoveredFlags_DelayShort                    = 1 << 15,  // IsItemHovered() only: Return true after style.HoverDelayShort elapsed (~0.15 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
    ImGuiHoveredFlags_DelayNormal                   = 1 << 16,  // IsItemHovered() only: Return true after style.HoverDelayNormal elapsed (~0.40 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
    ImGuiHoveredFlags_NoSharedDelay                 = 1 << 17,  // IsItemHovered() only: Disable shared delay system where moving from one item to the next keeps the previous timer for a short time (standard for tooltips with long delays)
};

enum ImGuiDragDropFlags_
{
    ImGuiDragDropFlags_None                         = 0,
    // BeginDragDropSource() flags
    ImGuiDragDropFlags_SourceNoPreviewTooltip       = 1 << 0,   // Disable preview tooltip. By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disables this behavior.
    ImGuiDragDropFlags_SourceNoDisableHover         = 1 << 1,   // By default, when dragging we clear data so that IsItemHovered() will return false, to avoid subsequent user code submitting tooltips. This flag disables this behavior so you can still call IsItemHovered() on the source item.
    ImGuiDragDropFlags_SourceNoHoldToOpenOthers     = 1 << 2,   // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
    ImGuiDragDropFlags_SourceAllowNullID            = 1 << 3,   // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is extremely unusual within the dear imgui ecosystem and so we made it explicit.
    ImGuiDragDropFlags_SourceExtern                 = 1 << 4,   // External source (from outside of dear imgui), won't attempt to read current item/window info. Will always return true. Only one Extern source can be active simultaneously.
    ImGuiDragDropFlags_PayloadAutoExpire            = 1 << 5,   // Automatically expire the payload if the source cease to be submitted (otherwise payloads are persisting while being dragged)
    ImGuiDragDropFlags_PayloadNoCrossContext        = 1 << 6,   // Hint to specify that the payload may not be copied outside current dear imgui context.
    ImGuiDragDropFlags_PayloadNoCrossProcess        = 1 << 7,   // Hint to specify that the payload may not be copied outside current process.
    // AcceptDragDropPayload() flags
    ImGuiDragDropFlags_AcceptBeforeDelivery         = 1 << 10,  // AcceptDragDropPayload() will returns true even before the mouse button is released. You can then call IsDelivery() to test if the payload needs to be delivered.
    ImGuiDragDropFlags_AcceptNoDrawDefaultRect      = 1 << 11,  // Do not draw the default highlight rectangle when hovering over target.
    ImGuiDragDropFlags_AcceptNoPreviewTooltip       = 1 << 12,  // Request hiding the BeginDragDropSource tooltip from the BeginDragDropTarget site.
    ImGuiDragDropFlags_AcceptDrawAsHovered          = 1 << 13,  // Accepting item will render as if hovered. Useful for e.g. a Button() used as a drop target.
    ImGuiDragDropFlags_AcceptPeekOnly               = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect, // For peeking ahead and inspecting the payload before delivery.

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    //ImGuiDragDropFlags_SourceAutoExpirePayload = ImGuiDragDropFlags_PayloadAutoExpire, // Renamed in 1.90.9
#endif
};

enum ImGuiConfigFlags_
{
    ImGuiConfigFlags_None                   = 0,
    ImGuiConfigFlags_NavEnableKeyboard      = 1 << 0,   // Master keyboard navigation enable flag. Enable full Tabbing + directional arrows + Space/Enter to activate. Note: some features such as basic Tabbing and CtrL+Tab are enabled by regardless of this flag (and may be disabled via other means, see #4828, #9218).
    ImGuiConfigFlags_NavEnableGamepad       = 1 << 1,   // Master gamepad navigation enable flag. Backend also needs to set ImGuiBackendFlags_HasGamepad.
    ImGuiConfigFlags_NoMouse                = 1 << 4,   // Instruct dear imgui to disable mouse inputs and interactions.
    ImGuiConfigFlags_NoMouseCursorChange    = 1 << 5,   // Instruct backend to not alter mouse cursor shape and visibility. Use if the backend cursor changes are interfering with yours and you don't want to use SetMouseCursor() to change mouse cursor. You may want to honor requests from imgui by reading GetMouseCursor() yourself instead.
    ImGuiConfigFlags_NoKeyboard             = 1 << 6,   // Instruct dear imgui to disable keyboard inputs and interactions. This is done by ignoring keyboard events and clearing existing states.

    // [Unused] User storage (to allow your backend/engine to communicate to code that may be shared between multiple projects. Those flags are NOT used by core Dear ImGui)
    ImGuiConfigFlags_IsSRGB                 = 1 << 20,  // Application is SRGB-aware.
    ImGuiConfigFlags_IsTouchScreen          = 1 << 21,  // Application is using a touch screen instead of a mouse.
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiConfigFlags_NavEnableSetMousePos   = 1 << 2,   // [moved/renamed in 1.91.4] -> use bool io.ConfigNavMoveSetMousePos
    ImGuiConfigFlags_NavNoCaptureKeyboard   = 1 << 3,   // [moved/renamed in 1.91.4] -> use bool io.ConfigNavCaptureKeyboard
#endif
};

enum ImGuiBackendFlags_
{
    ImGuiBackendFlags_None                  = 0,
    ImGuiBackendFlags_HasGamepad            = 1 << 0,   // Backend Platform supports gamepad and currently has one connected.
    ImGuiBackendFlags_HasMouseCursors       = 1 << 1,   // Backend Platform supports honoring GetMouseCursor() value to change the OS cursor shape.
    ImGuiBackendFlags_HasSetMousePos        = 1 << 2,   // Backend Platform supports io.WantSetMousePos requests to reposition the OS mouse position (only used if io.ConfigNavMoveSetMousePos is set).
    ImGuiBackendFlags_RendererHasVtxOffset  = 1 << 3,   // Backend Renderer supports ImDrawCmd::VtxOffset. This enables output of large meshes (64K+ vertices) while still using 16-bit indices.
    ImGuiBackendFlags_RendererHasTextures   = 1 << 4,   // Backend Renderer supports ImTextureData requests to create/update/destroy textures. This enables incremental texture updates and texture reloads. See https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md for instructions on how to upgrade your custom backend.
};

enum ImGuiColorEditFlags_
{
    ImGuiColorEditFlags_None            = 0,
    ImGuiColorEditFlags_NoAlpha         = 1 << 1,   //              // ColorEdit, ColorPicker, ColorButton: ignore Alpha component (will only read 3 components from the input pointer).
    ImGuiColorEditFlags_NoPicker        = 1 << 2,   //              // ColorEdit: disable picker when clicking on color square.
    ImGuiColorEditFlags_NoOptions       = 1 << 3,   //              // ColorEdit: disable toggling options menu when right-clicking on inputs/small preview.
    ImGuiColorEditFlags_NoSmallPreview  = 1 << 4,   //              // ColorEdit, ColorPicker: disable color square preview next to the inputs. (e.g. to show only the inputs)
    ImGuiColorEditFlags_NoInputs        = 1 << 5,   //              // ColorEdit, ColorPicker: disable inputs sliders/text widgets (e.g. to show only the small preview color square).
    ImGuiColorEditFlags_NoTooltip       = 1 << 6,   //              // ColorEdit, ColorPicker, ColorButton: disable tooltip when hovering the preview.
    ImGuiColorEditFlags_NoLabel         = 1 << 7,   //              // ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).
    ImGuiColorEditFlags_NoSidePreview   = 1 << 8,   //              // ColorPicker: disable bigger color preview on right side of the picker, use small color square preview instead.
    ImGuiColorEditFlags_NoDragDrop      = 1 << 9,   //              // ColorEdit: disable drag and drop target/source. ColorButton: disable drag and drop source.
    ImGuiColorEditFlags_NoBorder        = 1 << 10,  //              // ColorButton: disable border (which is enforced by default)
    ImGuiColorEditFlags_NoColorMarkers  = 1 << 11,  //              // ColorEdit: disable rendering R/G/B/A color marker. May also be disabled globally by setting style.ColorMarkerSize = 0.

    // Alpha preview
    // - Prior to 1.91.8 (2025/01/21): alpha was made opaque in the preview by default using old name ImGuiColorEditFlags_AlphaPreview.
    // - We now display the preview as transparent by default. You can use ImGuiColorEditFlags_AlphaOpaque to use old behavior.
    // - The new flags may be combined better and allow finer controls.
    ImGuiColorEditFlags_AlphaOpaque     = 1 << 12,  //              // ColorEdit, ColorPicker, ColorButton: disable alpha in the preview,. Contrary to _NoAlpha it may still be edited when calling ColorEdit4()/ColorPicker4(). For ColorButton() this does the same as _NoAlpha.
    ImGuiColorEditFlags_AlphaNoBg       = 1 << 13,  //              // ColorEdit, ColorPicker, ColorButton: disable rendering a checkerboard background behind transparent color.
    ImGuiColorEditFlags_AlphaPreviewHalf= 1 << 14,  //              // ColorEdit, ColorPicker, ColorButton: display half opaque / half transparent preview.

    // User Options (right-click on widget to change some of them)
    // Current settings are stored in style.ColorEditFlags.
    ImGuiColorEditFlags_AlphaBar        = 1 << 18,  //              // ColorEdit, ColorPicker: show vertical alpha bar/gradient in picker.
    ImGuiColorEditFlags_HDR             = 1 << 19,  //              // (WIP) ColorEdit: Currently only disable 0.0f..1.0f limits in RGBA edition (note: you probably want to use ImGuiColorEditFlags_Float flag as well).
    ImGuiColorEditFlags_DisplayRGB      = 1 << 20,  // [Display]    // ColorEdit: override _display_ type among RGB/HSV/Hex. ColorPicker: select any combination using one or more of RGB/HSV/Hex.
    ImGuiColorEditFlags_DisplayHSV      = 1 << 21,  // [Display]    // "
    ImGuiColorEditFlags_DisplayHex      = 1 << 22,  // [Display]    // "
    ImGuiColorEditFlags_Uint8           = 1 << 23,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0..255.
    ImGuiColorEditFlags_Float           = 1 << 24,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers. No round-trip of value via integers.
    ImGuiColorEditFlags_PickerHueBar    = 1 << 25,  // [Picker]     // ColorPicker: bar for Hue, rectangle for Sat/Value.
    ImGuiColorEditFlags_PickerHueWheel  = 1 << 26,  // [Picker]     // ColorPicker: wheel for Hue, triangle for Sat/Value.
    ImGuiColorEditFlags_PickerNoRotate  = 1 << 27,  // [Picker]     // ColorPicker: disable rotating Sat/Value triangle. Best set in io.ConfigColorEditFlags once.
    ImGuiColorEditFlags_InputRGB        = 1 << 28,  // [Input]      // ColorEdit, ColorPicker: input and output data in RGB format.
    ImGuiColorEditFlags_InputHSV        = 1 << 29,  // [Input]      // ColorEdit, ColorPicker: input and output data in HSV format.

    // Defaults Options copied to io.ConfigColorEditFlags during initialization.
    // The intent is that you probably don't want to override them in most of your calls.
    // Let the user choose via the option menu and/or modify io.ConfigColorEditFlags directly during startup if you want.
    ImGuiColorEditFlags_DefaultOptions_ = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar,

    // [Internal] Masks
    ImGuiColorEditFlags_AlphaMask_      = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaOpaque | ImGuiColorEditFlags_AlphaNoBg | ImGuiColorEditFlags_AlphaPreviewHalf,
    ImGuiColorEditFlags_DisplayMask_    = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex,
    ImGuiColorEditFlags_DataTypeMask_   = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float,
    ImGuiColorEditFlags_PickerMask_     = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_PickerHueBar,
    ImGuiColorEditFlags_InputMask_      = ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_InputHSV,

    // Obsolete names
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiColorEditFlags_AlphaPreview = 0, // Removed in 1.91.8. This is the default now. Will display a checkerboard unless ImGuiColorEditFlags_AlphaNoBg is set.
    //ImGuiColorEditFlags_RGB = ImGuiColorEditFlags_DisplayRGB, ImGuiColorEditFlags_HSV = ImGuiColorEditFlags_DisplayHSV, ImGuiColorEditFlags_HEX = ImGuiColorEditFlags_DisplayHex  // [renamed in 1.69]
#endif
};

enum ImGuiSliderFlags_
{
    ImGuiSliderFlags_None               = 0,
    ImGuiSliderFlags_Logarithmic        = 1 << 5,       // Make the widget logarithmic (linear otherwise). Consider using ImGuiSliderFlags_NoRoundToFormat with this if using a format-string with small amount of digits.
    ImGuiSliderFlags_NoRoundToFormat    = 1 << 6,       // Disable rounding underlying value to match precision of the display format string (e.g. %.3f values are rounded to those 3 digits).
    ImGuiSliderFlags_NoInput            = 1 << 7,       // Disable Ctrl+Click or Enter key allowing to input text directly into the widget.
    ImGuiSliderFlags_WrapAround         = 1 << 8,       // Enable wrapping around from max to min and from min to max. Only supported by DragXXX() functions for now.
    ImGuiSliderFlags_ClampOnInput       = 1 << 9,       // Clamp value to min/max bounds when input manually with Ctrl+Click. By default Ctrl+Click allows going out of bounds.
    ImGuiSliderFlags_ClampZeroRange     = 1 << 10,      // Clamp even if min==max==0.0f. Otherwise due to legacy reason DragXXX functions don't clamp with those values. When your clamping limits are dynamic you almost always want to use it.
    ImGuiSliderFlags_NoSpeedTweaks      = 1 << 11,      // Disable keyboard modifiers altering tweak speed. Useful if you want to alter tweak speed yourself based on your own logic.
    ImGuiSliderFlags_ColorMarkers       = 1 << 12,      // DragScalarN(), SliderScalarN(): Draw R/G/B/A color markers on each component.
    ImGuiSliderFlags_AlwaysClamp        = ImGuiSliderFlags_ClampOnInput | ImGuiSliderFlags_ClampZeroRange,
    //ImGuiSliderFlags_LiveEditOnInput  = 1 << 13,      // Shortcut to enable LiveEdit for this field.
    //ImGuiSliderFlags_NoLiveEditOnInput= 1 << 14,      // Shortcut to disable LiveEdit for this field.
    ImGuiSliderFlags_InvalidMask_       = 0x7000000F,   // [Internal] We treat using those bits as being potentially a 'float power' argument from legacy API (obsoleted 2020-08) that has got miscast to this enum, and will trigger an assert if needed.
};

enum ImGuiTableFlags_
{
    // Features
    ImGuiTableFlags_None                       = 0,
    ImGuiTableFlags_Resizable                  = 1 << 0,   // Enable resizing columns.
    ImGuiTableFlags_Reorderable                = 1 << 1,   // Enable reordering columns in header row. (Need calling TableSetupColumn() + TableHeadersRow() to display headers, or using ImGuiTableFlags_ContextMenuInBody to access context-menu without headers).
    ImGuiTableFlags_Hideable                   = 1 << 2,   // Enable hiding/disabling columns in context menu.
    ImGuiTableFlags_Sortable                   = 1 << 3,   // Enable sorting. Call TableGetSortSpecs() to obtain sort specs. Also see ImGuiTableFlags_SortMulti and ImGuiTableFlags_SortTristate.
    ImGuiTableFlags_NoSavedSettings            = 1 << 4,   // Disable persisting columns order, width, visibility and sort settings in the .ini file.
    ImGuiTableFlags_ContextMenuInBody          = 1 << 5,   // Right-click on columns body/contents will also display table context menu. By default it is available in TableHeadersRow().
    // Decorations
    ImGuiTableFlags_RowBg                      = 1 << 6,   // Set each RowBg color with ImGuiCol_TableRowBg or ImGuiCol_TableRowBgAlt (equivalent of calling TableSetBgColor with ImGuiTableBgFlags_RowBg0 on each row manually)
    ImGuiTableFlags_BordersInnerH              = 1 << 7,   // Draw horizontal borders between rows.
    ImGuiTableFlags_BordersOuterH              = 1 << 8,   // Draw horizontal borders at the top and bottom.
    ImGuiTableFlags_BordersInnerV              = 1 << 9,   // Draw vertical borders between columns.
    ImGuiTableFlags_BordersOuterV              = 1 << 10,  // Draw vertical borders on the left and right sides.
    ImGuiTableFlags_BordersH                   = ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersOuterH, // Draw horizontal borders.
    ImGuiTableFlags_BordersV                   = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV, // Draw vertical borders.
    ImGuiTableFlags_BordersInner               = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersInnerH, // Draw inner borders.
    ImGuiTableFlags_BordersOuter               = ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH, // Draw outer borders.
    ImGuiTableFlags_Borders                    = ImGuiTableFlags_BordersInner | ImGuiTableFlags_BordersOuter,   // Draw all borders.
    ImGuiTableFlags_NoBordersInBody            = 1 << 11,  // [ALPHA] Disable vertical borders in columns Body (borders will always appear in Headers). -> May move to style
    ImGuiTableFlags_NoBordersInBodyUntilResize = 1 << 12,  // [ALPHA] Disable vertical borders in columns Body until hovered for resize (borders will always appear in Headers). -> May move to style
    // Sizing Policy (read above for defaults)
    ImGuiTableFlags_SizingFixedFit             = 1 << 13,  // Columns default to _WidthFixed or _WidthAuto (if resizable or not resizable), matching contents width.
    ImGuiTableFlags_SizingFixedSame            = 2 << 13,  // Columns default to _WidthFixed or _WidthAuto (if resizable or not resizable), matching the maximum contents width of all columns. Implicitly enable ImGuiTableFlags_NoKeepColumnsVisible.
    ImGuiTableFlags_SizingStretchProp          = 3 << 13,  // Columns default to _WidthStretch with default weights proportional to each columns contents widths.
    ImGuiTableFlags_SizingStretchSame          = 4 << 13,  // Columns default to _WidthStretch with default weights all equal, unless overridden by TableSetupColumn().
    // Sizing Extra Options
    ImGuiTableFlags_NoHostExtendX              = 1 << 16,  // Make outer width auto-fit to columns, overriding outer_size.x value. Only available when ScrollX/ScrollY are disabled and Stretch columns are not used.
    ImGuiTableFlags_NoHostExtendY              = 1 << 17,  // Make outer height stop exactly at outer_size.y (prevent auto-extending table past the limit). Only available when ScrollX/ScrollY are disabled. Data below the limit will be clipped and not visible.
    ImGuiTableFlags_NoKeepColumnsVisible       = 1 << 18,  // Disable keeping column always minimally visible when ScrollX is off and table gets too small. Not recommended if columns are resizable.
    ImGuiTableFlags_PreciseWidths              = 1 << 19,  // Disable distributing remainder width to stretched columns (width allocation on a 100-wide table with 3 columns: Without this flag: 33,33,34. With this flag: 33,33,33). With larger number of columns, resizing will appear to be less smooth.
    // Clipping
    ImGuiTableFlags_NoClip                     = 1 << 20,  // Disable clipping rectangle for every individual columns (reduce draw command count, items will be able to overflow into other columns). Generally incompatible with TableSetupScrollFreeze().
    // Padding
    ImGuiTableFlags_PadOuterX                  = 1 << 21,  // Default if BordersOuterV is on. Enable outermost padding. Generally desirable if you have headers.
    ImGuiTableFlags_NoPadOuterX                = 1 << 22,  // Default if BordersOuterV is off. Disable outermost padding.
    ImGuiTableFlags_NoPadInnerX                = 1 << 23,  // Disable inner padding between columns (double inner padding if BordersOuterV is on, single inner padding if BordersOuterV is off).
    // Scrolling
    ImGuiTableFlags_ScrollX                    = 1 << 24,  // Enable horizontal scrolling. Require 'outer_size' parameter of BeginTable() to specify the container size. Changes default sizing policy. Because this creates a child window, ScrollY is currently generally recommended when using ScrollX.
    ImGuiTableFlags_ScrollY                    = 1 << 25,  // Enable vertical scrolling. Require 'outer_size' parameter of BeginTable() to specify the container size.
    // Sorting
    ImGuiTableFlags_SortMulti                  = 1 << 26,  // Hold shift when clicking headers to sort on multiple column. TableGetSortSpecs() may return specs where (SpecsCount > 1).
    ImGuiTableFlags_SortTristate               = 1 << 27,  // Allow no sorting, disable default sorting. TableGetSortSpecs() may return specs where (SpecsCount == 0).
    // Miscellaneous
    ImGuiTableFlags_HighlightHoveredColumn     = 1 << 28,  // Highlight column headers when hovered (may evolve into a fuller highlight)

    // [Internal] Combinations and masks
    ImGuiTableFlags_SizingMask_                = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_SizingFixedSame | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_SizingStretchSame,
};

enum ImGuiTableColumnFlags_
{
    // Input configuration flags
    ImGuiTableColumnFlags_None                  = 0,
    ImGuiTableColumnFlags_Disabled              = 1 << 0,   // Overriding/master disable flag: hide column, won't show in context menu (unlike calling TableSetColumnEnabled() which manipulates the user accessible state)
    ImGuiTableColumnFlags_DefaultHide           = 1 << 1,   // Default as a hidden/disabled column.
    ImGuiTableColumnFlags_DefaultSort           = 1 << 2,   // Default as a sorting column.
    ImGuiTableColumnFlags_WidthStretch          = 1 << 3,   // Column will stretch. Preferable with horizontal scrolling disabled (default if table sizing policy is _SizingStretchSame or _SizingStretchProp).
    ImGuiTableColumnFlags_WidthFixed            = 1 << 4,   // Column will not stretch. Preferable with horizontal scrolling enabled (default if table sizing policy is _SizingFixedFit and table is resizable).
    ImGuiTableColumnFlags_NoResize              = 1 << 5,   // Disable manual resizing.
    ImGuiTableColumnFlags_NoReorder             = 1 << 6,   // Disable manual reordering this column, this will also prevent other columns from crossing over this column.
    ImGuiTableColumnFlags_NoHide                = 1 << 7,   // Disable ability to hide/disable this column.
    ImGuiTableColumnFlags_NoClip                = 1 << 8,   // Disable clipping for this column (all NoClip columns will render in a same draw command).
    ImGuiTableColumnFlags_NoSort                = 1 << 9,   // Disable ability to sort on this field (even if ImGuiTableFlags_Sortable is set on the table).
    ImGuiTableColumnFlags_NoSortAscending       = 1 << 10,  // Disable ability to sort in the ascending direction.
    ImGuiTableColumnFlags_NoSortDescending      = 1 << 11,  // Disable ability to sort in the descending direction.
    ImGuiTableColumnFlags_NoHeaderLabel         = 1 << 12,  // TableHeadersRow() will submit an empty label for this column. Convenient for some small columns. Name will still appear in context menu or in angled headers. You may append into this cell by calling TableSetColumnIndex() right after the TableHeadersRow() call.
    ImGuiTableColumnFlags_NoHeaderWidth         = 1 << 13,  // Disable header text width contribution to automatic column width.
    ImGuiTableColumnFlags_PreferSortAscending   = 1 << 14,  // Make the initial sort direction Ascending when first sorting on this column (default).
    ImGuiTableColumnFlags_PreferSortDescending  = 1 << 15,  // Make the initial sort direction Descending when first sorting on this column.
    ImGuiTableColumnFlags_IndentEnable          = 1 << 16,  // Use current Indent value when entering cell (default for column 0).
    ImGuiTableColumnFlags_IndentDisable         = 1 << 17,  // Ignore current Indent value when entering cell (default for columns > 0). Indentation changes _within_ the cell will still be honored.
    ImGuiTableColumnFlags_AngledHeader          = 1 << 18,  // TableHeadersRow() will submit an angled header row for this column. Note this will add an extra row.

    // Output status flags, read-only via TableGetColumnFlags()
    ImGuiTableColumnFlags_IsEnabled             = 1 << 24,  // Status: is enabled == not hidden by user/api (referred to as "Hide" in _DefaultHide and _NoHide) flags.
    ImGuiTableColumnFlags_IsVisible             = 1 << 25,  // Status: is visible == is enabled AND not clipped by scrolling.
    ImGuiTableColumnFlags_IsSorted              = 1 << 26,  // Status: is currently part of the sort specs
    ImGuiTableColumnFlags_IsHovered             = 1 << 27,  // Status: is hovered by mouse

    // [Internal] Combinations and masks
    ImGuiTableColumnFlags_WidthMask_            = ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_WidthFixed,
    ImGuiTableColumnFlags_IndentMask_           = ImGuiTableColumnFlags_IndentEnable | ImGuiTableColumnFlags_IndentDisable,
    ImGuiTableColumnFlags_StatusMask_           = ImGuiTableColumnFlags_IsEnabled | ImGuiTableColumnFlags_IsVisible | ImGuiTableColumnFlags_IsSorted | ImGuiTableColumnFlags_IsHovered,
    ImGuiTableColumnFlags_NoDirectResize_       = 1 << 30,  // [Internal] Disable user resizing this column directly (it may however we resized indirectly from its left edge)
};


typedef int ImGuiCol;             // -> enum ImGuiCol_
typedef int ImGuiStyleVar;        // -> enum ImGuiStyleVar_
typedef int ImGuiInputFlags;      // -> enum ImGuiInputFlags_
typedef int ImGuiMouseCursor;     // -> enum ImGuiMouseCursor_

enum ImGuiCol_
{
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg,              // Background of normal windows
    ImGuiCol_ChildBg,               // Background of child windows
    ImGuiCol_PopupBg,               // Background of popups, menus, tooltips windows
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg,               // Title bar
    ImGuiCol_TitleBgActive,         // Title bar when focused
    ImGuiCol_TitleBgCollapsed,      // Title bar when collapsed
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrab,
    ImGuiCol_ScrollbarGrabHovered,
    ImGuiCol_ScrollbarGrabActive,
    ImGuiCol_CheckMark,             // Checkbox tick and RadioButton circle
    ImGuiCol_CheckboxSelectedBg,    // Checkbox background when Selected, otherwise use FrameBg
    ImGuiCol_SliderGrab,
    ImGuiCol_SliderGrabActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header,                // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Separator,
    ImGuiCol_SeparatorHovered,
    ImGuiCol_SeparatorActive,
    ImGuiCol_ResizeGrip,            // Resize grip in lower-right and lower-left corners of windows.
    ImGuiCol_ResizeGripHovered,
    ImGuiCol_ResizeGripActive,
    ImGuiCol_InputTextCursor,       // InputText cursor/caret
    ImGuiCol_TabHovered,            // Tab background, when hovered
    ImGuiCol_Tab,                   // Tab background, when tab-bar is focused & tab is unselected
    ImGuiCol_TabSelected,           // Tab background, when tab-bar is focused & tab is selected
    ImGuiCol_TabSelectedOverline,   // Tab horizontal overline, when tab-bar is focused & tab is selected
    ImGuiCol_TabDimmed,             // Tab background, when tab-bar is unfocused & tab is unselected
    ImGuiCol_TabDimmedSelected,     // Tab background, when tab-bar is unfocused & tab is selected
    ImGuiCol_TabDimmedSelectedOverline,//..horizontal overline, when tab-bar is unfocused & tab is selected
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TableHeaderBg,         // Table header background
    ImGuiCol_TableBorderStrong,     // Table outer and header borders (prefer using Alpha=1.0 here)
    ImGuiCol_TableBorderLight,      // Table inner borders (prefer using Alpha=1.0 here)
    ImGuiCol_TableRowBg,            // Table row background (even rows)
    ImGuiCol_TableRowBgAlt,         // Table row background (odd rows)
    ImGuiCol_TextLink,              // Hyperlink color
    ImGuiCol_TextSelectedBg,        // Selected text inside an InputText
    ImGuiCol_TreeLines,             // Tree node hierarchy outlines when using ImGuiTreeNodeFlags_DrawLines
    ImGuiCol_DragDropTarget,        // Rectangle border highlighting a drop target
    ImGuiCol_DragDropTargetBg,      // Rectangle background highlighting a drop target
    ImGuiCol_UnsavedMarker,         // Unsaved Document marker (in window title and tabs)
    ImGuiCol_NavCursor,             // Color of keyboard/gamepad navigation cursor/rectangle, when visible
    ImGuiCol_NavWindowingHighlight, // Highlight window when using Ctrl+Tab
    ImGuiCol_NavWindowingDimBg,     // Darken/colorize entire screen behind the Ctrl+Tab window list, when active
    ImGuiCol_ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
    ImGuiCol_COUNT,

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGuiCol_TabActive = ImGuiCol_TabSelected,                  // [renamed in 1.90.9]
    ImGuiCol_TabUnfocused = ImGuiCol_TabDimmed,                 // [renamed in 1.90.9]
    ImGuiCol_TabUnfocusedActive = ImGuiCol_TabDimmedSelected,   // [renamed in 1.90.9]
    ImGuiCol_NavHighlight = ImGuiCol_NavCursor,                 // [renamed in 1.91.4]
#endif
};

enum ImGuiStyleVar_
{
    // Enum name -------------------------- // Member in ImGuiStyle structure (see ImGuiStyle for descriptions)
    ImGuiStyleVar_Alpha,                    // float     Alpha
    ImGuiStyleVar_DisabledAlpha,            // float     DisabledAlpha
    ImGuiStyleVar_WindowPadding,            // ImVec2    WindowPadding
    ImGuiStyleVar_WindowRounding,           // float     WindowRounding
    ImGuiStyleVar_WindowBorderSize,         // float     WindowBorderSize
    ImGuiStyleVar_WindowMinSize,            // ImVec2    WindowMinSize
    ImGuiStyleVar_WindowTitleAlign,         // ImVec2    WindowTitleAlign
    ImGuiStyleVar_ChildRounding,            // float     ChildRounding
    ImGuiStyleVar_ChildBorderSize,          // float     ChildBorderSize
    ImGuiStyleVar_PopupRounding,            // float     PopupRounding
    ImGuiStyleVar_PopupBorderSize,          // float     PopupBorderSize
    ImGuiStyleVar_FramePadding,             // ImVec2    FramePadding
    ImGuiStyleVar_FrameRounding,            // float     FrameRounding
    ImGuiStyleVar_FrameBorderSize,          // float     FrameBorderSize
    ImGuiStyleVar_ItemSpacing,              // ImVec2    ItemSpacing
    ImGuiStyleVar_ItemInnerSpacing,         // ImVec2    ItemInnerSpacing
    ImGuiStyleVar_IndentSpacing,            // float     IndentSpacing
    ImGuiStyleVar_CellPadding,              // ImVec2    CellPadding
    ImGuiStyleVar_ScrollbarSize,            // float     ScrollbarSize
    ImGuiStyleVar_ScrollbarRounding,        // float     ScrollbarRounding
    ImGuiStyleVar_ScrollbarPadding,         // float     ScrollbarPadding
    ImGuiStyleVar_GrabMinSize,              // float     GrabMinSize
    ImGuiStyleVar_GrabRounding,             // float     GrabRounding
    ImGuiStyleVar_ImageRounding,            // float     ImageRounding
    ImGuiStyleVar_ImageBorderSize,          // float     ImageBorderSize
    ImGuiStyleVar_TabRounding,              // float     TabRounding
    ImGuiStyleVar_TabBorderSize,            // float     TabBorderSize
    ImGuiStyleVar_TabMinWidthBase,          // float     TabMinWidthBase
    ImGuiStyleVar_TabMinWidthShrink,        // float     TabMinWidthShrink
    ImGuiStyleVar_TabBarBorderSize,         // float     TabBarBorderSize
    ImGuiStyleVar_TabBarOverlineSize,       // float     TabBarOverlineSize
    ImGuiStyleVar_TableAngledHeadersAngle,  // float     TableAngledHeadersAngle
    ImGuiStyleVar_TableAngledHeadersTextAlign,// ImVec2  TableAngledHeadersTextAlign
    ImGuiStyleVar_TreeLinesSize,            // float     TreeLinesSize
    ImGuiStyleVar_TreeLinesRounding,        // float     TreeLinesRounding
    ImGuiStyleVar_MenuItemRounding,         // float     MenuItemRounding
    ImGuiStyleVar_SelectableRounding,       // float     SelectableRounding
    ImGuiStyleVar_DragDropTargetRounding,   // float     DragDropTargetRounding
    ImGuiStyleVar_ButtonTextAlign,          // ImVec2    ButtonTextAlign
    ImGuiStyleVar_SelectableTextAlign,      // ImVec2    SelectableTextAlign
    ImGuiStyleVar_SeparatorSize,            // float     SeparatorSize
    ImGuiStyleVar_SeparatorTextBorderSize,  // float     SeparatorTextBorderSize
    ImGuiStyleVar_SeparatorTextAlign,       // ImVec2    SeparatorTextAlign
    ImGuiStyleVar_SeparatorTextPadding,     // ImVec2    SeparatorTextPadding
    ImGuiStyleVar_COUNT
};

enum ImGuiDir : int
{
    ImGuiDir_None    = -1,
    ImGuiDir_Left    = 0,
    ImGuiDir_Right   = 1,
    ImGuiDir_Up      = 2,
    ImGuiDir_Down    = 3,
    ImGuiDir_COUNT
};

enum ImGuiInputFlags_
{
    ImGuiInputFlags_None                    = 0,
    ImGuiInputFlags_Repeat                  = 1 << 0,   // Enable repeat. Return true on successive repeats. Default for legacy IsKeyPressed(). NOT Default for legacy IsMouseClicked(). MUST BE == 1.

    // Flags for Shortcut(), SetNextItemShortcut()
    // - Routing policies: RouteGlobal+OverActive >> RouteActive or RouteFocused (if owner is active item) >> RouteGlobal+OverFocused >> RouteFocused (if in focused window stack) >> RouteGlobal.
    // - Default policy is RouteFocused. Can select only 1 policy among all available.
    ImGuiInputFlags_RouteActive             = 1 << 10,  // Route to active item only.
    ImGuiInputFlags_RouteFocused            = 1 << 11,  // Route to windows in the focus stack (DEFAULT). Deep-most focused window takes inputs. Active item takes inputs over deep-most focused window.
    ImGuiInputFlags_RouteGlobal             = 1 << 12,  // Global route (unless a focused window or active item registered the route).
    ImGuiInputFlags_RouteAlways             = 1 << 13,  // Do not register route, poll keys directly.
    // - Routing options
    ImGuiInputFlags_RouteOverFocused        = 1 << 14,  // Option: global route: higher priority than focused route (unless active item in focused route).
    ImGuiInputFlags_RouteOverActive         = 1 << 15,  // Option: global route: higher priority than active item. Unlikely you need to use that: will interfere with every active items, e.g. Ctrl+A registered by InputText will be overridden by this. May not be fully honored as user/internal code is likely to always assume they can access keys when active.
    ImGuiInputFlags_RouteUnlessBgFocused    = 1 << 16,  // Option: global route: will not be applied if underlying background/void is focused (== no Dear ImGui windows are focused). Useful for overlay applications.
    ImGuiInputFlags_RouteFromRootWindow     = 1 << 17,  // Option: route evaluated from the point of view of root window rather than current window.

    // Flags for SetNextItemShortcut()
    ImGuiInputFlags_Tooltip                 = 1 << 18,  // Automatically display a tooltip when hovering item [BETA] Unsure of right api (opt-in/opt-out)
};

enum ImGuiMouseCursor_
{
    ImGuiMouseCursor_None = -1,
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput,         // When hovering over InputText, etc.
    ImGuiMouseCursor_ResizeAll,         // (Unused by Dear ImGui functions)
    ImGuiMouseCursor_ResizeNS,          // When hovering over a horizontal border
    ImGuiMouseCursor_ResizeEW,          // When hovering over a vertical border or a column
    ImGuiMouseCursor_ResizeNESW,        // When hovering over the bottom-left corner of a window
    ImGuiMouseCursor_ResizeNWSE,        // When hovering over the bottom-right corner of a window
    ImGuiMouseCursor_Hand,              // (Unused by Dear ImGui functions. Use for e.g. hyperlinks)
    ImGuiMouseCursor_Wait,              // When waiting for something to process/load.
    ImGuiMouseCursor_Progress,          // When waiting for something to process/load, but application is still interactive.
    ImGuiMouseCursor_NotAllowed,        // When hovering something with disallowed interaction. Usually a crossed circle.
    ImGuiMouseCursor_COUNT
};

