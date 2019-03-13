//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_interact_cubes_gpu(Shell app, var parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(panel);
	TrackballController controls = two.ui.trackball_controller(viewer);

	controls.staticMoving = true;
	controls.dynamicDampingFactor = 0.3;

	var scene = viewer.scene;

	struct Object { var position; quat rotation; var scale; };
	vector<Object> objects = {};
	
	//Texture* pickingTexture;
	//Scene* pickingScene;
	//var highlightBox;

	//var mouse = new THREE.Vector2();
	//var offset = new THREE.Vector3(10, 10, 10);
	
	this.pbr = app.gfx.programs.file('pbr/pbr');

	//var defaultvar = new THREE.MeshPhongMaterial({ color: 0xffffff, flatShading : true, vertexColors : THREE.VertexColors, shininess : 0 });
	this.material = app.gfx.materials.create('material',  [](var m) {
		m.program = pbr;
		m.base.shader_color = ShaderColor::Vertex;
		m.pbr.albedo = two.rgb(0xffffff);
		m.pbr.roughness = 1.0;
		// flatShading = true;
		// shininess : 0
	});

	bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 70.0; camera.near = 1.0; camera.far = 10000.0;
		camera.eye.z = 1000.0;

		//scene.background = new THREE.Color(0xffffff);

		//pickingScene = new THREE.Scene();
		//pickingTexture = new THREE.WebGLRenderTarget(1, 1);

		//scene.add(new THREE.AmbientLight(0x555555));

		var l = scene.nodes().add(new two.Node3(new two.vec3(0.0, 500.0, 2000.0)));
		var light = scene.lights().add(new two.Light(l, two.LightType.Spot, false, two.rgb(0xffffff), 1.5));

		//var pickingvar = new THREE.MeshBasicMaterial({ vertexColors: THREE.VertexColors });

		//var geometriesDrawn = [];
		//var geometriesPicking = [];
		//
		//var matrix = new THREE.Matrix4();
		//var quaternion = new THREE.Quaternion();
		//var color = new THREE.Color();

		//vector<MeshPacker

		for(var i = 0; i < 5000; i++)
		{
			var p = new two.vec3(Math.random() * 10.0 - 5.0, Math.random() * 6.0 - 3.0, Math.random() * 8.0 - 4.0) * 1000.0;
			var a = new two.vec3(Math.random(), Math.random(), Math.random()) * 2.0 * Math.PI;
			var s = new two.vec3(Math.random(), Math.random(), Math.random()) * 200.0 + 100.0;

			MeshPacker geometry;
			//var geometry = new THREE.BoxBufferGeometry();

			function pavar = [](MeshPacker geometry, var color)
			{
				for(var i = 0; i < geometry.positions.length; ++i)
					geometry.colours.push(color);
			};

			paint(geometry, two.rgba(Math.random() * 0xffffff));
			geometry.pack_vertices(MeshAdapter(), bxTRS(s, new two.quat(a), p));
			//geometriesDrawn.push(geometry);

			//geometry = geometry.clone();

			paint(geometry, two.rgba(i));
			geometry.pack_vertices(MeshAdapter(), bxTRS(s, new two.quat(a), p));
			//geometriesPicking.push(geometry);

			objects[i] = { p, new two.quat(a), s };
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

	function pick = []() {

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
		//	if(data.position  data.rotation  data.scale) {
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
