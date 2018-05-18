#include <mud/mud.h>

#include <00_cube/00_cube.h>
#include <01_shapes/01_shapes.h>
#include <02_camera/02_camera.h>
#include <03_materials/03_materials.h>
#include <04_lights/04_lights.h>
#include <04_sponza/04_sponza.h>
#include <05_character/05_character.h>
#include <06_particles/06_particles.h>
#include <07_gltf/07_gltf.h>
#include <07_prefabs/07_prefabs.h>
#include <08_sky/08_sky.h>
#include <09_live_shader/09_live_shader.h>
#include <10_post_process/10_post_process.h>
#include <11_selection/11_selection.h>
#include <12_ui/12_ui.h>
#include <13_live_ui/13_live_ui.h>
#include <14_live_gfx/14_live_gfx.h>
#include <14_live_gfx_visual/14_live_gfx_visual.h>
#include <15_script/15_script.h>
#include <16_visual_script/16_visual_script.h>
#include <17_wfc/17_wfc.h>
//#include <18_pathfinding/18_pathfinding.h>
#include <19_multi_viewport/19_multi_viewport.h>
#include <20_meta/20_meta.h>

using namespace mud;

struct Example
{
	std::function<void(Shell&, Widget&, Dockbar&)> m_func;
	cstring m_name;
	bool m_with_tab;
};

static Example* current_example = nullptr;

static Example examples[] = {
	{ ex_00_cube,				"00_cube",				false },
	{ ex_01_shapes,				"01_shapes",			false },
	{ ex_02_camera,				"02_camera",			false },
	{ ex_03_materials,			"03_materials",			false },
	{ ex_04_lights,				"04_lights",			false },
	{ ex_04_sponza,				"04_sponza",			false },
	{ ex_05_character,			"05_character",			false },
	{ ex_06_particles,			"06_particles",			true  },
	{ ex_07_gltf,				"07_gltf",				false },
	{ ex_07_prefabs,			"07_prefabs",			false },
	{ ex_08_sky,				"08_sky",				true  },
	{ ex_09_live_shader,		"09_live_shader",		true  },
	{ ex_10_post_process,		"10_post_process",		true  },
	{ ex_11_selection,			"11_selection",			false },
	{ ex_12_ui,					"12_ui",				true  },
	{ ex_13_live_ui,			"13_live_ui",			true  },
	{ ex_14_live_gfx,			"14_live_gfx",			true  },
	{ ex_14_live_gfx_visual,	"14_live_gfx_visual",	true  },
	{ ex_15_script,				"15_script",			true  },
	{ ex_16_visual_script,		"16_visual_script",		true  },
	{ ex_17_wfc,				"17_wfc",				true  },
	{ ex_19_multi_viewport,		"19_multi_viewport",	false },
	{ ex_20_meta,				"20_meta",				true  },
};

void example_select(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	static std::vector<cstring> example_names = []() { std::vector<cstring> names; for(Example ex : examples) names.push_back(ex.m_name); return names; }();

	size_t example = 0;
	ui::label(parent, "Select an example");
	if(ui::dropdown_input(parent, example_names, example))
	{
		current_example = &examples[example];
		if(examples[example].m_with_tab)
			dockbar.m_current_tab = 1;
	}
}

void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor);

	if(Widget* dock = ui::dockitem(*app.m_editor.m_dockbar, "Options", carray<uint16_t, 1>{ 0U }))
		example_select(app, *dock, *app.m_editor.m_dockbar);
	
	if(current_example)
		current_example->m_func(app, ui::widget(*app.m_editor.m_screen, styles().board, current_example), *app.m_editor.m_dockbar);

	edit_tools(app.m_editor, *app.m_editor.m_screen);
}

int main(int argc, char *argv[])
{
	std::vector<string> example_paths = []() { std::vector<string> paths; for(Example ex : examples) paths.push_back(MUD_RESOURCE_PATH "examples/" + string(ex.m_name) + "/"); return paths; }();
	std::vector<cstring> resource_paths;
	resource_paths.push_back(MUD_RESOURCE_PATH);
	for(const string& path : example_paths)
		resource_paths.push_back(path.c_str());

	Shell app(resource_paths, argc, argv);
	app.run(pump);
}