
var particles = 500000;

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if (init) {
    var camera = viewer.camera;
    camera.fov = 27.0; camera.near = 5.0; camera.far = 3500.0;
    camera.eye.z = 2750.0;

    var program = app.gfx.programs.fetch('point');

    var material = app.gfx.materials.create('points'); var m = material;
        m.program = program;
        m.base.shader_color = two.ShaderColor.Vertex;
        m.point.point_size = 15.0;

    //scene.background = new THREE.Color(0x050505);
    //scene.fog = new THREE.Fog(0x050505, 2000, 3500);

    var s = 1000.0; var s2 = s / 2.0; // particles spread in the cube

    var instances = new Float32Array(particles * 16);
    
    var f =  0;
    for(var i = 0; i < particles; i++)
    {
        var x = Math.random() * s - s2;
        var y = Math.random() * s - s2;
        var z = Math.random() * s - s2;
        
        instances[f++] = x;
        instances[f++] = y;
        instances[f++] = z;
        instances[f++] = 0.0; // padding
        
        instances[f++] = 15.0;
        instances[f++] = 15.0;
        instances[f++] = 0.0; // padding
        instances[f++] = 0.0; // padding
        
        instances[f++] = x / s + 0.5;
        instances[f++] = y / s + 0.5;
        instances[f++] = z / s + 0.5;
        instances[f++] = 1.0;
    }

    var model = app.gfx.models.get('point');

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, model, 0, material));
    this.node = n;

    var batch = scene.batches().add(new two.Batch(it, 16 * 4));
    it.batch = batch;
    
    batch.cache(instances);
}

//var time = app.gfx.time / 2.0;

var angles = new two.vec3(time * 0.25, time * 0.5, 0.0);
this.node.apply(new two.vec3(0.0), new two.quat(angles));

