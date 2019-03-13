//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

//	import './js/nodes/THREE.Nodes.js';

void xx_performance_nodes(Shell app, var parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(panel);
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

#if 0
	var container, stats;

	var camera, scene, renderer;

	var geometry;
	var meshes = [];

	var mouseX = 0, mouseY = 0;

	var windowHalfX = window.innerWidth / 2;
	var windowHalfY = window.innerHeight / 2;

	document.addEventListener('mousemove', onDocumentMouseMove, false);

	init();
	animate();

	function createScene(MaterialClass, count) {

		count = count != = undefined ? count : 70;

		var i = 0;

		for(i = 0; i < meshes.length; i++) {

			meshes[i].material.dispose();

			scene.remove(meshes[i]);

		}

		meshes = [];

		for(i = 0; i < count; i++) {

			var material = new MaterialClass(),
				color = 0xFFFFFF * random();

			if(material.color.isNode) material.color.value.setHex(color);
			else material.color.setHex(color);

			// prevent share code
			material.defines.UUID = material.uuid;

			var mesh = new THREE.Mesh(geometry, material);

			mesh.position.x = random() * 1000 - 500;
			mesh.position.y = random() * 1000 - 500;
			mesh.position.z = random() * 1000 - 500;
			mesh.rotation.x = random() * 2 * PI;
			mesh.rotation.y = random() * 2 * PI;
			mesh.scale.x = mesh.scale.y = mesh.scale.z = random() * 50 + 100;
			mesh.matrixAutoUpdate = false;
			mesh.updateMatrix();

			scene.add(mesh);

			meshes.push(mesh);

		}

	}

	function benchmark() {

		var time, benchmarkTime;

		// Stabilizes CPU

		createScene(THREE.MeshStandardMaterial, 10);

		render();

		// Standard *Node* Material

		time = performance.now();

		createScene(THREE.StandardNodeMaterial);

		render();

		benchmarkTime = (performance.now() - time) / 1000;

		document.getElementById('node').textContent = benchmarkTime.toFixed(3) + ' seconds';

		// Mesh Standard *Node* Material

		time = performance.now();

		createScene(THREE.MeshStandardNodeMaterial);

		render();

		benchmarkTime = (performance.now() - time) / 1000;

		document.getElementById('nodeBased').textContent = benchmarkTime.toFixed(3) + ' seconds';

		// Mesh Standard Material

		time = performance.now();

		createScene(THREE.MeshStandardMaterial);

		render();

		benchmarkTime = (performance.now() - time) / 1000;

		document.getElementById('default').textContent = benchmarkTime.toFixed(3) + ' seconds';

	}

	document.getElementById('bench').addEventListener('click', function() {

		if(geometry) {

			benchmark();

		}

	});

	function init() {

		container = document.createElement('div');
		document.body.appendChild(container);

		camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 1, 10000);
		camera.position.z = 3200;

		scene = new THREE.Scene();
		scene.add(new THREE.PointLight(0xFFFFFF));
		//scene.background = new THREE.Color(0xffffff);

		var loader = new THREE.BufferGeometryLoader();
		loader.load('models/json/suzanne_buffergeometry.json', function(geo) {

			geo.computeVertexNormals();

			geometry = geo;

		});

		renderer = new THREE.WebGLRenderer();
		renderer.setPixelRatio(window.devicePixelRatio);
		renderer.setSize(window.innerWidth, window.innerHeight);
		//renderer.sortObjects = false;

		container.appendChild(renderer.domElement);

		stats = new Stats();
		container.appendChild(stats.dom);

		//

		window.addEventListener('resize', onWindowResize, false);

	}

	function onWindowResize() {

		windowHalfX = window.innerWidth / 2;
		windowHalfY = window.innerHeight / 2;

		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();

		renderer.setSize(window.innerWidth, window.innerHeight);

	}

	function onDocumentMouseMove(event) {

		mouseX = (event.clientX - windowHalfX) * 10;
		mouseY = (event.clientY - windowHalfY) * 10;

	}

	//

	function animate() {

		requestAnimationFrame(animate);

		render();
		stats.update();

	}

	function render() {

		camera.position.x += (mouseX - camera.position.x) * .05;
		camera.position.y += (-mouseY - camera.position.y) * .05;

		camera.lookAt(scene.position);

		renderer.render(scene, camera);

	}
#endif
}
