#include <infra/Cpp20.h>
import two.frame;
import two.gfx.obj;
import two.gfx.pbr;

#include <04_sponza/04_sponza.h>
#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>
#include <04_lights/04_lights.h>

using namespace two;

#define DEBUG_FRUSTUM 0
#define GI_PROBE 0
#define LIGHTMAPS 0
#define DEBUG_CAPTURE 0
#define DIRECT_LIGHT 1
#define POINT_LIGHTS 0
#define CLUSTERED 1
#define SHAPES 1
#define POSTPROCESS 0

void ex_04_sponza(Shell& app, Widget& parent, DockbarHandle dockbar)
{
	static ImporterOBJ obj_importer(app.m_gfx);

	SceneViewerHandle viewer = ui::scene_viewer(key(), parent);
	Tonemap& tonemap = viewer->m_viewport.comp<Tonemap>();

	tonemap.m_enabled = true;
	tonemap.m_mode = TonemapMode::ACES;
	tonemap.m_mode = TonemapMode::Filmic;
	tonemap.m_mode = TonemapMode::Reinhardt;

	viewer->m_viewport.m_lighting = Lighting::VoxelGI;

	viewer->m_viewport.m_to_gamma = true;

	viewer->m_scene.m_env.m_radiance.m_ambient = Colour(0.1f);

	OrbitController& controller = ui::free_orbit_controller(viewer);
	viewer.self().take_focus();

	if(app.m_gfx.m_frame == 1)
	{
		controller.m_yaw = c_pi2;
		controller.m_pitch = -c_pi / 16.f;
		controller.m_distance = 80.f;

		BlockShadow& shadow = *app.m_gfx.m_renderer.block<BlockShadow>();
		shadow.m_atlas = ShadowAtlas(4096U, 1U);
	}

	Gnode& scene = viewer->m_scene.begin();

	Material& material = milky_white(app.m_gfx);

#if DIRECT_LIGHT
	static float azimuth = 0.f;
	static float altitude = c_pi2 - 0.01f - 0.1f;

	Light& direct_light = gfx::direct_light_node(scene, sun_rotation(azimuth, altitude));
	direct_light.m_energy = 2.f;
	direct_light.m_shadow_range = 150.f; // @todo why does need to be doubled ? extents of this model are only ~70 in Y axis
#endif

	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

#if SHAPES
	static vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder() }; // @todo Circle() looks weird
	static vector<ShapeInstance> shape_items = create_shape_grid(10U, 10U, shapes);
	static Symbol symbol;
	shape_grid(scene, { shape_items.data(), 10U, 10U }, &symbol, true, &material);
#endif

#if POINT_LIGHTS
	static vector<LightInstance> light_items = create_light_grid(10U, 10U);
	light_grid(scene, { light_items.data(), 10U, 10U }, true, LightType::Point, 9.f, 0.4f, 0.f, 0.f);
#endif

	ImportConfig config;
	config.m_flags = ItemFlag::Static;
	config.m_transform = bxscale(vec3(0.1f));
	config.m_optimize_geometry = true;
	static Prefab& prefab = import_prefab(app.m_gfx, ModelFormat::obj, "sponza", config);

	//Gnode& sponza_node = gfx::node(scene, vec3(0.f, -5.f, 0.f));
	Gnode& sponza_node = gfx::node(scene, -prefab.m_aabb.m_center);
	gfx::prefab(sponza_node, prefab, false, ItemFlag::NoUpdate);

#if GI_PROBE
	GIProbe& probe = gfx::gi_probe(scene, 512, prefab.m_aabb.m_extents);
	//probe.m_transform = bxtranslation(-model.m_aabb.m_center);

	if(app.m_gfx.m_frame == 1)
	{
		//probe.m_bounces = 1;
		probe.m_diffuse = 6.f;
	}
#endif

#if LIGHTMAPS
	string path = app.m_gfx.m_resource_path + "/examples/04_sponza/lightmaps/";
	LightmapAtlas& lightmap = gfx::lightmap(scene, 4096U, 4.f, path);
	lightmap.m_capture_transform = bxidentity();
	lightmap.m_capture_extents = prefab.m_aabb.m_extents;
#endif

#if DEBUG_CAPTURE
	if(app.m_gfx.m_frame % 100 == 0)
		app.m_gfx.m_capture = true;
	if(app.m_gfx.m_frame % 100 == 1)
		probe.m_dirty = true;
#endif

#if CLUSTERED
	viewer->m_viewport.set_clustered(app.m_gfx);
#endif

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::columns(key(), *dock, { 0.3f, 0.7f });

		ui::label(key(), sheet, "Zone :");
		ui::color_field(key(), sheet, "Ambient", viewer->m_scene.m_env.m_radiance.m_ambient);

#if POSTPROCESS
		Tonemap& tonemap = viewer->m_viewport.comp<Tonemap>();
		BCS& bcs = viewer->m_viewport.comp<BCS>();

		ui::label(key(), sheet, "Post process :");
		ui::slider_field(key(), sheet, "Exposure",   tonemap.m_exposure,    { 0.f, 2.f, 0.01f });
		ui::slider_field(key(), sheet, "Whitepoint", tonemap.m_white_point, { 0.f, 2.f, 0.01f });

		bcs.m_enabled = true;
		ui::slider_field(key(), sheet, "Brightness", bcs.m_brightness, { 0.f, 2.f, 0.01f });
		ui::slider_field(key(), sheet, "Contrast",   bcs.m_contrast,   { 0.f, 2.f, 0.01f });
		ui::slider_field(key(), sheet, "Saturation", bcs.m_saturation, { 0.f, 2.f, 0.01f });
#endif

#if DIRECT_LIGHT
		ui::label(key(), sheet, "Shadow : ");
		ui::flag_field(key(), sheet, "Stabilize", (uint32_t&) direct_light.m_shadow_flags, 0);

		ui::label(key(), sheet, "Sun :");
		ui::slider_field(key(), sheet, "Azimuth", azimuth, { 0.f, c_pi, 0.01f });
		ui::slider_field(key(), sheet, "Altitude", altitude, { 0.f, c_pi2, 0.01f });
#endif

#if GI_PROBE
		ui::label(key(), sheet, "GI Probe :");
		ui::slider_field(key(), sheet, "Diffuse", probe.m_diffuse, { 0.f, 10.f, 0.1f });
		ui::slider_field(key(), sheet, "Bounces", probe.m_bounces, { 0, 10, 1 });
		ui::slider_field(key(), sheet, "Bias", probe.m_bias, { 0.f, 10.f, 0.1f });
		ui::slider_field(key(), sheet, "Normal Bias", probe.m_normal_bias, { 0.f, 10.f, 0.1f });

		if(ui::button(key(), sheet, "Recompute GI").activated())
			probe.m_dirty = true;
#endif
	}
}

#ifdef _04_SPONZA_EXE
void pump(Shell& app, ShellWindow& window)
{
	shell_context(window.m_ui->begin(), app.m_editor);
	ex_04_sponza(app, *app.m_editor.m_screen, app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(TWO_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx.add_resource_path("examples/04_sponza");
	app.m_gfx.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif
