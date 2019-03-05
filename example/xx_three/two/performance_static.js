//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_performance_static(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(parent);
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

#if 0
	var container, stats;

	var camera, scene, renderer;

	var mouseX = 0, mouseY = 0;

	var windowHalfX = window.innerWidth / 2;
	var windowHalfY = window.innerHeight / 2;

	document.addEventListener('mousemove', onDocumentMouseMove, false);

	init();
	animate();


	function init() {

		container = document.createElement('div');
		document.body.appendChild(container);

		camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 1, 10000);
		camera.position.z = 3200;

		scene = new THREE.Scene();
		scene.background = new THREE.Color(0xffffff);

		var material = new THREE.MeshNormalMaterial();

		var loader = new THREE.BufferGeometryLoader();
		loader.load('models/json/suzanne_buffergeometry.json', function(geometry) {

			geometry.computeVertexNormals();

			for(var i = 0; i < 7700; i++) {

				var mesh = new THREE.Mesh(geometry, material);

				mesh.position.x = random() * 10000 - 5000;
				mesh.position.y = random() * 10000 - 5000;
				mesh.position.z = random() * 10000 - 5000;
				mesh.rotation.x = random() * 2 * PI;
				mesh.rotation.y = random() * 2 * PI;
				mesh.scale.x = mesh.scale.y = mesh.scale.z = random() * 50 + 100;
				mesh.matrixAutoUpdate = false;
				mesh.updateMatrix();

				scene.add(mesh);

			}

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