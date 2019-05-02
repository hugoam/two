//#include <two/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace two;

void xx_interact_cubes(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	//vec2 mouse = vec2(0.f); // , INTERSECTED;
	float radius = 100; float theta = 0;

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;
	Camera& camera = viewer.m_camera;

	if(init)
	{
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 10000.f;

		//scene.background = new THREE.Color(0xf0f0f0);

		gfx::lights(scene).add(Light(scene.m_root_node, LightType::Direct, false));
		//var light = new THREE.DirectionalLight(0xffffff, 1);
		//light.position.set(1, 1, 1).normalize();
		//scene.add(light);

		//var geometry = new THREE.BoxBufferGeometry(20, 20, 20);
		Model& model = app.m_gfx.shape(Cube(20.f));

		for(size_t i = 0; i < 2000; i++)
		{
			// new THREE.MeshLambertMaterial({ color: random() * 0xffffff })
			Material& material = app.m_gfx.fetch_material("cubes" + to_string(i), "pbr/pbr");
			material.m_pbr.m_albedo = hsl(randf(), 0.7f, 0.5f);

			const vec3 pos = vec3(randf(), randf(), randf()) * 800.f - 400.f;
			const vec3 angles = vec3(randf(), randf(), randf()) * c_2pi;
			const vec3 scale = vec3(randf(), randf(), randf()) + 0.5f;

			Node3& n = gfx::nodes(scene).add(Node3(pos, quat(angles), scale));
			Item& it = gfx::items(scene).add(Item(n, model, ItemFlag::Default | ItemFlag::Selectable, &material));
			UNUSED(it);
		}

		//raycaster = new THREE.Raycaster();
	}

	//if(MouseEvent mouse_event)
	//{
	//	mouse.x = (event.clientX / window.innerWidth) * 2 - 1;
	//	mouse.y = -(event.clientY / window.innerHeight) * 2 + 1;
	//}

	theta += 0.1f;

	camera.m_eye.x = radius * sin(to_radians(theta));
	camera.m_eye.y = radius * sin(to_radians(theta));
	camera.m_eye.z = radius * cos(to_radians(theta));
	//camera.m_target = scene.position;

	static Item* hovered = nullptr;

	auto hover = [](Item& item) { item.m_material->m_lit.m_emissive = rgba(0xff0000ff); };
	auto unhover = [](Item& item) { item.m_material->m_lit.m_emissive = rgba(0x00000000); };

	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		auto pick = [&](Item* item) { if(hovered) unhover(*hovered); hovered = item; if(hovered) hover(*hovered); };
		viewer.picker(0).pick_point(viewer.m_viewport, event.m_relative, pick, ItemFlag::Selectable);
	}

	// find intersections
	//raycaster.setFromCamera(mouse, camera);
	//
	//var intersects = raycaster.intersectObjects(scene.children);
	//
	//if(intersects.length > 0) {
	//
	//	if(INTERSECTED != intersects[0].object) {
	//
	//		if(INTERSECTED) INTERSECTED.material.emissive.setHex(INTERSECTED.currentHex);
	//
	//		INTERSECTED = intersects[0].object;
	//		INTERSECTED.currentHex = INTERSECTED.material.emissive.getHex();
	//		INTERSECTED.material.emissive.setHex(0xff0000);
	//
	//	}
	//
	//}
	//else {
	//
	//	if(INTERSECTED) INTERSECTED.material.emissive.setHex(INTERSECTED.currentHex);
	//
	//	INTERSECTED = null;
	//
	//}
}