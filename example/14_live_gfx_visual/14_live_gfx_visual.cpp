//#include <two/frame.h>
#include <frame/Api.h>
#include <lang/Api.h>
#include <uio/Api.h>
#include <meta/gfx.meta.h>

#include <14_live_gfx_visual/14_live_gfx_visual.h>

using namespace two;

static float g_time = 0.f;

void define_visual_script(VisualScript& script)
{
	script.lock();

	using Var = Valve;

	Valve& scene = script.input("scene");

	//static float g_time = 0.f;
	Var& time = script.reference(&g_time);
	//Var& speed = script.value(0.01f);
	//script.function(add<float>, { &time, &speed });

	Var& grid_interval = script.value(vec3(3.f, 0.f, 3.f));
	Var& grid_size = script.value(uvec3(11U, 1U, 11U));

	Var& coords = *script.function(grid, { &grid_size });

	Var& c = script.value(vec3(15.f, 0.f, 15.f));
	Var& grid_position = *script.function(multiply<vec3>, { &coords, &grid_interval });
	Var& position = *script.function(subtract<vec3>, { &grid_position, &c });

	Var& offsets = script.value(vec3(0.21f, 0.f, 0.37f));
	Var& f = *script.function(multiply<vec3>, { &coords, &offsets });
	Var& angles = *script.function(add<vec3>, { &f, &time });
	Var& rotation = script.create<quat>({ &angles });

	Var& t = *script.function(add<vec3>, { &f, &time });
	Var& tx = script.get(&vec3::x, { &t });
	Var& ty = script.get(&vec3::z, { &t });

	Var& r = *script.function(ncosf, { &tx });
	Var& b = *script.function(nsinf, { &ty });
	Var& g = *script.function(ncosf, { &time });

	Var& s0 = script.value(vec3(1.f));
	Var& s1 = script.value(1.f);
	Var& scale = *script.function(multiply<vec3>, { &s0, &s1 });

	Var& colour = script.create<Colour>({ &r, &g, &b, &script.value(1.f) });

	Gnode& (*func_node)(Gnode&, const vec3&, const quat&, const vec3&) = gfx::node;
	Var& node = *script.function(func_node, { &scene, &position, &rotation, &scale });

	Var& fill_colour = script.value(Colour::None);
	Var& symbol = script.create<Symbol>({ &fill_colour, &colour });
	Var& shape = script.value(Cube());

	using Draw = void(*)(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags);
	script.function((Draw)gfx::draw, { &node, &shape, &symbol });
}

VisualScript& create_visual_script()
{
	Signature signature = { { Param{ "scene", type<Gnode>() } } };
	static VisualScript script = { "Example Script", signature };
	define_visual_script(script);
	return script;
}

void ex_14_live_gfx_visual(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
#ifdef TWO_PLATFORM_EMSCRIPTEN
	// speed it up a bit on Emscripten cause it's clamped to 60fps
	g_time += 0.02f;
#else
	g_time += 0.01f;
#endif

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	static VisualScript& script = create_visual_script();

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
		visual_script_edit(*dock, script);

	Gnode& scene = viewer.m_scene.begin();

	static Call call = { script, vector<Var>{ Ref(&scene)} };
	call();	
}

#ifdef _14_LIVE_GFX_VISUAL_EXE
void pump(Shell& app, ShellWindow& window)
{
	shell_context(window.m_ui->begin(), app.m_editor);
	ex_14_live_gfx_visual(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(TWO_RESOURCE_PATH, exec_path(argc, argv));
	System::instance().load_modules({ &two_gfx::m() });
	app.m_gfx.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif

