//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <02_camera/02_camera.h>
#include <03_materials/03_materials.h>

using namespace mud;

void ex_02_camera(Shell& app, Widget& parent, Dockbar& dockbar)
{
#if 1
	Viewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Scene& scene = *viewer.m_scene;

	static vector<Node3*> lights;

	static bool once = false;
	if(!once)
	{
		once = true;

		// MATERIALS

#if 0
		Texture* texture = app.m_gfx_system.textures().file("disturb.jpg");
		//texture.repeat.set( 20, 10 );
		//texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
		//texture.format = THREE.RGBFormat;

		Material& ground_material = app.m_gfx_system.materials().fetch("ground"); //new THREE.MeshPhongMaterial( { color: 0xffffff, map: texture } );
		Material& material = gfx::pbr_material(app.m_gfx_system, "object", from_rgba(0xffffff), 0.5f, 1.0f); //new THREE.MeshStandardMaterial( { color: 0xffffff, roughness: 0.5, metalness: 1.0 } );

		// GROUND

		Model& model = app.m_gfx_system.fetch_symbol(Symbol(), Rect(), DrawMode::PLAIN); //new THREE.Mesh( new THREE.PlaneBufferGeometry( 800, 400, 2, 2 ), groundMaterial );
		Node3& node = gfx::nodes(scene).add(Node3(vec3(0, -5, 0), quat(-c_pi / 2.f, 0, 0, 1)));
		gfx::items(scene).add(Item(node, model, 0, &ground_material));
#endif

		// OBJECTS
		Material& material = gfx::pbr_material(app.m_gfx_system, "object", Colour(1.f));//, 0.5, 1.0); //new THREE.MeshStandardMaterial( { color: 0xffffff, roughness: 0.5, metalness: 1.0 } );

		//var torus = Torus();
		Model& torus_model = app.m_gfx_system.fetch_symbol(Symbol(), Torus(1.f, 0.1f), DrawMode::PLAIN); //new THREE.TorusBufferGeometry( 1.5, 0.4, 8, 16 );

		for(int i = 0; i < 5000; i++) {

			float x = 400.f * (0.5 - random_scalar<float>());
			float y = 50.f * (0.5 - random_scalar<float>()) + 25;
			float z = 200.f * (0.5 - random_scalar<float>());

			float a = 3.14 * (0.5 - random_scalar<float>());
			float b = 3.14 * (0.5 - random_scalar<float>());

			Node3& n = gfx::nodes(scene).add(Node3(vec3(x, y, z), quat(a, b, 0, 1)));
			Item& it = gfx::items(scene).add(Item(n, torus_model, 0, &material));

			//gfx::update_item_aabb(it);

			//Gnode& n = gfx::node(root, {}, vec3(x, y, z));
			//gfx::item(n, torus_model, 0, &material);
		}

		// LIGHTS

		float intensity = 2.5;
		float distance = 100;
		float decay = 2.0;

		uint32_t colours[] = { 0xff0040, 0x0040ff, 0x80ff80, 0xffaa00, 0x00ffaa, 0xff1100 };

		Sphere sphere = Sphere(0.25); //THREE.SphereBufferGeometry( 0.25, 16, 8 );
		Model& sphere_model = app.m_gfx_system.fetch_symbol(Symbol(), sphere, DrawMode::PLAIN);

		for(int i = 0; i < 6; ++i)
		{
			Material& m = gfx::unshaded_material(app.m_gfx_system, ("light" + to_string(i)).c_str(), from_rgba(colours[i])); //Material({ color: colours[i] }) );
			Node3& n = gfx::nodes(scene).add(Node3());
			Light& l = gfx::lights(scene).add(Light(n, LightType::Point, false));
			l.m_colour = from_rgba(colours[i]);
			l.m_energy = intensity;
			l.m_range = distance;
			//l.decay = decay;
			Item& it = gfx::items(scene).add(Item(n, sphere_model, 0, &m));

			lights.push_back(&n);
		}

		//Node3& direct_node = gfx::nodes(scene).add(Node3());
		//Light& direct_light = gfx::lights(scene).add(Light(direct_node, LightType::Direct)); //THREE.DirectionalLight( 0xffffff, 0.05 );
		//dlight.position.set( 0.5, 1, 0 ).normalize();
	}

	//var scene = viewer.scene.begin();

	Gnode& root = viewer.m_scene->begin();

	Material& material = milky_white(app.m_gfx_system);

	//gfx::direct_light_node(root);
	gfx::radiance(root, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
	gfx::shape(root, Sphere(), Symbol(), 0U, &material);
	gfx::shape(root, Torus(1.f, 0.1f), Symbol(), 0U, &material);

	return;

	float coef0[] = { 0.7, 0.3, 0.7, 0.3, 0.3, 0.7 };
	float coef1[] = { 0.3, 0.7, 0.5, 0.5, 0.5, 0.5 };

	//var time = Date.now() * 0.00025;
	float d = 150;

	static float time = 0.f;
	time += 0.01f;

	for(int i = 0; i < 6; ++i)
	{
		vec2 pos = { sin(time * coef0[i]) * d, cos(time * coef1[i]) * d };
		lights[i]->m_transform = bxtranslation({ pos.x, 0.f, pos.y });
	}

#elif 1
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

