
var vertex_shader = `$input a_position, a_color0
		$output v_position, v_color
		
		#include <common.sh>
		
		void main()
		{
			v_position = vec4(a_position.xyz, 1.0);
			v_color = a_color0;
		
			gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
		}`;

var fragment_shader = `$input v_position, v_color
		
		#include <common.sh>
		
		void main()
		{
			vec4 color = vec4(v_color);
			color.r += sin(v_position.x * 10.0 + u_time) * 0.5;
		
			gl_FragColor = color;
		}`;


var triangles = 500;

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if (init) {
    var camera = viewer.camera;
    camera.fov = 50.0; camera.near = 1.0; camera.far = 10.0;
    camera.eye.z = 2.0;

    var program = app.gfx.programs.create('rawshader');
    program.set_block(two.MaterialBlock.Solid);
    program.set_source(two.ShaderType.Vertex, vertex_shader);
    program.set_source(two.ShaderType.Fragment, fragment_shader);
    
    var material = app.gfx.materials.create('rawshader'); var m = material;
        m.program = program;
        m.base.cull_mode = two.CullMode.None;
        m.base.blend_mode = two.BlendMode.Alpha;
        m.alpha.is_alpha = true;

    //scene.background = new THREE.Color(0x101010);

    var geometry = new two.MeshPacker();

    for(var i = 0; i < triangles; i++)
    {
        var p = new two.vec3(Math.random() - 0.5, Math.random() - 0.5, Math.random() - 0.5);
        var c = new two.Colour(Math.random(), Math.random(), Math.random(), Math.random()); // * 255
        geometry.position(p);
        geometry.colour(c);
    }

    var model = app.gfx.create_model_geo('model', geometry);
    
    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, model, 0, material));
    this.node = n;
}

//var time = app.gfx.time;

var angles = new two.vec3(0.0, time * 0.2, 0.0);
this.node.apply(new two.vec3(0.0), new two.quat(angles));
