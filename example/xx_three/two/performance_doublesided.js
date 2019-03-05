//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_performance_doublesided(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(parent);
	//two.ui.orbit_controller(viewer);

	var camera = viewer.camera;
	var scene = viewer.scene;

	Texture reflection = app.gfx.textures().file('SwedishRoyalCastle.cube');

	this.pbr = app.gfx.programs().file('pbr/pbr');

	//var material = new THREE.MeshPhongMaterial({ specular: 0x101010, shininess : 100, envMap : reflectionCube, combine : THREE.MixOperation, reflectivity : 0.1, side : THREE.DoubleSide });
	this.material = app.gfx.materials().create('material',  [](var m) {
		m.program = pbr; //m.pbr.albedo = rgb(0xaaaaaa); m.pbr.metallic = 1.0; m.pbr.roughness = 0.66f;
		m.base.cull_mode = two.CullMode.None;
	});

	static bool once = false;
	if(!once)
	{
		once = true;

		camera.fov = 50.0; camera.near = 1.0; camera.far = 20000.0;
		camera.eye.z = 3200.0;

		//scene.background = new THREE.Color(0x050505);

		//scene.add(new THREE.AmbientLight(0x050505));

		var l0 = two.gfx.nodes(scene).add(new two.Node3(new two.vec3(4000.0, 0.0, 0.0)));
		two.gfx.lights(scene).add(Light(l0, LightType::Point, false, rgb(0x0011f), 1.0, 5500.0));

		var l1 = two.gfx.nodes(scene).add(new two.Node3(new two.vec3(-4000.0, 0.0, 0.0)));
		two.gfx.lights(scene).add(Light(l1, LightType::Point, false, rgb(0xff1100), 1.0, 5500.0));

		var l2 = two.gfx.nodes(scene).add(new two.Node3(new two.vec3(0.0)));
		two.gfx.lights(scene).add(Light(l2, LightType::Point, false, rgb(0xffaa00), 2.0, 3000.0));

		var geometry = app.gfx.shape(new two.Sphere());
		//new THREE.SphereBufferGeometry(1, 32, 16, 0, PI);

		for(var i = 0; i < 5000; ++i)
		{
			var p = new two.vec3(Math.random(), Math.random(), Math.random()) * 10000.0 - 5000.0;
			var a = new two.vec3(Math.random(), Math.random(), 0.0) * 2 * Math.PI;
			var s = new two.vec3(Math.random()) * 50.0 + 100.0;

			var n = two.gfx.nodes(scene).add(new two.Node3(p, new two.quat(a), s));
			two.gfx.items(scene).add(new two.Item(n, geometry, 0U, material));
		}
	}

	if(var mouse_event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved))
	{
		var coord = mouse_event.relative;
		camera.eye.x += (coord.x - camera.eye.x) * 0.05;
		camera.eye.y += (-coord.y - camera.eye.y) * 0.05;
	}
}