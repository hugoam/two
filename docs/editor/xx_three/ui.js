
function theme_menu(parent) {
    var styles = [ two.style_minimal, two.style_vector, two.style_imgui_dark, two.style_blendish_light, two.style_blendish_dark ];
    var names = [ 'Minimal', 'Vector', 'Imgui (Dark)', 'Blendish (Light)', 'Blendish (Dark)' ];

    var menu = two.ui.menu(parent, 'Theme').body;
    if(menu)
    {
        for(var i = 0; i < styles.length; ++i)
        {
            if(two.ui.menu_choice(menu, names[i]).activated())
            {
                parent.ui_window().reset_styles();
                styles[i](parent.ui_window());
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
    var popup = two.ui.hoverbox(label);
    if(popup)
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
function ShowDemoWindow(parent, init)
{
    var window = two.ui.window(parent, 'ImGui Demo', two.WindowState.Default | two.WindowState.Menu);

    var body = two.ui.scrollable(window.body);
    //var scrollsheet = two.ui.scroll_sheet(window.body);
    //var body = scrollsheet.body;

    if(window.menu)
    {
        menubar = window.menu;

        var menu = two.ui.menu(menubar, 'Menu').body
        if(menu)
        {
            //ShowExampleMenuFile();
        }

        theme_menu(menubar);

        var menu = two.ui.menu(menubar, 'Examples').body
        if(menu)
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

        var help = two.ui.menu(menubar, 'Help').body
        if(help)
        {
            //two.ui.menu_option(help, 'Metrics', '', show_app_metrics);
            //two.ui.menu_option(help, 'Style Editor', '', show_app_style_editor);
            //two.ui.menu_option(help, 'About Dear ImGui', '', show_app_about);
        }
    }

    //two.ui.labelf(body, 'dear imgui says hello. (%s)', '1.0'); //IMGUI_VERSION);
    //two.ui.Spacing();

    var help = two.ui.expandbox(body, 'Help').body
    if(help)
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

    var config = two.ui.expandbox(body, 'Configuration').body
    if(config)
    {
    }

    if(init)
    {
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
    }
    
    var opts = two.ui.expandbox(body, 'Window options').body
    if(opts)
    {
        row0 = two.ui.row(opts);
        two.ui.field_bool(row0, 'No titlebar', this.no_titlebar, true);
        two.ui.field_bool(row0, 'No scrollbar', this.no_scrollbar, true);
        two.ui.field_bool(row0, 'No menu', this.no_menu, true);

        row1 = two.ui.row(opts);
        two.ui.field_bool(row1, 'No move', this.no_move, true);
        two.ui.field_bool(row1, 'No resize', this.no_resize, true);
        two.ui.field_bool(row1, 'No collapse', this.no_collapse, true);

        row2 = two.ui.row(opts);
        two.ui.field_bool(row2, 'No close', this.no_close, true);
        two.ui.field_bool(row2, 'No nav', this.no_nav, true);
        two.ui.field_bool(row2, 'No background', this.no_background, true);

        row3 = two.ui.row(opts);
        two.ui.field_bool(row3, 'No bring to front', this.no_bring_to_front, true);
    }

}

ShowDemoWindow(panel, init);
