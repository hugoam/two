#define MUD_NO_GFX
#include <frame/Api.h>
#include <00_ui/00_ui.h>

#include <stl/array.h>
#include <stl/vector.hpp>

#ifdef MUD_RENDERER_GL
#include <gl/GlSystem.h>
#elif defined MUD_RENDERER_BGFX
#include <bgfx/BgfxSystem.h>
#endif

#include <ui-vg/VgVg.h>

using namespace mud;

// dear imgui, v1.70 WIP
// (demo code)

// Play it nice with Windows users. Notepad in 2017 still doesn't display text data with Unix-style \n.
#ifdef _WIN32
#define NEWLINE  "\r\n"
#define snprintf    _snprintf
#define vsnprintf   _vsnprintf
#else
#define NEWLINE  "\n"
#endif

void ShowStyleEditor(Widget& parent, ImguiLook& style, ImguiColours& colours);

// Forward Declarations
//static void ShowExampleAppDocuments(bool* p_open);
//static void ShowExampleAppMainMenuBar();
//static void ShowExampleAppConsole(bool* p_open);
//static void ShowExampleAppLog(bool* p_open);
//static void ShowExampleAppLayout(bool* p_open);
//static void ShowExampleAppPropertyEditor(bool* p_open);
//static void ShowExampleAppLongText(bool* p_open);
//static void ShowExampleAppAutoResize(bool* p_open);
//static void ShowExampleAppConstrainedResize(bool* p_open);
//static void ShowExampleAppSimpleOverlay(bool* p_open);
//static void ShowExampleAppWindowTitles(bool* p_open);
//static void ShowExampleAppCustomRendering(bool* p_open);
//static void ShowExampleMenuFile();

using SelectTheme = void(*)(UiWindow&);

void theme_menu(Widget& parent)
{
	static SelectTheme select[] = { style_minimal, style_vector, style_imgui_dark, style_blendish_light, style_blendish_dark }; // style_minimal, style_minimal };
	static cstring themes[] = { "Minimal", "Vector", "Imgui (Dark)", "Blendish (Light)", "Blendish (Dark)" }; //, "TurboBadger", "MyGui" };

	if(Widget* menu = ui::menu(parent, "Theme").m_body)
	{
		for(size_t i = 0; i < array_size(select); ++i)
		{
			if(ui::menu_choice(*menu, themes[i]).activated())
			{
				parent.ui_window().reset_styles();
				select[i](parent.ui_window());
				parent.ui().reset_styles();
			}
		}
	}
}

void theme_selector(Widget& parent)
{
	static SelectTheme select[] = { style_minimal, style_vector, style_imgui_dark, style_blendish_light, style_blendish_dark }; // style_minimal, style_minimal };
	static cstring themes[] = { "Minimal", "Vector", "Imgui (Dark)", "Blendish (Light)", "Blendish (Dark)" }; //, "TurboBadger", "MyGui" };

	static uint32_t theme = 0;
	if(ui::dropdown_input(parent, themes, theme))
	{
		parent.ui_window().reset_styles();
		select[theme](parent.ui_window());
		parent.ui().reset_styles();
	}
}

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see misc/fonts/README.txt)
static void HelpMarker(Widget& parent, const char* desc)
{
	//Widget& label = ui::label(parent, " (?)"); // @kludge space just to prevent () image syntax
	Widget& label = ui::item(parent, styles().control, " (?)");
	label.enable_state(DISABLED);
	if(Widget* popup = ui::hoverbox(label))
	{
		//ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		//ImGui::TextUnformatted(desc);
		//ImGui::PopTextWrapPos();
		//ui::text(*popup, desc);
		ui::label(*popup, desc);
	}
}

// Helper to display basic user controls.
void ShowUserGuide(Widget& parent)
{
	//ImGuiIO& io = ImGui::GetIO();
	ui::bullet(parent, "Double-click on title bar to collapse window.");
	ui::bullet(parent, "Click and drag on lower right corner to resize window\n(double-click to auto fit window to its contents).");
	ui::bullet(parent, "Click and drag on any empty space to move window.");
	ui::bullet(parent, "TAB/SHIFT+TAB to cycle through keyboard editable fields.");
	ui::bullet(parent, "CTRL+Click on a slider or drag box to input value as text.");
	//if(io.FontAllowUserScaling)
		ui::bullet(parent, "CTRL+Mouse Wheel to zoom window contents.");
	ui::bullet(parent, "Mouse Wheel to scroll.");
	ui::bullet(parent, "While editing text:\n");

	Widget& indent = ui::indent(parent);
	ui::bullet(indent, "Hold SHIFT or use mouse to select text.");
	ui::bullet(indent, "CTRL+Left/Right to word jump.");
	ui::bullet(indent, "CTRL+A or double-click to select all.");
	ui::bullet(indent, "CTRL+X,CTRL+C,CTRL+V to use clipboard.");
	ui::bullet(indent, "CTRL+Z,CTRL+Y to undo/redo.");
	ui::bullet(indent, "ESCAPE to revert.");
	ui::bullet(indent, "You can apply arithmetic operators +,*,/ on numerical values.\nUse +- to subtract.");
}

// [section] Demo Window / ShowDemoWindow()

// We split the contents of the big ShowDemoWindow() function into smaller functions (because the link time of very large functions grow non-linearly)
static void ShowDemoWindowWidgets(Widget& parent);
static void ShowDemoWindowLayout(Widget& parent);
static void ShowDemoWindowPopups(Widget& parent);
static void ShowDemoWindowColumns(Widget& parent);
static void ShowDemoWindowMisc(Widget& parent);


struct ConfigFlags
{
	enum Enum : unsigned int
	{
		None                   = 0,
		NavEnableKeyboard      = 1 << 0,   // Master keyboard navigation enable flag. NewFrame() will automatically fill io.NavInputs[] based on io.KeysDown[].
		NavEnableGamepad       = 1 << 1,   // Master gamepad navigation enable flag. This is mostly to instruct your imgui back-end to fill io.NavInputs[]. Back-end also needs to set ImGuiBackendFlags_HasGamepad.
		NavEnableSetMousePos   = 1 << 2,   // Instruct navigation to move the mouse cursor. May be useful on TV/console systems where moving a virtual mouse is awkward. Will update io.MousePos and set io.WantSetMousePos=true. If enabled you MUST honor io.WantSetMousePos requests in your binding, otherwise ImGui will react as if the mouse is jumping around back and forth.
		NavNoCaptureKeyboard   = 1 << 3,   // Instruct navigation to not set the io.WantCaptureKeyboard flag when io.NavActive is set.
		NoMouse                = 1 << 4,   // Instruct imgui to clear mouse position/buttons in NewFrame(). This allows ignoring the mouse information set by the back-end.
		NoMouseCursorChange    = 1 << 5,   // Instruct back-end to not alter mouse cursor shape and visibility. Use if the back-end cursor changes are interfering with yours and you don't want to use SetMouseCursor() to change mouse cursor. You may want to honor requests from imgui by reading GetMouseCursor() yourself instead.

		// User storage (to allow your back-end/engine to communicate to code that may be shared between multiple projects. Those flags are not used by core ImGui)
		IsSRGB                 = 1 << 20,  // Application is SRGB-aware.
		IsTouchScreen          = 1 << 21   // Application is using a touch screen instead of a mouse.
	};
};

struct BackendFlags
{
	enum Enum : unsigned int
	{
		None                  = 0,
		HasGamepad            = 1 << 0,   // Back-end supports gamepad and currently has one connected.
		HasMouseCursors       = 1 << 1,   // Back-end supports honoring GetMouseCursor() value to change the OS cursor shape.
		HasSetMousePos        = 1 << 2    // Back-end supports io.WantSetMousePos requests to reposition the OS mouse position (only used if ImGuiConfigFlags_NavEnableSetMousePos is set).
	};
};

