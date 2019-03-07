//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/array.h>
#include <stl/vector.hpp>

#include <cstdio>
#include <cstring>

using namespace mud;

void xx_lines_fat(Shell& app, Widget& parent, Dockbar& dockbar)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);
	//controls.minDistance = 10;
	//controls.maxDistance = 500;

	Scene& scene = viewer.m_scene;

	//camera2 = new THREE.PerspectiveCamera(40, 1, 1, 1000);
	//camera2.position.copy(camera.position);
	
	static Program& program = app.m_gfx.programs().fetch("line");

	static Material& material = app.m_gfx.materials().create("line", [&](Material& m) {
		m.m_program = &program;
		m.m_solid.m_colour = rgb(0xffffff);
		m.m_line.m_line_width = 5.f;
		m.m_line.m_dashed = true;
		m.m_base.m_shader_color = ShaderColor::Vertex;
	});

	static Batch* batch = nullptr;
	static vector<Lines::Segment> segments;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		camera.m_eye = vec3(-40.f, 0.f, 60.f);

		Lines lines = Lines(app.m_gfx);

		vector<vec3> points = hilbert3d(vec3(0.f), 20.f, 1);

		CurveCatmullRom3 curve = { points };
		uint32_t divisions = uint32_t(12U * points.size());

		float l = float(divisions);

		for(uint32_t i = 0; i < divisions - 1; i++)
		{
			vec3 start = curve.point(float(i+0) / l);
			vec3 end   = curve.point(float(i+1) / l);

			Colour color_start = hsl(float(i+0) / l, 1.f, 0.5f);
			Colour color_end   = hsl(float(i+1) / l, 1.f, 0.5f);

			lines.add(start, end, color_start, color_end);
		}

		segments = lines.m_segments;

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, *lines.m_model, 0U, &material));
		batch = &gfx::batches(scene).add(Batch(it));
		it.m_batch = batch;

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

	Gnode& root = scene.begin();

	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	static Material& testmat = app.m_gfx.materials().create("test", [&](Material& m) {
		m.m_program = &pbr; m.m_pbr.m_albedo = rgb(0x888888); m.m_pbr.m_metallic = 1.0f; m.m_pbr.m_roughness = 0.66f;
	});

	gfx::radiance(root, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	gfx::shape(root, Sphere(), Symbol(), 0U, &testmat);

	span<float> memory = batch->begin(segments.size(), sizeof(Lines::Segment));
	memcpy(memory.data(), segments.data(), memory.size() * sizeof(float));

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::columns(*dock, { 0.3f, 0.7f });

		ui::slider_field<float>(sheet, "line width", { material.m_line.m_line_width, { 0.f, 20.f, 0.1f } });

		ui::input_field<bool>(sheet, "dased", material.m_line.m_dashed);
		ui::slider_field<float>(sheet, "dash scale", { material.m_line.m_dash_scale, { 0.f, 20.f, 0.1f } });
		ui::slider_field<float>(sheet, "dash size", { material.m_line.m_dash_size,  { 0.f, 20.f, 0.1f } });
		ui::slider_field<float>(sheet, "dash gap", { material.m_line.m_dash_gap,   { 0.f, 20.f, 0.1f } });
	}
}
			