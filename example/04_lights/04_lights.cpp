#include <mud/mud.h>
#include <04_lights/04_lights.h>

#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

#include <meta/gfx/Convert.h>

using namespace mud;

static float g_time = 0.f;

struct LightInstance { Colour colour; };

std::vector<LightInstance> create_light_grid(size_t size_x, size_t size_y)
{
	std::vector<LightInstance> light_items = {};
	light_items.resize(size_x * size_y);

	for(size_t x = 0; x < size_x; ++x)
		for(size_t y = 0; y < size_y; ++y)
		{
			LightInstance& light_item = light_items[x + y * size_x];
			light_item.colour = hsla_to_rgba({ random_scalar(0.f, 1.f), 1.f, 0.5f });
		}

	return light_items;
}

void light_grid(Gnode& parent, array_2d<LightInstance> shape_grid, bool moving, LightType light_type, float range, float attenuation, float spot_angle, float spot_attenuation)
{
	size_t size_x = shape_grid.m_size_x / 2;
	size_t size_y = shape_grid.m_size_y / 2;
	float spacing = 4.f * 2.f;
	vec3 center = { size_x * spacing * -0.5f, 0.f, size_y * spacing * -0.5f };

	for(size_t x = 0; x < size_x; ++x)
		for(size_t y = 0; y < size_y; ++y)
		{
			LightInstance& light_item = shape_grid[x + y * size_x];

			float height = moving ? sinf(g_time + float(y + x) * 0.21f) * 5.f : 5.f;

			Gnode& light_node = gfx::node(parent, {}, center + vec3{ x * spacing, height, y * spacing }, angleAxis(c_pi / 2.f, X3));
			Light& light = gfx::light(light_node, light_type, false, light_item.colour, range, attenuation);
			if(light_type == LightType::Spot)
			{
				light.m_spot_attenuation = spot_attenuation;
				light.m_spot_angle = spot_angle;
			}

			gfx::shape(light_node, Cube(0.1f), Symbol(), ItemFlag::Default | ItemFlag::Selectable);
			//if(light_type == LightType::Point)
			//	gfx::shape(light_node, Spheroid(range), Symbol::wire(hsl_to_rgb(float(light.m_shot_index) / float(255.f), 1.f, 0.5f)), ItemFlag::Default | ItemFlag::Selectable);
			
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
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

	//gfx::radiance(scene, "radiance/rocky_ridge_1k.hdr", BackgroundMode::None);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static std::vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder(1.f, 2.f, Axis::Y) }; // @todo Circle() looks weird
	static std::vector<ShapeInstance > shape_items = create_shape_grid(10U, 10U, shapes);
	static std::vector<LightInstance > light_items = create_light_grid(10U, 10U);

	static bool debug = false;
	static bool clustered = true;
	static bool ground = false;
	static bool moving_lights = true;
	static LightType light_type = LightType::Point;
	static float light_range = 9.f;
	static float light_attenuation = 0.4f;
	static float spot_angle = 45.f;
	static float spot_attenuation = 0.9f;

	shape_grid(scene, { shape_items.data(), 10U, 10U }, Symbol(), shapes, true, &material);
	light_grid(scene, { light_items.data(), 10U, 10U }, moving_lights, light_type, light_range, light_attenuation, spot_angle, spot_attenuation);

	//gfx::shape(scene, Quad(vec2(50.f), X3, Y3), Symbol::plain(Colour::AlphaWhite), ItemFlag::Occluder);
	//gfx::shape(scene, Cylinder(20.f, 20.f, Axis::Y), Symbol::plain(Colour::AlphaWhite), ItemFlag::Occluder);

	if(clustered && viewer.m_viewport.m_rect != uvec4(0) && !viewer.m_camera.m_clusters)
	{
		viewer.m_camera.m_clustered = true;
		viewer.m_camera.m_clusters = make_unique<Froxelizer>(viewer.m_scene->m_gfx_system);
		viewer.m_camera.m_clusters->prepare(viewer.m_viewport, viewer.m_camera.m_projection, viewer.m_camera.m_near, viewer.m_camera.m_far);
	}

	if(debug)
	{
		Viewer& debug_viewer = ui::viewer(parent, *viewer.m_scene);
		ui::orbit_controller(debug_viewer);
		debug_draw_light_clusters(scene, viewer.m_camera);
	}

	if(ground)
	{
		Gnode& ground_node = gfx::node(scene, {}, vec3{ 0.f, -5.f, 0.f });
		gfx::shape(ground_node, Rect(vec2{ -50.f, -50.f }, vec2{ 100.f }), Symbol(), 0U, &material);
	}

#ifdef DOCKBAR
	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
	{
		Widget& sheet = ui::columns(*dock, carray<float, 2>{ 0.3f, 0.7f });

		ui::label(sheet, "Environment :");
		ui::number_field<float>(sheet, "Ambient", { viewer.m_environment.m_radiance.m_ambient, { 0.f, 100.f, 0.01f } });

		ui::label(sheet, "Lights :");

		ui::input_field<bool>(sheet, "Moving", moving_lights);

		uint32_t light_type_index = UINT32_MAX;
		carray<cstring, 2> light_types = { "Point", "Spot" };
		if(ui::radio_field(sheet, "Type", light_types, light_type_index))
			light_type = from_string<LightType>(light_types[light_type_index]);

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
#ifdef DOCKBAR
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_04_lights(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
#else
	ex_04_lights(app, app.m_ui->begin());
#endif
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif
