
var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

struct Params {
    var opacity = 1.0;
    var roughness = 1.0;
    var bumpScale = 1.0;
    var exposure = 3.0;
    var whitePovar = 5.0;
    //toneMapping : 'Uncharted2',
    //renderMode : 'Renderer'
};

Params params;

this.diffuse = app.gfx.textures.file('brick_diffuse.jpg');
//map.encoding = THREE.sRGBEncoding;

this.bump = app.gfx.textures.file('brick_bump.jpg');
this.rough = app.gfx.textures.file('brick_roughness.jpg');

this.pbr = app.gfx.programs.file('pbr/pbr');

this.material = app.gfx.materials.create('material');

var m = this.material;
m.program = pbr;
m.pbr.albedo = rgb(0xffffff);
m.pbr.albedo = diffuse;
m.pbr.normal = -0.05;
m.pbr.normal = bump;
m.pbr.metallic = 0.9;
m.pbr.roughness = 0.8;
m.pbr.roughness = rough;
m.base.uv0_scale = new two.vec2(9.0, 0.5);
m.base.anisotropy = 4.0; // texture filtering anisotropy
// premultipliedAlpha : true,
// transparent : true

this.matfloor = app.gfx.materials.create('floor');
m = this.matfloor;
m.program = pbr;
m.pbr.albedo = rgb(0x888888);
m.pbr.metallic = 0.0;
m.pbr.roughness = 1.0;
m.base.cull_mode = two.CullMode.Front;

this.hdrenv = app.gfx.textures.file('pisaHDR.hdr.cube');

this.mesh = nullptr;

if(typeof this.state == 'undefined') {
    this.state = 1;

    var camera = viewer.camera;
    camera.fov = 40.0; camera.near = 1.0; camera.far = 2000.0;
    camera.eye = new two.vec3(0.0, 40.0, 40.0 * 3.5);

    var geometry = app.gfx.shape(new two.TorusKnot(18.0, 8.0)); // new THREE.TorusKnotBufferGeometry(18, 8, 150, 20);

    var n = scene.nodes().add(new two.Node3());
    scene.items().add(new two.Item(n, geometry, 0, material));
    mesh = n;

    var geomfloor = app.gfx.shape(new two.Cube(100.0));

    var nfloor = scene.nodes().add(new two.Node3(new two.vec3(0.0, 50.0, 0.0), new two.quat(new two.vec3(-Math.PI2, 0.0, 0.0))));
    scene.items().add(new two.Item(n, geomfloor, 0, matfloor));

    // Lights

    //scene.add(new THREE.HemisphereLight(0x111111, 0x000000));

    var ln = scene.nodes().add(new two.Node3(new two.vec3(50.0, 100.0, 50.0)));
    var spot = scene.lights().add(new two.Light(ln, two.LightType.Spot, true, rgb(0xffffff), 1.0, 300.0));
    spot.spot_angle = Math.PI / 7.0;
    spot.attenuation = 2.0;
    spot.spot_attenuation = 0.8;
    //spot.penumbra = 0.8;

    //composer = new THREE.EffectComposer(renderer);
    //composer.setSize(window.innerWidth, window.innerHeight);
    //
    //var renderScene = new THREE.RenderPass(scene, camera);
    //composer.addPass(renderScene);
    //
    //var copyPass = new THREE.ShaderPass(THREE.CopyShader);
    //copyPass.renderToScreen = true;
    //composer.addPass(copyPass);
}

//var gui = new dat.GUI();
//
//gui.add(params, 'toneMapping', Object.keys(toneMappingOptions));
//gui.add(params, 'exposure', 0, 10);
//gui.add(params, 'whitePoint', 0, 10);
//gui.add(params, 'opacity', 0, 1);
//gui.add(params, 'renderMode', ['Renderer', 'Composer']);
//gui.open();

material.pbr.roughness = params.roughness;
material.pbr.normal = -0.05 * params.bumpScale;
material.alpha.alpha = params.opacity;

//if(renderer.toneMapping != toneMappingOptions[params.toneMapping]) {
//
//	renderer.toneMapping = toneMappingOptions[params.toneMapping];
//	standardMaterial.needsUpdate = true;
//	floorMaterial.needsUpdate = true;
//
//}

//renderer.toneMappingExposure = params.exposure;
//renderer.toneMappingWhitePovar = params.whitePoint;

this.rotation = new two.vec3(0.0);
rotation.y += 0.005;

mesh.apply(new two.vec3(1.0), new two.quat(rotation), new two.vec3(0.0));

//if(params.renderMode == 'Composer') {
//	composer.render();
//}
//else {
//	renderer.render(scene, camera);
//}
