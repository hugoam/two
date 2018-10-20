#include <mud/mud.h>
#include <10_post_process/10_post_process.h>

#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

using namespace mud;

void ex_10_post_process(Shell& app, Widget& parent, Dockbar& dockbar)//, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
		edit_viewer_filters(*dock, viewer);

	Gnode& scene = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

	Gnode& ground_node = gfx::node(scene, {}, vec3{ 0.f, -5.f, 0.f });
	gfx::shape(ground_node, Rect(vec2{ -50.f, -50.f }, vec2{ 100.f }), Symbol(), 0U, &material);

	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static std::vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder() }; // @todo Circle() looks weird
	static std::vector<ShapeInstance > shape_items = create_shape_grid(10U, 10U, shapes);

	shape_grid(scene, { shape_items.data(), 10U, 10U }, Symbol(), shapes, true, &material);
}

#ifdef _10_POST_PROCESS_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_10_post_process(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif

