// refraction_balls.js

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);

var camera = viewer.camera;
var scene = viewer.scene;

var zeroq = new two.quat(new two.vec3(0.0));

if(init) {
    this.mouse = new two.vec2(0.0);
    
    camera.fov = 60.0; camera.near = 1.0; camera.far = 100000.0;
    camera.eye.z = 3200.0;

    var refraction = app.gfx.textures.file('cube/park.jpg.cube');
    
    var env = scene.env;
    env.radiance.texture = refraction;
    env.radiance.filter = false;
    env.background.texture = refraction;
    env.background.mode = two.BackgroundMode.Panorama;

    var sphere = app.gfx.shape(new two.Sphere(100.0));

    var phong = app.gfx.programs.file('pbr/phong');

    var material = app.gfx.materials.create('balls'); var m = material;
        m.program = phong;
        m.phong.refraction.value = 0.95;
    
    this.spheres = [];
    for(var i = 0; i < 500; i++) {
        
        var p = new two.vec3(Math.random() * 10000.0 - 5000.0, Math.random() * 10000.0 - 5000.0, Math.random() * 10000.0 - 5000.0);
        var s = new two.vec3(Math.random() * 3.0 + 1.0);
        var n = scene.nodes().add(new two.Node3(p, zeroq, s));
        scene.items().add(new two.Item(n, sphere, 0, material));

        spheres.push({ p: p, s: s, node: n });
    }
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
if(event.valid())
{
    this.mouse.x = (event.relative.x - viewer.frame.size.x / 2.0) * 10.0;
    this.mouse.y = (event.relative.y - viewer.frame.size.y / 2.0) * 10.0;
}

//var timer = app.gfx.time * -0.0001;

for(var i = 0; i < spheres.length; i++) {
    
    var p = spheres[i].p;
    p.x = Math.cos(time * -0.01 + i) * 5000.0;
    p.y = Math.sin(time * -0.01 + i * 1.1) * 5000.0;
    spheres[i].node.apply(p, zeroq, spheres[i].s);
}

var camera = viewer.camera;
camera.eye.x += (mouse.x - camera.eye.x) * .05;
camera.eye.y += (-mouse.y - camera.eye.y) * .05;
