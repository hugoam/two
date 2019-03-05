//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_loader_gltf(Shell app, Widget parent, Dockbar dockbar)
{
	static ImporterGltf importer_gltf = { app.gfx };

	var viewer = two.ui.scene_viewer(app.ui.begin());
	//two.ui.orbit_controller(viewer);

	//controls.target.set(0, -0.2, -0.2);
	//controls.update();

	var scene = viewer.scene;

	//var urls = ['posx.jpg', 'negx.jpg', 'posy.jpg', 'negy.jpg', 'posz.jpg', 'negz.jpg'];
	//var loader = new THREE.CubeTextureLoader().setPath('textures/cube/Bridge2/');
	//var background = loader.load(urls);

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 45.0; camera.near = 0.25; camera.far = 20.0;
		camera.eye = new two.vec3(-1.8, 0.9, 2.7);

		//scene.background = background;

		//light = new THREE.HemisphereLight(0xbbbbff, 0x444422);
		//light.position.set(0, 1, 0);
		//scene.add(light);

		var model = app.gfx.models.file('DamagedHelmet'); // .gltf');

		var n = scene.nodes().add(new two.Node3());
		var i = scene.items().add(new two.Item(n, model));
	}
}
