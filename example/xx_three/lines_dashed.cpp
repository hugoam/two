//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/array.h>

using namespace mud;

Model& cube_model(GfxSystem& gfx, float size)
{
	const float h = size * 0.5f;

	Lines lines;

	const vec3 positions[] = {
		vec3(-h, -h, -h), vec3(-h,  h, -h),
		vec3(-h,  h, -h), vec3( h,  h, -h),
		vec3( h,  h, -h), vec3( h, -h, -h),
		vec3( h, -h, -h), vec3(-h, -h, -h),
		vec3(-h, -h,  h), vec3(-h,  h,  h),
		vec3(-h,  h,  h), vec3( h,  h,  h),
		vec3( h,  h,  h), vec3( h, -h,  h),
		vec3( h, -h,  h), vec3(-h, -h,  h),
		vec3(-h, -h, -h), vec3(-h, -h,  h),
		vec3(-h,  h,  h), vec3(-h,  h, -h),
		vec3( h,  h, -h), vec3( h,  h,  h),
		vec3( h, -h,  h), vec3( h, -h, -h),
	};

	for(size_t i = 0; i < array_size(positions); i += 2)
		lines.add(positions[i+0], positions[i+1]);

	Model& model = gfx.create_model("cube");
	lines.write(model.get_mesh(0));
	return model;
}

void xx_lines_dashed(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	static Program& program = app.m_gfx.programs().fetch("line");

	static Node3* node0 = nullptr;
	static Node3* node1 = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 200.f;
		camera.m_eye.z = 150.f;

		viewer.m_viewport.m_clear_colour = rgb(0x111111);
		scene.m_env.m_fog = { true, 1.f, rgb(0x111111), true, 150.f, 200.f };

		constexpr size_t subdiv = 6;
		constexpr int recursion = 1;

		vector<vec3> points = hilbert3d(vec3(0.f), 25.f, recursion);
		CurveCatmullRom3 curve = { points };

		const size_t divs = points.size() * subdiv;
		Lines lines = { curve, divs };

		Model& spline = app.m_gfx.create_model("spline");
		lines.write(*spline.m_items[0].m_mesh);
		
		auto dash_material = [&](Material& m, const Colour& colour, float dash_size, float dash_gap) {
			m.m_program = &program;
			m.m_solid.m_colour = colour;
			m.m_line.m_dashed = true;
			m.m_line.m_dash_size = dash_size;
			m.m_line.m_dash_gap = dash_gap;
			m.m_base.m_shader_color = ShaderColor::Vertex;
		};

		Material& mat0 = app.m_gfx.materials().create("line0");
		dash_material(mat0, rgb(0xffffff), 1.f, 0.5f);

		Node3& n0 = gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(n0, spline, 0U, &mat0));
		//line.computeLineDistances();
		node0 = &n0;

		Model& cube = cube_model(app.m_gfx, 50.f);

		Material& mat1 = app.m_gfx.materials().create("line1");
		dash_material(mat1, rgb(0xffaa00), 3.f, 1.f);

		Node3& n1 = gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(n1, cube, 0U, &mat1));
		//lineSegments.computeLineDistances();
		node1 = &n1;
	}

	const float time = app.m_gfx.m_time;

	const vec3 angles = vec3(0.25f * time, 0.25f * time, 0.f);

	for(Node3* node : { node0, node1 })
	{
		node->apply(vec3(0.f), quat(angles));
	}
}
