//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <02_camera/02_camera.h>
#include <03_materials/03_materials.h>

using namespace mud;

void ex_02_camera(Shell& app, Widget& parent, Dockbar& dockbar)
{
#if 1
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	static bool once = false;
	if(!once)
	{
		once = true;

		Program* pbr = app.m_gfx_system.programs().file("pbr/pbr");

		Material& c = app.m_gfx_system.materials().fetch("cube");
		c.m_program = pbr;
		c.m_pbr_block = PbrMaterialBlock(Colour(1.f, 0.f, 1.f));
		c.m_base_block.m_cull_mode = CullMode::Front;

		Material& s = app.m_gfx_system.materials().fetch("sphere");
		s.m_program = pbr;
		s.m_pbr_block.m_enabled = true;
		//s.m_pbr_block = PbrMaterialBlock(from_rgba(0xa0adaf));
	}

	Material& cube_material = app.m_gfx_system.materials().fetch("cube");
	Material& sphere_material = app.m_gfx_system.materials().fetch("sphere");

	auto light_source = [&](Gnode& parent, Colour color, vec3 pos, quat rot) -> Gnode&
	{
		float intensity = 1.5;
		float range = 20.f;

		Gnode& node = gfx::node(parent, {}, pos, rot);
		Light& light = gfx::light(node, LightType::Point, false, color, range, 0.4f);// intensity);
		Item& inner = gfx::shape(node, Sphere(0.3f), Symbol::plain(color * intensity));
		Item& outer = gfx::shape(node, Sphere(2.0f), Symbol::plain(Colour::White), 0U, &sphere_material);
		return node;
	};

	auto light_pos = [](float time) -> vec3
	{
		return vec3(sin(time * 0.6) * 9, sin(time * 0.7) * 9 + 5, sin(time * 0.8) * 9);
	};

	auto light_rot = [](float time) -> quat
	{
		return quat(vec3(time, 0.f, time));
	};

	Gnode& scene = viewer.m_scene.begin();

	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	double time = app.m_gfx_system.m_frame_time;//performance.now() * 0.001;
	vec3 pos0 = light_pos(time);
	quat rot0 = light_rot(time);
	Gnode& light0 = light_source(scene, from_rgba(0x0088ff), pos0, rot0);

	time += 10000;
	vec3 pos1 = light_pos(time);
	quat rot1 = light_rot(time);
	Gnode& light1 = light_source(scene, from_rgba(0xff8888), pos1, rot1);

	Box box = Cube(vec3(30.f));
	Gnode& node = gfx::node(scene, {}, Y3 * 10.f);
	gfx::shape(node, box, Symbol::plain(Colour::White), 0, &cube_material);

#else
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Material& material = milky_white(app.m_gfx_system);

	Gnode& scene = viewer.m_scene.begin();
	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
	gfx::shape(scene, Sphere(), Symbol(), 0U, &material);
#endif
}

#ifdef _02_CAMERA_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_02_camera(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif

