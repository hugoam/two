
function theme_menu(parent) {
    var styles = [ two.style_minimal, two.style_vector, two.style_imgui_dark, two.style_blendish_light, two.style_blendish_dark ];
    var names = [ 'Minimal', 'Vector', 'Imgui (Dark)', 'Blendish (Light)', 'Blendish (Dark)' ];

    menu = two.ui.menu(parent, 'Theme').body;
    if(menu)
    {
        for(var i = 0; i < array_size(select); ++i)
        {
            if(two.ui.menu_choice(menu, names[i]).activated())
            {
                parent.ui_window().reset_styles();
                select[i](parent.ui_window());
                parent.ui().reset_styles();
            }
        }
    }
}

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see misc/fonts/README.txt)
function HelpMarker(parent, desc) {
    label = two.ui.label(parent, ' (?)'); // @kludge space just to prevent () image syntax
    //label = two.ui.item(parent, styles().control, ' (?)');
    //label.enable_state(DISABLED);
    if(popup = two.ui.hoverbox(label))
    {
        two.ui.label(popup, desc);
    }
}

// Helper to display basic user controls.
function ShowUserGuide(parent) {
    
    two.ui.bullet(parent, 'Double-click on title bar to collapse window.');
    two.ui.bullet(parent, 'Click and drag on lower right corner to resize window\n(double-click to auto fit window to its contents).');
    two.ui.bullet(parent, 'Click and drag on any empty space to move window.');
    two.ui.bullet(parent, 'TAB/SHIFT+TAB to cycle through keyboard editable fields.');
    two.ui.bullet(parent, 'CTRL+Click on a slider or drag box to input value as text.');
    //if(io.FontAllowUserScaling)
    //    two.ui.bullet(parent, 'CTRL+Mouse Wheel to zoom window contents.');
    two.ui.bullet(parent, 'Mouse Wheel to scroll.');
    two.ui.bullet(parent, 'While editing text:\n');

    indent = two.ui.indent(parent);
    two.ui.bullet(indent, 'Hold SHIFT or use mouse to select text.');
    two.ui.bullet(indent, 'CTRL+Left/Right to word jump.');
    two.ui.bullet(indent, 'CTRL+A or double-click to select all.');
    two.ui.bullet(indent, 'CTRL+X,CTRL+C,CTRL+V to use clipboard.');
    two.ui.bullet(indent, 'CTRL+Z,CTRL+Y to undo/redo.');
    two.ui.bullet(indent, 'ESCAPE to revert.');
    two.ui.bullet(indent, 'You can apply arithmetic operators +,*,/ on numerical values.\nUse +- to subtract.');
}

// [section] Demo Window / ShowDemoWindow()

