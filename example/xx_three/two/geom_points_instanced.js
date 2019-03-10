
var particles = 500000;

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if(typeof this.state == 'undefined') {
    this.state = 1;

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

    var instances = new Float32Buffer(particles * 16);
    
    for(var i = 0; i < particles; i++)
    {
        var p = new two.vec3(Math.random() * s - s2, Math.random() * s - s2, Math.random() * s - s2);
        var c = new two.Colour(p / s + 0.5, 1.0);

        instances[i] = { p, 0.0, new two.vec2(15.0), 0.0, 0.0, c };
    }

    var model = app.gfx.models.get('point');

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, model, 0, material));
    this.node = n;

    this.batch = scene.batches().add(new two.Batch(it));
    it.batch = this.batch;
    
    this.batch.cache(instances, 16);
}

//var time = app.gfx.time / 2.0;

var angles = new two.vec3(time * 0.25, time * 0.5, 0.0);
this.node.apply(new two.vec3(0.0), new two.quat(angles));

