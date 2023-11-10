//#include <two/frame.h>
#include <frame/Api.h>
#include <01_shapes/01_shapes.h>

#include <stl/vector.hpp>

using namespace two;

vector<ShapeInstance> create_shape_grid(size_t size_x, size_t size_y, span<ShapeVar> shapes, bool plain)
{
	vector<ShapeInstance> shape_items = {};
	shape_items.resize(size_x * size_y);

	for(size_t x = 0; x < size_x; ++x)
		for(size_t y = 0; y < size_y; ++y)
		{
			ShapeInstance& shape = shape_items[x + y * size_x];
			size_t index = randi(size_t(0), shapes.size() - 1);
			shape.shape = shapes[index];
			shape.colour = hsl(randf(0.f, 1.f), 1.f, 0.5f);
			shape.symbol = plain ? Symbol::plain(shape.colour) : Symbol::wire(shape.colour);
		}

	return shape_items;
}

void shape_grid(Gnode& parent, span2d<ShapeInstance> shape_grid, const Symbol* symbol, bool rotate, Material* material)
{
	static float time = 0.f;
	time += 0.01f;

	float spacing = 4.f;
	vec3 center = { (shape_grid.m_x-1) * spacing * -0.5f, 0.f, (shape_grid.m_y-1) * spacing * -0.5f };

	for(size_t x = 0; x < shape_grid.m_x; ++x)
		for(size_t y = 0; y < shape_grid.m_y; ++y)
		{
			const ShapeInstance& shape = shape_grid[x + y * shape_grid.m_x];

			vec3 angles = rotate ? vec3(time + float(x) * 0.21f, 0.f, time + float(y) * 0.37f)
								 : vec3(0.f);

			Gnode& node = gfx::node(parent, center + vec3(x * spacing, 0.f, y * spacing), quat(angles));
			gfx::shape(node, shape.shape, symbol ? *symbol : shape.symbol, ItemFlag::Default | ItemFlag::Selectable, material);
		}
}

void ex_01_shapes(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene.begin();

	Gnode& node = gfx::node(scene, vec3(-5.f, 0.f, -5.f));
	gfx::shape(node, Grid2({ 10.f, 10.f }), Symbol(Colour::AlphaGrey));

	static vector<ShapeVar> shapes = { Cube(), Sphere(), Spheroid(), Cylinder(), Rect(), Circle() };
	static vector<ShapeInstance > shape_items = create_shape_grid(10U, 10U, shapes, false);

	shape_grid(scene, { shape_items.data(), 10U, 10U });
}

#ifdef _01_SHAPES_EXE
void pump(Shell& app, ShellWindow& window)
{
	shell_context(window.m_ui->begin(), app.m_editor);
	ex_01_shapes(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(TWO_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif

