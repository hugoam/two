//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_refraction(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	static Texture& refraction = *app.m_gfx.textures().file("Park3Med.jpg.cube");
	//textureCube.mapping = THREE.CubeRefractionMapping;

	Scene& scene = viewer.m_scene;

	static Node3* light = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 100000.f;
		camera.m_eye.z = -4000.f;

		scene.m_env.m_radiance.m_texture = &refraction;

		//var ambient = new THREE.AmbientLight(0xffffff);

		Model& sphere = app.m_gfx.shape(Sphere(100.f * 0.05f));

		Node3& ln = gfx::nodes(scene).add(Node3());
		gfx::lights(scene).add(Light(ln, LightType::Point, false, rgb(0xffffff), 2.f));
		gfx::items(scene).add(Item(ln, sphere, 0U, &gfx::solid_material(app.m_gfx, "light", rgb(0xffffff))));
		light = &ln;

		// material samples

		auto phong_material = [&](const string& name, Colour colour, float refraction, float reflectivity = 0.f) -> Material&
		{
			return app.m_gfx.materials().create(name, [&](Material& m) {
				m.m_program = &pbr;
				m.m_pbr.m_specular_mode = PbrSpecularMode::Phong;
				m.m_pbr.m_refraction = refraction;
				//m.m_pbr.m_reflectivity = reflectivity;
			});
		};

		Material& m3 = phong_material("material0", rgb(0xccddff), 0.98f, 0.9f);
		Material& m2 = phong_material("material1", rgb(0xccfffd), 0.985f);
		Material& m1 = phong_material("material2", rgb(0xffffff), 0.98f);

		//var loader = new THREE.PLYLoader();
		Model& model = *app.m_gfx.models().file("Lucy100k.ply");
		//geometry.computeVertexNormals();

		const float s = 1.5f;

		Node3& n0 = gfx::nodes(scene).add(Node3(vec3(0.f, 0.f, 0.f), ZeroQuat, vec3(s)));
		gfx::items(scene).add(Item(n0, model, 0U, &m1));

		Node3& n1 = gfx::nodes(scene).add(Node3(vec3(-1500.f, 0.f, 0.f), ZeroQuat, vec3(s)));
		gfx::items(scene).add(Item(n1, model, 0U, &m2));

		Node3& n2 = gfx::nodes(scene).add(Node3(vec3(1500.f, 0.f, 0.f), ZeroQuat, vec3(s)));
		gfx::items(scene).add(Item(n2, model, 0U, &m3));
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_frame.m_size / 2.f) * 4.f;
	}
	
	float timer = app.m_gfx.m_time * -0.0002;

	Camera& camera = viewer.m_camera;
	camera.m_eye.x += (mouse.x - camera.m_eye.x) * .05f;
	camera.m_eye.y += (-mouse.y - camera.m_eye.y) * .05f;

	//camera.lookAt(scene.position);

	vec3 position = vec3(cos(timer), sin(timer), 0.f) * 1500.f;
	light->apply(position);
}