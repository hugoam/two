// geom_selective.js

var vertex_shader = `$input a_position, a_color0
    $output v_color
    
    #include <common.sh>
    
    void main()
    {
        v_color = a_color0;
        gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    
    }`;

var fragment_shader = `$input v_color
    
    #include <common.sh>
    
    void main()
    {
        if (v_color.a > 0.0) {
            gl_FragColor = vec4(v_color.rgb, 1.0);
        } else {
            discard;
        }
    
    }`;

var numLat = 100;
var numLng = 200;

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if (init) {
    var camera = viewer.camera;
    camera.fov = 45.0; camera.near = 0.01; camera.far = 10.0;
    camera.eye.z = 3.5;

    var program = app.gfx.programs.create('program');
    program.set_block(two.MaterialBlock.Solid);
    program.set_source(two.ShaderType.Vertex, vertex_shader);
    program.set_source(two.ShaderType.Fragment, fragment_shader);
    
    this.material = app.gfx.materials.create('material'); var m = material;
        m.program = program;
    
    //scene.add(new THREE.AmbientLight(0x444444));

    var geometry = new two.MeshPacker();
    geometry.primitive = two.PrimitiveType.Lines;

    for(var i = 0; i < numLat; ++i)
        for(var j = 0; j < numLng; ++j)
        {
            var lat = (Math.random() * Math.PI) / 50.0 + i / numLat * Math.PI;
            var lng = (Math.random() * Math.PI) / 50.0 + j / numLng * 2 * Math.PI;

            var index = i * numLng + j;
            var point = new two.vec3(Math.sin(lat) * Math.cos(lng), Math.cos(lat), Math.sin(lat) * Math.sin(lng));

            geometry.position(new two.vec3(0.0));
            geometry.position(point);

            var color0 = two.hsl(lat / Math.PI, 1.0, 0.2);
            geometry.colour(color0);

            var color1 = two.hsl(lat / Math.PI, 1.0, 0.7);
            geometry.colour(color1);
        }

    this.model = app.gfx.create_model_geo('lines', geometry, false); // , dynamic = true);

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, model, 0, material));
    this.node = n;

    //updateCount();
}

//var time = app.gfx.time; // * 0.001;

var angles = new two.vec3(time * 0.25, time * 0.5, 0.0);
this.node.apply(new two.vec3(0.0), new two.quat(angles));

