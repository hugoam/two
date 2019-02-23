//#include <mud/frame.h>
#include <frame/Api.h>
#include <lang/Api.h>
#include <uio/Api.h>
#include <meta/ui.meta.h>
#include <meta/gfx.ui.meta.h>

#include <13_live_ui/13_live_ui.h>

#include <stl/vector.hpp>

using namespace mud;

#define NATIVE 0

#if 0
"local l = ui.scrollable(d1)\n"
"local modules = system().modules\n"
"for _, module in ipairs(modules) do\n"
"    local types = module.types\n"
"    for _, type in ipairs(types) do\n"
"        --local tb = ui.button(l, type.name)\n"
"        --if tb.activated then\n"
"        --    selected_type = type\n"
"        --end\n"
"    end\n"
"end\n"
"local w = window(d2, 'A random window', WINDOW_DEFAULT)"               "\n"
"if selected_type then\n"
"    local e = ui.expandbox(d2, { selected_type.name }, true).body\n"
"    if e then\n"
"        ui.button(e, selected_type.name)\n"
"    end\n"
"end\n"
#endif

static TextScript create_script(LuaInterpreter& interpreter)
{
	Signature signature = { vector<Param>{ { "ui_root", type<Widget>() } } };
	TextScript script = { "Example Script", Language::Lua, signature };
	script.m_interpreter = &interpreter;

	//interpreter.set("selected_type", Var());

	script.m_script =
		"local b = ui.board(ui_root)\n"
		"local d1 = ui.div(b)\n"
		"\n"
		"local r = ui.row(d1)\n"
		"ui.button(r, '(arrow_right)')\n"
		"ui.button(r, '(arrow_left)')\n"
		"ui.button(r, '(arrow_down)')\n"
		"ui.button(r, '(arrow_up)')\n"
		"ui.button(r, 'test button')\n"
		"--ui.multi_button(r, { '(folder_15)', 'test' }, nil)""\n"
		"\n"
		"local col = Colour.Pink\n"
		"ui.color_edit(d1, col)\n"
		"\n"
		"local d2 = ui.layout(b)\n"
		"\n"
		"local viewer_size = vec2(200, 170)\n"
		"local viewers = {}\n"
		"local colours = {}\n"
		"\n"
		"local c = ui.canvas(d2)\n"
		// @todo default values don't work because we are using same call object under the hood (value from previous call is persisted)
		"local main_viewer = ui.scene_viewer(d2, vec2(0))\n"
		"local prev_output = nil\n"
		"\n"
		"function next_colour()\n"
		"    local c = to_hsla(col)\n"
		"    col.r = (col.r + 0.13) % 1.0\n"
		"    col = to_rgba(c)\n"
		"end\n"
		"\n"
		"for i = 1,5 do\n"
		"    next_colour()\n"
		"    table.insert(colours, col)\n"

		"    local n = ui.node(c, 'Node ' .. tostring(i), vec2(200 + i * (viewer_size.x + 50), 100), 0)\n"
		"    local input = ui.node_input(n, 'Input', '(file_15)', col, 1, 0)\n"
		"    local output = ui.node_output(n, 'Output', '', col, 1, 0)\n"
		"    \n"
		// @todo comment these two fixes the main viewer wrong parent issue -> investigate
		"    local viewer = ui.scene_viewer(n, viewer_size)\n"
		"    table.insert(viewers, viewer)\n"
		"    \n"
		"    if prev_output then\n"
		"        ui.node_cable(c, prev_output, input)\n"
		"    end\n"
		"    prev_output = output\n"
		"end\n"
		"\n"
		//"local main_viewer = ui.scene_viewer(d2, vec2(0))\n"
		"next_colour()\n"
		"table.insert(colours, col)\n"
		"table.insert(viewers, main_viewer)\n"
		"\n"
		"if time == nil then\n"
		"    time = 0.0\n"
		"end\n"
		"\n"
		"time = time + 0.01\n"
		"\n"
		"local rotation = vec3(0, time, 0)\n"

		"for i, viewer in ipairs(viewers) do\n"
		"    local gfx_root = viewer.scene.begin()\n"
		"    \n"
		"    local cn = gfx.node(gfx_root, nil, vec3(0), quat(rotation), vec3(1))\n"
		"    gfx.shape(cn, Cube(), Symbol(Colour.None, colours[i]))\n"
		"    \n"
		"    local cn = gfx.node(gfx_root, nil, vec3(0), quat(rotation), vec3(2))\n"
		"    gfx.shape(cn, Cube(), Symbol(colours[i], Colour.None))\n"
		"end\n"
		"\n"
		//"local viewer = ui.viewer(d2)"                                          "\n"
		// @todo ^ this should silently fail but it crashes, but scene arg is not nullable
		// -> lua wrapper should detect it and not call
		"\n"

		;

	return script;
}

