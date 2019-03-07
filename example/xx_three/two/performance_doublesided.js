
var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var camera = viewer.camera;
var scene = viewer.scene;

if(typeof this.state == 'undefined') {
    this.state = 1;

    camera.fov = 50.0; camera.near = 1.0; camera.far = 20000.0;
    camera.eye.z = 3200.0;

    var pbr = app.gfx.programs.file('pbr/pbr');

    var reflection = app.gfx.textures.file('SwedishRoyalCastle.cube');
    //scene.env.radiance. = reflection;

    //var material = new THREE.MeshPhongMaterial({ specular: 0x101010, shininess : 100, envMap : reflectionCube, combine : THREE.MixOperation, reflectivity : 0.1, side : THREE.DoubleSide });
    var material = app.gfx.materials.create('material');
    var m = material;
    m.program = pbr;
    m.base.cull_mode = two.CullMode.None;

    //scene.background = new THREE.Color(0x050505);

    //scene.add(new THREE.AmbientLight(0x050505));

    var l0 = scene.nodes().add(new two.Node3(new two.vec3(4000.0, 0.0, 0.0)));
    scene.lights().add(Light(l0, LightType::Point, false, two.rgb(0x0011ff), 1.0, 5500.0));

    var l1 = scene.nodes().add(new two.Node3(new two.vec3(-4000.0, 0.0, 0.0)));
    scene.lights().add(Light(l1, LightType::Point, false, two.rgb(0xff1100), 1.0, 5500.0));

    var l2 = scene.nodes().add(new two.Node3(new two.vec3(0.0)));
    scene.lights().add(Light(l2, LightType::Point, false, two.rgb(0xffaa00), 2.0, 3000.0));

    var geometry = app.gfx.shape(new two.Sphere());
    //new THREE.SphereBufferGeometry(1, 32, 16, 0, PI);

    for(var i = 0; i < 5000; ++i)
    {
        var p = new two.vec3(Math.random(), Math.random(), Math.random()) * 10000.0 - 5000.0;
        var a = new two.vec3(Math.random(), Math.random(), 0.0) * 2 * Math.PI;
        var s = new two.vec3(Math.random()) * 50.0 + 100.0;

        var n = scene.nodes().add(new two.Node3(p, new two.quat(a), s));
        scene.items().add(new two.Item(n, geometry, 0, material));
    }
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
if(event.valid())
{
    var coord = event.relative;
    
    camera.eye.x += (coord.x - camera.eye.x) * 0.05;
    camera.eye.y += (-coord.y - camera.eye.y) * 0.05;
}
