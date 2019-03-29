//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

void xx_lights_point(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);
	TrackballController& controls = ui::trackball_controller(viewer);
	controls.m_dynamicDampingFactor = 0.15f;
	
	//controls.keys = [65, 83, 68];

	Scene& scene = viewer.m_scene;

	static vector<Node3*> lights;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 300.f;
		camera.m_eye = vec3(0.f, 15.f, 150.f);

		Texture& hdrenv = *app.m_gfx.textures().file("radiance/tiber_1_1k.hdr");
		scene.m_env.m_radiance.m_texture = &hdrenv;
		//scene.m_env.m_background.m_texture = &hdrenv;
		//scene.m_env.m_background.m_mode = BackgroundMode::Panorama;


		Material& groundmat = app.m_gfx.materials().create("ground", [&](Material& m) {
			m.m_program = &app.m_gfx.programs().fetch("pbr/pbr");
			m.m_base.m_uv0_scale = { 20.f, 10.f };
			m.m_pbr.m_albedo = rgb(0xffffff);
			m.m_pbr.m_albedo = rgb(0x444444);
			m.m_pbr.m_albedo = app.m_gfx.textures().file("disturb.jpg");
			// Phong
		});
		//new THREE.MeshPhongMaterial({ color: 0xffffff, map: texture });

		// GROUND

		Model& model = app.m_gfx.shape(Rect(vec2(0.f), vec2(800.f, 400.f)));
		Node3& node = gfx::nodes(scene).add(Node3(vec3(0.f, -5.f, 0.f), quat(vec3(0.f))));
		gfx::items(scene).add(Item(node, model, 0, &groundmat));

		// OBJECTS
		//Material& material = gfx::pbr_material(app.m_gfx, "object", Colour(1.f));
		Material& material = gfx::pbr_material(app.m_gfx, "object", rgb(0xffffff), 0.5f, 1.0f);
		//new THREE.MeshStandardMaterial({ color: 0xffffff, roughness: 0.5f, metalness: 1.0f });

		Model& torus = app.m_gfx.shape(Torus(1.5f, 0.4f));
		//Model& torus = app.m_gfx.shape(Torus(1.f, 0.1f));

		//for(int i = 0; i < 1; i++) {
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

		float intensity = 2.5f;
		float distance = 100.f;
		//float decay = 2.0f;

		uint32_t colours[] = { 0xff0040, 0x0040ff, 0x80ff80, 0xffaa00, 0x00ffaa, 0xff1100 };

		Sphere sphere = Sphere(0.25f); //THREE.SphereBufferGeometry(0.25, 16, 8);
		Model& sphere_model = app.m_gfx.shape(sphere);

		lights.clear();
		for(int i = 0; i < 6; ++i)
		{
			Colour c = rgb(colours[i]);
			Material& m = gfx::solid_material(app.m_gfx, ("light" + to_string(i)).c_str(), c); //Material({ color: colours[i] }));
			Node3& n = gfx::nodes(scene).add(Node3());
			Light& l = gfx::lights(scene).add(Light(n, LightType::Point, false, c, intensity, distance));
			l.m_attenuation = 2.f;
			//l.decay = decay;
			Item& it = gfx::items(scene).add(Item(n, sphere_model, ItemFlag::Default, &m));
			UNUSED(it);

			lights.push_back(&n);
		}

		//Node3& direct_node = gfx::nodes(scene) += Node3());
		//Light& direct_light = gfx::lights(scene) += Light(direct_node, LightType::Direct)); //THREE.DirectionalLight(0xffffff, 0.05);
		//dlight.position.set(0.5f, 1, 0).normalize();
	}

	float coef0[] = { 0.7f, 0.3f, 0.7f, 0.3f, 0.3f, 0.7f };
	float coef1[] = { 0.3f, 0.7f, 0.5f, 0.5f, 0.5f, 0.5f };

	float d = 150;

	const float time = app.m_gfx.m_time * 0.2f;

	for(int i = 0; i < 6; ++i)
	{
		vec2 pos = vec2(sin(time * coef0[i]) * d, cos(time * coef1[i]) * d);
		lights[i]->apply(vec3(pos.x, 0.f, pos.y));
	}
}
