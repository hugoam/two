#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>

#include <stl/vector.hpp>

using namespace two;

EX(xx_interact_cubes_gpu)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

#if UI
	TrackballController& controls = ui::trackball_controller(viewer);
	controls.m_staticMoving = true;
	controls.m_dynamicDampingFactor = 0.3f;
#endif

	struct Object { vec3 position; quat rotation; vec3 scale; };
	vector<Object> objects = {};
	
	//Texture* pickingTexture;
	//Scene* pickingScene;
	//var highlightBox;

	//var mouse = new THREE.Vector2();
	//var offset = new THREE.Vector3(10, 10, 10);
	
	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye.z = 1000.f;
		
		//var defaultMaterial = new THREE.MeshPhongMaterial({ color: 0xffffff, flatShading : true, vertexColors : THREE.VertexColors, shininess : 0 });
		Material& material = app.m_gfx.materials().create("cubes",  [&](Material& m) {
			m.m_program = &pbr;
			m.m_base.m_flat_shaded = true;
			m.m_base.m_shader_color = ShaderColor::Vertex;
			m.m_pbr.m_albedo = rgb(0xffffff);
			m.m_pbr.m_roughness = 1.f;
			// flatShading = true;
			// shininess : 0
		});

		//scene.background = new THREE.Color(0xffffff);

		//pickingScene = new THREE.Scene();
		//pickingTexture = new THREE.WebGLRenderTarget(1, 1);

		//scene.add(new THREE.AmbientLight(0x555555));

		Node3& l = gfx::nodes(scene).add(Node3(vec3(0.f, 500.f, 2000.f)));
		Light& light = gfx::lights(scene).add(Light(l, LightType::Spot, false, rgb(0xffffff), 1.5f));

		//var pickingMaterial = new THREE.MeshBasicMaterial({ vertexColors: THREE.VertexColors });

		//var geometriesDrawn = [];
		//var geometriesPicking = [];
		//
		//var matrix = new THREE.Matrix4();
		//var quaternion = new THREE.Quaternion();
		//var color = new THREE.Color();

		//vector<MeshPacker

		for(uint32_t i = 0; i < 5000; i++)
		{
			vec3 p = vec3(randf() * 10.f - 5.f, randf() * 6.f - 3.f, randf() * 8.f - 4.f) * 1000.f;
			vec3 a = vec3(randf(), randf(), randf()) * c_2pi;
			vec3 s = vec3(randf(), randf(), randf()) * 200.f + 100.f;

			MeshPacker geometry;
			//var geometry = new THREE.BoxBufferGeometry();

			auto paint = [](MeshPacker& geometry, const Colour& color)
			{
				for(size_t i = 0; i < geometry.m_positions.size(); ++i)
					geometry.m_colours.push_back(color);
			};

			paint(geometry, rgb(randi() * 0xffffff));
			//geometry.pack_vertices(MeshAdapter(), bxTRS(s, quat(a), p));
			//geometriesDrawn.push(geometry);

			//geometry = geometry.clone();

			paint(geometry, rgb(i));
			//geometry.pack_vertices(MeshAdapter(), bxTRS(s, quat(a), p));
			//geometriesPicking.push(geometry);

			objects[i] = { p, quat(a), s };
		}

		//var objects = new THREE.Mesh(THREE.BufferGeometryUtils.mergeBufferGeometries(geometriesDrawn), defaultMaterial);
		//scene.add(objects);
		//
		//pickingScene.add(new THREE.Mesh(THREE.BufferGeometryUtils.mergeBufferGeometries(geometriesPicking), pickingMaterial));
		//
		//highlightBox = new THREE.Mesh(
		//	new THREE.BoxBufferGeometry(),
		//	new THREE.MeshLambertMaterial({ color: 0xffff00 }
		//));
		//scene.add(highlightBox);
	}

	//function onMouseMove(e) {
	//
	//	mouse.x = e.clientX;
	//	mouse.y = e.clientY;
	//
	//}

	auto pick = []() {

		//render the picking scene off-screen

		// set the view offset to represent just a single pixel under the mouse
		//camera.setViewOffset(renderer.domElement.width, renderer.domElement.height, mouse.x * window.devicePixelRatio | 0, mouse.y * window.devicePixelRatio | 0, 1, 1);
		//
		//// render the scene
		//renderer.render(pickingScene, camera, pickingTexture);
		//
		//// clear the view offset so rendering returns to normal
		//camera.clearViewOffset();
		//
		////create buffer for reading single pixel
		//var pixelBuffer = new Uint8Array(4);
		//
		////read the pixel
		//renderer.readRenderTargetPixels(pickingTexture, 0, 0, 1, 1, pixelBuffer);
		//
		////interpret the pixel as an ID
		//var id = (pixelBuffer[0] << 16) | (pixelBuffer[1] << 8) | (pixelBuffer[2]);
		//var data = pickingData[id];
		//
		//if(data)
		//{
		//	//move our highlightBox so that it surrounds the picked object
		//	if(data.position && data.rotation && data.scale) {
		//		highlightBox.position.copy(data.position);
		//		highlightBox.rotation.copy(data.rotation);
		//		highlightBox.scale.copy(data.scale).add(offset);
		//		highlightBox.visible = true;
		//	}
		//
		//}
		//else {
		//	highlightBox.visible = false;
		//}
	};

	pick();
}
