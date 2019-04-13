//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

#define SIDE_PANEL 1
#define MULTI_WINDOW 0
#define MULTI_VIEWPORT 0

// todo js:
// fix black helmet before envmap is filtered
// xx_light_point has weird white light near camera
// xx_shadow_point random crash (in atlas probably)
// xx_shader_ocean (need to pass mat4 to shader on material submit)

// todo:
// fix shadow filtering

// small:
// specular reflections are almost absent in xx_perf_twosided
// xx_material_standard no tonemapping in JS

// ported not ok:
// xx_geom_points_hw (doesn't work)
// xx_tiled_forward (fix clusters)

// todo js:
// xx_geom_dynamic

using ExampleFunc = void(*)(Shell&, Widget&, Dockbar&, bool);
struct Example { string name; ExampleFunc func; };
Example examples[] = 
{
	//{ "billboards",			xx_billboards },
	{ "depthtexture",			xx_depth_texture },
	{ "geom/dynamic",			xx_geom_dynamic },
	{ "geom/instances",			xx_geom_instances },
	{ "geom/lines",				xx_geom_lines },
	{ "geom/points",			xx_geom_points },
	//{ "geom/points/hw",		xx_geom_points_hw },
	{ "geom/rawshader",			xx_geom_rawshader },
	{ "geom/selective",			xx_geom_selective },
	{ "geom/sprites",			xx_geom_sprites },
	//{ "interact/cubes",		xx_interact_cubes },
	//{ "interact/geom",		xx_interact_geom },
	{ "hierarchy",				xx_hierarchy },
	{ "hierarchy2",				xx_hierarchy2 },
	{ "light/hemisphere",		xx_light_hemisphere },
	{ "light/point",			xx_light_point },
	{ "lines/dashed",			xx_lines_dashed },
	{ "lines/fat",				xx_lines_fat },
	{ "loader/gltf",			xx_loader_gltf },
	{ "loader/ply",				xx_loader_ply },
	{ "marchingcubes",			xx_marching_cubes },
	{ "material/cubemap",		xx_material_cubemap },
	{ "material/displace",		xx_material_displace },
	{ "material/skin",			xx_material_skin },
	{ "material/standard",		xx_material_standard },
	{ "material/variations",	xx_material_variations },
	{ "material/translucent",	xx_material_translucent },
	{ "perf",					xx_perf },
	//{ "perf/nodes",			xx_perf_nodes },
	//{ "perf/static",			xx_perf_static },
	{ "perf/twosided",			xx_perf_twosided },
	{ "effect",					xx_effect },
	{ "effect/bloom",			xx_effect_bloom },
	{ "effect/dof",				xx_effect_dof },
	//{ "effect/glitch",			xx_effect_glitch },
	{ "effect/godrays",			xx_effect_godrays },
	{ "effect/halftone",		xx_effect_halftone },
	{ "effect/sao",				xx_effect_sao },
	{ "effect/sobel",			xx_effect_sobel },
	{ "post/fxaa",				xx_post_fxaa },
	{ "cubemap/dynamic",		xx_cubemap_dynamic },
	{ "refraction/mesh",		xx_refraction_mesh },
	{ "refraction/balls",		xx_refraction_balls },
	{ "shader",					xx_shader },
	{ "shader/lava",			xx_shader_lava },
	{ "shader/ocean",			xx_shader_ocean },
	{ "shadow/point",			xx_shadow_point },
	{ "tiledforward",			xx_tiled_forward },
	{ "clustered",				xx_clustered },
};

vector<cstring> example_labels()
{
	vector<cstring> vec;
	for(const Example& ex : examples)
		vec.push_back(ex.name.c_str());
	return vec;
}

uint32_t find_example(const string& name)
{
	uint32_t i = 0;
	for(const Example& ex : examples)
	{
		if(ex.name == name)
			return i;
		++i;
	}
	return 0;
}

void ex_xx_three(Shell& app, Widget& parent, Dockbar& dockbar, bool& init, uint32_t& example)
{
	static vector<cstring> labels = example_labels();

#if !MULTI_VIEWPORT
#if SIDE_PANEL
	Widget& sheet = ui::board(parent);
	bool changed = ui::radio_switch(sheet, labels, example, Axis::Y);
#else
	Widget& sheet = ui::sheet(parent);
	bool changed = ui::dropdown_field(sheet, "switch example:", labels, example);
#endif
#else
	Widget& sheet = parent;
	bool changed = false;
#endif

	Widget& canvas = ui::sheet(sheet);
	if(changed)
	{
		//app.m_gfx.models().clear();
		//app.m_gfx.materials().clear();

		app.m_gfx.set_renderer(Shading::Shaded, render_pbr_forward);

		canvas.clear();

		init = true;
	}

	examples[example].func(app, canvas, dockbar, init);
	init = false;
}

#ifdef _XX_THREE_EXE
void pump(Shell& app, ShellWindow& window, bool& init, uint32_t& example)
{
	shell_context(window.m_ui->begin(), app.m_editor);
	ex_xx_three(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar, init, example);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv), false);
	app.m_gfx.add_resource_path("examples/xx_three");
	
	ShellWindow& w0 = app.window("two", uvec2(1600U, 900U));

	app.m_gfx.init_pipeline(pipeline_pbr);
	//app.m_gfx.init_pipeline(pipeline_minimal);

#if !MULTI_VIEWPORT && !MULTI_WINDOW
	//static uint32_t example = 0;
	//static uint32_t example = find_example("loader/gltf");
	static uint32_t example = find_example("perf/twosided");
	static bool init = true;

	app.run([](Shell& app, ShellWindow& win) { pump(app, win, init, example); });
#else
#if MULTI_WINDOW
	ShellWindow& w1 = app.window("two", uvec2(1600U, 900U));
#endif

	static uint32_t example[6] = {
		15, 16, 17, 18, 19, 20
	};
	
	static bool init[6] = {
		true, true, true, true, true, true
	};

	while(true)
	{
		bool pursue = app.begin_frame();

#if MULTI_VIEWPORT
		shell_context(w0.m_ui->begin(), app.m_editor);

		Widget& screen = ui::sheet(*app.m_editor.m_screen);

		Widget& row0 = ui::board(screen);
		Widget& row1 = ui::board(screen);

		for(size_t i = 0; i < 6; ++i)
		{
			Widget& parent = i < 3 ? row0 : row1;
			Widget& panel = ui::sheet(parent);
			ex_xx_three(app, panel, *app.m_editor.m_dockbar, init[i], example[i]);
	}
#else
		pump(app, w0, init0, example0);
#if MULTI_WINDOW
		pump(app, w1, init1, example1);
#endif
#endif

		app.end_frame();
		if(!pursue) break;
	}
#endif
}
#endif