// Demonstrate most Dear ImGui features (this is big function!)
// You may execute this function to experiment with the UI and understand what it does. You may then search for keywords in the code when you are interested by a specific feature.
function ShowDemoWindow(parent)
{
    // Demonstrate the various window flags. Typically you would just use the default!
    this.no_titlebar = false;
    this.no_scrollbar = false;
    this.no_menu = false;
    this.no_move = false;
    this.no_resize = false;
    this.no_collapse = false;
    this.no_close = false;
    this.no_nav = false;
    this.no_background = false;
    this.no_bring_to_front = false;

    var flags = two.WindowState.None;
    if(!no_titlebar)       flags = flags | two.WindowState.Header);
    if(!no_scrollbar)      flags = flags | two.WindowState.Scrollable);
    if(!no_menu)           flags = flags | two.WindowState.Menu);
    if(!no_move)           flags = flags | two.WindowState.Movable);
    if(!no_resize)         flags = flags | two.WindowState.Sizable);
    //if(no_collapse)      flags |= two.WindowState.NoCollapse;
    //if(no_nav)           flags |= two.WindowState.NoNav;
    //if(no_background)    flags |= two.WindowState.NoBackground;
    //if(no_bring_to_front)flags |= two.WindowState.NoBringToFrontOnFocus;
    if(!no_close)          flags = flags | two.WindowState.Closable);

    // Main body of the Demo window starts here.
    var window = two.ui.window(parent, 'ImGui Demo', flags);

    var scrollsheet = two.ui.scroll_sheet(*window.body);
    body = scrollsheet.body;

    // Most 'big' widgets share a common width settings by default.
    //two.ui.PushItemWidth(two.ui.GetWindowWidth() * 0.65);    // Use 2/3 of the space for widgets and 1/3 for labels (default)
    //two.ui.PushItemWidth(two.ui.GetFontSize() * -12);           // Use fixed width for labels (by passing a negative value), the rest goes to widgets. We choose a width proportional to our font size.

    // Menu Bar
    if(window.menu)
    {
        menubar = window.menu;

        if(menu = two.ui.menu(menubar, 'Menu').body)
        {
            //ShowExampleMenuFile();
        }

        theme_menu(menubar);

        if(menu = two.ui.menu(menubar, 'Examples').body)
        {
            //two.ui.menu_option(menu, 'Main menu bar', '', show_app_main_menu_bar);
            //two.ui.menu_option(menu, 'Console', '', show_app_console);
            //two.ui.menu_option(menu, 'Log', '', show_app_log);
            //two.ui.menu_option(menu, 'Simple layout', '', show_app_layout);
            //two.ui.menu_option(menu, 'Property editor', '', show_app_property_editor);
            //two.ui.menu_option(menu, 'Long text display', '', show_app_long_text);
            //two.ui.menu_option(menu, 'Auto-resizing window', '', show_app_auto_resize);
            //two.ui.menu_option(menu, 'Constrained-resizing window', '', show_app_constrained_resize);
            //two.ui.menu_option(menu, 'Simple overlay', '', show_app_simple_overlay);
            //two.ui.menu_option(menu, 'Manipulating window titles', '', show_app_window_titles);
            //two.ui.menu_option(menu, 'Custom rendering', '', show_app_custorendering);
            //two.ui.menu_option(menu, 'Documents', '', show_app_documents);
        }

        if(help = two.ui.menu(menubar, 'Help').body)
        {
            two.ui.menu_option(help, 'Metrics', '', show_app_metrics);
            two.ui.menu_option(help, 'Style Editor', '', show_app_style_editor);
            two.ui.menu_option(help, 'About Dear ImGui', '', show_app_about);
        }
    }

    //two.ui.labelf(body, 'dear imgui says hello. (%s)', '1.0'); //IMGUI_VERSION);
    //two.ui.Spacing();

    if(help = two.ui.expandbox(body, 'Help').body)
    {
        two.ui.label(help, 'PROGRAMMER GUIDE:');
        two.ui.bullet(help, 'Please see the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!');
        two.ui.bullet(help, 'Please see the comments in imgui.cpp.');
        two.ui.bullet(help, 'Please see the examples/ in application.');
        two.ui.bullet(help, 'Enable io.ConfigFlags |= NavEnableKeyboard for keyboard controls.');
        two.ui.bullet(help, 'Enable io.ConfigFlags |= NavEnableGamepad for gamepad controls.');
        two.ui.separator(help);

        two.ui.label(help, 'USER GUIDE:');
        ShowUserGuide(help);
    }

    if(config = two.ui.expandbox(body, 'Configuration').body)
    {
    }

    if(opts = two.ui.expandbox(body, 'Window options').body)
    {
        row0 = two.ui.row(opts);
        two.ui.field(row0, 'No titlebar', no_titlebar, true);
        two.ui.field(row0, 'No scrollbar', no_scrollbar, true);
        two.ui.field(row0, 'No menu', no_menu, true);

        row1 = two.ui.row(opts);
        two.ui.field(row1, 'No move', no_move, true);
        two.ui.field(row1, 'No resize', no_resize, true);
        two.ui.field(row1, 'No collapse', no_collapse, true);

        row2 = two.ui.row(opts);
        two.ui.field(row2, 'No close', no_close, true);
        two.ui.field(row2, 'No nav', no_nav, true);
        two.ui.field(row2, 'No background', no_background, true);

        row3 = two.ui.row(opts);
        two.ui.field(row3, 'No bring to front', no_bring_to_front, true);
    }

    // All demo contents
    ShowDemoWindowWidgets(body);
    //ShowDemoWindowLayout(body);
    //ShowDemoWindowPopups(body);
    //ShowDemoWindowColumns(body);
    //ShowDemoWindowMisc(body);

    // End of ShowDemoWindow()
    //two.ui.End();
}

