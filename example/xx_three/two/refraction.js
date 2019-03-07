//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_refraction(Shell app, var parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(app.ui.begin());
	//two.ui.orbit_controller(viewer);

	this.pbr = app.gfx.programs.file('pbr/pbr');

	this.refraction = app.gfx.textures.file('Park3Med.jpg.cube');
	//textureCube.mapping = THREE.CubeRefractionMapping;

	var scene = viewer.scene;

	this.light = nullptr;

	bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 50.0; camera.near = 1.0; camera.far = 100000.0;
		camera.eye.z = -4000.0;

		scene.env.radiance.texture = refraction;

		//var ambient = new THREE.AmbientLight(0xffffff);

		var sphere = app.gfx.shape(new two.Sphere(100.0 * 0.05));

		var ln = scene.nodes().add(new two.Node3());
		scene.lights().add(new two.Light(ln, LightType::Point, false, rgb(0xffffff), 2.0));
		scene.items().add(new two.Item(ln, sphere, 0, two.gfx.solid_material(app.gfx, 'light', rgb(0xffffff))));
		light = ln;

		// material samples

		function phong_material = [](var name, var colour, var refraction, var reflectivity = 0.0) -> Material
		{
			return app.gfx.materials.create(name, [](var m) {
				m.program = pbr;
				m.pbr.specular_mode = PbrSpecularMode::Phong;
				m.pbr.refraction = refraction;
				//m.pbr.reflectivity = reflectivity;
			});
		};

		var m3 = phong_material('material0', rgb(0xccddff), 0.98, 0.9);
		var m2 = phong_material('material1', rgb(0xccfffd), 0.985);
		var m1 = phong_material('material2', rgb(0xffffff), 0.98);

		//var loader = new THREE.PLYLoader();
		var model = app.gfx.models.file('Lucy100k.ply');
		//geometry.computeVertexNormals();

		var s = 1.5;

		var n0 = scene.nodes().add(new two.Node3(new two.vec3(0.0, 0.0, 0.0), ZeroQuat, new two.vec3(s)));
		scene.items().add(new two.Item(n0, model, 0, m1));

		var n1 = scene.nodes().add(new two.Node3(new two.vec3(-1500.0, 0.0, 0.0), ZeroQuat, new two.vec3(s)));
		scene.items().add(new two.Item(n1, model, 0, m2));

		var n2 = scene.nodes().add(new two.Node3(new two.vec3(1500.0, 0.0, 0.0), ZeroQuat, new two.vec3(s)));
		scene.items().add(new two.Item(n2, model, 0, m3));
	}

	this.mouse = new two.vec2(0.0);
	if(var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved))
	{
		mouse = (event.relative - viewer.frame.size / 2.0) * 4.0;
	}
	
	var timer = app.gfx.time * -0.0002;

	var camera = viewer.camera;
	camera.eye.x += (mouse.x - camera.eye.x) * .05;
	camera.eye.y += (-mouse.y - camera.eye.y) * .05;

	//camera.lookAt(scene.position);

	var position = new two.vec3(Math.cos(timer), Math.sin(timer), 0.0) * 1500.0;
	light.apply(new two.vec3(1.0), ZeroQuat, position);
}