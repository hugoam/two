#include <math/Api.h>
#include <gfx/Api.h>
#include <gfx-ui/Api.h>
#include <mud/Shell.h>

#include <01_shapes/01_shapes.h>

using namespace mud;

std::vector<ShapeInstance> create_shape_grid(size_t size_x, size_t size_y, const std::vector<ShapeVar> shapes)
{
	std::vector<ShapeInstance> shape_items = {};
	shape_items.resize(size_x * size_y);

	for(size_t x = 0; x < size_x; ++x)
		for(size_t y = 0; y < size_y; ++y)
		{
			shape_items[x + y * size_x].index = random_integer(size_t(0), shapes.size() - 1);
		}

	return shape_items;
}

void shape_grid(Gnode& parent, array_2d<ShapeInstance> shape_grid, const Symbol& symbol, const std::vector<ShapeVar> shapes, bool rotate, Material* material)
{
	static float time = 0.f;
	time += 0.01f;

	static Clock clock;
	bool swap = false;
	if(clock.read() > 1.f)
	{
		//swap = true;
		clock.step();
	}

	float spacing = 4.f;
	vec3 center = { (shape_grid.m_size_x-1) * spacing * -0.5f, 0.f, (shape_grid.m_size_y-1) * spacing * -0.5f };

	//size_t x = shape_grid.m_size_x - 1;
	//size_t y = shape_grid.m_size_y - 1;
	for(size_t x = 0; x < shape_grid.m_size_x; ++x)
		for(size_t y = 0; y < shape_grid.m_size_y; ++y)
		{
			ShapeInstance& shape_item = shape_grid[x + y * shape_grid.m_size_x];

			if(swap)
				shape_item.index = (shape_item.index + 1) % shapes.size();

			vec3 angles = rotate ? vec3{ time + float(x) * 0.21f, 0.f, time + float(y) * 0.37f }
								 : Zero3;

			Gnode& node = gfx::node(parent, {}, center + vec3{ x * spacing, 0.f, y * spacing }, quat(angles));
			gfx::shape(node, shapes[shape_item.index], symbol, ItemFlag::Default | ItemFlag::Selectable, material);
		}
}

void ex_01_shapes(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene->begin();

	Gnode& node = gfx::node(scene, {}, vec3(-5.f, 0.f, -5.f));
	gfx::shape(node, Grid2({ 10.f, 10.f }), Symbol(Colour::AlphaGrey));

	static std::vector<ShapeVar> shapes = { Cube(), Sphere(), Spheroid(), Cylinder(), Rect(), Circle() };
	static std::vector<ShapeInstance > shape_items = create_shape_grid(10U, 10U, shapes);

	shape_grid(scene, { shape_items.data(), 10U, 10U }, Symbol::wire(Colour::Red), shapes);
}

#ifdef _01_SHAPES_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_01_shapes(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif

