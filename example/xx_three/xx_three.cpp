//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

#define SIDE_PANEL 1

// html ok :
// xx_shadow_point (try shadows)
// xx_tiled_forward (fix clusters)

// ported not ok:
// xx_geom_points
// xx_geom_points_instanced

// todo:
//xx_depth_texture
//xx_effect_dof
//xx_lines_dashed
//xx_geom
//xx_geom_instances

using ExampleFunc = void(*)(Shell&, Widget&, Dockbar&, bool);
struct Example { string name; ExampleFunc func; };
Example examples[] = 
{
	"lights/point",			xx_lights_point,
	"shadow/point",			xx_shadow_point,
	"shader",				xx_shader,
	"shader/lava",			xx_shader_lava,
	"tiledforward",			xx_tiled_forward,
	"perf",					xx_perf,
	"perf/twosided",		xx_perf_twosided,
	"perf/static",			xx_perf_static,
	"billboards",			xx_billboards,
	"lines/fat",			xx_lines_fat,
	"lines/dashed",			xx_lines_dashed,
	"geom",					xx_geom,
	"geom/sprites",			xx_geom_sprites,
	"geom/instances",		xx_geom_instances,
	"geom/lines",			xx_geom_lines,
	"geom/points",			xx_geom_points,
	"geom/points/instance", xx_geom_points_instanced,
	"geom/rawshader",		xx_geom_rawshader,
	"geom/selective",		xx_geom_selective,
	//"interact/cubes",		xx_interact_cubes,
	//"interact/cubes",		xx_interact_geom,
	"marchingcubes",		xx_marching_cubes,
	"hierarchy",			xx_hierarchy,
	"hierarchy2",			xx_hierarchy2,
	"materials/skin",		xx_materials_skin,
	"materials/standard",	xx_materials_standard,
	"materials/variations", xx_materials_variations,
	"depthtexture",			xx_depth_texture,
	"effect/dof",			xx_effect_dof,
	"effect/godrays",		xx_effect_godrays,
	"effect/glitch",		xx_effect_glitch,
	"effect/sao",			xx_effect_sao,
};

vector<cstring> example_labels()
{
	vector<cstring> vec;
	for(const Example& ex : examples)
		vec.push_back(ex.name.c_str());
	return vec;
}

void ex_xx_three(Shell& app, Widget& parent, Dockbar& dockbar)
{
	static vector<cstring> labels = example_labels();
	static uint32_t example = 0;
	static bool init = true;

#if SIDE_PANEL
	Widget& sheet = ui::board(parent);
	bool changed = ui::radio_switch(sheet, labels, example, Axis::Y);
#else
	Widget& sheet = ui::sheet(parent);
	bool changed = ui::dropdown_field(sheet, "switch example:", labels, example);
#endif

	Widget& canvas = ui::sheet(sheet);
	if(changed)
	{
		//app.m_gfx.models().clear();
		app.m_gfx.materials().clear();

		canvas.clear();

		init = true;
	}

	examples[example].func(app, canvas, dockbar, init);
	init = false;
}

#ifdef _XX_THREE_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_xx_three(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx.add_resource_path("examples/xx_three");
	app.m_gfx.init_pipeline(pipeline_pbr);
	//app.m_gfx.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
