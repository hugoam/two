//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>
#include <ecs/ECS.hpp>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_material_standard(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	static ImporterOBJ importer_obj = { app.m_gfx };

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);
	ui::trackball_controller(viewer);

	Scene& scene = viewer.m_scene;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 0.01f; camera.m_far = 1000.f;
		camera.m_eye.z = 2.f;

		viewer.m_viewport.m_to_gamma = true;

		Tonemap& tonemap = viewer.m_viewport.comp<Tonemap>();
		tonemap.m_enabled = true;
		tonemap.m_mode = TonemapMode::Reinhardt;
		tonemap.m_exposure = 3.f;

		Zone& env = scene.m_env;

		Texture& hdrenv = *app.m_gfx.textures().file("cube/pisaHDR.hdr.cube");
		env.m_radiance.m_texture = &hdrenv;
		env.m_background.m_texture = &hdrenv;
		env.m_background.m_mode = BackgroundMode::Panorama;

		env.m_radiance.m_ambient = rgb(0xffffff);

		//env.m_skylight.m_enabled = true;
		env.m_skylight.m_color = rgb(0x443333);
		env.m_skylight.m_ground = rgb(0x222233);
		env.m_skylight.m_intensity = 4.f;

		Texture& albedo = *app.m_gfx.textures().file("cerberus/Cerberus_A.jpg");
		Texture& metrough = *app.m_gfx.textures().file("cerberus/Cerberus_RM.jpg");
		Texture& normal = *app.m_gfx.textures().file("cerberus/Cerberus_N.jpg");

		Model& model = *app.m_gfx.models().file("Cerberus");

		Program& pbr = *app.m_gfx.programs().file("pbr/pbr");
		Program& three = *app.m_gfx.programs().file("pbr/three");

		Material& material = app.m_gfx.materials().create("standard", [&](Material& m) {
			m.m_program = &three;
			m.m_pbr.m_metallic = 1.f;
			m.m_pbr.m_roughness = 1.f;
			m.m_pbr.m_albedo = &albedo;
			m.m_pbr.m_metallic = &metrough;
			m.m_pbr.m_roughness = &metrough;
			m.m_lit.m_normal = &normal;
		});

		const vec3 position = vec3(-0.45f, 0.f, 0.f);
		const vec3 angles = vec3(0.f, -c_pi2, 0.f);
		Node3& n = gfx::nodes(scene).add(Node3(position, quat(angles)));
		gfx::items(scene).add(Item(n, model, 0U, &material));
	}
}
