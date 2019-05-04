#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>

using namespace two;

EX(xx_light_point)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

#if UI
	TrackballController& controls = ui::trackball_controller(viewer);
	controls.m_dynamicDampingFactor = 0.15f;
#endif
	
	//controls.keys = [65, 83, 68];

	static vector<Node3*> lights;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 300.f;
		camera.m_eye = vec3(0.f, 15.f, 150.f);

		const Colour bg = to_linear(rgb(0x040306));
		viewer.m_viewport.m_to_gamma = true;
		viewer.m_viewport.m_clear_colour = bg;

		Zone& env = scene.m_env;
		env.m_fog = { true, 1.f, bg, true, 10.f, 300.f };

		Material& groundmat = app.m_gfx.materials().create("ground", [&](Material& m) {
			m.m_program = &app.m_gfx.programs().fetch("pbr/phong");
			m.m_base.m_uv0_scale = vec2(20.f, 10.f);
			m.m_phong.m_diffuse = app.m_gfx.textures().file("disturb.jpg");
		});

		// GROUND

		Model& model = app.m_gfx.shape(Rect(vec2(0.f), vec2(800.f, 400.f)));
		Node3& node = gfx::nodes(scene).add(Node3(vec3(0.f, -5.f, 0.f), quat(vec3(0.f))));
		gfx::items(scene).add(Item(node, model, 0, &groundmat));

		// OBJECTS

		Material& material = app.m_gfx.materials().create("lightpoint", [&](Material& m) {
			m.m_program = &app.m_gfx.programs().fetch("pbr/three");
			m.m_pbr.m_albedo = rgb(0xffffff);
			m.m_pbr.m_metallic = 1.f;
			m.m_pbr.m_roughness = 0.5f;
		});

		Symbol symbol; symbol.m_subdiv = uvec2(8, 16);
		Model& torus = app.m_gfx.shape(Torus(1.5f, 0.4f), symbol);
		//Model& torus = app.m_gfx.shape(Torus(1.f, 0.1f));

		for(int i = 0; i < 5000; i++) {

			float x = 400.f * (0.5f - randf());
			float y = 50.f * (0.5f - randf()) + 25;
			float z = 200.f * (0.5f - randf());

			float a = 3.14f * (0.5f - randf());
			float b = 3.14f * (0.5f - randf());

			uint32_t flags = ItemFlag::Default;// | ItemFlag::NoCull;
			//Node3& n = gfx::nodes(scene).add(Node3(vec3(x, y, z), quat(a, b, 0, 1)));
			Node3& n = gfx::nodes(scene).add(Node3(vec3(x, y, z), quat(vec3(a, b, 0.f))));
			Item& it = gfx::items(scene).add(Item(n, torus, flags, &material));
			UNUSED(it);
		}

		// LIGHTS

		constexpr float intensity = 2.5f;
		constexpr float distance = 100.f;
		constexpr float decay = 2.0f;

		constexpr uint32_t colours[] = { 0xff0040, 0x0040ff, 0x80ff80, 0xffaa00, 0x00ffaa, 0xff1100 };

		Sphere sphere = Sphere(0.25f);
		Model& sphere_model = app.m_gfx.shape(sphere);

		lights.clear();
		for(int i = 0; i < 6; ++i)
		{
			const Colour c = rgb(colours[i]);
			Material& m = gfx::solid_material(app.m_gfx, ("light" + to_string(i)).c_str(), c);
			Node3& n = gfx::nodes(scene).add(Node3());
			Light& l = gfx::lights(scene).add(Light(n, LightType::Point, false, c, intensity, distance));
			l.m_attenuation = decay;
			Item& it = gfx::items(scene).add(Item(n, sphere_model, ItemFlag::Default, &m));
			UNUSED(it);

			lights.push_back(&n);
		}

		Node3& dn = gfx::nodes(scene).add(Node3(vec3(0.f), look_dir(-vec3(0.5f, 1.f, 0.f))));
		gfx::lights(scene).add(Light(dn, LightType::Direct, false, rgb(0xffffff), 0.05f));
	}

	constexpr float coef0[] = { 0.7f, 0.3f, 0.7f, 0.3f, 0.3f, 0.7f };
	constexpr float coef1[] = { 0.3f, 0.7f, 0.5f, 0.5f, 0.5f, 0.5f };

	constexpr float d = 150.f;

	const float time = app.m_gfx.m_time * 0.2f;

	for(int i = 0; i < 6; ++i)
	{
		vec2 pos = vec2(sin(time * coef0[i]) * d, cos(time * coef1[i]) * d);
		lights[i]->apply(vec3(pos.x, 0.f, pos.y));
	}
}
