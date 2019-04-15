// hierarchy2.js

var viewer = two.ui.scene_viewer(panel);
//two.ui.trackball_controller(viewer);

if (init) {
    this.mouse = new two.vec2(0.0);

    var camera = viewer.camera;
    camera.fov = 60.0; camera.near = 1.0; camera.far = 15000.0;
    camera.eye.z = 500.0;

    var scene = viewer.scene;
    //viewer.viewport.clear_colour = two.rgb(0xffffff);
    //scene.env.background.colour = two.rgb(0xffffff);

    var normal = app.gfx.programs.fetch('normal');
    var material = app.gfx.materials.create('hierarchy2');
    var m = material;
    m.program = normal;
    
    var geometry = app.gfx.shape(new two.Cube(new two.vec3(50.0)));
    var zeroquat = new two.quat(new two.vec3(0.0));
            
    var root = scene.nodes().add(new two.Node3(new two.vec3(1000.0, 0.0, 0.0), zeroquat));
    scene.items().add(new two.Item(root, geometry, 0, material));

    var amount = 200;

    this.nodes = [];
    
    var offsets = [
        new two.vec3(100.0, 0.0, 0.0), new two.vec3(-100.0, 0.0, 0.0),
        new two.vec3(0.0, -100.0, 0.0), new two.vec3(0.0, 100.0, 0.0),
        new two.vec3(0.0, 0.0, -100.0), new two.vec3(0.0, 0.0, 100.0),
    ];

    for(var o = 0; o < 6; ++o)
    {
        var p = offsets[o];
        var prev = root;

        for(var i = 0; i < amount; i++)
        {
            var n = scene.nodes().add(new two.Node3(p, zeroquat));
            scene.items().add(new two.Item(n, geometry, 0, material));

            this.nodes.push({ parent: prev, node: n, position: p });
            prev = n;
        }
    }
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
if(event.valid())
{
    this.mouse.x = (event.relative.x - viewer.frame.size.x / 2.0) * 10.0;
    this.mouse.y = (event.relative.y - viewer.frame.size.y / 2.0) * 10.0;
}

var time = app.gfx.time;

var rx = Math.sin(time * 0.7) * 0.2;
var ry = Math.sin(time * 0.3) * 0.1;
var rz = Math.sin(time * 0.2) * 0.1;

var camera = viewer.camera;
camera.eye.x += (this.mouse.x - camera.eye.x) * 0.05;
camera.eye.y += (-this.mouse.y - camera.eye.y) * 0.05;

for(var i = 0; i < this.nodes.length; ++i)
{
    var node = this.nodes[i];
    var rotation = new two.vec3(rx, ry, rz);
    node.node.derive(node.parent, node.position, new two.quat(rotation));
}
