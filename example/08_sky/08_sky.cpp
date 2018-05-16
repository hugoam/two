#include <mud/mud.h>
#include <08_sky/08_sky.h>

#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

using namespace mud;

#if 0
static void generator_script(VisualScript& script)
{
	using Var = Valve;

	script.lock();

	Var& origin = script.getInput("origin");
	Var& height = script.function(noise).plug({});

	Var& sectors = script.function(sector_grid).plug({});
	Var& blocks = script.function(block_grid).plug({});

	script.unlock();
}
#endif

void example_options(Widget& parent, PerezSky& sky)
{
	//Widget& body = *ui::window(parent, "Procedural Sky").m_body;
	//Widget& body = ui::columns(parent, {});
	Widget& body = ui::table(parent, carray<cstring, 2>{ "field", "value" }, {});
	ui::slider_field<float>(body, "Time scale", { sky.m_time_scale, StatDef<float>(0.0f, 1.0f, 0.01f) });
	ui::slider_field<float>(body, "Time", { sky.m_time, StatDef<float>(0.0f, 24.0f) });
	ui::slider_field<float>(body, "Latitude", { sky.m_sun.m_latitude, StatDef<float>(-90.0f, 90.0f) });
	ui::slider_field<float>(body, "Turbidity", { sky.m_turbidity, StatDef<float>(1.9f, 10.0f, 0.1f) });
	ui::input_field<bool>(body, "Prevent color banding", sky.m_sky.m_preventBanding);

	static cstring months[12] =
	{
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	ui::dropdown_field(body, "Month", { months, 12 }, (size_t&)sky.m_sun.m_month);
}

static PerezSky g_sky;

void ex_08_sky(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	if(!g_sky.m_initialized)
		g_sky.init(*app.m_gfx_system);

	//app.m_gfx_system->m_pipeline->block<BlockTonemap>()->m_enabled = false;

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<size_t, 1>{ 1U }))
		example_options(*dock, g_sky);

	Gnode& groot = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

	Gnode& ground_node = gfx::node(groot, {}, vec3{ 0.f, -5.f, 0.f });
	gfx::shape(ground_node, Rect(vec2{ -50.f, -50.f }, vec2{ 100.f }), Symbol(Colour::None, Colour::White), 0U, &material);

	gfx::directional_light_node(groot, g_sky.m_sun.m_sun_rotation);
	gfx::radiance(groot, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static std::vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder() }; // @todo Circle() looks weird
	static std::vector<ShapeInstance > shape_items = create_shape_grid(10U, 10U, shapes);

	shape_grid(groot, { shape_items.data(), 10U, 10U }, Symbol(Colour::None, Colour::White), shapes, true, &material);

	gfx::custom_sky(groot, [](Render& render) { g_sky.render(render); });
}

#ifdef _08_SKY_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_08_sky(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif
