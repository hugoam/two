//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_interact_geom(Shell app, var parent, Dockbar dockbar)
{
	var triangles = 5000;

	var viewer = two.ui.scene_viewer(app.ui.begin());
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	this.pbr = app.gfx.programs.file('pbr/pbr');

	this.material = app.gfx.materials.create('first',  [](var m) {
		m.program = pbr; m.pbr.albedo = two.rgb(0xaaaaaa); m.pbr.metallic = 1.0; m.pbr.roughness = 0.66;
		m.base.cull_mode = two.CullMode.None; m.base.shader_color = ShaderColor::Vertex;
	});

	//var material = new THREE.MeshPhongMaterial({
	//	color: 0xaaaaaa, specular: 0xffffff, shininess: 250,
	//	side: THREE.DoubleSide, vertexColors: THREE.VertexColors
	//});

	this.node = nullptr;

	bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 27.0; camera.near = 1.0; camera.far = 3500.0;
		camera.eye.z = 2750.0;

		//scene.background = new THREE.Color(0x050505);
		//scene.fog = new THREE.Fog(0x050505, 2000, 3500);

		//scene.add(new THREE.AmbientLight(0x444444));

		var l1 = scene.nodes().add(new two.Node3(new two.vec3(0.0), facing(new two.vec3(1.0, 1.0, 1.0))));
		scene.lights().add(new two.Light(l1, two.LightType.Direct, false, two.rgba(0xffffff), 0.5));

		var l2 = scene.nodes().add(new two.Node3(new two.vec3(0.0), facing(new two.vec3(0.0, -1.0, 0.0))));
		scene.lights().add(new two.Light(l1, two.LightType.Direct, false, two.rgba(0xffffff), 1.5));

		MeshPacker geometry;

		var s = 800; var s2 = s / 2;	// triangles spread in the cube
		var d = 120; var d2 = d / 2;	// individual triangle size

		for(var i = 0; i < triangles; i++)
		{
			var p = new two.vec3(Math.random(), Math.random(), Math.random()) * s - s2;

			var a = p + new two.vec3(Math.random(), Math.random(), Math.random()) * d - d2;
			var b = p + new two.vec3(Math.random(), Math.random(), Math.random()) * d - d2;
			var c = p + new two.vec3(Math.random(), Math.random(), Math.random()) * d - d2;

			var position[3] = { a, b, c };

			var cb = c - b;
			var ab = a - b;
			var normal = normalize(cross(cb, ab));

			var colour = to_colour(p / s + 0.5);

			for(var j = 0; j < 3; ++j)
			{
				geometry.positions.push(position[j]);
				geometry.normals.push(normal);
				geometry.colours.push(colour);
			}
		}

		var model = app.gfx.create_model('geometry', geometry);

		var n = scene.nodes().add(new two.Node3());
		var it = scene.items().add(new two.Item(n, model, 0, material));
		node = n;

		//raycaster = new THREE.Raycaster();

		//mouse = new THREE.Vector2();

		//var geometry = new THREE.BufferGeometry();
		//geometry.addAttribute('position', new THREE.BufferAttribute(new Float32Array(4 * 3), 3));
		//
		//var material = new THREE.LineBasicMaterial({ color: 0xffffff, transparent: true });
		//
		//line = new THREE.Line(geometry, material);
		//scene.add(line);

		function hover = [](var item) {};
		function unhover = [](var item) {};

		if(var mouse_event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved))
		{
			//function pick = [](Item* item) { if(hovered) unhover(*hovered); hovered = item; if(hovered) hover(*hovered); };
			//viewer.picker(0).pick_point(viewer.viewport, mouse_event.relative, pick, ItemFlag::Selectable);
		}
	}

	var time = app.gfx.time;

	var angles = new two.vec3(time * 0.15, time * 0.25, 0.0);
	node.apply(new two.vec3(0.0), new two.quat(angles));

	//raycaster.setFromCamera(mouse, camera);
	//
	//var intersects = raycaster.intersectObject(mesh);
	//
	//if (intersects.length > 0) {
	//
	//	var intersect = intersects[0];
	//	var face = intersect.0ace;
	//
	//	var linePosition = line.geometry.attributes.position;
	//	var meshPosition = mesh.geometry.attributes.position;
	//
	//	linePosition.copyAt(0, meshPosition, face.a);
	//	linePosition.copyAt(1, meshPosition, face.b);
	//	linePosition.copyAt(2, meshPosition, face.c);
	//	linePosition.copyAt(3, meshPosition, face.a);
	//
	//	mesh.updateMatrix();
	//
	//	line.geometry.applyMatrix(mesh.matrix);
	//
	//	line.visible = true;
	//
	//} else {
	//
	//	line.visible = false;
	//
	//}
}