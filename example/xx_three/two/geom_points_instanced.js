//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#include <cstring>

using namespace mud;

void xx_geopoints_instanced(Shell app, Widget parent, Dockbar dockbar)
{
	var particles = 500000;

	var viewer = two.ui.scene_viewer(app.ui.begin());
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	this.program = app.gfx.programs.fetch('point');

	this.material = app.gfx.materials.create('points', [](var m) {
		m.program = program;
		m.base.geometry_filter = uint32_t(1 << uint(PrimitiveType::Triangles));
		m.base.shader_color = ShaderColor::Vertex;
		m.point.point_size = 15.0;
	});

	this.node = nullptr;

	this.batch = nullptr;
	struct Instance { var position; var pad0; var scale; var pad1; var pad2; Colour colour; };
	static vector<Instance> instances = vector<Instance>(particles);

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 27.0; camera.near = 5.0; camera.far = 3500.0;
		camera.eye.z = 2750.0;

		//scene.background = new THREE.Color(0x050505);
		//scene.fog = new THREE.Fog(0x050505, 2000, 3500);

		var s = 1000.0; var s2 = s / 2.0; // particles spread in the cube

		for(var i = 0; i < particles; i++)
		{
			var p = new two.vec3(Math.random(), Math.random(), Math.random()) * s - s2;
			Colour c = to_colour(p / s + 0.5);

			instances[i] = { p, 0.0, new two.vec2(15.0), 0.0, 0.0, c };
		}

		var model = app.gfx.models.get('point');

		var n = scene.nodes().add(new two.Node3());
		var it = scene.items().add(new two.Item(n, model, 0, material));
		node = n;

		batch = two.gfx.batches(scene).add(new two.Batch(it));
		it.batch = batch;
	}

	var time = app.gfx.time / 2.0;

	var angles = new two.vec3(time * 0.25, time * 0.5, 0.0);
	node.apply(new two.vec3(1.0), new two.quat(angles), new two.vec3(0.0));

	span<float> memory = batch->begin(instances.length, sizeof(Instance));
	memcpy(memory.data(), instances.data(), memory.length * sizeof(float));
}
