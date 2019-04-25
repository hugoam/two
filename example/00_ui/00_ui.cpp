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

const string girl_names[] =
{
	"Maja", "Alice", "Julia", "Linnea", "Wilma", "Ella", "Elsa", "Emma", "Alva", "Olivia", "Molly", "Ebba", "Klara", "Nellie", "Agnes",
	"Isabelle", "Ida", "Elin", "Ellen", "Moa", "Emilia", "Nova", "Alma", "Saga", "Amanda", "Isabella", "Lilly", "Alicia", "Astrid",
	"Matilda", "Tuva", "Tilde", "Stella", "Felicia", "Elvira", "Tyra", "Hanna", "Sara", "Vera", "Thea", "Freja", "Lova", "Selma",
	"Meja", "Signe", "Ester", "Lovisa", "Ellie", "Lea", "Tilda", "Tindra", "Sofia", "Nora", "Nathalie", "Leia", "Filippa", "Siri",
	"Emelie", "Inez", "Edith", "Stina", "Liv", "Lisa", "Linn", "Tove", "Emmy", "Livia", "Jasmine", "Evelina", "Cornelia", "Marta",
	"Svea", "Ingrid", "My", "Rebecca", "Joline", "Mira", "Ronja", "Hilda", "Melissa", "Anna", "Frida", "Maria", "Iris", "Josefine",
	"Elise", "Elina", "Greta", "Vilda", "Minna", "Lina", "Hedda", "Nicole", "Kajsa", "Majken", "Sofie", "Annie", "Juni", "Novalie", "Hedvig"
};

const string boy_names[] =
{
	"Oscar", "William", "Lucas", "Elias", "Alexander", "Hugo", "Oliver", "Theo", "Liam", "Leo", "Viktor", "Erik", "Emil",
	"Isak", "Axel", "Filip", "Anton", "Gustav", "Edvin", "Vincent", "Arvid", "Albin", "Ludvig", "Melvin", "Noah", "Charlie", "Max",
	"Elliot", "Viggo", "Alvin", "Alfred", "Theodor", "Adam", "Olle", "Wilmer", "Benjamin", "Simon", "Nils", "Noel", "Jacob", "Leon",
	"Rasmus", "Kevin", "Linus", "Casper", "Gabriel", "Jonathan", "Milo", "Melker", "Felix", "Love", "Ville", "Sebastian", "Sixten",
	"Carl", "Malte", "Neo", "David", "Joel", "Adrian", "Valter", "Josef", "Jack", "Hampus", "Samuel", "Mohammed", "Alex", "Tim",
	"Daniel", "Vilgot", "Wilhelm", "Harry", "Milton", "Maximilian", "Robin", "Sigge", "Mans", "Eddie", "Elton", "Vidar", "Hjalmar",
	"Loke", "Elis", "August", "John", "Hannes", "Sam", "Frank", "Svante", "Marcus", "Mio", "Otto", "Ali", "Johannes", "Fabian",
	"Ebbe", "Aron", "Julian", "Elvin", "Ivar"
};

enum Gender
{
	MALE,
	FEMALE
};

struct Person
{
	string m_name;
	Gender m_gender;
	bool m_selected;
	bool m_removed;
};

vector<Person> person_vector()
{
	vector<Person> persons;
	for(const string& name : boy_names)
		persons.push_back({ name, MALE, false, false });
	for(const string& name : girl_names)
		persons.push_back({ name, FEMALE, false, false });
	return persons;
}

vector<Person> persons = person_vector();

void custom_element(Widget& parent, cstring name, cstring gender, bool& selected, bool& removed)
{
	Widget& self = ui::row(parent);
	ui::checkbox(self, selected);
	ui::icon(self, "(tbb/icon48)");
	{
		Widget& stack = ui::stack(self);
		ui::label(stack, name);
		ui::label(stack, gender);
	}
	if(ui::button(self, ui::window_styles().close_button, "").activated())
		removed = true;
};

