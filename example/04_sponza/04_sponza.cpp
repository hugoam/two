#include <mud/mud.h>
#include <04_sponza/04_sponza.h>

#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

using namespace mud;

#define DEBUG_FRUSTUM 0

void ex_04_sponza(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	viewer.m_viewport.m_lighting = Lighting::VoxelGI;

	ui::free_orbit_controller(viewer);
	viewer.take_focus();

	Gnode& scene = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

	static float azimuth = 0.f;
	static float altitude = c_pi / 2.f - 0.01f - 0.1f;

	Light& directional_light = gfx::directional_light_node(scene, sun_rotation(azimuth, altitude));
	directional_light.m_energy = 2.f;
	directional_light.m_shadows = false;

	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static std::vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder() }; // @todo Circle() looks weird
	static std::vector<ShapeInstance > shape_items = create_shape_grid(10U, 10U, shapes);

	shape_grid(scene, { shape_items.data(), 10U, 10U }, Symbol(), shapes, true, &material);

	Gnode& sponza_node = gfx::node(scene, {}, vec3{ 0.f, -5.f, 0.f });

	Model& model = *app.m_gfx_system.models().file("sponza");
	//gfx::item(sponza_node, model);
	gfx::multi_item(sponza_node, model);

	GIProbe& probe = gfx::gi_probe(scene, 512, model.m_aabb.m_extents);
	probe.m_transform = bxtranslation(-model.m_aabb.m_center);
	//probe.m_dirty = true;

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
	{
		Widget& sheet = ui::columns(*dock, carray<float, 2>{ 0.3f, 0.7f });

		ui::label(sheet, "Environment :");
		ui::number_field<float>(sheet, "Ambient", { viewer.m_environment.m_radiance.m_ambient, { 0.f, 100.f, 0.01f } });

		ui::label(sheet, "Shadow : ");
		ui::flag_field(sheet, "Stabilize", (uint32_t&) directional_light.m_shadow_flags, 0);

		ui::label(sheet, "Sun :");
		ui::slider_field<float>(sheet, "Azimuth", { azimuth, { 0.f, c_pi, 0.01f } });
		ui::slider_field<float>(sheet, "Altitude", { altitude, { 0.f, c_pi / 2.f, 0.01f } });
	}
}

#ifdef _04_SPONZA_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_04_sponza(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	cstring example_path = MUD_RESOURCE_PATH "examples/04_sponza/";
	Shell app(carray<cstring, 2>{ MUD_RESOURCE_PATH, example_path }, argc, argv);
	app.run(pump);
}
#endif
