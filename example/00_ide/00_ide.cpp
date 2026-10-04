#include <infra/Cpp20.h>
import two.frame;

using namespace two;

#include <00_ide/00_ide.h>

namespace
{
	const string c_root = string(TWO_RESOURCE_PATH) + "/../";

	// a file or a folder of the repository, scanned the first time it's shown open
	struct FileNode
	{
		string name;
		string path;
		bool folder = false;
		bool scanned = false;
		vector<FileNode> children;
		cstring icon = nullptr;		// overrides the icon deduced from the kind of node
		bool project = false;
		bool open = false;

		cstring image() const
		{
			auto is = [&](const string& extension) { return has_suffix(name, extension); };
			if(icon) return icon;
			if(project) return "(vs/cpp_project_node)";
			if(folder) return open ? "(vs/folder_opened)" : "(vs/folder_closed)";
			if(is(".cpp") || is(".c") || is(".cc")) return "(vs/cpp_file_node)";
			if(is(".h") || is(".hpp")) return "(vs/cpp_header_file)";
			return "(vs/document)";
		}

		void scan()
		{
			if(scanned || !folder) return;
			scanned = true;
			visit_folders(path, [&](const string& name) { children.push_back({ name, path + "/" + name, true }); });
			visit_files(path, [&](const string& name) { children.push_back({ name, path + "/" + name, false }); });
		}
	};

	// a source file opened in an editor tab
	struct Document
	{
		string name;
		string path;
		string text;
		bool loaded = false;

		uint32_t scope = 0;
		uint32_t symbol = 0;
		uint32_t zoom = 3;

		void load()
		{
			if(loaded) return;
			loaded = true;
			text = file_exists(path) ? read_text_file(path) : "// " + path + " not found";
		}
	};

	struct Ide
	{
		Ide()
		{
			struct Open { cstring name; cstring path; };
			const Open opened[] =
			{
				{ "ui.meta.cpp", "src/meta/ui.meta.cpp" }, { "vector", "src/infra/Vector.h" }, { "LayoutTree.cpp", "src/ui/Frame/LayoutTree.cpp" },
				{ "Graph.h", "src/tree/Graph.h" }, { "DockStruct.cpp", "src/ui/DockStruct.cpp" }, { "Shell.cpp", "src/frame/Shell.cpp" },
				{ "Key.h", "src/tree/Key.h" }, { "Dock.cpp", "src/ui/Dock.cpp" }, { "InputDevice.cpp", "src/ctx/InputDevice.cpp" },
				{ "00_ui.cpp", "example/00_ui/00_ui.cpp" },
			};
			for(const Open& open : opened)
				this->open(open.name, c_root + open.path);

			// the folders of a group are its projects
			auto group = [](cstring name, const string& path)
			{
				FileNode node = { name, path, true };
				node.scan();
				for(FileNode& child : node.children)
					child.project = child.folder;
				return node;
			};
			m_solution = { "Solution 'two' (97 of 104 projects)", c_root, true, true };
			m_solution.icon = "(vs/solution)";
			m_solution.children.push_back(group("3rdparty", c_root + "3rdparty"));
			m_solution.children.push_back(group("examples", c_root + "example"));
			m_solution.children.push_back(group("lib", c_root + "src"));
		}

		Document& open(const string& name, const string& path)
		{
			for(unique<Document>& document : m_documents)
				if(document->path == path)
					return *document;
			m_documents.push_back(make_unique<Document>(Document{ name, path }));
			return *m_documents.back();
		}

		Docksystem m_docksystem;
		vector<unique<Document>> m_documents;
		FileNode m_solution;

		string m_search = "";
		string m_explorer_search = "";
		string m_commit_message = "";
		uint32_t m_configuration = 0;
		uint32_t m_platform = 0;
		uint32_t m_arguments = 0;
		uint32_t m_debugger = 0;
		uint32_t m_scope = 0;
		uint32_t m_output_source = 0;

