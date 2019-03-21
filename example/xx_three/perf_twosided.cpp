//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_perf_twosided(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Camera& camera = viewer.m_camera;
	Scene& scene = viewer.m_scene;

	Texture& reflection = *app.m_gfx.textures().file("cube/royal.jpg.cube");

	if(init)
	{
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
		
		Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

		//var material = new THREE.MeshPhongMaterial({ specular: 0x101010, shininess : 100, envMap : reflectionCube, combine : THREE.MixOperation, reflectivity : 0.1, side : THREE.DoubleSide });
		Material& material = app.m_gfx.materials().create("material",  [&](Material& m) {
			m.m_program = &pbr; //m.m_pbr.m_albedo = rgb(0xaaaaaa); m.m_pbr.m_metallic = 1.0f; m.m_pbr.m_roughness = 0.66f;
			m.m_base.m_cull_mode = CullMode::None;
		});

		Model& geometry = app.m_gfx.shape(Sphere());
		//new THREE.SphereBufferGeometry(1, 32, 16, 0, c_pi);

		for(size_t i = 0; i < 5000; ++i)
		{
			vec3 p = vec3(randf(), randf(), randf()) * 10000.f - 5000.f;
			vec3 a = vec3(randf(), randf(), 0.f) * c_2pi;
			vec3 s = vec3(randf()) * 50.f + 100.f;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
		}
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_frame.m_size / 2.f) * 10.f;
	}

	camera.m_eye.x += (mouse.x - camera.m_eye.x) * .05f;
	camera.m_eye.y += (-mouse.y - camera.m_eye.y) * .05f;
}