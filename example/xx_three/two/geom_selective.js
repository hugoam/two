//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#include <cstring>

using namespace mud;

var vertex_shader()
{
	var shader =

		'$input a_position, a_color0\n'
		'$output v_color\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'void main()\n'
	    '{\n'
		'	v_color = a_color0;\n'
		'	gl_Position = u_modelViewProj * new two.vec4(a_position, 1.0);\n'
		'\n'
		'}\n';

	return shader;
}

var fragment_shader()
{
	var shader =

		'$input v_color\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'void main()\n'
	    '{\n'
		'	if (v_color.a > 0.0) {\n'
		'		gl_FragColor = new two.vec4(v_color.rgb, 1.0);\n'
		'	} else {\n'
		'		discard;\n'
		'	}\n'
		'\n'
		'}\n';

	return shader;
}

void xx_geoselective(Shell app, var parent, Dockbar dockbar)
{
	var numLat = 100;
	var numLng = 200;

	var viewer = two.ui.scene_viewer(app.ui.begin());
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	var vertex = vertex_shader();
	var fragment = fragment_shader();

	var program = { 'program', {}, { nullptr, fragment.c_str(), nullptr, vertex.c_str() } };
	program.blocks[MaterialBlock::Solid] = true;

	this.material = app.gfx.materials.create('material'); var m = material;
		m.program = program;
		m.base.geometry_filter = uint32_t(1 << uint(PrimitiveType::Lines)); // @todo this should not be necessary: in the program ?
	});

	Model* model = nullptr;
	this.node = nullptr;

	bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 45.0; camera.near = 0.01; camera.far = 10.0;
		camera.eye.z = 3.5;

		//scene.add(new THREE.AmbientLight(0x444444));

		function addLines = [](var radius)
		{
			var nuverts = numLat * numLng * 2;

			MeshPacker geometry;
			geometry.primitive = PrimitiveType::Lines;

			for(var i = 0; i < numLat; ++i)
				for(var j = 0; j < numLng; ++j)
				{
					var lat = (Math.random() * Math.PI) / 50.0 + float(i) / float(numLat) * Math.PI;
					var lng = (Math.random() * Math.PI) / 50.0 + float(j) / float(numLng) * 2 * Math.PI;

					var index = i * numLng + j;
					var povar = new two.vec3(Math.sin(lat) * Math.cos(lng), Math.cos(lat), Math.sin(lat) * Math.sin(lng)) * radius;

					geometry.positions.push(new two.vec3(0.0));
					geometry.positions.push(point);

					var color0 = two.hsl(lat / Math.PI, 1.0, 0.2);
					geometry.colours.push(color0);

					var color1 = two.hsl(lat / Math.PI, 1.0, 0.7);
					geometry.colours.push(color1);
				}

			model = app.gfx.create_model('lines', geometry, false); // , dynamic = true);

			var n = scene.nodes().add(new two.Node3());
			var it = scene.items().add(new two.Item(n, *model, 0, material));
			node = n;

			//updateCount();
		};

		addLines(1.0);
	}

	//var numLinesCulled = 0;

	//function updateCount() {
	//
	//	var str = '1 draw call, ' + numLat * numLng + ' lines, ' + numLinesCulled + ' culled (<a target='_blank' href='http://callum.com'>author</a>)';
	//	document.getElementById('title').innerHTML = str.replace(/\B(?=(\d{3})+(?!\d))/g, ',');
	//
	//}

	function hideLines = []()
	{
		GpuMesh gpu_lines = model->items[0].mesh->begin();

		for(var i = 0; i < gpu_lines.vertex_count; i += 2)
		{
			if(Math.random() < 0.75) continue;

			//if(geometry.attributes.visible.array[i + 0]) {
			//	++numLinesCulled;
			//}

			//geometry.attributes.visible.array[i + 0] = 0;
			//geometry.attributes.visible.array[i + 1] = 0;
		}

		//geometry.attributes.visible.needsUpdate = true;

		//updateCount();
	};

	function showLines = []()
	{
		//numLinesCulled = 0;
			
		GpuMesh gpu_lines = model->items[0].mesh->begin();

		for(var i = 0; i < gpu_lines.vertex_count; i += 2)
		{
			//var col = ;
			//col.a = 1.0;
			//gpu_lines.writer.colour()
			//geometry.attributes.visible.array[i + 0] = 1;
			//geometry.attributes.visible.array[i + 1] = 1;
		}

		//geometry.attributes.visible.needsUpdate = true;

		//updateCount();
	};


	var time = app.gfx.time; // * 0.001;

	var angles = new two.vec3(time * 0.25, time * 0.5, 0.0);
	node.apply(new two.vec3(1.0), new two.quat(angles), new two.vec3(0.0));
}
