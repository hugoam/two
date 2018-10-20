#include <mud/mud.h>
#include <07_gltf/07_gltf.h>

using namespace mud;

void debug_normals(Gnode& parent, Mesh& mesh, const mat4& transform, float length = 1.f)
{
	MeshData source = mesh.m_cache;

	for(size_t i = 0; i < source.m_vertices.size(); ++i)
	{
		vec3 position = transform * vec4(source.position(), 1.f);
		vec3 normal = normalize(vec3(transform * vec4(source.normal(), 0.f)));
		gfx::draw(parent, Line(position, position + normal * length), Symbol(to_colour(normal)));
	}
}

void ex_07_gltf(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene->begin();

	gfx::direct_light_node(scene, sun_rotation(c_pi / 4.f, c_pi / 4.f));
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
	
	Gnode& model_node = gfx::node(scene);
	gfx::model(model_node, "DamagedHelmet");
	
	//Model& model = *viewer.m_gfx_system.models().file("DamagedHelmet");
	//debug_normals(scene, *model.m_meshes[0], model.m_items[0].m_transform, 0.2f);
	
	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
		edit_viewer_filters(*dock, viewer);
}

#ifdef _07_GLTF_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_07_gltf(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	cstring example_path = MUD_RESOURCE_PATH "examples/07_gltf/";
	Shell app(cstrarray(MUD_RESOURCE_PATH, example_path), argc, argv);
	app.run(pump);
}
#endif
