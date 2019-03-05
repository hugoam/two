//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_geopoints_packed(Shell app, Widget parent, Dockbar dockbar)
{
	UNUSED(dockbar);
	var particles = 500000;

	var viewer = two.ui.scene_viewer(parent);
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	this.program = app.gfx.programs().fetch('solid');

	this.material = app.gfx.materials().create('points', [](var m) {
		m.program = program;
		m.base.geometry_filter = uint32_t(1 << uint(PrimitiveType::Points)); // @todo this should not be necessary: in the program ?
		m.base.shader_color = ShaderColor::Vertex;
		m.point.point_size = 15.0;
	});

	this.node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 27.0; camera.near = 5.0; camera.far = 3500.0;
		camera.eye.z = 2750.0;

		//scene.background = new THREE.Color(0x050505);
		//scene.fog = new THREE.Fog(0x050505, 2000, 3500);

		GpuMesh gpu_mesh = alloc_mesh(PrimitiveType::Points, VertexAttribute::Position | VertexAttribute::Colour, particles, 0);
		
		var s = 1000.0; var s2 = s / 2.0; // particles spread in the cube

		for(var i = 0; i < particles; i++)
		{
			var p = new two.vec3(Math.random(), Math.random(), Math.random()) * s - s2;
			Colour c = to_colour(p / s + 0.5);

			// 12 bytes = float3 position (xyz)
			// 4 bytes = uint32 color (rgba)

			gpu_mesh.writer.position(p);
			gpu_mesh.writer.colour(c);
		}

		gpu_mesh.writer.bound();

		var model = app.gfx.create_model('points', gpu_mesh);

		var n = two.gfx.nodes(scene).add(new two.Node3());
		var it = two.gfx.items(scene).add(new two.Item(n, model, 0U, material));
		node = n;
	}

	var time = app.gfx.time / 2.0;

	var angles = new two.vec3(time * 0.25, time * 0.5, 0.0);
	node->transform = bxTRS(new two.vec3(1.0), new two.quat(angles), new two.vec3(0.0));

}