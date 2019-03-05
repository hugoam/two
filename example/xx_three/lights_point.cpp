//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

void xx_lights_point(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);
	TrackballController& controls = ui::trackball_controller(viewer);
	controls.m_dynamicDampingFactor = 0.15f;
	
	//controls.keys = [65, 83, 68];

	Scene& scene = viewer.m_scene;

	static vector<Node3*> lights;

	static bool once = false;
	if(!once)
	{
		once = true;

		// MATERIALS

#if 0
		Texture* texture = app.m_gfx.textures().file("disturb.jpg");
		//texture.repeat.set(20, 10);
		//texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
		//texture.format = THREE.RGBFormat;

		Material& ground_material = app.m_gfx.materials().fetch("ground"); //new THREE.MeshPhongMaterial({ color: 0xffffff, map: texture });
		Material& material = gfx::pbr_material(app.m_gfx, "object", rgb(0xffffff), 0.5f, 1.0f); //new THREE.MeshStandardMaterial({ color: 0xffffff, roughness: 0.5f, metalness: 1.0f });

		// GROUND

		Model& model = app.m_gfx.shape(Rect()); //new THREE.Mesh(new THREE.PlaneBufferGeometry(800, 400, 2, 2), groundMaterial);
		Node3& node = gfx::nodes(scene) += Node3(vec3(0, -5, 0), quat(-c_pi / 2.f, 0, 0, 1)));
		gfx::items(scene) += Item(node, model, 0, &ground_material));
#endif

		// OBJECTS
		Material& material = gfx::pbr_material(app.m_gfx, "object", Colour(1.f));//, 0.5f, 1.0f); //new THREE.MeshStandardMaterial({ color: 0xffffff, roughness: 0.5f, metalness: 1.0f });

		//var torus = Torus();
		Model& torus_model = app.m_gfx.shape(Torus(1.f, 0.1f)); //new THREE.TorusBufferGeometry(1.5, 0.4, 8, 16);

		for(int i = 0; i < 5000; i++) {

			float x = 400.f * (0.5f - randf());
			float y = 50.f * (0.5f - randf()) + 25;
			float z = 200.f * (0.5f - randf());

			float a = 3.14f * (0.5f - randf());
			float b = 3.14f * (0.5f - randf());

			uint32_t flags = ItemFlag::Default;// | ItemFlag::NoCull;
			Node3& n = gfx::nodes(scene).add(Node3(vec3(x, y, z), quat(a, b, 0, 1)));
			Item& it = gfx::items(scene).add(Item(n, torus_model, flags, &material));
			UNUSED(it);

			//Gnode& n = gfx::node(root, {}, vec3(x, y, z));
			//gfx::item(n, torus_model, 0, &material);
		}

		// LIGHTS

		float intensity = 2.5f;
		float distance = 100.f;
		//float decay = 2.0f;

		uint32_t colours[] = { 0xff0040, 0x0040ff, 0x80ff80, 0xffaa00, 0x00ffaa, 0xff1100 };

		Sphere sphere = Sphere(2.5f); //THREE.SphereBufferGeometry(0.25, 16, 8);
		Model& sphere_model = app.m_gfx.shape(sphere);

		for(int i = 0; i < 6; ++i)
		{
			Colour c = rgb(colours[i]);
			Material& m = gfx::solid_material(app.m_gfx, ("light" + to_string(i)).c_str(), c); //Material({ color: colours[i] }));
			Node3& n = gfx::nodes(scene).add(Node3());
			Light& l = gfx::lights(scene).add(Light(n, LightType::Point, false));
			l.m_colour = c;
			l.m_energy = intensity;
			l.m_range = distance;
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

	Gnode& root = viewer.m_scene.begin();
	gfx::radiance(root, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	float coef0[] = { 0.7f, 0.3f, 0.7f, 0.3f, 0.3f, 0.7f };
	float coef1[] = { 0.3f, 0.7f, 0.5f, 0.5f, 0.5f, 0.5f };

	//var time = Date.now() * 0.00025;
	float d = 150;

	static float time = 0.f;
	time += 0.01f;

	for(int i = 0; i < 6; ++i)
	{
		vec2 pos = { sin(time * coef0[i]) * d, cos(time * coef1[i]) * d };
		lights[i]->m_transform = bxSRT(vec3(1.f), ZeroQuat, vec3(pos.x, 0.f, pos.y));
	}
}