		string m_output =
			"1>D:\\dev\\two\\example\\00_imgui\\00_imgui.cpp(2989,3): warning C4390: ';': empty controlled statement found; is this the intent?\n"
			"1>          ;// style = *ref;\n"
			"1>          ^\n"
			"1>  00_imgui.cpp\n"
			"1>     Creating library ..\\..\\win64_vs2026\\bin\\00_imgui_d.lib and object ..\\..\\win64_vs2026\\bin\\00_imgui_d.exp\n"
			"1>  00_imgui.vcxproj -> D:\\dev\\two\\build\\win64_vs2026\\bin\\00_imgui_d.exe\n"
			"========== Build: 1 succeeded, 0 failed, 29 up-to-date, 0 skipped ==========\n"
			"========== Build completed at 01:31 and took 03.249 seconds ==========\n";
	};

	void titlebar(Widget& parent, Ide& ide)
	{
		Widget& menubar = ui::menubar(key(), parent);

		ui::icon(key(), menubar, "(vs/visual_studio)");

		if(Widget* menu = ui::menu(key(), menubar, "File").m_body)
		{
			if(Widget* submenu = ui::menu(key(), *menu, "New", true).m_body)
			{
				ui::menu_choice(key(), *submenu, "Project...", "Ctrl+Shift+N");
				ui::menu_choice(key(), *submenu, "File...", "Ctrl+N");
			}
			if(Widget* submenu = ui::menu(key(), *menu, "Open", true).m_body)
			{
				ui::menu_choice(key(), *submenu, "Project/Solution...", "Ctrl+Shift+O");
				ui::menu_choice(key(), *submenu, "Folder...", "Ctrl+Shift+Alt+O");
				ui::menu_choice(key(), *submenu, "File...", "Ctrl+O");
			}
			ui::menu_choice(key(), *menu, "Save Solver.cpp", "Ctrl+S");
			ui::menu_choice(key(), *menu, "Save All", "Ctrl+Shift+S");
			ui::menu_option(key(), *menu, "Close Solution", nullptr, false);
			ui::menu_choice(key(), *menu, "Exit", "Alt+F4");
		}

		if(Widget* menu = ui::menu(key(), menubar, "Edit").m_body)
		{
			ui::menu_choice(key(), *menu, "Undo", "Ctrl+Z");
			ui::menu_choice(key(), *menu, "Redo", "Ctrl+Y");
			ui::menu_choice(key(), *menu, "Cut", "Ctrl+X");
			ui::menu_choice(key(), *menu, "Copy", "Ctrl+C");
			ui::menu_choice(key(), *menu, "Paste", "Ctrl+V");
			if(Widget* submenu = ui::menu(key(), *menu, "Find and Replace", true).m_body)
			{
				ui::menu_choice(key(), *submenu, "Quick Find", "Ctrl+F");
				ui::menu_choice(key(), *submenu, "Quick Replace", "Ctrl+H");
				ui::menu_choice(key(), *submenu, "Find in Files", "Ctrl+Shift+F");
			}
			ui::menu_choice(key(), *menu, "Go To All", "Ctrl+T");
		}

		if(Widget* menu = ui::menu(key(), menubar, "View").m_body)
		{
			ui::menu_choice(key(), *menu, "Solution Explorer", "Ctrl+Alt+L");
			ui::menu_choice(key(), *menu, "Git Changes", "Ctrl+0, Ctrl+G");
			ui::menu_choice(key(), *menu, "Properties Window", "F4");
			ui::menu_choice(key(), *menu, "Output", "Ctrl+Alt+O");
			ui::menu_choice(key(), *menu, "Find Symbol Results", "Ctrl+Alt+F12");
		}

		ui::menu(key(), menubar, "Git");
		ui::menu(key(), menubar, "Project");

		if(Widget* menu = ui::menu(key(), menubar, "Build").m_body)
		{
			ui::menu_choice(key(), *menu, "Build Solution", "Ctrl+Shift+B");
			ui::menu_choice(key(), *menu, "Rebuild Solution");
			ui::menu_choice(key(), *menu, "Clean Solution");
			ui::menu_choice(key(), *menu, "Build two_ui", "Ctrl+B");
		}

		if(Widget* menu = ui::menu(key(), menubar, "Debug").m_body)
		{
			ui::menu_choice(key(), *menu, "Start Debugging", "F5");
			ui::menu_choice(key(), *menu, "Start Without Debugging", "Ctrl+F5");
			ui::menu_choice(key(), *menu, "Attach to Process...", "Ctrl+Alt+P");
			ui::menu_choice(key(), *menu, "Toggle Breakpoint", "F9");
		}

		ui::menu(key(), menubar, "Test");
		ui::menu(key(), menubar, "Tools");
		ui::menu(key(), menubar, "Extensions");
		ui::menu(key(), menubar, "Window");

		if(Widget* menu = ui::menu(key(), menubar, "Help").m_body)
			ui::menu_choice(key(), *menu, "About two");

		ui::type_in(key(), menubar, ide.m_search);
		ui::label(key(), menubar, "two");

		ui::spacer(key(), menubar);

		ui::label(key(), menubar, "HA");
		ui::toolbutton(key(), menubar, "(vs/close)");
	}

