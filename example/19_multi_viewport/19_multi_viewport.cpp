//#include <two/frame.h>
#include <frame/Api.h>

#include <19_multi_viewport/19_multi_viewport.h>
#include <03_materials/03_materials.h>

#include <stl/vector.hpp>

using namespace two;

size_t viewport_mode(Widget& parent)
{
	vector<size_t> num_viewer_vals = { 1, 2, 4 };

	ui::label(parent, "num viewports : ");
	static uint32_t choice = 1;
	ui::radio_switch(parent, { "1", "2", "4" }, choice);

	return num_viewer_vals[choice];
}

void ex_19_multi_viewport(Shell& app, Widget& parent, Dockbar& dockbar)
{
	static float time = 0.f;
	time += 0.01f;

	bool multiple_scene = false;

	static size_t num_viewers = 2;
	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
		num_viewers = viewport_mode(*dock);

	Widget& layout = ui::layout(parent);
	Widget& first_split = ui::board(layout);
	Widget* second_split = num_viewers > 2 ? &ui::board(layout) : nullptr;

	vector<Viewer*> viewers = {};

	if(!multiple_scene)
	{
		static Scene scene = { app.m_gfx };
		for(size_t i = 0; i < num_viewers; ++i)
			viewers.push_back(&ui::viewer(i >= 2 ? *second_split : first_split, scene));
	}
	else
	{
		for(size_t i = 0; i < num_viewers; ++i)
			viewers.push_back(&ui::scene_viewer(i >= 2 ? *second_split : first_split));
	}


	for(Viewer* viewer : viewers)
	{
		ui::orbit_controller(*viewer);

		Gnode& scene = viewer->m_scene->begin();

		for(size_t x = 0; x < 11; ++x)
			for(size_t y = 0; y < 11; ++y)
			{
				vec3 angles = { time + x * 0.21f, 0.f, time + y * 0.37f };
				vec3 pos = { -15.f + x * 3.f, 0, -15.f + y * 3.f };

				float r = ncosf(time + float(x) * 0.21f);
				float b = nsinf(time + float(y) * 0.37f);
				float g = ncosf(time);
				Colour color = { r, g, b };

				Gnode& gnode = gfx::node(scene, pos, quat(angles), vec3(1.f));
				gfx::shape(gnode, Cube(), Symbol(color, Colour::None));
			}
	}
}

#ifdef _19_MULTI_VIEWPORT_EXE
void pump(Shell& app, ShellWindow& window)
{
	shell_context(window.m_ui->begin(), app.m_editor);
	ex_19_multi_viewport(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(TWO_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif