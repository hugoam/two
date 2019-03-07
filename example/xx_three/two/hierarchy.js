// hierarchy.js

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;


if(typeof this.state == 'undefined') {
    this.state = 1;

    this.mouse = new two.vec2(0.0);

    this.group; // = nullptr;
    this.nodes = [];

    var normal = app.gfx.programs.fetch('normal');

    var material = app.gfx.materials.create('normal');
    var m = material;
    m.program = normal;

    var camera = viewer.camera;
    camera.fov = 60.0; camera.near = 1.0; camera.far = 10000.0;
    camera.eye.z = 500.0;

    var scene = viewer.scene;
    scene.env.background.colour = two.rgb(0xffffff);
    //scene.fog = new THREE.Fog(0xffffff, 1, 10000);

    var geometry = app.gfx.shape(new two.Cube(new two.vec3(50.0)));

    var node = scene.nodes().add(new two.Node3());
    group = node;

    for(var i = 0; i < 1000; i++)
    {
        var p = new two.vec3(Math.random() * 2000.0 - 1000.0, Math.random() * 2000.0 - 1000.0, Math.random() * 2000.0 - 1000.0);
        var a = new two.vec3(Math.random() * 2 * Math.PI, Math.random() * 2 * Math.PI, 0.0);
        //var p = new two.vec3(Math.random(), Math.random(), Math.random()) * 2000.0 - 1000.0;
        //var a = new two.vec3(Math.random(), Math.random(), 0.0) * 2 * Math.PI;

        var n = scene.nodes().add(new two.Node3(p, new two.quat(a)));
        scene.items().add(new two.Item(n, geometry, 0, material));
    }
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
if(event.valid())
{
    this.mouse.x = (event.relative.x - viewer.frame.size.x / 2.0) * 10.0;
    this.mouse.y = (event.relative.y - viewer.frame.size.y / 2.0) * 10.0;
}

var rx = Math.sin(time * 0.7) * 0.5;
var ry = Math.sin(time * 0.3) * 0.5;
var rz = Math.sin(time * 0.2) * 0.5;

var camera = viewer.camera;
camera.eye.x += (this.mouse.x - camera.eye.x) * 0.05;
camera.eye.y += (-this.mouse.y - camera.eye.y) * 0.05;

group.apply(new two.vec3(1.0), new two.quat(new two.vec3(rx, ry, rz)), new two.vec3(0.0));
