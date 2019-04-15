// geom_instances.js

var vertex_shader = `$input a_position, i_data0, i_data1, i_data2, i_data3
    $output v_position, v_color
    
    #define i_offset i_data0.xyz
    #define i_color i_data1
    #define i_rotation_start i_data2
    #define i_rotation_end i_data3
    
    #include <common.sh>
    
    void main()
    {
    	float t = sin(u_time * 0.2);
    	vec3 position = i_offset * max(abs(t * 2.0 + 1.0), 0.5) + a_position.xyz;
    	vec4 rotation = normalize(mix(i_rotation_start, i_rotation_end, t));
    	vec3 vcV = cross(rotation.xyz, position);
    	position = vcV * (2.0 * rotation.w) + (cross(rotation.xyz, vcV) * 2.0 + position);
    
    	v_color = i_color;
    
        v_position = vec4(position, 1.0);
    	gl_Position = mul(u_modelViewProj, vec4(position, 1.0));
    }`;

var fragment_shader = `$input v_position, v_color
    
    #include <common.sh>
    
    void main()
    {
    	vec4 color = vec4(v_color);
        // @todo u_time doesn't work because of precision mismatch between vertex and fragment
    	//color.r += sin(v_position.x * 10.0 + u_time) * 0.5;
    	color.r += sin(v_position.x * 10.0) * 0.5;
    
    	gl_FragColor = color;
    }`;

var num_instances = 50000;

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if (init) {
    var camera = viewer.camera;
    camera.fov = 50.0; camera.near = 0.1; camera.far = 10.0;
    camera.eye.z = 2.0;

    var program = app.gfx.programs.create('instances');
    program.set_source(two.ShaderType.Vertex, vertex_shader);
    program.set_source(two.ShaderType.Fragment, fragment_shader);
    program.set_block(two.MaterialBlock.Solid);

    var material = app.gfx.materials.create('instances'); var m = material;
        m.program = program;
        m.base.cull_mode = two.CullMode.None;
        m.base.blend_mode = two.BlendMode.Alpha;
        m.alpha.is_alpha = true;

    var instances = new Float32Array(num_instances * 16);

    var j = 0;
    for(var i = 0; i < num_instances; ++i)
    {
        // position
        instances[j++] = Math.random() - 0.5;
        instances[j++] = Math.random() - 0.5;
        instances[j++] = Math.random() - 0.5;
        instances[j++] = 0.0;
        
        // colour
        instances[j++] = Math.random();
        instances[j++] = Math.random();
        instances[j++] = Math.random();
        instances[j++] = Math.random();

        // rotation0
        instances[j++] = Math.random() * 2.0 - 1.0;
        instances[j++] = Math.random() * 2.0 - 1.0;
        instances[j++] = Math.random() * 2.0 - 1.0;
        instances[j++] = Math.random() * 2.0 - 1.0;

        // rotation1
        instances[j++] = Math.random() * 2.0 - 1.0;
        instances[j++] = Math.random() * 2.0 - 1.0;
        instances[j++] = Math.random() * 2.0 - 1.0;
        instances[j++] = Math.random() * 2.0 - 1.0;
    }

    var geometry = new two.MeshPacker();

    geometry.position(new two.vec3(  0.025, -0.025,    0.0));
    geometry.position(new two.vec3( -0.025,  0.025,    0.0));
    geometry.position(new two.vec3(    0.0,    0.0,  0.025));
    geometry.index(0); geometry.index(1); geometry.index(2);

    var model = app.gfx.create_model_geo('triangle', geometry);

    var n = scene.nodes().add(new two.Node3());
    //var it = scene.items().add(new two.Item(n, model, two.ItemFlag.Default | two.ItemFlag.NoCull, material));
    var it = scene.items().add(new two.Item(n, model, 7683 | 256, material));
    this.node = n;

    var batch = scene.batches().add(new two.Batch(it, 4 * 4 * 4));
    it.batch = batch;
    
    batch.cache(instances);
}

var time = app.gfx.time;

var angles = new two.vec3(0.0, time * 0.1, 0.0);
this.node.apply(new two.vec3(0.0), new two.quat(angles));

//this.batch.commit(instances);

