//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/array.h>
#include <stl/vector.hpp>

#include <cstdio>
#include <cstring>

using namespace mud;

#define FAT 0

void xx_lines_fat(Shell& app, Widget& parent, Dockbar& dockbar)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);
	//controls.minDistance = 10;
	//controls.maxDistance = 500;

	Scene& scene = viewer.m_scene;

	//camera2 = new THREE.PerspectiveCamera(40, 1, 1, 1000);
	//camera2.position.copy(camera.position);
	
	static Lines lines;
	static Batch* batch = nullptr;
	static Material* material = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		camera.m_eye = vec3(-40.f, 0.f, 60.f);

		auto setup_material = [&](Material& m) {
			m.m_solid.m_colour = rgb(0xffffff);
			m.m_line.m_line_width = 5.f;
			m.m_line.m_dashed = true;
			m.m_base.m_shader_color = ShaderColor::Vertex;
		};

		const vector<vec3> points = hilbert3d(vec3(0.f), 20.f, 1);

		const CurveCatmullRom3 curve = { points };
		const uint32_t divisions = uint32_t(12U * points.size());

		const float l = float(divisions);

		lines.start(curve.point(0.f), hsl(0.f, 1.f, 0.5f));

		for(uint32_t i = 0; i < divisions; i++)
		{
			const vec3 position = curve.point(float(i) / l);
			const Colour color = hsl(float(i) / l, 1.f, 0.5f);

			lines.next(position, color);
		}

#if FAT
			// fat line

			Program& program = app.m_gfx.programs().fetch("line_fat");
			material = &app.m_gfx.materials().create("line_fat", setup_material);
			material->m_program = &program;

			const Model& model = app.m_gfx.models().fetch("line");

			Node3& n = gfx::nodes(scene).add(Node3());
			Item& it = gfx::items(scene).add(Item(n, model, 0U, material));
			batch = &gfx::batches(scene).add(Batch(it));
			it.m_batch = batch;
			it.m_visible = true;
#else
			// regular line

			Program& program = app.m_gfx.programs().fetch("line");
			material = &app.m_gfx.materials().create("line", setup_material);
			material->m_program = &program;
			
			Model& model = app.m_gfx.create_model("lines");
			lines.write(*model.m_items[0].m_mesh);

			Node3& n = gfx::nodes(scene).add(Node3());
			Item& it = gfx::items(scene).add(Item(n, model, 0U, material));
			it.m_visible = true;
#endif

	}

	Gnode& root = scene.begin();
	gfx::radiance(root, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

#if FAT
	// this should not be necessary each frame, add cache to the batch ?
	lines.commit(*batch);
#endif

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::columns(*dock, { 0.3f, 0.7f });

		ui::slider_field<float>(sheet, "line width", { material->m_line.m_line_width, { 0.f, 20.f, 0.1f } });

		ui::input_field<bool>(sheet, "dashed", material->m_line.m_dashed);
		ui::slider_field<float>(sheet, "dash scale", { material->m_line.m_dash_scale, { 0.f, 20.f, 0.1f } });
		ui::slider_field<float>(sheet, "dash size",  { material->m_line.m_dash_size,  { 0.f, 20.f, 0.1f } });
		ui::slider_field<float>(sheet, "dash gap",   { material->m_line.m_dash_gap,   { 0.f, 20.f, 0.1f } });
	}
}
			