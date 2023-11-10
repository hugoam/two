// light_point.js

var viewer = two.ui.scene_viewer(panel);
var controls = two.ui.trackball_controller(viewer);
//controls.dynamicDampingFactor = 0.15;
//controls.keys = [ 65, 83, 68 ];

var scene = viewer.scene;

if (init) {
    var camera = viewer.camera;
    camera.fov = 50.0; camera.near = 1.0; camera.far = 300.0;
    camera.eye = new two.vec3(0.0, 15.0, 150.0);

    var bg = two.to_linear(two.rgb(0x040306));
    viewer.viewport.to_gamma = true;
    viewer.viewport.clear_colour = bg;

    var env = scene.env;
    env.fog.enabled = true;
    env.fog.colour = bg;
    env.fog.depth_begin = 10.0;
    env.fog.depth_end = 300.0;

    // GROUND

    var groundmat = app.gfx.materials.create('ground'); var m = groundmat;
        m.program = app.gfx.programs.fetch('pbr/phong');
        m.base.uv0_scale = new two.vec2(20.0, 10.0);
        m.phong.diffuse.texture = app.gfx.textures.file('disturb.jpg');

    var zeroq = new two.quat(new two.vec3(0.0));
    
    var model = app.gfx.shape(new two.Rect(new two.vec2(0.0), new two.vec2(800.0, 400.0)));
    var node = scene.nodes().add(new two.Node3(new two.vec3(0, -5, 0), zeroq));
    scene.items().add(new two.Item(node, model, 0, groundmat));

    // OBJECTS
    
    //var material = two.gfx.pbr_material(app.gfx, 'lightpoint', two.rgb(0xffffff), 0.5, 1.0);

    var material = app.gfx.materials.create('lightpoint'); m = material;
        m.program = app.gfx.programs.fetch('pbr/three');
        m.pbr.albedo.value = two.rgb(0xffffff);
        m.pbr.metallic.value = 1.0;
        m.pbr.roughness.value = 0.5;
        
    var symbol = new two.Symbol(new two.Colour(1.0)); symbol.subdiv = new two.uvec2(8, 16);
    //var torus = app.gfx.shape(new two.Torus(1.0, 0.1));
    var torus = app.gfx.shape(new two.Torus(1.5, 0.4), symbol);
    
    for (var i = 0; i < 5000; i ++) {

        var x = 400.0 * (0.5 - Math.random());
        var y = 50.0 * (0.5 - Math.random()) + 25;
        var z = 200.0 * (0.5 - Math.random());

        var a = 3.14 * (0.5 - Math.random());
        var b = 3.14 * (0.5 - Math.random());

        //var n = scene.nodes().add(new two.Node3(new two.vec3(x, y, z), new two.quat(a, b, 0, 1)));
        var n = scene.nodes().add(new two.Node3(new two.vec3(x, y, z), new two.quat(new two.vec3(a, b, 0))));
        var it = scene.items().add(new two.Item(n, torus, 0, material));
    }

    // LIGHTS

    var intensity = 2.5;
    var distance = 100;
    var decay = 2.0;

    var colours = [0xff0040, 0x0040ff, 0x80ff80, 0xffaa00, 0x00ffaa, 0xff1100];

    var sphere = app.gfx.shape(new two.Sphere(0.25));

    this.lights = [];

    for(var i = 0; i < 6; ++i)
    {
        var c = two.rgb(colours[i]);
        var m = two.gfx.solid_material(app.gfx, 'light' + i.toString(), c);
        var n = scene.nodes().add(new two.Node3());
        var l = scene.lights().add(new two.Light(n, two.LightType.Point, false, c, intensity, distance));
        l.attenuation = decay;
        var it = scene.items().add(new two.Item(n, sphere, 0, m));
        
        this.lights.push(n);
    }

    var dn = scene.nodes().add(new two.Node3(new two.vec3(0.0), two.look_dir(new two.vec3(-0.5, -1, 0))));
    scene.lights().add(new two.Light(dn, two.LightType.Direct, false, two.rgb(0xffffff), 0.05));
}

var coef0 = [0.7, 0.3, 0.7, 0.3, 0.3, 0.7];
var coef1 = [0.3, 0.7, 0.5, 0.5, 0.5, 0.5];

var time = app.gfx.time * 0.2;

var d = 150;

for(var i = 0; i < 6; ++i)
{
    var pos = new two.vec3(Math.sin(time * coef0[i]) * d, 0.0, Math.cos(time * coef1[i]) * d);
    this.lights[i].apply(pos);
}
