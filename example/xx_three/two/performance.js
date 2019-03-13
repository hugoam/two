// performance.js

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

//scene.background = new THREE.Color(0xffffff);

var objects = [];

if (init) {
    this.mouse = new two.vec2(0.0);

    var camera = viewer.camera;
    camera.fov = 60.0; camera.near = 1.0; camera.far = 10000.0;
    camera.eye.z = 3200.0;

    var normal = app.gfx.programs.fetch('normal');
    //var normal = app.gfx.programs.fetch('pbr/pbr');

    var material = app.gfx.materials.create('normal');
    var m = material; m.program = normal;

    var suzanne = two.gfx.model_suzanne(app.gfx);

    for(var i = 0; i < 5000; i++)
    {
        var p = new two.vec3(Math.random() * 8000.0 - 4000.0, Math.random() * 8000.0 - 4000.0, Math.random() * 8000.0 - 4000.0);
        var a = new two.vec3(Math.random() * 2 * Math.PI, Math.random() * 2 * Math.PI, 0.0);
        var s = new two.vec3(Math.random() * 50 + 100);

        var n = scene.nodes().add(new two.Node3(p, new two.quat(a), s));
        var it = scene.items().add(new two.Item(n, suzanne, 0, material));

        objects.push({ node: n, position: p, angles: a, scale: s });
    }
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
if(event.valid())
{
    this.mouse.x = (event.relative.x - viewer.frame.size.x / 2.0) * 10.0;
    this.mouse.y = (event.relative.y - viewer.frame.size.y / 2.0) * 10.0;
}

var camera = viewer.camera;
camera.eye.x += (mouse.x - camera.eye.x) * .05;
camera.eye.y += (-mouse.y - camera.eye.y) * .05;

for(var i = 0; i < objects.length; ++i)
{
    var o = objects[i];
    o.angles.x += 0.01;
    o.angles.y += 0.02;

    o.node.apply(o.position, new two.quat(o.angles), o.scale);
}

var root = scene.begin();
two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', two.BackgroundMode.Radiance);

//two.gfx.shape(root, new two.Sphere(), new two.Symbol(), 0, material);
