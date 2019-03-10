// geom_sprites.js

var vertex_shader = `$input a_position, a_texcoord0, i_data0
    $output v_uv0, v_scale
    
    #include <common.sh>
    
    void main()
    {
        vec3 i_position = i_data0.xyz;
        vec3 timexyz = i_position + vec3_splat(u_time / 2.0);
        float scale =  sin(timexyz.x * 2.1) + sin(timexyz.y * 3.2) + sin(timexyz.z * 4.3);
        v_scale = scale;
        float size = scale * 10.0 + 10.0;
        vec3 view = mul(u_modelView, vec4(i_position, 1.0)).xyz;
        view += a_position.xyz * size;
        v_uv0 = a_texcoord0;
        gl_Position = mul(u_proj, vec4(view, 1.0));
    
    }`;

var fragment_shader = `$input v_uv0, v_scale
    
    #include <common.sh>
    #include <convert.sh>
    
    void main()
    {
        vec4 color = texture2D(s_color, v_uv0);
        vec3 hsl = hsl_to_rgb(vec3(v_scale/5.0, 1.0, 0.5));
        gl_FragColor = vec4(color.rgb * hsl.rgb, color.a);
        if (color.a < 0.5) discard;
    }`;

var particles = 75000;

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if(typeof this.state == 'undefined') {
    this.state = 1;

    var camera = viewer.camera;
    camera.fov = 50.0; camera.near = 1.0; camera.far = 5000.0;
    camera.eye.z = 1400.0;

    var program = app.gfx.programs.create('circles');
    program.set_block(two.MaterialBlock.Solid);
    program.set_source(two.ShaderType.Vertex, vertex_shader);
    program.set_source(two.ShaderType.Fragment, fragment_shader);

    var texture = app.gfx.textures.file('sprites/circle.png');

    var material = app.gfx.materials.create('circles'); var m = material;
        m.program = program;
        m.base.depth_test = two.DepthTest.Enabled;
        m.base.depth_draw = two.DepthDraw.Enabled;
        m.solid.colour.texture = texture;

    // cool glitch
    //var circle = app.gfx.shape(new two.Circle());
    var circle = app.gfx.shape(new two.Circle(1.0, two.Axis.Z)); // new THREE.CircleBufferGeometry(1, 6);

    var instances = new Float32Array(particles * 4);

    var f = 0;
    for(var i = 0; i < particles; ++i)
    {
        instances[f++] = Math.random() * 2.0 - 1.0;
        instances[f++] = Math.random() * 2.0 - 1.0;
        instances[f++] = Math.random() * 2.0 - 1.0;
        instances[f++] = 0.0; // padding
    }

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, circle, 0, material));
    this.node = n;

    var batch = scene.batches().add(new two.Batch(it, 4 * 4));
    it.batch = batch;

    batch.cache(instances);
}

//var time = app.gfx.time / 2.0;

var scale = new two.vec3(500.0);
var angles = new two.vec3(time * 0.2, time * 0.4, 0.0);
this.node.apply(new two.vec3(0.0), new two.quat(angles), scale);
