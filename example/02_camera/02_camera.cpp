#include <mud/mud.h>
#include <02_camera/02_camera.h>

#include <03_materials/03_materials.h>

using namespace mud;

void ex_02_camera(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Material& material = milky_white(viewer.m_gfx_system);

	Gnode& scene = viewer.m_scene->begin();
	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
	gfx::shape(scene, Sphere(), Symbol(), 0U, &material);
}

#ifdef _02_CAMERA_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_02_camera(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif

