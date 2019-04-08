// material_displace.js

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);
//controls.enableZoom = false;
//controls.enableDamping = true;

var scene = viewer.scene;

var height = 500; // of camera frustum

var r = 0.0;

if(init) {
    this.importerOBJ = new two.ImporterOBJ(app.gfx);

    var camera = viewer.camera;
    camera.fov = 40.0; camera.near = 1.0; camera.far = 10000.0;
    camera.eye.z = 1500.0;

    viewer.viewport.to_gamma = true;

    var reflection = app.gfx.textures.file('cube/royal.jpg.cube');
    
    var env = scene.env;
    env.radiance.texture = reflection;
    env.radiance.ambient = 0.2;
    env.radiance.colour = two.rgb(0xffffff);

    // lights

    var zeroq = new two.quat(new two.vec3(0.0));
    
    var ln0 = scene.nodes().add(new two.Node3(new two.vec3(0.0, 0.0, 2500.0), zeroq));
    scene.lights().add(new two.Light(ln0, two.LightType.Point, false, two.rgb(0xff0000), 0.5, 0.0));
    this.light = ln0;

    var ln1 = scene.nodes().add(new two.Node3(new two.vec3(0.0), zeroq));
    scene.lights().add(new two.Light(ln1, two.LightType.Point, false, two.rgb(0xff6666), 1.0, 0.0));

    var ln2 = scene.nodes().add(new two.Node3(new two.vec3(-1000.0, 0.0, 1000.0), zeroq));
    scene.lights().add(new two.Light(ln2, two.LightType.Point, false, two.rgb(0x0000ff), 1.0, 0.0));

    var three = app.gfx.programs.file('pbr/three');

    var mat = app.gfx.materials.create('ninja'); var m = mat;
        m.program = three;
        m.pbr.albedo.value = two.rgb(0x888888);
        m.pbr.metallic.value = 1.0;
        m.pbr.roughness.value = 0.4;
        m.lit.normal.texture = app.gfx.textures.file('ninja/normal.jpg');
        m.lit.occlusion.texture = app.gfx.textures.file('ninja/ao.jpg');
        m.lit.displace.texture = app.gfx.textures.file('ninja/displacement.jpg');
        m.lit.displace.value = 2.436143; // from original model
        m.lit.displace_bias = -0.428408;
        // normalScale: vec2(1, -1), // why does the normal map require negation in this case?

    this.material = mat;

    var model = app.gfx.models.file('ninjaHead_Low'); // .obj');
    //geometry.center();

    var n = scene.nodes().add(new two.Node3(new two.vec3(0.0, -175.0 * 25.0, 0.0), zeroq, new two.vec3(25.0)));
    scene.items().add(new two.Item(n, model, 0, mat));
}

var r = time; // * 0.1;

this.light.apply(new two.vec3(2500.0 * Math.cos(r), 2500.0 * Math.sin(r), 0.0));

//this.material.pbr.roughness.value = (Math.cos(r) + 1.0) / 2.0;
this.material.pbr.metallic.value = (Math.cos(r) + 1.0) / 2.0;
this.material.lit.displace.value = (Math.sin(r) + 1.0) / 2.0 * 5.0;

r += 0.01;
