var vertex_shader = `$input a_position, a_texcoord0, i_data0\n'
    '$output v_texcoord0, v_scale\n'
    '\n'
    '#include <common.sh>\n'
    '\n'
    'void main()\n'
    '{\n'
    '   var i_position = i_data0.xyz;'
    '	var timexyz = i_position + vec3_splat(u_time / 2.0);\n'
    '	var scale =  Math.sin(timexyz.x * 2.1) + Math.sin(timexyz.y * 3.2) + Math.sin(timexyz.z * 4.3);\n'
    '	v_scale = scale;\n'
    '	var size = scale * 10.0 + 10.0;\n'
    '	var view = mul(u_modelView, new two.vec4(i_position, 1.0)).xyz;\n'
    '	view += a_position * size;\n'
    '	v_texcoord0 = new two.vec4(a_texcoord0.xy, 0.0, 0.0);\n'
    '	gl_Position = mul(u_proj, new two.vec4(view, 1.0));\n'
    '\n'
    '}`;

var fragment_shader = `$input v_texcoord0, v_scale\n'
    '\n'
    '#include <common.sh>\n'
    '#include <convert.sh>\n'
    '\n'
    'void main()\n'
    '{\n'
    '	vec4 color = texture2D(s_color, v_texcoord0.xy);\n'
    '   var hsl = hsl_to_rgb(new two.vec3(v_scale/5.0, 1.0, 0.5));\n'
    '	gl_FragColor = new two.vec4(color.rgb * hsl.rgb, color.a);\n'
    '	if (color.a < 0.5) discard;\n'
    '}`;

var particleCount = 75000;

var viewer = two.ui.scene_viewer(app.ui.begin());
two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if(typeof this.state == 'undefined') {
    this.state = 1;

    //struct Instance { var position; var distance; };
    this.instances = new Float32Array(particleCount);

    this.node = nullptr;
    this.batch = nullptr;

    var camera = viewer.camera;
    camera.fov = 50.0; camera.near = 1.0; camera.far = 5000.0;
    camera.eye.z = 1400.0;

    var program = pp.gfx.programs.create('circles');
    program.set_block(two.MaterialBlock.Solid);
    program.set_source(two.ShaderType.Vertex, vertex_shader);
    program.set_source(two.ShaderType.Fragment, fragment_shader);

    var texture = app.gfx.textures.file('sprites/circle.png');

    var material = app.gfx.materials.create('circles'); var m = material;
        m.program = program;
        m.base.depth_test = two.DepthTest.Enabled;
        m.base.depth_draw = two.DepthDraw.Enabled;
        //m.solid.colour = texture;

    // cool glitch
    //var circle = app.gfx.shape(new two.Circle());
    var circle = app.gfx.shape(new two.Circle(1.0, two.Axis.Z)); // new THREE.CircleBufferGeometry(1, 6);

    //geometry = new THREE.InstancedBufferGeometry();
    //geometry.index = circleGeometry.index;
    //geometry.attributes = circleGeometry.attributes;

    for(var i = 0; i < particleCount; ++i)
    {
        instances[i] = { new two.vec3(Math.random(), Math.random(), Math.random()) * 2.0 - 1.0 };
    }

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, circleGeometry, 0, material));
    this.node = n;

    batch = two.gfx.batches(scene).add(new two.Batch(it));
    it.batch = batch;
}

var time = app.gfx.time / 2.0;

var scale = new two.vec3(500.0);
var angles = new two.vec3(time * 0.2, time * 0.4, 0.0);
this.node.apply(scale, new two.quat(angles), new two.vec3(0.0));

span<float> memory = batch->begin(instances.length, sizeof(Instance));
memcpy(memory.data(), instances.data(), memory.length * sizeof(float));
