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

    env.radiance.ambient = new two.Colour(1.0);

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

        this.spheres.push({ p: p, s: s, node: n });
    }
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
if(event.valid())
{
    this.mouse.x = (event.relative.x - viewer.frame.size.x / 2.0) * 10.0;
    this.mouse.y = (event.relative.y - viewer.frame.size.y / 2.0) * 10.0;
}

var time = app.gfx.time * -0.01;

for(var i = 0; i < this.spheres.length; i++) {
    
    var sphere = this.spheres[i];
    var p = sphere.p;
    p.x = Math.cos(time * -0.01 + i) * 5000.0;
    p.y = Math.sin(time * -0.01 + i * 1.1) * 5000.0;
    sphere.node.apply(p, zeroq, sphere.s);
}

var camera = viewer.camera;
camera.eye.x += (this.mouse.x - camera.eye.x) * .05;
camera.eye.y += (-this.mouse.y - camera.eye.y) * .05;