void ex_custom_list(Widget& parent)
{
	static string criteria = "";

	//ScrollSheet& list = ui::select_list(parent);
	ScrollSheet& list = ui::scroll_sheet(parent);

	for(Person& person : persons)
		if(ui::filter(criteria, person.m_name) && !person.m_removed)
			custom_element(*list.m_body, person.m_name.c_str(), person.m_gender == MALE ? "Male" : "Female", person.m_selected, person.m_removed);

	ui::type_in(parent, criteria);
}

void ex_filtered_list(Widget& parent)
{
	static string criteria = "";

	ScrollSheet& list = ui::scroll_sheet(parent);

	for(Person& person : persons)
		if(ui::filter(criteria, person.m_name))
			ui::label(*list.m_body, person.m_name.c_str());

	ui::type_in(parent, criteria);
}

void ex_scroll_list(Widget& parent)
{
	Widget& sequence = ui::layout(parent);

	{
		Widget& sheet = ui::scroll_sheet(sequence);
		for(int i = 0; i < 100; i++)
			ui::label(sheet, ("Element " + to_string(i)).c_str());
	}

	{
		Widget& sheet = ui::scroll_sheet(sequence);
		for(int i = 0; i < 100; i++)
			ui::button(sheet, ("Element " + to_string(i)).c_str());
	}
}

void ex_text_editor(Widget& parent)
{
	{
		Widget& menubar = ui::menubar(parent);
		{
			Widget* menu = ui::menu(menubar, "Menu").m_body;
			if(menu)
			{
				ui::menu_choice(*menu, "Redo");
				ui::menu_choice(*menu, "Undo");
				{
					Widget* submenu = ui::menu(*menu, "Change Font", true).m_body;
					if(submenu)
					{
						ui::menu_choice(*submenu, "Arial");
						ui::menu_choice(*submenu, "Myriad");
					}
				}
			}
		}

		ui::button(menubar, "Open File");
		ui::button(menubar, "Undo");
		ui::button(menubar, "Redo");
	}

	static string text = "This is an example text editor field\nYou can use it as any common editor";
	//ui::text_edit(parent, text);
	ui::code_edit(parent, text);
}

void ex_application(Widget& parent)
{
	{
		Widget& menubar = ui::menubar(parent);

		{
			Widget* menu = ui::menu(menubar, "File").m_body;
			if(menu)
			{
				ui::menu_choice(*menu, "Open");
				ui::menu_choice(*menu, "Save");
				{
					Widget* submenu = ui::menu(*menu, "Save As", true).m_body;
					if(submenu)
					{
						ui::menu_choice(*submenu, "Save As JPEG");
						ui::menu_choice(*submenu, "Save As PNG");
						ui::menu_choice(*submenu, "Save As PDF");
					}
				}
				ui::menu_choice(*menu, "Close");
			}
		}

		{
			Widget* menu = ui::menu(menubar, "Edit").m_body;
			if(menu)
			{
				ui::menu_choice(*menu, "Redo");
				ui::menu_choice(*menu, "Undo");
			}
		}

		{
			Widget* menu = ui::menu(menubar, "Help").m_body;
			if(menu)
			{
				ui::menu_choice(*menu, "About kiUi");
			}
		}
	}

	{
		Widget& tools = ui::tooldock(parent);
		{
			Widget& toolbar = ui::toolbar(tools, true);
			ui::toolbutton(toolbar, "(arrow_left_15)");
			ui::toolbutton(toolbar, "(arrow_right_15)");
		}
		{
			Widget& toolbar = ui::toolbar(tools, true);
			ui::toolbutton(toolbar, "(file_15)");
			ui::toolbutton(toolbar, "(folder_15)");
			ui::toolbutton(toolbar, "(close_15)");
		}
	}
}

#ifdef SCRIPT
LuaInterpreter& lua_interpreter()
{
	static LuaInterpreter lua;
	lua.declare_types();
	return lua;
}

void ex_console(Widget& parent)
{
	static LuaInterpreter& lua = lua_interpreter();

	static string feed = "console v0.1";
	static string line = "type lua code here";
	static string command = "";

	ui::console(parent, feed, line, command);
	if(command != "")
	{
		lua.call(command.c_str());
		feed += "\n<< " + lua.flush();
		command = "";
	}
}
#endif