static function ShowDemoWindowWidgets(parent)
{
    var body = two.ui.expandbox(parent, 'Widgets').body;
    if(!body)
        return;

    if(var n = two.ui.tree_node(body, 'Basic').body)
    {
        this.clicked = 0;
        var r0 = two.ui.row(n);
        if(two.ui.button(r0, 'Button').activated())
            clicked++;
        if(clicked & 1)
        {
            two.ui.label(r0, 'Thanks for clicking me!');
        }

        this.check = true;
        two.ui.field(n, 'checkbox', check, true);

        this.e = 0;
        var row0 = two.ui.row(n);
        two.ui.radio_button(row0, 'radio a', e, 0);
        two.ui.radio_button(row0, 'radio b', e, 1);
        two.ui.radio_button(row0, 'radio c', e, 2);

        // Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
        var buttons = two.ui.row(n);
        var styles = [];
        for(int i = 0; i < 7; i++)
        {
            styles[i] = new two.Style(); 
            styles[i].skin.background_colour = hsv(i / 7.0, 0.6, 0.6);
            styles[i].decline_skin(HOVERED).background_colour = hsv(i / 7.0, 0.7, 0.7);
            styles[i].decline_skin(ACTIVE).background_colour = hsv(i / 7.0, 0.8, 0.8);

            two.ui.button(buttons, styles[i], 'Click');
        }

        var r1 = two.ui.row(n);
        var label0 = two.ui.label(r1, 'Hover over me');
        if(var popup = two.ui.hoverbox(label0))
        {
            two.ui.text(popup, 'I am a tooltip');
        }

        //two.ui.SameLine();
        var label1 = two.ui.label(r1, '- or me');
        if(var popup = two.ui.hoverbox(label1))
        {
            two.ui.label(parent, 'I am a fancy tooltip');
            var arr = [ 0.6, 0.1, 1.0, 0.5, 0.92, 0.1, 0.2 ];
            //two.ui.PlotLines('Curve', arr, IM_ARRAYSIZE(arr));
        }

        two.ui.separator(n);

        //two.ui.bilabel
        var t = two.ui.table(n, [ 'Value', 'label' ], [ 0.75, 0.25 ]);

        function label = [](parent, label, help)
        {
            var row = two.ui.row(parent);
            two.ui.label(row, label);
            if(help)
                HelpMarker(row, help);
        };

        {
            // Using the _simplified_ one-liner Combo() api here
            // See 'Combo' section for examples of how to use the more complete BeginCombo()/EndCombo() api.
            var items = [ 'AAAA', 'BBBB', 'CCCC', 'DDDD', 'EEEE', 'FFFF', 'GGGG', 'HHHH', 'IIII', 'JJJJ', 'KKKK', 'LLLLLLL', 'MMMM', 'OOOOOOO' ];
            this.item_current = 0;
            var row = two.ui.row(t);
            two.ui.dropdown_input(row, items, this.item_current);
            label(row, 'combo', 'Refer to the \'Combo\' section below for an explanation of the full BeginCombo/EndCombo API, and demonstration of various flags.\n');
        }

        {
            this.str0 = 'Hello, world!';
            var row = two.ui.row(t);
            two.ui.input_string(row, str0);
            label(row, 'input text', 'USER:\nHold SHIFT or use mouse to select text.\n' 'CTRL+Left/Right to word jump.\n' 'CTRL+A or double-click to select all.\n' 'CTRL+X,CTRL+C,CTRL+V clipboard.\n' 'CTRL+Z,CTRL+Y undo/redo.\n' 'ESCAPE to revert.\n\nPROGRAMMER:\nYou can use the ImGuiInputTextFlags_CallbackResize facility if you need to wire InputText() to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example (this is not demonstrated in imgui_demo.cpp).');
        }
        {
            this.str1 = '';
            var row = two.ui.row(t);
            two.ui.input_string(row, str1); // 'input text (w/ hint)'
            label(row, 'enter text here');
            //two.ui.InputTextWithHint('input text (w/ hint)', 'enter text here', str1);
        }
        {
            this.i0 = 123;
            var row = two.ui.row(t);
            two.ui.number_input_int(row, i0);
            label(row, 'input int', 'You can apply arithmetic operators +,*,/ on numerical values.\n  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\nUse +- to subtract.\n');
        }

        {
            this.f0 = 0.001;
            var row = two.ui.row(t);
            two.ui.number_input_float(row, f0, new StatDef_float(0.01, 1.0)); // , '%.3');
            label(row, 'input float');
        }

        {
            this.d0 = 999999.00000001;
            var row = two.ui.row(t);
            two.ui.number_input_double_(row, d0, new StatDef_double(0.01, 1.0)); // , '%.8');
            label(row, 'input double');
        }

        {
            this.f1 = 1.e10;
            var row = two.ui.row(t);
            two.ui.number_input_float(row, f1, { 0.0, 0.0 }); // , '%e');
            label(row, 'input scientific', 'You can input value using the scientific notation,\n  e.g. \'1e+8\' becomes \'100000000\'.\n');

            this.vec4a = [0.10, 0.20, 0.30, 0.44];
            //two.ui.InputFloat3('input float3', vec4a);
            //two.ui.vec3_edit(t);
        }

        this.i1 = 50; this.i2 = 42;
        {
            var row = two.ui.row(t);
            two.ui.drag_input_int(row, i1, { 1 });
            label(row, 'drag int', 'Click and drag to edit value.\nHold SHIFT/ALT for faster/slower edit.\nDouble-click or CTRL+click to input value.');
        }

        {
            var row = two.ui.row(t);
            two.ui.drag_input_int(row, i2, { 1, 0, 100 }); // , '%d%%');
            label(row, 'drag int 0..100');
        }

        {
            this.f1 = 1.00; this.f2 = 0.0067;
            {
                var row = two.ui.row(t);
                two.ui.drag_input_float(row, f1, new StatDef_float(0.005));
                label(row, 'drag float');
            }
            {
                var row = two.ui.row(t);
                two.ui.drag_input_float(row, f2, new StatDef_float(0.0001, 0.0, 0.0)); // , '%.06 ns');
                label(row, 'drag small float');
            }
        }

        {
            this.i1 = 0;
            var row = two.ui.row(t);
            two.ui.slider_input_int(row, i1, new StatDef_int(-1, 3));
            label(row, 'slider int', 'CTRL+click to input value.');
        }

        this.f1 = 0.123; this.f2 = 0.0;
        {
            var row = two.ui.row(t);
            two.ui.slider_input_float(row, f1, new StatDef_float(0.0, 1.0)); // , 'ratio = %.3');
            label(row, 'slider float');
        }

        {
            var row = two.ui.row(t);
            two.ui.slider_input_float(row, f2, new StatDef_float(-10.0, 10.0)); // , '%.4', 2.0);
            label(row, 'slider float (curve)');
            //static float angle = 0.0;
            //two.ui.SliderAngle('slider angle', angle);
        }

        this.col1 = new two.Colour(1.0,0.0,0.2);
        this.col2 = new two.Colour(0.4,0.7,0.0,0.5);
        {
            var row = two.ui.row(t);
            //two.ui.ColorEdit3(row, 'color 1', col1);
            two.ui.color_toggle_edit(row, col1);
            label(row, 'color 1', 'Click on the colored square to open a color picker.\nClick and hold to use drag and drop.\nRight-click on the colored square to show options.\nCTRL+click on individual component to input value.\n');
        }

        {
            var row = two.ui.row(t);
            two.ui.color_toggle_edit(row, col2);
            label(row, 'color 2');
            //two.ui.ColorEdit4('color 2', col2);
        }

        {
            // List box
            var listbox_items = [ 'Apple', 'Banana', 'Cherry', 'Kiwi', 'Mango', 'Orange', 'Pineapple', 'Strawberry', 'Watermelon' ];
            this.listbox_item_current = 1;
            //two.ui.ListBox('listbox\n(single select)', listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 4);

            //static int listbox_itecurrent2 = 2;
            //two.ui.SetNextItemWidth(-1);
            //two.ui.ListBox('##listbox2', listbox_itecurrent2, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
        }

        //two.ui.TreePop();
    }

    // Testing ImGuiOnceUponAFrame helper.
    //static ImGuiOnceUponAFrame once;
    //for (int i = 0; i < 5; i++)
    //    if (once)
    //        two.ui.label(parent, 'This will be displayed only once.');

    if(var n = two.ui.tree_node(body, 'Trees').body)
    {
        if(var b = two.ui.tree_node(n, 'Basic trees').body)
        {
            for(var i = 0; i < 5; i++)
                //if(c = two.ui.tree_node(b, (void*)(intptr_t)i, 'Child %d', i).body)
                if(var c = two.ui.tree_node(b, 'Child ' + i.toString()).body)
                {
                    var row = two.ui.row(c);
                    two.ui.label(row, 'blah blah');
                    //two.ui.SameLine();
                    if(two.ui.button(row, 'button').activated()) {};
                    //two.ui.TreePop();
                }
            //two.ui.TreePop();
        }

        if(n = two.ui.tree_node(parent, 'Advanced, with Selectable nodes').body)
        {
            HelpMarker(n, 'This is a more typical looking tree with selectable nodes.\nClick to select, CTRL+Click to toggle, click on arrows or double-click to open.');
            this.align_label_with_current_x_position = false;
            two.ui.field(n, 'Align label with current X position)', align_label_with_current_x_position);
            two.ui.label(n, 'Hello!');
            //if(align_label_with_current_x_position)
            //  two.ui.Unindent(two.ui.GetTreeNodeToLabelSpacing());
        }
    }

    if(n = two.ui.tree_node(body, 'Collapsing Headers').body)
    {
        this.closable_group = true;
        two.ui.field(n, 'Show 2nd header', closable_group);
        if(h = two.ui.expandbox(n, 'Header').body)
        {
            two.ui.labelf(h, 'IsItemHovered: %d', false); // two.ui.IsItemHovered());
            for(int i = 0; i < 5; i++)
                two.ui.labelf(h, 'Some content %d', i);
        }
        if(h = two.ui.expandbox(n, 'Header with a close button').body) //, closable_group))
        {
            two.ui.labelf(h, 'IsItemHovered: %d', false); // two.ui.IsItemHovered());
            for(int i = 0; i < 5; i++)
                two.ui.labelf(h, 'More content %d', i);
        }
        //two.ui.TreePop();
    }

    if(var n = two.ui.tree_node(body, 'Bullets').body)
    {
        two.ui.bullet(n, 'Bullet point 1');
        two.ui.bullet(n, 'Bullet point 2\nOn multiple lines');

        var b0 = two.ui.row(n);
        two.ui.item(b0, styles().bullet);
        two.ui.label(n, 'Bullet point 3 (two calls)');

        var b1 = two.ui.row(n);
        two.ui.item(b1, styles().bullet);
        two.ui.button(b1, 'Button');
        //two.ui.TreePop();
    }

    if(var n = two.ui.tree_node(body, 'Combo').body)
    {
        // Expose flags as checkbox for the demo
        //static ImGuiComboFlags flags = 0;
        //two.ui.flag_field(parent, 'ImGuiComboFlags_PopupAlignLeft', (uint32_t&)flags, ImGuiComboFlags_PopupAlignLeft);
        //two.ui.SameLine(); HelpMarker('Only makes a difference if the popup is larger than the combo');
        //if(two.ui.flag_field(parent, 'ImGuiComboFlags_NoArrowButton', (uint32_t&)flags, ImGuiComboFlags_NoArrowButton))
        //  flags &= ~ImGuiComboFlags_NoPreview;     // Clear the other flag, as we cannot combine both
        //if(two.ui.flag_field(parent, 'ImGuiComboFlags_NoPreview', (uint32_t&)flags, ImGuiComboFlags_NoPreview))
        //  flags &= ~ImGuiComboFlags_NoArrowButton; // Clear the other flag, as we cannot combine both

        // General BeginCombo() API, you have full control over your selection data and display type.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag stored in the object itself, etc.)
        const char* items[] = { 'AAAA', 'BBBB', 'CCCC', 'DDDD', 'EEEE', 'FFFF', 'GGGG', 'HHHH', 'IIII', 'JJJJ', 'KKKK', 'LLLLLLL', 'MMMM', 'OOOOOOO' };
        static const char* itecurrent = items[0];            // Here our selection is a single pointer stored outside the object.
//#if 0
//        if(two.ui.BeginCombo('combo 1', itecurrent, flags)) // The second parameter is the label previewed before opening the combo.
//        {
//            for(int n = 0; n < IM_ARRAYSIZE(items); n++)
//            {
//                bool is_selected = (itecurrent == items[n]);
//                if(two.ui.selectable(parent, items[n], is_selected))
//                    itecurrent = items[n];
//                if(is_selected)
//                    two.ui.SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
//            }
//            two.ui.EndCombo();
//        }
//#endif

        // Simplified one-liner Combo() API, using values packed in a single constant string
        this.item_current_2 = 0;
        two.ui.dropdown_field(n, 'combo 2 (one-liner)', [ 'aaaa', 'bbbb', 'cccc', 'dddd', 'eeee' ], item_current_2);

        // Simplified one-liner Combo() using an array of const char*
        this.item_current_3 = -1; // If the selection isn't within 0..count, Combo won't display a preview
        two.ui.dropdown_field(n, 'combo 3 (array)', items, item_current_3);

        // Simplified one-liner Combo() using an accessor function
        //struct FuncHolder { this.ItemGetter(void* data, int idx, const char** out_str) { *out_str = ((const char**)data)[idx]; return true; } };
        //static int itecurrent_4 = 0;
        //two.ui.dropdown_field(n, 'combo 4 (function)', itecurrent_4, &FuncHolder::ItemGetter, items, IM_ARRAYSIZE(items));
    }