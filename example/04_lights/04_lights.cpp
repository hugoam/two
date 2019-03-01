//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <04_lights/04_lights.h>
#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

#include <stl/vector.hpp>

//#include <meta/gfx/Convert.h>

using namespace mud;

#define CLUSTERED 1
#define DEBUG_CLUSTERED 0
#define OCCLUSION 0
#define DOCKBAR 1

static float g_time = 0.f;

vector<LightInstance> create_light_grid(size_t size_x, size_t size_y)
{
	vector<LightInstance> light_items = {};
	light_items.resize(size_x * size_y);

	for(size_t x = 0; x < size_x; ++x)
		for(size_t y = 0; y < size_y; ++y)
		{
			LightInstance& light_item = light_items[x + y * size_x];
			light_item.colour = hsl(randf(0.f, 1.f), 1.f, 0.5f);
		}

	return light_items;
}

void light_grid(Gnode& parent, span2d<LightInstance> light_grid, bool moving, LightType light_type, float range, float attenuation, float spot_angle, float spot_attenuation)
{
	size_t size_x = light_grid.m_x / 2;
	size_t size_y = light_grid.m_y / 2;
	float spacing = 4.f * 2.f;
	vec3 center = { (size_x-1) * spacing * -0.5f, 0.f, (size_y-1) * spacing * -0.5f };

	for(size_t x = 0; x < size_x; ++x)
		for(size_t y = 0; y < size_y; ++y)
		{
			LightInstance& light_item = light_grid[x + y * size_x];

			float height = moving ? sinf(g_time + float(y + x) * 0.21f) * 5.f : 5.f;

			Gnode& light_node = gfx::node(parent, {}, center + vec3{ x * spacing, height, y * spacing }, angle_axis(c_pi / 2.f, X3));
			Light& light = gfx::light(light_node, light_type, false, light_item.colour, range, attenuation);
			if(light_type == LightType::Spot)
			{
				light.m_spot_attenuation = spot_attenuation;
				light.m_spot_angle = spot_angle;
			}

			gfx::shape(light_node, Cube(0.1f), Symbol(), ItemFlag::Default | ItemFlag::Selectable);
			//if(light_type == LightType::Point)
			//	gfx::shape(light_node, Spheroid(range), Symbol::wire(hsl(float(light.m_shot_index) / float(255.f), 1.f, 0.5f)), ItemFlag::Default | ItemFlag::Selectable);
			
		}
}

#ifdef DOCKBAR
void ex_04_lights(Shell& app, Widget& parent, Dockbar& dockbar)
#else
void ex_04_lights(Shell& app, Widget& parent)
#endif
{
	UNUSED(app);
#ifdef MUD_PLATFORM_EMSCRIPTEN
	g_time += 0.02f;
#else
	g_time += 0.01f;
#endif

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::free_orbit_controller(viewer);

	//viewer.m_viewport.comp<Tonemap>().m_enabled = true;

	Gnode& scene = viewer.m_scene.begin();

	Material& material = milky_white(app.m_gfx_system);

	//gfx::radiance(scene, "radiance/rocky_ridge_1k.hdr", BackgroundMode::None);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder(1.f, 2.f, Axis::Y) }; // @todo Circle() looks weird
	static vector<ShapeInstance> shape_items = create_shape_grid(10U, 10U, shapes);
	static vector<LightInstance> light_items = create_light_grid(10U, 10U);

#if DEBUG_CLUSTERED
	static bool debug = true;
#endif
	static bool clustered = true;
	static bool ground = false;
	static bool moving_lights = false;
	static LightType light_type = LightType::Point;
	static float light_range = 9.f;
	static float light_attenuation = 0.4f;
	static float spot_angle = 45.f;
	static float spot_attenuation = 0.9f;

	static Symbol symbol;

	shape_grid(scene, { shape_items.data(), 10U, 10U }, &symbol, true, &material);
	light_grid(scene, { light_items.data(), 10U, 10U }, moving_lights, light_type, light_range, light_attenuation, spot_angle, spot_attenuation);

#if OCCLUSION
	Colour pink = { 1.f, 0.f, 1.f, 0.15f };
	gfx::draw(scene, Quad(vec2(40.f), X3,  Y3), Symbol::wire(Colour::White), ItemFlag::Render);
	gfx::shape(scene, Quad(vec2(40.f), X3,  Y3), Symbol::plain(Colour::Invisible),  ItemFlag::Render | ItemFlag::Occluder);
	gfx::shape(scene, Quad(vec2(40.f), X3, -Y3), Symbol::plain(Colour::Invisible),  ItemFlag::Render | ItemFlag::Occluder);
	//gfx::shape(scene, Cylinder(20.f, 20.f, Axis::Y), Symbol::plain(Colour::AlphaWhite), ItemFlag::Render | ItemFlag::Occluder);
#endif

#if CLUSTERED
	Camera& camera = viewer.m_camera;
	if(clustered && viewer.m_viewport.m_rect != uvec4(0U) && !camera.m_clusters)
	{
		camera.m_clustered = true;
		camera.m_clusters = make_unique<Froxelizer>(app.m_gfx_system);
		camera.m_clusters->prepare(viewer.m_viewport, camera.m_projection, camera.m_near, camera.m_far);
	}
#endif

#if DEBUG_CLUSTERED
	if(debug)
	{
		Viewer& debug_viewer = ui::viewer(parent, viewer.m_scene);
		ui::free_orbit_controller(debug_viewer);
		debug_draw_light_clusters(scene, viewer.m_camera);
	}
#endif

	if(ground)
	{
		Gnode& ground_node = gfx::node(scene, {}, vec3{ 0.f, -5.f, 0.f });
		gfx::shape(ground_node, Rect(vec2{ -50.f, -50.f }, vec2{ 100.f }), Symbol(), 0U, &material);
	}

#if DOCKBAR
	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::columns(*dock, { 0.3f, 0.7f });

		ui::label(sheet, "Zone :");
		ui::number_field<float>(sheet, "Ambient", { viewer.m_scene.m_env.m_radiance.m_ambient, { 0.f, 100.f, 0.01f } });

		ui::label(sheet, "Lights :");

		ui::input_field<bool>(sheet, "Moving", moving_lights);

		uint32_t light_type_index = UINT32_MAX;
		cstring light_types[3] = { "Direct", "Point", "Spot" };
		if(ui::radio_field(sheet, "Type", light_types, light_type_index))
			light_type = LightType(light_type_index);

		ui::slider_field<float>(sheet, "Range", { light_range, { 0.f, 100.f, 0.01f } });
		ui::slider_field<float>(sheet, "Attenuation", { light_attenuation, { 0.f, 4.f, 0.01f } });
		ui::slider_field<float>(sheet, "Spot Angle", { spot_angle, { 0.f, 180.f, 0.1f } });
		ui::slider_field<float>(sheet, "Spot Attenuation", { spot_attenuation, { 0.f, 4.f, 0.01f } });
	}
#endif
}

#ifdef _04_LIGHTS_EXE
void pump(Shell& app)
{
#if DOCKBAR
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_04_lights(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
#else
	ex_04_lights(app, app.m_ui->begin());
#endif
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif
