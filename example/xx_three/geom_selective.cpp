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

		"$input a_position, a_color0\n"
		"$output v_color\n"
		"\n"
		"#include <common.sh>\n"
		"\n"
		"void main()\n"
	    "{\n"
		"	v_color = a_color0;\n"
		"	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));\n"
		"\n"
		"}\n";

	return shader;
}

static string fragment_shader()
{
	string shader =

		"$input v_color\n"
		"\n"
		"#include <common.sh>\n"
		"\n"
		"void main()\n"
	    "{\n"
		"	if (v_color.a > 0.0) {\n"
		"		gl_FragColor = vec4(v_color.rgb, 1.0);\n"
		"	} else {\n"
		"		discard;\n"
		"	}\n"
		"\n"
		"}\n";

	return shader;
}

void xx_geom_selective(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	constexpr size_t numLat = 100;
	constexpr size_t numLng = 200;

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Program program = { "program" };
	program.m_blocks[MaterialBlock::Solid] = true;
	program.m_sources[ShaderType::Vertex] = vertex_shader();
	program.m_sources[ShaderType::Fragment] = fragment_shader();

	static Material& material = app.m_gfx.materials().create("material", [](Material& m) {
		m.m_program = &program;
	});

	static Model* model = nullptr;
	static Node3* node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 45.f; camera.m_near = 0.01f; camera.m_far = 10.f;
		camera.m_eye.z = 3.5f;

		//scene.add(new THREE.AmbientLight(0x444444));

		auto addLines = [&](float radius)
		{
			const size_t num_verts = numLat * numLng * 2;

			MeshPacker geometry;
			geometry.m_primitive = PrimitiveType::Lines;

			for(size_t i = 0; i < numLat; ++i)
				for(size_t j = 0; j < numLng; ++j)
				{
					float lat = (randf() * c_pi) / 50.f + float(i) / float(numLat) * c_pi;
					float lng = (randf() * c_pi) / 50.f + float(j) / float(numLng) * c_2pi;

					size_t index = i * numLng + j;
					vec3 point = vec3(sin(lat) * cos(lng), cos(lat), sin(lat) * sin(lng)) * radius;

					geometry.m_positions.push_back(vec3(0.f));
					geometry.m_positions.push_back(point);

					Colour color0 = hsl(lat / c_pi, 1.f, 0.2f);
					geometry.m_colours.push_back(color0);

					Colour color1 = hsl(lat / c_pi, 1.f, 0.7f);
					geometry.m_colours.push_back(color1);
				}

			model = &app.m_gfx.create_model_geo("lines", geometry, false); // , dynamic = true);

			Node3& n = gfx::nodes(scene).add(Node3());
			Item& it = gfx::items(scene).add(Item(n, *model, 0U, &material));
			UNUSED(it);
			node = &n;

			//updateCount();
		};

		addLines(1.f);
	}

	//var numLinesCulled = 0;

	//function updateCount() {
	//
	//	var str = '1 draw call, ' + numLat * numLng + ' lines, ' + numLinesCulled + ' culled (<a target="_blank" href="http://callum.com">author</a>)';
	//	document.getElementById('title').innerHTML = str.replace(/\B(?=(\d{3})+(?!\d))/g, ",");
	//
	//}

	auto hideLines = []()
	{
		GpuMesh gpu_lines = model->m_items[0].m_mesh->begin();

		for(size_t i = 0; i < gpu_lines.m_vertex_count; i += 2)
		{
			if(randf() < 0.75f) continue;

			//if(geometry.attributes.visible.array[i + 0]) {
			//	++numLinesCulled;
			//}

			//geometry.attributes.visible.array[i + 0] = 0;
			//geometry.attributes.visible.array[i + 1] = 0;
		}

		//geometry.attributes.visible.needsUpdate = true;

		//updateCount();
	};

	auto showLines = []()
	{
		//numLinesCulled = 0;
			
		GpuMesh gpu_lines = model->m_items[0].m_mesh->begin();

		for(size_t i = 0; i < gpu_lines.m_vertex_count; i += 2)
		{
			//Colour col = ;
			//col.a = 1.f;
			//gpu_lines.m_writer.colour()
			//geometry.attributes.visible.array[i + 0] = 1;
			//geometry.attributes.visible.array[i + 1] = 1;
		}

		//geometry.attributes.visible.needsUpdate = true;

		//updateCount();
	};


	const float time = app.m_gfx.m_time; // * 0.001;

	vec3 angles = vec3(time * 0.25f, time * 0.5f, 0.f);
	node->apply(vec3(0.f), quat(angles));
}