void ex_script_editor(Widget& parent)
{
	static string text = "This is an example text editor field\nYou can use it as any common editor vec3 float";
	ui::code_edit(parent, text);
}

void ex_dockspace(Widget& parent)
{
	//MasterDockline::style().m_layout.d_weights = { 0.2f, 0.6f, 0.2f };

	Widget& board = ui::board(parent);

	static Docksystem docksystem;

	Docker& dockspace = ui::dockspace(board, docksystem);
	Docker& dockbar = ui::dockbar(board, docksystem);

	docksystem.m_dockers = { &dockspace, &dockbar };

	if(Widget* dock = ui::dockitem(dockspace, "Dock 0", { 0U, 0U }))
		ex_controls(*dock);

	if(Widget* dock = ui::dockitem(dockspace, "Dock 1", { 0U, 1U }))
		ex_inline_controls(*dock);

	if(Widget* dock = ui::dockitem(dockspace, "Dock 2", { 0U, 2U }))
		ex_table(*dock);

	if(Widget* dock = ui::dockitem(dockbar, "Options", { 0U }))
		ex_controls(*dock);

}

struct NodeCable
{
	struct Plug
	{
		Node* m_node;
		bool m_input;
		size_t m_index;

		bool operator==(const Plug& other) const { return m_node == other.m_node && m_input == other.m_input && m_index == other.m_index; }
	};

	Plug m_in;
	Plug m_out;
};

class CanvasExample
{
public:
	CanvasExample() {}

	NodeCable& connect(NodeCable::Plug in, NodeCable::Plug out)
	{
		m_cables.push_back(NodeCable{ in, out });
		return m_cables.back();
	}

	void disconnect(NodeCable::Plug plug)
	{
		remove_if(m_cables, [=](const NodeCable& cable) { return cable.m_in == plug || cable.m_out == plug; });
	}

	vector<NodeCable> m_cables;
};

void ex_nodes(Widget& parent)
{
	Widget& tools = ui::toolbar(parent);
	CanvasExample model;

	Canvas& canvas = ui::canvas(parent, 4);

	if(ui::toolbutton(tools, "autolayout").activated())
		ui::canvas_autolayout(canvas);
	
	//if(ui::toolbutton(tools, "autolayout selected").activated())
		//

	{
		static vec2 position = { 150.f, 250.f };
		Node& node = ui::node(canvas, "A Node", position);
		ui::node_input(node, "a", "", Colour::Cyan);
		ui::node_input(node, "b", "", Colour::Cyan);
		ui::node_output(node, "result");
	}

	{
		static vec2 position = { 350.f, 150.f };
		Node& node = ui::node(canvas, "A Node", position);
		ui::node_input(node, "a");
		ui::node_input(node, "b");
		ui::node_output(node, "result", "", Colour::Red);
	}

	{
		static vec2 position = { 450.f, 450.f };
		Node& node = ui::node(canvas, "Another Node", position);
		ui::node_input(node, "u", "", Colour::Pink);
		ui::node_input(node, "v", "", Colour::Pink);
		ui::node_output(node, "x", "", Colour::Cyan);
		ui::node_output(node, "y", "", Colour::Cyan);
		ui::node_output(node, "z", "", Colour::Cyan);
	}

	{
		static vec2 position = { 800.f, 200.f };
		Node& node = ui::node(canvas, "End Node", position);
		ui::node_input(node, "input 1");
		ui::node_input(node, "input 2");
	}

	ui::canvas_connect(canvas);

	//for(NodeCable& cable : model.m_cables)
	//	ui::node_cable(*canvas.m_cables, canvas.m_plan->m_frame, cable.m_out.m_node->m_frame, cable.m_out.m_node->m_frame, Colour::NeonGreen, Colour::Red);

}

void ex_tabs(Widget& parent)
{
	Tabber& tabber = ui::tabber(parent);

	Widget* tab0 = ui::tab(tabber, "Tab 0");
	if(tab0)
		ex_table(*tab0);

	Widget* tab1 = ui::tab(tabber, "Tab 1");
	if(tab1)
		ex_inline_controls(*tab1);

	Widget* tab2 = ui::tab(tabber, "Tab 2");
	if(tab2)
		ex_controls(*tab2);
}

