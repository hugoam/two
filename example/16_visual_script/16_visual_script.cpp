#include <mud/core.h>
#include <core/Types.h>
#include <lang/Api.h>
#include <uio/Api.h>
#include <noise/Api.h>

#include <11_selection/11_selection.h>
#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

using namespace mud;

void generator_script(VisualScript& script)
{
	using Var = Valve;

	script.lock();

	//Var& grid_size = script.value(100U);
	//Var& grid_size_3 = script.create<uvec3>({ &grid_size });
	//
	//Var& coords = script.function(grid, { &grid_size_3 });
	//
	//Var& coord_x = script.get(&vec3::x, { &coords });
	//Var& coord_y = script.get(&vec3::y, { &coords });
	//Var& coord_z = script.get(&vec3::z, { &coords });
	//Var& noise_type = script.value(Noise::Perlin);
	//Var& noise = script.function(noise_3d, { &coord_x, &coord_y, &coord_z, });

	Var& field = script.input("field");
	Var& noise = *script.function(noise_field_3d, { &field });
	UNUSED(noise);

	//script.unlock();
}

static VisualScript& create_script()
{
	Signature signature = { { Param{ "field", Ref(type<array_3d<float>>()) } } };
	static VisualScript script = { "Example Script", signature };
	generator_script(script);
	return script;
}

void ex_16_visual_script(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene->begin();

	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static VisualScript& script = create_script();

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
		visual_script_edit(*dock, script);

	static size_t field_size = 10U;
	static array_3d<float> noise_field = { field_size };

	std::vector<Var> args = { Ref(&noise_field) };
	script(args);

	Gnode& filled_node = gfx::node(scene);
	Gnode& empty_node = gfx::node(scene);

	std::vector<vec3> filled_positions;
	std::vector<vec3> empty_positions;

	for(size_t x = 0; x < field_size; ++x)
		for(size_t y = 0; y < field_size; ++y)
			for(size_t z = 0; z < field_size; ++z)
			{
				if(noise_field.at(x, y, z) < 0.5f)
					empty_positions.push_back({ x, y, z });
				else
					filled_positions.push_back({ x, y, z });
			}

	Item& filled_item = gfx::shape(filled_node, Cube(), Symbol(), 0U, nullptr, filled_positions.size());
	Item& empty_item = gfx::shape(empty_node, Cube(), Symbol(Colour::White, Colour::None), 0U, nullptr, empty_positions.size());

	for(size_t i = 0; i < filled_positions.size(); ++i)
		filled_item.m_instances[i] = bxtranslation(filled_positions[i]);

	for(size_t i = 0; i < empty_positions.size(); ++i)
		empty_item.m_instances[i] = bxtranslation(empty_positions[i]);
}

#ifdef _16_VISUAL_SCRIPT_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_16_visual_script(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, argc, argv);
	app.m_gfx_system.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
