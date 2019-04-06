// material_array.js

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);

var scene = viewer.scene;

if(init) {
    var camera = viewer.camera;
    camera.fov = 40.0; camera.near = 1.0; camera.far = 2000.0;
    camera.eye = new two.vec3(0.0, 400.0, 400.0 * 3.5);

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
    //this.tonemap.mode = two.TonemapMode.Uncharted2;
    //this.tonemap.exposure = 0.75;
    
    //scene.add(new THREE.AmbientLight(0x222222));

    // Materials

    //var texture = app.gfx.textures.file('planets/moon_1024.jpg');
    //imgTexture.anisotropy = 16;

    var subdiv = 5;
    var width = 400.0;
    var radius = (width / subdiv) * 0.8 * 0.5;
    var step = 1.0 / subdiv;

    var geometry = app.gfx.shape(new two.Sphere(radius));

    var index = 0;

    var pbr = app.gfx.programs.file('pbr/pbr');

    var zeroq = new two.quat(new two.vec3(0.0));
    
    for(var alpha = 0.0; alpha <= 1.0; alpha += step)
        for(var beta = 0.0; beta <= 1.0; beta += step)
            for(var gamma = 0.0; gamma <= 1.0; gamma += step)
            {
                // basic monochromatic energy preservation
                var diffuse = two.hsl(alpha, 0.5, gamma * 0.5 + 0.1);

                var name = 'variation' + index.toString();
                var material = app.gfx.materials.create(name); var m = material;
                    m.program = pbr;
                    m.pbr.albedo.value = diffuse;
                    //m.pbr.albedo.texture = texture;
                    //m.pbr.normal.texture = texture;
                    m.lit.normal.value = 1.0;
                    m.pbr.metallic.value = beta;
                    m.pbr.roughness.value = 1.0 - alpha;
                    m.pbr.scene_environment = index % 2 == 0 ? false : true;

                index++;

                var p = new two.vec3(alpha * 400.0 - 200.0, beta * 400.0 - 200.0, gamma * 400.0 - 200.0);

                var node = scene.nodes().add(new two.Node3(p, zeroq));
                scene.items().add(new two.Item(node, geometry, 0, material));
            }

    var sphere = app.gfx.shape(new two.Sphere(4.0));
    var l = scene.nodes().add(new two.Node3());
    //var il = scene.items().add(new two.Item(l, sphere, 0, two.gfx.solid_material(app.gfx, 'light', new two.Colour(1.0))));
    var ll = scene.lights().add(new two.Light(l, two.LightType.Point, false, two.rgb(0xffffff), 2.0, 800.0));
    this.light = l;
    
    var dir = two.look_dir(new two.vec3(-1.0, -1.0, -1.0))
    var dl = scene.nodes().add(new two.Node3(new two.vec3(0.0), dir));
    scene.lights().add(new two.Light(dl, two.LightType.Direct, false, two.rgb(0xffffff)));
}

var timer = time * 0.1;

//camera.position.x = cos(timer) * 800;
//camera.position.z = sin(timer) * 800;

var p = new two.vec3(Math.sin(timer * 7.0) * 300.0, Math.cos(timer * 5.0) * 400.0, Math.cos(timer * 3.0) * 300.0);
this.light.apply(p);
