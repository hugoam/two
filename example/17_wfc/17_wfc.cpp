#include <mud/mud.h>
#include <17_wfc/17_wfc.h>

using namespace mud;

#if 0
static void generator_script(Shell& app, VisualScript& script)
{
	script.lock();

	Valve& grid_size = script.value(uvec3(20, 4, 20));
	//Valve& coords = script.function(grid, { &grid_size });

	string path = app.m_resource_path + "models/" + "platform/platform.tls";
	Valve& tileset = script.function(parse_json_wave_tileset, { &script.value(path), &script.value(string("")) });

	Valve& tileblock = script.create<Tileblock>({ &grid_size, &script.value(Unit3), &tileset });
	//Valve& world = script.method(&Tileblock::update, { &empty_world, &wave });

	script.unlock();
}

VisualScript& create_visual_script(Shell& app)
{
	static VisualScript script = { "Example Script" };
	generator_script(app, script);
	return script;
}
#endif

WaveTileset& create_tileset(Shell& app)
{
	static WaveTileset tileset;

	string path = app.m_gfx_system->locate_file("models/platform/platform", carray<cstring, 1>{ ".tls" });
	parse_json_wave_tileset(path + "models/platform/platform.tls", "", tileset);

	return tileset;
}

void tileblock_options(Widget& parent, Tileblock& tileblock)
{
	Widget& self = ui::sheet(parent);
	if(ui::button(self, "regenerate").activated())
		tileblock.reset();
	tileblock_edit(self, tileblock);
}

void ex_17_wfc(Shell& app, Widget& parent, Dockbar& dockbar)
{
	//static VisualScript& script = create_visual_script(app);

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& groot = viewer.m_scene->begin();

	static WaveTileset& tileset = create_tileset(app);
	static Tileblock tileblock = { { 20, 4, 20 }, Unit3, tileset };

	//gfx::directional_light_node(groot);
	gfx::radiance(groot, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	paint_tileblock(groot, tileblock);

	static size_t tick = 0;
	tick++;

	tileblock.next_frame(tick, 1);

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<size_t, 1>{ 1U }))
		tileblock_options(*dock, tileblock);
}

#ifdef _17_WFC_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_17_wfc(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	cstring example_path = MUD_RESOURCE_PATH "examples/17_wfc/";
	Shell app(carray<cstring, 2>{ MUD_RESOURCE_PATH, example_path }, argc, argv);
	app.run(pump);
}
#endif