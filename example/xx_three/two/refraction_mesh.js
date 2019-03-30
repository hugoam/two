// refraction_mesh.js

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);

var camera = viewer.camera;
var scene = viewer.scene;

if(init) {
    this.importerPLY = new two.ImporterPLY(app.gfx);
    
    this.mouse = new two.vec2(0.0);
    
    camera.fov = 50.0; camera.near = 1.0; camera.far = 100000.0;
    camera.eye.z = -4000.0;

	var pbr = app.gfx.programs.fetch('pbr/pbr');

    var refraction = app.gfx.textures.file('cube/park.jpg.cube');
    scene.env.radiance.texture = refraction;
    scene.env.background.texture = refraction;
    scene.env.background.mode = two.BackgroundMode.Panorama;

	//var ambient = new THREE.AmbientLight(0xffffff);

    var sphere = app.gfx.shape(new two.Sphere(100.0 * 0.05));

    var ln = scene.nodes().add(new two.Node3());
    scene.lights().add(new two.Light(ln, two.LightType.Point, false, two.rgb(0xffffff), 2.0));
    scene.items().add(new two.Item(ln, sphere, 0, two.gfx.solid_material(app.gfx, 'light', two.rgb(0xffffff))));
    this.light = ln;

    // material samples

    function phong_material(name, colour, refraction, reflectivity) {
        
        var m = app.gfx.materials.create(name);
            m.program = pbr;
            m.pbr.specular_mode = two.PbrSpecularMode.Phong;
            m.pbr.albedo.value = colour;
            m.pbr.metallic.value = 1.0;
            m.pbr.roughness.value = 0.0;
            m.pbr.refraction.value = refraction;
            //m.pbr.reflectivity = reflectivity;
        return m;
    };

    var m3 = phong_material('refraction0', two.rgb(0xccddff), 0.98, 0.9);
    var m2 = phong_material('refraction1', two.rgb(0xccfffd), 0.985);
    var m1 = phong_material('refraction2', two.rgb(0xffffff), 0.98);

    var model = app.gfx.models.file('Lucy100k');

    var s = new two.vec3(1.5);

    var zeroq = new two.quat(new two.vec3(0.0));

    var n0 = scene.nodes().add(new two.Node3(new two.vec3(0.0, 0.0, 0.0), zeroq, s));
    scene.items().add(new two.Item(n0, model, 0, m1));

    var n1 = scene.nodes().add(new two.Node3(new two.vec3(-1500.0, 0.0, 0.0), zeroq, s));
    scene.items().add(new two.Item(n1, model, 0, m2));

    var n2 = scene.nodes().add(new two.Node3(new two.vec3(1500.0, 0.0, 0.0), zeroq, s));
    scene.items().add(new two.Item(n2, model, 0, m3));
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
if(event.valid())
{
    this.mouse.x = (event.relative.x - viewer.frame.size.x / 2.0) * 4.0;
    this.mouse.y = (event.relative.y - viewer.frame.size.y / 2.0) * 4.0;
}

var timer = time * -0.02;

var camera = viewer.camera;
camera.eye.x += (mouse.x - camera.eye.x) * .05;
camera.eye.y += (-mouse.y - camera.eye.y) * .05;

var position = new two.vec3(Math.cos(timer) * 1500.0, Math.sin(timer) * 1500.0, 0.0);
this.light.apply(position);
