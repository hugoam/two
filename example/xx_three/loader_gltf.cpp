//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_loader_gltf(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	static ImporterGltf importer_gltf = { app.m_gfx };

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);

	viewer.m_camera.m_target = vec3(0.f, -0.2f, -0.2f);
	//controls.target.set(0, -0.2, -0.2);
	//controls.update();

	Scene& scene = viewer.m_scene;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 45.f; camera.m_near = 0.25f; camera.m_far = 20.f;
		camera.m_eye = vec3(-1.8f, 0.9f, 2.7f);

		Texture& texture = *app.m_gfx.textures().file("cube/bridge.jpg.cube");
		scene.m_env.m_radiance.m_texture = &texture;
		scene.m_env.m_radiance.m_energy = 1.f;
		scene.m_env.m_radiance.m_colour = Colour(1.f);
		scene.m_env.m_background.m_texture = &texture;
		scene.m_env.m_background.m_mode = BackgroundMode::Panorama;

		//light = new THREE.HemisphereLight(0xbbbbff, 0x444422);
		//light.position.set(0, 1, 0);
		//scene.add(light);

		Model& model = *app.m_gfx.models().file("DamagedHelmet"); // .gltf");

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& i = gfx::items(scene).add(Item(n, model));
		UNUSED(i);
	}
}