void ex_13_live_ui(Shell& app, Widget& parent, Dockbar& dockbar)
{
#if NATIVE
	Widget& ui = parent;
	Widget& b = ui::board(ui);
	Widget& d1 = ui::div(b);
		
	Widget& r = ui::row(d1);
	ui::button(r, "(arrow_right)");
	ui::button(r, "(arrow_left)");
	ui::button(r, "(arrow_down)");
	ui::button(r, "(arrow_up)");
	ui::button(r, "test button");
	ui::multi_button(r, { "(folder_15)", "test" });
		
	Colour col = Colour::Pink;
	ui::color_edit(d1, col);
		
	Widget& d2 = ui::layout(b);
		
	vec2 viewer_size = vec2(200, 170);
	vector<SceneViewer*> viewers = {};
	vector<Colour> colours = {};
		
	Canvas& c = ui::canvas(d2);
		// @todo default values don"t work because we are using same call object under the hood (value from previous call is persisted)
	SceneViewer& main_viewer = ui::scene_viewer(d2, vec2(0.f));
	NodePlug* prev_output = nullptr;
		
	auto next_colour = [&]() {
		col = to_hsla(col);
		col.r = fmod((col.r + 0.13), 1.0);
		col = to_rgba(col);
	};
		
	for(int i = 1; i < 5; ++i)
	{
		next_colour();
		colours.push_back(col);

		Node& n = ui::node(c, ("Node " + to_string(i)).c_str(), vec2(200 + i * (viewer_size.x + 50), 100), 0);
		NodePlug& input = ui::node_input(n, "Input", "(file_15)", col, 1, 0);
		NodePlug& output = ui::node_output(n, "Output", "", col, 1, 0);
		    
		// @todo comment these two fixes the main viewer wrong parent issue -> investigate
		SceneViewer& viewer = ui::scene_viewer(n, viewer_size);
		viewers.push_back(&viewer);
		    
		if(prev_output)
			ui::node_cable(c, *prev_output, input);
		prev_output = &output;
	}
		
	//SceneViewer& main_viewer = ui::scene_viewer(d2, vec2(0));
	next_colour();
	colours.push_back(col);
	viewers.push_back(&main_viewer);
		
	static float time = 0.f;
	time = time + 0.01;
		
	vec3 rotation = vec3(0, time, 0);

	for(size_t i = 0; i < viewers.size(); ++i)
	{
		Gnode& scene = viewers[i]->m_scene.begin();

		Gnode& cn1 = gfx::node(scene, {}, vec3(0.f), quat(rotation), vec3(1.f));
		gfx::shape(cn1, Cube(), Symbol::plain(colours[i]));

		Gnode& cn2 = gfx::node(scene, {}, vec3(0.f), quat(rotation), vec3(2.f));
		gfx::shape(cn2, Cube(), Symbol::wire(colours[i]));
	}
	
#else
	UNUSED(app);
	static LuaInterpreter interpreter = { true };
	static TextScript script = create_script(interpreter);
	static Call call = { script, vector<Var>{ Ref(&parent) } };

	call();

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
		script_edit(*dock, script);
#endif
}

#ifdef _13_LIVE_UI_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_13_live_ui(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	System::instance().load_modules({ &mud_ui::m(), &mud_gfx_ui::m() });
	app.m_gfx_system.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
