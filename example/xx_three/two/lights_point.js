
var viewer = two.ui.scene_viewer(panel);
var controls = two.ui.trackball_controller(viewer);
//controls.dynamicDampingFactor = 0.15;
//controls.keys = [ 65, 83, 68 ];

var scene = viewer.scene;

//scene.background = new THREE.Color( 0x040306 );
//scene.fog = new THREE.Fog( 0x040306, 10, 300 );

if (init) {
    //viewer.camera.eye = new two.vec3(0, 15, 150);
    
    var texture = app.gfx.textures.file('disturb.jpg');
    //texture.repeat.set(20, 10);

    var groundmat = app.gfx.materials.fetch('ground'); //new THREE.MeshPhongMaterial({ color: 0xffffff, map: texture });
    var material = two.gfx.pbr_material(app.gfx, 'object', two.rgb(0xffffff), 0.5, 1.0);

    // GROUND
    
    //var model = app.gfx.shape(new two.Rect(new two.vec2(800.0, 400.0));
    //var node = scene.nodes().add(new two.Node3(new two.vec3(0, -5, 0), new two.quat(-Math.PI / 2.0, 0, 0, 1)));
    //scene.items().add(new two.Item(node, model, 0, groundmat));

    // OBJECTS
    
    var torus = app.gfx.shape(new two.Torus(1.0, 0.1)); //new THREE.TorusBufferGeometry(1.5, 0.4, 8, 16);

    for (var i = 0; i < 5000; i ++) {

        var x = 400.0 * (0.5 - Math.random());
        var y = 50.0 * (0.5 - Math.random()) + 25;
        var z = 200.0 * (0.5 - Math.random());

        var a = 3.14 * (0.5 - Math.random());
        var b = 3.14 * (0.5 - Math.random());

        var n = scene.nodes().add(new two.Node3(new two.vec3(x, y, z), new two.quat(a, b, 0, 1)));
        var it = scene.items().add(new two.Item(n, torus, 0, material));
    }

    // LIGHTS

    var intensity = 2.5;
    var distance = 100;
    var decay = 2.0;

    var colours = [0xff0040, 0x0040ff, 0x80ff80, 0xffaa00, 0x00ffaa, 0xff1100];

    var sphere = app.gfx.shape(new two.Sphere(2.5));

    this.lights = [];

    for(var i = 0; i < 6; ++i)
    {
        var c = two.rgba(colours[i]);
        var m = two.gfx.solid_material(app.gfx, 'light' + i.toString(), c);
        var n = scene.nodes().add(new two.Node3());
        var l = scene.lights().add(new two.Light(n, two.LightType.Point, false, c, intensity, distance));
        l.attenuation = 2.0;
        //l.decay = decay;
        var it = scene.items().add(new two.Item(n, sphere, 0, m));
        
        this.lights.push(n);
    }

    //var direct_node = scene.nodes() += new two.Node3());
    //var direct_light = scene.lights() += Light(direct_node, two.LightType.Direct)); //THREE.DirectionalLight(0xffffff, 0.05);
    //dlight.position.set(0.5, 1, 0).normalize();
}

var root = viewer.scene.begin();
two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', two.BackgroundMode.Radiance);

var coef0 = [0.7, 0.3, 0.7, 0.3, 0.3, 0.7];
var coef1 = [0.3, 0.7, 0.5, 0.5, 0.5, 0.5];

//var time = Date.now() * 0.00025;
var d = 150;

for(var i = 0; i < 6; ++i)
{
    var pos = new two.vec3(Math.sin(time * coef0[i]) * d, 0.0, Math.cos(time * coef1[i]) * d);
    this.lights[i].apply(pos);
}
