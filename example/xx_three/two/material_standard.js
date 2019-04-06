// material_standard.js

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);
two.ui.trackball_controller(viewer);

var scene = viewer.scene;


if(init) {
    this.importerOBJ = new two.ImporterOBJ(app.gfx);
    
    var camera = viewer.camera;
    camera.fov = 50.0; camera.near = 0.01; camera.far = 1000.0;
    camera.eye.z = 2.0;

    var hdrenv = app.gfx.textures.file('cube/pisaHDR.hdr.cube');
    
    var env = scene.env;
    env.radiance.texture = hdrenv;
    env.background.texture = hdrenv;
    env.background.mode = two.BackgroundMode.Panorama;

    viewer.viewport.to_gamma = true;
    
    //this.tonemap = new two.Tonemap();
    //this.tonemap.enabled = true;
    //this.tonemap.mode = two.TonemapMode.Reinhardt;
    //this.tonemap.exposure = 3.0;
    
    //scene.add(new THREE.HemisphereLight(0x443333, 0x222233, 4));

    var albedo = app.gfx.textures.file('cerberus/Cerberus_A.jpg');
    var metrough = app.gfx.textures.file('cerberus/Cerberus_RM.jpg');
    var normal = app.gfx.textures.file('cerberus/Cerberus_N.jpg');

    var model = app.gfx.models.file('Cerberus');

    var pbr = app.gfx.programs.file('pbr/pbr');

    var material = app.gfx.materials.create('standard'); var m = material;
        m.program = pbr;
        m.pbr.metallic.value = 1.0;
        m.pbr.roughness.value = 1.0;
        m.pbr.albedo.texture = albedo;
        m.pbr.metallic.texture = metrough;
        m.pbr.roughness.texture = metrough;
        m.lit.normal.texture = normal;

    var position = new two.vec3(-0.45, 0.0, 0.0);
    var angles = new two.vec3(0.0, -Math.PI / 2, 0.0);
    var n = scene.nodes().add(new two.Node3(position, new two.quat(angles)));
    scene.items().add(new two.Item(n, model, 0, material));
}