	void toolbars(Widget& parent, Ide& ide)
	{
		Widget& tools = ui::tooldock(key(), parent);

		Widget& navigation = ui::toolbar(key(), tools, true);
		ui::toolbutton(key(), navigation, "(vs/backwards)");
		ui::toolbutton(key(), navigation, "(vs/forwards)");

		Widget& files = ui::toolbar(key(), tools, true);
		ui::toolbutton(key(), files, "(vs/new_item)");
		ui::toolbutton(key(), files, "(vs/open_file)");
		ui::toolbutton(key(), files, "(vs/save)");
		ui::toolbutton(key(), files, "(vs/save_all)");

		Widget& edit = ui::toolbar(key(), tools, true);
		ui::toolbutton(key(), edit, "(vs/undo)");
		ui::toolbutton(key(), edit, "(vs/redo)");

		Widget& build = ui::toolbar(key(), tools, true);
		static cstring configurations[] = { "Debug", "Release" };
		static cstring platforms[] = { "x64", "x86", "ARM64" };
		static cstring arguments[] = { "No command-line arg", "--test", "--verbose" };
		ui::dropdown_input(key(), build, configurations, ide.m_configuration);
		ui::dropdown_input(key(), build, platforms, ide.m_platform);
		ui::dropdown_input(key(), build, arguments, ide.m_arguments);

		Widget& debug = ui::toolbar(key(), tools, true);
		static cstring debuggers[] = { "Local Windows Debugger", "Remote Windows Debugger", "Web Browser" };
		static cstring scopes[] = { "Auto", "Current Document", "Entire Solution" };
		ui::toolbutton(key(), debug, "(vs/run)");
		ui::dropdown_input(key(), debug, debuggers, ide.m_debugger);
		ui::toolbutton(key(), debug, "(vs/run_outline)");
		ui::dropdown_input(key(), debug, scopes, ide.m_scope);

		Widget& misc = ui::toolbar(key(), tools, true);
		ui::toolbutton(key(), misc, "(vs/attach)");
		ui::toolbutton(key(), misc, "(vs/bookmark)");
		ui::toolbutton(key(), misc, "(vs/comment)");
	}

	void file_node(Widget& parent, Ide& ide, FileNode& node, bool open = false)
	{
		cstring elements[] = { node.image(), node.name.c_str() };
		TreeNode& self = ui::tree_node(key(&node), parent, elements, !node.folder, open);
		node.open = self.m_body != nullptr;

		if(!node.folder && self.m_header->mouse_event(DeviceType::MouseLeft, EventType::DoubleStroked))
			ide.open(node.name, node.path);

		if(self.m_body)
		{
			node.scan();
			for(FileNode& child : node.children)
				file_node(*self.m_body, ide, child);
		}
	}

