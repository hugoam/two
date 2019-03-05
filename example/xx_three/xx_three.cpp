//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

void ex_xx_three(Shell& app, Widget& parent, Dockbar& dockbar)
{
	//xx_lights_point(app, parent, dockbar);
	//xx_shadow_point(app, parent, dockbar);
	//xx_shader(app, parent, dockbar);
	//xx_shader_lava(app, parent, dockbar);
	//xx_tiled_forward(app, parent, dockbar);
	//xx_performance(app, parent, dockbar);
	//xx_performance_doublesided(app, parent, dockbar);
	//xx_billboards(app, parent, dockbar);
	//xx_lines_fat(app, parent, dockbar);
	//xx_lines_dashed(app, parent, dockbar);
	//xx_geom(app, parent, dockbar);
	//xx_geom_sprites(app, parent, dockbar);
	//xx_geom_instances(app, parent, dockbar);
	//xx_geom_lines(app, parent, dockbar);
	//xx_geom_points(app, parent, dockbar);
	//xx_geom_points_packed(app, parent, dockbar);
	//xx_geom_points_instanced(app, parent, dockbar);
	//xx_geom_rawshader(app, parent, dockbar);
	//xx_geom_selective(app, parent, dockbar);
	//xx_interact_cubes(app, parent, dockbar);
	//xx_interact_geom(app, parent, dockbar);
	//xx_marching_cubes(app, parent, dockbar);
	//xx_hierarchy(app, parent, dockbar);
	//xx_hierarchy2(app, parent, dockbar);
	//xx_materials_skin(app, parent, dockbar);
	//xx_materials_standard(app, parent, dockbar);
	//xx_materials_variations(app, parent, dockbar);
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
	app.run(pump);
}
#endif
