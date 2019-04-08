// loader_ply.js

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);

var scene = viewer.scene;

if(init) {
    this.importerPLY = new two.ImporterPLY(app.gfx);
    
    var camera = viewer.camera;
    camera.fov = 35.0; camera.near = 1.0; camera.far = 15.0;
    camera.eye = new two.vec3(3.0, 0.15, 3.0);
    camera.target = new two.vec3(0.0, -0.1, 0.0);

    var bg = two.to_linear(two.rgb(0x72645b));
    bg = new two.Colour(bg.r, bg.g, bg.b);
    
    viewer.viewport.to_gamma = true;
    viewer.viewport.clear_colour = bg;
    
    var env = scene.env;
    env.background.colour = bg;
    
    env.fog.enabled = true;
    env.fog.colour = bg;
    env.fog.depth_begin = 2.0;
    env.fog.depth_end = 15.0;
    
    var zeroq = new two.quat(new two.vec3(0.0));

    function add_light(scene, r, color, intensity, shadows) {

        var n = scene.nodes().add(new two.Node3(new two.vec3(0.0), r));
        var l = scene.lights().add(new two.Light(n, two.LightType.Direct, shadows, color, intensity));
        //l.shadow_range = 4.0;
        //l.shadow.bias = -0.001;
    }

    var three = app.gfx.programs.fetch('pbr/three');
    var phong = app.gfx.programs.fetch('pbr/phong');

    // Ground

    var groundmat = app.gfx.materials.create('ground'); var m = groundmat;
        m.program = phong;
        m.phong.diffuse.value = two.rgb(0x999999);
        m.phong.specular.value = two.rgb(0x101010);
        // Phong

    var ground = app.gfx.shape(new two.Rect(new two.vec2(0.0), new two.vec2(40.0)));
    var n = scene.nodes().add(new two.Node3(new two.vec3(0.0, -0.5, 0.0), zeroq));
    scene.items().add(new two.Item(n, ground, 0, groundmat));

    var material = app.gfx.materials.create('ply'); m = material;
        m.program = three;
        m.base.flat_shaded = true;
        m.pbr.albedo.value = two.rgb(0x0055ff);
        m.pbr.roughness.value = 0.5;
        m.pbr.metallic.value = 0.5;

    // PLY file

    var dolphin = app.gfx.models.file('dolphins'); // .ply
    
    var ndolphin = scene.nodes().add(new two.Node3(new two.vec3(-0.2, 0.0, 0.3), new two.quat(new two.vec3(-Math.PI / 2, 0.0, 0.0)), new two.vec3(0.001)));
    scene.items().add(new two.Item(ndolphin, dolphin, 0, material));

    var lucy = app.gfx.models.file('Lucy100k'); // .ply

    var nlucy = scene.nodes().add(new two.Node3(new two.vec3(-0.2, -0.02, -0.2), zeroq, new two.vec3(0.0006)));
    scene.items().add(new two.Item(nlucy, lucy, 0, material));

    // Lights

    var skylight = scene.env.skylight;
    skylight.enabled = true;
    skylight.intensity = 1.0;
    skylight.position = new two.vec3(0.0, 1.0, 0.0);
    skylight.color = two.rgb(0x443333);
    skylight.ground = two.rgb(0x111122);

    add_light(scene, new two.quat(-0.325, 0.325, 0.0, 0.888), two.rgb(0xffffff), 1.35, true);
    add_light(scene, new two.quat(-0.816, 0.408, 0.0, 0.408), two.rgb(0xffaa00), 1.0, true);
    
    //add_light(scene, new two.vec3(-1.0, -1.0, -1.0), two.rgb(0xffffff), 1.35, true);
    //add_light(scene, new two.vec3(-0.5, -1.0, 1.0), two.rgb(0xffaa00), 1.0, true);
}

var timer = app.gfx.time * 0.5;

var camera = viewer.camera;
camera.eye.x = Math.sin(timer) * 2.5;
camera.eye.z = Math.cos(timer) * 2.5;