	void solution_explorer(Widget& parent, Ide& ide)
	{
		Widget& toolbar = ui::toolbar(key(), parent);
		ui::toolbutton(key(), toolbar, "(vs/home)");
		ui::toolbutton(key(), toolbar, "(vs/sync)");
		ui::toolbutton(key(), toolbar, "(vs/refresh)");
		ui::toolbutton(key(), toolbar, "(vs/collapse_all)");
		ui::toolbutton(key(), toolbar, "(vs/show_all_files)");
		ui::toolbutton(key(), toolbar, "(vs/settings)");

		Widget& search = ui::row(key(), parent);
		ui::type_in(key(), search, ide.m_explorer_search);
		ui::icon(key(), search, "(vs/search)");

		Widget& sheet = *ui::scroll_sheet(key(), parent).m_body;
		Widget& tree = ui::tree(key(), sheet);
		file_node(tree, ide, ide.m_solution, true);
	}

	void properties(Widget& parent, Ide& ide)
	{
		Document& document = *ide.m_documents[2];

		static cstring categories[] = { "Misc" };
		static uint32_t category = 0;
		ui::dropdown_input(key(), parent, categories, category);

		Widget& sheet = *ui::scroll_sheet(key(), parent).m_body;
		Table& table = ui::table(key(), sheet, { "Property", "Value" }, { 0.4f, 0.6f });

		static string name = document.name;
		static string path = document.path;
		static uint32_t type = 0;
		static cstring types[] = { "C/C++ compiler", "C/C++ header", "Does not participate in build", "Text" };
		static bool excluded = false;
		static bool content = false;

		ui::field<string>(key(), table, "Name", name);
		ui::field<string>(key(), table, "Full Path", path);
		ui::dropdown_field(key(), table, "Item Type", types, type);
		ui::field<bool>(key(), table, "Excluded From Build", excluded);
		ui::field<bool>(key(), table, "Content", content);
	}

	void git_changes(Widget& parent, Ide& ide)
	{
		Widget& header = ui::row(key(), parent);
		ui::label(key(), header, "Git Changes - two");
		ui::spacer(key(), header);
		ui::toolbutton(key(), header, "(vs/settings)");

		Widget& branch = ui::row(key(), parent);
		ui::icon(key(), branch, "(vs/branch)");
		ui::label(key(), branch, "fix/reflection-runtime");

		ui::type_in(key(), parent, ide.m_commit_message, 3);

		Widget& actions = ui::row(key(), parent);
		ui::button(key(), actions, "Commit All");
		ui::spacer(key(), actions);
		ui::toolbutton(key(), actions, "(vs/find_previous)");
		ui::toolbutton(key(), actions, "(vs/sync)");

		Widget& sheet = *ui::scroll_sheet(key(), parent).m_body;
		Widget& tree = ui::tree(key(), sheet);
		if(Widget* changes = ui::tree_node(key(), tree, "Changes (6)").m_body)
		{
			static cstring files[] = { "Frame.cpp  M", "Frame.h  M", "LayoutTree.cpp  A", "LayoutTree.h  A", "Solver.cpp  M", "WidgetStruct.cpp  M" };
			for(size_t i = 0; i < size(files); ++i)
			{
				cstring elements[] = { "(vs/cpp_file_node)", files[i] };
				ui::tree_node(key(i), *changes, elements, true);
			}
		}
	}

