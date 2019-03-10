//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#include <cstring>

#define SORT 0

using namespace mud;

static string vertex_shader()
{
	string shader =

		"$input a_position, a_texcoord0, i_data0\n"
		"$output v_uv0, v_scale\n"
		"\n"
		"#include <common.sh>\n"
		"\n"
		"void main()\n"
	    "{\n"
		"   vec3 i_position = i_data0.xyz;"
		"	vec3 timexyz = i_position + vec3_splat(u_time / 2.0);\n"
		"	float scale =  sin(timexyz.x * 2.1) + sin(timexyz.y * 3.2) + sin(timexyz.z * 4.3);\n"
		"	v_scale = scale;\n"
		"	float size = scale * 10.0 + 10.0;\n"
		"	vec3 view = mul(u_modelView, vec4(i_position, 1.0)).xyz;\n"
		"	view += a_position * size;\n"
		"	v_uv0 = vec4(a_texcoord0, 0.0, 0.0);\n"
		"	gl_Position = mul(u_proj, vec4(view, 1.0));\n"
		"\n"
		"}\n";

	return shader;
}

static string fragment_shader()
{
	string shader =

		"$input v_uv0, v_scale\n"
		"\n"
		"#include <common.sh>\n"
		"#include <convert.sh>\n"
		"\n"
		"void main()\n"
	    "{\n"
		"	vec4 color = texture2D(s_color, v_uv0);\n"
		"   vec3 hsl = hsl_to_rgb(vec3(v_scale/5.0, 1.0, 0.5));\n"
		"	gl_FragColor = vec4(color.rgb * hsl.rgb, color.a);\n"
		"	if (color.a < 0.5) discard;\n"
		"}\n";

	return shader;
}

void xx_geom_sprites(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	constexpr size_t particleCount = 75000;

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Program program = { "circles" };
	program.m_blocks[MaterialBlock::Solid] = true;
	program.m_sources[ShaderType::Vertex] = vertex_shader();
	program.m_sources[ShaderType::Fragment] = fragment_shader();

	static Texture& texture = *app.m_gfx.textures().file("sprites/circle.png");

	static Material& material = app.m_gfx.materials().create("circles", [](Material& m) {
		m.m_program = &program;
		m.m_base.m_depth_test = DepthTest::Enabled;
		m.m_base.m_depth_draw = DepthDraw::Enabled;
		//m.m_solid.m_colour = &texture;
	});

	struct Instance { vec3 position; float distance; };
	static vector<Instance> instances(particleCount);

	static Node3* node = nullptr;
	static Batch* batch = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 5000.f;
		camera.m_eye.z = 1400.f;

		// cool glitch
		//Model& circle = app.m_gfx.shape(Circle());
		Model& circle = app.m_gfx.shape(Circle(1.f, Axis::Z)); // new THREE.CircleBufferGeometry(1, 6);

		for(size_t i = 0; i < particleCount; ++i)
		{
			instances[i] = { vec3(randf(), randf(), randf()) * 2.f - 1.f };
		}

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, circle, 0U, &material));
		node = &n;

		batch = &gfx::batches(scene).add(Batch(it, sizeof(Instance)));
		it.m_batch = batch;

		span<float> data = { &instances[0].position.x, instances.size() * sizeof(Instance) / sizeof(float) };
		batch->cache(data);
	}

	const float time = app.m_gfx.m_time / 2.f;

	vec3 scale = vec3(500.f);
	vec3 angles = vec3(time * 0.2f, time * 0.4f, 0.f);
	node->apply(vec3(0.f), quat(angles), scale);
}