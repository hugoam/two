// geom_lines.js

var segments = 10000;

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if(typeof this.state == 'undefined') {
    this.state = 1;

    var camera = viewer.camera;
    camera.fov = 27.0; camera.near = 1.0; camera.far = 4000.0;
    camera.eye.z = 2750.0;

    //this.program = app.gfx.programs.fetch('line');
    var program = app.gfx.programs.fetch('solid');

    var material = app.gfx.materials.create('lines'); var m = material;
        m.program = program;
        m.base.shader_color = two.ShaderColor.Vertex;
    

    var geometry = new two.MeshPacker();
    geometry.primitive = two.PrimitiveType.LineStrip;

    var r = 800.0; var r2 = r / 2.0;

    for(var i = 0; i < segments; i++)
    {
        var p = new two.vec3(Math.random() * r - r2, Math.random() * r - r2, Math.random() * r - r2);
        var c = new two.Colour(p.x / r + 0.5, p.y / r + 0.5, p.z / r + 0.5);

        geometry.position(p);
        geometry.colour(c);
    }

    var model = app.gfx.create_model_geo('lines', geometry);

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, model, 0, material));
    this.node = n;
}

//var time = app.gfx.time / 2.0; // * 0.001;

var angles = new two.vec3(time * 0.25, time * 0.5, 0.0);
this.node.apply(new two.vec3(0.0), new two.quat(angles));