	void document_view(Widget& parent, Document& document)
	{
		document.load();

		Widget& navigation = ui::row(key(), parent);
		static cstring projects[] = { "two_ui" };
		static cstring scopes[] = { "two::RowSolver", "two::FrameSolver", "two::LineSolver" };
		static cstring symbols[] = { "position(FrameSolver & frame, Axis dim)", "resize(FrameSolver & frame, Axis dim)", "measure(FrameSolver & frame, Axis dim)" };
		static uint32_t project = 0;
		ui::dropdown_input(key(), navigation, projects, project);
		ui::dropdown_input(key(), navigation, scopes, document.scope);
		ui::dropdown_input(key(), navigation, symbols, document.symbol);

		TextEdit& edit = ui::code_edit(key(), parent, document.text);
		edit.m_language = &LanguageCpp();

		Widget& status = ui::row(key(), parent);
		static cstring zooms[] = { "50 %", "70 %", "80 %", "90 %", "100 %", "125 %", "150 %", "200 %" };
		ui::dropdown_input(key(), status, zooms, document.zoom);
		ui::icon(key(), status, "(vs/status_ok)");
		ui::label(key(), status, "No issues found");
		ui::spacer(key(), status);
		const size_t cursor = min(size_t(edit.m_selection.m_cursor.m_index), document.text.size());
		const size_t line_start = cursor == 0 ? 0 : document.text.rfind('\n', cursor - 1) + 1;
		size_t line = 0;
		for(size_t i = 0; i < cursor; ++i)
			line += document.text[i] == '\n';
		ui::labelf(key(), status, "Ln: %zu, Ch: %zu", line + 1, cursor - line_start + 1);
		ui::label(key(), status, "TABS");
		ui::label(key(), status, "CRLF");
		ui::label(key(), status, "UTF-8");
	}

	void output(Widget& parent, Ide& ide)
	{
		Widget& header = ui::row(key(), parent);
		static cstring sources[] = { "Build", "Debug", "Git", "Source Control - Git", "Tests" };
		ui::label(key(), header, "Show output from:");
		ui::dropdown_input(key(), header, sources, ide.m_output_source);
		ui::toolbutton(key(), header, "(vs/find_previous)");
		ui::toolbutton(key(), header, "(vs/find_next)");
		ui::toolbutton(key(), header, "(vs/clear_window_content)");
		ui::toolbutton(key(), header, "(vs/word_wrap)");

		ui::text_edit(key(), parent, ide.m_output);
	}

	void find_symbol_results(Widget& parent)
	{
		ui::label(key(), parent, "Find all \"RowSolver\" - 6 matches");
		Widget& sheet = *ui::scroll_sheet(key(), parent).m_body;
		Widget& tree = ui::tree(key(), sheet);
		if(Widget* definitions = ui::tree_node(key(), tree, "two::RowSolver").m_body)
		{
			static cstring results[] = {
				"Solver.h(115): class RowSolver : public FrameSolver",
				"Solver.cpp(182): RowSolver::RowSolver()",
				"Solver.cpp(185): RowSolver::RowSolver(FrameSolver* solver, Layout* layout, Frame* frame)",
				"Solver.cpp(189): void RowSolver::compute(FrameSolver& frame, Axis dim)",
				"Solver.cpp(222): void RowSolver::layout(FrameSolver& frame, Axis dim)",
				"Node.cpp(45): RowSolver overlay(plan.m_solver.get(), &layout_overlay);",
			};
			for(size_t i = 0; i < size(results); ++i)
			{
				cstring elements[] = { "(vs/method)", results[i] };
				ui::tree_node(key(i), *definitions, elements, true);
			}
		}
	}

	void diagnostic_tools(Widget& parent)
	{
		ui::label(key(), parent, "Diagnostics session: 0 seconds");

		if(Widget* events = ui::expandbox(key(), parent, "Events").m_body)
			ui::label(key(), *events, "No events");

		if(Widget* memory = ui::expandbox(key(), parent, "Process Memory (MB)").m_body)
		{
			ui::fill_bar(key(), *memory, 0.35f);
			ui::label(key(), *memory, "412 MB");
		}

		if(Widget* cpu = ui::expandbox(key(), parent, "CPU (% of all processors)").m_body)
		{
			ui::fill_bar(key(), *cpu, 0.12f);
			ui::label(key(), *cpu, "12 %");
		}
	}

