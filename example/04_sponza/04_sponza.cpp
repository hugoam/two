#include <mud/frame.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>

#include <04_sponza/04_sponza.h>
#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>
#include <04_lights/04_lights.h>

using namespace mud;

#define DEBUG_FRUSTUM 0
#define GI_PROBE 0
#define LIGHTMAPS 0
#define DEBUG_CAPTURE 0
#define DIRECT_LIGHT 1
#define POINT_LIGHTS 0
#define CLUSTERED 1
#define SHAPES 1
#define POSTPROCESS 0

void ex_04_sponza(Shell& app, Widget& parent, Dockbar& dockbar)
{
	static ImporterOBJ obj_importer(app.m_gfx_system);

	SceneViewer& viewer = ui::scene_viewer(parent);
	viewer.m_viewport.comp<Tonemap>().m_mode = TonemapMode::ACES;
	viewer.m_viewport.comp<Tonemap>().m_mode = TonemapMode::Filmic;
	viewer.m_viewport.comp<Tonemap>().m_mode = TonemapMode::Reinhardt;
	viewer.m_viewport.m_lighting = Lighting::VoxelGI;

	OrbitController& controller = ui::free_orbit_controller(viewer);
	viewer.take_focus();

	if(app.m_gfx_system.m_frame == 1)
	{
		controller.m_yaw = c_pi / 2.f;
		controller.m_pitch = -c_pi / 16.f;
		controller.m_distance = 80.f;
	}

	Gnode& scene = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

#if DIRECT_LIGHT
	static float azimuth = 0.f;
	static float altitude = c_pi / 2.f - 0.01f - 0.1f;

	Light& direct_light = gfx::direct_light_node(scene, sun_rotation(azimuth, altitude));
	direct_light.m_energy = 2.f;
	direct_light.m_shadow_range = 150.f; // @todo why does needs to be double ? extents of this model are only ~70 in Y axis
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
	static Prefab& prefab = import_prefab(app.m_gfx_system, ModelFormat::obj, "sponza", config);

	//Gnode& sponza_node = gfx::node(scene, {}, vec3{ 0.f, -5.f, 0.f });
	Gnode& sponza_node = gfx::node(scene, {}, -prefab.m_aabb.m_center);
	gfx::prefab(sponza_node, prefab, false, ItemFlag::NoUpdate);

#if GI_PROBE
	GIProbe& probe = gfx::gi_probe(scene, 512, prefab.m_aabb.m_extents);
	//probe.m_transform = bxtranslation(-model.m_aabb.m_center);

	if(app.m_gfx_system.m_frame == 1)
	{
		//probe.m_bounces = 1;
		probe.m_diffuse = 6.f;
	}
#endif

#if LIGHTMAPS
	string path = app.m_gfx_system.m_resource_path + "/examples/04_sponza/lightmaps/";
	LightmapAtlas& lightmap = gfx::lightmap(scene, 4096U, 4.f, path);
	lightmap.m_capture_transform = bxidentity();
	lightmap.m_capture_extents = prefab.m_aabb.m_extents;
#endif

#if DEBUG_CAPTURE
	if(app.m_gfx_system.m_frame % 100 == 0)
		app.m_gfx_system.m_capture = true;
	if(app.m_gfx_system.m_frame % 100 == 1)
		probe.m_dirty = true;
#endif

#if CLUSTERED
	if(rect_size(vec4(viewer.m_viewport.m_rect)) != vec2(0.f) && !viewer.m_camera.m_clusters)
	{
		viewer.m_camera.m_clustered = true;
		viewer.m_camera.m_clusters = make_unique<Froxelizer>(viewer.m_scene->m_gfx_system);
		viewer.m_camera.m_clusters->prepare(viewer.m_viewport, viewer.m_camera.m_projection, viewer.m_camera.m_near, viewer.m_camera.m_far);
	}
#endif

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
	{
		Widget& sheet = ui::columns(*dock, carray<float, 2>{ 0.3f, 0.7f });

		ui::label(sheet, "Environment :");
		ui::number_field<float>(sheet, "Ambient", { viewer.m_environment.m_radiance.m_ambient, { 0.f, 100.f, 0.01f } });

#if POSTPROCESS
		ui::label(sheet, "Post process :");
		ui::slider_field<float>(sheet, "Exposure", { viewer.m_viewport.comp<Tonemap>().m_exposure, { 0.f, 2.f, 0.01f } });
		ui::slider_field<float>(sheet, "Whitepoint", { viewer.m_viewport.comp<Tonemap>().m_white_point, { 0.f, 2.f, 0.01f } });

		viewer.m_viewport.comp<BCS>().m_enabled = true;
		ui::slider_field<float>(sheet, "Brightness", { viewer.m_viewport.comp<BCS>().m_brightness, { 0.f, 2.f, 0.01f } });
		ui::slider_field<float>(sheet, "Contrast", { viewer.m_viewport.comp<BCS>().m_contrast, { 0.f, 2.f, 0.01f } });
		ui::slider_field<float>(sheet, "Saturation", { viewer.m_viewport.comp<BCS>().m_saturation, { 0.f, 2.f, 0.01f } });
#endif

#if DIRECT_LIGHT
		ui::label(sheet, "Shadow : ");
		ui::flag_field(sheet, "Stabilize", (uint32_t&) direct_light.m_shadow_flags, 0);

		ui::label(sheet, "Sun :");
		ui::slider_field<float>(sheet, "Azimuth", { azimuth, { 0.f, c_pi, 0.01f } });
		ui::slider_field<float>(sheet, "Altitude", { altitude, { 0.f, c_pi / 2.f, 0.01f } });
#endif

#if GI_PROBE
		ui::label(sheet, "GI Probe :");
		ui::slider_field<float>(sheet, "Diffuse", { probe.m_diffuse, { 0.f, 10.f, 0.1f } });
		ui::slider_field<int>(sheet, "Bounces", { probe.m_bounces, { 0, 10, 1 } });
		ui::slider_field<float>(sheet, "Bias", { probe.m_bias, { 0.f, 10.f, 0.1f } });
		ui::slider_field<float>(sheet, "Normal Bias", { probe.m_normal_bias, { 0.f, 10.f, 0.1f } });

		if(ui::button(sheet, "Recompute GI").activated())
			probe.m_dirty = true;
#endif
	}
}

#ifdef _04_SPONZA_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_04_sponza(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx_system.add_resource_path("examples/04_sponza");
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif
