#include <mud/frame.h>
#include <refl/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>
#include <meta/gfx-gltf/Module.h>

#include <07_gltf/07_gltf.h>

using namespace mud;

void debug_normals(Gnode& parent, Mesh& mesh, const mat4& transform, float length = 1.f)
{
	MeshAdapter source = mesh.m_cache.read();

	for(size_t i = 0; i < source.m_vertices.size(); ++i)
	{
		vec3 position = mulp(transform, source.position());
		vec3 normal = muln(transform, source.normal());
		gfx::draw(parent, Line(position, position + normal * length), Symbol(to_colour(normal)));
	}
}

void ex_07_gltf(Shell& app, Widget& parent, Dockbar& dockbar)
{
	static ImporterGltf gltf_importer(app.m_gfx_system);

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene->begin();

	gfx::direct_light_node(scene, sun_rotation(c_pi / 4.f, c_pi / 4.f));
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
	
	Gnode& model_node = gfx::node(scene);
	gfx::model(model_node, "DamagedHelmet");
	
	//Model& model = *viewer.m_gfx_system.models().file("DamagedHelmet");
	//debug_normals(scene, *model.m_meshes[0], model.m_items[0].m_transform, 0.2f);
	
	//if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
	//	edit_viewer_filters(*dock, viewer);
}

#ifdef _07_GLTF_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_07_gltf(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv).c_str());
	app.m_gfx_system.add_resource_path("examples/07_gltf/");
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif
