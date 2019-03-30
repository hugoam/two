// performance_doublesided.js

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controller(viewer);

var camera = viewer.camera;
var scene = viewer.scene;

if (init) {
    this.mouse = new two.vec2(0.0);
    
    camera.fov = 50.0; camera.near = 1.0; camera.far = 20000.0;
    camera.eye.z = 3200.0;

    var pbr = app.gfx.programs.file('pbr/pbr');

    var reflection = app.gfx.textures.file('cube/royal.jpg.cube');
    scene.env.radiance.texture = reflection;

    //var material = new THREE.MeshPhongMaterial({ specular: 0x101010, shininess : 100, envMap : reflectionCube, combine : THREE.MixOperation, reflectivity : 0.1, side : THREE.DoubleSide });
    var material = app.gfx.materials.create('twosided');
    var m = material;
    m.program = pbr;
    m.base.cull_mode = two.CullMode.None;
    m.pbr.roughness.value = 0.0;

    //scene.background = new THREE.Color(0x050505);

    //scene.add(new THREE.AmbientLight(0x050505));

    var zeroq = new two.quat(new two.vec3(0.0));
    
    var l0 = scene.nodes().add(new two.Node3(new two.vec3(4000.0, 0.0, 0.0), zeroq));
    scene.lights().add(new two.Light(l0, two.LightType.Point, false, two.rgb(0x0011ff), 1.0, 5500.0));

    var l1 = scene.nodes().add(new two.Node3(new two.vec3(-4000.0, 0.0, 0.0), zeroq));
    scene.lights().add(new two.Light(l1, two.LightType.Point, false, two.rgb(0xff1100), 1.0, 5500.0));

    var l2 = scene.nodes().add(new two.Node3(new two.vec3(0.0), zeroq));
    scene.lights().add(new two.Light(l2, two.LightType.Point, false, two.rgb(0xffaa00), 2.0, 3000.0));

    var geometry = app.gfx.shape(new two.Sphere(1.0, 0.0, Math.PI));

    for(var i = 0; i < 5000; ++i)
    {
        var p = new two.vec3(Math.random() * 10000.0 - 5000.0, Math.random() * 10000.0 - 5000.0, Math.random() * 10000.0 - 5000.0);
        var a = new two.vec3(Math.random() * 2 * Math.PI, Math.random() * 2 * Math.PI, 0.0);
        var s = new two.vec3(Math.random() * 50.0 + 100.0);

        var n = scene.nodes().add(new two.Node3(p, new two.quat(a), s));
        scene.items().add(new two.Item(n, geometry, 0, material));
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
