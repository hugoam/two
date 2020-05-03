#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;
#else
#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>
#include <stl/vector.hpp>
#include <cstring>
#endif

using namespace two;

#define PAD 0.f

EX(xx_geom_points)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	constexpr size_t particles = 500000;

	static Program& program = app.m_gfx.programs().fetch("point");

	static Node3* node = nullptr;

	static Batch* batch = nullptr;
	struct Instance { vec3 position; float pad0; vec2 scale; float pad1; float pad2; Colour colour; };
	static vector<Instance> instances = vector<Instance>(particles);

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 27.f; camera.m_near = 5.f; camera.m_far = 3500.f;
		camera.m_eye.z = 2750.f;
		
		Material& material = app.m_gfx.materials().create("points", [&](Material& m) {
			m.m_program = &program;
			m.m_base.m_shader_color = ShaderColor::Vertex;
			m.m_point.m_point_size = 15.f;
			m.m_point.m_project = true;
		});

		viewer.m_viewport.m_clear_colour = rgb(0x050505);
		scene.m_env.m_fog = { true, 1.f, rgb(0x050505), true, 2000.f, 3500.f };

		const float s = 1000.f; const float s2 = s / 2.f; // particles spread in the cube

		for(size_t i = 0; i < particles; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * s - s2;
			Colour c = to_colour(p / s + 0.5f);

			instances[i] = { p, PAD, vec2(15.f), PAD, PAD, c };
		}

		Model& model = *app.m_gfx.models().get("point");

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, model, 0U, &material));
		node = &n;

		batch = &gfx::batches(scene).add(Batch(it, sizeof(Instance)));
		it.m_batch = batch;

		batch->cache({ (float*)instances.data(), instances.size() * sizeof(Instance) / sizeof(float) });
	}

	const float time = app.m_gfx.m_time / 2.f;

	vec3 angles = vec3(time * 0.25f, time * 0.5f, 0.f);
	node->apply(vec3(0.f), quat(angles));

	//batch->commit({ (float*)instances.data(), instances.size() * sizeof(Instance) / sizeof(float) });
}