// Demonstrate most Dear ImGui features (this is big function!)
// You may execute this function to experiment with the UI and understand what it does. You may then search for keywords in the code when you are interested by a specific feature.
void ShowDemoWindow(Widget& parent)
{
	// Examples Apps (accessible from the "Examples" menu)
	static bool show_app_documents = false;
	static bool show_app_main_menu_bar = false;
	static bool show_app_console = false;
	static bool show_app_log = false;
	static bool show_app_layout = false;
	static bool show_app_property_editor = false;
	static bool show_app_long_text = false;
	static bool show_app_auto_resize = false;
	static bool show_app_constrained_resize = false;
	static bool show_app_simple_overlay = false;
	static bool show_app_window_titles = false;
	static bool show_app_custom_rendering = false;

	//if(show_app_documents)           ShowExampleAppDocuments(&show_app_documents);
	//if(show_app_main_menu_bar)       ShowExampleAppMainMenuBar();
	//if(show_app_console)             ShowExampleAppConsole(&show_app_console);
	//if(show_app_log)                 ShowExampleAppLog(&show_app_log);
	//if(show_app_layout)              ShowExampleAppLayout(&show_app_layout);
	//if(show_app_property_editor)     ShowExampleAppPropertyEditor(&show_app_property_editor);
	//if(show_app_long_text)           ShowExampleAppLongText(&show_app_long_text);
	//if(show_app_auto_resize)         ShowExampleAppAutoResize(&show_app_auto_resize);
	//if(show_app_constrained_resize)  ShowExampleAppConstrainedResize(&show_app_constrained_resize);
	//if(show_app_simple_overlay)      ShowExampleAppSimpleOverlay(&show_app_simple_overlay);
	//if(show_app_window_titles)       ShowExampleAppWindowTitles(&show_app_window_titles);
	//if(show_app_custom_rendering)    ShowExampleAppCustomRendering(&show_app_custom_rendering);

	// Dear ImGui Apps (accessible from the "Help" menu)
	static bool show_app_metrics = false;
	static bool show_app_style_editor = false;
	static bool show_app_about = false;

	//if(show_app_metrics) { ImGui::ShowMetricsWindow(&show_app_metrics); }
	//if(show_app_style_editor) { ImGui::Begin("Style Editor", show_app_style_editor); ImGui::ShowStyleEditor(); ImGui::End(); }
	//if(show_app_about) { ImGui::ShowAboutWindow(&show_app_about); }

	// Demonstrate the various window flags. Typically you would just use the default!
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;

	WindowState window_flags = WindowState::None;
	auto set_flag = [&](WindowState flag) { window_flags = WindowState(uint32_t(window_flags) | uint32_t(flag)); };
	if(!no_titlebar)       set_flag(WindowState::Header);
	if(!no_scrollbar)      set_flag(WindowState::Scrollable);
	if(!no_menu)           set_flag(WindowState::Menu);
	if(!no_move)           set_flag(WindowState::Movable);
	if(!no_resize)         set_flag(WindowState::Sizable);
	//if(no_collapse)        window_flags |= WindowState::NoCollapse;
	//if(no_nav)             window_flags |= WindowState::NoNav;
	//if(no_background)      window_flags |= WindowState::NoBackground;
	//if(no_bring_to_front)  window_flags |= WindowState::NoBringToFrontOnFocus;
	//if(no_close)           p_open = NULL; // Don't pass our bool* to Begin
	if(!no_close)          set_flag(WindowState::Closable);

	// We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.
	//ImGui::SetNextWindowPos(vec2(650, 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(vec2(550, 680), ImGuiCond_FirstUseEver);

	// Main body of the Demo window starts here.
	Window& window = ui::window(parent, "ImGui Demo", window_flags);
	//if(window == nullptr)
	if(false)
	{
		// Early out if the window is collapsed, as an optimization.
		return;
	}

	ScrollSheet& scrollsheet = ui::scroll_sheet(*window.m_body);
	Widget& body = *scrollsheet.m_body;

	// Most "big" widgets share a common width settings by default.
	//ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);    // Use 2/3 of the space for widgets and 1/3 for labels (default)
	//ImGui::PushItemWidth(ImGui::GetFontSize() * -12);           // Use fixed width for labels (by passing a negative value), the rest goes to widgets. We choose a width proportional to our font size.

	// Menu Bar
	if(window.m_menu)
	{
		Widget& menubar = *window.m_menu;

		if(Widget* menu = ui::menu(menubar, "Menu").m_body)
		{
			//ShowExampleMenuFile();
		}

		theme_menu(menubar);

		if(Widget* menu = ui::menu(menubar, "Examples").m_body)
		{
			ui::menu_option(*menu, "Main menu bar", NULL, &show_app_main_menu_bar);
			ui::menu_option(*menu, "Console", NULL, &show_app_console);
			ui::menu_option(*menu, "Log", NULL, &show_app_log);
			ui::menu_option(*menu, "Simple layout", NULL, &show_app_layout);
			ui::menu_option(*menu, "Property editor", NULL, &show_app_property_editor);
			ui::menu_option(*menu, "Long text display", NULL, &show_app_long_text);
			ui::menu_option(*menu, "Auto-resizing window", NULL, &show_app_auto_resize);
			ui::menu_option(*menu, "Constrained-resizing window", NULL, &show_app_constrained_resize);
			ui::menu_option(*menu, "Simple overlay", NULL, &show_app_simple_overlay);
			ui::menu_option(*menu, "Manipulating window titles", NULL, &show_app_window_titles);
			ui::menu_option(*menu, "Custom rendering", NULL, &show_app_custom_rendering);
			ui::menu_option(*menu, "Documents", NULL, &show_app_documents);
		}

		if(Widget* help = ui::menu(menubar, "Help").m_body)
		{
			ui::menu_option(*help, "Metrics", NULL, &show_app_metrics);
			ui::menu_option(*help, "Style Editor", NULL, &show_app_style_editor);
			ui::menu_option(*help, "About Dear ImGui", NULL, &show_app_about);
		}
	}

	ui::labelf(body, "dear imgui says hello. (%s)", "1.0"); //IMGUI_VERSION);
	//ImGui::Spacing();

	if(Widget* help = ui::expandbox(body, "Help").m_body)
	{
		ui::label(*help, "PROGRAMMER GUIDE:");
		ui::bullet(*help, "Please see the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
		ui::bullet(*help, "Please see the comments in imgui.cpp.");
		ui::bullet(*help, "Please see the examples/ in application.");
		ui::bullet(*help, "Enable 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
		ui::bullet(*help, "Enable 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");
		ui::separator(*help);

		ui::label(*help, "USER GUIDE:");
		ShowUserGuide(*help);
	}

	if(Widget* config = ui::expandbox(body, "Configuration").m_body)
	{
		//ImGuiIO& io = ImGui::GetIO();

		static ConfigFlags::Enum ConfigFlags = ConfigFlags::None;
		static bool ConfigInputTextCursorBlink = false;
		static bool ConfigWindowsResizeFromEdges = false;
		static bool ConfigWindowsMoveFromTitleBarOnly = false;
		static bool MouseDrawCursor = false;
		static BackendFlags::Enum BackendFlags = BackendFlags::None;

		auto flag_field = [](Widget& parent, cstring label, uint32_t& flags, uint8_t shift, cstring help = nullptr)
		{
			Widget& row = ui::row(parent);
			ui::flag_field(row, label, (uint32_t&)flags, shift, true);
			if(help != nullptr)
				HelpMarker(row, help);
		};

		auto bool_field = [](Widget& parent, cstring label, bool& value, cstring help = nullptr)
		{
			Widget& row = ui::row(parent);
			ui::input_field(row, label, value, true);
			if(help != nullptr)
				HelpMarker(row, help);
		};

		if(Widget* n = ui::tree_node(*config, "Configuration##2").m_body)
		{
			flag_field(*n, "ConfigFlags: NavEnableKeyboard", (uint32_t&)ConfigFlags, ConfigFlags::NavEnableKeyboard, nullptr);
			flag_field(*n, "ConfigFlags: NavEnableGamepad",  (uint32_t&)ConfigFlags, ConfigFlags::NavEnableGamepad, "Required back-end to feed in gamepad inputs in io.NavInputs[] and set io.BackendFlags |= ImGuiBackendFlags_HasGamepad.\n\nRead instructions in imgui.cpp for details.");
			flag_field(*n, "ConfigFlags: NavEnableSetMousePos", (uint32_t&)ConfigFlags, ConfigFlags::NavEnableSetMousePos, "Instruct navigation to move the mouse cursor. See comment for ConfigFlags::NavEnableSetMousePos.");
			flag_field(*n, "ConfigFlags: NoMouse", (uint32_t&)ConfigFlags, ConfigFlags::NoMouse, nullptr);
			if(ConfigFlags & ConfigFlags::NoMouse) // Create a way to restore this flag otherwise we could be stuck completely!
			{
				//if(fmodf((float)ImGui::GetTime(), 0.40f) < 0.20f)
				//{
				//	ImGui::SameLine();
				//	ui::label(parent, "<<PRESS SPACE TO DISABLE>>");
				//}
				//if(ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Space)))
				//	config_flags &= ~ConfigFlags::NoMouse;
			}
			flag_field(*n, "ConfigFlags: NoMouseCursorChange", (uint32_t&)ConfigFlags, ConfigFlags::NoMouseCursorChange, "Instruct back-end to not alter mouse cursor shape and visibility.");
			bool_field(*n, "ConfigInputTextCursorBlink", ConfigInputTextCursorBlink, "Set to false to disable blinking cursor, for users who consider it distracting");
			bool_field(*n, "ConfigWindowsResizeFromEdges", ConfigWindowsResizeFromEdges, "Enable resizing of windows from their edges and from the lower-left corner.\nThis requires (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors) because it needs mouse cursor feedback.");
			bool_field(*n, "ConfigWindowsMoveFromTitleBarOnly", ConfigWindowsMoveFromTitleBarOnly, nullptr);
			bool_field(*n, "MouseDrawCursor", MouseDrawCursor, "Instruct Dear ImGui to render a mouse cursor for you. Note that a mouse cursor rendered via your application GPU rendering path will feel more laggy than hardware cursor, but will be more in sync with your other visuals.\n\nSome desktop applications may use both kinds of cursors (e.g. enable software cursor only when resizing/dragging something).");
			ui::separator(*n);
		}

		if(Widget* n = ui::tree_node(*config, "Backend Flags").m_body)
		{
			HelpMarker(*n, "Those flags are set by the back-ends (imgui_impl_xxx files) to specify their capabilities.");
			flag_field(*n, "io.BackendFlags: HasGamepad", (uint32_t&)BackendFlags, BackendFlags::HasGamepad);
			flag_field(*n, "io.BackendFlags: HasMouseCursors", (uint32_t&)BackendFlags, BackendFlags::HasMouseCursors);
			flag_field(*n, "io.BackendFlags: HasSetMousePos", (uint32_t&)BackendFlags, BackendFlags::HasSetMousePos);
			ui::separator(*n);
		}

		if(Widget* n = ui::tree_node(*config, "Style").m_body)
		{
			static ImguiLook look;
			static ImguiColours colours;
			ShowStyleEditor(*n, look, colours);
			ui::separator(*n);
		}

		if(Widget* n = ui::tree_node(*config, "Capture/Logging").m_body)
		{
			ui::text(*n, "The logging API redirects all text output so you can easily capture the content of a window or a block. Tree nodes can be automatically expanded.");
			HelpMarker(*n, "Try opening any of the contents below in this window and then click one of the \"Log To\" button.");
			//ImGui::LogButtons();
			ui::text(*n, "You can also call ImGui::LogText() to output directly to the log without a visual output.");
			if(ui::button(*n, "Copy \"Hello, world!\" to clipboard").activated())
			{
				//ImGui::LogToClipboard();
				//ImGui::LogText("Hello, world!");
				//ImGui::LogFinish();
			}
			//ImGui::TreePop();
		}
	}

	if(Widget* opts = ui::expandbox(body, "Window options").m_body)
	{
		Widget& row0 = ui::row(*opts);
		ui::input_field(row0, "No titlebar", no_titlebar, true);// ImGui::SameLine(150);
		ui::input_field(row0, "No scrollbar", no_scrollbar, true);// ImGui::SameLine(300);
		ui::input_field(row0, "No menu", no_menu, true);

		Widget& row1 = ui::row(*opts);
		ui::input_field(row1, "No move", no_move, true);// ImGui::SameLine(150);
		ui::input_field(row1, "No resize", no_resize, true);// ImGui::SameLine(300);
		ui::input_field(row1, "No collapse", no_collapse, true);

		Widget& row2 = ui::row(*opts);
		ui::input_field(row2, "No close", no_close, true);// ImGui::SameLine(150);
		ui::input_field(row2, "No nav", no_nav, true);// ImGui::SameLine(300);
		ui::input_field(row2, "No background", no_background, true);

		Widget& row3 = ui::row(*opts);
		ui::input_field(row3, "No bring to front", no_bring_to_front, true);
	}

	// All demo contents
	ShowDemoWindowWidgets(body);
	//ShowDemoWindowLayout(body);
	//ShowDemoWindowPopups(body);
	//ShowDemoWindowColumns(body);
	//ShowDemoWindowMisc(body);

	// End of ShowDemoWindow()
	//ImGui::End();
}

static void ShowDemoWindowWidgets(Widget& parent)
{
	Widget* body = ui::expandbox(parent, "Widgets").m_body;
	if(!body)
		return;

	if(Widget* n = ui::tree_node(*body, "Basic").m_body)
	{
		static int clicked = 0;
		Widget& r0 = ui::row(*n);
		if(ui::button(r0, "Button").activated())
			clicked++;
		if(clicked & 1)
		{
			ui::label(r0, "Thanks for clicking me!");
		}

		static bool check = true;
		ui::input_field(*n, "checkbox", check, true);

		static uint32_t e = 0;
		Widget& row0 = ui::row(*n);
		ui::radio_button(row0, "radio a", e, 0);
		ui::radio_button(row0, "radio b", e, 1);
		ui::radio_button(row0, "radio c", e, 2);

		// Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
		Widget& buttons = ui::row(*n);
		static Style styles[7] = {};
		for(int i = 0; i < 7; i++)
		{
			styles[i].m_skin.m_background_colour = hsv(i / 7.0f, 0.6f, 0.6f);
			styles[i].decline_skin(HOVERED).m_background_colour = hsv(i / 7.0f, 0.7f, 0.7f);
			styles[i].decline_skin(ACTIVE).m_background_colour = hsv(i / 7.0f, 0.8f, 0.8f);

			ui::button(buttons, styles[i], "Click");
		}

		// Use AlignTextToFramePadding() to align text baseline to the baseline of framed elements (otherwise a Text+SameLine+Button sequence will have the text a little too high by default)
		//ImGui::AlignTextToFramePadding();
#if 0
		ui::label(parent, "Hold to repeat:");
		ImGui::SameLine();

		// Arrow buttons with Repeater
		static int counter = 0;
		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if(ImGui::ArrowButton("##left", ImGuiDir_Left)) { counter--; }
		ImGui::SameLine(0.0f, spacing);
		if(ImGui::ArrowButton("##right", ImGuiDir_Right)) { counter++; }
		ImGui::PopButtonRepeat();
		ImGui::SameLine();
		ui::label(parent, "%d", counter);
#endif

		{
			Widget& r1 = ui::row(*n);
			Widget& label0 = ui::label(r1, "Hover over me");
			if(Widget* popup = ui::hoverbox(label0))
			{
				ui::text(*popup, "I am a tooltip");
			}

			//ImGui::SameLine();
			Widget& label1 = ui::label(r1, "- or me");
			if(Widget* popup = ui::hoverbox(label1))
			{
				ui::label(parent, "I am a fancy tooltip");
				static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
				//ImGui::PlotLines("Curve", arr, IM_ARRAYSIZE(arr));
			}
		}

		ui::separator(*n);

		//ui::bilabel
		//ImGui::LabelText("label", "Value");
		Widget& t = ui::table(*n, { "Value", "label" }, { 0.75f, 0.25f });

		auto label = [](Widget& parent, const string& label, cstring help = nullptr)
		{
			Widget& row = ui::row(parent);
			ui::label(row, label);
			if(help != nullptr)
				HelpMarker(row, help);
		};

		{
			// Using the _simplified_ one-liner Combo() api here
			// See "Combo" section for examples of how to use the more complete BeginCombo()/EndCombo() api.
			const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
			static uint32_t item_current = 0;
			Widget& row = ui::row(t);
			ui::dropdown_input(row, items, item_current);
			label(row, "combo", "Refer to the \"Combo\" section below for an explanation of the full BeginCombo/EndCombo API, and demonstration of various flags.\n");
		}

		{
			//static char str0[128] = "Hello, world!";
			static string str0 = "Hello, world!";
			Widget& row = ui::row(t);
			ui::input<string>(row, str0);
			label(row, "input text", "USER:\nHold SHIFT or use mouse to select text.\n" "CTRL+Left/Right to word jump.\n" "CTRL+A or double-click to select all.\n" "CTRL+X,CTRL+C,CTRL+V clipboard.\n" "CTRL+Z,CTRL+Y undo/redo.\n" "ESCAPE to revert.\n\nPROGRAMMER:\nYou can use the ImGuiInputTextFlags_CallbackResize facility if you need to wire InputText() to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example (this is not demonstrated in imgui_demo.cpp).");
		}
		{
			//static char str1[128] = "";
			static string str1 = "";
			Widget& row = ui::row(t);
			ui::input<string>(row, str1); // "input text (w/ hint)"
			label(row, "enter text here");
			//ImGui::InputTextWithHint("input text (w/ hint)", "enter text here", str1);
		}
		{
			static int i0 = 123;
			Widget& row = ui::row(t);
			ui::number_input<int>(row, i0);
			label(row, "input int", "You can apply arithmetic operators +,*,/ on numerical values.\n  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\nUse +- to subtract.\n");
		}

		{
			static float f0 = 0.001f;
			Widget& row = ui::row(t);
			ui::number_input<float>(row, { f0, 0.01f, 1.0f }); // , "%.3f");
			label(row, "input float");
		}

		{
			static double d0 = 999999.00000001;
			Widget& row = ui::row(t);
			ui::number_input<double>(row, { d0, 0.01, 1.0 }); // , "%.8f");
			label(row, "input double");
		}

		{
			static float f1 = 1.e10f;
			Widget& row = ui::row(t);
			ui::number_input<float>(row, { f1, 0.0f, 0.0f }); // , "%e");
			label(row, "input scientific", "You can input value using the scientific notation,\n  e.g. \"1e+8\" becomes \"100000000\".\n");

			static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
			//ImGui::InputFloat3("input float3", vec4a);
			//ui::vec3_edit(t);
		}

		static int i1 = 50, i2 = 42;
		{
			Widget& row = ui::row(t);
			ui::drag_input<int>(row, { i1, 1 });
			label(row, "drag int", "Click and drag to edit value.\nHold SHIFT/ALT for faster/slower edit.\nDouble-click or CTRL+click to input value.");
		}

		{
			Widget& row = ui::row(t);
			ui::drag_input<int>(row, { i2, 1, 0, 100 }); // , "%d%%");
			label(row, "drag int 0..100");
		}

		{
			static float f1 = 1.00f, f2 = 0.0067f;
			{
				Widget& row = ui::row(t);
				ui::drag_input<float>(row, { f1, 0.005f });
				label(row, "drag float");
			}
			{
				Widget& row = ui::row(t);
				ui::drag_input<float>(row, { f2, 0.0001f, 0.0f, 0.0f }); // , "%.06f ns");
				label(row, "drag small float");
			}
		}

		{
			static int i1 = 0;
			Widget& row = ui::row(t);
			ui::slider_input<int>(row, { i1, -1, 3 });
			label(row, "slider int", "CTRL+click to input value.");
		}

		static float f1 = 0.123f, f2 = 0.0f;
		{
			Widget& row = ui::row(t);
			ui::slider_input<float>(row, { f1, 0.0f, 1.0f }); // , "ratio = %.3f");
			label(row, "slider float");
		}

		{
			Widget& row = ui::row(t);
			ui::slider_input<float>(row, { f2, -10.0f, 10.0f }); // , "%.4f", 2.0f);
			label(row, "slider float (curve)");
			//static float angle = 0.0f;
			//ImGui::SliderAngle("slider angle", angle);
		}

		//static float col1[3] = { 1.0f,0.0f,0.2f };
		//static float col2[4] = { 0.4f,0.7f,0.0f,0.5f };
		static Colour col1 = { 1.0f,0.0f,0.2f };
		static Colour col2 = { 0.4f,0.7f,0.0f,0.5f };
		{
			Widget& row = ui::row(t);
			//ImGui::ColorEdit3(row, "color 1", col1);
			ui::color_toggle_edit(row, col1);
			label(row, "color 1", "Click on the colored square to open a color picker.\nClick and hold to use drag and drop.\nRight-click on the colored square to show options.\nCTRL+click on individual component to input value.\n");
		}

		{
			Widget& row = ui::row(t);
			ui::color_toggle_edit(row, col2);
			label(row, "color 2");
			//ImGui::ColorEdit4("color 2", col2);
		}

		{
			// List box
			const char* listbox_items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
			static int listbox_item_current = 1;
			//ImGui::ListBox("listbox\n(single select)", listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 4);

			//static int listbox_item_current2 = 2;
			//ImGui::SetNextItemWidth(-1);
			//ImGui::ListBox("##listbox2", listbox_item_current2, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
		}

		//ImGui::TreePop();
	}

	// Testing ImGuiOnceUponAFrame helper.
	//static ImGuiOnceUponAFrame once;
	//for (int i = 0; i < 5; i++)
	//    if (once)
	//        ui::label(parent, "This will be displayed only once.");

	if(Widget* n = ui::tree_node(*body, "Trees").m_body)
	{
		if(Widget* b = ui::tree_node(*n, "Basic trees").m_body)
		{
			for(int i = 0; i < 5; i++)
				//if(Widget* c = ui::tree_node(*b, (void*)(intptr_t)i, "Child %d", i).m_body)
				if(Widget* c = ui::tree_node(*b, ("Child " + to_string(i)).c_str()).m_body)
				{
					Widget& row = ui::row(*c);
					ui::label(row, "blah blah");
					//ImGui::SameLine();
					if(ui::button(row, "button").activated()) {};
					//ImGui::TreePop();
				}
			//ImGui::TreePop();
		}

		if(Widget* n = ui::tree_node(parent, "Advanced, with Selectable nodes").m_body)
		{
			HelpMarker(*n, "This is a more typical looking tree with selectable nodes.\nClick to select, CTRL+Click to toggle, click on arrows or double-click to open.");
			static bool align_label_with_current_x_position = false;
			ui::input_field(*n, "Align label with current X position)", align_label_with_current_x_position);
			ui::label(*n, "Hello!");
			//if(align_label_with_current_x_position)
			//	ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

#if 0
			static int selection_mask = (1 << 2); // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.
			int node_clicked = -1;                // Temporary storage of what node we have clicked to process selection at the end of the loop. May be a pointer to your own node type, etc.
			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3); // Increase spacing to differentiate leaves from expanded contents.
			for(int i = 0; i < 6; i++)
			{
				// Disable the default open on single-click behavior and pass in Selected flag according to our selection state.
				ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
				if(selection_mask & (1 << i))
					node_flags |= ImGuiTreeNodeFlags_Selected;
				if(i < 3)
				{
					// Items 0..2 are Tree Node
					bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
					if(ImGui::IsItemClicked())
						node_clicked = i;
					if(node_open)
					{
						ui::label(parent, "Blah blah\nBlah Blah");
						//ImGui::TreePop();
					}
				}
				else
				{
					// Items 3..5 are Tree Leaves
					// The only reason we use TreeNode at all is to allow selection of the leaf.
					// Otherwise we can use BulletText() or TreeAdvanceToLabelPos()+Text().
					node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
					ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
					if(ImGui::IsItemClicked())
						node_clicked = i;
				}
			}
			if(node_clicked != -1)
			{
				// Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
				if(ImGui::GetIO().KeyCtrl)
					selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
				else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
					selection_mask = (1 << node_clicked);           // Click to single-select
			}
			ImGui::PopStyleVar();
			if(align_label_with_current_x_position)
				ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
#endif
			//ImGui::TreePop();
		}
		//ImGui::TreePop();
	}

	if(Widget* n = ui::tree_node(*body, "Collapsing Headers").m_body)
	{
		static bool closable_group = true;
		ui::input_field(*n, "Show 2nd header", closable_group);
		if(Widget* h = ui::expandbox(*n, "Header").m_body)
		{
			ui::labelf(*h, "IsItemHovered: %d", false); // ImGui::IsItemHovered());
			for(int i = 0; i < 5; i++)
				ui::labelf(*h, "Some content %d", i);
		}
		if(Widget* h = ui::expandbox(*n, "Header with a close button").m_body) //, closable_group))
		{
			ui::labelf(*h, "IsItemHovered: %d", false); // ImGui::IsItemHovered());
			for(int i = 0; i < 5; i++)
				ui::labelf(*h, "More content %d", i);
		}
		//ImGui::TreePop();
	}

	if(Widget* n = ui::tree_node(*body, "Bullets").m_body)
	{
		ui::bullet(*n, "Bullet point 1");
		ui::bullet(*n, "Bullet point 2\nOn multiple lines");

		Widget& b0 = ui::row(*n);
		ui::item(b0, styles().bullet);
		ui::label(*n, "Bullet point 3 (two calls)");

		Widget& b1 = ui::row(*n);
		ui::item(b1, styles().bullet);
		ui::button(b1, "Button");
		//ImGui::TreePop();
	}

#if 0
	if(Widget& n = ui::tree_node(*body, "Text"))
	{
		if(Widget& n = ui::tree_node(*n, "Colored Text"))
		{
			// Using shortcut. You can use PushStyleColor()/PopStyleColor() for more flexibility.
			ImGui::TextColored(vec4(1.0f, 0.0f, 1.0f, 1.0f), "Pink");
			ImGui::TextColored(vec4(1.0f, 1.0f, 0.0f, 1.0f), "Yellow");
			ImGui::TextDisabled("Disabled");
			ImGui::SameLine(); HelpMarker("The TextDisabled color is stored in ImGuiStyle.");
			//ImGui::TreePop();
		}

		if(Widget& n = ui::tree_node(*n, "Word Wrapping"))
		{
			// Using shortcut. You can use PushTextWrapPos()/PopTextWrapPos() for more flexibility.
			ui::text(parent, "This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");
			ImGui::Spacing();

			static float wrap_width = 200.0f;
			ui::slider_field<float>(parent, "Wrap width", wrap_width, -20, 600, "%.0f");

			ui::label(parent, "Test paragraph 1:");
			vec2 pos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(vec2(pos.x + wrap_width, pos.y), vec2(pos.x + wrap_width + 10, pos.y + ImGui::GetTextLineHeight()), IM_COL32(255, 0, 255, 255));
			ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
			ui::label(parent, "The lazy dog is a good dog. This paragraph is made to fit within %.0f pixels. Testing a 1 character word. The quick brown fox jumps over the lazy dog.", wrap_width);
			ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
			ImGui::PopTextWrapPos();

			ui::label(parent, "Test paragraph 2:");
			pos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(vec2(pos.x + wrap_width, pos.y), vec2(pos.x + wrap_width + 10, pos.y + ImGui::GetTextLineHeight()), IM_COL32(255, 0, 255, 255));
			ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
			ui::label(parent, "aaaaaaaa bbbbbbbb, c cccccccc,dddddddd. d eeeeeeee   ffffffff. gggggggg!hhhhhhhh");
			ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
			ImGui::PopTextWrapPos();

			//ImGui::TreePop();
		}

		if(Widget& n = ui::tree_node(*n, "UTF-8 Text"))
		{
			// UTF-8 test with Japanese characters
			// (Needs a suitable font, try Noto, or Arial Unicode, or M+ fonts. Read misc/fonts/README.txt for details.)
			// - From C++11 you can use the u8"my text" syntax to encode literal strings as UTF-8
			// - For earlier compiler, you may be able to encode your sources as UTF-8 (e.g. Visual Studio save your file as 'UTF-8 without signature')
			// - FOR THIS DEMO FILE ONLY, BECAUSE WE WANT TO SUPPORT OLD COMPILERS, WE ARE *NOT* INCLUDING RAW UTF-8 CHARACTERS IN THIS SOURCE FILE.
			//   Instead we are encoding a few strings with hexadecimal constants. Don't do this in your application!
			//   Please use u8"text in any language" in your application!
			// Note that characters values are preserved even by InputText() if the font cannot be displayed, so you can safely copy & paste garbled characters into another application.
			ui::text(parent, "CJK text will only appears if the font was loaded with the appropriate CJK character ranges. Call io.Font->AddFontFromFileTTF() manually to load extra character ranges. Read misc/fonts/README.txt for details.");
			ui::label(parent, "Hiragana: \xe3\x81\x8b\xe3\x81\x8d\xe3\x81\x8f\xe3\x81\x91\xe3\x81\x93 (kakikukeko)"); // Normally we would use u8"blah blah" with the proper characters directly in the string.
			ui::label(parent, "Kanjis: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");
			static char buf[32] = "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e";
			//static char buf[32] = u8"NIHONGO"; // <- this is how you would write it with C++11, using real kanjis
			ImGui::InputText("UTF-8 input", buf, IM_ARRAYSIZE(buf));
			//ImGui::TreePop();
		}
		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Images"))
	{
		ImGuiIO& io = ImGui::GetIO();
		ui::text(parent, "Below we are displaying the font texture (which is the only texture we have access to in this demo). Use the 'ImTextureID' type as storage to pass pointers or identifier to your own texture data. Hover the texture for a zoomed view!");

		// Here we are grabbing the font texture because that's the only one we have access to inside the demo code.
		// Remember that ImTextureID is just storage for whatever you want it to be, it is essentially a value that will be passed to the render function inside the ImDrawCmd structure.
		// If you use one of the default imgui_impl_XXXX.cpp renderer, they all have comments at the top of their file to specify what they expect to be stored in ImTextureID.
		// (for example, the imgui_impl_dx11.cpp renderer expect a 'ID3D11ShaderResourceView*' pointer. The imgui_impl_glfw_gl3.cpp renderer expect a GLuint OpenGL texture identifier etc.)
		// If you decided that ImTextureID = MyEngineTexture*, then you can pass your MyEngineTexture* pointers to ImGui::Image(), and gather width/height through your own functions, etc.
		// Using ShowMetricsWindow() as a "debugger" to inspect the draw data that are being passed to your render will help you debug issues if you are confused about this.
		// Consider using the lower-level ImDrawList::AddImage() API, via ImGui::GetWindowDrawList()->AddImage().
		ImTextureID my_tex_id = io.Fonts->TexID;
		float my_tex_w = (float)io.Fonts->TexWidth;
		float my_tex_h = (float)io.Fonts->TexHeight;

		ui::label(parent, "%.0fx%.0f", my_tex_w, my_tex_h);
		vec2 pos = ImGui::GetCursorScreenPos();
		ImGui::Image(my_tex_id, vec2(my_tex_w, my_tex_h), vec2(0, 0), vec2(1, 1), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 0.5f));
		if(ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			float region_sz = 32.0f;
			float region_x = io.MousePos.x - pos.x - region_sz * 0.5f; if(region_x < 0.0f) region_x = 0.0f; else if(region_x > my_tex_w - region_sz) region_x = my_tex_w - region_sz;
			float region_y = io.MousePos.y - pos.y - region_sz * 0.5f; if(region_y < 0.0f) region_y = 0.0f; else if(region_y > my_tex_h - region_sz) region_y = my_tex_h - region_sz;
			float zoom = 4.0f;
			ui::label(parent, "Min: (%.2f, %.2f)", region_x, region_y);
			ui::label(parent, "Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
			vec2 uv0 = vec2((region_x) / my_tex_w, (region_y) / my_tex_h);
			vec2 uv1 = vec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
			ImGui::Image(my_tex_id, vec2(region_sz * zoom, region_sz * zoom), uv0, uv1, vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 0.5f));
			ImGui::EndTooltip();
		}
		ui::text(parent, "And now some textured buttons..");
		static int pressed_count = 0;
		for(int i = 0; i < 8; i++)
		{
			ImGui::PushID(i);
			int frame_padding = -1 + i;     // -1 = uses default padding
			if(ImGui::ImageButton(my_tex_id, vec2(32, 32), vec2(0, 0), vec2(32.0f / my_tex_w, 32 / my_tex_h), frame_padding, vec4(0.0f, 0.0f, 0.0f, 1.0f)))
				pressed_count += 1;
			ImGui::PopID();
			ImGui::SameLine();
		}
		ImGui::NewLine();
		ui::label(parent, "Pressed %d times.", pressed_count);
		//ImGui::TreePop();
	}
#endif
	if(Widget* n = ui::tree_node(*body, "Combo").m_body)
	{
		// Expose flags as checkbox for the demo
		//static ImGuiComboFlags flags = 0;
		//ui::flag_field(parent, "ImGuiComboFlags_PopupAlignLeft", (uint32_t&)flags, ImGuiComboFlags_PopupAlignLeft);
		//ImGui::SameLine(); HelpMarker("Only makes a difference if the popup is larger than the combo");
		//if(ui::flag_field(parent, "ImGuiComboFlags_NoArrowButton", (uint32_t&)flags, ImGuiComboFlags_NoArrowButton))
		//	flags &= ~ImGuiComboFlags_NoPreview;     // Clear the other flag, as we cannot combine both
		//if(ui::flag_field(parent, "ImGuiComboFlags_NoPreview", (uint32_t&)flags, ImGuiComboFlags_NoPreview))
		//	flags &= ~ImGuiComboFlags_NoArrowButton; // Clear the other flag, as we cannot combine both

		// General BeginCombo() API, you have full control over your selection data and display type.
		// (your selection data could be an index, a pointer to the object, an id for the object, a flag stored in the object itself, etc.)
		const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
		static const char* item_current = items[0];            // Here our selection is a single pointer stored outside the object.
#if 0
		if(ImGui::BeginCombo("combo 1", item_current, flags)) // The second parameter is the label previewed before opening the combo.
		{
			for(int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (item_current == items[n]);
				if(ui::selectable(parent, items[n], is_selected))
					item_current = items[n];
				if(is_selected)
					ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
			}
			ImGui::EndCombo();
		}
#endif

		// Simplified one-liner Combo() API, using values packed in a single constant string
		static uint32_t item_current_2 = 0;
		ui::dropdown_field(*n, "combo 2 (one-liner)", { "aaaa", "bbbb", "cccc", "dddd", "eeee", "", "" }, item_current_2);

		// Simplified one-liner Combo() using an array of const char*
		static uint32_t item_current_3 = -1; // If the selection isn't within 0..count, Combo won't display a preview
		ui::dropdown_field(*n, "combo 3 (array)", items, item_current_3);

		// Simplified one-liner Combo() using an accessor function
		//struct FuncHolder { static bool ItemGetter(void* data, int idx, const char** out_str) { *out_str = ((const char**)data)[idx]; return true; } };
		//static int item_current_4 = 0;
		//ui::dropdown_field(*n, "combo 4 (function)", item_current_4, &FuncHolder::ItemGetter, items, IM_ARRAYSIZE(items));

		//ImGui::TreePop();
	}
#if 0
	if(Widget& n = ui::tree_node(*body, "Selectables"))
	{
		// Selectable() has 2 overloads:
		// - The one taking "bool selected" as a read-only selection information. When Selectable() has been clicked is returns true and you can alter selection state accordingly.
		// - The one taking "bool* p_selected" as a read-write selection information (convenient in some cases)
		// The earlier is more flexible, as in real application your selection may be stored in a different manner (in flags within objects, as an external list, etc).
		if(Widget& n = ui::tree_node(*n, "Basic"))
		{
			static bool selection[5] = { false, true, false, false, false };
			ui::selectable(parent, "1. I am selectable", selection[0]);
			ui::selectable(parent, "2. I am selectable", selection[1]);
			ui::label(parent, "3. I am not selectable");
			ui::selectable(parent, "4. I am selectable", selection[3]);
			if(ui::selectable(parent, "5. I am double clickable", selection[4], ImGuiSelectableFlags_AllowDoubleClick))
				if(ImGui::IsMouseDoubleClicked(0))
					selection[4] = !selection[4];
			//ImGui::TreePop();
		}
		if(Widget& n = ui::tree_node(*n, "Selection State: Single Selection"))
		{
			static int selected = -1;
			for(int n = 0; n < 5; n++)
			{
				char buf[32];
				sprintf(buf, "Object %d", n);
				if(ui::selectable(parent, buf, selected == n))
					selected = n;
			}
			//ImGui::TreePop();
		}
		if(Widget& n = ui::tree_node(*n, "Selection State: Multiple Selection"))
		{
			HelpMarker("Hold CTRL and click to select multiple items.");
			static bool selection[5] = { false, false, false, false, false };
			for(int n = 0; n < 5; n++)
			{
				char buf[32];
				sprintf(buf, "Object %d", n);
				if(ui::selectable(parent, buf, selection[n]))
				{
					if(!ImGui::GetIO().KeyCtrl)    // Clear selection when CTRL is not held
						memset(selection, 0, sizeof(selection));
					selection[n] ^= 1;
				}
			}
			//ImGui::TreePop();
		}
		if(Widget& n = ui::tree_node(*n, "Rendering more text into the same line"))
		{
			// Using the Selectable() override that takes "bool* p_selected" parameter and toggle your booleans automatically.
			static bool selected[3] = { false, false, false };
			ui::selectable(parent, "main.c", selected[0]); ImGui::SameLine(300); ui::label(parent, " 2,345 bytes");
			ui::selectable(parent, "Hello.cpp", selected[1]); ImGui::SameLine(300); ui::label(parent, " 12,345 bytes");
			ui::selectable(parent, "Hello.h", selected[2]); ImGui::SameLine(300); ui::label(parent, " 2,345 bytes");
			//ImGui::TreePop();
		}
		if(Widget& n = ui::tree_node(*n, "In columns"))
		{
			Widget& cols = ui::columns(parent, 3, NULL, false);
			static bool selected[16] = { 0 };
			for(int i = 0; i < 16; i++)
			{
				char label[32]; sprintf(label, "Item %d", i);
				if(ui::selectable(parent, label, &selected[i])) {}
				ImGui::NextColumn();
			}
			
			//ImGui::TreePop();
		}
		if(Widget& n = ui::tree_node(*n, "Grid"))
		{
			static bool selected[4 * 4] = { true, false, false, false, false, true, false, false, false, false, true, false, false, false, false, true };
			for(int i = 0; i < 4 * 4; i++)
			{
				ImGui::PushID(i);
				if(ui::selectable(parent, "Sailor", selected[i], 0, vec2(50, 50)))
				{
					// Note: We _unnecessarily_ test for both x/y and i here only to silence some static analyzer. The second part of each test is unnecessary.
					int x = i % 4;
					int y = i / 4;
					if(x > 0) { selected[i - 1] ^= 1; }
					if(x < 3 && i < 15) { selected[i + 1] ^= 1; }
					if(y > 0 && i > 3) { selected[i - 4] ^= 1; }
					if(y < 3 && i < 12) { selected[i + 4] ^= 1; }
				}
				if((i % 4) < 3) ImGui::SameLine();
				ImGui::PopID();
			}
			//ImGui::TreePop();
		}
		if(Widget& n = ui::tree_node(*n, "Alignment"))
		{
			HelpMarker("Alignment applies when a selectable is larger than its text content.\nBy default, Selectables uses style.SelectableTextAlign but it can be overriden on a per-item basis using PushStyleVar().");
			static bool selected[3 * 3] = { true, false, true, false, true, false, true, false, true };
			for(int y = 0; y < 3; y++)
			{
				for(int x = 0; x < 3; x++)
				{
					vec2 alignment = vec2((float)x / 2.0f, (float)y / 2.0f);
					char name[32];
					sprintf(name, "(%.1f,%.1f)", alignment.x, alignment.y);
					if(x > 0) ImGui::SameLine();
					ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, alignment);
					ui::selectable(parent, name, &selected[3 * y + x], ImGuiSelectableFlags_None, vec2(80, 80));
					ImGui::PopStyleVar();
				}
			}
			//ImGui::TreePop();
		}
		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Text Input"))
	{
		if(Widget& n = ui::tree_node(parent, "Multi-line Text Input"))
		{
			// Note: we are using a fixed-sized buffer for simplicity here. See ImGuiInputTextFlags_CallbackResize
			// and the code in misc/cpp/imgui_stdlib.h for how to setup InputText() for dynamically resizing strings.
			static char text[1024 * 16] =
				"/*\n"
				" The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
				" the hexadecimal encoding of one offending instruction,\n"
				" more formally, the invalid operand with locked CMPXCHG8B\n"
				" instruction bug, is a design flaw in the majority of\n"
				" Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
				" processors (all in the P5 microarchitecture).\n"
				"*/\n\n"
				"label:\n"
				"\tlock cmpxchg8b eax\n";

			static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
			HelpMarker("You can use the ImGuiInputTextFlags_CallbackResize facility if you need to wire InputTextMultiline() to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example. (This is not demonstrated in imgui_demo.cpp)");
			ui::flag_field(parent, "ImGuiInputTextFlags_ReadOnly", (uint32_t&)flags, ImGuiInputTextFlags_ReadOnly);
			ui::flag_field(parent, "ImGuiInputTextFlags_AllowTabInput", (uint32_t&)flags, ImGuiInputTextFlags_AllowTabInput);
			ui::flag_field(parent, "ImGuiInputTextFlags_CtrlEnterForNewLine", (uint32_t&)flags, ImGuiInputTextFlags_CtrlEnterForNewLine);
			ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), vec2(-1.0f, ImGui::GetTextLineHeight() * 16), flags);
			//ImGui::TreePop();
		}

		if(Widget& n = ui::tree_node(parent, "Filtered Text Input"))
		{
			static char buf1[64] = ""; ImGui::InputText("default", buf1, 64);
			static char buf2[64] = ""; ImGui::InputText("decimal", buf2, 64, ImGuiInputTextFlags_CharsDecimal);
			static char buf3[64] = ""; ImGui::InputText("hexadecimal", buf3, 64, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
			static char buf4[64] = ""; ImGui::InputText("uppercase", buf4, 64, ImGuiInputTextFlags_CharsUppercase);
			static char buf5[64] = ""; ImGui::InputText("no blank", buf5, 64, ImGuiInputTextFlags_CharsNoBlank);
			struct TextFilters { static int FilterImGuiLetters(ImGuiInputTextCallbackData* data) { if(data->EventChar < 256 && strchr("imgui", (char)data->EventChar)) return 0; return 1; } };
			static char buf6[64] = ""; ImGui::InputText("\"imgui\" letters", buf6, 64, ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterImGuiLetters);

			ui::label(parent, "Password input");
			static char bufpass[64] = "password123";
			ImGui::InputText("password", bufpass, 64, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			ImGui::SameLine(); HelpMarker("Display all characters as '*'.\nDisable clipboard cut and copy.\nDisable logging.\n");
			ImGui::InputTextWithHint("password (w/ hint)", "<password>", bufpass, 64, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputText("password (clear)", bufpass, 64, ImGuiInputTextFlags_CharsNoBlank);
			//ImGui::TreePop();
		}

		if(Widget& n = ui::tree_node(*body, "Resize Callback"))
		{
			// If you have a custom string type you would typically create a ImGui::InputText() wrapper than takes your type as input.
			// See misc/cpp/imgui_stdlib.h and .cpp for an implementation of this using std::string.
			HelpMarker("Demonstrate using ImGuiInputTextFlags_CallbackResize to wire your resizable string type to InputText().\n\nSee misc/cpp/imgui_stdlib.h for an implementation of this for std::string.");
			struct Funcs
			{
				static int MyResizeCallback(ImGuiInputTextCallbackData* data)
				{
					if(data->EventFlag == ImGuiInputTextFlags_CallbackResize)
					{
						vector<char>* my_str = (vector<char>*)data->UserData;
						IM_ASSERT(my_str->begin() == data->Buf);
						my_str->resize(data->BufSize);  // NB: On resizing calls, generally data->BufSize == data->BufTextLen + 1
						data->Buf = my_str->begin();
					}
					return 0;
				}

				// Tip: Because ImGui:: is a namespace you would typicall add your own function into the namespace in your own source files.
				// For example, you may add a function called ImGui::InputText(const char* label, MyString* my_str).
				static bool MyInputTextMultiline(const char* label, vector<char>* my_str, const vec2& size = vec2(0, 0), ImGuiInputTextFlags flags = 0)
				{
					IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
					return ImGui::InputTextMultiline(label, my_str->begin(), (size_t)my_str->size(), size, flags | ImGuiInputTextFlags_CallbackResize, Funcs::MyResizeCallback, (void*)my_str);
				}
			};

			// For this demo we are using vector as a string container.
			// Note that because we need to store a terminating zero character, our size/capacity are 1 more than usually reported by a typical string class.
			static vector<char> my_str;
			if(my_str.empty())
				my_str.push_back(0);
			Funcs::MyInputTextMultiline("##MyStr", my_str, vec2(-1.0f, ImGui::GetTextLineHeight() * 16));
			ui::label(parent, "Data: %p\nSize: %d\nCapacity: %d", (void*)my_str.begin(), my_str.size(), my_str.capacity());
			//ImGui::TreePop();
		}

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Plots Widgets"))
	{
		static bool animate = true;
		ui::input_field(parent, "Animate", animate);

		static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
		ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));

		// Create a dummy array of contiguous float values to plot
		// Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float and the sizeof() of your structure in the Stride parameter.
		static float values[90] = { 0 };
		static int values_offset = 0;
		static double refresh_time = 0.0;
		if(!animate || refresh_time == 0.0)
			refresh_time = ImGui::GetTime();
		while(refresh_time < ImGui::GetTime()) // Create dummy data at fixed 60 hz rate for the demo
		{
			static float phase = 0.0f;
			values[values_offset] = cosf(phase);
			values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
			phase += 0.10f*values_offset;
			refresh_time += 1.0f / 60.0f;
		}
		ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "avg 0.0", -1.0f, 1.0f, vec2(0, 80));
		ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, vec2(0, 80));

		// Use functions to generate output
		// FIXME: This is rather awkward because current plot API only pass in indices. We probably want an API passing floats and user provide sample rate/count.
		struct Funcs
		{
			static float Sin(void*, int i) { return sinf(i * 0.1f); }
			static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
		};
		static int func_type = 0, display_count = 70;
		ui::separator(parent);
		ImGui::SetNextItemWidth(100);
		ui::dropdown_field(parent, "func", func_type, "Sin", "Saw", "");
		ImGui::SameLine();
		ui::slider_field<int>(parent, ("Sample count", display_count, 1, 400);
		float(*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
		ImGui::PlotLines("Lines", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, vec2(0, 80));
		ImGui::PlotHistogram("Histogram", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, vec2(0, 80));
		ui::separator(parent);

		// Animate a simple progress bar
		static float progress = 0.0f, progress_dir = 1.0f;
		if(animate)
		{
			progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
			if(progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
			if(progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }
		}

		// Typically we would use vec2(-1.0f,0.0f) to use all available width, or vec2(width,0.0f) for a specified width. vec2(0.0f,0.0f) uses ItemWidth.
		ImGui::ProgressBar(progress, vec2(0.0f, 0.0f));
		ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
		ui::label(parent, "Progress Bar");

		float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;
		char buf[32];
		sprintf(buf, "%d/%d", (int)(progress_saturated * 1753), 1753);
		ImGui::ProgressBar(progress, vec2(0.f, 0.f), buf);
		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Color/Picker Widgets"))
	{
		static vec4 color = vec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);

		static bool alpha_preview = true;
		static bool alpha_half_preview = false;
		static bool drag_and_drop = true;
		static bool options_menu = true;
		static bool hdr = false;
		ui::input_field(parent, "With Alpha Preview", alpha_preview);
		ui::input_field(parent, "With Half Alpha Preview", alpha_half_preview);
		ui::input_field(parent, "With Drag and Drop", drag_and_drop);
		ui::input_field(parent, "With Options Menu", options_menu); ImGui::SameLine(); HelpMarker("Right-click on the individual color widget to show options.");
		ui::input_field(parent, "With HDR", hdr); ImGui::SameLine(); HelpMarker("Currently all this does is to lift the 0..1 limits on dragging widgets.");
		int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

		ui::label(parent, "Color widget:");
		ImGui::SameLine(); HelpMarker("Click on the colored square to open a color picker.\nCTRL+click on individual component to input value.\n");
		ImGui::ColorEdit3("MyColor##1", (float*)&color, misc_flags);

		ui::label(parent, "Color widget HSV with Alpha:");
		ImGui::ColorEdit4("MyColor##2", (float*)&color, ImGuiColorEditFlags_DisplayHSV | misc_flags);

		ui::label(parent, "Color widget with Float Display:");
		ImGui::ColorEdit4("MyColor##2f", (float*)&color, ImGuiColorEditFlags_Float | misc_flags);

		ui::label(parent, "Color button with Picker:");
		ImGui::SameLine(); HelpMarker("With the ImGuiColorEditFlags_NoInputs flag you can hide all the slider/text inputs.\nWith the ImGuiColorEditFlags_NoLabel flag you can pass a non-empty label which will only be used for the tooltip and picker popup.");
		ImGui::ColorEdit4("MyColor##3", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | misc_flags);

		ui::label(parent, "Color button with Custom Picker Popup:");

		// Generate a dummy default palette. The palette will persist and can be edited.
		static bool saved_palette_init = true;
		static vec4 saved_palette[32] = { };
		if(saved_palette_init)
		{
			for(int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
			{
				ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f, saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
				saved_palette[n].w = 1.0f; // Alpha
			}
			saved_palette_init = false;
		}

		static vec4 backup_color;
		bool open_popup = ImGui::ColorButton("MyColor##3b", color, misc_flags);
		ImGui::SameLine();
		open_popup |= ui::button(parent, "Palette");
		if(open_popup)
		{
			ImGui::OpenPopup("mypicker");
			backup_color = color;
		}
		if(ImGui::BeginPopup("mypicker"))
		{
			ui::label(parent, "MY CUSTOM COLOR PICKER WITH AN AMAZING PALETTE!");
			ui::separator(parent);
			ImGui::ColorPicker4("##picker", (float*)&color, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
			ImGui::SameLine();

			ImGui::BeginGroup(); // Lock X position
			ui::label(parent, "Current");
			ImGui::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, vec2(60, 40));
			ui::label(parent, "Previous");
			if(ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, vec2(60, 40)))
				color = backup_color;
			ui::separator(parent);
			ui::label(parent, "Palette");
			for(int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
			{
				ImGui::PushID(n);
				if((n % 8) != 0)
					ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);
				if(ImGui::ColorButton("##palette", saved_palette[n], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip, vec2(20, 20)))
					color = vec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w); // Preserve alpha!

				// Allow user to drop colors into each palette entry
				// (Note that ColorButton is already a drag source by default, unless using ImGuiColorEditFlags_NoDragDrop)
				if(ImGui::BeginDragDropTarget())
				{
					if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
						memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
					if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
						memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
					ImGui::EndDragDropTarget();
				}

				ImGui::PopID();
			}
			ImGui::EndGroup();
			ImGui::EndPopup();
		}

		ui::label(parent, "Color button only:");
		ImGui::ColorButton("MyColor##3c", *(vec4*)&color, misc_flags, vec2(80, 80));

		ui::label(parent, "Color picker:");
		static bool alpha = true;
		static bool alpha_bar = true;
		static bool side_preview = true;
		static bool ref_color = false;
		static vec4 ref_color_v(1.0f, 0.0f, 1.0f, 0.5f);
		static int display_mode = 0;
		static int picker_mode = 0;
		ui::input_field(parent, "With Alpha", alpha);
		ui::input_field(parent, "With Alpha Bar", alpha_bar);
		ui::input_field(parent, "With Side Preview", side_preview);
		if(side_preview)
		{
			ImGui::SameLine();
			ui::input_field(parent, "With Ref Color", ref_color);
			if(ref_color)
			{
				ImGui::SameLine();
				ImGui::ColorEdit4("##RefColor", ref_color_v.x, ImGuiColorEditFlags_NoInputs | misc_flags);
			}
		}
		ui::dropdown_field(parent, "Display Mode", display_mode, { "Auto/Current", "None", "RGB Only", "HSV Only", "Hex Only" });
		ImGui::SameLine(); HelpMarker("ColorEdit defaults to displaying RGB inputs if you don't specify a display mode, but the user can change it with a right-click.\n\nColorPicker defaults to displaying RGB+HSV+Hex if you don't specify a display mode.\n\nYou can change the defaults using SetColorEditOptions().");
		ui::dropdown_field(parent, "Picker Mode", picker_mode, "Auto/Current", "Hue bar + SV rect", "Hue wheel + SV triangle", "");
		ImGui::SameLine(); HelpMarker("User can right-click the picker to change mode.");
		ImGuiColorEditFlags flags = misc_flags;
		if(!alpha)            flags |= ImGuiColorEditFlags_NoAlpha;        // This is by default if you call ColorPicker3() instead of ColorPicker4()
		if(alpha_bar)         flags |= ImGuiColorEditFlags_AlphaBar;
		if(!side_preview)     flags |= ImGuiColorEditFlags_NoSidePreview;
		if(picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
		if(picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
		if(display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
		if(display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // Override display mode
		if(display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
		if(display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
		ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);

		ui::label(parent, "Programmatically set defaults:");
		ImGui::SameLine(); HelpMarker("SetColorEditOptions() is designed to allow you to set boot-time default.\nWe don't have Push/Pop functions because you can force options on a per-widget basis if needed, and the user can change non-forced ones with the options menu.\nWe don't have a getter to avoid encouraging you to persistently save values that aren't forward-compatible.");
		if(ui::button(parent, "Default: Uint8 + HSV + Hue Bar"))
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_PickerHueBar);
		if(ui::button(parent, "Default: Float + HDR + Hue Wheel"))
			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);

		// HSV encoded support (to avoid RGB<>HSV round trips and singularities when S==0 or V==0)
		static vec4 color_stored_as_hsv(0.23f, 1.0f, 1.0f, 1.0f);
		ImGui::Spacing();
		ui::label(parent, "HSV encoded colors");
		ImGui::SameLine(); HelpMarker("By default, colors are given to ColorEdit and ColorPicker in RGB, but ImGuiColorEditFlags_InputHSV allows you to store colors as HSV and pass them to ColorEdit and ColorPicker as HSV. This comes with the added benefit that you can manipulate hue values with the picker even when saturation or value are zero.");
		ui::label(parent, "Color widget with InputHSV:");
		ImGui::ColorEdit4("HSV shown as HSV##1", (float*)&color_stored_as_hsv, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float);
		ImGui::ColorEdit4("HSV shown as RGB##1", (float*)&color_stored_as_hsv, ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float);
		ImGui::DragFloat4("Raw HSV values", (float*)&color_stored_as_hsv, 0.01f, 0.0f, 1.0f);

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Range Widgets"))
	{
		static float begin = 10, end = 90;
		static int begin_i = 100, end_i = 1000;
		ImGui::DragFloatRange2("range", begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
		ImGui::DragIntRange2("range int (no bounds)", begin_i, &end_i, 5, 0, 0, "Min: %d units", "Max: %d units");
		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Data Types"))
	{
		// The DragScalar/InputScalar/SliderScalar functions allow various data types: signed/unsigned int/long long and float/double
		// To avoid polluting the public API with all possible combinations, we use the ImGuiDataType enum to pass the type,
		// and passing all arguments by address.
		// This is the reason the test code below creates local variables to hold "zero" "one" etc. for each types.
		// In practice, if you frequently use a given type that is not covered by the normal API entry points, you can wrap it
		// yourself inside a 1 line function which can take typed argument as value instead of void*, and then pass their address
		// to the generic function. For example:
		//   bool MySliderU64(const char *label, u64* value, u64 min = 0, u64 max = 0, const char* format = "%lld")
		//   {
		//      return SliderScalar(label, ImGuiDataType_U64, value, &min, &max, format);
		//   }

		// Limits (as helper variables that we can take the address of)
		// Note that the SliderScalar function has a maximum usable range of half the natural type maximum, hence the /2 below.
#ifndef LLONG_MIN
		ImS64 LLONG_MIN = -9223372036854775807LL - 1;
		ImS64 LLONG_MAX = 9223372036854775807LL;
		ImU64 ULLONG_MAX = (2ULL * 9223372036854775807LL + 1);
#endif
		const char    s8_zero = 0, s8_one = 1, s8_fifty = 50, s8_min = -128, s8_max = 127;
		const ImU8    u8_zero = 0, u8_one = 1, u8_fifty = 50, u8_min = 0, u8_max = 255;
		const short   s16_zero = 0, s16_one = 1, s16_fifty = 50, s16_min = -32768, s16_max = 32767;
		const ImU16   u16_zero = 0, u16_one = 1, u16_fifty = 50, u16_min = 0, u16_max = 65535;
		const ImS32   s32_zero = 0, s32_one = 1, s32_fifty = 50, s32_min = INT_MIN / 2, s32_max = INT_MAX / 2, s32_hi_a = INT_MAX / 2 - 100, s32_hi_b = INT_MAX / 2;
		const ImU32   u32_zero = 0, u32_one = 1, u32_fifty = 50, u32_min = 0, u32_max = UINT_MAX / 2, u32_hi_a = UINT_MAX / 2 - 100, u32_hi_b = UINT_MAX / 2;
		const ImS64   s64_zero = 0, s64_one = 1, s64_fifty = 50, s64_min = LLONG_MIN / 2, s64_max = LLONG_MAX / 2, s64_hi_a = LLONG_MAX / 2 - 100, s64_hi_b = LLONG_MAX / 2;
		const ImU64   u64_zero = 0, u64_one = 1, u64_fifty = 50, u64_min = 0, u64_max = ULLONG_MAX / 2, u64_hi_a = ULLONG_MAX / 2 - 100, u64_hi_b = ULLONG_MAX / 2;
		const float   f32_zero = 0.f, f32_one = 1.f, f32_lo_a = -10000000000.0f, f32_hi_a = +10000000000.0f;
		const double  f64_zero = 0., f64_one = 1., f64_lo_a = -1000000000000000.0, f64_hi_a = +1000000000000000.0;

		// State
		static char   s8_v = 127;
		static ImU8   u8_v = 255;
		static short  s16_v = 32767;
		static ImU16  u16_v = 65535;
		static ImS32  s32_v = -1;
		static ImU32  u32_v = (ImU32)-1;
		static ImS64  s64_v = -1;
		static ImU64  u64_v = (ImU64)-1;
		static float  f32_v = 0.123f;
		static double f64_v = 90000.01234567890123456789;

		const float drag_speed = 0.2f;
		static bool drag_clamp = false;
		ui::label(parent, "Drags:");
		ui::input_field(parent, "Clamp integers to 0..50", drag_clamp); ImGui::SameLine(); HelpMarker("As with every widgets in dear imgui, we never modify values unless there is a user interaction.\nYou can override the clamping limits by using CTRL+Click to input a value.");
		ImGui::DragScalar("drag s8", ImGuiDataType_S8, &s8_v, drag_speed, drag_clamp ? &s8_zero : NULL, drag_clamp ? &s8_fifty : NULL);
		ImGui::DragScalar("drag u8", ImGuiDataType_U8, &u8_v, drag_speed, drag_clamp ? &u8_zero : NULL, drag_clamp ? &u8_fifty : NULL, "%u ms");
		ImGui::DragScalar("drag s16", ImGuiDataType_S16, &s16_v, drag_speed, drag_clamp ? &s16_zero : NULL, drag_clamp ? &s16_fifty : NULL);
		ImGui::DragScalar("drag u16", ImGuiDataType_U16, &u16_v, drag_speed, drag_clamp ? &u16_zero : NULL, drag_clamp ? &u16_fifty : NULL, "%u ms");
		ImGui::DragScalar("drag s32", ImGuiDataType_S32, &s32_v, drag_speed, drag_clamp ? &s32_zero : NULL, drag_clamp ? &s32_fifty : NULL);
		ImGui::DragScalar("drag u32", ImGuiDataType_U32, &u32_v, drag_speed, drag_clamp ? &u32_zero : NULL, drag_clamp ? &u32_fifty : NULL, "%u ms");
		ImGui::DragScalar("drag s64", ImGuiDataType_S64, &s64_v, drag_speed, drag_clamp ? &s64_zero : NULL, drag_clamp ? &s64_fifty : NULL);
		ImGui::DragScalar("drag u64", ImGuiDataType_U64, &u64_v, drag_speed, drag_clamp ? &u64_zero : NULL, drag_clamp ? &u64_fifty : NULL);
		ImGui::DragScalar("drag float", ImGuiDataType_Float, &f32_v, 0.005f, &f32_zero, &f32_one, "%f", 1.0f);
		ImGui::DragScalar("drag float ^2", ImGuiDataType_Float, &f32_v, 0.005f, &f32_zero, &f32_one, "%f", 2.0f); ImGui::SameLine(); HelpMarker("You can use the 'power' parameter to increase tweaking precision on one side of the range.");
		ImGui::DragScalar("drag double", ImGuiDataType_Double, &f64_v, 0.0005f, &f64_zero, NULL, "%.10f grams", 1.0f);
		ImGui::DragScalar("drag double ^2", ImGuiDataType_Double, &f64_v, 0.0005f, &f64_zero, &f64_one, "0 < %.10f < 1", 2.0f);

		ui::label(parent, "Sliders");
		ImGui::SliderScalar("slider s8 full", ImGuiDataType_S8, &s8_v, &s8_min, &s8_max, "%d");
		ImGui::SliderScalar("slider u8 full", ImGuiDataType_U8, &u8_v, &u8_min, &u8_max, "%u");
		ImGui::SliderScalar("slider s16 full", ImGuiDataType_S16, &s16_v, &s16_min, &s16_max, "%d");
		ImGui::SliderScalar("slider u16 full", ImGuiDataType_U16, &u16_v, &u16_min, &u16_max, "%u");
		ImGui::SliderScalar("slider s32 low", ImGuiDataType_S32, &s32_v, &s32_zero, &s32_fifty, "%d");
		ImGui::SliderScalar("slider s32 high", ImGuiDataType_S32, &s32_v, &s32_hi_a, &s32_hi_b, "%d");
		ImGui::SliderScalar("slider s32 full", ImGuiDataType_S32, &s32_v, &s32_min, &s32_max, "%d");
		ImGui::SliderScalar("slider u32 low", ImGuiDataType_U32, &u32_v, &u32_zero, &u32_fifty, "%u");
		ImGui::SliderScalar("slider u32 high", ImGuiDataType_U32, &u32_v, &u32_hi_a, &u32_hi_b, "%u");
		ImGui::SliderScalar("slider u32 full", ImGuiDataType_U32, &u32_v, &u32_min, &u32_max, "%u");
		ImGui::SliderScalar("slider s64 low", ImGuiDataType_S64, &s64_v, &s64_zero, &s64_fifty, "%I64d");
		ImGui::SliderScalar("slider s64 high", ImGuiDataType_S64, &s64_v, &s64_hi_a, &s64_hi_b, "%I64d");
		ImGui::SliderScalar("slider s64 full", ImGuiDataType_S64, &s64_v, &s64_min, &s64_max, "%I64d");
		ImGui::SliderScalar("slider u64 low", ImGuiDataType_U64, &u64_v, &u64_zero, &u64_fifty, "%I64u ms");
		ImGui::SliderScalar("slider u64 high", ImGuiDataType_U64, &u64_v, &u64_hi_a, &u64_hi_b, "%I64u ms");
		ImGui::SliderScalar("slider u64 full", ImGuiDataType_U64, &u64_v, &u64_min, &u64_max, "%I64u ms");
		ImGui::SliderScalar("slider float low", ImGuiDataType_Float, &f32_v, &f32_zero, &f32_one);
		ImGui::SliderScalar("slider float low^2", ImGuiDataType_Float, &f32_v, &f32_zero, &f32_one, "%.10f", 2.0f);
		ImGui::SliderScalar("slider float high", ImGuiDataType_Float, &f32_v, &f32_lo_a, &f32_hi_a, "%e");
		ImGui::SliderScalar("slider double low", ImGuiDataType_Double, &f64_v, &f64_zero, &f64_one, "%.10f grams", 1.0f);
		ImGui::SliderScalar("slider double low^2", ImGuiDataType_Double, &f64_v, &f64_zero, &f64_one, "%.10f", 2.0f);
		ImGui::SliderScalar("slider double high", ImGuiDataType_Double, &f64_v, &f64_lo_a, &f64_hi_a, "%e grams", 1.0f);

		static bool inputs_step = true;
		ui::label(parent, "Inputs");
		ui::input_field(parent, "Show step buttons", inputs_step);
		ImGui::InputScalar("input s8", ImGuiDataType_S8, &s8_v, inputs_step ? &s8_one : NULL, NULL, "%d");
		ImGui::InputScalar("input u8", ImGuiDataType_U8, &u8_v, inputs_step ? &u8_one : NULL, NULL, "%u");
		ImGui::InputScalar("input s16", ImGuiDataType_S16, &s16_v, inputs_step ? &s16_one : NULL, NULL, "%d");
		ImGui::InputScalar("input u16", ImGuiDataType_U16, &u16_v, inputs_step ? &u16_one : NULL, NULL, "%u");
		ImGui::InputScalar("input s32", ImGuiDataType_S32, &s32_v, inputs_step ? &s32_one : NULL, NULL, "%d");
		ImGui::InputScalar("input s32 hex", ImGuiDataType_S32, &s32_v, inputs_step ? &s32_one : NULL, NULL, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
		ImGui::InputScalar("input u32", ImGuiDataType_U32, &u32_v, inputs_step ? &u32_one : NULL, NULL, "%u");
		ImGui::InputScalar("input u32 hex", ImGuiDataType_U32, &u32_v, inputs_step ? &u32_one : NULL, NULL, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
		ImGui::InputScalar("input s64", ImGuiDataType_S64, &s64_v, inputs_step ? &s64_one : NULL);
		ImGui::InputScalar("input u64", ImGuiDataType_U64, &u64_v, inputs_step ? &u64_one : NULL);
		ImGui::InputScalar("input float", ImGuiDataType_Float, &f32_v, inputs_step ? &f32_one : NULL);
		ImGui::InputScalar("input double", ImGuiDataType_Double, &f64_v, inputs_step ? &f64_one : NULL);

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Multi-component Widgets"))
	{
		static float vec4f[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
		static int vec4i[4] = { 1, 5, 100, 255 };

		ImGui::InputFloat2("input float2", vec4f);
		ImGui::DragFloat2("drag float2", vec4f, 0.01f, 0.0f, 1.0f);
		ui::float2_slider(parent, "slider float2", vec4f, 0.0f, 1.0f);
		ImGui::InputInt2("input int2", vec4i);
		ImGui::DragInt2("drag int2", vec4i, 1, 0, 255);
		ui::slider_field<int>(parent, 2("slider int2", vec4i, 0, 255);
		ImGui::Spacing();

		ImGui::InputFloat3("input float3", vec4f);
		ImGui::DragFloat3("drag float3", vec4f, 0.01f, 0.0f, 1.0f);
		ImGui::SliderFloat3("slider float3", vec4f, 0.0f, 1.0f);
		ImGui::InputInt3("input int3", vec4i);
		ImGui::DragInt3("drag int3", vec4i, 1, 0, 255);
		ui::slider_field<int>(parent, 3("slider int3", vec4i, 0, 255);
		ImGui::Spacing();

		ImGui::InputFloat4("input float4", vec4f);
		ImGui::DragFloat4("drag float4", vec4f, 0.01f, 0.0f, 1.0f);
		ImGui::SliderFloat4("slider float4", vec4f, 0.0f, 1.0f);
		ImGui::InputInt4("input int4", vec4i);
		ImGui::DragInt4("drag int4", vec4i, 1, 0, 255);
		ui::slider_field<int>(parent, 4("slider int4", vec4i, 0, 255);

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Vertical Sliders"))
	{
		const float spacing = 4;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, vec2(spacing, spacing));

		static int int_value = 0;
		ImGui::VSliderInt("##int", vec2(18, 160), &int_value, 0, 5);
		ImGui::SameLine();

		static float values[7] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f };
		ImGui::PushID("set1");
		for(int i = 0; i < 7; i++)
		{
			if(i > 0) ImGui::SameLine();
			ImGui::PushID(i);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, (vec4)ImColor::HSV(i / 7.0f, 0.5f, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (vec4)ImColor::HSV(i / 7.0f, 0.6f, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (vec4)ImColor::HSV(i / 7.0f, 0.7f, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_SliderGrab, (vec4)ImColor::HSV(i / 7.0f, 0.9f, 0.9f));
			ImGui::VSliderFloat("##v", vec2(18, 160), &values[i], 0.0f, 1.0f, "");
			if(ImGui::IsItemActive() || ImGui::IsItemHovered())
				ImGui::SetTooltip("%.3f", values[i]);
			ImGui::PopStyleColor(4);
			ImGui::PopID();
		}
		ImGui::PopID();

		ImGui::SameLine();
		ImGui::PushID("set2");
		static float values2[4] = { 0.20f, 0.80f, 0.40f, 0.25f };
		const int rows = 3;
		const vec2 small_slider_size(18, (160.0f - (rows - 1)*spacing) / rows);
		for(int nx = 0; nx < 4; nx++)
		{
			if(nx > 0) ImGui::SameLine();
			ImGui::BeginGroup();
			for(int ny = 0; ny < rows; ny++)
			{
				ImGui::PushID(nx*rows + ny);
				ImGui::VSliderFloat("##v", small_slider_size, &values2[nx], 0.0f, 1.0f, "");
				if(ImGui::IsItemActive() || ImGui::IsItemHovered())
					ImGui::SetTooltip("%.3f", values2[nx]);
				ImGui::PopID();
			}
			ImGui::EndGroup();
		}
		ImGui::PopID();

		ImGui::SameLine();
		ImGui::PushID("set3");
		for(int i = 0; i < 4; i++)
		{
			if(i > 0) ImGui::SameLine();
			ImGui::PushID(i);
			ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 40);
			ImGui::VSliderFloat("##v", vec2(40, 160), &values[i], 0.0f, 1.0f, "%.2f\nsec");
			ImGui::PopStyleVar();
			ImGui::PopID();
		}
		ImGui::PopID();
		ImGui::PopStyleVar();
		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Drag and Drop"))
	{
		{
			// ColorEdit widgets automatically act as drag source and drag target.
			// They are using standardized payload strings IMGUI_PAYLOAD_TYPE_COLOR_3F and IMGUI_PAYLOAD_TYPE_COLOR_4F to allow your own widgets
			// to use colors in their drag and drop interaction. Also see the demo in Color Picker -> Palette demo.
			ui::bullet(parent, "Drag and drop in standard widgets");
			ImGui::Indent();
			static float col1[3] = { 1.0f,0.0f,0.2f };
			static float col2[4] = { 0.4f,0.7f,0.0f,0.5f };
			ImGui::ColorEdit3("color 1", col1);
			ImGui::ColorEdit4("color 2", col2);
			ImGui::Unindent();
		}

		{
			ui::bullet(parent, "Drag and drop to copy/swap items");
			ImGui::Indent();
			enum Mode
			{
				Mode_Copy,
				Mode_Move,
				Mode_Swap
			};
			static int mode = 0;
			if(ui::radio_button(parent, "Copy", mode == Mode_Copy)) { mode = Mode_Copy; } ImGui::SameLine();
			if(ui::radio_button(parent, "Move", mode == Mode_Move)) { mode = Mode_Move; } ImGui::SameLine();
			if(ui::radio_button(parent, "Swap", mode == Mode_Swap)) { mode = Mode_Swap; }
			static const char* names[9] = { "Bobby", "Beatrice", "Betty", "Brianna", "Barry", "Bernard", "Bibi", "Blaine", "Bryn" };
			for(int n = 0; n < IM_ARRAYSIZE(names); n++)
			{
				ImGui::PushID(n);
				if((n % 3) != 0)
					ImGui::SameLine();
				ui::button(parent, names[n], vec2(60, 60));

				// Our buttons are both drag sources and drag targets here!
				if(ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
				{
					ImGui::SetDragDropPayload("DND_DEMO_CELL", n, sizeof(int));        // Set payload to carry the index of our item (could be anything)
					if(mode == Mode_Copy) { ui::label(parent, "Copy %s", names[n]); }        // Display preview (could be anything, e.g. when dragging an image we could decide to display the filename and a small preview of the image, etc.)
					if(mode == Mode_Move) { ui::label(parent, "Move %s", names[n]); }
					if(mode == Mode_Swap) { ui::label(parent, "Swap %s", names[n]); }
					ImGui::EndDragDropSource();
				}
				if(ImGui::BeginDragDropTarget())
				{
					if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
					{
						IM_ASSERT(payload->DataSize == sizeof(int));
						int payload_n = *(const int*)payload->Data;
						if(mode == Mode_Copy)
						{
							names[n] = names[payload_n];
						}
						if(mode == Mode_Move)
						{
							names[n] = names[payload_n];
							names[payload_n] = "";
						}
						if(mode == Mode_Swap)
						{
							const char* tmp = names[n];
							names[n] = names[payload_n];
							names[payload_n] = tmp;
						}
					}
					ImGui::EndDragDropTarget();
				}
				ImGui::PopID();
			}
			ImGui::Unindent();
		}

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(*body, "Querying Status (Active/Focused/Hovered etc.)"))
	{
		// Display the value of IsItemHovered() and other common item state functions. Note that the flags can be combined.
		// (because BulletText is an item itself and that would affect the output of IsItemHovered() we pass all state in a single call to simplify the code).
		static int item_type = 1;
		static bool b = false;
		static float col4f[4] = { 1.0f, 0.5, 0.0f, 1.0f };
		static char str[16] = {};
		ui::radio_button(parent, "Text", item_type, 0);
		ui::radio_button(parent, "Button", item_type, 1);
		ui::radio_button(parent, "Checkbox", item_type, 2);
		ui::radio_button(parent, "SliderFloat", item_type, 3);
		ui::radio_button(parent, "InputText", item_type, 4);
		ui::radio_button(parent, "ColorEdit4", item_type, 5);
		ui::radio_button(parent, "MenuItem", item_type, 6);
		ui::radio_button(parent, "TreeNode (w/ double-click)", item_type, 7);
		ui::radio_button(parent, "ListBox", item_type, 8);
		ui::separator(parent);
		bool ret = false;
		if(item_type == 0) { ui::label(parent, "ITEM: Text"); }                                              // Testing text items with no identifier/interaction
		if(item_type == 1) { ret = ui::button(parent, "ITEM: Button"); }                                    // Testing button
		if(item_type == 2) { ret = ui::input_field(parent, "ITEM: Checkbox", b); }                            // Testing checkbox
		if(item_type == 3) { ret = ui::slider_field<float>(parent, "ITEM: SliderFloat", col4f[0], 0.0f, 1.0f); }   // Testing basic item
		if(item_type == 4) { ret = ImGui::InputText("ITEM: InputText", str[0], IM_ARRAYSIZE(str)); }  // Testing input text (which handles tabbing)
		if(item_type == 5) { ret = ImGui::ColorEdit4("ITEM: ColorEdit4", col4f); }                     // Testing multi-component items (IsItemXXX flags are reported merged)
		if(item_type == 6) { ret = ui::menu_choice(parent, "ITEM: MenuItem"); }                                // Testing menu item (they use ImGuiButtonFlags_PressedOnRelease button policy)
		if(item_type == 7) { ret = ImGui::TreeNodeEx("ITEM: TreeNode w/ ImGuiTreeNodeFlags_OpenOnDoubleClick", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_NoTreePushOnOpen); } // Testing tree node with ImGuiButtonFlags_PressedOnDoubleClick button policy.
		if(item_type == 8) { const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi" }; static int current = 1; ret = ImGui::ListBox("ITEM: ListBox", current, items, IM_ARRAYSIZE(items), IM_ARRAYSIZE(items)); }
		ui::bullet(parent, 
			"Return value = %d\n"
			"IsItemFocused() = %d\n"
			"IsItemHovered() = %d\n"
			"IsItemHovered(_AllowWhenBlockedByPopup) = %d\n"
			"IsItemHovered(_AllowWhenBlockedByActiveItem) = %d\n"
			"IsItemHovered(_AllowWhenOverlapped) = %d\n"
			"IsItemHovered(_RectOnly) = %d\n"
			"IsItemActive() = %d\n"
			"IsItemEdited() = %d\n"
			"IsItemActivated() = %d\n"
			"IsItemDeactivated() = %d\n"
			"IsItemDeactivatedAfterEdit() = %d\n"
			"IsItemVisible() = %d\n"
			"IsItemClicked() = %d\n"
			"GetItemRectMin() = (%.1f, %.1f)\n"
			"GetItemRectMax() = (%.1f, %.1f)\n"
			"GetItemRectSize() = (%.1f, %.1f)",
			ret,
			ImGui::IsItemFocused(),
			ImGui::IsItemHovered(),
			ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup),
			ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
			ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlapped),
			ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly),
			ImGui::IsItemActive(),
			ImGui::IsItemEdited(),
			ImGui::IsItemActivated(),
			ImGui::IsItemDeactivated(),
			ImGui::IsItemDeactivatedAfterEdit(),
			ImGui::IsItemVisible(),
			ImGui::IsItemClicked(),
			ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y,
			ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y,
			ImGui::GetItemRectSize().x, ImGui::GetItemRectSize().y
		);

		static bool embed_all_inside_a_child_window = false;
		ui::input_field(parent, "Embed everything inside a child window (for additional testing)", embed_all_inside_a_child_window);
		if(embed_all_inside_a_child_window)
			ImGui::BeginChild("outer_child", vec2(0, ImGui::GetFontSize() * 20), true);

		// Testing IsWindowFocused() function with its various flags. Note that the flags can be combined.
		ui::bullet(parent, 
			"IsWindowFocused() = %d\n"
			"IsWindowFocused(_ChildWindows) = %d\n"
			"IsWindowFocused(_ChildWindows|_RootWindow) = %d\n"
			"IsWindowFocused(_RootWindow) = %d\n"
			"IsWindowFocused(_AnyWindow) = %d\n",
			ImGui::IsWindowFocused(),
			ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows),
			ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_RootWindow),
			ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow),
			ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow));

		// Testing IsWindowHovered() function with its various flags. Note that the flags can be combined.
		ui::bullet(parent, 
			"IsWindowHovered() = %d\n"
			"IsWindowHovered(_AllowWhenBlockedByPopup) = %d\n"
			"IsWindowHovered(_AllowWhenBlockedByActiveItem) = %d\n"
			"IsWindowHovered(_ChildWindows) = %d\n"
			"IsWindowHovered(_ChildWindows|_RootWindow) = %d\n"
			"IsWindowHovered(_ChildWindows|_AllowWhenBlockedByPopup) = %d\n"
			"IsWindowHovered(_RootWindow) = %d\n"
			"IsWindowHovered(_AnyWindow) = %d\n",
			ImGui::IsWindowHovered(),
			ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup),
			ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
			ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows),
			ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow),
			ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_AllowWhenBlockedByPopup),
			ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow),
			ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow));

		ImGui::BeginChild("child", vec2(0, 50), true);
		ui::label(parent, "This is another child window for testing the _ChildWindows flag.");
		ImGui::EndChild();
		if(embed_all_inside_a_child_window)
			ImGui::EndChild();

		// Calling IsItemHovered() after begin returns the hovered status of the title bar.
		// This is useful in particular if you want to create a context menu (with BeginPopupContextItem) associated to the title bar of a window.
		static bool test_window = false;
		ui::input_field(parent, "Hovered/Active tests after Begin() for title bar testing", test_window);
		if(test_window)
		{
			ImGui::Begin("Title bar Hovered/Active tests", test_window);
			if(ImGui::BeginPopupContextItem()) // <-- This is using IsItemHovered()
			{
				if(ui::menu_choice(parent, "Close")) { test_window = false; }
				ImGui::EndPopup();
			}
			ui::label(parent, 
				"IsItemHovered() after begin = %d (== is title bar hovered)\n"
				"IsItemActive() after begin = %d (== is window being clicked/moved)\n",
				ImGui::IsItemHovered(), ImGui::IsItemActive());
			ImGui::End();
		}

		//ImGui::TreePop();
	}
#endif

}

#if 0
static void ShowDemoWindowLayout()
{
	if(!ui::expandbox(parent, "Layout"))
		return;

	if(Widget& n = ui::tree_node(parent, "Child windows"))
	{
		HelpMarker("Use child windows to begin into a self-contained independent scrolling/clipping regions within a host window.");
		static bool disable_mouse_wheel = false;
		static bool disable_menu = false;
		ui::input_field(parent, "Disable Mouse Wheel", disable_mouse_wheel);
		ui::input_field(parent, "Disable Menu", disable_menu);

		static int line = 50;
		bool goto_line = ui::button(parent, "Goto");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		goto_line |= ui::number_field<int>(parent, "##Line", line, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue);

		// Child 1: no border, enable horizontal scrollbar
		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar | (disable_mouse_wheel ? ImGuiWindowFlags_NoScrollWithMouse : 0);
			ImGui::BeginChild("Child1", vec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 260), false, window_flags);
			for(int i = 0; i < 100; i++)
			{
				ui::label(parent, "%04d: scrollable region", i);
				if(goto_line && line == i)
					ImGui::SetScrollHereY();
			}
			if(goto_line && line >= 100)
				ImGui::SetScrollHereY();
			ImGui::EndChild();
		}

		ImGui::SameLine();

		// Child 2: rounded border
		{
			ImGuiWindowFlags window_flags = (disable_mouse_wheel ? ImGuiWindowFlags_NoScrollWithMouse : 0) | (disable_menu ? 0 : ImGuiWindowFlags_MenuBar);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			ImGui::BeginChild("Child2", vec2(0, 260), true, window_flags);
			if(!disable_menu && ImGui::BeginMenuBar())
			{
				if(ImGui::BeginMenu("Menu"))
				{
					ShowExampleMenuFile();
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			Widget& cols = ui::columns(parent, 2);
			for(int i = 0; i < 100; i++)
			{
				char buf[32];
				sprintf(buf, "%03d", i);
				ui::button(parent, buf, vec2(-1.0f, 0.0f));
				ImGui::NextColumn();
			}
			ImGui::EndChild();
			ImGui::PopStyleVar();
		}

		ui::separator(parent);

		// Demonstrate a few extra things
		// - Changing ImGuiCol_ChildBg (which is transparent black in default styles)
		// - Using SetCursorPos() to position the child window (because the child window is an item from the POV of the parent window)
		//   You can also call SetNextWindowPos() to position the child window. The parent window will effectively layout from this position.
		// - Using ImGui::GetItemRectMin/Max() to query the "item" state (because the child window is an item from the POV of the parent window)
		//   See "Widgets" -> "Querying Status (Active/Focused/Hovered etc.)" section for more details about this.
		{
			ImGui::SetCursorPosX(50);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(255, 0, 0, 100));
			ImGui::BeginChild("blah", vec2(200, 100), true, ImGuiWindowFlags_None);
			for(int n = 0; n < 50; n++)
				ui::label(parent, "Some test %d", n);
			ImGui::EndChild();
			vec2 child_rect_min = ImGui::GetItemRectMin();
			vec2 child_rect_max = ImGui::GetItemRectMax();
			ImGui::PopStyleColor();
			ui::label(parent, "Rect of child window is: (%.0f,%.0f) (%.0f,%.0f)", child_rect_min.x, child_rect_min.y, child_rect_max.x, child_rect_max.y);
		}

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Widgets Width"))
	{
		// Use SetNextItemWidth() to set the width of a single upcoming item.
		// Use PushItemWidth()/PopItemWidth() to set the width of a group of items.
		static float f = 0.0f;
		ui::label(parent, "SetNextItemWidth/PushItemWidth(100)");
		ImGui::SameLine(); HelpMarker("Fixed width.");
		ImGui::SetNextItemWidth(100);
		ui::drag_field<float>(parent, "float##1", f);

		ui::label(parent, "SetNextItemWidth/PushItemWidth(GetWindowWidth() * 0.5f)");
		ImGui::SameLine(); HelpMarker("Half of window width.");
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.5f);
		ui::drag_field<float>(parent, "float##2", f);

		ui::label(parent, "SetNextItemWidth/PushItemWidth(GetContentRegionAvailWidth() * 0.5f)");
		ImGui::SameLine(); HelpMarker("Half of available width.\n(~ right-cursor_pos)\n(works within a column set)");
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() * 0.5f);
		ui::drag_field<float>(parent, "float##3", f);

		ui::label(parent, "SetNextItemWidth/PushItemWidth(-100)");
		ImGui::SameLine(); HelpMarker("Align to right edge minus 100");
		ImGui::SetNextItemWidth(-100);
		ui::drag_field<float>(parent, "float##4", f);

		// Demonstrate using PushItemWidth to surround three items. Calling SetNextItemWidth() before each of them would have the same effect.
		ui::label(parent, "SetNextItemWidth/PushItemWidth(-1)");
		ImGui::SameLine(); HelpMarker("Align to right edge");
		ImGui::PushItemWidth(-1);
		ui::drag_field<float>(parent, "float##5a", f);
		ui::drag_field<float>(parent, "float##5b", f);
		ui::drag_field<float>(parent, "float##5c", f);
		ImGui::PopItemWidth();

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Basic Horizontal Layout"))
	{
		ui::text(parent, "(Use ImGui::SameLine() to keep adding items to the right of the preceding item)");

		// Text
		ui::label(parent, "Two items: Hello"); ImGui::SameLine();
		ImGui::TextColored(vec4(1, 1, 0, 1), "Sailor");

		// Adjust spacing
		ui::label(parent, "More spacing: Hello"); ImGui::SameLine(0, 20);
		ImGui::TextColored(vec4(1, 1, 0, 1), "Sailor");

		// Button
		ImGui::AlignTextToFramePadding();
		ui::label(parent, "Normal buttons"); ImGui::SameLine();
		ui::button(parent, "Banana"); ImGui::SameLine();
		ui::button(parent, "Apple"); ImGui::SameLine();
		ui::button(parent, "Corniflower");

		// Button
		ui::label(parent, "Small buttons"); ImGui::SameLine();
		ui::button(parent, "Like this one"); ImGui::SameLine();
		ui::label(parent, "can fit within a text block.");

		// Aligned to arbitrary position. Easy/cheap column.
		ui::label(parent, "Aligned");
		ImGui::SameLine(150); ui::label(parent, "x=150");
		ImGui::SameLine(300); ui::label(parent, "x=300");
		ui::label(parent, "Aligned");
		ImGui::SameLine(150); ui::button(parent, "x=150");
		ImGui::SameLine(300); ui::button(parent, "x=300");

		// Checkbox
		static bool c1 = false, c2 = false, c3 = false, c4 = false;
		Widget& row = ui::row(parent);
		ui::input_field(row, "My", c1);
		ui::input_field(row, "Tailor", c2);
		ui::input_field(row, "Is", c3);
		ui::input_field(row, "Rich", c4);

		// Various
		static float f0 = 1.0f, f1 = 2.0f, f2 = 3.0f;
		ImGui::PushItemWidth(80);
		const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD" };
		static int item = -1;
		Widget& row = ui::row(parent);
		ui::dropdown_field(parent, "Combo", item, items, IM_ARRAYSIZE(items));
		ui::slider_field<float>(row, "X", { f0, 0.0f, 5.0f });
		ui::slider_field<float>(row, "Y", { f1, 0.0f, 5.0f });
		ui::slider_field<float>(row, "Z", { f2, 0.0f, 5.0f });
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(80);
		ui::label(parent, "Lists:");
		static int selection[4] = { 0, 1, 2, 3 };
		for(int i = 0; i < 4; i++)
		{
			if(i > 0) ImGui::SameLine();
			ImGui::PushID(i);
			ImGui::ListBox("", selection[i], items, IM_ARRAYSIZE(items));
			ImGui::PopID();
			//if (ImGui::IsItemHovered()) ImGui::SetTooltip("ListBox %d hovered", i);
		}
		ImGui::PopItemWidth();

		// Dummy
		vec2 button_sz(40, 40);
		ui::button(parent, "A", button_sz); ImGui::SameLine();
		ImGui::Dummy(button_sz); ImGui::SameLine();
		ui::button(parent, "B", button_sz);

		// Manually wrapping (we should eventually provide this as an automatic layout feature, but for now you can do it manually)
		ui::label(parent, "Manually wrapping:");
		ImGuiStyle& style = ImGui::GetStyle();
		int buttons_count = 20;
		float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
		for(int n = 0; n < buttons_count; n++)
		{
			ImGui::PushID(n);
			ui::button(parent, "Box", button_sz);
			float last_button_x2 = ImGui::GetItemRectMax().x;
			float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
			if(n + 1 < buttons_count && next_button_x2 < window_visible_x2)
				ImGui::SameLine();
			ImGui::PopID();
		}

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Tabs"))
	{
		if(Widget& n = ui::tree_node(parent, "Basic"))
		{
			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			if(ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
			{
				if(ImGui::BeginTabItem("Avocado"))
				{
					ui::label(parent, "This is the Avocado tab!\nblah blah blah blah blah");
					ImGui::EndTabItem();
				}
				if(ImGui::BeginTabItem("Broccoli"))
				{
					ui::label(parent, "This is the Broccoli tab!\nblah blah blah blah blah");
					ImGui::EndTabItem();
				}
				if(ImGui::BeginTabItem("Cucumber"))
				{
					ui::label(parent, "This is the Cucumber tab!\nblah blah blah blah blah");
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ui::separator(parent);
			//ImGui::TreePop();
		}

		if(Widget& n = ui::tree_node(parent, "Advanced & Close Button"))
		{
			// Expose a couple of the available flags. In most cases you may just call BeginTabBar() with no flags (0).
			static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
			ui::flag_field(parent, "ImGuiTabBarFlags_Reorderable", (uint32_t&)tab_bar_flags, ImGuiTabBarFlags_Reorderable);
			ui::flag_field(parent, "ImGuiTabBarFlags_AutoSelectNewTabs", (uint32_t&)tab_bar_flags, ImGuiTabBarFlags_AutoSelectNewTabs);
			ui::flag_field(parent, "ImGuiTabBarFlags_TabListPopupButton", (uint32_t&)tab_bar_flags, ImGuiTabBarFlags_TabListPopupButton);
			ui::flag_field(parent, "ImGuiTabBarFlags_NoCloseWithMiddleMouseButton", (uint32_t&)tab_bar_flags, ImGuiTabBarFlags_NoCloseWithMiddleMouseButton);
			if((tab_bar_flags & ImGuiTabBarFlags_FittingPolicyMask_) == 0)
				tab_bar_flags |= ImGuiTabBarFlags_FittingPolicyDefault_;
			if(ui::flag_field(parent, "ImGuiTabBarFlags_FittingPolicyResizeDown", (uint32_t&)tab_bar_flags, ImGuiTabBarFlags_FittingPolicyResizeDown))
				tab_bar_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyResizeDown);
			if(ui::flag_field(parent, "ImGuiTabBarFlags_FittingPolicyScroll", (uint32_t&)tab_bar_flags, ImGuiTabBarFlags_FittingPolicyScroll))
				tab_bar_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyScroll);

			// Tab Bar
			const char* names[4] = { "Artichoke", "Beetroot", "Celery", "Daikon" };
			static bool opened[4] = { true, true, true, true }; // Persistent user state
			for(int n = 0; n < IM_ARRAYSIZE(opened); n++)
			{
				if(n > 0) { ImGui::SameLine(); }
				ui::input_field(parent, names[n], &opened[n]);
			}

			// Passing a bool* to BeginTabItem() is similar to passing one to Begin(): the underlying bool will be set to false when the tab is closed.
			if(ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
			{
				for(int n = 0; n < IM_ARRAYSIZE(opened); n++)
					if(opened[n] && ImGui::BeginTabItem(names[n], &opened[n]))
					{
						ui::label(parent, "This is the %s tab!", names[n]);
						if(n & 1)
							ui::label(parent, "I am an odd tab.");
						ImGui::EndTabItem();
					}
				ImGui::EndTabBar();
			}
			ui::separator(parent);
			//ImGui::TreePop();
		}
		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Groups"))
	{
		HelpMarker("Using ImGui::BeginGroup()/EndGroup() to layout items. BeginGroup() basically locks the horizontal position. EndGroup() bundles the whole group so that you can use functions such as IsItemHovered() on it.");
		ImGui::BeginGroup();
		{
			ImGui::BeginGroup();
			ui::button(parent, "AAA");
			ImGui::SameLine();
			ui::button(parent, "BBB");
			ImGui::SameLine();
			ImGui::BeginGroup();
			ui::button(parent, "CCC");
			ui::button(parent, "DDD");
			ImGui::EndGroup();
			ImGui::SameLine();
			ui::button(parent, "EEE");
			ImGui::EndGroup();
			if(ImGui::IsItemHovered())
				ImGui::SetTooltip("First group hovered");
		}
		// Capture the group size and create widgets using the same size
		vec2 size = ImGui::GetItemRectSize();
		const float values[5] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f };
		ImGui::PlotHistogram("##values", values, IM_ARRAYSIZE(values), 0, NULL, 0.0f, 1.0f, size);

		ui::button(parent, "ACTION", vec2((size.x - ImGui::GetStyle().ItemSpacing.x)*0.5f, size.y));
		ImGui::SameLine();
		ui::button(parent, "REACTION", vec2((size.x - ImGui::GetStyle().ItemSpacing.x)*0.5f, size.y));
		ImGui::EndGroup();
		ImGui::SameLine();

		ui::button(parent, "LEVERAGE\nBUZZWORD", size);
		ImGui::SameLine();

		if(ImGui::ListBoxHeader("List", size))
		{
			ui::selectable(parent, "Selected", true);
			ui::selectable(parent, "Not Selected", false);
			ImGui::ListBoxFooter();
		}

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Text Baseline Alignment"))
	{
		HelpMarker("This is testing the vertical alignment that gets applied on text to keep it aligned with widgets. Lines only composed of text or \"small\" widgets fit in less vertical spaces than lines with normal widgets.");

		ui::label(parent, "One\nTwo\nThree"); ImGui::SameLine();
		ui::label(parent, "Hello\nWorld"); ImGui::SameLine();
		ui::label(parent, "Banana");

		ui::label(parent, "Banana"); ImGui::SameLine();
		ui::label(parent, "Hello\nWorld"); ImGui::SameLine();
		ui::label(parent, "One\nTwo\nThree");

		ui::button(parent, "HOP##1"); ImGui::SameLine();
		ui::label(parent, "Banana"); ImGui::SameLine();
		ui::label(parent, "Hello\nWorld"); ImGui::SameLine();
		ui::label(parent, "Banana");

		ui::button(parent, "HOP##2"); ImGui::SameLine();
		ui::label(parent, "Hello\nWorld"); ImGui::SameLine();
		ui::label(parent, "Banana");

		ui::button(parent, "TEST##1"); ImGui::SameLine();
		ui::label(parent, "TEST"); ImGui::SameLine();
		ui::button(parent, "TEST##2");

		ImGui::AlignTextToFramePadding(); // If your line starts with text, call this to align it to upcoming widgets.
		ui::label(parent, "Text aligned to Widget"); ImGui::SameLine();
		ui::button(parent, "Widget##1"); ImGui::SameLine();
		ui::label(parent, "Widget"); ImGui::SameLine();
		ui::button(parent, "Widget##2"); ImGui::SameLine();
		ui::button(parent, "Widget##3");

		// Tree
		const float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ui::button(parent, "Button##1");
		ImGui::SameLine(0.0f, spacing);
		if(Widget& n = ui::tree_node(parent, "Node##1")) { for(int i = 0; i < 6; i++) ui::bullet(parent, "Item %d..", i); //ImGui::TreePop(); }    // Dummy tree data

		ImGui::AlignTextToFramePadding();         // Vertically align text node a bit lower so it'll be vertically centered with upcoming widget. Otherwise you can use SmallButton (smaller fit).
		bool node_open = ImGui::TreeNode("Node##2");  // Common mistake to avoid: if we want to SameLine after TreeNode we need to do it before we add child content.
		ImGui::SameLine(0.0f, spacing); ui::button(parent, "Button##2");
		if(node_open) { for(int i = 0; i < 6; i++) ui::bullet(parent, "Item %d..", i); //ImGui::TreePop(); }   // Dummy tree data

		// Bullet
		ui::button(parent, "Button##3");
		ImGui::SameLine(0.0f, spacing);
		ui::bullet(parent, "Bullet text");

		ImGui::AlignTextToFramePadding();
		ui::bullet(parent, "Node");
		ImGui::SameLine(0.0f, spacing); ui::button(parent, "Button##4");

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Scrolling"))
	{
		HelpMarker("Use SetScrollHereY() or SetScrollFromPosY() to scroll to a given position.");

		static bool track = true;
		static int track_line = 50, scroll_to_px = 200;
		ui::input_field(parent, "Track", track);
		ImGui::PushItemWidth(100);
		ImGui::SameLine(130); track |= ui::drag_field<int>(parent, "##line", track_line, 0.25f, 0, 99, "Line = %d");
		bool scroll_to = ui::button(parent, "Scroll To Pos");
		ImGui::SameLine(130); scroll_to |= ui::drag_field<int>(parent, "##pos_y", scroll_to_px, 1.00f, 0, 9999, "Y = %d px");
		ImGui::PopItemWidth();
		if(scroll_to) track = false;

		for(int i = 0; i < 5; i++)
		{
			if(i > 0) ImGui::SameLine();
			ImGui::BeginGroup();
			ui::label(parent, "%s", i == 0 ? "Top" : i == 1 ? "25%" : i == 2 ? "Center" : i == 3 ? "75%" : "Bottom");
			ImGui::BeginChild(ImGui::GetID((void*)(intptr_t)i), vec2(ImGui::GetWindowWidth() * 0.17f, 200.0f), true);
			if(scroll_to)
				ImGui::SetScrollFromPosY(ImGui::GetCursorStartPos().y + scroll_to_px, i * 0.25f);
			for(int line = 0; line < 100; line++)
			{
				if(track && line == track_line)
				{
					ImGui::TextColored(vec4(1, 1, 0, 1), "Line %d", line);
					ImGui::SetScrollHereY(i * 0.25f); // 0.0f:top, 0.5f:center, 1.0f:bottom
				}
				else
				{
					ui::label(parent, "Line %d", line);
				}
			}
			float scroll_y = ImGui::GetScrollY(), scroll_max_y = ImGui::GetScrollMaxY();
			ImGui::EndChild();
			ui::label(parent, "%.0f/%0.f", scroll_y, scroll_max_y);
			ImGui::EndGroup();
		}
		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Horizontal Scrolling"))
	{
		HelpMarker("Horizontal scrolling for a window has to be enabled explicitly via the ImGuiWindowFlags_HorizontalScrollbar flag.\n\nYou may want to explicitly specify content width by calling SetNextWindowContentWidth() before Begin().");
		static int lines = 7;
		ui::slider_field<int>(parent, ("Lines", lines, 1, 15);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, vec2(2.0f, 1.0f));
		ImGui::BeginChild("scrolling", vec2(0, ImGui::GetFrameHeightWithSpacing() * 7 + 30), true, ImGuiWindowFlags_HorizontalScrollbar);
		for(int line = 0; line < lines; line++)
		{
			// Display random stuff (for the sake of this trivial demo we are using basic Button+SameLine. If you want to create your own time line for a real application you may be better off
			// manipulating the cursor position yourself, aka using SetCursorPos/SetCursorScreenPos to position the widgets yourself. You may also want to use the lower-level ImDrawList API)
			int num_buttons = 10 + ((line & 1) ? line * 9 : line * 3);
			for(int n = 0; n < num_buttons; n++)
			{
				if(n > 0) ImGui::SameLine();
				ImGui::PushID(n + line * 1000);
				char num_buf[16];
				sprintf(num_buf, "%d", n);
				const char* label = (!(n % 15)) ? "FizzBuzz" : (!(n % 3)) ? "Fizz" : (!(n % 5)) ? "Buzz" : num_buf;
				float hue = n * 0.05f;
				ImGui::PushStyleColor(ImGuiCol_Button, (vec4)ImColor::HSV(hue, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (vec4)ImColor::HSV(hue, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (vec4)ImColor::HSV(hue, 0.8f, 0.8f));
				ui::button(parent, label, vec2(40.0f + sinf((float)(line + n)) * 20.0f, 0.0f));
				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
		}
		float scroll_x = ImGui::GetScrollX();
		float scroll_max_x = ImGui::GetScrollMaxX();
		ImGui::EndChild();
		ImGui::PopStyleVar(2);
		float scroll_x_delta = 0.0f;
		ui::button(parent, "<<"); if(ImGui::IsItemActive()) { scroll_x_delta = -ImGui::GetIO().DeltaTime * 1000.0f; } ImGui::SameLine();
		ui::label(parent, "Scroll from code"); ImGui::SameLine();
		ui::button(parent, ">>"); if(ImGui::IsItemActive()) { scroll_x_delta = +ImGui::GetIO().DeltaTime * 1000.0f; } ImGui::SameLine();
		ui::label(parent, "%.0f/%.0f", scroll_x, scroll_max_x);
		if(scroll_x_delta != 0.0f)
		{
			ImGui::BeginChild("scrolling"); // Demonstrate a trick: you can use Begin to set yourself in the context of another window (here we are already out of your child window)
			ImGui::SetScrollX(ImGui::GetScrollX() + scroll_x_delta);
			ImGui::EndChild();
		}
		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Clipping"))
	{
		static vec2 size(100, 100), offset(50, 20);
		ui::text(parent, "On a per-widget basis we are occasionally clipping text CPU-side if it won't fit in its frame. Otherwise we are doing coarser clipping + passing a scissor rectangle to the renderer. The system is designed to try minimizing both execution and CPU/GPU rendering cost.");
		ImGui::DragFloat2("size", (float*)&size, 0.5f, 1.0f, 200.0f, "%.0f");
		ui::text(parent, "(Click and drag)");
		vec2 pos = ImGui::GetCursorScreenPos();
		vec4 clip_rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
		ImGui::InvisibleButton("##dummy", size);
		if(ImGui::IsItemActive() && ImGui::IsMouseDragging()) { offset.x += ImGui::GetIO().MouseDelta.x; offset.y += ImGui::GetIO().MouseDelta.y; }
		ImGui::GetWindowDrawList()->AddRectFilled(pos, vec2(pos.x + size.x, pos.y + size.y), IM_COL32(90, 90, 120, 255));
		ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize()*2.0f, vec2(pos.x + offset.x, pos.y + offset.y), IM_COL32(255, 255, 255, 255), "Line 1 hello\nLine 2 clip me!", NULL, 0.0f, &clip_rect);
		//ImGui::TreePop();
	}
}

static void ShowDemoWindowPopups(Widget& parent)
{
	if(!ui::expandbox(parent, "Popups & Modal windows"))
		return;

	// The properties of popups windows are:
	// - They block normal mouse hovering detection outside them. (*)
	// - Unless modal, they can be closed by clicking anywhere outside them, or by pressing ESCAPE.
	// - Their visibility state (~bool) is held internally by imgui instead of being held by the programmer as we are used to with regular Begin() calls.
	//   User can manipulate the visibility state by calling OpenPopup().
	// (*) One can use IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) to bypass it and detect hovering even when normally blocked by a popup.
	// Those three properties are connected. The library needs to hold their visibility state because it can close popups at any time.

	// Typical use for regular windows:
	//   bool my_tool_is_active = false; if (ui::button(parent, "Open")) my_tool_is_active = true; [...] if (my_tool_is_active) Begin("My Tool", my_tool_is_active) { [...] } End();
	// Typical use for popups:
	//   if (ui::button(parent, "Open")) ImGui::OpenPopup("MyPopup"); if (ImGui::BeginPopup("MyPopup") { [...] EndPopup(); }

	// With popups we have to go through a library call (here OpenPopup) to manipulate the visibility state.
	// This may be a bit confusing at first but it should quickly make sense. Follow on the examples below.

	if(Widget& n = ui::tree_node(parent, "Popups"))
	{
		ui::text(parent, "When a popup is active, it inhibits interacting with windows that are behind the popup. Clicking outside the popup closes it.");

		static int selected_fish = -1;
		const char* names[] = { "Bream", "Haddock", "Mackerel", "Pollock", "Tilefish" };
		static bool toggles[] = { true, false, false, false, false };

		// Simple selection popup
		// (If you want to show the current selection inside the Button itself, you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
		if(ui::button(parent, "Select.."))
			ImGui::OpenPopup("my_select_popup");
		ImGui::SameLine();
		ImGui::TextUnformatted(selected_fish == -1 ? "<None>" : names[selected_fish]);
		if(ImGui::BeginPopup("my_select_popup"))
		{
			ui::label(parent, "Aquarium");
			ui::separator(parent);
			for(int i = 0; i < IM_ARRAYSIZE(names); i++)
				if(ui::selectable(parent, names[i]))
					selected_fish = i;
			ImGui::EndPopup();
		}

		// Showing a menu with toggles
		if(ui::button(parent, "Toggle.."))
			ImGui::OpenPopup("my_toggle_popup");
		if(ImGui::BeginPopup("my_toggle_popup"))
		{
			for(int i = 0; i < IM_ARRAYSIZE(names); i++)
				ui::menu_choice(parent, names[i], "", toggles[i]);
			if(ImGui::BeginMenu("Sub-menu"))
			{
				ui::menu_choice(parent, "Click me");
				ImGui::EndMenu();
			}

			ui::separator(parent);
			ui::label(parent, "Tooltip here");
			if(ImGui::IsItemHovered())
				ImGui::SetTooltip("I am a tooltip over a popup");

			if(ui::button(parent, "Stacked Popup"))
				ImGui::OpenPopup("another popup");
			if(ImGui::BeginPopup("another popup"))
			{
				for(int i = 0; i < IM_ARRAYSIZE(names); i++)
					ui::menu_choice(parent, names[i], "", toggles[i]);
				if(ImGui::BeginMenu("Sub-menu"))
				{
					ui::menu_choice(parent, "Click me");
					ImGui::EndMenu();
				}
				ImGui::EndPopup();
			}
			ImGui::EndPopup();
		}

		// Call the more complete ShowExampleMenuFile which we use in various places of this demo
		if(ui::button(parent, "File Menu.."))
			ImGui::OpenPopup("my_file_popup");
		if(ImGui::BeginPopup("my_file_popup"))
		{
			ShowExampleMenuFile();
			ImGui::EndPopup();
		}

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Context menus"))
	{
		// BeginPopupContextItem() is a helper to provide common/simple popup behavior of essentially doing:
		//    if (IsItemHovered() && IsMouseReleased(0))
		//       OpenPopup(id);
		//    return BeginPopup(id);
		// For more advanced uses you may want to replicate and cuztomize this code. This the comments inside BeginPopupContextItem() implementation.
		static float value = 0.5f;
		ui::label(parent, "Value = %.3f (<-- right-click here)", value);
		if(ImGui::BeginPopupContextItem("item context menu"))
		{
			if(ui::selectable(parent, "Set to zero")) value = 0.0f;
			if(ui::selectable(parent, "Set to PI")) value = 3.1415f;
			ImGui::SetNextItemWidth(-1);
			ui::drag_field<float>(parent, "##Value", value, 0.1f, 0.0f, 0.0f);
			ImGui::EndPopup();
		}

		// We can also use OpenPopupOnItemClick() which is the same as BeginPopupContextItem() but without the Begin call.
		// So here we will make it that clicking on the text field with the right mouse button (1) will toggle the visibility of the popup above.
		ui::label(parent, "(You can also right-click me to open the same popup as above.)");
		ImGui::OpenPopupOnItemClick("item context menu", 1);

		// When used after an item that has an ID (here the Button), we can skip providing an ID to BeginPopupContextItem().
		// BeginPopupContextItem() will use the last item ID as the popup ID.
		// In addition here, we want to include your editable label inside the button label. We use the ### operator to override the ID (read FAQ about ID for details)
		static char name[32] = "Label1";
		char buf[64]; sprintf(buf, "Button: %s###Button", name); // ### operator override ID ignoring the preceding label
		ui::button(parent, buf);
		if(ImGui::BeginPopupContextItem())
		{
			ui::label(parent, "Edit name:");
			ImGui::InputText("##edit", name, IM_ARRAYSIZE(name));
			if(ui::button(parent, "Close"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
		ImGui::SameLine(); ui::label(parent, "(<-- right-click here)");

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Modals"))
	{
		ui::text(parent, "Modal windows are like popups but the user cannot close them by clicking outside the window.");

		if(ui::button(parent, "Delete.."))
			ImGui::OpenPopup("Delete?");

		if(ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ui::label(parent, "All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
			ui::separator(parent);

			//static int dummy_i = 0;
			//ui::dropdown_field(parent, "Combo", dummy_i, "Delete", "Delete harder", "");

			static bool dont_ask_me_next_time = false;
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, vec2(0, 0));
			ui::input_field(parent, "Don't ask me next time", dont_ask_me_next_time);
			ImGui::PopStyleVar();

			if(ui::button(parent, "OK", vec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if(ui::button(parent, "Cancel", vec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}

		if(ui::button(parent, "Stacked modals.."))
			ImGui::OpenPopup("Stacked 1");
		if(ImGui::BeginPopupModal("Stacked 1", NULL, ImGuiWindowFlags_MenuBar))
		{
			if(ImGui::BeginMenuBar())
			{
				if(ImGui::BeginMenu("File"))
				{
					if(ui::menu_choice(parent, "Dummy menu item")) {}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			ui::label(parent, "Hello from Stacked The First\nUsing style.Colors[ImGuiCol_ModalWindowDimBg] behind it.");

			// Testing behavior of widgets stacking their own regular popups over the modal.
			static int item = 1;
			static float color[4] = { 0.4f,0.7f,0.0f,0.5f };
			ui::dropdown_field(parent, "Combo", item, "aaaa", "bbbb", "cccc", "dddd", "eeee", "", "");
			ImGui::ColorEdit4("color", color);

			if(ui::button(parent, "Add another modal.."))
				ImGui::OpenPopup("Stacked 2");

			// Also demonstrate passing a bool* to BeginPopupModal(), this will create a regular close button which will close the popup.
			// Note that the visibility state of popups is owned by imgui, so the input value of the bool actually doesn't matter here.
			bool dummy_open = true;
			if(ImGui::BeginPopupModal("Stacked 2", dummy_open))
			{
				ui::label(parent, "Hello from Stacked The Second!");
				if(ui::button(parent, "Close"))
					ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
			}

			if(ui::button(parent, "Close"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}

		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Menus inside a regular window"))
	{
		ui::text(parent, "Below we are testing adding menu items to a regular window. It's rather unusual but should work!");
		ui::separator(parent);
		// NB: As a quirk in this very specific example, we want to differentiate the parent of this menu from the parent of the various popup menus above.
		// To do so we are encloding the items in a PushID()/PopID() block to make them two different menusets. If we don't, opening any popup above and hovering our menu here
		// would open it. This is because once a menu is active, we allow to switch to a sibling menu by just hovering on it, which is the desired behavior for regular menus.
		ImGui::PushID("foo");
		ui::menu_choice(parent, "Menu item", "CTRL+M");
		if(ImGui::BeginMenu("Menu inside a regular window"))
		{
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		ImGui::PopID();
		ui::separator(parent);
		//ImGui::TreePop();
	}
}

static void ShowDemoWindowColumns()
{
	if(!ui::expandbox(parent, "Columns"))
		return;

	ImGui::PushID("Columns");

	static bool disable_indent = false;
	ui::input_field(parent, "Disable tree indentation", disable_indent);
	ImGui::SameLine();
	HelpMarker("Disable the indenting of tree nodes so demo columns can use the full window width.");
	if(disable_indent)
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);

	// Basic columns
	if(Widget& n = ui::tree_node(parent, "Basic"))
	{
		ui::label(parent, "Without border:");
		Widget& cols = ui::columns(parent, 3, "mycolumns3", false);  // 3-ways, no border
		ui::separator(parent);
		for(int n = 0; n < 14; n++)
		{
			char label[32];
			sprintf(label, "Item %d", n);
			if(ui::selectable(parent, label)) {}
			//if (ui::button(parent, label, vec2(-1,0))) {}
			ImGui::NextColumn();
		}
		
		ui::separator(parent);

		ui::label(parent, "With border:");
		Widget& cols = ui::columns(parent, 4); // 4-ways, with border
		ui::separator(parent);
		Widget& row = ui::row(parent);
		ui::label(row, "ID");
		ui::label(row, "Name");
		ui::label(row, "Path");
		ui::label(row, "Hovered");
		ui::separator(parent);
		const char* names[3] = { "One", "Two", "Three" };
		const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
		static int selected = -1;
		for(int i = 0; i < 3; i++)
		{
			char label[32];
			sprintf(label, "%04d", i);
			if(ui::selectable(parent, label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
				selected = i;
			bool hovered = ImGui::IsItemHovered();
			ImGui::NextColumn();
			Widget& row = ui::row(cols);
			ui::label(row, names[i]);
			ui::label(row, paths[i]);
			ui::labelf(row, "%d", hovered);
		}
		ui::separator(parent);
		//ImGui::TreePop();
	}

	// Create multiple items in a same cell before switching to next column
	if(Widget& n = ui::tree_node(parent, "Mixed items"))
	{
		Widget& cols = ui::columns(parent, 3); // , "mixed");
		ui::separator(parent);

		Widget& row0 = ui::row(cols);

		Widget& col0 = ui::row(row);
		ui::label(col0, "Hello");
		ui::button(col0, "Banana");

		Widget& col1 = ui::row(row);
		ui::label(col1, "ImGui");
		ui::button(col1, "Apple");
		static float foo = 1.0f;
		ui::number_field<float>(col1, "red", { foo, 0.05f, 0 }); // , "%.3f");
		ui::label(col1, "An extra line here.");

		Widget& col2 = ui::row(row);
		ui::label(col2, "Sailor");
		ui::button(col2, "Corniflower");
		static float bar = 1.0f;
		ui::number_field<float>(col2, "blue", { bar, 0.05f, 0 }); // , "%.3f");

		Widget& row1 = ui::row(cols);
		if(Widget& b = ui::expandbox(row1, "Category A")) { ui::label(b, "Blah blah blah"); }
		if(Widget& b = ui::expandbox(row1, "Category B")) { ui::label(b, "Blah blah blah"); }
		if(Widget& b = ui::expandbox(row1, "Category C")) { ui::label(b, "Blah blah blah"); }
		ui::separator(parent);
		//ImGui::TreePop();
	}

	// Word wrapping
	if(Widget& n = ui::tree_node(parent, "Word-wrapping"))
	{
		Widget& cols = ui::columns(n, 2); // , "word-wrapping");
		ui::separator(parent);
		Widget& s0 = ui::stack(cols);
		ui::text(s0, "The quick brown fox jumps over the lazy dog.");
		ui::text(s0, "Hello Left");
		//ImGui::NextColumn();
		Widget& s1 = ui::stack(cols);
		ui::text(s1, "The quick brown fox jumps over the lazy dog.");
		ui::text(s1, "Hello Right");
		ui::separator(parent);
		//ImGui::TreePop();
	}

	if(Widget& n = ui::tree_node(parent, "Borders"))
	{
		// NB: Future columns API should allow automatic horizontal borders.
		static bool h_borders = true;
		static bool v_borders = true;
		ui::input_field(parent, "horizontal", h_borders);
		ImGui::SameLine();
		ui::input_field(parent, "vertical", v_borders);
		Widget& cols = ui::columns(parent, 4, NULL, v_borders);
		for(int i = 0; i < 4 * 3; i++)
		{
			if(h_borders && ImGui::GetColumnIndex() == 0)
				ui::separator(parent);
			ui::label(parent, "%c%c%c", 'a' + i, 'a' + i, 'a' + i);
			ui::label(parent, "Width %.2f", ImGui::GetColumnWidth());
			ui::label(parent, "Offset %.2f", ImGui::GetColumnOffset());
			ui::label(parent, "Long text that is likely to clip");
			ui::button(parent, "Button", vec2(-1.0f, 0.0f));
			ImGui::NextColumn();
		}
		
		if(h_borders)
			ui::separator(parent);
		//ImGui::TreePop();
	}

	// Scrolling columns
	/*
	if (ImGui::TreeNode("Vertical Scrolling"))
	{
		ImGui::BeginChild("##header", vec2(0, ImGui::GetTextLineHeightWithSpacing()+ImGui::GetStyle().ItemSpacing.y));
		Widget& cols = ui::columns(parent, 3);
		ui::label(parent, "ID"); ImGui::NextColumn();
		ui::label(parent, "Name"); ImGui::NextColumn();
		ui::label(parent, "Path"); ImGui::NextColumn();
		
		ui::separator(parent);
		ImGui::EndChild();
		ImGui::BeginChild("##scrollingregion", vec2(0, 60));
		Widget& cols = ui::columns(parent, 3);
		for (int i = 0; i < 10; i++)
		{
			ui::label(parent, "%04d", i); ImGui::NextColumn();
			ui::label(parent, "Foobar"); ImGui::NextColumn();
			ui::label(parent, "/path/foobar/%04d/", i); ImGui::NextColumn();
		}
		
		ImGui::EndChild();
		//ImGui::TreePop();
	}
	*/

	if(Widget& n = ui::tree_node(parent, "Horizontal Scrolling"))
	{
		ImGui::SetNextWindowContentSize(vec2(1500.0f, 0.0f));
		ImGui::BeginChild("##ScrollingRegion", vec2(0, ImGui::GetFontSize() * 20), false, ImGuiWindowFlags_HorizontalScrollbar);
		Widget& cols = ui::columns(parent, 10);
		int ITEMS_COUNT = 2000;
		ImGuiListClipper clipper(ITEMS_COUNT);  // Also demonstrate using the clipper for large list
		while(clipper.Step())
		{
			for(int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
				for(int j = 0; j < 10; j++)
				{
					ui::label(parent, "Line %d Column %d...", i, j);
					ImGui::NextColumn();
				}
		}
		
		ImGui::EndChild();
		//ImGui::TreePop();
	}

	bool node_open = ImGui::TreeNode("Tree within single cell");
	ImGui::SameLine(); HelpMarker("NB: Tree node must be poped before ending the cell. There's no storage of state per-cell.");
	if(node_open)
	{
		Widget& cols = ui::columns(parent, 2, "tree items");
		ui::separator(parent);
		if(Widget& n = ui::tree_node(parent, "Hello")) { ui::bullet(parent, "Sailor"); //ImGui::TreePop(); } ImGui::NextColumn();
		if(Widget& n = ui::tree_node(parent, "Bonjour")) { ui::bullet(parent, "Marin"); //ImGui::TreePop(); } ImGui::NextColumn();
		
		ui::separator(parent);
		//ImGui::TreePop();
	}

	if(disable_indent)
		ImGui::PopStyleVar();
	ImGui::PopID();
}

static void ShowDemoWindowMisc()
{
	if(ui::expandbox(parent, "Filtering"))
	{
		static ImGuiTextFilter filter;
		ui::label(parent, "Filter usage:\n"
			"  \"\"         display all lines\n"
			"  \"xxx\"      display lines containing \"xxx\"\n"
			"  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
			"  \"-xxx\"     hide lines containing \"xxx\"");
		filter.Draw();
		const char* lines[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" };
		for(int i = 0; i < IM_ARRAYSIZE(lines); i++)
			if(filter.PassFilter(lines[i]))
				ui::bullet(parent, "%s", lines[i]);
	}

	if(ui::expandbox(parent, "Inputs, Navigation & Focus"))
	{
		ImGuiIO& io = ImGui::GetIO();

		ui::label(parent, "WantCaptureMouse: %d", io.WantCaptureMouse);
		ui::label(parent, "WantCaptureKeyboard: %d", io.WantCaptureKeyboard);
		ui::label(parent, "WantTextInput: %d", io.WantTextInput);
		ui::label(parent, "WantSetMousePos: %d", io.WantSetMousePos);
		ui::label(parent, "NavActive: %d, NavVisible: %d", io.NavActive, io.NavVisible);

		if(Widget& n = ui::tree_node(parent, "Keyboard, Mouse & Navigation State"))
		{
			if(ImGui::IsMousePosValid())
				ui::label(parent, "Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
			else
				ui::label(parent, "Mouse pos: <INVALID>");
			ui::label(parent, "Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
			ui::label(parent, "Mouse down:");     for(int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if(io.MouseDownDuration[i] >= 0.0f) { ImGui::SameLine(); ui::label(parent, "b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
			ui::label(parent, "Mouse clicked:");  for(int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if(ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ui::label(parent, "b%d", i); }
			ui::label(parent, "Mouse dbl-clicked:"); for(int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if(ImGui::IsMouseDoubleClicked(i)) { ImGui::SameLine(); ui::label(parent, "b%d", i); }
			ui::label(parent, "Mouse released:"); for(int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if(ImGui::IsMouseReleased(i)) { ImGui::SameLine(); ui::label(parent, "b%d", i); }
			ui::label(parent, "Mouse wheel: %.1f", io.MouseWheel);

			ui::label(parent, "Keys down:");      for(int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if(io.KeysDownDuration[i] >= 0.0f) { ImGui::SameLine(); ui::label(parent, "%d (0x%X) (%.02f secs)", i, i, io.KeysDownDuration[i]); }
			ui::label(parent, "Keys pressed:");   for(int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if(ImGui::IsKeyPressed(i)) { ImGui::SameLine(); ui::label(parent, "%d (0x%X)", i, i); }
			ui::label(parent, "Keys release:");   for(int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if(ImGui::IsKeyReleased(i)) { ImGui::SameLine(); ui::label(parent, "%d (0x%X)", i, i); }
			ui::label(parent, "Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
			ui::label(parent, "Chars queue:");    for(int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; ImGui::SameLine();  ui::label(parent, "\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); } // FIXME: We should convert 'c' to UTF-8 here but the functions are not public.

			ui::label(parent, "NavInputs down:"); for(int i = 0; i < IM_ARRAYSIZE(io.NavInputs); i++) if(io.NavInputs[i] > 0.0f) { ImGui::SameLine(); ui::label(parent, "[%d] %.2f", i, io.NavInputs[i]); }
			ui::label(parent, "NavInputs pressed:"); for(int i = 0; i < IM_ARRAYSIZE(io.NavInputs); i++) if(io.NavInputsDownDuration[i] == 0.0f) { ImGui::SameLine(); ui::label(parent, "[%d]", i); }
			ui::label(parent, "NavInputs duration:"); for(int i = 0; i < IM_ARRAYSIZE(io.NavInputs); i++) if(io.NavInputsDownDuration[i] >= 0.0f) { ImGui::SameLine(); ui::label(parent, "[%d] %.2f", i, io.NavInputsDownDuration[i]); }

			ui::button(parent, "Hovering me sets the\nkeyboard capture flag");
			if(ImGui::IsItemHovered())
				ImGui::CaptureKeyboardFromApp(true);
			ImGui::SameLine();
			ui::button(parent, "Holding me clears the\nthe keyboard capture flag");
			if(ImGui::IsItemActive())
				ImGui::CaptureKeyboardFromApp(false);

			//ImGui::TreePop();
		}

		if(Widget& n = ui::tree_node(parent, "Tabbing"))
		{
			ui::label(parent, "Use TAB/SHIFT+TAB to cycle through keyboard editable fields.");
			static char buf[32] = "dummy";
			ImGui::InputText("1", buf, IM_ARRAYSIZE(buf));
			ImGui::InputText("2", buf, IM_ARRAYSIZE(buf));
			ImGui::InputText("3", buf, IM_ARRAYSIZE(buf));
			ImGui::PushAllowKeyboardFocus(false);
			ImGui::InputText("4 (tab skip)", buf, IM_ARRAYSIZE(buf));
			//ImGui::SameLine(); HelpMarker("Use ImGui::PushAllowKeyboardFocus(bool)\nto disable tabbing through certain widgets.");
			ImGui::PopAllowKeyboardFocus();
			ImGui::InputText("5", buf, IM_ARRAYSIZE(buf));
			//ImGui::TreePop();
		}

		if(Widget& n = ui::tree_node(parent, "Focus from code"))
		{
			bool focus_1 = ui::button(parent, "Focus on 1"); ImGui::SameLine();
			bool focus_2 = ui::button(parent, "Focus on 2"); ImGui::SameLine();
			bool focus_3 = ui::button(parent, "Focus on 3");
			int has_focus = 0;
			static char buf[128] = "click on a button to set focus";

			if(focus_1) ImGui::SetKeyboardFocusHere();
			ImGui::InputText("1", buf, IM_ARRAYSIZE(buf));
			if(ImGui::IsItemActive()) has_focus = 1;

			if(focus_2) ImGui::SetKeyboardFocusHere();
			ImGui::InputText("2", buf, IM_ARRAYSIZE(buf));
			if(ImGui::IsItemActive()) has_focus = 2;

			ImGui::PushAllowKeyboardFocus(false);
			if(focus_3) ImGui::SetKeyboardFocusHere();
			ImGui::InputText("3 (tab skip)", buf, IM_ARRAYSIZE(buf));
			if(ImGui::IsItemActive()) has_focus = 3;
			ImGui::PopAllowKeyboardFocus();

			if(has_focus)
				ui::label(parent, "Item with focus: %d", has_focus);
			else
				ui::label(parent, "Item with focus: <none>");

			// Use >= 0 parameter to SetKeyboardFocusHere() to focus an upcoming item
			static float f3[3] = { 0.0f, 0.0f, 0.0f };
			int focus_ahead = -1;
			if(ui::button(parent, "Focus on X")) { focus_ahead = 0; } ImGui::SameLine();
			if(ui::button(parent, "Focus on Y")) { focus_ahead = 1; } ImGui::SameLine();
			if(ui::button(parent, "Focus on Z")) { focus_ahead = 2; }
			if(focus_ahead != -1) ImGui::SetKeyboardFocusHere(focus_ahead);
			ImGui::SliderFloat3("Float3", f3[0], 0.0f, 1.0f);
			
			ui::text(parent, "NB: Cursor & selection are preserved when refocusing last used item in code.");
			//ImGui::TreePop();
		}

		if(Widget& n = ui::tree_node(parent, "Dragging"))
		{
			ui::text(parent, "You can use ImGui::GetMouseDragDelta(0) to query for the dragged amount on any widget.");
			for(int button = 0; button < 3; button++)
				ui::label(parent, "IsMouseDragging(%d):\n  w/ default threshold: %d,\n  w/ zero threshold: %d\n  w/ large threshold: %d",
					button, ImGui::IsMouseDragging(button), ImGui::IsMouseDragging(button, 0.0f), ImGui::IsMouseDragging(button, 20.0f));

			ui::button(parent, "Drag Me");
			if(ImGui::IsItemActive())
				ImGui::GetForegroundDrawList()->AddLine(io.MouseClickedPos[0], io.MousePos, ImGui::GetColorU32(ImGuiCol_Button), 4.0f); // Draw a line between the button and the mouse cursor

			// Drag operations gets "unlocked" when the mouse has moved past a certain threshold (the default threshold is stored in io.MouseDragThreshold)
			// You can request a lower or higher threshold using the second parameter of IsMouseDragging() and GetMouseDragDelta()
			vec2 value_raw = ImGui::GetMouseDragDelta(0, 0.0f);
			vec2 value_with_lock_threshold = ImGui::GetMouseDragDelta(0);
			vec2 mouse_delta = io.MouseDelta;
			ui::label(parent, "GetMouseDragDelta(0):\n  w/ default threshold: (%.1f, %.1f),\n  w/ zero threshold: (%.1f, %.1f)\nMouseDelta: (%.1f, %.1f)", value_with_lock_threshold.x, value_with_lock_threshold.y, value_raw.x, value_raw.y, mouse_delta.x, mouse_delta.y);
			//ImGui::TreePop();
		}

		if(Widget& n = ui::tree_node(parent, "Mouse cursors"))
		{
			const char* mouse_cursors_names[] = { "Arrow", "TextInput", "Move", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE", "Hand" };
			IM_ASSERT(IM_ARRAYSIZE(mouse_cursors_names) == ImGuiMouseCursor_COUNT);

			ui::label(parent, "Current mouse cursor = %d: %s", ImGui::GetMouseCursor(), mouse_cursors_names[ImGui::GetMouseCursor()]);
			ui::label(parent, "Hover to see mouse cursors:");
			ImGui::SameLine(); HelpMarker("Your application can render a different mouse cursor based on what ImGui::GetMouseCursor() returns. If software cursor rendering (io.MouseDrawCursor) is set ImGui will draw the right cursor for you, otherwise your backend needs to handle it.");
			for(int i = 0; i < ImGuiMouseCursor_COUNT; i++)
			{
				char label[32];
				sprintf(label, "Mouse cursor %d: %s", i, mouse_cursors_names[i]);
				ImGui::Bullet(); ui::selectable(parent, label, false);
				if(ImGui::IsItemHovered() || ImGui::IsItemFocused())
					ImGui::SetMouseCursor(i);
			}
			//ImGui::TreePop();
		}
	}
}


// [section] About Window / ShowAboutWindow()
// Access from ImGui Demo -> Help -> About

void ShowAboutWindow(Widget& parent, bool* p_open)
{
	if(!ImGui::Begin("About Dear ImGui", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}
	ui::label(parent, "Dear ImGui %s", ImGui::GetVersion());
	ui::separator(parent);
	ui::label(parent, "By Omar Cornut and all dear imgui contributors.");
	ui::label(parent, "Dear ImGui is licensed under the MIT License, see LICENSE for more information.");

	static bool show_config_info = false;
	ui::input_field(parent, "Config/Build Information", show_config_info);
	if(show_config_info)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		bool copy_to_clipboard = ui::button(parent, "Copy to clipboard");
		ImGui::BeginChildFrame(ImGui::GetID("cfginfos"), vec2(0, ImGui::GetTextLineHeightWithSpacing() * 18), ImGuiWindowFlags_NoMove);
		if(copy_to_clipboard)
			ImGui::LogToClipboard();

		ui::label(parent, "Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
		ui::separator(parent);
		ui::label(parent, "sizeof(size_t): %d, sizeof(ImDrawIdx): %d, sizeof(ImDrawVert): %d", (int)sizeof(size_t), (int)sizeof(ImDrawIdx), (int)sizeof(ImDrawVert));
		ui::label(parent, "define: __cplusplus=%d", (int)__cplusplus);
#ifdef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
		ui::label(parent, "define: IMGUI_DISABLE_OBSOLETE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS
		ui::label(parent, "define: IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
		ui::label(parent, "define: IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_FUNCTIONS
		ui::label(parent, "define: IMGUI_DISABLE_WIN32_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS
		ui::label(parent, "define: IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_MATH_FUNCTIONS
		ui::label(parent, "define: IMGUI_DISABLE_MATH_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_ALLOCATORS
		ui::label(parent, "define: IMGUI_DISABLE_DEFAULT_ALLOCATORS");
#endif
#ifdef IMGUI_USE_BGRA_PACKED_COLOR
		ui::label(parent, "define: IMGUI_USE_BGRA_PACKED_COLOR");
#endif
#ifdef _WIN32
		ui::label(parent, "define: _WIN32");
#endif
#ifdef _WIN64
		ui::label(parent, "define: _WIN64");
#endif
#ifdef __linux__
		ui::label(parent, "define: __linux__");
#endif
#ifdef __APPLE__
		ui::label(parent, "define: __APPLE__");
#endif
#ifdef _MSC_VER
		ui::label(parent, "define: _MSC_VER=%d", _MSC_VER);
#endif
#ifdef __MINGW32__
		ui::label(parent, "define: __MINGW32__");
#endif
#ifdef __MINGW64__
		ui::label(parent, "define: __MINGW64__");
#endif
#ifdef __GNUC__
		ui::label(parent, "define: __GNUC__=%d", (int)__GNUC__);
#endif
#ifdef __clang_version__
		ui::label(parent, "define: __clang_version__=%s", __clang_version__);
#endif
		ui::separator(parent);
		ui::label(parent, "io.BackendPlatformName: %s", io.BackendPlatformName ? io.BackendPlatformName : "NULL");
		ui::label(parent, "io.BackendRendererName: %s", io.BackendRendererName ? io.BackendRendererName : "NULL");
		ui::label(parent, "io.ConfigFlags: 0x%08X", io.ConfigFlags);
		if(io.ConfigFlags & ConfigFlags::NavEnableKeyboard)        ui::label(parent, " NavEnableKeyboard");
		if(io.ConfigFlags & ConfigFlags::NavEnableGamepad)         ui::label(parent, " NavEnableGamepad");
		if(io.ConfigFlags & ConfigFlags::NavEnableSetMousePos)     ui::label(parent, " NavEnableSetMousePos");
		if(io.ConfigFlags & ConfigFlags::NavNoCaptureKeyboard)     ui::label(parent, " NavNoCaptureKeyboard");
		if(io.ConfigFlags & ConfigFlags::NoMouse)                  ui::label(parent, " NoMouse");
		if(io.ConfigFlags & ConfigFlags::NoMouseCursorChange)      ui::label(parent, " NoMouseCursorChange");
		if(io.MouseDrawCursor)                                         ui::label(parent, "io.MouseDrawCursor");
		if(io.ConfigMacOSXBehaviors)                                   ui::label(parent, "io.ConfigMacOSXBehaviors");
		if(io.ConfigInputTextCursorBlink)                              ui::label(parent, "io.ConfigInputTextCursorBlink");
		if(io.ConfigWindowsResizeFromEdges)                            ui::label(parent, "io.ConfigWindowsResizeFromEdges");
		if(io.ConfigWindowsMoveFromTitleBarOnly)                       ui::label(parent, "io.ConfigWindowsMoveFromTitleBarOnly");
		ui::label(parent, "io.BackendFlags: 0x%08X", io.BackendFlags);
		if(io.BackendFlags & ImGuiBackendFlags_HasGamepad)             ui::label(parent, " HasGamepad");
		if(io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)        ui::label(parent, " HasMouseCursors");
		if(io.BackendFlags & ImGuiBackendFlags_HasSetMousePos)         ui::label(parent, " HasSetMousePos");
		ui::separator(parent);
		ui::label(parent, "io.Fonts: %d fonts, Flags: 0x%08X, TexSize: %d,%d", io.Fonts->Fonts.Size, io.Fonts->Flags, io.Fonts->TexWidth, io.Fonts->TexHeight);
		ui::label(parent, "io.DisplaySize: %.2f,%.2f", io.DisplaySize.x, io.DisplaySize.y);
		ui::label(parent, "io.DisplayFramebufferScale: %.2f,%.2f", io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		ui::separator(parent);
		ui::label(parent, "style.WindowPadding: %.2f,%.2f", style.WindowPadding.x, style.WindowPadding.y);
		ui::label(parent, "style.WindowBorderSize: %.2f", style.WindowBorderSize);
		ui::label(parent, "style.FramePadding: %.2f,%.2f", style.FramePadding.x, style.FramePadding.y);
		ui::label(parent, "style.FrameRounding: %.2f", style.FrameRounding);
		ui::label(parent, "style.FrameBorderSize: %.2f", style.FrameBorderSize);
		ui::label(parent, "style.ItemSpacing: %.2f,%.2f", style.ItemSpacing.x, style.ItemSpacing.y);
		ui::label(parent, "style.ItemInnerSpacing: %.2f,%.2f", style.ItemInnerSpacing.x, style.ItemInnerSpacing.y);

		if(copy_to_clipboard)
			ImGui::LogFinish();
		ImGui::EndChildFrame();
	}
	ImGui::End();
}

// [section] Style Editor / ShowStyleEditor()

// Demo helper function to select among default colors. See ShowStyleEditor() for more advanced options.
// Here we use the simplified Combo() api that packs items into a single literal string. Useful for quick combo boxes where the choices are known locally.
bool ImGui::ShowStyleSelector(const char* label)
{
	static int style_idx = -1;
	if(ui::dropdown_field(parent, label, &style_idx, "Classic", "Dark", "Light", ""))
	{
		switch(style_idx)
		{
		case 0: ImGui::StyleColorsClassic(); break;
		case 1: ImGui::StyleColorsDark(); break;
		case 2: ImGui::StyleColorsLight(); break;
		}
		return true;
	}
	return false;
}

// Demo helper function to select among loaded fonts.
// Here we use the regular BeginCombo()/EndCombo() api which is more the more flexible one.
void ShowFontSelector(const char* label)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font_current = ImGui::GetFont();
	if(ImGui::BeginCombo(label, font_current->GetDebugName()))
	{
		for(int n = 0; n < io.Fonts->Fonts.Size; n++)
		{
			ImFont* font = io.Fonts->Fonts[n];
			ImGui::PushID((void*)font);
			if(ui::selectable(parent, font->GetDebugName(), font == font_current))
				io.FontDefault = font;
			ImGui::PopID();
		}
		ImGui::EndCombo();
	}
	ImGui::SameLine();
	HelpMarker(
		"- Load additional fonts with io.Fonts->AddFontFromFileTTF().\n"
		"- The font atlas is built when calling io.Fonts->GetTexDataAsXXXX() or io.Fonts->Build().\n"
		"- Read FAQ and documentation in misc/fonts/ for more details.\n"
		"- If you need to add/remove fonts at runtime (e.g. for DPI change), do it before calling NewFrame().");
}
#endif

void ShowStyleEditor(Widget& parent, ImguiLook& style, ImguiColours& colours)
{
	// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
	//ImGuiStyle& style = ImGui::GetStyle();
	//static ImGuiStyle ref_saved_style;

	// Default to using internal storage as reference
	static bool init = true;
	//if(init && ref == NULL)
	//	ref_saved_style = style;
	init = false;
	//if(ref == NULL)
	//	ref = &ref_saved_style;

	//ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);

	//if(ImGui::ShowStyleSelector("Colors##Selector"))
	//	ref_saved_style = style;
	//ImGui::ShowFontSelector("Fonts##Selector");

	// Simplified Settings
	if(ui::slider_field<float>(parent, "FrameRounding", { style.FrameRounding, 0.0f, 12.0f })) //, "%.0f"))
		style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding

	Widget& row = ui::row(parent);
	{ bool window_border = (style.WindowBorderSize > 0.0f); if(ui::input_field(row, "WindowBorder", window_border)) style.WindowBorderSize = window_border ? 1.0f : 0.0f; }
	{ bool frame_border = (style.FrameBorderSize > 0.0f); if(ui::input_field(row, "FrameBorder", frame_border)) style.FrameBorderSize = frame_border ? 1.0f : 0.0f; }
	{ bool popup_border = (style.PopupBorderSize > 0.0f); if(ui::input_field(row, "PopupBorder", popup_border)) style.PopupBorderSize = popup_border ? 1.0f : 0.0f; }

	// Save/Revert button
	Widget& ops = ui::row(parent);
	if(ui::button(ops, "Save Ref").activated())
		;// *ref = ref_saved_style = style;
	if(ui::button(ops, "Revert Ref").activated())
		;// style = *ref;
	HelpMarker(ops, "Save/Revert in local non-persistent storage. Default Colors definition are not affected. Use \"Export Colors\" below to save them somewhere.");

	ui::separator(parent);

	Tabber& tabber = ui::tabber(parent); // ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if(Widget* tab = ui::tab(tabber, "Sizes"))
		{
			Widget& cols = ui::columns(*tab, { 0.6f, 0.4f });
			ui::label(cols, "Main");
			ui::float2_slider(cols, "WindowPadding", { "x", "y" }, style.WindowPadding.f, { 0.0f, 20.0f }); // , "%.0f");
			ui::float2_slider(cols, "FramePadding", { "x", "y" }, style.FramePadding.f, { 0.0f, 20.0f }); // , "%.0f");
			ui::float2_slider(cols, "ItemSpacing", { "x", "y" }, style.ItemSpacing.f, { 0.0f, 20.0f }); // , "%.0f");
			ui::float2_slider(cols, "ItemInnerSpacing", { "x", "y" }, style.ItemInnerSpacing.f, { 0.0f, 20.0f }); // , "%.0f");
			ui::float2_slider(cols, "TouchExtraPadding", { "x", "y" }, style.TouchExtraPadding.f, { 0.0f, 10.0f }); // , "%.0f");
			ui::slider_field<float>(cols, "IndentSpacing", { style.IndentSpacing, 0.0f, 30.0f }, true); // , "%.0f");
			ui::slider_field<float>(cols, "ScrollbarSize", { style.ScrollbarSize, 1.0f, 20.0f }, true); // , "%.0f");
			ui::slider_field<float>(cols, "GrabMinSize", { style.GrabMinSize, 1.0f, 20.0f }, true); //, "%.0f");
			ui::label(cols, "Borders");
			ui::slider_field<float>(cols, "WindowBorderSize", { style.WindowBorderSize, 0.0f, 1.0f }, true); //, "%.0f");
			ui::slider_field<float>(cols, "ChildBorderSize", { style.ChildBorderSize, 0.0f, 1.0f }, true); //, "%.0f");
			ui::slider_field<float>(cols, "PopupBorderSize", { style.PopupBorderSize, 0.0f, 1.0f }, true); //, "%.0f");
			ui::slider_field<float>(cols, "FrameBorderSize", { style.FrameBorderSize, 0.0f, 1.0f }, true); //, "%.0f");
			ui::slider_field<float>(cols, "TabBorderSize", { style.TabBorderSize, 0.0f, 1.0f }, true); //, "%.0f");
			ui::label(cols, "Rounding");
			ui::slider_field<float>(cols, "WindowRounding", { style.WindowRounding, 0.0f, 12.0f }, true);// , "%.0f");
			ui::slider_field<float>(cols, "ChildRounding", { style.ChildRounding, 0.0f, 12.0f }, true);//, "%.0f");
			ui::slider_field<float>(cols, "FrameRounding", { style.FrameRounding, 0.0f, 12.0f }, true);//, "%.0f");
			ui::slider_field<float>(cols, "PopupRounding", { style.PopupRounding, 0.0f, 12.0f }, true);//, "%.0f");
			ui::slider_field<float>(cols, "ScrollbarRounding", { style.ScrollbarRounding, 0.0f, 12.0f }, true);//, "%.0f");
			ui::slider_field<float>(cols, "GrabRounding", { style.GrabRounding, 0.0f, 12.0f }, true);//, "%.0f");
			ui::slider_field<float>(cols, "TabRounding", { style.TabRounding, 0.0f, 12.0f }, true);//, "%.0f");
			ui::label(cols, "Alignment");
			ui::float2_slider(cols, "WindowTitleAlign", { "x", "y" }, style.WindowTitleAlign.f, { 0.0f, 1.0f }); // , "%.2f");
			ui::float2_slider(cols, "ButtonTextAlign", { "x", "y" }, style.ButtonTextAlign.f, { 0.0f, 1.0f }); // , "%.2f");
			//ImGui::SameLine(); HelpMarker("Alignment applies when a button is larger than its text content.");
			ui::float2_slider(cols, "SelectableTextAlign", { "x", "y" }, style.SelectableTextAlign.f, { 0.0f, 1.0f }); // , "%.2f");
			//ImGui::SameLine(); HelpMarker("Alignment applies when a selectable is larger than its text content.");
			ui::label(cols, "Safe Area Padding");
			//ImGui::SameLine(); HelpMarker("Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).");
			ui::float2_slider(cols, "DisplaySafeAreaPadding", { "x", "y" }, style.DisplaySafeAreaPadding.f, { 0.0f, 30.0f }); // , "%.0f");
			//ImGui::EndTabItem();
		}

		if(Widget* tab = ui::tab(tabber, "Colors"))
		{
#if 0
			static int output_dest = 0;
			static bool output_only_modified = true;
			if(ui::button(*tab, "Export Unsaved"))
			{
				if(output_dest == 0)
					ImGui::LogToClipboard();
				else
					ImGui::LogToTTY();
				ImGui::LogText("vec4* colors = ImGui::GetStyle().Colors;" IM_NEWLINE);
				for(int i = 0; i < ImGuiCol_COUNT; i++)
				{
					const vec4& col = style.Colors[i];
					const char* name = ImGui::GetStyleColorName(i);
					if(!output_only_modified || memcmp(&col, &ref->Colors[i], sizeof(vec4)) != 0)
						ImGui::LogText("colors[ImGuiCol_%s]%*s= vec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE, name, 23 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
				}
				ImGui::LogFinish();
			}
			ImGui::SameLine(); ImGui::SetNextItemWidth(120); ui::dropdown_field(*tab, "##output_type", output_dest, "To Clipboard", "To TTY", "");
			ImGui::SameLine(); ui::input_field(*tab, "Only Modified Colors", output_only_modified);
#endif

#if 0
			static ImGuiTextFilter filter;
			filter.Draw("Filter colors", ImGui::GetFontSize() * 16);
#endif

#if 0
			static ImGuiColorEditFlags alpha_flags = 0;
			ui::radio_button(*tab, "Opaque", alpha_flags, 0); ImGui::SameLine();
			ui::radio_button(*tab, "Alpha", alpha_flags, ImGuiColorEditFlags_AlphaPreview); ImGui::SameLine();
			ui::radio_button(*tab, "Both", alpha_flags, ImGuiColorEditFlags_AlphaPreviewHalf); ImGui::SameLine();
			HelpMarker("In the color list:\nLeft-click on colored square to open color picker,\nRight-click to open edit options menu.");
#endif

			//ImGui::BeginChild("##colors", vec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
			//ImGui::PushItemWidth(-160);
			span<Colour> array = { &colours.Border, 48 };
			for(int i = 0; i < 48; i++)
			{
				const char* name = "";// ImGui::GetStyleColorName(i);
				//if(!filter.PassFilter(name))
				//	continue;
				//ImGui::PushID(i);
				Widget& row = ui::row(*tab);
				ui::color_toggle_edit(row, array[i]);
				//ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
				//if(memcmp(&style.Colors[i], &ref->Colors[i], sizeof(vec4)) != 0)
				//{
				//	// Tips: in a real user application, you may want to merge and use an icon font into the main font, so instead of "Save"/"Revert" you'd use icons.
				//	// Read the FAQ and misc/fonts/README.txt about using icon fonts. It's really easy and super convenient!
				//	ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if(ui::button(*tab, "Save")) ref->Colors[i] = style.Colors[i];
				//	ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if(ui::button(*tab, "Revert")) style.Colors[i] = ref->Colors[i];
				//}
				ui::label(row, name);
				//ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
				//ImGui::TextUnformatted(name);
				//ImGui::PopID();
			}
			//ImGui::PopItemWidth();
			//ImGui::EndChild();
		}

#if 0
		if(ImGui::BeginTabItem("Fonts"))
		{
			ImGuiIO& io = ImGui::GetIO();
			ImFontAtlas* atlas = io.Fonts;
			HelpMarker("Read FAQ and misc/fonts/README.txt for details on font loading.");
			ImGui::PushItemWidth(120);
			for(int i = 0; i < atlas->Fonts.Size; i++)
			{
				ImFont* font = atlas->Fonts[i];
				ImGui::PushID(font);
				bool font_details_opened = ImGui::TreeNode(font, "Font %d: \"%s\"\n%.2f px, %d glyphs, %d file(s)", i, font->ConfigData ? font->ConfigData[0].Name : "", font->FontSize, font->Glyphs.Size, font->ConfigDataCount);
				ImGui::SameLine(); if(ui::button(*tab, "Set as default")) { io.FontDefault = font; }
				if(font_details_opened)
				{
					ImGui::PushFont(font);
					ui::label(*tab, "The quick brown fox jumps over the lazy dog");
					ImGui::PopFont();
					ui::drag_field<float>(*tab, "Font scale", font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");   // Scale only this font
					ImGui::SameLine(); HelpMarker("Note than the default embedded font is NOT meant to be scaled.\n\nFont are currently rendered into bitmaps at a given size at the time of building the atlas. You may oversample them to get some flexibility with scaling. You can also render at multiple sizes and select which one to use at runtime.\n\n(Glimmer of hope: the atlas system should hopefully be rewritten in the future to make scaling more natural and automatic.)");
					ui::number_field<float>(*tab, "Font offset", font->DisplayOffset.y, 1, 1, "%.0f");
					ui::label(*tab, "Ascent: %f, Descent: %f, Height: %f", font->Ascent, font->Descent, font->Ascent - font->Descent);
					ui::label(*tab, "Fallback character: '%c' (%d)", font->FallbackChar, font->FallbackChar);
					const float surface_sqrt = sqrtf((float)font->MetricsTotalSurface);
					ui::label(*tab, "Texture surface: %d pixels (approx) ~ %dx%d", font->MetricsTotalSurface, (int)surface_sqrt, (int)surface_sqrt);
					for(int config_i = 0; config_i < font->ConfigDataCount; config_i++)
						if(const ImFontConfig* cfg = &font->ConfigData[config_i])
							ui::bullet(*tab, "Input %d: \'%s\', Oversample: (%d,%d), PixelSnapH: %d", config_i, cfg->Name, cfg->OversampleH, cfg->OversampleV, cfg->PixelSnapH);
					if(Widget& n = ui::tree_node(*tab, "Glyphs", "Glyphs (%d)", font->Glyphs.Size))
					{
						// Display all glyphs of the fonts in separate pages of 256 characters
						for(int base = 0; base < 0x10000; base += 256)
						{
							int count = 0;
							for(int n = 0; n < 256; n++)
								count += font->FindGlyphNoFallback((ImWchar)(base + n)) ? 1 : 0;
							if(count > 0 && ImGui::TreeNode((void*)(intptr_t)base, "U+%04X..U+%04X (%d %s)", base, base + 255, count, count > 1 ? "glyphs" : "glyph"))
							{
								float cell_size = font->FontSize * 1;
								float cell_spacing = style.ItemSpacing.y;
								vec2 base_pos = ImGui::GetCursorScreenPos();
								ImDrawList* draw_list = ImGui::GetWindowDrawList();
								for(int n = 0; n < 256; n++)
								{
									vec2 cell_p1(base_pos.x + (n % 16) * (cell_size + cell_spacing), base_pos.y + (n / 16) * (cell_size + cell_spacing));
									vec2 cell_p2(cell_p1.x + cell_size, cell_p1.y + cell_size);
									const ImFontGlyph* glyph = font->FindGlyphNoFallback((ImWchar)(base + n));
									draw_list->AddRect(cell_p1, cell_p2, glyph ? IM_COL32(255, 255, 255, 100) : IM_COL32(255, 255, 255, 50));
									if(glyph)
										font->RenderChar(draw_list, cell_size, cell_p1, ImGui::GetColorU32(ImGuiCol_Text), (ImWchar)(base + n)); // We use ImFont::RenderChar as a shortcut because we don't have UTF-8 conversion functions available to generate a string.
									if(glyph && ImGui::IsMouseHoveringRect(cell_p1, cell_p2))
									{
										ImGui::BeginTooltip();
										ui::label(*tab, "Codepoint: U+%04X", base + n);
										ui::separator(*tab);
										ui::label(*tab, "AdvanceX: %.1f", glyph->AdvanceX);
										ui::label(*tab, "Pos: (%.2f,%.2f)->(%.2f,%.2f)", glyph->X0, glyph->Y0, glyph->X1, glyph->Y1);
										ui::label(*tab, "UV: (%.3f,%.3f)->(%.3f,%.3f)", glyph->U0, glyph->V0, glyph->U1, glyph->V1);
										ImGui::EndTooltip();
									}
								}
								ImGui::Dummy(vec2((cell_size + cell_spacing) * 16, (cell_size + cell_spacing) * 16));
								//ImGui::TreePop();
							}
						}
						//ImGui::TreePop();
					}
					//ImGui::TreePop();
				}
				ImGui::PopID();
			}
			if(Widget& n = ui::tree_node(*tab, "Atlas texture", "Atlas texture (%dx%d pixels)", atlas->TexWidth, atlas->TexHeight))
			{
				vec4 tint_col = vec4(1.0f, 1.0f, 1.0f, 1.0f);
				vec4 border_col = vec4(1.0f, 1.0f, 1.0f, 0.5f);
				ImGui::Image(atlas->TexID, vec2((float)atlas->TexWidth, (float)atlas->TexHeight), vec2(0, 0), vec2(1, 1), tint_col, border_col);
				//ImGui::TreePop();
			}

			static float window_scale = 1.0f;
			if(ui::drag_field<float>(*tab, "this window scale", window_scale, 0.005f, 0.3f, 2.0f, "%.2f"))   // scale only this window
				ImGui::SetWindowFontScale(window_scale);
			ui::drag_field<float>(*tab, "global scale", io.FontGlobalScale, 0.005f, 0.3f, 2.0f, "%.2f");      // scale everything
			ImGui::PopItemWidth();

			ImGui::EndTabItem();
		}
#endif

		if(Widget* tab = ui::tab(tabber, "Rendering"))
		{
			ui::input_field(*tab, "Anti-aliased lines", style.AntiAliasedLines);
			//ImGui::SameLine(); HelpMarker("When disabling anti-aliasing lines, you'll probably want to disable borders in your style as well.");
			ui::input_field(*tab, "Anti-aliased fill", style.AntiAliasedFill);
			//ImGui::PushItemWidth(100);
			ui::drag_field<float>(*tab, "Curve Tessellation Tolerance", { style.CurveTessellationTol, 0.02f, 0.10f, FLT_MAX }); // , "%.2f", 2.0f);
			if(style.CurveTessellationTol < 0.10f) style.CurveTessellationTol = 0.10f;
			ui::drag_field<float>(*tab, "Global Alpha", { style.Alpha, 0.005f, 0.20f, 1.0f }); // , "%.2f"); // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
			//ImGui::PopItemWidth();
		}
	}

	//ImGui::PopItemWidth();
}

#if 0
// [section] Example App: Main Menu Bar / ShowExampleAppMainMenuBar()

// Demonstrate creating a "main" fullscreen menu bar and populating it.
// Note the difference between BeginMainMenuBar() and BeginMenuBar():
// - BeginMenuBar() = menu-bar inside current window we Begin()-ed into (the window needs the ImGuiWindowFlags_MenuBar flag)
// - BeginMainMenuBar() = helper to create menu-bar-sized window at the top of the main viewport + call BeginMenuBar() into it.
static void ShowExampleAppMainMenuBar()
{
	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu("File"))
		{
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu("Edit"))
		{
			if(ui::menu_choice(parent, "Undo", "CTRL+Z")) {}
			if(ui::menu_choice(parent, "Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ui::separator(parent);
			if(ui::menu_choice(parent, "Cut", "CTRL+X")) {}
			if(ui::menu_choice(parent, "Copy", "CTRL+C")) {}
			if(ui::menu_choice(parent, "Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

// Note that shortcuts are currently provided for display only (future version will add flags to BeginMenu to process shortcuts)
static void ShowExampleMenuFile()
{
	ui::menu_choice(parent, "(dummy menu)", NULL, false, false);
	if(ui::menu_choice(parent, "New")) {}
	if(ui::menu_choice(parent, "Open", "Ctrl+O")) {}
	if(ImGui::BeginMenu("Open Recent"))
	{
		ui::menu_choice(parent, "fish_hat.c");
		ui::menu_choice(parent, "fish_hat.inl");
		ui::menu_choice(parent, "fish_hat.h");
		if(ImGui::BeginMenu("More.."))
		{
			ui::menu_choice(parent, "Hello");
			ui::menu_choice(parent, "Sailor");
			if(ImGui::BeginMenu("Recurse.."))
			{
				ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if(ui::menu_choice(parent, "Save", "Ctrl+S")) {}
	if(ui::menu_choice(parent, "Save As..")) {}
	ui::separator(parent);
	if(ImGui::BeginMenu("Options"))
	{
		static bool enabled = true;
		ui::menu_choice(parent, "Enabled", "", enabled);
		ImGui::BeginChild("child", vec2(0, 60), true);
		for(int i = 0; i < 10; i++)
			ui::label(parent, "Scrolling Text %d", i);
		ImGui::EndChild();
		static float f = 0.5f;
		static int n = 0;
		static bool b = true;
		ui::slider_field<float>(parent, "Value", f, 0.0f, 1.0f);
		ui::number_field<float>(parent, "Input", f, 0.1f);
		ui::dropdown_field(parent, "Combo", n, "Yes", "No", "Maybe", "", "");
		ui::input_field(parent, "Check", b);
		ImGui::EndMenu();
	}
	if(ImGui::BeginMenu("Colors"))
	{
		float sz = ImGui::GetTextLineHeight();
		for(int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
			vec2 p = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(p, vec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
			ImGui::Dummy(vec2(sz, sz));
			ImGui::SameLine();
			ui::menu_choice(parent, name);
		}
		ImGui::EndMenu();
	}
	if(ImGui::BeginMenu("Disabled", false)) // Disabled
	{
		IM_ASSERT(0);
	}
	if(ui::menu_choice(parent, "Checked", NULL, true)) {}
	if(ui::menu_choice(parent, "Quit", "Alt+F4")) {}
}


// [section] Example App: Debug Console / ShowExampleAppConsole()

// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, here we are using a more C++ like approach of declaring a class to hold the data and the functions.
struct ExampleAppConsole
{
	char                  InputBuf[256];
	vector<char*>         Items;
	vector<const char*>   Commands;
	vector<char*>         History;
	int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
	ImGuiTextFilter       Filter;
	bool                  AutoScroll;
	bool                  ScrollToBottom;

	ExampleAppConsole()
	{
		ClearLog();
		memset(InputBuf, 0, sizeof(InputBuf));
		HistoryPos = -1;
		Commands.push_back("HELP");
		Commands.push_back("HISTORY");
		Commands.push_back("CLEAR");
		Commands.push_back("CLASSIFY");  // "classify" is only here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
		AutoScroll = true;
		ScrollToBottom = true;
		AddLog("Welcome to Dear ImGui!");
	}
	~ExampleAppConsole()
	{
		ClearLog();
		for(int i = 0; i < History.Size; i++)
			free(History[i]);
	}

	// Portable helpers
	static int   Stricmp(const char* str1, const char* str2) { int d; while((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
	static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while(n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
	static char* Strdup(const char *str) { size_t len = strlen(str) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)str, len); }
	static void  Strtrim(char* str) { char* str_end = str + strlen(str); while(str_end > str && str_end[-1] == ' ') str_end--; *str_end = 0; }

	void    ClearLog()
	{
		for(int i = 0; i < Items.Size; i++)
			free(Items[i]);
		Items.clear();
		ScrollToBottom = true;
	}

	void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		// FIXME-OPT
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
		buf[IM_ARRAYSIZE(buf) - 1] = 0;
		va_end(args);
		Items.push_back(Strdup(buf));
		if(AutoScroll)
			ScrollToBottom = true;
	}

	void    Draw(const char* title, bool* p_open)
	{
		ImGui::SetNextWindowSize(vec2(520, 600), ImGuiCond_FirstUseEver);
		if(!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}

		// As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar. So e.g. IsItemHovered() will return true when hovering the title bar.
		// Here we create a context menu only available from the title bar.
		if(ImGui::BeginPopupContextItem())
		{
			if(ui::menu_choice(parent, "Close Console"))
				*p_open = false;
			ImGui::EndPopup();
		}

		ui::text(parent, "This example implements a console with basic coloring, completion and history. A more elaborate implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
		ui::text(parent, "Enter 'HELP' for help, press TAB to use text completion.");

		// TODO: display items starting from the bottom

		if(ui::button(parent, "Add Dummy Text")) { AddLog("%d some text", Items.Size); AddLog("some more text"); AddLog("display very important message here!"); } ImGui::SameLine();
		if(ui::button(parent, "Add Dummy Error")) { AddLog("[error] something went wrong"); } ImGui::SameLine();
		if(ui::button(parent, "Clear")) { ClearLog(); } ImGui::SameLine();
		bool copy_to_clipboard = ui::button(parent, "Copy"); ImGui::SameLine();
		if(ui::button(parent, "Scroll to bottom")) ScrollToBottom = true;
		//static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

		ui::separator(parent);

		// Options menu
		if(ImGui::BeginPopup("Options"))
		{
			if(ui::input_field(parent, "Auto-scroll", AutoScroll))
				if(AutoScroll)
					ScrollToBottom = true;
			ImGui::EndPopup();
		}

		// Options, Filter
		if(ui::button(parent, "Options"))
			ImGui::OpenPopup("Options");
		ImGui::SameLine();
		Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
		ui::separator(parent);

		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
		ImGui::BeginChild("ScrollingRegion", vec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
		if(ImGui::BeginPopupContextWindow())
		{
			if(ui::selectable(parent, "Clear")) ClearLog();
			ImGui::EndPopup();
		}

		// Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
		// NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping to only process visible items.
		// You can seek and display only the lines that are visible using the ImGuiListClipper helper, if your elements are evenly spaced and you have cheap random access to the elements.
		// To use the clipper we could replace the 'for (int i = 0; i < Items.Size; i++)' loop with:
		//     ImGuiListClipper clipper(Items.Size);
		//     while (clipper.Step())
		//         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		// However, note that you can not use this code as is if a filter is active because it breaks the 'cheap random-access' property. We would need random-access on the post-filtered list.
		// A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices that passed the filtering test, recomputing this array when user changes the filter,
		// and appending newly elements as they are inserted. This is left as a task to the user until we can manage to improve this example code!
		// If your items are of variable size you may want to implement code similar to what ImGuiListClipper does. Or split your data into fixed height items to allow random-seeking into your list.
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, vec2(4, 1)); // Tighten spacing
		if(copy_to_clipboard)
			ImGui::LogToClipboard();
		for(int i = 0; i < Items.Size; i++)
		{
			const char* item = Items[i];
			if(!Filter.PassFilter(item))
				continue;

			// Normally you would store more information in your item (e.g. make Items[] an array of structure, store color/type etc.)
			bool pop_color = false;
			if(strstr(item, "[error]")) { ImGui::PushStyleColor(ImGuiCol_Text, vec4(1.0f, 0.4f, 0.4f, 1.0f)); pop_color = true; }
			else if(strncmp(item, "# ", 2) == 0) { ImGui::PushStyleColor(ImGuiCol_Text, vec4(1.0f, 0.8f, 0.6f, 1.0f)); pop_color = true; }
			ImGui::TextUnformatted(item);
			if(pop_color)
				ImGui::PopStyleColor();
		}
		if(copy_to_clipboard)
			ImGui::LogFinish();
		if(ScrollToBottom)
			ImGui::SetScrollHereY(1.0f);
		ScrollToBottom = false;
		ImGui::PopStyleVar();
		ImGui::EndChild();
		ui::separator(parent);

		// Command-line
		bool reclaim_focus = false;
		if(ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this))
		{
			char* s = InputBuf;
			Strtrim(s);
			if(s[0])
				ExecCommand(s);
			strcpy(s, "");
			reclaim_focus = true;
		}

		// Auto-focus on window apparition
		ImGui::SetItemDefaultFocus();
		if(reclaim_focus)
			ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

		ImGui::End();
	}

	void    ExecCommand(const char* command_line)
	{
		AddLog("# %s\n", command_line);

		// Insert into history. First find match and delete it so it can be pushed to the back. This isn't trying to be smart or optimal.
		HistoryPos = -1;
		for(int i = History.Size - 1; i >= 0; i--)
			if(Stricmp(History[i], command_line) == 0)
			{
				free(History[i]);
				History.erase(History.begin() + i);
				break;
			}
		History.push_back(Strdup(command_line));

		// Process command
		if(Stricmp(command_line, "CLEAR") == 0)
		{
			ClearLog();
		}
		else if(Stricmp(command_line, "HELP") == 0)
		{
			AddLog("Commands:");
			for(int i = 0; i < Commands.Size; i++)
				AddLog("- %s", Commands[i]);
		}
		else if(Stricmp(command_line, "HISTORY") == 0)
		{
			int first = History.Size - 10;
			for(int i = first > 0 ? first : 0; i < History.Size; i++)
				AddLog("%3d: %s\n", i, History[i]);
		}
		else
		{
			AddLog("Unknown command: '%s'\n", command_line);
		}

		// On commad input, we scroll to bottom even if AutoScroll==false
		ScrollToBottom = true;
	}

	static int TextEditCallbackStub(ImGuiInputTextCallbackData* data) // In C++11 you are better off using lambdas for this sort of forwarding callbacks
	{
		ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
		return console->TextEditCallback(data);
	}

	int     TextEditCallback(ImGuiInputTextCallbackData* data)
	{
		//AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
		switch(data->EventFlag)
		{
		case ImGuiInputTextFlags_CallbackCompletion:
		{
			// Example of TEXT COMPLETION

			// Locate beginning of current word
			const char* word_end = data->Buf + data->CursorPos;
			const char* word_start = word_end;
			while(word_start > data->Buf)
			{
				const char c = word_start[-1];
				if(c == ' ' || c == '\t' || c == ',' || c == ';')
					break;
				word_start--;
			}

			// Build a list of candidates
			vector<const char*> candidates;
			for(int i = 0; i < Commands.Size; i++)
				if(Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
					candidates.push_back(Commands[i]);

			if(candidates.Size == 0)
			{
				// No match
				AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
			}
			else if(candidates.Size == 1)
			{
				// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
				data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
				data->InsertChars(data->CursorPos, candidates[0]);
				data->InsertChars(data->CursorPos, " ");
			}
			else
			{
				// Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
				int match_len = (int)(word_end - word_start);
				for(;;)
				{
					int c = 0;
					bool all_candidates_matches = true;
					for(int i = 0; i < candidates.Size && all_candidates_matches; i++)
						if(i == 0)
							c = toupper(candidates[i][match_len]);
						else if(c == 0 || c != toupper(candidates[i][match_len]))
							all_candidates_matches = false;
					if(!all_candidates_matches)
						break;
					match_len++;
				}

				if(match_len > 0)
				{
					data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
					data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
				}

				// List matches
				AddLog("Possible matches:\n");
				for(int i = 0; i < candidates.Size; i++)
					AddLog("- %s\n", candidates[i]);
			}

			break;
		}
		case ImGuiInputTextFlags_CallbackHistory:
		{
			// Example of HISTORY
			const int prev_history_pos = HistoryPos;
			if(data->EventKey == ImGuiKey_UpArrow)
			{
				if(HistoryPos == -1)
					HistoryPos = History.Size - 1;
				else if(HistoryPos > 0)
					HistoryPos--;
			}
			else if(data->EventKey == ImGuiKey_DownArrow)
			{
				if(HistoryPos != -1)
					if(++HistoryPos >= History.Size)
						HistoryPos = -1;
			}

			// A better implementation would preserve the data on the current input line along with cursor position.
			if(prev_history_pos != HistoryPos)
			{
				const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
				data->DeleteChars(0, data->BufTextLen);
				data->InsertChars(0, history_str);
			}
		}
		}
		return 0;
	}
};

static void ShowExampleAppConsole(bool* p_open)
{
	static ExampleAppConsole console;
	console.Draw("Example: Console", p_open);
}


// [section] Example App: Debug Log / ShowExampleAppLog()

// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
struct ExampleAppLog
{
	//ImGuiTextBuffer     Buf;
	//ImGuiTextFilter     Filter;
	vector<int>       LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
	bool                AutoScroll;
	bool                ScrollToBottom;

	ExampleAppLog()
	{
		AutoScroll = true;
		ScrollToBottom = false;
		Clear();
	}

	void    Clear()
	{
		Buf.clear();
		LineOffsets.clear();
		LineOffsets.push_back(0);
	}

	void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendfv(fmt, args);
		va_end(args);
		for(int new_size = Buf.size(); old_size < new_size; old_size++)
			if(Buf[old_size] == '\n')
				LineOffsets.push_back(old_size + 1);
		if(AutoScroll)
			ScrollToBottom = true;
	}

	void    Draw(const char* title, bool* p_open = NULL)
	{
		if(!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}

		// Options menu
		if(ImGui::BeginPopup("Options"))
		{
			if(ui::input_field(parent, "Auto-scroll", AutoScroll))
				if(AutoScroll)
					ScrollToBottom = true;
			ImGui::EndPopup();
		}

		// Main window
		if(ui::button(parent, "Options"))
			ImGui::OpenPopup("Options");
		ImGui::SameLine();
		bool clear = ui::button(parent, "Clear");
		ImGui::SameLine();
		bool copy = ui::button(parent, "Copy");
		ImGui::SameLine();
		Filter.Draw("Filter", -100.0f);

		ui::separator(parent);
		ImGui::BeginChild("scrolling", vec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

		if(clear)
			Clear();
		if(copy)
			ImGui::LogToClipboard();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, vec2(0, 0));
		const char* buf = Buf.begin();
		const char* buf_end = Buf.end();
		if(Filter.IsActive())
		{
			// In this example we don't use the clipper when Filter is enabled.
			// This is because we don't have a random access on the result on our filter.
			// A real application processing logs with ten of thousands of entries may want to store the result of search/filter.
			// especially if the filtering function is not trivial (e.g. reg-exp).
			for(int line_no = 0; line_no < LineOffsets.Size; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no];
				const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
				if(Filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else
		{
			// The simplest and easy way to display the entire buffer:
			//   ImGui::TextUnformatted(buf_begin, buf_end);
			// And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward to skip non-visible lines.
			// Here we instead demonstrate using the clipper to only process lines that are within the visible area.
			// If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them on your side is recommended.
			// Using ImGuiListClipper requires A) random access into your data, and B) items all being the  same height,
			// both of which we can handle since we an array pointing to the beginning of each line of text.
			// When using the filter (in the block of code above) we don't have random access into the data to display anymore, which is why we don't use the clipper.
			// Storing or skimming through the search result would make it possible (and would be recommended if you want to search through tens of thousands of entries)
			ImGuiListClipper clipper;
			clipper.Begin(LineOffsets.Size);
			while(clipper.Step())
			{
				for(int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{
					const char* line_start = buf + LineOffsets[line_no];
					const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		if(ScrollToBottom)
			ImGui::SetScrollHereY(1.0f);
		ScrollToBottom = false;
		ImGui::EndChild();
		ImGui::End();
	}
};

// Demonstrate creating a simple log window with basic filtering.
static void ShowExampleAppLog(bool* p_open)
{
	static ExampleAppLog log;

	// For the demo: add a debug button _BEFORE_ the normal log window contents
	// We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
	// Most of the contents of the window will be added by the log.Draw() call.
	ImGui::SetNextWindowSize(vec2(500, 400), ImGuiCond_FirstUseEver);
	ImGui::Begin("Example: Log", p_open);
	if(ui::button(parent, "[Debug] Add 5 entries"))
	{
		static int counter = 0;
		for(int n = 0; n < 5; n++)
		{
			const char* categories[3] = { "info", "warn", "error" };
			const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
			log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
				ImGui::GetFrameCount(), categories[counter % IM_ARRAYSIZE(categories)], ImGui::GetTime(), words[counter % IM_ARRAYSIZE(words)]);
			counter++;
		}
	}
	ImGui::End();

	// Actually call in the regular Log helper (which will Begin() into the same window as we just did)
	log.Draw("Example: Log", p_open);
}

// [section] Example App: Simple Layout / ShowExampleAppLayout()

// Demonstrate create a window with multiple child windows.
static void ShowExampleAppLayout(bool* p_open)
{
	ImGui::SetNextWindowSize(vec2(500, 440), ImGuiCond_FirstUseEver);
	if(ImGui::Begin("Example: Simple layout", p_open, ImGuiWindowFlags_MenuBar))
	{
		if(ImGui::BeginMenuBar())
		{
			if(ImGui::BeginMenu("File"))
			{
				if(ui::menu_choice(parent, "Close")) *p_open = false;
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// left
		static int selected = 0;
		ImGui::BeginChild("left pane", vec2(150, 0), true);
		for(int i = 0; i < 100; i++)
		{
			char label[128];
			sprintf(label, "MyObject %d", i);
			if(ui::selectable(parent, label, selected == i))
				selected = i;
		}
		ImGui::EndChild();
		ImGui::SameLine();

		// right
		ImGui::BeginGroup();
		ImGui::BeginChild("item view", vec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
		ui::label(parent, "MyObject: %d", selected);
		ui::separator(parent);
		if(ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
		{
			if(ImGui::BeginTabItem("Description"))
			{
				ui::text(parent, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
				ImGui::EndTabItem();
			}
			if(ImGui::BeginTabItem("Details"))
			{
				ui::label(parent, "ID: 0123456789");
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::EndChild();
		if(ui::button(parent, "Revert")) {}
		ImGui::SameLine();
		if(ui::button(parent, "Save")) {}
		ImGui::EndGroup();
	}
	ImGui::End();
}


// [section] Example App: Property Editor / ShowExampleAppPropertyEditor()

// Demonstrate create a simple property editor.
static void ShowExampleAppPropertyEditor(bool* p_open)
{
	ImGui::SetNextWindowSize(vec2(430, 450), ImGuiCond_FirstUseEver);
	if(!ImGui::Begin("Example: Property editor", p_open))
	{
		ImGui::End();
		return;
	}

	HelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, vec2(2, 2));
	Widget& cols = ui::columns(parent, 2);
	ui::separator(parent);

	struct funcs
	{
		static void ShowDummyObject(const char* prefix, int uid)
		{
			ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
			ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
			bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
			ImGui::NextColumn();
			ImGui::AlignTextToFramePadding();
			ui::label(parent, "my sailor is rich");
			ImGui::NextColumn();
			if(node_open)
			{
				static float dummy_members[8] = { 0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f };
				for(int i = 0; i < 8; i++)
				{
					ImGui::PushID(i); // Use field index as identifier.
					if(i < 2)
					{
						ShowDummyObject("Child", 424242);
					}
					else
					{
						// Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
						ImGui::AlignTextToFramePadding();
						ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Field_%d", i);
						ImGui::NextColumn();
						ImGui::SetNextItemWidth(-1);
						if(i >= 5)
							ui::number_field<float>(parent, "##value", dummy_members[i], 1.0f);
						else
							ui::drag_field<float>(parent, "##value", dummy_members[i], 0.01f);
						ImGui::NextColumn();
					}
					ImGui::PopID();
				}
				//ImGui::TreePop();
			}
			ImGui::PopID();
		}
	};

	// Iterate dummy objects with dummy members (all the same data)
	for(int obj_i = 0; obj_i < 3; obj_i++)
		funcs::ShowDummyObject("Object", obj_i);

	
	ui::separator(parent);
	ImGui::PopStyleVar();
	ImGui::End();
}


// [section] Example App: Long Text / ShowExampleAppLongText()

// Demonstrate/test rendering huge amount of text, and the incidence of clipping.
static void ShowExampleAppLongText(bool* p_open)
{
	ImGui::SetNextWindowSize(vec2(520, 600), ImGuiCond_FirstUseEver);
	if(!ImGui::Begin("Example: Long text display", p_open))
	{
		ImGui::End();
		return;
	}

	static int test_type = 0;
	static ImGuiTextBuffer log;
	static int lines = 0;
	ui::label(parent, "Printing unusually long amount of text.");
	ui::dropdown_field(parent, "Test type", test_type, "Single call to TextUnformatted()", "Multiple calls to Text(), clipped manually", "Multiple calls to Text(), not clipped (slow)", "");
	ui::label(parent, "Buffer contents: %d lines, %d bytes", lines, log.size());
	if(ui::button(parent, "Clear")) { log.clear(); lines = 0; }
	ImGui::SameLine();
	if(ui::button(parent, "Add 1000 lines"))
	{
		for(int i = 0; i < 1000; i++)
			log.appendf("%i The quick brown fox jumps over the lazy dog\n", lines + i);
		lines += 1000;
	}
	ImGui::BeginChild("Log");
	switch(test_type)
	{
	case 0:
		// Single call to TextUnformatted() with a big buffer
		ImGui::TextUnformatted(log.begin(), log.end());
		break;
	case 1:
	{
		// Multiple calls to Text(), manually coarsely clipped - demonstrate how to use the ImGuiListClipper helper.
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, vec2(0, 0));
		ImGuiListClipper clipper(lines);
		while(clipper.Step())
			for(int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
				ui::label(parent, "%i The quick brown fox jumps over the lazy dog", i);
		ImGui::PopStyleVar();
		break;
	}
	case 2:
		// Multiple calls to Text(), not clipped (slow)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, vec2(0, 0));
		for(int i = 0; i < lines; i++)
			ui::label(parent, "%i The quick brown fox jumps over the lazy dog", i);
		ImGui::PopStyleVar();
		break;
	}
	ImGui::EndChild();
	ImGui::End();
}

// [section] Example App: Auto Resize / ShowExampleAppAutoResize()

// Demonstrate creating a window which gets auto-resized according to its content.
static void ShowExampleAppAutoResize(bool* p_open)
{
	if(!ImGui::Begin("Example: Auto-resizing window", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}

	static int lines = 10;
	ui::label(parent, "Window will resize every-frame to the size of its content.\nNote that you probably don't want to query the window size to\noutput your content because that would create a feedback loop.");
	ui::slider_field<int>(parent, ("Number of lines", lines, 1, 20);
	for(int i = 0; i < lines; i++)
		ui::label(parent, "%*sThis is line %d", i * 4, "", i); // Pad with space to extend size horizontally
	ImGui::End();
}


// [section] Example App: Constrained Resize / ShowExampleAppConstrainedResize()

// Demonstrate creating a window with custom resize constraints.
static void ShowExampleAppConstrainedResize(bool* p_open)
{
	struct CustomConstraints // Helper functions to demonstrate programmatic constraints
	{
		static void Square(ImGuiSizeCallbackData* data) { data->DesiredSize = vec2(IM_MAX(data->DesiredSize.x, data->DesiredSize.y), IM_MAX(data->DesiredSize.x, data->DesiredSize.y)); }
		static void Step(ImGuiSizeCallbackData* data) { float step = (float)(int)(intptr_t)data->UserData; data->DesiredSize = vec2((int)(data->DesiredSize.x / step + 0.5f) * step, (int)(data->DesiredSize.y / step + 0.5f) * step); }
	};

	static bool auto_resize = false;
	static int type = 0;
	static int display_lines = 10;
	if(type == 0) ImGui::SetNextWindowSizeConstraints(vec2(-1, 0), vec2(-1, FLT_MAX));      // Vertical only
	if(type == 1) ImGui::SetNextWindowSizeConstraints(vec2(0, -1), vec2(FLT_MAX, -1));      // Horizontal only
	if(type == 2) ImGui::SetNextWindowSizeConstraints(vec2(100, 100), vec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
	if(type == 3) ImGui::SetNextWindowSizeConstraints(vec2(400, -1), vec2(500, -1));          // Width 400-500
	if(type == 4) ImGui::SetNextWindowSizeConstraints(vec2(-1, 400), vec2(-1, 500));          // Height 400-500
	if(type == 5) ImGui::SetNextWindowSizeConstraints(vec2(0, 0), vec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);                     // Always Square
	if(type == 6) ImGui::SetNextWindowSizeConstraints(vec2(0, 0), vec2(FLT_MAX, FLT_MAX), CustomConstraints::Step, (void*)(intptr_t)100); // Fixed Step

	ImGuiWindowFlags flags = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : 0;
	if(ImGui::Begin("Example: Constrained Resize", p_open, flags))
	{
		const char* desc[] =
		{
			"Resize vertical only",
			"Resize horizontal only",
			"Width > 100, Height > 100",
			"Width 400-500",
			"Height 400-500",
			"Custom: Always Square",
			"Custom: Fixed Steps (100)",
		};
		if(ui::button(parent, "200x200")) { ImGui::SetWindowSize(vec2(200, 200)); } ImGui::SameLine();
		if(ui::button(parent, "500x500")) { ImGui::SetWindowSize(vec2(500, 500)); } ImGui::SameLine();
		if(ui::button(parent, "800x200")) { ImGui::SetWindowSize(vec2(800, 200)); }
		ImGui::SetNextItemWidth(200);
		ui::dropdown_field(parent, "Constraint", type, desc, IM_ARRAYSIZE(desc));
		ImGui::SetNextItemWidth(200);
		ui::drag_field<int>(parent, "Lines", display_lines, 0.2f, 1, 100);
		ui::input_field(parent, "Auto-resize", auto_resize);
		for(int i = 0; i < display_lines; i++)
			ui::label(parent, "%*sHello, sailor! Making this line long enough for the example.", i * 4, "");
	}
	ImGui::End();
}


// [section] Example App: Simple Overlay / ShowExampleAppSimpleOverlay()

// Demonstrate creating a simple static window with no decoration + a context-menu to choose which corner of the screen to use.
static void ShowExampleAppSimpleOverlay(bool* p_open)
{
	const float DISTANCE = 10.0f;
	static int corner = 0;
	ImGuiIO& io = ImGui::GetIO();
	if(corner != -1)
	{
		vec2 window_pos = vec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		vec2 window_pos_pivot = vec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if(ImGui::Begin("Example: Simple overlay", p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ui::label(parent, "Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
		ui::separator(parent);
		if(ImGui::IsMousePosValid())
			ui::label(parent, "Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
		else
			ui::label(parent, "Mouse Position: <invalid>");
		if(ImGui::BeginPopupContextWindow())
		{
			if(ui::menu_choice(parent, "Custom", NULL, corner == -1)) corner = -1;
			if(ui::menu_choice(parent, "Top-left", NULL, corner == 0)) corner = 0;
			if(ui::menu_choice(parent, "Top-right", NULL, corner == 1)) corner = 1;
			if(ui::menu_choice(parent, "Bottom-left", NULL, corner == 2)) corner = 2;
			if(ui::menu_choice(parent, "Bottom-right", NULL, corner == 3)) corner = 3;
			if(p_open && ui::menu_choice(parent, "Close")) *p_open = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}

// [section] Example App: Manipulating Window Titles / ShowExampleAppWindowTitles()

// Demonstrate using "##" and "###" in identifiers to manipulate ID generation.
// This apply to all regular items as well. Read FAQ section "How can I have multiple widgets with the same label? Can I have widget without a label? (Yes). A primer on the purpose of labels/IDs." for details.
static void ShowExampleAppWindowTitles(bool*)
{
	// By default, Windows are uniquely identified by their title.
	// You can use the "##" and "###" markers to manipulate the display/ID.

	// Using "##" to display same title but have unique identifier.
	ImGui::SetNextWindowPos(vec2(100, 100), ImGuiCond_FirstUseEver);
	ImGui::Begin("Same title as another window##1");
	ui::label(parent, "This is window 1.\nMy title is the same as window 2, but my identifier is unique.");
	ImGui::End();

	ImGui::SetNextWindowPos(vec2(100, 200), ImGuiCond_FirstUseEver);
	ImGui::Begin("Same title as another window##2");
	ui::label(parent, "This is window 2.\nMy title is the same as window 1, but my identifier is unique.");
	ImGui::End();

	// Using "###" to display a changing title but keep a static identifier "AnimatedTitle"
	char buf[128];
	sprintf(buf, "Animated title %c %d###AnimatedTitle", "|/-\\"[(int)(ImGui::GetTime() / 0.25f) & 3], ImGui::GetFrameCount());
	ImGui::SetNextWindowPos(vec2(100, 300), ImGuiCond_FirstUseEver);
	ImGui::Begin(buf);
	ui::label(parent, "This window has a changing title.");
	ImGui::End();
}



// [section] Example App: Custom Rendering using ImDrawList API / ShowExampleAppCustomRendering()

// Demonstrate using the low-level ImDrawList to draw custom shapes.
static void ShowExampleAppCustomRendering(bool* p_open)
{
	ImGui::SetNextWindowSize(vec2(350, 560), ImGuiCond_FirstUseEver);
	if(!ImGui::Begin("Example: Custom rendering", p_open))
	{
		ImGui::End();
		return;
	}

	// Tip: If you do a lot of custom rendering, you probably want to use your own geometrical types and benefit of overloaded operators, etc.
	// Define IM_VEC2_CLASS_EXTRA in imconfig.h to create implicit conversions between your types and vec2/vec4.
	// ImGui defines overloaded operators but they are internal to imgui.cpp and not exposed outside (to avoid messing with your types)
	// In this example we are not using the maths operators!
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	if(ImGui::BeginTabBar("##TabBar"))
	{
		// Primitives
		if(ImGui::BeginTabItem("Primitives"))
		{
			static float sz = 36.0f;
			static float thickness = 4.0f;
			static vec4 col = vec4(1.0f, 1.0f, 0.4f, 1.0f);
			ui::drag_field<float>(parent, "Size", sz, 0.2f, 2.0f, 72.0f, "%.0f");
			ui::drag_field<float>(parent, "Thickness", thickness, 0.05f, 1.0f, 8.0f, "%.02f");
			ImGui::ColorEdit4("Color", col.x);
			const vec2 p = ImGui::GetCursorScreenPos();
			const ImU32 col32 = ImColor(col);
			float x = p.x + 4.0f, y = p.y + 4.0f, spacing = 8.0f;
			for(int n = 0; n < 2; n++)
			{
				// First line uses a thickness of 1.0, second line uses the configurable thickness
				float th = (n == 0) ? 1.0f : thickness;
				draw_list->AddCircle(vec2(x + sz * 0.5f, y + sz * 0.5f), sz*0.5f, col32, 6, th); x += sz + spacing;   // Hexagon
				draw_list->AddCircle(vec2(x + sz * 0.5f, y + sz * 0.5f), sz*0.5f, col32, 20, th); x += sz + spacing;  // Circle
				draw_list->AddRect(vec2(x, y), vec2(x + sz, y + sz), col32, 0.0f, ImDrawCornerFlags_All, th); x += sz + spacing;
				draw_list->AddRect(vec2(x, y), vec2(x + sz, y + sz), col32, 10.0f, ImDrawCornerFlags_All, th); x += sz + spacing;
				draw_list->AddRect(vec2(x, y), vec2(x + sz, y + sz), col32, 10.0f, ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotRight, th); x += sz + spacing;
				draw_list->AddTriangle(vec2(x + sz * 0.5f, y), vec2(x + sz, y + sz - 0.5f), vec2(x, y + sz - 0.5f), col32, th); x += sz + spacing;
				draw_list->AddLine(vec2(x, y), vec2(x + sz, y), col32, th); x += sz + spacing;                  // Horizontal line (note: drawing a filled rectangle will be faster!)
				draw_list->AddLine(vec2(x, y), vec2(x, y + sz), col32, th); x += spacing;                       // Vertical line (note: drawing a filled rectangle will be faster!)
				draw_list->AddLine(vec2(x, y), vec2(x + sz, y + sz), col32, th); x += sz + spacing;             // Diagonal line
				draw_list->AddBezierCurve(vec2(x, y), vec2(x + sz * 1.3f, y + sz * 0.3f), vec2(x + sz - sz * 1.3f, y + sz - sz * 0.3f), vec2(x + sz, y + sz), col32, th);
				x = p.x + 4;
				y += sz + spacing;
			}
			draw_list->AddCircleFilled(vec2(x + sz * 0.5f, y + sz * 0.5f), sz*0.5f, col32, 6); x += sz + spacing;     // Hexagon
			draw_list->AddCircleFilled(vec2(x + sz * 0.5f, y + sz * 0.5f), sz*0.5f, col32, 32); x += sz + spacing;    // Circle
			draw_list->AddRectFilled(vec2(x, y), vec2(x + sz, y + sz), col32); x += sz + spacing;
			draw_list->AddRectFilled(vec2(x, y), vec2(x + sz, y + sz), col32, 10.0f); x += sz + spacing;
			draw_list->AddRectFilled(vec2(x, y), vec2(x + sz, y + sz), col32, 10.0f, ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotRight); x += sz + spacing;
			draw_list->AddTriangleFilled(vec2(x + sz * 0.5f, y), vec2(x + sz, y + sz - 0.5f), vec2(x, y + sz - 0.5f), col32); x += sz + spacing;
			draw_list->AddRectFilled(vec2(x, y), vec2(x + sz, y + thickness), col32); x += sz + spacing;        // Horizontal line (faster than AddLine, but only handle integer thickness)
			draw_list->AddRectFilled(vec2(x, y), vec2(x + thickness, y + sz), col32); x += spacing + spacing;   // Vertical line (faster than AddLine, but only handle integer thickness)
			draw_list->AddRectFilled(vec2(x, y), vec2(x + 1, y + 1), col32);          x += sz;                  // Pixel (faster than AddLine)
			draw_list->AddRectFilledMultiColor(vec2(x, y), vec2(x + sz, y + sz), IM_COL32(0, 0, 0, 255), IM_COL32(255, 0, 0, 255), IM_COL32(255, 255, 0, 255), IM_COL32(0, 255, 0, 255));
			ImGui::Dummy(vec2((sz + spacing) * 9.5f, (sz + spacing) * 3));
			ImGui::EndTabItem();
		}

		if(ImGui::BeginTabItem("Canvas"))
		{
			static vector<vec2> points;
			static bool adding_line = false;
			if(ui::button(parent, "Clear")) points.clear();
			if(points.Size >= 2) { ImGui::SameLine(); if(ui::button(parent, "Undo")) { points.pop_back(); points.pop_back(); } }
			ui::label(parent, "Left-click and drag to add lines,\nRight-click to undo");

			// Here we are using InvisibleButton() as a convenience to 1) advance the cursor and 2) allows us to use IsItemHovered()
			// But you can also draw directly and poll mouse/keyboard by yourself. You can manipulate the cursor using GetCursorPos() and SetCursorPos().
			// If you only use the ImDrawList API, you can notify the owner window of its extends by using SetCursorPos(max).
			vec2 canvas_pos = ImGui::GetCursorScreenPos();            // ImDrawList API uses screen coordinates!
			vec2 canvas_size = ImGui::GetContentRegionAvail();        // Resize canvas to what's available
			if(canvas_size.x < 50.0f) canvas_size.x = 50.0f;
			if(canvas_size.y < 50.0f) canvas_size.y = 50.0f;
			draw_list->AddRectFilledMultiColor(canvas_pos, vec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), IM_COL32(50, 50, 50, 255), IM_COL32(50, 50, 60, 255), IM_COL32(60, 60, 70, 255), IM_COL32(50, 50, 60, 255));
			draw_list->AddRect(canvas_pos, vec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), IM_COL32(255, 255, 255, 255));

			bool adding_preview = false;
			ImGui::InvisibleButton("canvas", canvas_size);
			vec2 mouse_pos_in_canvas = vec2(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
			if(adding_line)
			{
				adding_preview = true;
				points.push_back(mouse_pos_in_canvas);
				if(!ImGui::IsMouseDown(0))
					adding_line = adding_preview = false;
			}
			if(ImGui::IsItemHovered())
			{
				if(!adding_line && ImGui::IsMouseClicked(0))
				{
					points.push_back(mouse_pos_in_canvas);
					adding_line = true;
				}
				if(ImGui::IsMouseClicked(1) && !points.empty())
				{
					adding_line = adding_preview = false;
					points.pop_back();
					points.pop_back();
				}
			}
			draw_list->PushClipRect(canvas_pos, vec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), true);      // clip lines within the canvas (if we resize it, etc.)
			for(int i = 0; i < points.Size - 1; i += 2)
				draw_list->AddLine(vec2(canvas_pos.x + points[i].x, canvas_pos.y + points[i].y), vec2(canvas_pos.x + points[i + 1].x, canvas_pos.y + points[i + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);
			draw_list->PopClipRect();
			if(adding_preview)
				points.pop_back();
			ImGui::EndTabItem();
		}

		if(ImGui::BeginTabItem("BG/FG draw lists"))
		{
			static bool draw_bg = true;
			static bool draw_fg = true;
			ui::input_field(parent, "Draw in Background draw list", draw_bg);
			ui::input_field(parent, "Draw in Foreground draw list", draw_fg);
			vec2 window_pos = ImGui::GetWindowPos();
			vec2 window_size = ImGui::GetWindowSize();
			vec2 window_center = vec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f);
			if(draw_bg)
				ImGui::GetBackgroundDrawList()->AddCircle(window_center, window_size.x * 0.6f, IM_COL32(255, 0, 0, 200), 32, 10 + 4);
			if(draw_fg)
				ImGui::GetForegroundDrawList()->AddCircle(window_center, window_size.y * 0.6f, IM_COL32(0, 255, 0, 200), 32, 10);
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}


// [section] Example App: Documents Handling / ShowExampleAppDocuments()

// Simplified structure to mimic a Document model
struct MyDocument
{
	const char* Name;           // Document title
	bool        Open;           // Set when the document is open (in this demo, we keep an array of all available documents to simplify the demo)
	bool        OpenPrev;       // Copy of Open from last update.
	bool        Dirty;          // Set when the document has been modified
	bool        WantClose;      // Set when the document
	vec4      Color;          // An arbitrary variable associated to the document

	MyDocument(const char* name, bool open = true, const vec4& color = vec4(1.0f, 1.0f, 1.0f, 1.0f))
	{
		Name = name;
		Open = OpenPrev = open;
		Dirty = false;
		WantClose = false;
		Color = color;
	}
	void DoOpen() { Open = true; }
	void DoQueueClose() { WantClose = true; }
	void DoForceClose() { Open = false; Dirty = false; }
	void DoSave() { Dirty = false; }

	// Display dummy contents for the Document
	static void DisplayContents(MyDocument* doc)
	{
		ImGui::PushID(doc);
		ui::label(parent, "Document \"%s\"", doc->Name);
		ImGui::PushStyleColor(ImGuiCol_Text, doc->Color);
		ui::text(parent, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
		ImGui::PopStyleColor();
		if(ui::button(parent, "Modify", vec2(100, 0)))
			doc->Dirty = true;
		ImGui::SameLine();
		if(ui::button(parent, "Save", vec2(100, 0)))
			doc->DoSave();
		ImGui::ColorEdit3("color", doc->Color.x);  // Useful to test drag and drop and hold-dragged-to-open-tab behavior.
		ImGui::PopID();
	}

	// Display context menu for the Document
	static void DisplayContextMenu(MyDocument* doc)
	{
		if(!ImGui::BeginPopupContextItem())
			return;

		char buf[256];
		sprintf(buf, "Save %s", doc->Name);
		if(ui::menu_choice(parent, buf, "CTRL+S", false, doc->Open))
			doc->DoSave();
		if(ui::menu_choice(parent, "Close", "CTRL+W", false, doc->Open))
			doc->DoQueueClose();
		ImGui::EndPopup();
	}
};

struct ExampleAppDocuments
{
	vector<MyDocument> Documents;

	ExampleAppDocuments()
	{
		Documents.push_back(MyDocument("Lettuce", true, vec4(0.4f, 0.8f, 0.4f, 1.0f)));
		Documents.push_back(MyDocument("Eggplant", true, vec4(0.8f, 0.5f, 1.0f, 1.0f)));
		Documents.push_back(MyDocument("Carrot", true, vec4(1.0f, 0.8f, 0.5f, 1.0f)));
		Documents.push_back(MyDocument("Tomato", false, vec4(1.0f, 0.3f, 0.4f, 1.0f)));
		Documents.push_back(MyDocument("A Rather Long Title", false));
		Documents.push_back(MyDocument("Some Document", false));
	}
};

// [Optional] Notify the system of Tabs/Windows closure that happened outside the regular tab interface.
// If a tab has been closed programmatically (aka closed from another source such as the Checkbox() in the demo, as opposed
// to clicking on the regular tab closing button) and stops being submitted, it will take a frame for the tab bar to notice its absence.
// During this frame there will be a gap in the tab bar, and if the tab that has disappeared was the selected one, the tab bar
// will report no selected tab during the frame. This will effectively give the impression of a flicker for one frame.
// We call SetTabItemClosed() to manually notify the Tab Bar or Docking system of removed tabs to avoid this glitch.
// Note that this completely optional, and only affect tab bars with the ImGuiTabBarFlags_Reorderable flag.
static void NotifyOfDocumentsClosedElsewhere(ExampleAppDocuments& app)
{
	for(int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
	{
		MyDocument* doc = &app.Documents[doc_n];
		if(!doc->Open && doc->OpenPrev)
			ImGui::SetTabItemClosed(doc->Name);
		doc->OpenPrev = doc->Open;
	}
}

void ShowExampleAppDocuments(bool* p_open)
{
	static ExampleAppDocuments app;

	// Options
	static bool opt_reorderable = true;
	static ImGuiTabBarFlags opt_fitting_flags = ImGuiTabBarFlags_FittingPolicyDefault_;

	if(!ImGui::Begin("Example: Documents", p_open, ImGuiWindowFlags_MenuBar))
	{
		ImGui::End();
		return;
	}

	// Menu
	if(ImGui::BeginMenuBar())
	{
		if(ImGui::BeginMenu("File"))
		{
			int open_count = 0;
			for(int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
				open_count += app.Documents[doc_n].Open ? 1 : 0;

			if(ImGui::BeginMenu("Open", open_count < app.Documents.Size))
			{
				for(int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
				{
					MyDocument* doc = &app.Documents[doc_n];
					if(!doc->Open)
						if(ui::menu_choice(parent, doc->Name))
							doc->DoOpen();
				}
				ImGui::EndMenu();
			}
			if(ui::menu_choice(parent, "Close All Documents", NULL, false, open_count > 0))
				for(int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
					app.Documents[doc_n].DoQueueClose();
			if(ui::menu_choice(parent, "Exit", "Alt+F4")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// [Debug] List documents with one checkbox for each
	for(int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
	{
		MyDocument* doc = &app.Documents[doc_n];
		if(doc_n > 0)
			ImGui::SameLine();
		ImGui::PushID(doc);
		if(ui::input_field(parent, doc->Name, &doc->Open))
			if(!doc->Open)
				doc->DoForceClose();
		ImGui::PopID();
	}

	ui::separator(parent);

	// Submit Tab Bar and Tabs
	{
		ImGuiTabBarFlags tab_bar_flags = (opt_fitting_flags) | (opt_reorderable ? ImGuiTabBarFlags_Reorderable : 0);
		if(ImGui::BeginTabBar("##tabs", tab_bar_flags))
		{
			if(opt_reorderable)
				NotifyOfDocumentsClosedElsewhere(app);

			// [DEBUG] Stress tests
			//if ((ImGui::GetFrameCount() % 30) == 0) docs[1].Open ^= 1;            // [DEBUG] Automatically show/hide a tab. Test various interactions e.g. dragging with this on.
			//if (ImGui::GetIO().KeyCtrl) ImGui::SetTabItemSelected(docs[1].Name);  // [DEBUG] Test SetTabItemSelected(), probably not very useful as-is anyway..

			// Submit Tabs
			for(int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
			{
				MyDocument* doc = &app.Documents[doc_n];
				if(!doc->Open)
					continue;

				ImGuiTabItemFlags tab_flags = (doc->Dirty ? ImGuiTabItemFlags_UnsavedDocument : 0);
				bool visible = ImGui::BeginTabItem(doc->Name, &doc->Open, tab_flags);

				// Cancel attempt to close when unsaved add to save queue so we can display a popup.
				if(!doc->Open && doc->Dirty)
				{
					doc->Open = true;
					doc->DoQueueClose();
				}

				MyDocument::DisplayContextMenu(doc);
				if(visible)
				{
					MyDocument::DisplayContents(doc);
					ImGui::EndTabItem();
				}
			}

			ImGui::EndTabBar();
		}
	}

	// Update closing queue
	static vector<MyDocument*> close_queue;
	if(close_queue.empty())
	{
		// Close queue is locked once we started a popup
		for(int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
		{
			MyDocument* doc = &app.Documents[doc_n];
			if(doc->WantClose)
			{
				doc->WantClose = false;
				close_queue.push_back(doc);
			}
		}
	}

	// Display closing confirmation UI
	if(!close_queue.empty())
	{
		int close_queue_unsaved_documents = 0;
		for(int n = 0; n < close_queue.Size; n++)
			if(close_queue[n]->Dirty)
				close_queue_unsaved_documents++;

		if(close_queue_unsaved_documents == 0)
		{
			// Close documents when all are unsaved
			for(int n = 0; n < close_queue.Size; n++)
				close_queue[n]->DoForceClose();
			close_queue.clear();
		}
		else
		{
			if(!ImGui::IsPopupOpen("Save?"))
				ImGui::OpenPopup("Save?");
			if(ImGui::BeginPopupModal("Save?"))
			{
				ui::label(parent, "Save change to the following items?");
				ImGui::SetNextItemWidth(-1.0f);
				if(ImGui::ListBoxHeader("##", close_queue_unsaved_documents, 6))
				{
					for(int n = 0; n < close_queue.Size; n++)
						if(close_queue[n]->Dirty)
							ui::label(parent, "%s", close_queue[n]->Name);
					ImGui::ListBoxFooter();
				}

				if(ui::button(parent, "Yes", vec2(80, 0)))
				{
					for(int n = 0; n < close_queue.Size; n++)
					{
						if(close_queue[n]->Dirty)
							close_queue[n]->DoSave();
						close_queue[n]->DoForceClose();
					}
					close_queue.clear();
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if(ui::button(parent, "No", vec2(80, 0)))
				{
					for(int n = 0; n < close_queue.Size; n++)
						close_queue[n]->DoForceClose();
					close_queue.clear();
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if(ui::button(parent, "Cancel", vec2(80, 0)))
				{
					close_queue.clear();
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
	}

	ImGui::End();
}
#endif

void switchUiTheme(UiWindow& ui_window, const string& name)
{
}

void example_ui(Widget& ui)
{
	static Style style = Style("Background", styles().board, [](Layout& l) {}, [](InkStyle& i) { i.m_empty = false; i.m_background_colour = rgb(0x738c99); });
	ui::widget(ui, style);
	ShowDemoWindow(ui);
}

#ifdef _00_IMGUI_EXE
bool pump(RenderSystem& render_system, BgfxContext& context, UiWindow& ui_window)
{
	bool pursue = context.begin_frame();
	pursue &= ui_window.input_frame();
	example_ui(ui_window.m_ui->begin());
	context.render_frame();
	ui_window.render_frame(240);
	render_system.end_frame();
	return pursue;
}

#ifdef MUD_PLATFORM_EMSCRIPTEN
	#include <emscripten/emscripten.h>

	RenderSystem* g_render_system = nullptr;
	UiWindow* g_window = nullptr;
	void iterate() { pump(*g_render_system, *g_window); }
#endif

int main(int argc, char *argv[])
{
	UNUSED(argc); UNUSED(argv);
#ifdef SCRIPT
	System::instance().load_modules({ &mud_obj::m(), &mud_math::m(), &mud_lang::m(), &mud_ui::m() });
#endif

#ifdef MUD_RENDERER_GL
	static GlSystem render_system = { MUD_RESOURCE_PATH };
#elif defined MUD_RENDERER_BGFX
	static BgfxSystem render_system = { MUD_RESOURCE_PATH };
#endif

	static BgfxContext context = BgfxContext(render_system, "mud ui demo", uvec2(1200, 800), false, true);

	static VgVg vg = VgVg(MUD_RESOURCE_PATH, &render_system.allocator());
	vg.setup_context();

	static UiWindow ui_window = UiWindow(context, vg);

	ui_window.init();

	style_minimal(ui_window);
	//style_imgui(ui_window, ImguiStyle::Dark);

#ifdef MUD_PLATFORM_EMSCRIPTEN
	g_render_system = &render_system;
	g_window = &ui_window;
	emscripten_set_main_loop(iterate, 0, 1);
#else
	bool pursue = true;
	while(pursue)
		pump(render_system, context, ui_window);
#endif
}
#endif
