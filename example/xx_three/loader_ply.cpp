module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

#define CUSTOM_RENDER 0

EX(xx_loader_ply)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = *ui::scene_viewer(key(), parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	static ImporterPLY importer_ply = { app.m_gfx };

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 35.f; camera.m_near = 1.f; camera.m_far = 15.f;
		camera.m_eye = vec3(3.f, 0.15f, 3.f);
		camera.m_target = vec3(0.f, -0.1f, 0.f);

		viewer.m_viewport.m_to_gamma = true;

		//Colour colour = to_linear(rgb(0x72645b));
		Colour colour = to_colour(pow(to_vec3(rgb(0x72645b)), vec3(2.f)));

		viewer.m_viewport.m_clear_colour = colour;

		Zone& env = scene.m_env;
		env.m_background.m_colour = colour;

		env.m_fog.m_enabled = true;
		env.m_fog.m_colour = colour;
		env.m_fog.m_depth_begin = 2.f;
		env.m_fog.m_depth_end = 15.f;

		auto add_light = [&](vec3 d, Colour color, float intensity, bool shadows)
		{
			const quat r = look_dir(normalize(d));
			Node3Handle n = Node3(vec3(0.f), r).add(scene.m_graph);
			LightHandle l = Light(n, LightType::Direct, shadows, color, intensity).add(scene.m_graph);
			//l->m_shadow_range = 4.f;
			//l.shadow.bias = -0.001;
		};

		Program& three = *app.m_gfx.programs().file("pbr/three");
		Program& phong = *app.m_gfx.programs().file("pbr/phong");

		// ground

		Material& groundmat = app.m_gfx.materials().create("plyground", [&](Material& m) {
			m.m_program = &phong;
			m.m_phong.m_diffuse = rgb(0x999999);
			m.m_phong.m_specular = rgb(0x101010);
		});

		Model& ground = app.m_gfx.shape(Rect(vec2(0.f), vec2(40.f)));
		Node3Handle n = Node3(vec3(0.f, -0.5f, 0.f)).add(scene.m_graph);
		Item(n, ground, 0, &groundmat).add(scene.m_graph);

		Material& material = app.m_gfx.materials().create("ply", [&](Material& m) {
			m.m_program = &three;
			m.m_base.m_flat_shaded = true;
			m.m_pbr.m_albedo = rgb(0x0055ff);
			// those are defaults in three.js standard material
			m.m_pbr.m_roughness = 0.5f;
			m.m_pbr.m_metallic = 0.5f;
		});

		// PLY models

		Model& dolphin = *app.m_gfx.models().file("dolphins"); // .ply
		Model& lucy = *app.m_gfx.models().file("Lucy100k"); // .ply
			
		Node3Handle n0 = Node3(vec3(-0.2f, 0.f, 0.3f), quat(vec3(-c_pi2, 0.f, 0.f)), vec3(0.001f)).add(scene.m_graph);
		Item(n0, dolphin, 0, &material).add(scene.m_graph);

		Node3Handle n1 = Node3(vec3(-0.2f, -0.02f, -0.2f), quat(vec3(0.f)), vec3(0.0006f)).add(scene.m_graph);
		Item(n1, lucy, 0, &material).add(scene.m_graph);
	
		// lights

		scene.m_env.m_skylight = { true, 1.f, -y3, vec3(0.f), rgb(0x443333), rgb(0x111122) };

		add_light(normalize(vec3(-1.f, -1.f, -1.f)), rgb(0xffffff), 1.35f, true);
		add_light(normalize(vec3(-0.5f, -1.f, 1.f)), rgb(0xffaa00), 1.f, true);
	}

	const float timer = app.m_gfx.m_time * 0.5f;

	Camera& camera = viewer.m_camera;
	camera.m_eye.x = sin(timer) * 2.5f;
	camera.m_eye.z = cos(timer) * 2.5f;
}