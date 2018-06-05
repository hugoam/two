#include <mud/mud.h> // @ todo why doesn't compile without this ?
#include <15_script/15_script.h>

#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>
#include <15_script/Generated/Module.h>

GameObject::GameObject(const ShapeInstance* shape, Material* material, Colour colour)
	: m_index(index(type<GameObject>(), this))
	, m_shape(shape)
	, m_colour(colour)
	, m_material(material)
{}

std::vector<GameObject> create_game_objects(GfxSystem& gfx_system, const std::vector<ShapeInstance>& items)
{
	// @todo make it either non-copy or fix indexing issues when copied (for now it is just unindexed)
	std::vector<GameObject> objects;
	objects.reserve(items.size());
	size_t index = 0;
	for(const ShapeInstance& shape_item : items)
		objects.emplace_back(&shape_item, &milky_white(gfx_system, "object_" + to_string(index++)), Colour::Pink);
	return objects;
}

static LuaScript create_script()
{
	LuaScript script = { "Example Script" };
	Var test = var(script);

	script.m_script =
		"\n"
		"if time == nil then" "\n"
		"    time = 0.0" "\n"
		"end" "\n"
		"\n"
		"time = time + 0.01" "\n"
		"\n"
		"for x = 1,10 do" "\n"
		"    for y = 0,9 do" "\n"
		"\n"
		"        local object = indexed(GameObject, x + y * 10)" "\n"
		"\n"
		"        local r = (math.cos(time + x * 0.21) + 1.0) / 2.0" "\n"
		"        local b = (math.sin(time + y * 0.37) + 1.0) / 2.0" "\n"
		"        local g = (math.cos(time) + 1.0) / 2.0" "\n"
		"\n"
		"        object.colour = Colour(r, g, b)" "\n"
		"\n"
		"    end" "\n"
		"end" "\n"
	;


	return script;
}

void ex_15_script(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& groot = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

	Gnode& ground_node = gfx::node(groot, {}, vec3{ 0.f, -5.f, 0.f });
	gfx::shape(ground_node, Rect(vec2{ -50.f, -50.f }, vec2{ 100.f }), Symbol(Colour::None, Colour::White), 0U, &material);

	gfx::directional_light_node(groot);
	gfx::radiance(groot, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static std::vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder() }; // @todo Circle() looks weird
	static std::vector<ShapeInstance > shape_items = create_shape_grid(10U, 10U, shapes);
	static std::vector<GameObject> objects = create_game_objects(viewer.m_gfx_system, shape_items);

	//shape_grid(groot, { shape_items.data(), 10U, 10U }, Symbol(Colour::None, Colour::White), shapes, true, &material);

	static size_t size_x = 10U;
	static size_t size_y = 10U;

	float spacing = 4.f;
	vec3 center = { size_x * spacing * -0.5f, 0.f, size_y * spacing * -0.5f };

	for(size_t x = 0; x < size_x; ++x)
		for(size_t y = 0; y < size_y; ++y)
		{
			GameObject& object = objects[x + y * size_x];
			object.m_material->m_pbr_block.m_albedo.m_value = object.m_colour;

			Gnode& shape_node = gfx::node(groot, {}, center + vec3{ x * spacing, 0.f, y * spacing });
			gfx::shape(shape_node, shapes[object.m_shape->index], Symbol(Colour::None, object.m_colour), ITEM_SELECTABLE, object.m_material);
		}

	static LuaInterpreter lua = { true };
	static Script script = create_script();
	script.m_interpreter = &lua;

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
	{
		script_edit(*dock, script);
	}

	script({});
}

#ifdef _15_SCRIPT_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_15_script(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);

	system().load_module(ex_15_script::m());

	app.m_lua.declareTypes();
	app.run(pump);
}
#endif