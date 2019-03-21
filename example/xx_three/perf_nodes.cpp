//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

//	import './js/nodes/THREE.Nodes.js';

void xx_perf_nodes(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	static Program& pbr = app.m_gfx.programs().fetch("pbr/pbr");

	static vector<Node3*> meshes;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye.z = 3200.f;

		//scene.add(new THREE.PointLight(0xFFFFFF));
		//scene.background = new THREE.Color(0xffffff);
	}

	auto createScene = [&](int MaterialClass, size_t count = 70)
	{
		Model& geometry = gfx::model_suzanne(app.m_gfx);

		for(size_t i = 0; i < meshes.size(); i++)
		{
			//meshes[i].material.dispose();
			//
			//scene.remove(meshes[i]);
		}

		meshes = {};

		for(size_t i = 0; i < count; i++)
		{
			const Colour colour = rgb(randi() * 0xffffff);

			Material& material = app.m_gfx.materials().create("material",  [&](Material& m) {
				m.m_program = &pbr;
				m.m_pbr.m_albedo = colour;
			});

			//var material = new MaterialClass(),
			//	

			//if(material.color.isNode) material.color.value.setHex(color);
			//else material.color.setHex(color);

			// prevent share code
			//material.defines.UUID = material.uuid;

			const vec3 p = vec3(randf(), randf(), randf()) * 1000.f - 500.f;
			const vec3 a = vec3(randf(), randf(), 0.f) * c_2pi;
			const vec3 s = vec3(randf()) * 50.f + 100.f;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
			meshes.push_back(&n);
		}

	};

	auto benchmark = [&]() {

		float time, benchmarkTime;

		// Stabilizes CPU

		//createScene(THREE.MeshStandardMaterial, 10);
		//render();
		//
		//// Standard *Node* Material
		//
		//time = app.m_gfx.m_time;;
		//
		//createScene(THREE.StandardNodeMaterial);
		//
		//render();
		//
		//benchmarkTime = (performance.now() - time) / 1000;
		//
		//document.getElementById('node').textContent = benchmarkTime.toFixed(3) + " seconds";
		//
		//// Mesh Standard *Node* Material
		//
		//time = performance.now();
		//
		//createScene(THREE.MeshStandardNodeMaterial);
		//
		//render();
		//
		//benchmarkTime = (performance.now() - time) / 1000;
		//
		//document.getElementById('nodeBased').textContent = benchmarkTime.toFixed(3) + " seconds";
		//
		//// Mesh Standard Material
		//
		//time = performance.now();
		//
		//createScene(THREE.MeshStandardMaterial);
		//
		//render();
		//
		//benchmarkTime = (performance.now() - time) / 1000;
		//
		//document.getElementById('default').textContent = benchmarkTime.toFixed(3) + " seconds";

	};


	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_frame.m_size / 2.f) * 10.f;
	}

	Camera& camera = viewer.m_camera;
	camera.m_eye.x += (mouse.x - camera.m_eye.x) * .05f;
	camera.m_eye.y += (-mouse.y - camera.m_eye.y) * .05f;
	
	//camera.lookAt(scene.position);
}