void ex_table(Widget& parent)
{
	{
		Widget& table = ui::table(parent, { "ID", "Name", "Path", "Flags" }, { 0.25f, 0.25f, 0.25f, 0.25f });

		cstring contents[3][4] = {
			{ "0000", "Robert",    "/path/robert",    "...." },
			{ "0001", "Stephanie", "/path/stephanie", "line 1" },
			{ "0002", "C64",       "/path/computer",  "...." }
		};

		for(auto& r : contents)
		{
			Widget& row = ui::row(table);
			for(cstring name : r)
				ui::label(row, name);
		}
	}

	{
		Widget& table = ui::table(parent, { "Column 0", "Column 1", "Column 3" }, { 0.33f, 0.33f, 0.33f });

		{
			Widget& row = ui::row(table);
			for(cstring name : { "Hello", "kiUi", "World!" })
				ui::label(row, name);
		}

		{
			Widget& row = ui::row(table);
			for(cstring name : { "Banana", "Apple", "Corniflower" })
				ui::button(row, name);
		}

		static uint32_t radio_val = 0;
		ui::radio_switch(table, { "radio a", "radio b", "radio c" }, radio_val);

		{
			Widget& row = ui::row(table);

			for(const string& c : { "A", "B", "C" })
			{
				Widget* expandbox = ui::expandbox(row, (string("Category") + c).c_str()).m_body;
				if(expandbox)
					ui::label(*expandbox, "Blah blah blah");
			}
		}
	}

	{
		Widget& table = ui::table(parent, { "Left", "Right" }, { 0.5f, 0.5f });

		{
			Widget& row = ui::row(table);
			float red = 0.05f;
			float blue = 0.05f;
			ui::number_field<float>(row, "Red", red);
			ui::number_field<float>(row, "Blue", blue);
		}

		{
			Widget& row = ui::row(table);
			string s0 = "The quick brown fox jumps over the lazy dog.";
			string s1 = "The quick brown fox jumps over the lazy dog.";
			ui::type_in(row, s0);
			ui::type_in(row, s1);
		}

		{
			Widget& row = ui::row(table);
			ui::label(row, "Hello Left");
			ui::label(row, "Hello Right");
		}
	}
}

void ex_tree(Widget& parent)
{
	Widget& tree = ui::tree(parent);
	Widget* root_node = ui::tree_node(tree, "Tree").m_body;

	if(!root_node) return;

	for(size_t i = 0; i < 5; i++)
	{
		Widget* node = ui::tree_node(*root_node, ("Child " + to_string(i)).c_str(), false, true).m_body;
		for(size_t j = 0; j < 5; j++)
			if(node)
				node = ui::tree_node(*node, ("Child " + to_string(i) + " : " + to_string(j)).c_str(), j == 4, true).m_body;
	}

	for(size_t i = 0; i < 5; i++)
	{
		Widget* node = ui::tree_node(*root_node, ("Child " + to_string(5 + i)).c_str()).m_body;
		if(node)
		{
			Widget& row = ui::row(*node);
			ui::label(row, "Blah blah");
			ui::button(row, "Print");
		}
	}
}

void ex_table_tree(Widget& parent)
{
	Widget& tree = ui::tree(parent);

	ui::tree_node(tree, "Inside a tree...");
	ui::tree_node(tree, "Node 1 (with borders)");

	Widget* node2 = ui::tree_node(tree, "Table Node 0").m_body;
	if(node2)
	{
		ui::label(*node2, "aaa");
		ui::label(*node2, "bbb");
		ui::label(*node2, "ccc");
		ui::label(*node2, "ddd");
	}

	Widget* node3 = ui::tree_node(tree, "Table Node 1").m_body;
	if(node3)
	{
		ui::label(*node3, "eee");
		ui::label(*node3, "fff");
		ui::label(*node3, "ggg");
		ui::label(*node3, "hhh");
	}
}

