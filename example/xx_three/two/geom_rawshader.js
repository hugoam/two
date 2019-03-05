//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

static string vertex_shader()
{
	string shader =

		'$input a_position, a_color0\n'
		'$output v_position, v_color\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'void main()\n'
		'{\n'
		'	v_position = new two.vec4(a_position, 1.0);\n'
		'	v_color = a_color0;\n'
		'\n'
		'	gl_Position = mul(u_modelViewProj, new two.vec4(a_position, 1.0));\n'
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

void xx_georawshader(Shell app, Widget parent, Dockbar dockbar)
{
	UNUSED(dockbar);
	var triangles = 500;

	var viewer = two.ui.scene_viewer(parent);
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	static string vertex = vertex_shader();
	static string fragment = fragment_shader();

	static Program program = { 'shader', {}, { nullptr, fragment.c_str(), nullptr, vertex.c_str() } };
	program.blocks[MaterialBlock::Solid] = true;
	
	this.material = app.gfx.materials().create('material', [](var m) {
		m.program = program;
		m.base.cull_mode = two.CullMode.None;
		m.base.blend_mode = BlendMode::Alpha;
		m.alpha.is_alpha = true;
	});

	this.node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 50.0; camera.near = 1.0; camera.far = 10.0;
		camera.eye.z = 2.0;

		//scene.background = new THREE.Color(0x101010);

		MeshPacker geometry;

		for(var i = 0; i < triangles; i++)
		{
			var p = new two.vec3(Math.random(), Math.random(), Math.random()) - 0.5;
			Colour c = new two.Colour(Math.random(), Math.random(), Math.random(), Math.random()); // * 255
			geometry.positions.push(p);
			geometry.colours.push(c);
		}

		var model = app.gfx.create_model('model', geometry);
		
		var n = two.gfx.nodes(scene).add(new two.Node3());
		var it = two.gfx.items(scene).add(new two.Item(n, model, 0U, material));
		node = n;
	}

	var time = app.gfx.time;

	var angles = new two.vec3(0.0, time * 0.2f, 0.0);
	node->transform = bxTRS(new two.vec3(1.0), new two.quat(angles), new two.vec3(0.0));
}