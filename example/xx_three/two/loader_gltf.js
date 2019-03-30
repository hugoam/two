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

    var texture = app.gfx.textures.file('cube/bridge.jpg.cube');
    scene.env.radiance.texture = texture;
    scene.env.radiance.energy = 1.0;
    scene.env.background.texture = texture;
    scene.env.background.mode = two.BackgroundMode.Panorama;

    //light = new THREE.HemisphereLight(0xbbbbff, 0x444422);
    //light.position.set(0, 1, 0);
    //scene.add(light);

    var model = app.gfx.models.file('DamagedHelmet'); // .gltf');

    var n = scene.nodes().add(new two.Node3());
    var i = scene.items().add(new two.Item(n, model));
}
