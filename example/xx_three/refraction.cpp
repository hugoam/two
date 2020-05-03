#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;
#else
#include <xx_three/xx_three.h>
#include <srlz/Serial.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>
#include <stl/vector.hpp>
#include <cstdio>
#endif

using namespace two;

EX(xx_refraction_mesh)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
	ControlNode& input = viewer;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
	ControlNode& input = window;
#endif

	static ImporterPLY ply_importer(app.m_gfx);

	static Node3* light = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 100000.f;
		camera.m_eye.z = -4000.f;

		Zone& env = scene.m_env;

		Texture& refraction = *app.m_gfx.textures().file("cube/park.jpg.cube");
		env.m_radiance.m_texture = &refraction;
		env.m_radiance.m_filter = false;
		env.m_background.m_texture = &refraction;
		env.m_background.m_mode = BackgroundMode::Panorama;

		env.m_radiance.m_ambient = Colour(1.f);

		Model& sphere = app.m_gfx.shape(Sphere(100.f * 0.05f));

		Node3& ln = gfx::nodes(scene).add(Node3());
		gfx::lights(scene).add(Light(ln, LightType::Point, false, rgb(0xffffff), 2.f, 0.f));
		gfx::items(scene).add(Item(ln, sphere, 0U, &gfx::solid_material(app.m_gfx, "light", rgb(0xffffff))));
		light = &ln;

		// material samples

		//static Program& phong = *app.m_gfx.programs().file("pbr/phong");
		static Program& phong = *app.m_gfx.programs().file("pbr/lambert");

		auto phong_material = [&](const string& name, Colour colour, float refraction, float reflectivity = 1.f) -> Material&
		{
			return app.m_gfx.materials().create(name, [&](Material& m) {
				m.m_program = &phong;
				m.m_phong.m_diffuse = colour;
				m.m_lit.m_refraction = refraction;
				m.m_phong.m_reflectivity = reflectivity;
			});
		};

		Material& m3 = phong_material("refraction0", rgb(0xccddff), 0.98f, 0.9f);
		Material& m2 = phong_material("refraction1", rgb(0xccfffd), 0.985f);
		Material& m1 = phong_material("refraction2", rgb(0xffffff), 0.98f);

		Model& model = *app.m_gfx.models().file("Lucy100k"); // .ply

		const float s = 1.5f;

		Node3& n0 = gfx::nodes(scene).add(Node3(vec3(0.f, 0.f, 0.f), ZeroQuat, vec3(s)));
		gfx::items(scene).add(Item(n0, model, 0U, &m1));

		Node3& n1 = gfx::nodes(scene).add(Node3(vec3(-1500.f, 0.f, 0.f), ZeroQuat, vec3(s)));
		gfx::items(scene).add(Item(n1, model, 0U, &m2));

		Node3& n2 = gfx::nodes(scene).add(Node3(vec3(1500.f, 0.f, 0.f), ZeroQuat, vec3(s)));
		gfx::items(scene).add(Item(n2, model, 0U, &m3));
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = input.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_size / 2.f) * 4.f;
	}
	
	float timer = app.m_gfx.m_time * -0.2;

	Camera& camera = viewer.m_camera;
	camera.m_eye.x += (mouse.x - camera.m_eye.x) * .05f;
	camera.m_eye.y += (-mouse.y - camera.m_eye.y) * .05f;

	//camera.lookAt(scene.position);

	vec3 position = vec3(cos(timer), sin(timer), 0.f) * 1500.f;
	light->apply(position);
}