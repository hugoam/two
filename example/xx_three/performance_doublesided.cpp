//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_performance_doublesided(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Camera& camera = viewer.m_camera;
	Scene& scene = viewer.m_scene;

	Texture& reflection = *app.m_gfx.textures().file("SwedishRoyalCastle.cube");

	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	//var material = new THREE.MeshPhongMaterial({ specular: 0x101010, shininess : 100, envMap : reflectionCube, combine : THREE.MixOperation, reflectivity : 0.1, side : THREE.DoubleSide });
	static Material& material = app.m_gfx.materials().create("material",  [&](Material& m) {
		m.m_program = &pbr; //m.m_pbr.m_albedo = rgb(0xaaaaaa); m.m_pbr.m_metallic = 1.0f; m.m_pbr.m_roughness = 0.66f;
		m.m_base.m_cull_mode = CullMode::None;
	});

	static bool once = false;
	if(!once)
	{
		once = true;

		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 20000.f;
		camera.m_eye.z = 3200.f;

		//scene.background = new THREE.Color(0x050505);

		//scene.add(new THREE.AmbientLight(0x050505));

		Node3& l0 = gfx::nodes(scene).add(Node3(vec3(4000.f, 0.f, 0.f)));
		gfx::lights(scene).add(Light(l0, LightType::Point, false, rgb(0x0011ff), 1.f, 5500.f));

		Node3& l1 = gfx::nodes(scene).add(Node3(vec3(-4000.f, 0.f, 0.f)));
		gfx::lights(scene).add(Light(l1, LightType::Point, false, rgb(0xff1100), 1.f, 5500.f));

		Node3& l2 = gfx::nodes(scene).add(Node3(vec3(0.f)));
		gfx::lights(scene).add(Light(l2, LightType::Point, false, rgb(0xffaa00), 2.f, 3000.f));

		Model& geometry = app.m_gfx.shape(Sphere());
		//new THREE.SphereBufferGeometry(1, 32, 16, 0, PI);

		for(size_t i = 0; i < 5000; ++i)
		{
			vec3 p = vec3(randf(), randf(), randf()) * 10000.f - 5000.f;
			vec3 a = vec3(randf(), randf(), 0.f) * c_2pi;
			vec3 s = vec3(randf()) * 50.f + 100.f;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
		}
	}

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		vec2 coord = mouse_event.m_relative;
		camera.m_eye.x += (coord.x - camera.m_eye.x) * 0.05f;
		camera.m_eye.y += (-coord.y - camera.m_eye.y) * 0.05f;
	}
}