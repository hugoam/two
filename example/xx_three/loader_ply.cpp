//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_loader_ply(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	static ImporterPLY importer_ply = { app.m_gfx };

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 35.f; camera.m_near = 1.f; camera.m_far = 15.f;
		camera.m_eye = vec3(3.f, 0.15f, 3.f);
		camera.m_target = vec3(0.f, -0.1f, 0.f);

		viewer.m_viewport.m_clear_colour = rgb(0x72645b);
		scene.m_env.m_background.m_colour = rgb(0x72645b);
		scene.m_env.m_radiance.m_colour = rgb(0x72645b);
		scene.m_env.m_radiance.m_energy = 1.f;
		//scene.background = new THREE.Color(  );
		//scene.fog = new THREE.Fog( 0x72645b, 2, 15 );

		auto add_light = [&](vec3 d, Colour color, float intensity)
		{
			//Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f), facing(d)));
			Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f), quat(d * c_pi2)));
			Light& l = gfx::lights(scene).add(Light(n, LightType::Direct, true, color, intensity));
			//l.m_shadow_range = 4.f;

			l.m_shadow_flags = CSM_Stabilize;
			l.m_shadow_bias = 0.1f;
#ifdef MUD_PLATFORM_EMSCRIPTEN
			l.m_shadow_num_splits = 2;
#else
			l.m_shadow_num_splits = 4;
#endif

			//var d = 1;
			//directionalLight.shadow.camera.left = -d;
			//directionalLight.shadow.camera.right = d;
			//directionalLight.shadow.camera.top = d;
			//directionalLight.shadow.camera.bottom = -d;
			//
			//directionalLight.shadow.camera.near = 1;
			//directionalLight.shadow.camera.far = 4;
			//
			//directionalLight.shadow.mapSize.width = 1024;
			//directionalLight.shadow.mapSize.height = 1024;

			//directionalLight.shadow.bias = -0.001;
		};

		// Ground

		{
			Material& material = app.m_gfx.materials().create("ground", [&](Material& m) {
				m.m_program = &pbr;
				m.m_pbr.m_albedo = rgb(0x999999);
				m.m_pbr.m_roughness = 0.f;
				//m.m_pbr.m_specular = rgb(0x101010);
				// Phong
			});

			Model& model = app.m_gfx.shape(Rect(vec2(0.f), vec2(40.f)));
			Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f, -0.5f, 0.f)));
			gfx::items(scene).add(Item(n, model, 0, &material));
		}

		Material& material = app.m_gfx.materials().create("material", [&](Material& m) {
			m.m_program = &pbr;
			m.m_pbr.m_albedo = rgb(0x0055ff);
			m.m_pbr.m_roughness = 0.f;
			// flatShading: true
		});

		// PLY file

		{
			Model& dolphin = *app.m_gfx.models().file("dolphins"); // .ply
			
			Node3& n = gfx::nodes(scene).add(Node3(vec3(-0.2f, 0.f, 0.3f), quat(vec3(-c_pi2, 0.f, 0.f)), vec3(0.001f)));
			gfx::items(scene).add(Item(n, dolphin, 0, &material));
		}

		{
			Model& lucy = *app.m_gfx.models().file("Lucy100k"); // .ply

			Node3& n = gfx::nodes(scene).add(Node3(vec3(-0.2f, 0.02f, -0.2f), quat(vec3(0.f)), vec3(0.0006f)));
			gfx::items(scene).add(Item(n, lucy, 0, &material));
		}

		// Lights

		//scene.add( new THREE.HemisphereLight( 0x443333, 0x111122 ) );

		add_light(normalize(vec3(-1.f, -1.f, -1.f)), rgb(0xffffff), 1.35f);
		add_light(normalize(vec3(-0.5f, -1.f, 1.f)), rgb(0xffaa00), 1.f);
	}


	const float timer = app.m_gfx.m_time * 0.5f;

	Camera& camera = viewer.m_camera;
	camera.m_eye.x = sin(timer) * 2.5f;
	camera.m_eye.z = cos(timer) * 2.5f;

	//camera.lookAt(cameraTarget);
}