#include <mud/mud.h>
#include <07_gltf/07_gltf.h>

using namespace mud;

void ex_07_gltf(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& groot = viewer.m_scene->begin();

	gfx::directional_light_node(groot, sun_rotation(M_PI / 4.f, M_PI / 4.f));
	gfx::radiance(groot, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
	
	Gnode& model_node = gfx::node(groot);
	gfx::model(model_node, "DamagedHelmet");

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<size_t, 1>{ 1U }))
		edit_viewer_filters(*dock, viewer);
}

#ifdef _07_GLTF_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_07_gltf(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	cstring example_path = MUD_RESOURCE_PATH "examples/07_gltf/";
	Shell app(cstrarray(MUD_RESOURCE_PATH, example_path), argc, argv);
	app.run(pump);
}
#endif
