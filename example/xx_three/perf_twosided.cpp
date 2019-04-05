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

	auto ungamma = [](const Colour& c) { return to_colour(pow(to_vec3(c), vec3(2.f))); };

	if(init)
	{
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 20000.f;
		camera.m_eye.z = 3200.f;

		viewer.m_viewport.m_to_gamma = true;

		viewer.m_viewport.m_clear_colour = ungamma(rgb(0x050505));

		Texture& reflection = *app.m_gfx.textures().file("cube/royal.jpg.cube");
		scene.m_env.m_radiance.m_texture = &reflection;
		scene.m_env.m_radiance.m_filter = false;

		scene.m_env.m_radiance.m_colour = rgb(0x050505);

		Node3& l0 = gfx::nodes(scene).add(Node3(vec3(4000.f, 0.f, 0.f)));
		gfx::lights(scene).add(Light(l0, LightType::Point, false, rgb(0x0011ff), 1.f, 5500.f));

		Node3& l1 = gfx::nodes(scene).add(Node3(vec3(-4000.f, 0.f, 0.f)));
		gfx::lights(scene).add(Light(l1, LightType::Point, false, rgb(0xff1100), 1.f, 5500.f));

		Node3& l2 = gfx::nodes(scene).add(Node3(vec3(0.f)));
		gfx::lights(scene).add(Light(l2, LightType::Point, false, rgb(0xffaa00), 2.f, 3000.f));
		
		Program& phong = *app.m_gfx.programs().file("pbr/phong");

		Material& material = app.m_gfx.materials().create("twosided",  [&](Material& m) {
			m.m_program = &phong;
			m.m_base.m_cull_mode = CullMode::None;
			m.m_phong.m_specular = rgb(0x101010);
			m.m_phong.m_shininess = 100.f;
			m.m_phong.m_reflectivity = 0.1f;
			m.m_phong.m_env_blend = PhongEnvBlendMode::Mix;
		});

		Model& geometry = app.m_gfx.shape(Sphere(1.f, 0.f, c_pi));
		//Model& geometry = app.m_gfx.shape(SphereRing(1.f, 0.f, c_pi));
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