//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_geolines(Shell app, Widget parent, Dockbar dockbar)
{
	var segments = 10000;

	var viewer = two.ui.scene_viewer(app.ui.begin());
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	//this.program = app.gfx.programs.fetch('line');
	this.program = app.gfx.programs.fetch('solid');

	this.material = app.gfx.materials.create('lines', [](var m) {
		m.program = program;
		m.base.geometry_filter = uint32_t(1 << uint(PrimitiveType::LineStrip)); // @todo this should not be necessary: in the program ?
		m.base.shader_color = ShaderColor::Vertex;
	});

	this.node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 27.0; camera.near = 1.0; camera.far = 4000.0;
		camera.eye.z = 2750.0;

		MeshPacker geometry;
		geometry.primitive = PrimitiveType::LineStrip;

		var r = 800.0;

		for(var i = 0; i < segments; i++)
		{
			var p = new two.vec3(Math.random(), Math.random(), Math.random()) * r - r / 2.0;
			Colour c = to_colour(p / r + 0.5);

			geometry.positions.push(p);
			geometry.colours.push(c);
		}

		var model = app.gfx.create_model('lines', geometry);

		var n = scene.nodes().add(new two.Node3());
		var it = scene.items().add(new two.Item(n, model, 0, material));
		node = n;
	}

	var time = app.gfx.time / 2.0; // * 0.001;

	var angles = new two.vec3(time * 0.25, time * 0.5, 0.0);
	node.apply(new two.vec3(1.0), new two.quat(angles), new two.vec3(0.0));
}