	void statusbar(Widget& parent)
	{
		Widget& status = ui::row(key(), parent);
		ui::icon(key(), status, "(vs/status_ok)");
		ui::label(key(), status, "Ready");
		ui::spacer(key(), status);
		ui::label(key(), status, "0 / 0");
		ui::label(key(), status, "9");
		ui::icon(key(), status, "(vs/branch)");
		ui::label(key(), status, "fix/reflection-runtime");
		ui::icon(key(), status, "(vs/git_repository)");
		ui::label(key(), status, "two");
	}
}

void example_ide(Widget& ui)
{
	static Ide ide;

	titlebar(ui, ide);
	toolbars(ui, ide);

	Widget& board = ui::board(key(), ui);

	Docker& dockspace = ui::dockspace(key(), board, ide.m_docksystem);
	Docker& dockbar = ui::dockbar(key(), board, ide.m_docksystem);

	// left column: the panels stacked as tabs
	if(Widget* dock = ui::dockitem(dockspace, "Solution Explorer", { 0U, 0U }, 0.2f))
		solution_explorer(*dock, ide);
	if(Widget* dock = ui::dockitem(dockspace, "Properties", { 0U, 0U }))
		properties(*dock, ide);
	if(Widget* dock = ui::dockitem(dockspace, "Git Changes", { 0U, 0U }))
		git_changes(*dock, ide);

	// right column: the documents above, the output below
	for(unique<Document>& document : ide.m_documents)
		if(Widget* dock = ui::dockitem(dockspace, document->name.c_str(), { 0U, 1U, 0U }, 0.7f))
			document_view(*dock, *document);

	if(Widget* dock = ui::dockitem(dockspace, "Output", { 0U, 1U, 1U }, 0.3f))
		output(*dock, ide);
	if(Widget* dock = ui::dockitem(dockspace, "Find Symbol Results", { 0U, 1U, 1U }))
		find_symbol_results(*dock);

	if(Widget* dock = ui::dockitem(dockbar, "Diagnostic Tools", { 0U }))
		diagnostic_tools(*dock);

	statusbar(ui);
}

#ifdef _00_IDE_EXE
bool pump(RenderSystem& render_system, BgfxContext& context, UiWindow& ui_window)
{
	bool pursue = context.begin_frame();
	pursue &= ui_window.input_frame();
	example_ide(ui_window.m_ui->begin());
	context.render_frame();
	ui_window.render_frame(240);
	render_system.end_frame();
	return pursue;
}

#ifdef TWO_PLATFORM_EMSCRIPTEN
	#include <emscripten/emscripten.h>

	RenderSystem* g_render_system = nullptr;
	BgfxContext* g_context = nullptr;
	UiWindow* g_window = nullptr;
	void iterate() { pump(*g_render_system, *g_context, *g_window); }
#endif

void install_crash_report();

int main(int argc, char *argv[])
{
	UNUSED(argc); UNUSED(argv);
	install_crash_report();

	static BgfxSystem render_system = { TWO_RESOURCE_PATH };
	static BgfxContext context = BgfxContext(render_system, "two ide", uvec2(1600U, 900U), false, true);
	static VgVg vg = VgVg(TWO_RESOURCE_PATH, &render_system.allocator());
	vg.setup_context();

	static UiWindow ui_window = UiWindow(context, vg);
	ui_window.init();
	style_vs_dark(ui_window);

#ifdef TWO_PLATFORM_EMSCRIPTEN
	g_render_system = &render_system;
	g_context = &context;
	g_window = &ui_window;
	emscripten_set_main_loop(iterate, 0, 1);
#else
	bool pursue = true;
	while(pursue)
		pump(render_system, context, ui_window);
#endif
}
#endif