void ex_markup_text(Widget& parent)
{
	ui::text(parent, "This is a long paragraph. The text should automatically wrap on the edge of the window. The current implementation follows no word splitting rules, text is just split at the last character.");
	ui::slider_field<float>(parent, "Wrap width", AutoStat<float>(200.f, -20.f, 600.f, 0.1f), false);

	{
		Widget& row = ui::row(parent);
		ui::icon(row, "(bullet)");
		ui::label(row, "Bullet point 1");
	}

	{
		Widget& row = ui::row(parent);
		ui::icon(row, "(bullet)");
		ui::text(row, "Bullet point 2\nOn multiple lines");
	}

	{
		Widget& row = ui::row(parent);
		ui::icon(row, "(bullet)");
		ui::label(row, "Bullet point 3");
	}
}

void ex_controls(Widget& parent)
{
	Widget& table = ui::table(parent, { "input", "label" }, { 0.7f, 0.3f });

	static bool val_bool = false;
	static string val_string = "Hello, world!";
	static uint32_t val_radio = 0;

	ui::input_field<bool>(table, "checkbox input", val_bool, true);
	ui::radio_field(table, "radio input", { "radio a", "radio b", "radio c" }, val_radio, Axis::X, true);

	static uint32_t val_choice = 0;
	static vector<cstring> choices = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" };
	ui::dropdown_field(table, "dropdown input", choices, val_choice, true);
	ui::typedown_field(table, "typedown input", choices, val_choice, true);

	ui::input_field<string>(table, "string input", val_string, true);

	static int val_int = 123;
	static float val_float_input = 0.001f;
	ui::number_field<int>(table, "int input", { val_int, { 0, 1000, 1 } }, true);
	ui::number_field<float>(table, "float input", { val_float_input, { 0.f, 100.f, 0.001f } }, true);

	static int val_int_0_3 = 2;
	static int val_int_100_100 = 0;
	ui::slider_field<int>(table, "int 0..3", { val_int_0_3, { 0, 3, 1 } }, true);
	ui::slider_field<int>(table, "int -100..100", { val_int_100_100, { -100, 100, 1 } }, true);

	static float val_float = 1.123f;
	ui::slider_field<float>(table, "float input", { val_float, { 0.0f, 2.0f, 0.001f } }, true);
	//table.emplace<SliderFloat>("log float", AutoStat<float>(0.f, 0.0f, 10.0f, 1.f));
	//table.emplace<SliderFloat>("signed log float", AutoStat<float>(0.f, -10.0f, 10.0f, 1.f));
	//table.emplace<SliderFloat>("unbound float", AutoStat<float>(123456789.0f, -FLT_MAX, FLT_MAX, 1.f));

	// table.emplace<SliderAngle>("angle", 0.f);

	// table.emplace<InputVec3>("slider float3", 0.0f, 1.0f);

	static Colour val_colour0 = Colour::Red;
	static Colour val_colour1 = Colour::Green;

	ui::input_field<Colour>(table, "color input", val_colour0, true);
	ui::color_field(table, "color input", val_colour1, true);
}

void ex_focus_tabbing(Widget& parent)
{
	ui::label(parent, "Use TAB/SHIFT+TAB to cycle through keyboard editable fields.");

	string s1 = "1";
	string s2 = "2";
	string s3 = "3";
	string s4 = "4 (tab skip)";
	string s5 = "5";

	ui::type_in(parent, s1);
	ui::type_in(parent, s2);
	ui::type_in(parent, s3);
	ui::type_in(parent, s4);
	ui::type_in(parent, s5);
}

void ex_file_browser(Widget& parent)
{
	static string path = "..";
	ui::file_browser(parent, path);
}

void ex_file_tree(Widget& parent)
{
	ui::file_tree(parent, "..");
}

