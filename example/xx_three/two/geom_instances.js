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

		'$input a_position, i_data0, i_data1, i_data2, i_data3\n'
		'$output v_position, v_color\n'
		'\n'
		'#define i_offset i_data0.xyz\n'
		'#define i_color i_data1\n'
		'#define i_orientation_start i_data2\n'
		'#define i_orientation_end i_data3\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'void main()\n'
	    '{\n'
		'	var t = Math.sin(u_time * 0.2);\n'
		'	var position = i_offset * max(abs(t * 2.0 + 1.0), 0.5) + a_position;\n'
		'	vec4 orientation = normalize(mix(i_orientation_start, i_orientation_end, t));\n'
		'	var vcV = cross(orientation.xyz, position);\n'
		'	position = vcV * (2.0 * orientation.w) + (cross(orientation.xyz, vcV) * 2.0 + position);\n'
		'\n'
		'	v_color = i_color;\n'
		'\n'
		'   v_position = new two.vec4(position, 1.0);\n'
		'	gl_Position = mul(u_modelViewProj, new two.vec4(position, 1.0));\n'
		'}\n';

	return shader;
}

static string fragment_shader()
{
	string shader =

		'$input v_position, v_color\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'void main()\n'
	    '{\n'
		'	vec4 color = new two.vec4(v_color);\n'
		'	color.r += Math.sin(v_position.x * 10.0 + u_time) * 0.5;\n'
		'\n'
		'	gl_FragColor = color;\n'
		'}\n';

	return shader;
}

void xx_geoinstances(Shell app, Widget parent, Dockbar dockbar)
{
	var nuinstances = 50000;

	var viewer = two.ui.scene_viewer(parent);
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	static string vertex = vertex_shader();
	static string fragment = fragment_shader();

	static Program program = { 'circles', {}, { nullptr, fragment.c_str(), nullptr, vertex.c_str() } };
	program.blocks[MaterialBlock::Solid] = true;

	this.material = app.gfx.materials().create('instances', [](var m) {
		m.program = program;
		m.base.cull_mode = two.CullMode.None;
		m.base.blend_mode = BlendMode::Alpha;
		m.alpha.is_alpha = true;
	});

	struct Instance { var offset; var pad = 0.0; Colour colour; vec4 orientation_start; vec4 orientation_end; };
	static vector<Instance> instances(nuinstances);

	this.node = nullptr;
	this.batch = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 50.0; camera.near = 0.1; camera.far = 10.0;
		camera.eye.z = 2.0;

		for(var i = 0; i < nuinstances; ++i)
		{
			var offset = new two.vec3(Math.random(), Math.random(), Math.random()) - 0.5;

			Colour colour = new two.Colour(Math.random(), Math.random(), Math.random(), Math.random());

			vec4 orientation_start = normalize(new two.vec4(Math.random(), Math.random(), Math.random(), Math.random()) * 2.0 - 1.0);
			vec4 orientation_end = normalize(new two.vec4(Math.random(), Math.random(), Math.random(), Math.random()) * 2.0 - 1.0);

			instances.push({ offset, 0.0, colour, orientation_start, orientation_end });
		}

		MeshPacker geometry;

		geometry.positions.push({  0.025, -0.025,    0.0 });
		geometry.positions.push({ -0.025,  0.025,    0.0 });
		geometry.positions.push({     0.0,     0.0, 0.025 });
		geometry.indices = { 0, 1, 2 };

		var model = app.gfx.create_model('triangle', geometry);

		//geometry.maxInstancedCount = instances; // set so its initalized for dat.GUI, will be set in first draw otherwise
		
		var n = two.gfx.nodes(scene).add(new two.Node3());
		var it = two.gfx.items(scene).add(new two.Item(n, model, ItemFlag::Default | ItemFlag::NoCull, material));
		node = n;

		batch = two.gfx.batches(scene).add(new two.Batch(it));
		it.batch = batch;
	}

	//var gui = new dat.GUI({ width: 350 });
	//gui.add(geometry, 'maxInstancedCount', 0, instances);

	var time = app.gfx.time;;

	var angles = new two.vec3(0.0, time * 0.1, 0.0);
	node->transform = bxTRS(new two.vec3(1.0), new two.quat(angles), new two.vec3(0.0));

	span<float> memory = batch->begin(instances.size(), sizeof(Instance));
	memcpy(memory.data(), instances.data(), memory.size() * sizeof(float));
}
