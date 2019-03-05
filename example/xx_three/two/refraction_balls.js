//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_refraction_balls(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(app.ui.begin());
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	this.refraction = app.gfx.textures.file('Park3Med.jpg.cube');

	static vector<Node3*> spheres;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 60.0; camera.near = 1.0; camera.far = 100000.0;
		camera.eye.z = 3200.0;

		var sphere = app.gfx.shape(new two.Sphere(100.0));

		var material = two.gfx.pbr_material(app.gfx, 'material', rgb(0xffffff));
		material.pbr.refraction = 0.95;
		//material.envMap.mapping = THREE.CubeRefractionMapping;

		for(var i = 0; i < 500; i++)
		{
			var p = new two.vec3(Math.random(), Math.random(), Math.random()) * 10000.0 - 5000.0;
			var s = new two.vec3(Math.random()) * 3.0 + 1.0;
			var n = scene.nodes().add(new two.Node3(p, ZeroQuat, s));
			scene.items().add(new two.Item(n, sphere, 0, material));

			spheres.push(n);
		}
	}

	this.mouse = new two.vec2(0.0);
	if(var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved))
	{
		mouse = (event.relative - viewer.frame.size / 2.0) * 10.0;
	}//

	var timer = app.gfx.time * -0.0001;
	
	for(var i = 0; i < spheres.length; i++)
	{
		var p = new two.vec3(Math.cos(timer + float(i)), Math.sin(timer + float(i) * 1.1), 0.0) * 5000.0;
		spheres[i].apply(new two.vec3(1.0), ZeroQuat, p);
	}

	var camera = viewer.camera;
	camera.eye.x += (mouse.x - camera.eye.x) * .05;
	camera.eye.y += (-mouse.y - camera.eye.y) * .05;

	//camera.lookAt(scene.position);
}