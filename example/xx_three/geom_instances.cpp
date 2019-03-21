//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#include <cstring>

using namespace mud;

static string vertex_shader()
{
	string shader =

		"$input a_position, i_data0, i_data1, i_data2, i_data3\n"
		"$output v_position, v_color\n"
		"\n"
		"#define i_offset i_data0.xyz\n"
		"#define i_color i_data1\n"
		"#define i_orientation_start i_data2\n"
		"#define i_orientation_end i_data3\n"
		"\n"
		"#include <common.sh>\n"
		"\n"
		"void main()\n"
	    "{\n"
		"	float t = sin(u_time * 0.2);\n"
		"	vec3 position = i_offset * max(abs(t * 2.0 + 1.0), 0.5) + a_position.xyz;\n"
		"	vec4 orientation = normalize(mix(i_orientation_start, i_orientation_end, t));\n"
		"	vec3 vcV = cross(orientation.xyz, position);\n"
		"	position = vcV * (2.0 * orientation.w) + (cross(orientation.xyz, vcV) * 2.0 + position);\n"
		"\n"
		"	v_color = i_color;\n"
		"\n"
		"   v_position = vec4(a_position.xyz, 1.0);\n"
		"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
		"}\n";

	return shader;
}

static string fragment_shader()
{
	string shader =

		"$input v_position, v_color\n"
		"\n"
		"#include <common.sh>\n"
		"\n"
		"void main()\n"
	    "{\n"
		"	vec4 color = vec4(v_color);\n"
		"	color.r += sin(v_position.x * 10.0 + u_time) * 0.5;\n"
		"\n"
		"	gl_FragColor = color;\n"
		"}\n";

	return shader;
}

void xx_geom_instances(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	constexpr size_t num_instances = 50000;

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	static Program program = { "circles" };
	program.m_blocks[MaterialBlock::Solid] = true;
	program.m_sources[ShaderType::Vertex] = vertex_shader();
	program.m_sources[ShaderType::Fragment] = fragment_shader();

	struct Instance { vec3 offset; float pad = 0.f; Colour colour; vec4 orientation_start; vec4 orientation_end; };
	static vector<Instance> instances(num_instances);

	static Node3* node = nullptr;
	static Batch* batch = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 0.1f; camera.m_far = 10.f;
		camera.m_eye.z = 2.f;
		
		Material& material = app.m_gfx.materials().create("instances", [](Material& m) {
			m.m_program = &program;
			m.m_base.m_cull_mode = CullMode::None;
			m.m_base.m_blend_mode = BlendMode::Alpha;
			m.m_alpha.m_is_alpha = true;
		});

		for(size_t i = 0; i < num_instances; ++i)
		{
			vec3 offset = vec3(randf(), randf(), randf()) - 0.5f;

			Colour colour = Colour(randf(), randf(), randf(), randf());

			vec4 orientation_start = normalize(vec4(randf(), randf(), randf(), randf()) * 2.f - 1.f);
			vec4 orientation_end = normalize(vec4(randf(), randf(), randf(), randf()) * 2.f - 1.f);

			instances.push_back({ offset, 0.f, colour, orientation_start, orientation_end });
		}

		MeshPacker geometry;

		geometry.position(vec3(0.025f, -0.025f,    0.f));
		geometry.position(vec3(-0.025f,  0.025f,    0.f));
		geometry.position(vec3(0.f,     0.f, 0.025f));
		geometry.m_indices = { 0, 1, 2 };

		Model& model = app.m_gfx.create_model_geo("triangle", geometry);

		//geometry.maxInstancedCount = instances; // set so its initalized for dat.GUI, will be set in first draw otherwise
		
		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, model, ItemFlag::Default | ItemFlag::NoCull, &material));
		node = &n;

		batch = &gfx::batches(scene).add(Batch(it, sizeof(Instance)));
		it.m_batch = batch;
	}

	//var gui = new dat.GUI({ width: 350 });
	//gui.add(geometry, 'maxInstancedCount', 0, instances);

	const float time = app.m_gfx.m_time;;

	const vec3 angles = vec3(0.f, time * 0.1f, 0.f);
	node->apply(vec3(0.f), quat(angles));

	span<float> memory = batch->begin(instances.size());
	memcpy(memory.data(), instances.data(), memory.size() * sizeof(float));
}