void ex_inline_controls(Widget& parent)
{
	{
		Widget& row = ui::row(parent);
		ui::label(row, "Hello");
		ui::label(row, "World");
	}

	{
		Widget& row = ui::row(parent);
		ui::button(row, "Banana");
		ui::button(row, "Apple");
		ui::button(row, "Corniflower");
	}

	{
		Widget& row = ui::row(parent);
		ui::label(row, "Small buttons");
		ui::button(row, "Like this one");
		ui::label(row, "can fit within a text block.");
	}

	{
		Widget& row = ui::row(parent);
		static bool values[4] = { false, false, false, false };
		ui::input_field<bool>(row, "My", values[0]);
		ui::input_field<bool>(row, "Tailor", values[1]);
		ui::input_field<bool>(row, "Is", values[2]);
		ui::input_field<bool>(row, "Rich", values[3]);
	}

	{
		Widget& row = ui::row(parent);
		static float values[3] = { 0.f, 0.f, 0.f };
		StatDef<float> def = {};
		ui::number_field<float>(row, "X", { values[0], def });
		ui::number_field<float>(row, "Y", { values[1], def });
		ui::number_field<float>(row, "Z", { values[2], def });
	}
}

void ex_progress_dialog(Widget& parent)
{
	static float percentage = 0.57f;
	ui::fill_bar(parent, percentage);
	ui::slider_field<float>(parent, "Set progress", { percentage, { 0.f, 1.f, 0.01f } }, false);
}

WindowState window_state = WINDOW_DEFAULT;

void ex_window(Widget& parent)
{
	Widget& window = ui::window(parent, "Test Window", window_state);
	ex_window_page(*window.m_body);
}

void ex_window_page(Widget& parent)
{
	ui::text(parent, "kiui says hello.\n" "line breaks can happen in a label");

	{
		Widget* expandbox = ui::expandbox(parent, "Help").m_body;
		if(expandbox)
			ui::text(*expandbox, "This window is being created by the ex_window_page() function.\nPlease refer to the code for programming reference.\n\nUser Guide:");
	}

	{
		Widget* expandbox = ui::expandbox(parent, "Window options").m_body;
		if(expandbox)
		{
			ui::flag_field(*expandbox, "titlebar", (uint32_t&)window_state, 1, true);
			ui::flag_field(*expandbox, "closable", (uint32_t&)window_state, 3, true);
			ui::flag_field(*expandbox, "movable", (uint32_t&)window_state, 4, true);
			ui::flag_field(*expandbox, "resizable", (uint32_t&)window_state, 5, true);

			static float alpha = 0.f; //[&window](float alpha) { window.frame().d_inkstyle->m_background_colour.m_a = alpha; }
			ui::slider_field<float>(*expandbox, "fill alpha", AutoStat<float>(alpha, { 0.f, 1.f, 0.1f }), true);
		}
	}

	{
		Widget* expandbox = ui::expandbox(parent, "Widgets").m_body;
		if(expandbox)
			ex_controls(*expandbox);
	}

	{
		Widget* expandbox = ui::expandbox(parent, "Table").m_body;
		if(expandbox)
			ex_table(*expandbox);
	}
}

void ex_debug_dock(Widget& parent)
{
	static Docksystem docksystem;

	Dockbar& tooldock = ui::dockbar(parent, docksystem);

	{
		Widget* options = ui::dockitem(tooldock, "Options", { 0U });
		UNUSED(options);

		//VgRenderer& renderer = *Frame::s_renderer;
		//ui::input_field<string>(tooldock, "Debug draw filter", renderer.m_debug_filter);
		//ui::input_field<bool>(tooldock, "Debug draw Frame", renderer.m_debug_frame_rect);
		//ui::input_field<bool>(tooldock, "Debug draw Padding", renderer.m_debug_padded_rect);
		//ui::input_field<bool>(tooldock, "Debug draw Content", renderer.m_debug_content_rect);
		//ui::input_field<bool>(tooldock, "Debug draw Clip", renderer.m_debug_clip_rect);
	}
}

void switchUiTheme(UiWindow& ui_window, const string& name)
{
#if STYLE_SHEETS
	string clean_name = to_lower(replace_all(name, " ", "_"));
	if(name == "Default")
		set_default_style_sheet(*ui_window.m_styler);
	else
		set_style_sheet(*ui_window.m_styler, (string(ui_window.m_resource_path) + "interface/styles/" + clean_name + ".yml").c_str());

	//ui_window.m_styler->style(CustomElement::style()).m_layout.d_align = Dim<Align>(LEFT, CENTER);
#endif
}

using Sample = void(*)(Widget&);

