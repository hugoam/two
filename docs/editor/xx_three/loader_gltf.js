// loader_gltf.js

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);

var camera = viewer.camera;
var scene = viewer.scene;

if(init) {
    this.importerGltf = new two.ImporterGltf(app.gfx);

    camera.fov = 45.0; camera.near = 0.25; camera.far = 20.0;
    camera.eye = new two.vec3(-1.8, 0.9, 2.7);
    camera.target = new two.vec3(0.0, -0.2, -0.2);

    viewer.viewport.to_gamma = true;
    
    var texture = app.gfx.textures.file('cube/bridge.jpg.cube');
    
    var env = scene.env;
    env.radiance.texture = texture;
    env.background.texture = texture;
    env.background.mode = two.BackgroundMode.Panorama;

    var three = app.gfx.programs.fetch('pbr/three');

    var model = app.gfx.models.file('DamagedHelmet'); // .gltf');
    var mesh = model.get_mesh(0);
    mesh.material.program = three;
    mesh.material.pbr.albedo.texture.reload(app.gfx, true);
    
    var n = scene.nodes().add(new two.Node3());
    var i = scene.items().add(new two.Item(n, model));
}
