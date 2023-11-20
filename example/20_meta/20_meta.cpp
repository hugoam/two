#include <infra/Cpp20.h>
import two.frame;

#include <20_meta/20_meta.h>
#include <03_materials/03_materials.h>

using namespace two;

void ex_20_meta(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	//meta_browser(parent);

	Gnode& scene = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	gfx::shape(scene, Cube(), Symbol(), ItemFlag::Default | ItemFlag::Selectable, &material);
}

#ifdef _20_META_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_20_meta(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv).c_str());
	app.m_gfx_system.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
