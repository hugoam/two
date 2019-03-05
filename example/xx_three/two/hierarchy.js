
var viewer = two.ui.scene_viewer(parent);
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

this.normal = app.gfx.programs().fetch('normal');

this.material = app.gfx.materials().create('normal');
var m = this.material;
m.program = normal;

this.group = nullptr;
this.nodes = [];

if(typeof this.state == 'undefined') {
    this.state = 1;
    
    var camera = viewer.camera;
    camera.fov = 60.0; camera.near = 1.0; camera.far = 10000.0;
    camera.eye.z = 500.0;

    //scene.background = new THREE.Color(0xffffff);
    //scene.fog = new THREE.Fog(0xffffff, 1, 10000);

    var geometry = app.gfx.shape(new two.Cube(50.0));

    var node = two.gfx.nodes(scene).add(new two.Node3());
    group = node;

    for(var i = 0; i < 1000; i++)
    {
        var p = new two.vec3(Math.random(), Math.random(), Math.random()) * 2000.0 - 1000.0;
        var a = new two.vec3(Math.random(), Math.random(), 0.0) * 2 * Math.PI;

        var n = two.gfx.nodes(scene).add(new two.Node3(p, new two.quat(a)));
        two.gfx.items(scene).add(new two.Item(n, geometry, 0U, material));
    }
}

this.mouse = new two.vec2(0.0);
if(var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved))
{
    mouse = (event.relative - viewer.frame.size / 2.0) * 10.0;
}

var time = app.gfx.time;

var rx = Math.sin(time * 0.7) * 0.5;
var ry = Math.sin(time * 0.3) * 0.5;
var rz = Math.sin(time * 0.2f) * 0.5;

var camera = viewer.camera;
camera.eye.x += (mouse.x - camera.eye.x) * 0.05;
camera.eye.y += (-mouse.y - camera.eye.y) * 0.05;

//camera.lookAt(scene.position);

group.transform(new two.vec3(1.0), new two.quat(new two.vec3(rx, ry, rz)), new two.vec3(0.0));
