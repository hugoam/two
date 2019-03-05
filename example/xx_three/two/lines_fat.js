//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/array.h>
#include <stl/vector.hpp>

#include <cstdio>
#include <cstring>

using namespace mud;

struct Lines // LineSegmentsGeometry
{
	//var plane = new THREE.BufferGeometry();
	Lines(GfxSystem gfx)
	{
		MeshPacker geometry;

		geometry.positions = { new two.vec3(-1, 2, 0), new two.vec3(1, 2, 0), new two.vec3(-1, 1, 0), new two.vec3(1, 1, 0), new two.vec3(-1, 0, 0), new two.vec3(1, 0, 0), new two.vec3(-1, -1, 0), new two.vec3(1, -1, 0) };
		geometry.uv0s = { new two.vec2(-1, 2), new two.vec2(1, 2), new two.vec2(-1, 1), new two.vec2(1, 1), new two.vec2(-1, -1), new two.vec2(1, -1), new two.vec2(-1, -2), new two.vec2(1, -2) };
		geometry.indices = { 0, 2, 1, 2, 3, 1, 2, 4, 3, 4, 5, 3, 4, 6, 5, 6, 7, 5 };

		model = gfx.create_model('lines', geometry);
	}

	Model* model = nullptr;

	struct Segment { var start; var start_distance; var end; var end_distance; Colour start_colour; Colour end_colour; };
	vector<Segment> segments;

	Aabb aabb;
	var radius;

	void compute_distances()
	{
		for(var i = 0; i < segments.length; ++i)
		{
			Segment seg = segments[i];
			seg.start_distance = i > 0 ? segments[i-1].end_distance : 0.0;
			seg.end_distance = seg.start_distance + distance(seg.start, seg.end);
		}
	}

	void update_aabb()
	{ 
		aabb = {};

		for(Segment seg : segments)
		{
			aabb.merge(seg.start);
			aabb.merge(seg.end);
		}
	}

	void update_sphere()
	{
		var center = aabb.center;
		var radius2 = 0.0;

		for(Segment seg : segments)
		{
			radius2 = max(radius2, distance2(center, seg.start));
			radius2 = max(radius2, distance2(center, seg.end));
		}

		radius = Math.sqrt(radius2);
	}
};


void xx_lines_fat(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(app.ui.begin());
	two.ui.orbit_controller(viewer);
	//controls.minDistance = 10;
	//controls.maxDistance = 500;

	var scene = viewer.scene;

	//camera2 = new THREE.PerspectiveCamera(40, 1, 1, 1000);
	//camera2.position.copy(camera.position);
	
	this.program = app.gfx.programs.fetch('line');

	this.material = app.gfx.materials.create('line', [](var m) {
		m.program = program;
		m.solid.colour = rgb(0xffffff);
		m.line.line_width = 5.0;
		m.line.dashed = true;
		m.base.shader_color = ShaderColor::Vertex;
	});

	this.batch = nullptr;
	static vector<Lines::Segment> segments;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 40.0; camera.near = 1.0; camera.far = 1000.0;
		camera.eye = new two.vec3(-40.0, 0.0, 60.0);

		Lines lines = Lines(app.gfx);

		vector<vec3> points = hilbert3d(new two.vec3(0.0), 20.0, 1);

		CurveCatmullRom3 curve = { points };
		uint32_t divisions = round(12 * points.length);
		var l = float(divisions);

		for(int i = 0; i < divisions - 1; i++)
		{
			var start = curve.point(float(i+0) / l);
			var end   = curve.point(float(i+1) / l);

			Colour color_start = two.hsl(float(i+0) / l, 1.0, 0.5);
			Colour color_end   = two.hsl(float(i+1) / l, 1.0, 0.5);

			lines.segments.push({ start, 0.0, end, 0.0, color_start, color_end });
		}

		lines.compute_distances();

		segments = lines.segments;

		var n = scene.nodes().add(new two.Node3());
		var it = scene.items().add(new two.Item(n, *lines.model, 0, material));
		batch = two.gfx.batches(scene).add(new two.Batch(it));
		it.batch = batch;

		//line = new THREE.Line2(geometry, matLine);
		//line.computeLineDistances();
		//line.scale.set(1, 1, 1);
		//scene.add(line);


		// THREE.Line (BufferGeometry, LineBasicMaterial) - rendered with gl.LINE_STRIP

		/*var geo = new THREE.BufferGeometry();
		geo.addAttribute('position', new THREE.Float32BufferAttribute(positions, 3));
		geo.addAttribute('color', new THREE.Float32BufferAttribute(colors, 3));

		matLineBasic = new THREE.LineBasicMaterial({ vertexColors: THREE.VertexColors });
		matLineDashed = new THREE.LineDashedMaterial({ vertexColors: THREE.VertexColors, scale: 2, dashSize: 1, gapSize: 1 });

		line1 = new THREE.Line(geo, matLineBasic);
		line1.computeLineDistances();
		line1.visible = false;
		scene.add(line1);

		initGui();*/
	}

	Gnode root = scene.begin();

	this.pbr = app.gfx.programs.file('pbr/pbr');

	this.testmat = app.gfx.materials.create('test', [](var m) {
		m.program = pbr; m.pbr.albedo = two.rgb(0x888888); m.pbr.metallic = 1.0; m.pbr.roughness = 0.66;
	});

	two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', BackgroundMode::Radiance);

	two.gfx.shape(root, new two.Sphere(), new two.Symbol(), 0, testmat);

	span<float> memory = batch->begin(segments.length, sizeof(Lines::Segment));
	memcpy(memory.data(), segments.data(), memory.length * sizeof(float));

	if(Widget* dock = two.ui.dockitem(dockbar, 'Game', { 1U }))
	{
		Widget sheet = two.ui.columns(*dock, { 0.3, 0.7 });

		two.ui.slider_field<float>(sheet, 'line width', { material.line.line_width, { 0.0, 20.0, 0.1 } });

		two.ui.input_field<bool>(sheet, 'dased', material.line.dashed);
		two.ui.slider_field<float>(sheet, 'dash scale', { material.line.dash_scale, { 0.0, 20.0, 0.1 } });
		two.ui.slider_field<float>(sheet, 'dash size', { material.line.dash_size,  { 0.0, 20.0, 0.1 } });
		two.ui.slider_field<float>(sheet, 'dash gap', { material.line.dash_gap,   { 0.0, 20.0, 0.1 } });
	}
}
			