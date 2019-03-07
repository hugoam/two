//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

Model& cube_model(GfxSystem& gfx, float size)
{
	const float h = size * 0.5f;

	MeshPacker geometry;
	geometry.m_primitive = PrimitiveType::Lines;

	geometry.m_positions = {
		vec3(-h, -h, -h), vec3(-h,  h, -h),
		vec3(-h,  h, -h), vec3( h,  h, -h),
		vec3( h,  h, -h), vec3( h, -h, -h),
		vec3( h, -h, -h), vec3(-h, -h, -h),
		vec3(-h, -h,  h), vec3(-h,  h,  h),
		vec3(-h,  h,  h), vec3( h,  h,  h),
		vec3( h,  h,  h), vec3( h, -h,  h),
		vec3( h, -h,  h), vec3(-h, -h,  h),
		vec3(-h, -h, -h), vec3(-h, -h,  h),
		vec3(-h,  h, -h), vec3(-h,  h,  h),
		vec3( h,  h, -h), vec3( h,  h,  h),
		vec3( h, -h, -h), vec3( h, -h,  h)
	};

	return gfx.create_model_geo("cube", geometry);
}

void xx_lines_dashed(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Program& program = app.m_gfx.programs().fetch("line");

	static Node3* node0 = nullptr;
	static Node3* node1 = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 200.f;
		camera.m_eye.z = 150.f;

		//scene.background = new THREE.Color(0x111111);
		//scene.fog = new THREE.Fog(0x111111, 150, 200);

		size_t subdivisions = 6;
		int recursion = 1;

		vector<vec3> points = hilbert3d(vec3(0.f), 25.f, recursion);
		CurveCatmullRom3 curve = { points };

		vector<vec3> samples = curve.points(points.size() * subdivisions);

		MeshPacker geometry;
		geometry.m_primitive = PrimitiveType::Lines;
		geometry.m_positions = samples;

		Model& spline = app.m_gfx.create_model_geo("spline", geometry);

		auto dash_material = [&](const Colour& colour, float dash_size, float dash_gap) -> Material&
		{
			return app.m_gfx.materials().create("line", [&](Material& m) {
				m.m_program = &program;
				m.m_solid.m_colour = colour;
				m.m_line.m_dashed = true;
				m.m_line.m_dash_size = dash_size;
				m.m_line.m_dash_gap = dash_gap;
				m.m_base.m_shader_color = ShaderColor::Vertex;
			});
		};

		Material& mat0 = dash_material(rgb(0xffffff), 1.f, 0.5f);
		Node3& n0 = gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(n0, spline, 0U, &mat0));
		//line.computeLineDistances();
		node0 = &n0;

		Model& cube = cube_model(app.m_gfx, 50.f);

		Material& mat1 = dash_material(rgb(0xffaa00), 3.f, 1.f);
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