enum class SampleId : uint32_t
{
	Application,
	Console,
	ScriptEditor,
	Dockspace,
	Nodes,
	Window,
	FilteredList,
	CustomList,
	TextEditor,
	Tabs,
	Table,
	Tree,
	Controls,
	FileBrowser,
	FileTree,
	ProgressDialog,
	Invalid,
};

cstring sample_names[] =
{
	"Application",
#ifdef SCRIPT
	"Console",
#endif
	"ScriptEditor",
	"Dockspace",
	"Nodes",
	"Window",
	"FilteredList",
	"CustomList",
	"TextEditor",
	"Tabs",
	"Table",
	"Tree",
	"Controls",
	"FileBrowser",
	"FileTree",
	"ProgressDialog"
};

Sample samples[] =
{
	ex_application,
#ifdef SCRIPT
	ex_console,
#endif
	ex_script_editor,
	ex_dockspace,
	ex_nodes,
	ex_window_page,
	ex_filtered_list,
	ex_custom_list,
	ex_text_editor,
	ex_tabs,
	ex_table,
	ex_tree,
	ex_controls,
	ex_file_browser,
	ex_file_tree,
	ex_progress_dialog,
};

using SampleMap = const map<SampleId, Sample>;

void example_ui(Widget& root_sheet)
{
	static cstring themes[6] = { "Minimal", "Vector", "Blendish Clear", "Blendish Dark", "TurboBadger", "MyGui" };

	static string active_theme = "Minimal";
	static vector<SampleId> active_window_samples = {};
	static SampleId active_board_sample = SampleId::Application;

	Widget& header = ui::header(root_sheet);

	ui::label(header, "Pick a demo sample : ");

	static SampleId selected = SampleId::Application;
	if(ui::dropdown_input(header, sample_names, (uint32_t&)selected))
	{
		if(selected < SampleId::Window && selected != active_board_sample)
			active_board_sample = selected;
		else if(selected >= SampleId::Window)
			active_window_samples.push_back(selected);
	}

	ui::label(header, "Switch theme : ");

	static uint32_t theme = 0;
	if(ui::dropdown_input(header, themes, theme))
	{
		switchUiTheme(root_sheet.ui_window(), themes[theme]);
		active_theme = themes[theme];
	}

	Widget& board = ui::board(root_sheet);
	Widget& layout = ui::layout(board);
	Widget& windows = ui::screen(layout);

	//ex_debug_dock(layout);

	if(active_board_sample != SampleId::Invalid)
	{
		samples[size_t(active_board_sample)](layout);
	}

	size_t index = 0;
	for(SampleId& sample : active_window_samples)
	{
		if(sample != SampleId::Invalid)
		{
			cstring name = sample_names[size_t(sample)];
			Widget& window = ui::window(windows, name, window_state, (void*)index);
			if(window.m_body)
			{
				ScrollSheet& scrollsheet = ui::scroll_sheet(*window.m_body);
				samples[size_t(sample)](*scrollsheet.m_body);
			}
			else
			{
				sample = SampleId::Invalid;
			}
		}
		index++;
	}
}

#ifdef _00_UI_EXE
bool pump(RenderSystem& render_system, BgfxContext& context, UiWindow& ui_window)
{
	bool pursue = context.begin_frame();
	pursue &= ui_window.input_frame();
	example_ui(ui_window.m_ui->begin());
	context.render_frame();
	//bgfx::setViewFrameBuffer(240, context.m_target->m_backbuffer.m_fbo);
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

	//context.m_vg = m_vg.get();
	//context.m_reset_vg = [](GfxWindow& context, Vg& vg) { return vg.load_texture(context.m_target->m_diffuse.m_tex.idx); };

	vg.setup_context();

	static UiWindow ui_window = UiWindow(context, vg);

	//switchUiTheme(ui_window, "Minimal");
	switchUiTheme(ui_window, "Blendish Dark");
	//switchUiTheme(ui_window, "Blendish");
	//switchUiTheme(ui_window, "TurboBadger");
	//switchUiTheme(ui_window, "MyGUI");

	ui_window.init();
	//m_ui = m_ui_window.m_ui.get();

	style_minimal(ui_window);

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
