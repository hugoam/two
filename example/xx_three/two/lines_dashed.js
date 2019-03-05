//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

var cube_model(GfxSystem gfx, var size)
{
	var h = size * 0.5;

	MeshPacker geometry;
	geometry.primitive = PrimitiveType::Lines;

	geometry.positions = {
		new two.vec3(-h, -h, -h), new two.vec3(-h,  h, -h),
		new two.vec3(-h,  h, -h), new two.vec3( h,  h, -h),
		new two.vec3( h,  h, -h), new two.vec3( h, -h, -h),
		new two.vec3( h, -h, -h), new two.vec3(-h, -h, -h),
		new two.vec3(-h, -h,  h), new two.vec3(-h,  h,  h),
		new two.vec3(-h,  h,  h), new two.vec3( h,  h,  h),
		new two.vec3( h,  h,  h), new two.vec3( h, -h,  h),
		new two.vec3( h, -h,  h), new two.vec3(-h, -h,  h),
		new two.vec3(-h, -h, -h), new two.vec3(-h, -h,  h),
		new two.vec3(-h,  h, -h), new two.vec3(-h,  h,  h),
		new two.vec3( h,  h, -h), new two.vec3( h,  h,  h),
		new two.vec3( h, -h, -h), new two.vec3( h, -h,  h)
	};

	return gfx.create_model('cube', geometry);
}

void xx_lines_dashed(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(parent);
	two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	this.program = app.gfx.programs().fetch('line');

	this.node0 = nullptr;
	this.node1 = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 60.0; camera.near = 1.0; camera.far = 200.0;
		camera.eye.z = 150.0;

		//scene.background = new THREE.Color(0x111111);
		//scene.fog = new THREE.Fog(0x111111, 150, 200);

		var subdivisions = 6;
		var recursion = 1;

		vector<vec3> points = hilbert3d(new two.vec3(0.0), 25.0, recursion);
		CurveCatmullRom3 curve = { points };

		vector<vec3> samples = curve.points(points.size() * subdivisions);

		MeshPacker geometry;
		geometry.primitive = PrimitiveType::Lines;
		geometry.positions = samples;

		var spline = app.gfx.create_model('spline', geometry);

		function dash_material = [](Colour colour, var dash_size, var dash_gap)
		{
			return app.gfx.materials().create('line', [](var m) {
				m.program = program;
				m.solid.colour = colour;
				m.line.dashed = true;
				m.line.dash_size = dash_size;
				m.line.dash_gap = dash_gap;
				m.base.shader_color = ShaderColor::Vertex;
			});
		};

		var mat0 = dash_material(rgb(0xffffff), 1.0, 0.5);
		var n0 = two.gfx.nodes(scene).add(new two.Node3());
		two.gfx.items(scene).add(new two.Item(n0, spline, 0U, mat0));
		//line.computeLineDistances();
		node0 = n0;

		var cube = cube_model(app.gfx, 50.0);

		var mat1 = dash_material(rgb(0xffaa00), 3.0, 1.0);
		var n1 = two.gfx.nodes(scene).add(new two.Node3());
		two.gfx.items(scene).add(new two.Item(n1, cube, 0U, mat1));
		//lineSegments.computeLineDistances();
		node1 = n1;
	}

	var time = app.gfx.time;

	var angles = new two.vec3(0.25 * time, 0.25 * time, 0.0);

	for(Node3* node : { node0, node1 })
	{
		node->transform = bxTRS(new two.vec3(1.0), new two.quat(angles), new two.vec3(0.0));
	}
}
