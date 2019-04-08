// material_cubemap.js

var viewer = two.ui.scene_viewer(panel);
var controls = two.ui.orbit_controls(viewer);
//controls.enableZoom = false;
//controls.enablePan = false;
//controls.minPolarAngle = c_pi / 4;
//controls.maxPolarAngle = c_pi / 1.5;

var scene = viewer.scene;

if(init) {
    this.importerOBJ = new two.ImporterOBJ(app.gfx);
    
    var camera = viewer.camera;
    camera.fov = 50.0; camera.near = 1.0; camera.far = 5000.0;
    camera.eye.z = 2000.0;

    var envmap = app.gfx.textures.file('cube/royal.jpg.cube');
    
    var env = scene.env;
    env.radiance.texture = envmap;
    env.radiance.filter = false;
    env.background.texture = envmap;
    env.background.mode = two.BackgroundMode.Panorama;

    env.radiance.ambient = two.rgb(0xffffff);

    //lights

    var ln = scene.nodes().add(new two.Node3());
    var l = scene.lights().add(new two.Light(ln, two.LightType.Point, false, two.rgb(0xffffff), 2.0, 0.0));
    //light = &ln;

    var phong = app.gfx.programs.file('pbr/phong');
    var lambert = app.gfx.programs.file('pbr/lambert');
    var program = lambert;

    // materials

    var material3 = app.gfx.materials.create('material3'); var m = material3;
        m.program = program;
        m.phong.diffuse.value = two.rgb(0xff6600);
        m.phong.reflectivity.value = 0.3;
        m.phong.env_blend = two.PhongEnvBlendMode.Mix;

    var material2 = app.gfx.materials.create('material2'); m = material2;
        m.program = program;
        m.phong.diffuse.value = two.rgb(0xffee00);
        m.phong.refraction.value = 0.95;

    var material1 = app.gfx.materials.create('material1'); m = material1;
        m.program = program;
        m.phong.diffuse.value = two.rgb(0xffffff);

    var model = app.gfx.models.file('WaltHead');

    var zeroq = new two.quat(new two.vec3(0.0));
    var n0 = scene.nodes().add(new two.Node3(new two.vec3(0.0, -500.0, 0.0), zeroq, new two.vec3(15.0)));
    scene.items().add(new two.Item(n0, model, 0, material1));

    var n1 = scene.nodes().add(new two.Node3(new two.vec3(-900.0, -500.0, 0.0), zeroq, new two.vec3(15.0)));
    scene.items().add(new two.Item(n1, model, 0, material2));

    var n2 = scene.nodes().add(new two.Node3(new two.vec3(900.0, -500.0, 0.0), zeroq, new two.vec3(15.0)));
    scene.items().add(new two.Item(n2, model, 0, material3));
}

