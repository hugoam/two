#include <mud/frame.h>
#include <gfx-pbr/Api.h>
#include <wfc/Api.h>
#include <wfc-gfx/Api.h>

#include <17_wfc/17_wfc.h>

using namespace mud;

WaveTileset& create_tileset(Shell& app)
{
	static WaveTileset tileset;

	LocatedFile location = app.m_gfx_system.locate_file("models/platform/platform", { ".tls" });
	parse_json_wave_tileset(location.path(true), "", tileset);

	return tileset;
}

void ex_17_wfc(Shell& app, Widget& parent, Dockbar& dockbar)
{
	//static VisualScript& script = create_visual_script(app);

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);
	//viewer.m_camera.set_isometric(IsometricAngle(SOUTH | WEST), Zero3);

	Gnode& scene = viewer.m_scene->begin();

	static WaveTileset& tileset = create_tileset(app);
	static WfcBlock block = { Zero3, { 20, 4, 20 }, Unit3, tileset };
	static uvec3 highlighted = uvec3(UINT32_MAX);
	static uvec3 selected = uvec3(UINT32_MAX);
	static uvec3 focused = uvec3(UINT32_MAX);

	if(block.m_tile_models.empty())
		block.load_models(app.m_gfx_system);

	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	paint_tileblock(scene, {}, block, focused, nullptr, true);

	//if(highlighted != uvec3(UINT32_MAX))
	//	paint_tile_cube(scene, block, vec3(highlighted), Colour::DarkGrey);

	if(selected != uvec3(UINT32_MAX))
		paint_tile_cube(scene, block, selected, Colour::White, Colour::AlphaWhite);

	static size_t tick = 0;
	tick++;

	block.next_frame(tick, 1);

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
		tileblock_edit(*dock, viewer, block, highlighted, selected, focused);
}

#ifdef _17_WFC_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_17_wfc(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx_system.add_resource_path("examples/17_wfc");
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif