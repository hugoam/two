
var particles = 500000;

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

this.program = app.gfx.programs.fetch('solid');

this.material = app.gfx.materials.create('points'); var m = material;
    m.program = program;
    m.base.shader_color = two.ShaderColor.Vertex;
    m.point.point_size = 15.0;

this.node = nullptr;

if(init) {
    var camera = viewer.camera;
    camera.fov = 27.0; camera.near = 5.0; camera.far = 3500.0;
    camera.eye.z = 2750.0;

    //scene.background = new THREE.Color(0x050505);
    //scene.fog = new THREE.Fog(0x050505, 2000, 3500);

    var gpu_mesh = two.alloc_mesh(two.PrimitiveType.Points, two.VertexAttribute.Position | two.VertexAttribute.Colour, particles, 0);
    
    var s = 1000.0; var s2 = s / 2.0; // particles spread in the cube

    for(var i = 0; i < particles; i++)
    {
        var p = new two.vec3(Math.random(), Math.random(), Math.random()) * s - s2;
        var c = to_colour(p / s + 0.5);

        // 12 bytes = float3 position (xyz)
        // 4 bytes = uint32 color (rgba)

        gpu_mesh.writer.position(p);
        gpu_mesh.writer.colour(c);
    }

    gpu_mesh.writer.bound();

    var model = app.gfx.create_model_gpu('points', gpu_mesh);

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, model, 0, material));
    this.node = n;
}

var time = app.gfx.time / 2.0;

var angles = new two.vec3(time * 0.25, time * 0.5, 0.0);
this.node.apply(new two.vec3(0.0), new two.quat(angles));
