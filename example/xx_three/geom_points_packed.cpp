//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_geom_points_packed(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	constexpr size_t particles = 500000;

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Program& program = app.m_gfx.programs().fetch("solid");

	static Material& material = app.m_gfx.materials().create("points", [](Material& m) {
		m.m_program = &program;
		m.m_base.m_geometry_filter = uint32_t(1 << uint(PrimitiveType::Points)); // @todo this should not be necessary: in the program ?
		m.m_base.m_shader_color = ShaderColor::Vertex;
		m.m_point.m_point_size = 15.f;
	});

	static Node3* node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 27.f; camera.m_near = 5.f; camera.m_far = 3500.f;
		camera.m_eye.z = 2750.f;

		//scene.background = new THREE.Color(0x050505);
		//scene.fog = new THREE.Fog(0x050505, 2000, 3500);

		GpuMesh gpu_mesh = alloc_mesh(PrimitiveType::Points, VertexAttribute::Position | VertexAttribute::Colour, particles, 0);
		
		const float s = 1000.f; const float s2 = s / 2.f; // particles spread in the cube

		for(size_t i = 0; i < particles; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * s - s2;
			Colour c = to_colour(p / s + 0.5f);

			// 12 bytes = float3 position (xyz)
			// 4 bytes = uint32 color (rgba)

			gpu_mesh.m_writer.position(p);
			gpu_mesh.m_writer.colour(c);
		}

		gpu_mesh.m_writer.bound();

		Model& model = app.m_gfx.create_model_gpu("points", gpu_mesh);

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, model, 0U, &material));
		node = &n;
		UNUSED(it);
	}

	const float time = app.m_gfx.m_time / 2.f;

	vec3 angles = vec3(time * 0.25f, time * 0.5f, 0.f);
	node->apply(vec3(0.f), quat(angles));

}