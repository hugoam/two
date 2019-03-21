//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_interact_drag(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);

	TrackballController& controls = ui::trackball_controller(viewer);
	controls.m_staticMoving = true;
	controls.m_dynamicDampingFactor = 0.3f;

	Scene& scene = viewer.m_scene;

	static vector<Node3*> objects;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 5000.f;
		camera.m_eye.z = 1000.f;

		//scene.background = new THREE.Color(0xf0f0f0);

		//scene.add(new THREE.AmbientLight(0x505050));

		//var light = new THREE.SpotLight(0xffffff, 1.5);
		//light.position.set(0, 500, 2000);
		//light.angle = c_pi / 9;
		//
		//light.castShadow = true;
		//light.shadow.camera.near = 1000;
		//light.shadow.camera.far = 4000;
		//light.shadow.mapSize.width = 1024;
		//light.shadow.mapSize.height = 1024;
		//
		//scene.add(light);

		Model& geometry = app.m_gfx.shape(Cube(20.f));

		for(size_t i = 0; i < 200; i++)
		{
			vec3 p = vec3(randf() * 1000.f - 500.f, randf() * 600.f - 300.f, randf() * 800.f - 400.f);
			vec3 a = vec3(randf(), randf(), randf()) * c_2pi;
			vec3 s = vec3(randf(), randf(), randf()) * 2.f + 1.f;

			Material& material = gfx::pbr_material(app.m_gfx, "material" + to_string(i), rgb(randi<uint32_t>()));
			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));

			objects.push_back(&n);
		}

		//renderer.shadowMap.enabled = true;
		//renderer.shadowMap.type = THREE.PCFShadowMap;

		//var dragControls = new THREE.DragControls(objects, camera, renderer.domElement);
		//dragControls.addEventListener('dragstart', function() {
		//
		//	controls.enabled = false;
		//
		//});
		//dragControls.addEventListener('dragend', function() {
		//
		//	controls.enabled = true;
		//
		//});

	}
}
