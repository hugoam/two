// hierarchy2

var viewer = two.ui.scene_viewer(parent);
//two.ui.orbit_controller(viewer);

if(typeof this.state == 'undefined') {
    this.state = 1;
        
    var camera = viewer.camera;
    camera.fov = 60.0; camera.near = 1.0; camera.far = 15000.0;
    camera.eye.z = 500.0;

    var scene = viewer.scene;
    scene.env.background.colour = two.rgb(0xffffff);
    //scene.background = new THREE.Color(0xffffff);

    this.normal = app.gfx.programs().fetch('normal');
    this.material = app.gfx.materials().create('normal');
    var m = this.material;
    m.program = normal;
    
    var geometry = app.gfx.shape(new two.Cube(50.0));

    var root = two.gfx.nodes(scene).add(new two.Node3(new two.vec3(1000.0, 0.0, 0.0)));
    two.gfx.items(scene).add(new two.Item(root, geometry, 0U, material));

    var amount = 200;

    this.parents = [];
    this.nodes = [];
    
    var offsets = [
        new two.vec3(100.0, 0.0, 0.0), new two.vec3(-100.0, 0.0, 0.0),
        new two.vec3(0.0, -100.0, 0.0), new two.vec3(0.0, 100.0, 0.0),
        new two.vec3(0.0, 0.0, -100.0), new two.vec3(0.0, 0.0, 100.0),
    ];

    for(var p : offsets)
    {
        var parent = root;

        for(var i = 0; i < amount; i++)
        {
            var n = two.gfx.nodes(scene).add(new two.Node3(p));
            two.gfx.items(scene).add(new two.Item(n, geometry, 0U, material));

            this.nodes.push({ parent: parent, node: n, position: p });
            parent = n;
        }
    }
}

this.mouse = new two.vec2(0.0);
if(var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved))
{
    mouse = (event.relative - viewer.frame.size / 2.0) * 10.0;
}

var time = app.gfx.time;

var rx = Math.sin(time * 0.7) * 0.2f;
var ry = Math.sin(time * 0.3) * 0.1;
var rz = Math.sin(time * 0.2f) * 0.1;

var camera = viewer.camera;
camera.eye.x += (mouse.x - camera.eye.x) * 0.05;
camera.eye.y += (-mouse.y - camera.eye.y) * 0.05;

//camera.lookAt(scene.position);

for(var i = 0; i < this.nodes.size(); ++i)
{
    var node = this.nodes[i];
    var rotation = new two.vec3(rx, ry, rz);
    node.node.transform(node.parent, node.position, new two.quat(rotation));
}
