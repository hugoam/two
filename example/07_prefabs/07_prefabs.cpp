#include <mud/mud.h>
#include <07_prefabs/07_prefabs.h>

using namespace mud;

void ex_07_prefabs(Shell& app, Widget& parent, Dockbar& dockbar)
{
	static PrefabNode prefab;

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);
	app.m_editor.m_viewer = &viewer;

	Gnode& groot = viewer.m_scene->begin();
	prefab.draw(groot);

	gfx::directional_light_node(groot, sun_rotation(M_PI / 4.f, M_PI / 4.f));
	gfx::radiance(groot, "radiance/tiber_1_1k.hdr", BackgroundMode::None);
	
	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<size_t, 1>{ 1U }))
	{
		PrefabNode* node = prefab_edit(*dock, viewer.m_gfx_system, prefab); // "Particle Editor" // identity = edited
		app.m_editor.m_selection = { &node->m_transform };
	}
}

#ifdef _07_PREFABS_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_07_prefabs(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	cstring prefab_path		= MUD_RESOURCE_PATH "examples/07_prefabs/";
	cstring gtlf_path		= MUD_RESOURCE_PATH "examples/07_gltf/";
	//cstring character_path	= MUD_RESOURCE_PATH "examples/07_character/";
	Shell app(cstrarray(MUD_RESOURCE_PATH, prefab_path, gtlf_path), argc, argv);
	app.run(pump);
}
#endif
