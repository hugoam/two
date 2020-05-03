#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;
#else
#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>
#include <stl/vector.hpp>
#endif

using namespace two;

EX(xx_material_cubemap)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	static ImporterOBJ obj_importer = { app.m_gfx };

#if UI
	OrbitControls& controls = ui::orbit_controls(viewer);
	controls.enableDamping = true;
	controls.dampingFactor = 0.25f;
	controls.rotateSpeed = 0.35f;
	//controls.enableZoom = false;
	//controls.enablePan = false;
	//controls.minPolarAngle = c_pi / 4;
	//controls.maxPolarAngle = c_pi / 1.5;
#endif

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 5000.f;
		camera.m_eye.z = 2000.f;

		Texture& envmap = *app.m_gfx.textures().file("cube/royal.jpg.cube");
		scene.m_env.m_radiance.m_texture = &envmap;
		scene.m_env.m_radiance.m_filter = false;
		scene.m_env.m_background.m_texture = &envmap;
		scene.m_env.m_background.m_mode = BackgroundMode::Panorama;

		scene.m_env.m_radiance.m_ambient = rgb(0xffffff);

		//lights

		Node3& ln = gfx::nodes(scene).add(Node3());
		Light& l = gfx::lights(scene).add(Light(ln, LightType::Point, false, rgb(0xffffff), 2.f, 0.f));
		//light = &ln;

		Program& phong = *app.m_gfx.programs().file("pbr/phong");
		Program& lambert = *app.m_gfx.programs().file("pbr/lambert");
		Program& program = lambert;

		// materials

		Material& material3 = app.m_gfx.materials().create("material3", [&](Material& m) {
			m.m_program = &program;
			m.m_phong.m_diffuse = rgb(0xff6600);
			m.m_phong.m_reflectivity = 0.3f;
			m.m_phong.m_env_blend = PhongEnvBlendMode::Mix;
		});

		Material& material2 = app.m_gfx.materials().create("material2", [&](Material& m) {
			m.m_program = &program;
			m.m_phong.m_diffuse = rgb(0xffee00);
			m.m_lit.m_refraction = 0.95f;
		});

		Material& material1 = app.m_gfx.materials().create("material1", [&](Material& m) {
			m.m_program = &program;
			m.m_phong.m_diffuse = rgb(0xffffff);
		});

		Model& model = *app.m_gfx.models().file("WaltHead");

		Node3& n0 = gfx::nodes(scene).add(Node3(vec3(0.f, -500.f, 0.f), ZeroQuat, vec3(15.f)));
		gfx::items(scene).add(Item(n0, model, 0U, &material1));

		Node3& n1 = gfx::nodes(scene).add(Node3(vec3(-900.f, -500.f, 0.f), ZeroQuat, vec3(15.f)));
		gfx::items(scene).add(Item(n1, model, 0U, &material2));

		Node3& n2 = gfx::nodes(scene).add(Node3(vec3(900.f, -500.f, 0.f), ZeroQuat, vec3(15.f)));
		gfx::items(scene).add(Item(n2, model, 0U, &material3));
	}
}
